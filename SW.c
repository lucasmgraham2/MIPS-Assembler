#include "Instruction.h"

void sw_immd_assm(void) {
	// Check if the op code matches
	if (strcmp(OP_CODE, "SW") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/
	if (PARAM1.type != REGISTER) { // Rt (source register)
		state = MISSING_REG;
		return;
	}

	if (PARAM2.type != REGISTER) { // Rs (base register)
		state = MISSING_REG;
		return;
	}

	if (PARAM3.type != IMMEDIATE) { // Immediate offset
		state = MISSING_PARAM;
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

	if (PARAM3.value != IMMEDIATE) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/
	// Set opcode for SW
	setBits_str(31, "101011");
	// Set Rs (base register)
	setBits_num(25, PARAM2.value, 5);
	// Set Rt (register containing the value to store)
	setBits_num(20, PARAM1.value, 5);
	// Set immediate offset
	setBits_num(15, PARAM3.value, 16);

	state = COMPLETE_ENCODE;
}
void sw_immd_bin(void) {
	// Check if the op code bits match
	if (checkBits(31, "101011") != 0) { // SW opcode is 101011
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/

	uint32_t Rt = getBits(20, 5);  // Register containing the value to store
	uint32_t Rs = getBits(25, 5);  // Base register
	uint32_t imm16 = getBits(15, 16); // Immediate offset

	/*
		Setting Instruction values
	*/

	setOp("SW");
	setParam(1, REGISTER, Rt);  // Register to store
	setParam(2, REGISTER, Rs);   // Base register
	setParam(3, IMMEDIATE, imm16); // Offset

	state = COMPLETE_DECODE;
}