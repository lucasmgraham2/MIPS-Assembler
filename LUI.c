#include "Instruction.h"
/*
Luke Graham: ADD, ADDI, BEQ, BNE, DIV
Wyatt Albertson: LUI, LW, MFHI, MFLO, MULT
Caleb Edwards: OR, ORI, SLT, SLTI, SUB, SW
*/
void lui_immd_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "LUI") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// Generally the first parameter should always be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// This is AND register, so param 2 needs to be an immediate
	if (PARAM2.type != IMMEDIATE) {
		state = MISSING_PARAM;
		return;
	}



	/*
		Checking the value of parameters
	*/

	// Rd should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}




	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "001111");

	// set Rs
	setBits_num(20, PARAM1.value, 5);

	// set immediate
	setBits_num(15, PARAM2.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "001111") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/
	// getBits(start_bit, width)
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);


	/*
		Setting Instuciton values
	*/

	setOp("LUI");
	//setCond_num(cond);
	//setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); //destination
	setParam(2, IMMEDIATE, imm16); //second source register operand


	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}



