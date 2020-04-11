#ifndef CS4417_DEMO_PROG_H
#define CS4417_DEMO_PROG_H

#ifndef CS4417_DEMO_MACHINE_H
#include "machine.h"
#endif

const struct instruction program[] = {
		/* 0000 */ {INST_JMP, REGX, REGX, REGX, 0x50}, // jump to routine for populating index table in memory
		/* 0001 */ {INST_SET, REG(1), REGX, REGX, 3}, // register representing the number of bytes remaining
		/* 0002 */ {INST_SET, REG(2), REGX, REGX, 0}, // register representing the number of bytes read

		// beginning of byte_read routine
		/* 0003 */ {INST_READ, REG(4), REG(0)}, // read a byte from stdin into R4
		/* 0004 */ {INST_JNZ, REG(0), REGX, REGX, 0x06}, // if a byte was read successfully, then hop over the next instruction
		/* 0005 */ {INST_JMP, REGX, REGX, REGX, 0x0a}, // if a byte was not read successfully, then stop reading
		/* 0006 */ {INST_STR, REG(4), REG(2)}, // store the value in R4 into memory location pointed by R2
		/* 0007 */ {INST_ADDI, REG(2), REG(2), REGX, 1}, // increment memory address register
		/* 0008 */ {INST_SUBI, REG(1), REG(1), REGX, 1}, // decrement bytes remaining register
		/* 0009 */ {INST_JNZ, REG(1), REGX, REGX, 0x03}, // if we still have bytes remaining, continue in this subroutine

		// if no bytes were read, jump to end of program
		/* 000a */ {INST_JZ, REG(2), REGX, REGX, 0x3f}, // if no bytes were read, jump to end of program

		// isolate first 6-bits
		/* 000b */ {INST_SET, REG(1), REGX, REGX, 0}, // register containing the byte address
		/* 000c */ {INST_LDR, REG(5), REG(1)}, // load the first byte into R5
		/* 000d */ {INST_SHR, REG(4), REG(5), REGX, 2}, // isolate the first six bits
		/* 000e */ {INST_ANDI, REG(4), REG(4), REGX, 0x3f}, // isolate the first six bits
		/* 000f */ {INST_SHL, REG(5), REG(5), REGX, 4}, // isolate the last two bits in R5
		/* 0010 */ {INST_ANDI, REG(5), REG(5), REGX, 0x30}, // isolate the last two bits in R5

		// encode first 6-bits
		/* 0011 */ {INST_ADDI, REG(4), REG(4), REGX, 128}, // convert isolated character to an index into the b64 index table
		/* 0012 */ {INST_LDR, REG(4), REG(4)}, // load the encoded symbol into R4
		/* 0013 */ {INST_WRITE, REG(4), REG(0)}, // write the encoded symbol to stdout
		/* 0014 */ {INST_JZ, REG(0), REGX, REGX, 0x3f}, // if failed, simply halt
		/* 0015 */ {INST_SUBI, REG(2), REG(2), REGX, 1}, // update number of bytes remaining
		/* 0016 */ {INST_JNZ, REG(2), REGX, REGX, 0x22}, // if we have no bytes remaining, we need to pad the output, otherwise skip that logic

		// pad output if no bytes remaining, then halt
		/* 0017 */ {INST_ADDI, REG(5), REG(5), REGX, 128}, // convert isolated character to an index into the b64 index table
		/* 0018 */ {INST_LDR, REG(5), REG(5)}, // load the encoded byte into R5
		/* 0019 */ {INST_WRITE, REG(5), REG(0)}, // write encoded byte to stdout
		/* 001a */ {INST_JZ, REG(0), REGX, REGX, 0x3f}, // if failed, simply halt
		/* 001b */ {INST_SET, REG(5), REGX, REGX, '='},
		/* 001c */ {INST_WRITE, REG(5), REG(0)},
		/* 001d */ {INST_JZ, REG(0), REGX, REGX, 0x3f}, // if failed, simply halt
		/* 001e */ {INST_SET, REG(5), REGX, REGX, '='},
		/* 001f */ {INST_WRITE, REG(5), REG(0)},
		/* 0020 */ {INST_JZ, REG(0), REGX, REGX, 0x3f}, // if failed, simply halt
		/* 0021 */ {INST_HLT},

		// isolate second 6-bits
		/* 0022 */ {INST_ADDI, REG(4), REG(5), REGX, 0}, //copy R5 into R4
		/* 0023 */ {INST_ADDI, REG(1), REG(1), REGX, 1}, //increment address reg
		/* 0024 */ {INST_LDR, REG(5), REG(1)}, // load byte into R5
		/* 0025 */ {INST_SHR, REG(6), REG(5), REGX, 4}, // isolate four bits in R5 into R6
		/* 0026 */ {INST_ANDI, REG(6), REG(6), REGX, 0x0f}, // isolate four bits
		/* 0027 */ {INST_OR, REG(4), REG(4), REG(6)}, // OR R4 and R6
		/* 0028 */ {INST_SHL, REG(5), REG(5), REGX, 2}, // isolate bits for next character
		/* 0029 */ {INST_ANDI, REG(5), REG(5), REGX, 0x3c},

		// encode second 6-bits
		/* 002a */ {INST_ADDI, REG(4), REG(4), REGX, 128}, // convert isolated character to an index into the b64 index table
		/* 002b */ {INST_LDR, REG(4), REG(4)}, // load the encoded byte into R4
		/* 002c */ {INST_WRITE, REG(4), REG(0)}, // write the encoded symbol to stdout
		/* 002d */ {INST_JZ, REG(0), REGX, REGX, 0x3f}, // if failed, simply halt
		/* 002e */ {INST_SUBI, REG(2), REG(2), REGX, 1}, // update number of bytes remaining
		/* 002f */ {INST_JNZ, REG(2), REGX, REGX, 0x38}, // if we have no bytes remaining, we need to pad the output, otherwise skip that logic

		// pad output if no bytes remaining, then halt
		/* 0030 */ {INST_ADDI, REG(5), REG(5), REGX, 128}, // convert isolated character to an index into the b64 index table
		/* 0031 */ {INST_LDR, REG(5), REG(5)}, // load the encoded byte into R5
		/* 0032 */ {INST_WRITE, REG(5), REG(0)}, // write encoded byte to stdout
		/* 0033 */ {INST_JZ, REG(0), REGX, REGX, 0x3f}, // if failed, simply halt
		/* 0034 */ {INST_SET, REG(5), REGX, REGX, '='},
		/* 0035 */ {INST_WRITE, REG(5), REG(0)},
		/* 0036 */ {INST_JZ, REG(0), REGX, REGX, 0x3f}, // if failed, simply halt
		/* 0037 */ {INST_HLT},

		// isolate next 6-bits
		/* 0038 */ {INST_ADDI, REG(4), REG(5), REGX, 0}, // copy R5 into R4
		/* 0039 */ {INST_ADDI, REG(1), REG(1), REGX, 1}, // increment address register
		/* 003a */ {INST_LDR, REG(5), REG(1)}, // load byte into R5
		/* 003b */ {INST_SHR, REG(6), REG(5), REGX, 6}, // isolate two bits in R5 into R6
		/* 003c */ {INST_ANDI, REG(6), REG(6), REGX, 0x03}, // isolate four bits
		/* 003d */ {INST_OR, REG(4), REG(4), REG(6)}, // OR R4 and R6
		/* 003e */ {INST_JMP, REGX, REGX, REGX, 0x40}, // jump over halt

		/* 003f */ {INST_HLT},


		/* 0040 */ {INST_ANDI, REG(5), REG(5), REGX, 0x3f}, // isolate bits for next character

		// encode last two
		/* 0041 */ {INST_ADDI, REG(4), REG(4), REGX, 128}, // convert isolated character into an index into the b64 table
		/* 0042 */ {INST_LDR, REG(4), REG(4)}, // load the encoded byte into R4
		/* 0043 */ {INST_WRITE, REG(4), REG(0)}, // write the encoded symbol to stdout
		/* 0044 */ {INST_JZ, REG(0), REGX, REGX, 0x3f}, // if failed, simply halt
		/* 0045 */ {INST_ADDI, REG(4), REG(5), REGX, 128}, // convert isolated character into an index into the b64 table
		/* 0046 */ {INST_LDR, REG(4), REG(4)}, // load the encoded byte into R4
		/* 0047 */ {INST_WRITE, REG(4), REG(0)}, // write the encoded symbol to stdout
		/* 0048 */ {INST_JZ, REG(0), REGX, REGX, 0x3f}, // if failed, simply halt
		/* 0049 */ {INST_JMP, REGX, REGX, REGX, 0x01},
		/* 004a */ {INST_ADDI, REG(0), REG(0), REGX, 0},
		/* 004b */ {INST_ADDI, REG(0), REG(0), REGX, 0}, // nop
		/* 004c */ {INST_ADDI, REG(0), REG(0), REGX, 0}, // nop
		/* 004d */ {INST_ADDI, REG(0), REG(0), REGX, 0}, // nop
		/* 004e */ {INST_ADDI, REG(0), REG(0), REGX, 0}, // nop
		/* 004f */ {INST_ADDI, REG(0), REG(0), REGX, 0}, // nop

		// populate memory with index table
		/* 0050 */ {INST_SET, REG(0), REGX, REGX, 128},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'A'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'B'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'C'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'D'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'E'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'F'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'G'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'H'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'I'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'J'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'K'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'L'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'M'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'N'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'O'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'P'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'Q'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'R'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'S'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'T'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'U'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'V'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'W'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'X'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'Y'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'Z'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'a'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'b'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'c'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'd'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'e'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'f'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'g'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'h'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'i'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'j'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'k'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'l'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'm'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'n'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'o'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'p'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'q'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'r'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 's'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 't'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'u'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'v'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'w'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'x'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'y'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, 'z'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '0'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '1'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '2'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '3'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '4'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '5'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '6'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '7'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '8'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '9'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '+'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_ST, REG(0), REGX, REGX, '/'},
		/* 0000 */ {INST_ADDI, REG(0), REG(0), REGX, 1},
		/* 0000 */ {INST_JMP, REGX, REGX, REGX, 0x01},
};

#endif //CS4417_DEMO_PROG_H
