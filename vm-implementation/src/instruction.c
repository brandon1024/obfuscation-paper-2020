#include <stdlib.h>
#include <unistd.h>
#include <sys/random.h>

#include "instruction.h"
#include "utils.h"

__attribute__((constructor)) static void construct();
__attribute__((destructor)) static void destruct();

static size_t offset;
static int (**instructions)(struct instruction *, struct reg[16], unsigned char[256], int *);

int execute(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	return instructions[(offset + instruction_reg->op) % 23](instruction_reg, gp_reg, memory, pc);
}

static int ex_read(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	char c;
	if (recoverable_read(STDIN_FILENO, &c, sizeof(char)) != sizeof(char))
		gp_reg[instruction_reg->reg2].val = 0;
	else
		gp_reg[instruction_reg->reg2].val = 1;
	gp_reg[instruction_reg->reg1].val = c;

	return 0;
}

static int ex_write(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	char c = (char) gp_reg[instruction_reg->reg1].val;
	if (recoverable_write(STDOUT_FILENO, &c, sizeof(char)) != sizeof(char))
		gp_reg[instruction_reg->reg2].val = 0;
	else
		gp_reg[instruction_reg->reg2].val = 1;

	return 0;
}

static int ex_set(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = instruction_reg->imm;
	return 0;
}

static int ex_add(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val + gp_reg[instruction_reg->reg3].val;
	return 0;
}

static int ex_addi(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val + instruction_reg->imm;
	return 0;
}

static int ex_sub(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val - gp_reg[instruction_reg->reg3].val;
	return 0;
}

static int ex_subi(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val - instruction_reg->imm;
	return 0;
}

static int ex_shl(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val << (unsigned)instruction_reg->imm;
	return 0;
}

static int ex_shr(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val >> (unsigned)instruction_reg->imm;
	return 0;
}

static int ex_andi(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val & instruction_reg->imm;
	return 0;
}

static int ex_ori(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val | instruction_reg->imm;
	return 0;
}

static int ex_xori(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val ^ instruction_reg->imm;
	return 0;
}

static int ex_and(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val & gp_reg[instruction_reg->reg3].val;
	return 0;
}

static int ex_or(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val | gp_reg[instruction_reg->reg3].val;
	return 0;
}

static int ex_xor(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val ^ gp_reg[instruction_reg->reg3].val;
	return 0;
}

static int ex_str(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) pc;

	memory[gp_reg[instruction_reg->reg2].val] = gp_reg[instruction_reg->reg1].val;
	return 0;
}

static int ex_ldr(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) pc;

	gp_reg[instruction_reg->reg1].val = memory[gp_reg[instruction_reg->reg2].val];
	return 0;
}

static int ex_st(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) pc;

	memory[gp_reg[instruction_reg->reg2].val] = instruction_reg->imm;
	return 0;
}

static int ex_ld(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) pc;

	gp_reg[instruction_reg->imm].val = memory[gp_reg[instruction_reg->reg2].val];
	return 0;
}

static int ex_jmp(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) gp_reg;
	(void) memory;

	*pc = (int)instruction_reg->imm;
	return 0;
}

static int ex_jz(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;

	if (!gp_reg[instruction_reg->reg1].val)
		*pc = (int)instruction_reg->imm;
	return 0;
}

static int ex_jnz(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;

	if (gp_reg[instruction_reg->reg1].val)
		*pc = (int)instruction_reg->imm;
	return 0;
}

static int ex_hlt(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) instruction_reg;
	(void) gp_reg;
	(void) memory;
	(void) pc;

	return 1;
}

__attribute__((constructor)) static void construct()
{
	instructions = malloc(sizeof(int (*)(struct instruction *, struct reg[16], unsigned char[256], int *)) * 23);
	if (!instructions)
		exit(EXIT_FAILURE);

	// get secure random
	if (getrandom(&offset, sizeof(size_t), 0) != sizeof(size_t))
		exit(EXIT_FAILURE);

	instructions[(offset + INST_READ) % 23] = &ex_read;
	instructions[(offset + INST_WRITE) % 23] = &ex_write;
	instructions[(offset + INST_SET) % 23] = &ex_set;
	instructions[(offset + INST_ADD) % 23] = &ex_add;
	instructions[(offset + INST_ADDI) % 23] = &ex_addi;
	instructions[(offset + INST_SUB) % 23] = &ex_sub;
	instructions[(offset + INST_SUBI) % 23] = &ex_subi;
	instructions[(offset + INST_SHL) % 23] = &ex_shl;
	instructions[(offset + INST_SHR) % 23] = &ex_shr;
	instructions[(offset + INST_ANDI) % 23] = &ex_andi;
	instructions[(offset + INST_ORI) % 23] = &ex_ori;
	instructions[(offset + INST_XORI) % 23] = &ex_xori;
	instructions[(offset + INST_AND) % 23] = &ex_and;
	instructions[(offset + INST_OR) % 23] = &ex_or;
	instructions[(offset + INST_XOR) % 23] = &ex_xor;
	instructions[(offset + INST_STR) % 23] = &ex_str;
	instructions[(offset + INST_LDR) % 23] = &ex_ldr;
	instructions[(offset + INST_ST) % 23] = &ex_st;
	instructions[(offset + INST_LD) % 23] = &ex_ld;
	instructions[(offset + INST_JMP) % 23] = &ex_jmp;
	instructions[(offset + INST_JZ) % 23] = &ex_jz;
	instructions[(offset + INST_JNZ) % 23] = &ex_jnz;
	instructions[(offset + INST_HLT) % 23] = &ex_hlt;
}

__attribute__((destructor)) static void destruct()
{
	free(instructions);
}
