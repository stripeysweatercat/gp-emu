#pragma once
#include <vector>
#include <stdint.h>

#include "SM83.h"

class Bus
{
public:
	Bus();
	~Bus();
public:
	// Internal Memory
	std::vector<uint8_t> ram;
	std::vector<uint8_t> vram;

public:
	// Connected Devices
	// SM83 cpu;

public:
	// Memory access functions for both ram and vram
	uint8_t read(uint16_t addr);
	uint8_t vRead(uint16_t addr);
	void write(uint16_t addr, uint8_t data);
	void vWrite(uint16_t addr, uint8_t data);
};