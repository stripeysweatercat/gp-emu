#pragma once
#include <stdint.h>
#include "Bus.h"

class Bus;

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

	// General purpose split registers
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

	enum Flags {
		C = (1 << 4),	// Carry - When 8b addition > 0xFF, 16b addition > 0xFFFF, if subraction < 0, << or >> shifts out 0b1
		H = (1 << 5),	// Half carry - idk lol
		N = (1 << 6),	// Subtraction - if previous instruction is subtraction
		Z = (1 << 7)	// Zero - set if result of operation is 0
	};

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

	// Misc / Control
	// TBC

	// Jump Calls
	// TBC

	// 8 bit load/store/move
	uint8_t LDBCA(); uint8_t LDB();	  uint8_t LDABC(); uint8_t LDC();	uint8_t LDDEA(); uint8_t LDD();	   uint8_t LDADE();  uint8_t LDE();
	uint8_t LDHPA(); uint8_t LDH();   uint8_t LDAHP(); uint8_t LDL();	uint8_t LDHNA(); uint8_t LDHLD8(); uint8_t LDAHN();	 uint8_t LDA();
	uint8_t LDBB();	 uint8_t LDBC();  uint8_t LDBD();  uint8_t LDBE();  uint8_t LDBH();	 uint8_t LDBL();   uint8_t LDBID();  uint8_t LDBA();
	uint8_t LDCB();	 uint8_t LDCC();  uint8_t LDCD();  uint8_t LDCE();  uint8_t LDCH();	 uint8_t LDCL();   uint8_t LDCID();  uint8_t LDCA();
	uint8_t LDDB();	 uint8_t LDDC();  uint8_t LDDD();  uint8_t LDDE();  uint8_t LDDH();	 uint8_t LDDL();   uint8_t LDDID();  uint8_t LDDA();
	uint8_t LDEB();	 uint8_t LDEC();  uint8_t LDED();  uint8_t LDEE();  uint8_t LDEH();	 uint8_t LDEL();   uint8_t LDEID();  uint8_t LDEA();
	uint8_t LDHB();	 uint8_t LDHC();  uint8_t LDHD();  uint8_t LDHE();  uint8_t LDHH();	 uint8_t LDHL();   uint8_t LDHID();  uint8_t LDHA();
	uint8_t LDLB();	 uint8_t LDLC();  uint8_t LDLD();  uint8_t LDLE();  uint8_t LDLH();	 uint8_t LDLL();   uint8_t LDLID();  uint8_t LDLA();
	uint8_t LDHLB(); uint8_t LDHLC(); uint8_t LDHLD(); uint8_t LDHLE(); uint8_t LDHLH(); uint8_t LDHLL();  uint8_t LDHLA();
	uint8_t LDAB();  uint8_t LDAC();  uint8_t LDAD();  uint8_t LDAE();  uint8_t LDAH();  uint8_t LDAL();   uint8_t LDAID();  uint8_t LDAA();

	// Placeholder
	uint8_t XXX();

public:
	uint8_t	 instructionCycles;		// Important for overlapping instructions
	uint32_t totalCycles;

	void clock();

	void ConnectBus(Bus* bus);

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
	std::vector<instruction> _16lookup;
};