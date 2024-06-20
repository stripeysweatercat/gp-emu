#include "Bus.h"

Bus::Bus()
{
	for (int i = 0; i <= 1024 * 8; i++)
	{
		ram.push_back(0x00);
		vram.push_back(0x00);
	}
}

Bus::~Bus(){}

uint8_t Bus::read(uint16_t addr)
{
	if (addr <= 0x2000)
		return ram[addr];
	return 0x00;
}

uint8_t Bus::vRead(uint16_t addr)
{
	if (addr <= 0x2000)
		return vram[addr];
	return 0x00;
}

void Bus::write(uint16_t addr, uint8_t data)
{
	if (addr <= 0x2000)
		ram[addr] = data;
}

void Bus::vWrite(uint16_t addr, uint8_t data)
{
	if (addr <= 0x2000)
		vram[addr] = data;
}
