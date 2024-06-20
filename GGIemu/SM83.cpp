#include "SM83.h"

SM83::SM83() 
{
	using x = SM83;

	_8lookup =
	{
		{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},
		{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},
		{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},
		{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},{&x::XXX, 0},
		{&x::LDBB, 4},{&x::LDBC, 4},{&x::LDBD, 4},{&x::LDBE, 4},{&x::LDBH, 4},{&x::LDBL, 4},{&x::LDBID, 8},{&x::LDBA, 4},{&x::LDCB, 4},{&x::LDCC, 4},{&x::LDCD, 4},{&x::LDCE, 4},{&x::LDCH, 4},{&x::LDCL, 4},{&x::LDCID, 8},{&x::LDCA, 4},
	};
}

SM83::~SM83() {}

void SM83::clock()
{
	if (instructionCycles == 0)
	{
		opcode = readBus(pc);
		pc++;
		instructionCycles += _8lookup[opcode].cycles;
		instructionCycles += (this->*_8lookup[opcode].op)();
	}
	instructionCycles--;
}

uint8_t SM83::readBus(uint16_t addr)
{
	return n->read(addr);
}

void SM83::writeBus(uint16_t addr, uint8_t data)
{
	n->write(addr, data);
}

uint8_t SM83::XXX()
{
	return 0;
}

// 8 Bit Load
uint8_t SM83::LDBB()
{
	BC.B = BC.B;
	return 0;
}

uint8_t SM83::LDBC()
{
	BC.B = BC.C;
	return 0;
}

uint8_t SM83::LDBD()
{
	BC.B = DE.D;
	return 0;
}

uint8_t SM83::LDBE()
{
	BC.B = DE.E;
	return 0;
}

uint8_t SM83::LDBH()
{
	BC.B = HL.H;
	return 0;
}

uint8_t SM83::LDBL()
{
	BC.B = HL.L;
	return 0;
}

uint8_t SM83::LDBID()
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	BC.B = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDBA()
{
	BC.B = A;
	return 0;
}

uint8_t SM83::LDCB()
{
	BC.C = BC.B;
	return 0;
}

uint8_t SM83::LDCC()
{
	BC.C = BC.C;
	return 0;
}

uint8_t SM83::LDCD()
{
	BC.C = DE.D;
	return 0;
}

uint8_t SM83::LDCE()
{
	BC.C = DE.E;
	return 0;
}

uint8_t SM83::LDCH()
{
	BC.C = HL.H;
	return 0;
}

uint8_t SM83::LDCL()
{
	BC.C = HL.L;
	return 0;
}

uint8_t SM83::LDCID()
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	BC.C = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDCA()
{
	BC.C = A;
	return 0;
}