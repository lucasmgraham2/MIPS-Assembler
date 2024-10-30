#include "Instruction.h"

void slt_reg_assm(void) {
	// Check if the op code matches
	if (strcmp(OP_CODE, "SLT") != 0) {
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
	setBits_str(5, "101010");     // Set funct to "SLT" (binary 101010)
	// Set Rd
	setBits_num(15, PARAM1.value, 5); 
	// Set Rs
	setBits_num(25, PARAM2.value, 5); 
	// Set Rt
	setBits_num(20, PARAM3.value, 5); 

	state = COMPLETE_ENCODE;   
}

void slt_reg_bin(void) {
	// Check if the op code and funct bits match for SLT
	if (checkBits(31, "000000") != 0 || checkBits(5, "101010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/

	uint32_t Rd = getBits(15, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	/*
		Setting Instruction values
	*/

	setOp("SLT");
	setParam(1, REGISTER, Rd); // destination register
	setParam(2, REGISTER, Rs); // first source register operand
	setParam(3, REGISTER, Rt); // second source register operand

	state = COMPLETE_DECODE;      

}


