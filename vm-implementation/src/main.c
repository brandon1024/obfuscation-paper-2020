#include "machine.h"
#include "prog.h"
#include "instruction.h"

int main(int argc, char *argv[])
{
	int pc = 0;
	struct reg gp_reg[16];
	struct instruction instruction_reg;
	unsigned char buffer[256];

	unsigned halt_cond = 0;
	while (!halt_cond) {
		instruction_reg = program[pc];
		pc++;

		halt_cond = execute(&instruction_reg, gp_reg, buffer, &pc);
	}

	return 0;
}
