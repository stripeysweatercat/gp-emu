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
		{&x::LDDB, 4},{&x::LDDC, 4},{&x::LDDD, 4},{&x::LDDE, 4},{&x::LDDH, 4},{&x::LDDL, 4},{&x::LDDID, 8},{&x::LDDA, 4},{&x::LDEB, 4},{&x::LDEC, 4},{&x::LDED, 4},{&x::LDEE, 4},{&x::LDEH, 4},{&x::LDEL, 4},{&x::LDEID, 8},{&x::LDEA, 4},
		{&x::LDHB, 4},{&x::LDHC, 4},{&x::LDHD, 4},{&x::LDHE, 4},{&x::LDHH, 4},{&x::LDHL, 4},{&x::LDHID, 8},{&x::LDHA, 4},{&x::LDLB, 4},{&x::LDLC, 4},{&x::LDLD, 4},{&x::LDLE, 4},{&x::LDLH, 4},{&x::LDLL, 4},{&x::LDLID, 8},{&x::LDLA, 4},
		{&x::LDHLB, 8},{&x::LDHLC, 8},{&x::LDHLD, 8},{&x::LDHLE, 8},{&x::LDHLH, 8},{&x::LDHLL, 8},{&x::XXX, 0},{&x::LDHLA, 8},{&x::LDAB, 4},{&x::LDAC, 4},{&x::LDAD, 4},{&x::LDAE, 4},{&x::LDAH, 4},{&x::LDAL, 4},{&x::LDAID, 8},{&x::LDAA, 4},
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

void SM83::ConnectBus(Bus* bus)
{
	this->n = bus;
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
// I have become aware after writing too many of these that mayyybe making a different function for each r, r'  or r ,(hl) could be inefficient
// CBA fixing it tho ;3

uint8_t SM83::LDBCA() // LD (BD), A
{
	addr_abs = ((uint16_t)BC.B << 8) | (uint16_t)BC.C;
	writeBus(addr_abs, A);
	return 0;
}

uint8_t SM83::LDB()	// LD B, d8
{
	BC.B = readBus(pc);
	pc++;
	return 0;
}

uint8_t SM83::LDABC() // LD A, (BC)
{
	addr_abs = ((uint16_t)BC.B << 8) | (uint16_t)BC.C;
	A = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDC() // LD C, d8
{
	BC.C = readBus(pc);
	pc++;
	return 0;
}

uint8_t SM83::LDDEA() // LD (DE), A
{
	addr_abs = ((uint16_t)DE.D << 8) | (uint16_t)DE.E;
	writeBus(addr_abs, A);
	return 0;
}

uint8_t SM83::LDD() // LD D, d8
{
	DE.D = readBus(pc);
	pc++;
	return 0;
}

uint8_t SM83::LDADE() // LD A, (DE)
{
	addr_abs = ((uint16_t)DE.D << 8) | (uint16_t)DE.E;
	A = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDE() // LD E, d8
{
	DE.E = readBus(pc);
	pc++;
	return 0;
}

uint8_t SM83::LDHPA() // LD (HL+), A
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	writeBus(addr_abs, A);
	addr_abs++;
	HL.H = (addr_abs & 0xFF00) >> 8;
	HL.L = (uint8_t)addr_abs & 0x00FF;
	return 0;
}

uint8_t SM83::LDH() // LD H, d8
{
	HL.H = readBus(pc);
	pc++;
	return 0;
}

uint8_t SM83::LDAHP() // LD A, (HL+)
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	A = readBus(addr_abs);
	addr_abs++;
	HL.H = (addr_abs & 0xFF00) >> 8;
	HL.L = (uint8_t)addr_abs & 0x00FF;
	return 0;
}

uint8_t SM83::LDL() // LD L, d8
{
	HL.L = readBus(pc);
	pc++;
	return 0;
}

uint8_t SM83::LDHNA() // LD (HL-), A
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	writeBus(addr_abs, A);
	addr_abs--;
	HL.H = (addr_abs & 0xFF00) >> 8;
	HL.L = (uint8_t)addr_abs & 0x00FF;
	return 0;
}

uint8_t SM83::LDHLD8() // LD (HL), d8
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	temp8 = readBus(pc);
	pc++;
	writeBus(addr_abs, temp8);
	return 0;
}

uint8_t SM83::LDAHN() // LD A, (HL-)
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	A = readBus(addr_abs);
	addr_abs--;
	HL.H = (addr_abs & 0xFF00) >> 8;
	HL.L = (uint8_t)addr_abs & 0x00FF;
	return 0;
}

uint8_t SM83::LDA() // LD A, d8
{
	A = readBus(pc);
	pc++;
	return 0;
}

uint8_t SM83::LDBB() // LD B, B
{
	BC.B = BC.B;
	return 0;
}

uint8_t SM83::LDBC() // LD B, C
{
	BC.B = BC.C;
	return 0;
}

uint8_t SM83::LDBD() // LD B, D
{
	BC.B = DE.D;
	return 0;
}

uint8_t SM83::LDBE() // LD B, E
{
	BC.B = DE.E;
	return 0;
}

uint8_t SM83::LDBH() // LD B, H
{
	BC.B = HL.H;
	return 0;
}

uint8_t SM83::LDBL() // LD B, L
{
	BC.B = HL.L;
	return 0;
}

uint8_t SM83::LDBID() // LD B, (HL)
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	BC.B = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDBA() // LD B, A
{
	BC.B = A;
	return 0;
}

uint8_t SM83::LDCB() // LD C, B
{
	BC.C = BC.B;
	return 0;
}

uint8_t SM83::LDCC() // LD C, C
{
	BC.C = BC.C;
	return 0;
}

uint8_t SM83::LDCD() // LD C, D
{
	BC.C = DE.D;
	return 0;
}

uint8_t SM83::LDCE() // LD C, E
{
	BC.C = DE.E;
	return 0;
}

uint8_t SM83::LDCH() // LD C, H
{
	BC.C = HL.H;
	return 0;
}

uint8_t SM83::LDCL() // LD C, L
{
	BC.C = HL.L;
	return 0;
}

uint8_t SM83::LDCID() // LD C, (HL)
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	BC.C = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDCA() // LD C, A
{
	BC.C = A;
	return 0;
}

uint8_t SM83::LDDB() // LD D, B
{
	DE.D = BC.C;
	return 0;
}

uint8_t SM83::LDDC() // LD D, C
{
	DE.D = BC.B;
	return 0;
}

uint8_t SM83::LDDD() // LD D, D
{
	DE.D = DE.D;
	return 0;
}

uint8_t SM83::LDDE() // LD D, E
{
	DE.D = DE.E;
	return 0;
}

uint8_t SM83::LDDH() // LD D, H
{
	DE.D = HL.H;
	return 0;
}

uint8_t SM83::LDDL() // LD D, L
{
	DE.D = HL.L;
	return 0;
}

uint8_t SM83::LDDID() // LD D, (HL)
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	DE.D = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDDA() // LD D, A
{
	DE.D = A;
	return 0;
}

uint8_t SM83::LDEB() // LD E, B
{
	DE.E = BC.B;
	return 0;
}

uint8_t SM83::LDEC() // LD E, C
{
	DE.E = BC.C;
	return 0;
}

uint8_t SM83::LDED() // LD E, D
{
	DE.E = DE.D;
	return 0;
}

uint8_t SM83::LDEE() // LD E, E
{
	DE.E = DE.E;
	return 0;
}

uint8_t SM83::LDEH() // LD E, H
{
	DE.E = HL.H;
	return 0;
}

uint8_t SM83::LDEL() // LD E, L
{
	DE.E = HL.L;
	return 0;
}

uint8_t SM83::LDEID() // LD E, (HL)
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	DE.E = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDEA() // LD E, A
{
	DE.E = A;
	return 0;
}

uint8_t SM83::LDHB() // LD H, B
{
	HL.L = BC.B;
	return 0;
}

uint8_t SM83::LDHC() // LD H, C
{
	HL.H = BC.C;
	return 0;
}

uint8_t SM83::LDHD() // LD H, D
{
	HL.H = DE.D;
	return 0;
}

uint8_t SM83::LDHE() // LD H, E
{
	HL.H = DE.E;
	return 0;
}

uint8_t SM83::LDHH() // LD H, H
{
	HL.H = HL.H;
	return 0;
}

uint8_t SM83::LDHL() // LD H, L
{
	HL.H = HL.L;
	return 0;
}

uint8_t SM83::LDHID() // LD H, (HL)
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	HL.H = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDHA() // LD H, A
{
	HL.H = A;
	return 0;
}

uint8_t SM83::LDLB() // LD L, B
{
	HL.L = BC.B;
	return 0;
}

uint8_t SM83::LDLC() // LD L, C
{
	HL.L = BC.C;
	return 0;
}

uint8_t SM83::LDLD() // LD L, D
{
	HL.L = DE.D;
	return 0;
}

uint8_t SM83::LDLE() // LD L, E
{
	HL.L = DE.E;
	return 0;
}

uint8_t SM83::LDLH() // LD L, H
{
	HL.L = HL.H;
	return 0;
}

uint8_t SM83::LDLL() // LD L, L
{
	HL.L = HL.L;
	return 0;
}

uint8_t SM83::LDLID() // LD L, (HL)
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	HL.L = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDLA() // LD L, A
{
	HL.L = A;
	return 0;
}

uint8_t SM83::LDHLB() // LD (HL), B
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	writeBus(addr_abs, BC.B);
	return 0;
}

uint8_t SM83::LDHLC() // LD (HL), C
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	writeBus(addr_abs, BC.C);
	return 0;
}

uint8_t SM83::LDHLD() // LD (HL), D
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	writeBus(addr_abs, DE.D);
	return 0;
}

uint8_t SM83::LDHLE() // LD (HL), E
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	writeBus(addr_abs, DE.E);
	return 0;
}

uint8_t SM83::LDHLH() // LD (HL), H
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	writeBus(addr_abs, HL.H);
	return 0;
}

uint8_t SM83::LDHLL() // LD (HL), L
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	writeBus(addr_abs, HL.L);
	return 0;
}

uint8_t SM83::LDHLA() // LD (HL), A
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	writeBus(addr_abs, A);
	return 0;
}

uint8_t SM83::LDAB() // LD A, B
{
	A = BC.B;
	return 0;
}

uint8_t SM83::LDAC() // LD A, C
{
	A = BC.C;
	return 0;
}

uint8_t SM83::LDAD() // LD A, D
{
	A = DE.D;
	return 0;
}

uint8_t SM83::LDAE() // LD A, E
{
	A = DE.E;
	return 0;
}

uint8_t SM83::LDAH() // LD A, H
{
	A = HL.H;
	return 0;
}

uint8_t SM83::LDAL() // LD A, L
{
	A = HL.L;
	return 0;
}

uint8_t SM83::LDAID() // LD A, (HL)
{
	addr_abs = ((uint16_t)HL.H << 8) | (uint16_t)HL.L;
	A = readBus(addr_abs);
	return 0;
}

uint8_t SM83::LDAA() // LD A, A
{
	A = A;
	return 0;
}
