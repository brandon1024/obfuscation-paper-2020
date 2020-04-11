#ifndef B64_ENCODER_VM_OBFUSCATED_INSTRUCTION_H
#define B64_ENCODER_VM_OBFUSCATED_INSTRUCTION_H

#ifndef CS4417_DEMO_MACHINE_H
#include "machine.h"
#endif

int execute(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);

#endif //B64_ENCODER_VM_OBFUSCATED_INSTRUCTION_H
