#include "Instruction.h"

void slti_immd_assm(void) {
	// Check if the op code matches
	if (strcmp(OP_CODE, "SLTI") != 0) {
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

	// Set opcode for SLTI
	setBits_str(31, "001010");
	// Set Rs
	setBits_num(25, PARAM2.value, 5); 
	// Set Rt
	setBits_num(20, PARAM1.value, 5);
	// Set immediate
	setBits_num(15, PARAM3.value, 16); 

	state = COMPLETE_ENCODE;
}

void slti_immd_bin(void) {
	// Check if the op code bits match
	if (checkBits(31, "001010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/

	uint32_t Rt = getBits(20, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting Instruction values
	*/

	setOp("SLTI");
	setParam(1, REGISTER, Rt);  // Destination register
	setParam(2, REGISTER, Rs);  // Source register
	setParam(3, IMMEDIATE, imm16); // Immediate value

	state = COMPLETE_DECODE;
}



