#include "Instruction.h"
/*
Luke Graham: ADD, ADDI, BEQ, BNE, DIV
Wyatt Albertson: LUI, LW, MFHI, MFLO, MULT
Caleb Edwards: OR, ORI, SLT, SLTI, SUB, SW
*/
void bne_immd_assm(void) {
	// Checking that the op code matches
	if (strcmp(OP_CODE, "BNE") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of parameters
	*/

	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	setBits_str(31, "000101");

	setBits_num(25, PARAM1.value, 5);

	setBits_num(20, PARAM2.value, 5);

	setBits_num(15, PARAM3.value, 16);

	state = COMPLETE_ENCODE;
}

void bne_immd_bin(void) {
	if (checkBits(31, "000101") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values from binary
	*/

	uint32_t Rs = getBits(20, 5);
	uint32_t Rt = getBits(25, 5);
	uint32_t imm16 = getBits(15, 16);


	/*
		Setting Instruction values
	*/

	setOp("BNE");
	setParam(1, REGISTER, Rt);
	setParam(2, REGISTER, Rs);
	setParam(3, IMMEDIATE, imm16);

	state = COMPLETE_DECODE;
}



