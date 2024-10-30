#include "Instruction.h"

void or_reg_assm(void) {
	// Check if the op code matches "OR"
	if (strcmp(OP_CODE, "OR") != 0) {
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
	
	// Set opcode to 0
	setBits_num(31, 0, 6);       
	// Set funct to "OR"
	setBits_str(5, "100101");     
	// Set Rd
	setBits_num(15, PARAM1.value, 5);
	// Set Rs
	setBits_num(25, PARAM2.value, 5);
	// Set Rt
	setBits_num(20, PARAM3.value, 5); 

	state = COMPLETE_ENCODE;     
}

void or_reg_bin(void) {
	// Check if the op code bits match
	if (checkBits(31, "000000") != 0 || checkBits(5, "100101") != 0) {
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

	setOp("OR");
	setParam(1, REGISTER, Rd); // destination
	setParam(2, REGISTER, Rs); // first source register operand
	setParam(3, REGISTER, Rt); // second source register operand

	state = COMPLETE_DECODE;    
}


