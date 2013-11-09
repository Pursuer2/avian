/* Copyright (c) 2008-2013, Avian Contributors

   Permission to use, copy, modify, and/or distribute this software
   for any purpose with or without fee is hereby granted, provided
   that the above copyright notice and this permission notice appear
   in all copies.

   There is NO WARRANTY for this software.  See license.txt for
   details. */

package regex;

/**
 * Opcodes for the Pike VM.
 * <p>
 * See {@link PikeVM}.
 * </p>
 * 
 * @author Johannes Schindelin
 */
interface PikeVMOpcodes {
  final static int CHAR = 1;
  final static int DOT = 2;
  final static int DOTALL = 3;
  final static int SAVE_OFFSET = 4;
  final static int SPLIT = 5;
  final static int JMP = 6;
}
