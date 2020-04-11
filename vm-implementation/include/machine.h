#ifndef CS4417_DEMO_MACHINE_H
#define CS4417_DEMO_MACHINE_H

#define INST_READ   0x00
#define INST_WRITE  0x01
#define INST_SET    0x02
#define INST_ADD    0x03
#define INST_ADDI   0x04
#define INST_SUB    0x05
#define INST_SUBI   0x06
#define INST_SHL    0x07
#define INST_SHR    0x08
#define INST_ANDI   0x09
#define INST_ORI    0x0a
#define INST_XORI   0x0b
#define INST_AND    0x0c
#define INST_OR     0x0d
#define INST_XOR    0x0e
#define INST_ST     0x0f
#define INST_LD     0x10
#define INST_STR    0x11
#define INST_LDR    0x12
#define INST_JMP    0x13
#define INST_JZ     0x14
#define INST_JNZ    0x15
#define INST_HLT    0x16

#define REG(x) (x)
#define REGX 0

struct instruction {
	unsigned op: 8;
	unsigned reg1: 4;
	unsigned reg2: 4;
	unsigned reg3: 4;
	unsigned imm: 8;
};

struct reg {
	unsigned int val;
};

#endif //CS4417_DEMO_MACHINE_H
