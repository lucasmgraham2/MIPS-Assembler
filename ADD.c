#include "Instruction.h"

void add_reg_assm(void) {
	// Check that the op code matches "ADD"
	if (strcmp(OP_CODE, "ADD") != 0) {
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
	if (PARAM3.type != REGISTER) {
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
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	setBits_num(31, 0, 6);

	setBits_str(5, "100000");

	setBits_num(15, PARAM1.value, 5);

	setBits_num(25, PARAM2.value, 5);

	setBits_num(20, PARAM3.value, 5);

	state = COMPLETE_ENCODE;
}

void add_reg_bin(void) {
	if (checkBits(31, "000000") != 0 || checkBits(5, "100000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values from binary
	*/

	uint32_t Rd = getBits(15, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	/*
		Setting Instruction values
	*/

	setOp("ADD");
	setParam(1, REGISTER, Rd); 
	setParam(2, REGISTER, Rs); 
	setParam(3, REGISTER, Rt); 

	state = COMPLETE_DECODE;
}


