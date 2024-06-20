#pragma once
#include <stdint.h>
#include "Bus.h"

class SM83
{
public:
	SM83();
	~SM83();
public:
	// Special registers
	uint16_t pc = 0x0000;	// Program counter
	uint16_t sp = 0x0000;	// Stack pointer

	uint8_t A  = 0x00;		// Accumulator
	uint8_t F  = 0x00;		// Flags
	uint8_t IR = 0x00;		// Instruction register
	uint8_t IE = 0x00;		// Interrupt enable

	uint8_t opcode = 0x00;	// Current opcode

	uint16_t addr_abs = 0x0000;	// Current address being referenced
	uint8_t  temp8    = 0x00;
	uint16_t temp16   = 0x0000;	// Temporary variables

	// General purpose registers
	struct {
		uint8_t B = 0x00;
		uint8_t C = 0x00;
	} BC;

	struct {
		uint8_t D = 0x00;
		uint8_t E = 0x00;
	} DE;

	struct {
		uint8_t H = 0x00;
		uint8_t L = 0x00;
	} HL;

public:
	/* INSTRUCTIONS
		Split up into 6 main groups: 
			Misc/control instructions
			Jumps/calls
			8bit load/store/move instructions
			16bit load/store/move instructions
     	  	8bit arithmetic/logical instructions
     	  	16bit arithmetic/logical instructions
		There is one more group, 8 bit rotations and shifts, however they all fall under opcodes prefixed with 0xCB
		Major table credit to https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html, and instruction explanaitions to https://gekkio.fi/files/gb-docs/gbctr.pdf
	*/

	// 8 bit load/store/move
	uint8_t LDBB();	uint8_t LDBC();	uint8_t LDBD();	uint8_t LDBE(); uint8_t LDBH();	uint8_t LDBL(); uint8_t LDBID(); uint8_t LDBA();
	uint8_t LDCB();	uint8_t LDCC();	uint8_t LDCD();	uint8_t LDCE(); uint8_t LDCH();	uint8_t LDCL(); uint8_t LDCID(); uint8_t LDCA();
	uint8_t LDDB();	uint8_t LDDC();	uint8_t LDDD();	uint8_t LDDE(); uint8_t LDDH();	uint8_t LDDL(); uint8_t LDDID(); uint8_t LDDA();
	uint8_t LDEB();	uint8_t LDCE();	uint8_t LDED();	uint8_t LDEE(); uint8_t LDEH();	uint8_t LDEL(); uint8_t LDEID(); uint8_t LDEA();

	// Placeholder
	uint8_t XXX();

public:
	uint8_t	 instructionCycles;		// Important for overlapping instructions
	uint32_t totalCycles;

	void clock();

private:
	Bus* n = nullptr;

	uint8_t readBus(uint16_t addr);
	void	writeBus(uint16_t addr, uint8_t data);

	struct instruction
	{
		uint8_t(SM83::*op)(void) = nullptr;
		uint8_t cycles;
	};

	std::vector<instruction> _8lookup;
};