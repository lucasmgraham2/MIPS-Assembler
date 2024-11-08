#include "Instruction.h"
/*
Luke Graham: ADD, ADDI, BEQ, BNE, DIV
Wyatt Albertson: LUI, LW, MFHI, MFLO, MULT
Caleb Edwards: OR, ORI, SLT, SLTI, SUB, SW
*/
void div_reg_assm(void) {
	// Check that the op code matches "ADD"
	if (strcmp(OP_CODE, "DIV") != 0) {
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

	/*
		Putting the binary together
	*/

	setBits_num(31, 0, 6);

	setBits_str(5, "011010");

	setBits_num(25, PARAM1.value, 5);

	setBits_num(20, PARAM2.value, 5);

	state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values from binary
	*/

	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);
	/*
		Setting Instruction values
	*/

	setOp("DIV");
	setParam(1, REGISTER, Rs);
	setParam(2, REGISTER, Rt);
	setParam(3, IMMEDIATE, imm16);
	state = COMPLETE_DECODE;
}


