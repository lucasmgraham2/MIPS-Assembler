#include "Instruction.h"
/*
Luke Graham: ADD, ADDI, BEQ, BNE, DIV
Wyatt Albertson: LUI, LW, MFHI, MFLO, MULT
Caleb Edwards: OR, ORI, SLT, SLTI, SUB, SW
*/
void sub_reg_assm(void) {
	// Check if the op code matches
	if (strcmp(OP_CODE, "SUB") != 0) {
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

	// Set Opcode for SUB
	setBits_num(31, 0, 6);
	// Set funct for SUB
	setBits_str(5, "100010");      
	// Set Rd
	setBits_num(15, PARAM1.value, 5);
	// Set Rs
	setBits_num(25, PARAM2.value, 5);
	// Set Rt
	setBits_num(20, PARAM3.value, 5); 

	state = COMPLETE_ENCODE;
}

void sub_reg_bin(void) {
	// Check if the op code bits match
	if (checkBits(31, "000000") != 0 || checkBits(5, "100010") != 0) {
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

	setOp("SUB");
	setParam(1, REGISTER, Rd);  // Destination register
	setParam(2, REGISTER, Rs);  // First source register
	setParam(3, REGISTER, Rt);  // Second source register

	state = COMPLETE_DECODE;
}


