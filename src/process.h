/* Copyright (c) 2008-2009, Avian Contributors

   Permission to use, copy, modify, and/or distribute this software
   for any purpose with or without fee is hereby granted, provided
   that the above copyright notice and this permission notice appear
   in all copies.

   There is NO WARRANTY for this software.  See license.txt for
   details. */

#ifndef PROCESS_H
#define PROCESS_H

#include "common.h"
#include "system.h"
#include "machine.h"
#include "constants.h"

namespace vm {

inline int16_t
codeReadInt16(Thread* t, object code, unsigned& ip)
{
  uint8_t v1 = codeBody(t, code, ip++);
  uint8_t v2 = codeBody(t, code, ip++);
  return ((v1 << 8) | v2);
}

inline int32_t
codeReadInt32(Thread* t, object code, unsigned& ip)
{
  uint8_t v1 = codeBody(t, code, ip++);
  uint8_t v2 = codeBody(t, code, ip++);
  uint8_t v3 = codeBody(t, code, ip++);
  uint8_t v4 = codeBody(t, code, ip++);
  return ((v1 << 24) | (v2 << 16) | (v3 << 8) | v4);
}

inline bool
isSuperclass(Thread* t, object class_, object base)
{
  for (object oc = classSuper(t, base); oc; oc = classSuper(t, oc)) {
    if (oc == class_) {
      return true;
    }
  }
  return false;
}

inline bool
isSpecialMethod(Thread* t, object method, object class_)
{
  return (classFlags(t, class_) & ACC_SUPER)
    and strcmp(reinterpret_cast<const int8_t*>("<init>"), 
               &byteArrayBody(t, methodName(t, method), 0)) != 0
    and isSuperclass(t, methodClass(t, method), class_);
}

object
resolveNativeMethod(Thread* t, object method);

inline void
populateMultiArray(Thread* t, object array, int32_t* counts,
                   unsigned index, unsigned dimensions)
{
  if (index + 1 == dimensions or counts[index] == 0) {
    return;
  }

  PROTECT(t, array);

  object spec = className(t, objectClass(t, array));
  PROTECT(t, spec);

  object elementSpec = makeByteArray(t, byteArrayLength(t, spec) - 1);
  memcpy(&byteArrayBody(t, elementSpec, 0),
         &byteArrayBody(t, spec, 1),
         byteArrayLength(t, spec) - 1);

  object class_ = resolveSystemClass(t, elementSpec);
  PROTECT(t, class_);

  for (int32_t i = 0; i < counts[index]; ++i) {
    object a = makeArray(t, counts[index + 1]);
    setObjectClass(t, a, class_);
    set(t, array, ArrayBody + (i * BytesPerWord), a);
    
    populateMultiArray(t, a, counts, index + 1, dimensions);
  }
}

int
findLineNumber(Thread* t, object method, unsigned ip);

} // namespace vm

#endif//PROCESS_H
