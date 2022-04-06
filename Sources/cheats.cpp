#include "cheats.hpp"
#include "values.h"

u32 offset = 0;
u32 random_v = 0;
u32 dataX = 0;
u32 dataY = 0;
u32 dataZ = 0;
static u32 x = 0;
static u32 y = 0;
static u32 z = 0;
unsigned int data = 0;
unsigned int g_rev;
unsigned int g_racePointer;
unsigned int g_raceCondition;
unsigned int g_FNsPointer;
unsigned int g_oldRacePointer5CC;
unsigned int g_oldRacePointer5D0;
unsigned int g_itemPointer;

bool is_pressed(u32 keys)
{
	if( Controller::IsKeysDown(keys) ) return true;
	return false;
}

/////////////////////////////////////////////////////////    Start of custom functions    /////////////////////////////////////////////////////////

unsigned int	GetRacePointer(void)
{
	unsigned int g_racePointer, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(READU32(READU32(0x140002F4) + 0x14) + 0x518) > 0x14000000 && READU32(READU32(READU32(0x140002F4) + 0x14) + 0x518) < 0x18000000)
	{
		g_racePointer = READU32(READU32(READU32(READU32(0x140002F4) + 0x14) + 0x518) + 0x1C);
		return (g_racePointer);
	}
	else
	{
		return (0);
	}
}

unsigned int	GetRaceCondition(void)
{
	unsigned int g_raceCondition;
	if (READU32(0x14000084) > 0x14000000 && READU32(0x14000084) < 0x18000000)
	{
		g_raceCondition = READU8(READU32(READU32(0x14000084) + 0x316C) + 0x118);
		return (g_raceCondition);
	}
	else
	{
		return (0);
	}
}

unsigned int	GetFNsPointer(void)
{
	unsigned int g_FNsPointer, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0xFFFF6F0) > 0x14000000 && READU32(0xFFFF6F0) < 0x18000000)
	{
		g_FNsPointer = READU32(0xFFFF6F0) + 8;
		return (g_FNsPointer);
    }
	else
	{
		return (0);
	}
}

unsigned int	GetOldPointer5CC(void)
{
	unsigned int g_oldRacePointer5CC, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0xFFFFBF4) > 0x14000000 && READU32(0xFFFFBF4) < 0x18000000 && READU32(READU32(0xFFFFBF4) + 0x5CC) > 0x14000000 && READU32(READU32(0xFFFFBF4) + 0x5CC) < 0x18000000)
	{
		g_oldRacePointer5CC = READU32(READU32(0xFFFFBF4) + 0x5CC);
		return (g_oldRacePointer5CC);
	}
	else
	{
		return (0);
	}
}

unsigned int	GetOldPointer5D0(void)
{
	unsigned int g_oldRacePointer5D0, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0xFFFFBF4) > 0x14000000 && READU32(0xFFFFBF4) < 0x18000000 && READU32(0x65C528) > 0x14000000 && READU32(0x65C528) < 0x18000000)
	{
		g_oldRacePointer5D0 = READU32(0x65C528);
		return (g_oldRacePointer5D0);
	}
	else
	{
		return (0);
	}
}

unsigned int	GetItemPointer(void)
{
	unsigned int g_itemPointer, g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1)
	{
		if (READU32(0x17782494) > 0x14000000 || READU32(0x177BE494) > 0x14000000)
		{
			if (READU32(0x17782494) < 0x18000000 || READU32(0x177BE494) < 0x18000000)
			{
				g_itemPointer = READU32(READU32(READU32(0x14000074) - 0x1B5C) + 0x27AC);
				return (g_itemPointer);
			}
		}
	}
	else
	{
		return (0);
	}
}

void	writeItem(u32 item)
{
	unsigned int g_raceCondition = GetRaceCondition(), g_itemPointer = GetItemPointer();
	if (g_raceCondition == 1 && g_itemPointer > 0x14000000 && g_itemPointer < 0x18000000)
	{
		WRITEU32(0x3C + g_itemPointer, 0xFFFFFFFF);
		WRITEU8(0xA8 + g_itemPointer, 3);
		WRITEU8(0xC8 + g_itemPointer, item);
		WRITEU32(0xD8 + g_itemPointer, 0x3F800000);
	}
}

void	writeSpeed(u32 speed)
{
	for (int i = 0; i < 0x2D; i++)
	{
		if (READU32(0x140002F4) > 0x14000000 && READU32(0x140002F4) < 0x18000000 && READU32(READU32(0x140002F4) - 0xA4) > 0x14000000 && READU32(READU32(0x140002F4) - 0xA4) < 0x18000000)
		{
			WRITEU32(READU32(READU32(0x140002F4) - 0xA4) - 0x2C3B0 + (i * 4), speed);
			WRITEU32(READU32(READU32(0x140002F4) - 0xA4) - 0x28E90 + (i * 4), speed);
			WRITEU32(READU32(READU32(0x140002F4) - 0xA4) - 0x1C730 + (i * 4), speed);
		}
	}
}

void	writeVR(u32 vr)
{
	if (READU32(0x663D04) > 0x10000000)
	{
		WRITEU32(READU32(0x663D04) - 0xE30, vr);
	}
}

void	writeLocation(u32 location)
{
	if (READU32(0x6673C8) > 0x10000000)
	{
		offset = READU32(0x6673C8);
		WRITEU32(offset + 0xF7CC, location);
	}
}

void	writeFlag(u8 flag)
{
	if (READU32(0x6673C8) > 0x10000000)
	{
		offset = READU32(0x6673C8);
		WRITEU8(offset + 0xE7CA, flag);
		WRITEU8(offset + 0xF7D0, flag);
	}
}

/////////////////////////////////////////////////////////    Start of race codes    /////////////////////////////////////////////////////////

void	invincible(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
	{
		WRITEU16(g_racePointer + 0x102C, 0xFFFF);
	}
}

void	alwaysStarPower(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
	{
		WRITEU16(g_racePointer + 0xFF4, 0xFFFF);
	}
}

void	trickAnywhere(void)
{
	u32 offset;
	u32 data;
	WRITEU32(offset + 0x02DB8DC, 0xE1A00000);
}

void	alwaysBlackKart(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
	{
		WRITEU16(g_racePointer + 0xFF8, 0xFFFF);
	}
}

void	alwaysShocked(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 & g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
	{
		WRITEU16(g_racePointer + 0x1000, 0xFFFF);
	}
}

void	alwaysCrushed(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
	{
		WRITEU16(g_racePointer + 0x1004, 0xFFFF);
	}
}

void	instantMT(void)
{
	WRITEU32(0x665634, 0);
	WRITEU32(0x665638, 0);
}

void	hugeBunnyhop(void)
{
	WRITEU32(0x6655D0, 0x40400000);
}

void	fastReverse(void)
{
	WRITEU32(0x6655A8, 0x41800000);
}

void	noCountdown(void)
{
	unsigned int g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x65C528) > 0x14000000 && READU32(0x65C528) < 0x18000000)
	{
		WRITEU8(READU32(0x65C528) + 0x109, 1);
		WRITEU8(READU32(0x65C528) + 0x589, 1);
	}
}

void	moonjump(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && is_pressed(Y + R + DU))
		WRITEU32(g_racePointer + 0x3C, 0x41200000);
}

void	saveSlotTeleporter(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	static u32 x = 0, y = 0, z = 0;
	if (g_raceCondition == 1)
	{
		if (is_pressed(ST + X))
		{
			x = READU32(g_racePointer + 0x24);
			y = READU32(g_racePointer + 0x28);
			z = READU32(g_racePointer + 0x2C);
		}
		if (is_pressed(ST + Y))
		{
			WRITEU32(g_racePointer + 0x24, x);
			WRITEU32(g_racePointer + 0x28, y);
			WRITEU32(g_racePointer + 0x2C, z);
		}
	}
}

void	maxTimer(void)
{
	unsigned int g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x65C528) > 0x14000000 && READU32(0x65C528) < 0x18000000)
		WRITEU32(READU32(0x65C528) + 0x80, 0x4650);
}

void	zeroTimer(void)
{
	unsigned int g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x65C528) > 0x14000000 && READU32(0x65C528) < 0x18000000)
		WRITEU32(READU32(0x65C528) + 0x80, 0);
}

void	waterEverywhere(void)
{
	unsigned int g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && READU32(0x663954) > 0x14000000 && READU32(0x663954) < 0x18000000 && READU32(READU32(0x663954) + 0x58) > 0x14000000 && READU32(READU32(0x663954) + 0x58) < 0x18000000)
		WRITEU32(READU32(READU32(0x663954) + 0x58) + 0x420, 0x48000000);
}

void	driveAnywhere(void)
{
	unsigned int g_raceCondition = GetRaceCondition(), g_racePointer = GetRacePointer();
	static unsigned int data = 0;
	if (g_raceCondition != 1)
	{
		data = 0;
		WRITEU32(0x6656D8, 0x14);
		return;
	}
	if (g_raceCondition == 1)
	{
		if (is_pressed(R + SE + DL))
		{
			data = 0;
			WRITEU32(0x6656D8, 0x14);
		}
		if (is_pressed(R + SE + DR))
		{
			data = 1;
			WRITEU32(0x6656D8, 0xFFFF);
		}
		if (data == 1)
		{
			WRITEU32(g_racePointer + 0x3C, 0);
			if (is_pressed(R + DU + Y))
			{
				WRITEU32(g_racePointer + 0x3C, 0x41000000);
			}
			if (is_pressed(R + DD + Y))
			{
				WRITEU32(g_racePointer + 0x3C, 0xC1000000);
			}
		}
	}
}

void	stalking(void) // could optimize a little more
{
	unsigned int g_raceCondition = GetRaceCondition(), g_racePointer = GetRacePointer(), tempActive = 0;
	static unsigned int pointer = 0, active = 0, player = 1;
	float dataY = 0, dataZ = 0;
	static bool held = false;
	if (g_raceCondition != 1)
	{
		player = 1;
		active = 0;
		pointer = 0;
		return;
	}
	if (g_raceCondition == 1)
	{
		if (!is_pressed(ST))
		{
			held = false;
		}
		if (is_pressed(ST))
		{
			tempActive = 1;
			if (is_pressed(DU))
			{
				active = 1;
			}	
			if (is_pressed(DD))
			{
				active = 0;
				player = 1;
			}
			if (!held)
			{
				if (is_pressed(DR))
				{
					held = true;
					player++;
				}
				if (is_pressed(DL))
				{
					held = true;
					player--;
				}
			}
		}
		if (active == 1 || tempActive == 1)
		{
			if (player > 8 || player < 1)
			{
				player = 1;
				return;
			}
			pointer = 0x209C + READU32(0x65DA44) + (player * 0x44);
			if (READU32(pointer) < 0x14000000 || READU32(pointer) > 0x18000000 || READU32(pointer) == g_racePointer || READU32(READU32(pointer) + 0x24) < 0x30000000 || READU32(READU32(pointer) + 0x24) > 0xD0000000 || READU32(READU32(pointer) + 0x2C) < 0x30000000 || READU32(READU32(pointer) + 0x2C) > 0xD0000000)
			{
				player++;
				return;
			}
			if (player > 0 && player < 9 && READU32(pointer) > 0x14000000 && READU32(pointer) < 0x18000000 && g_racePointer > 0x14000000 && g_racePointer < 0x18000000)
			{
				dataY = READFLOAT(READU32(pointer) + 0x28);
				dataY += 40;
				dataZ = READFLOAT(READU32(pointer) + 0x2C);
				if (dataY != 0 && dataY != 40 && dataZ != 0)
				{
					memcpy((void *)(g_racePointer), (void*)(READU32(pointer)), 0x28);
					WRITEFLOAT(g_racePointer + 0x28, dataY);
					WRITEFLOAT(g_racePointer + 0x2C, dataZ);
				}
				else
				{
					player++;
				}
			}
		}
	}
}

void	cpuBrawl(void)
{
	u32 g_raceCondition = GetRaceCondition(), pointer = 0, pointer2 = 0;
	if (g_raceCondition != 1)
		return;
	for (int i = 2; i < 9; i++)
	{
		pointer = READU32(0x209C + READU32(0x65DA44) + (i * 0x44));
		pointer2 = READU32(0x209C + READU32(0x65DA44) + ((i + 1) * 0x44));
		if (pointer > 0x16000000 && pointer < 0x18000000 && pointer2 > 0x16000000 && pointer2 < 0x18000000)
		{
			memcpy((void *)(pointer2 + 0x20), (void*)(pointer + 0x20), 24);
		}
	}
}

void	TouchCode(void)
{
	unsigned int g_raceCondition = GetRaceCondition(), g_racePointer = GetRacePointer();
	if (READU32(READU32(0x6789C8) + 0x1A48) == 1 && g_raceCondition == 1 && g_racePointer > 0x16000000 && g_racePointer < 0x18000000)
	{
		unsigned int touch_pointer = *(unsigned int *)0x6789C8;
		float X_Axis = *(float *)(touch_pointer + 0x1BCC);
		float Y_Axis = *(float *)(touch_pointer + 0x1BD0);
		unsigned int map_pointer = READU32(READU32(READU32(READU32(READU32(READU32(0x140002F4) + 0x14) + 0x370) + 0x270) + 0x60) + 0x688);
		float MapStatic1 = *(float *)map_pointer;
		float Map_Scale1 = *(float *)(map_pointer + 4);
		float MapStatic2 = *(float *)(map_pointer + 8);
		float Map_Scale2 = *(float *)(map_pointer + 12);
		Map_Scale1 -= Map_Scale2;
		Map_Scale1 /= 240.f;
		X_Axis *= Map_Scale1;
		Y_Axis *= Map_Scale1;
		X_Axis -= ((320.f * Map_Scale1) - MapStatic2);
		Y_Axis += Map_Scale2;
		*(float *)(g_racePointer + 0x3C) = 0;
		*(float *)(g_racePointer + 0x24) = X_Axis;
		*(float *)(g_racePointer + 0x2C) = Y_Axis;
	}
}

/////////////////////////////////////////////////////////    Start of item codes    /////////////////////////////////////////////////////////

void	fastBlueShell(void)
{
	WRITEU32(0x666094, 0x43000000);
}

void	stoppedBlueShell(void)
{
	WRITEU32(0x666094, 0);
}

void	fastGreenShell(void)
{
	WRITEU32(0x66619C, 0x43000000);
}

void	stoppedGreenShell(void)
{
	WRITEU32(0x66619C, 0);
}

void	dropMushrooms(void)
{
	unsigned int g_oldRacePointer5D0 = GetOldPointer5D0(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && g_oldRacePointer5D0 > 0x14000000 && g_oldRacePointer5D0 < 0x18000000)
	{
		WRITEU32(g_oldRacePointer5D0 + 0x1D0, READU32(g_oldRacePointer5D0 + 0x1F8));
	}
}

void	bulletControl(void)
{
	u32 offset;
	u32 data;
	if (is_pressed(0x00000013)) {
		offset = READU32(offset + 0x0666BB0);
		offset += 0xFFFF0000;
		if (READU32(offset + 0x000E248) > 0x16000000) {
			if (READU32(offset + 0x000E248) < 0x18000000) {
				offset = READU32(offset + 0x000E248);
				offset += 0xFFFF0000;
				WRITEU8(offset + 0x000EE9A, 0x40);
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000023)) {
		offset = READU32(offset + 0x0666BB0);
		offset += 0xFFFF0000;
		if (READU32(offset + 0x000E248) > 0x16000000) {
			if (READU32(offset + 0x000E248) < 0x18000000) {
				offset = READU32(offset + 0x000E248);
				offset += 0xFFFF0000;
				WRITEU8(offset + 0x000EE9A, 0x00);
			}
		}
	}
	offset = 0;
	data = 0;
}

void	disableStarMusic(void)
{
	unsigned int g_FNsPointer = GetFNsPointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && g_FNsPointer > 0x14000000 && g_FNsPointer < 0x18000000 && READU8(g_FNsPointer + 0x1F7) == 1)
	{
		WRITEU8(g_FNsPointer + 0x1F7, 0);
	}
}

void	bulletSpeed(void)
{
	if (is_pressed(A))
		WRITEU32(0x6655A4, 0x41C00000);
	if (is_pressed(B))
		WRITEU32(0x6655A4, 0xFF7FFFFF);
	if (is_pressed(Y))
		WRITEU32(0x6655A4, 0x40F33333);
}

void	blueShellRide(void)
{
	unsigned int dataX = 0, dataY = 0, dataZ = 0, g_raceCondition = GetRaceCondition(), g_racePointer = GetRacePointer();
	if (is_pressed(L + Y + DU))
	{
		if (g_raceCondition == 1 && READU32(0xFFFFBF4) > 0x14000000 && READU32(0xFFFFBF4) < 0x18000000 && READU32(READU32(0xFFFFBF4) - 0x63C) > 0x14000000 && READU32(READU32(0xFFFFBF4) - 0x63C) < 0x18000000)
		{
			dataX = READU32(READU32(READU32(0xFFFFBF4) - 0x63C) - 0x3CB0);
			dataY = READU32(READU32(READU32(0xFFFFBF4) - 0x63C) - 0x3CAC);
			dataZ = READU32(READU32(READU32(0xFFFFBF4) - 0x63C) - 0x3CA8);
			if (dataX > 0x1000 && dataX < 0xD0000000 &&  dataY > 0x1000 && dataY < 0xD0000000 && dataZ > 0x1000 && dataZ < 0xD0000000)
			{
				WRITEU32(g_racePointer + 0x24, dataX);
				WRITEU32(g_racePointer + 0x28, dataY);
				WRITEU32(g_racePointer + 0x2C, dataZ);
			}
		}
	}
}

void	itemWheel(void)
{
	u32 offset;
	u32 data;
	if (is_pressed(0x00000280)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0008) {
									WRITEU16(offset + 0x00000C8, 0x0008);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000220)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x000E) {
									WRITEU16(offset + 0x00000C8, 0x000E);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000210)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0005) {
									WRITEU16(offset + 0x00000C8, 0x0005);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000120)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0006) {
									WRITEU16(offset + 0x00000C8, 0x0006);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000180)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x000A) {
									WRITEU16(offset + 0x00000C8, 0x000A);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000110)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0009) {
									WRITEU16(offset + 0x00000C8, 0x0009);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000420)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0002) {
									WRITEU16(offset + 0x00000C8, 0x0002);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000480)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0004) {
									WRITEU16(offset + 0x00000C8, 0x0004);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000410)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0001) {
									WRITEU16(offset + 0x00000C8, 0x0001);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000820)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x000D) {
									WRITEU16(offset + 0x00000C8, 0x000D);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000880)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0000) {
									WRITEU16(offset + 0x00000C8, 0x0000);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000810)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x000C) {
									WRITEU16(offset + 0x00000C8, 0x000C);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
}

/////////////////////////////////////////////////////////    Start of speed codes    /////////////////////////////////////////////////////////

void	instantAcceleration(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && is_pressed(1) && g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
	{
		WRITEU32(g_racePointer + 0xF2C, READU32(READU32(READU32(0x140002F4) - 0xA4) - 0x2C3B0));
	}
}

void	instantBackAcceleration(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && is_pressed(2) && g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
	{
		WRITEFLOAT(g_racePointer + 0xF2C, -1.f * READFLOAT(READU32(READU32(0x140002F4) - 0xA4) - 0x2C3B0));
	}
}

void	instantStop(void)
{
	unsigned int g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && is_pressed(3) && g_racePointer > 0x15000000 && g_racePointer < 0x18000000)
	{
		WRITEU32(g_racePointer + 0xF2C, 0);
	}
}

void	TwoHundredCC(void)
{
	writeSpeed(0x413C0000);
}

void	FiveHundredCC(void)
{
	writeSpeed(0x41A00000);
}

/////////////////////////////////////////////////////////    Start of game modes    /////////////////////////////////////////////////////////

void	eliminationMode(void)
{
	WRITEU32(0x468D1C, 0xE1A00000);
	WRITEU32(0x469154, 0xE1A00000);
	WRITEU32(0x4165A8, 0xE1A00000);
	WRITEU32(0x233B54, 0xEA0EDF6D);
	offset = 0x5EB910;
	static const u8 buffer1[] = { 0xFF, 0x1F, 0x2D, 0xE9, 0xC4, 0x11, 0x9F, 0xE5, 0xC4, 0x31, 0x9F, 0xE5, 0xC4, 0x61, 0x9F, 0xE5, 0xC4, 0x71, 0x9F, 0xE5, 0xC4, 0x81, 0x9F, 0xE5, 0, 0x10, 0xD1, 0xE5, 0, 0, 0x51, 0xE3, 0x2, 0, 0, 0x1A, 0, 0x20, 0xA0, 0xE3, 0, 0x20, 0x83, 0xE5, 0x4, 0x20, 0x83, 0xE5, 0x1, 0, 0x51, 0xE3, 0x62, 0, 0, 0x1A, 0xA4, 0x11, 0x9F, 0xE5, 0, 0x90, 0x96, 0xE5, 0xC8, 0x90, 0x99, 0xE5, 0, 0, 0xA0, 0xE3, 0x34, 0, 0x89, 0xE5, 0x38, 0, 0x89, 0xE5, 0, 0x70, 0x97, 0xE5, 0x8, 0x70, 0x87, 0xE0, 0, 0x70, 0x97, 0xE5, 0x7, 0xB0, 0xA0, 0xE1, 0, 0x60, 0x96, 0xE5, 0xF4, 0x50, 0xD6, 0xE5, 0x2, 0, 0x55, 0xE3, 0x3, 0, 0, 0xA, 0x1E, 0x40, 0xA0, 0xE3, 0x46, 0x40, 0xC7, 0xE5, 0, 0, 0xD1, 0xE5, 0x4, 0, 0xC3, 0xE5, 0x2, 0, 0x55, 0xE3, 0x4E, 0, 0, 0x1A, 0, 0x20, 0x93, 0xE5, 0x46, 0x40, 0xD7, 0xE5, 0x1, 0x20, 0x82, 0xE2, 0x40, 0, 0x52, 0xE3, 0x8, 0, 0, 0xBA, 0, 0x20, 0xA0, 0xE3, 0, 0x20, 0x83, 0xE5, 0x1, 0x40, 0x44, 0xE2, 0, 0, 0x54, 0xE3, 0x2, 0, 0, 0xAA, 0x1E, 0x40, 0xA0, 0xE3, 0x46, 0x40, 0xC7, 0xE5, 0x1, 0, 0, 0xEA, 0x46, 0x40, 0xC7, 0xE5, 0, 0x20, 0x83, 0xE5, 0x46, 0x40, 0xD7, 0xE5, 0, 0, 0x54, 0xE3, 0x31, 0, 0, 0x1A, 0, 0x20, 0x93, 0xE5, 0x3E, 0, 0x52, 0xE3, 0x2E, 0, 0, 0x1A, 0x4, 0, 0xD3, 0xE5, 0xC8, 0x80, 0x96, 0xE5, 0, 0x6B, 0x96, 0xE5, 0x80, 0x50, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0x50, 0x90, 0xC6, 0xE5, 0xC4, 0x50, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0xC0, 0x90, 0xC6, 0xE5, 0x8, 0x51, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0x30, 0x91, 0xC6, 0xE5, 0x4C, 0x51, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0xA0, 0x91, 0xC6, 0xE5, 0x90, 0x51, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0x10, 0x92, 0xC6, 0xE5, 0xD4, 0x51, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0x80, 0x92, 0xC6, 0xE5, 0x18, 0x52, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0xF0, 0x92, 0xC6, 0xE5, 0x5C, 0x52, 0xD8, 0xE5, 0x5, 0, 0x50, 0xE1, 0x1, 0, 0, 0x1A, 0x4, 0x90, 0xA0, 0xE3, 0x60, 0x93, 0xC6, 0xE5, 0x4, 0, 0x93, 0xE5, 0x1, 0, 0x40, 0xE2, 0x4, 0, 0x83, 0xE5, 0xA, 0, 0, 0xEA, 0x4, 0, 0xD3, 0xE5, 0x8, 0x50, 0x93, 0xE5, 0x20, 0x50, 0x95, 0xE5, 0x1, 0, 0x55, 0xE3, 0x5, 0, 0, 0x1A, 0x1, 0, 0x50, 0xE3, 0x3, 0, 0, 0x1A, 0xC, 0x80, 0x93, 0xE5, 0, 0x90, 0xA0, 0xE3, 0x4, 0x90, 0x88, 0xE5, 0xB8, 0x95, 0xCB, 0xE1, 0xFF, 0x1F, 0xBD, 0xE8, 0x2C, 0x30, 0x93, 0xE5, 0x1D, 0x20, 0xF1, 0xEA, 0xF4, 0xFD, 0x78, 0x14, 0x7C, 0x1, 0x68, 0, 0x28, 0xC5, 0x65, 0, 0xAC, 0x5, 0, 0x14, 0xC4, 0x12, 0, 0, 0xE0, 0x4B, 0x47, 0x15 };
	memcpy((void *)(offset), buffer1, 0x1E8);
	WRITEU32(0x4690FC, 0xEB060A7D);
	offset = 0x5EBAF8;
	static const u8 buffer2[] = { 0x6C, 0x60, 0xA0, 0xE3, 0x59, 0x60, 0xC4, 0xE5, 0xE, 0xF0, 0xA0, 0xE1 };
	memcpy((void *)(offset), buffer2, 0xC);
	WRITEU32(0x3D4E04, 0xEB085B3E);
	offset = 0x5EBB04;
	static const u8 buffer3[] = { 0x8, 0x80, 0x9F, 0xE5, 0, 0, 0x88, 0xE5, 0x20, 0x90, 0x90, 0xE5, 0xE, 0xF0, 0xA0, 0xE1, 0x84, 0x1, 0x68, 0 };
	memcpy((void *)(offset), buffer3, 0x14);
	WRITEU32(0x45CBE4, 0xEA063BCB);
	offset = 0x5EBB18;
	static const u8 buffer4[] = { 0, 0x1, 0x2D, 0xE9, 0xC, 0x80, 0x9F, 0xE5, 0, 0, 0x88, 0xE5, 0, 0x1, 0xBD, 0xE8, 0x4, 0x10, 0x90, 0xE5, 0x2D, 0xC4, 0xF9, 0xEA, 0x88, 0x1, 0x68, 0 };
	memcpy((void *)(offset), buffer4, 0x1C);
}

void	tagMode(void)
{
	u32 g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition(), pointer = 0, d0pointer = 0, ccpointer = 0;
	static u8 playerSlot = 0, taggedPlayer = 0, score = 0;
	static u16 time = 0;
	static bool tagged = false;
	if (g_raceCondition != 1)
	{
		playerSlot = 0;
		pointer = 0;
		taggedPlayer = 0;
		time = 0;
		score = 30;
		tagged = false;
		return;
	}
	if (g_raceCondition == 1 && g_racePointer > 0x16000000 && g_racePointer < 0x18000000 && READU32(0x65DA44) > 0x14000000 && READU32(0x65DA44) < 0x18000000 && READU8(READU32(0x65C9A8) + 0x175A8) < 10 && READU32(0x140005AC) > 0x14000000 && READU32(0x140005AC) < 0x18000000)
	{
		if (READU32(READU32(0x140005AC) + 0x12C8) > 0x14000000 && READU32(READU32(0x140005AC) + 0x12C8) < 0x18000000 && READU32(READU32(0x140005AC) + 0x12C4) > 0x14000000 && READU32(READU32(0x140005AC) + 0x12C4) < 0x18000000)
		{
			ccpointer = READU32(READU32(0x140005AC) + 0x12C4);
			d0pointer = READU32(READU32(0x140005AC) + 0x12C8);
			playerSlot = READU8(READU32(0x65C9A8) + 0x175A8) + 1;
			if (READU16(d0pointer + 0x1878) == 7200)
			{
				score = 30;
				WRITEU8(ccpointer + 0x46, score);
				WRITEU8(ccpointer + 0x54, score);
				if (playerSlot == 1)
				{
					tagged = true;
					score = 51;
				}
			}
			for (int i = 1; i < 9; i++)
			{
				pointer = READU32(READU32(0x65DA44) + (i * 0x44) + 0x209C);
				if (pointer > 0x14000000 && pointer < 0x18000000)
				{
					if (READU16(pointer + 0xFF4) > 0x40 && READU16(pointer + 0xFF4) < 0x180)
					{
						taggedPlayer = i;
					}
				}
			}
			if (tagged)
			{
				WRITEU16(g_racePointer + 0xFF4, 0xB0);
				if (time == 0 && READU16(d0pointer + 0x1878) != 7200 || (time - 120) > READU16(d0pointer + 0x1878))
				{
					score--;
					time = READU16(d0pointer + 0x1878);
					WRITEU8(ccpointer + 0x46, score);
					WRITEU8(ccpointer + 0x54, score);
					if (time < 6900 && READU16(g_racePointer + 0xFF4) > 0x40 && taggedPlayer != playerSlot)
					{
						WRITEU16(g_racePointer + 0xFF4, 0);
						tagged = false;
						return;
					}
				}
				if (READU16(g_racePointer + 0x1F6C) > 5 && READU16(g_racePointer + 0x1F6C) < 0xA000)
				{
					for (int i = 1; i < 9; i++)
					{
						pointer = READU32(READU32(0x65DA44) + (i * 0x44) + 0x209C);
						if (i == playerSlot)
						{
							continue;
						}
						if (READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) < 40.f && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) > -40.f)
						{
							if (READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) < 40.f && READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) > -40.f)
							{
								if (READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) < 40.f && READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) > -40.f)
								{
									WRITEU16(g_racePointer + 0xFF4, 0);
									tagged = false; 
									taggedPlayer = i;
								}
							}
						}
					}
				}
			}
			if (!tagged)
			{
				pointer = READU32(READU32(0x65DA44) + (taggedPlayer * 0x44) + 0x209C);
				WRITEU16(g_racePointer + 0xFF4, 0);
				if (time == 0 || (time - 120) > READU16(d0pointer + 0x1878))
				{
					if (score < 99)
						score++;
					time = READU16(d0pointer + 0x1878);
					WRITEU8(ccpointer + 0x46, score);
					WRITEU8(ccpointer + 0x54, score);
					if (time < 6900 && READU16(READU32(READU32(0x65DA44) + (taggedPlayer * 0x44) + 0x209C) + 0xFF4) < 0x40 && playerSlot == taggedPlayer)
					{
						tagged = true;
						taggedPlayer = playerSlot;
						return;
					}
				}
				if (READU16(g_racePointer + 0xC32) == 1 && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) < 40.f && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) > -40.f)
				{
					if (READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) < 40.f && READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) > -40.f)
					{
						if (READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) < 40.f && READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) > -40.f)
						{
							WRITEU16(g_racePointer + 0xFF4, 0xB0);
							tagged = true;
							taggedPlayer = playerSlot;
						}
					}
				}
			}
		}
	}
}

void	shineTheif(void)
{
	u32 g_racePointer = GetRacePointer(), g_raceCondition = GetRaceCondition(), pointer = 0, d0pointer = 0, ccpointer = 0;
	static u8 playerSlot = 0, shinePlayer = 0, score = 0;
	static u16 time = 0;
	static bool withShine = false;
	if (g_raceCondition != 1)
	{
		playerSlot = 0;
		pointer = 0;
		shinePlayer = 0;
		time = 0;
		score = 0;
		withShine = false;
		return;
	}
	if (g_raceCondition == 1 && g_racePointer > 0x16000000 && g_racePointer < 0x18000000 && READU32(0x65DA44) > 0x14000000 && READU32(0x65DA44) < 0x18000000 && READU8(READU32(0x65C9A8) + 0x175A8) < 10 && READU32(0x140005AC) > 0x14000000 && READU32(0x140005AC) < 0x18000000)
	{
		if (READU32(READU32(0x140005AC) + 0x12C8) > 0x14000000 && READU32(READU32(0x140005AC) + 0x12C8) < 0x18000000 && READU32(READU32(0x140005AC) + 0x12C4) > 0x14000000 && READU32(READU32(0x140005AC) + 0x12C4) < 0x18000000)
		{
			ccpointer = READU32(READU32(0x140005AC) + 0x12C4);
			d0pointer = READU32(READU32(0x140005AC) + 0x12C8);
			playerSlot = READU8(READU32(0x65C9A8) + 0x175A8) + 1;
			if (READU16(d0pointer + 0x1878) == 7200)
			{
				score = 0;
				WRITEU8(ccpointer + 0x46, score);
				WRITEU8(ccpointer + 0x54, score);
				if (playerSlot == 1)
				{
					withShine = true;
				}
			}
			for (int i = 1; i < 9; i++)
			{
				pointer = READU32(READU32(0x65DA44) + (i * 0x44) + 0x209C);
				if (pointer > 0x14000000 && pointer < 0x18000000)
				{
					if (READU16(pointer + 0xFF4) > 0x40 && READU16(pointer + 0xFF4) < 0x180)
					{
						shinePlayer = i;
					}
				}
			}
			if (withShine)
			{
				WRITEU16(g_racePointer + 0xFF4, 0xB0);
				if (time == 0 && READU16(d0pointer + 0x1878) != 7200 || (time - 120) > READU16(d0pointer + 0x1878))
				{
					score++;
					time = READU16(d0pointer + 0x1878);
					WRITEU8(ccpointer + 0x46, score);
					WRITEU8(ccpointer + 0x54, score);
					if (time < 6900 && READU16(g_racePointer + 0xFF4) > 0x40 && shinePlayer != playerSlot)
					{
						WRITEU16(g_racePointer + 0xFF4, 0);
						withShine = false;
						return;
					}
				}
				if (READU16(g_racePointer + 0x1F6C) > 5 && READU16(g_racePointer + 0x1F6C) < 0xA000)
				{
					for (int i = 1; i < 9; i++)
					{
						pointer = READU32(READU32(0x65DA44) + (i * 0x44) + 0x209C);
						if (i == playerSlot)
						{
							continue;
						}
						if (READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) < 40.f && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) > -40.f)
						{
							if (READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) < 40.f && READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) > -40.f)
							{
								if (READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) < 40.f && READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) > -40.f)
								{
									WRITEU16(g_racePointer + 0xFF4, 0);
									withShine = false; 
									shinePlayer = i;
								}
							}
						}
					}
				}
			}
			if (!withShine)
			{
				pointer = READU32(READU32(0x65DA44) + (shinePlayer * 0x44) + 0x209C);
				WRITEU16(g_racePointer + 0xFF4, 0);
				if (time == 0 || (time - 120) > READU16(d0pointer + 0x1878))
				{
					time = READU16(d0pointer + 0x1878);
					if (time < 6900 && READU16(READU32(READU32(0x65DA44) + (shinePlayer * 0x44) + 0x209C) + 0xFF4) < 0x40 && playerSlot == shinePlayer)
					{
						withShine = true;
						shinePlayer = playerSlot;
						return;
					}
				}
				if (READU16(g_racePointer + 0xC32) == 1 && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) < 40.f && READFLOAT(pointer + 0x24) - READFLOAT(g_racePointer + 0x24) > -40.f)
				{
					if (READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) < 40.f && READFLOAT(pointer + 0x28) - READFLOAT(g_racePointer + 0x28) > -40.f)
					{
						if (READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) < 40.f && READFLOAT(pointer + 0x2C) - READFLOAT(g_racePointer + 0x2C) > -40.f)
						{
							WRITEU16(g_racePointer + 0xFF4, 0xB0);
							withShine = true;
							shinePlayer = playerSlot;
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////    Start of menu codes    /////////////////////////////////////////////////////////

void	disableFirstPersonView(void)
{
	offset = READU32(READU32(0x14000084) + 0x316C); // for some reason this doesn't work when it's reduced to one line...
	WRITEU8(offset + 0x119, 0);
}

void	vrExtender(void)
{
	if (READU32(0x663D04) > 0x10000000)
	{
		if(is_pressed(ST))
		{
			writeVR(654321);
		}
		if(is_pressed(X))
		{
			writeVR(350000);
		}
		if(is_pressed(DD))
		{
			writeVR(777777);
		}
		if(is_pressed(DU))
		{
			writeVR(999999);
		}
		if(is_pressed(DR))
		{
			writeVR(123456);
		}
		if(is_pressed(DL))
		{
			writeVR(0);
		}
	}
}

void	randomVR(void)
{
	if (READU16(0x14296A90) > 20000 && READU16(0x14296A90) < 200000)
	{
		random_v = READU16(0x14296A90) * 5;
		if (READU32(0x663D04) > 0x14000000 && READU32(0x663D04) < 0x18000000)
		{
			writeVR(random_v);
		}
	}
}

void	unlockEverything(void)
{
	if (READU32(0x6673C8) > 0x10000000 && READU32(0x6673C8) < 0x18000000)
	{
		offset = READU32(0x6673C8);
		WRITEU8(0x6BA3 + offset, 0x3F);
		WRITEU32(0x6BA4 + offset, 0x1FF003F);
		WRITEU16(0x6BAC + offset, 0x3FFF);
		WRITEU8(0x6BB0 + offset, 0x7F);
		WRITEU8(0x6BB4 + offset, 0x3F);
		WRITEU8(0x6BB8 + offset, 0xFF);
	}
}

void	NoDC(void)
{
	unsigned int g_oldRacePointer5CC = GetOldPointer5CC(), g_raceCondition = GetRaceCondition();
	if (g_raceCondition == 1 && g_oldRacePointer5CC > 0x14000000 && g_oldRacePointer5CC < 0x18000000)
	{
		WRITEU8(g_oldRacePointer5CC + 0x40, 2);
	}
}

void	fastGame(void)
{
	if (READU32(0x140002F4) > 0x14000000 && READU32(0x140002F4) < 0x18000000)
	{
		WRITEU32(READU32(READU32(0x140002F4) + 0x14) + 0x2B4, 0);
	}
}

/////////////////////////////////////////////////////////    Tsuika codes    /////////////////////////////////////////////////////////

void	ASS(void)
{
	u32 offset;
	u32 data;
	offset = READU32(offset + 0x0666BB0);
	offset += 0xFFFF0000;
	if (READU32(offset + 0x000E248) > 0x16000000) {
		if (READU32(offset + 0x000E248) < 0x18000000) {
			offset = READU32(offset + 0x000E248);
			offset += 0xFFFF0000;
			WRITEU16(offset + 0x000F240, 0xFFFF);
		}
	}
	offset = 0;
	data = 0;
}

void	IRP(void)
{
	u32 offset;
	u32 data;
	WRITEU32(offset + 0x02F96C4, 0xE5850241);
}

void	CC9000(void)
{
	writeSpeed(0x42C80000);
}

void	AutoPilot(void)
{
	u32 offset;
	u32 data;
	offset = READU32(offset + 0x0666BB0);
	offset += 0xFFFF0000;
	if (READU32(offset + 0x000E248) > 0x16000000) {
		if (READU32(offset + 0x000E248) < 0x18000000) {
			offset = READU32(offset + 0x000E248);
			offset += 0xFFFF0000;
			WRITEU8(offset + 0x000E30E, 0x01);
		}
	}
	offset = 0;
	data = 0;
}

void	ItemBattle(void)
{
	u32 offset;
	u32 data;
	if (is_pressed(0x00000280)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0008) {
									WRITEU16(offset + 0x00000C8, 0x0008);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000220)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x000E) {
									WRITEU16(offset + 0x00000C8, 0x000E);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000210)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0005) {
									WRITEU16(offset + 0x00000C8, 0x0005);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000180)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x000A) {
									WRITEU16(offset + 0x00000C8, 0x000A);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000110)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0009) {
									WRITEU16(offset + 0x00000C8, 0x0009);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000420)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0002) {
									WRITEU16(offset + 0x00000C8, 0x0002);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000480)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0004) {
									WRITEU16(offset + 0x00000C8, 0x0004);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000410)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0001) {
									WRITEU16(offset + 0x00000C8, 0x0001);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000820)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x000D) {
									WRITEU16(offset + 0x00000C8, 0x000D);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000880)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x0000) {
									WRITEU16(offset + 0x00000C8, 0x0000);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000810)) {
		offset = 0x14000000;
		if (READU32(offset + 0x0000074) > 0x16000000) {
			if (READU32(offset + 0x0000074) < 0x18000000) {
				offset = READU32(offset + 0x0000074);
				offset += 0xFFFFE4A4;
				if (READU32(offset + 0x0000000) > 0x16000000) {
					if (READU32(offset + 0x0000000) < 0x18000000) {
						offset = READU32(offset + 0x0000000);
						if (READU32(offset + 0x00027AC) > 0x16000000) {
							if (READU32(offset + 0x00027AC) < 0x18000000) {
								offset = READU32(offset + 0x00027AC);
								WRITEU32(offset + 0x000003C, 0xFFFFFFFF);
								WRITEU32(offset + 0x00000D8, 0xFFFFFFFF);
								WRITEU8(offset + 0x00000A8, 0x03);
								if (READU16(offset + 0x00000C8) != 0x000C) {
									WRITEU16(offset + 0x00000C8, 0x000C);
									WRITEU32(offset + 0x00000BC, 0x00000000);
								}
							}
						}
					}
				}
			}
		}
	}
	offset = 0;
	data = 0;
}

void	CoBTpts(void)
{
	u32 offset;
	u32 data;
	if (is_pressed(0x00000540)) {
		if (READU32(offset + 0xFFFFBF4) > 0x16000000) {
			if (READU32(offset + 0xFFFFBF4) < 0x18000000) {
				offset = READU32(offset + 0xFFFFBF4);
				offset = READU32(offset + 0x00005CC);
				data = READU8(offset + 0x00000054);
				offset += 0x00000001;
				WRITEU8(offset + 0x00000054, data);
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000580)) {
		if (READU32(offset + 0xFFFFBF4) > 0x16000000) {
			if (READU32(offset + 0xFFFFBF4) < 0x18000000) {
				offset = READU32(offset + 0xFFFFBF4);
				offset = READU32(offset + 0x00005CC);
				data = READU8(offset + 0x00000054);
				offset += 0xFFFFFFFF;
				WRITEU8(offset + 0x00000054, data);
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000540)) {
		if (READU32(offset + 0xFFFFBF4) > 0x16000000) {
			if (READU32(offset + 0xFFFFBF4) < 0x18000000) {
				offset = READU32(offset + 0xFFFFBF4);
				offset = READU32(offset + 0x00005CC);
				data = READU8(offset + 0x00000046);
				offset += 0x00000001;
				WRITEU32(offset + 0x00000046, data);
				offset += 0x4;
				WRITEU8(offset + 0x00000000, data);
			}
		}
	}
	offset = 0;
	data = 0;
	if (is_pressed(0x00000580)) {
		if (READU32(offset + 0xFFFFBF4) > 0x16000000) {
			if (READU32(offset + 0xFFFFBF4) < 0x18000000) {
				offset = READU32(offset + 0xFFFFBF4);
				offset = READU32(offset + 0x00005CC);
				data = READU8(offset + 0x00000046);
				offset += 0xFFFFFFFF;
				WRITEU8(offset + 0x00000046, data);
			}
		}
	}
	offset = 0;
	data = 0;
}

void	All99k(void)
{
	u32 offset;
	u32 data;
	offset = READU32(offset + 0x06673C8);
	WRITEU32(offset + 0x000698C, 0x0001869F);
	WRITEU32(offset + 0x0006B88, 0x0001869F);
	WRITEU32(offset + 0x0006B98, 0x0001869F);
	WRITEU32(offset + 0x0006B9C, 0x0001869F);
	WRITEU32(offset + 0x0006BA0, 0x3F01869F);
	offset = 0;
	data = 0;
}

void	vrM(void)
{
	if (READU32(0x663D04) > 0x10000000)
	{
		if(is_pressed(ST))
		{
			writeVR(1);
		}
		if(is_pressed(X))
		{
			writeVR(1000);
		}
		if(is_pressed(DD))
		{
			writeVR(5000);
		}
		if(is_pressed(DU))
		{
			writeVR(99999);
		}
		if(is_pressed(DR))
		{
			writeVR(50000);
		}
		if(is_pressed(DL))
		{
			writeVR(10000);
		}
	}
}

void	vrE2(void)
{
	if (READU32(0x663D04) > 0x10000000)
	{
		if(is_pressed(ST))
		{
			writeVR(512810);
		}
		if(is_pressed(X))
		{
			writeVR(454545);
		}
		if(is_pressed(DD))
		{
			writeVR(364364);
		}
		if(is_pressed(DU))
		{
			writeVR(114514);
		}
		if(is_pressed(DR))
		{
			writeVR(931810);
		}
		if(is_pressed(DL))
		{
			writeVR(191919);
		}
	}
}

void	vrE3(void)
{
	if (READU32(0x663D04) > 0x10000000)
	{
		if(is_pressed(ST))
		{
			writeVR(427427);
		}
		if(is_pressed(X))
		{
			writeVR(564731);
		}
		if(is_pressed(DD))
		{
			writeVR(427311);
		}
		if(is_pressed(DU))
		{
			writeVR(375641);
		}
		if(is_pressed(DR))
		{
			writeVR(444444);
		}
		if(is_pressed(DL))
		{
			writeVR(564219);
		}
	}
}

void	vr1(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00000001);
	}
	offset = 0;
	data = 0;
}

void	vr1000(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000003E8);
	}
	offset = 0;
	data = 0;
}

void	vr5000(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00001388);
	}
	offset = 0;
	data = 0;
}

void	vr10000(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00002710);
	}
	offset = 0;
	data = 0;
}

void	vr50000(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0000C350);
	}
	offset = 0;
	data = 0;
}

void	vr99999(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0001869F);
	}
	offset = 0;
	data = 0;
}

void	vr114514(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0001BF52);
	}
	offset = 0;
	data = 0;
}

void	vr931810(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000E37E2);
	}
	offset = 0;
	data = 0;
}

void	vr512810(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0007D32A);
	}
	offset = 0;
	data = 0;
}

void	vr454545(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0006EF91);
	}
	offset = 0;
	data = 0;
}

void	vr191919(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0002EDAF);
	}
	offset = 0;
	data = 0;
}

void	vr364364(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00058F4C);
	}
	offset = 0;
	data = 0;
}

void	vr375641(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0005BB59);
	}
	offset = 0;
	data = 0;
}

void	vr564219(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00089BFB);
	}
	offset = 0;
	data = 0;
}

void	vr564731(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00089DFB);
	}
	offset = 0;
	data = 0;
}

void	vr427311(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0006852F);
	}
	offset = 0;
	data = 0;
}

void	vr427427(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000685A3);
	}
	offset = 0;
	data = 0;
}

void	vr0(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00000000);
	}
	offset = 0;
	data = 0;
}

void	vr999999(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000F423F);
	}
	offset = 0;
	data = 0;
}

void	vr696969(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000AA289);
	}
	offset = 0;
	data = 0;
}

void	vr420000(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000668A0);
	}
	offset = 0;
	data = 0;
}

void	vr495000(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00078D98);
	}
	offset = 0;
	data = 0;
}

void	vr350000(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00055730);
	}
	offset = 0;
	data = 0;
}

void	vr355555(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00056CE3);
	}
	offset = 0;
	data = 0;
}

void	vr199998(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00030D3E);
	}
	offset = 0;
	data = 0;
}

void	vr655534(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000A00AE);
	}
	offset = 0;
	data = 0;
}

void	vr200102(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00030DA6);
	}
	offset = 0;
	data = 0;
}

void	vr123456(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0001E240);
	}
	offset = 0;
	data = 0;
}

void	vr654321(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0009FBF1);
	}
	offset = 0;
	data = 0;
}

void	vr888888(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000D9038);
	}
	offset = 0;
	data = 0;
}

void	vr777777(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000BDE31);
	}
	offset = 0;
	data = 0;
}

void	vr666666(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000A2C2A);
	}
	offset = 0;
	data = 0;
}

void	vr555555(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00087A23);
	}
	offset = 0;
	data = 0;
}

void	vr444444(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0006C81C);
	}
	offset = 0;
	data = 0;
}

void	vr333333(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x00051615);
	}
	offset = 0;
	data = 0;
}

void	vr222222(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0003640E);
	}
	offset = 0;
	data = 0;
}

void	vr111111(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x0001B207);
	}
	offset = 0;
	data = 0;
}

void	vr100000(void)
{
	u32 offset;
	u32 data;
	if (READU32(offset + 0x0663D04) != 0x00000000) {
		offset = READU32(offset + 0x0663D04);
		offset += 0xFFFF0000;
		WRITEU32(offset + 0x000F1D0, 0x000186A0);
	}
	offset = 0;
	data = 0;
}

void	pts40(void)
{
	u32 offset;
	u32 data;
	offset = 0x00000000;
	offset = READU32(offset + 0x065C9A8);
	if (READU16(offset + 0x00175A8) == 0x0000) {
		WRITEU16(offset + 0x0017444, 0x0028);
	}
	if (READU16(offset + 0x00175A8) == 0x0001) {
		WRITEU16(offset + 0x0017470, 0x0028);
	}
	if (READU16(offset + 0x00175A8) == 0x0002) {
		WRITEU16(offset + 0x001749C, 0x0028);
	}
	if (READU16(offset + 0x00175A8) == 0x0003) {
		WRITEU16(offset + 0x00174C8, 0x0028);
	}
	if (READU16(offset + 0x00175A8) == 0x0004) {
		WRITEU16(offset + 0x00174F4, 0x0028);
	}
	if (READU16(offset + 0x00175A8) == 0x0005) {
		WRITEU16(offset + 0x0017520, 0x0028);
	}
	if (READU16(offset + 0x00175A8) == 0x0006) {
		WRITEU16(offset + 0x001754C, 0x0028);
	}
	if (READU16(offset + 0x00175A8) == 0x0007) {
		WRITEU16(offset + 0x0017578, 0x0028);
	}
	offset = 0;
	data = 0;
}

void	pts255(void)
{
	u32 offset;
	u32 data;
	offset = 0x00000000;
	offset = READU32(offset + 0x065C9A8);
	if (READU16(offset + 0x00175A8) == 0x0000) {
		WRITEU16(offset + 0x0017444, 0x00FF);
	}
	if (READU16(offset + 0x00175A8) == 0x0001) {
		WRITEU16(offset + 0x0017470, 0x00FF);
	}
	if (READU16(offset + 0x00175A8) == 0x0002) {
		WRITEU16(offset + 0x001749C, 0x00FF);
	}
	if (READU16(offset + 0x00175A8) == 0x0003) {
		WRITEU16(offset + 0x00174C8, 0x00FF);
	}
	if (READU16(offset + 0x00175A8) == 0x0004) {
		WRITEU16(offset + 0x00174F4, 0x00FF);
	}
	if (READU16(offset + 0x00175A8) == 0x0005) {
		WRITEU16(offset + 0x0017520, 0x00FF);
	}
	if (READU16(offset + 0x00175A8) == 0x0006) {
		WRITEU16(offset + 0x001754C, 0x00FF);
	}
	if (READU16(offset + 0x00175A8) == 0x0007) {
		WRITEU16(offset + 0x0017578, 0x00FF);
	}
	offset = 0;
	data = 0;
}

void	pts999(void)
{
	u32 offset;
	u32 data;
	offset = 0x00000000;
	offset = READU32(offset + 0x065C9A8);
	if (READU16(offset + 0x00175A8) == 0x0000) {
		WRITEU16(offset + 0x0017444, 0x03E7);
	}
	if (READU16(offset + 0x00175A8) == 0x0001) {
		WRITEU16(offset + 0x0017470, 0x03E7);
	}
	if (READU16(offset + 0x00175A8) == 0x0002) {
		WRITEU16(offset + 0x001749C, 0x03E7);
	}
	if (READU16(offset + 0x00175A8) == 0x0003) {
		WRITEU16(offset + 0x00174C8, 0x03E7);
	}
	if (READU16(offset + 0x00175A8) == 0x0004) {
		WRITEU16(offset + 0x00174F4, 0x03E7);
	}
	if (READU16(offset + 0x00175A8) == 0x0005) {
		WRITEU16(offset + 0x0017520, 0x03E7);
	}
	if (READU16(offset + 0x00175A8) == 0x0006) {
		WRITEU16(offset + 0x001754C, 0x03E7);
	}
	if (READU16(offset + 0x00175A8) == 0x0007) {
		WRITEU16(offset + 0x0017578, 0x03E7);
	}
	offset = 0;
	data = 0;
}

/////////////////////////////////////////////////////////    Start of region & flag codes    /////////////////////////////////////////////////////////

void	region_Africa(void)
{
	writeLocation(Africa);
}

void	region_Argentina(void)
{
	writeLocation(ArgentinaSouthAmerica);
}

void	region_Australia(void)
{
	writeLocation(Australia);
}

void	region_China(void)
{
	writeLocation(MainlandChina);
}

void	region_Cuba(void)
{
	writeLocation(Cuba);
}

void	region_France(void)
{
	writeLocation(France);
}

void	region_Hawaii(void)
{
	writeLocation(Hawaii);
}

void	region_Haiti(void)
{
	writeLocation(Haiti);
}

void	region_Iran(void)
{
	writeLocation(Iran);
}

void	region_Iceland(void)
{
	writeLocation(Iceland);
}

void	region_Phillippines(void)
{
	writeLocation(Phillippines);
}

void	region_NorthernPhillippines(void)
{
	writeLocation(NorthernPhillippines);
}

void	region_Russia(void)
{
	writeLocation(RussiaEnmelen);
}

void	region_SaudiArabia(void)
{
	writeLocation(SaudiArabia);
}

void	region_UnitedStates(void)
{
	writeLocation(UnitedStates);
}

void	region_NorthPole(void)
{
	writeLocation(NorthPole);
}

void	region_NorthernPole(void)
{
	writeLocation(NorthernPole);
}

void	region_NorthernAntartica(void)
{
	writeLocation(NorthernNorthernAntarctica);
}

void	region_UpperAntartica(void)
{
	writeLocation(UpperAntartica);
}

void	region_LowerAntartica(void)
{
	writeLocation(LowerAntartica);
}

void	region_LowerAntartica2(void)
{
	writeLocation(LowerLowerAntarctica);
}

void	region_MoreAntartica(void)
{
	writeLocation(MoreAntarctica);
}

void	region_MoreAntartica2(void)
{
	writeLocation(MoreAntartica2);
}

void	region_MoreAntartica3(void)
{
	writeLocation(MoreAntarctica3);
}

void	region_MoreAntartica4(void)
{
	writeLocation(MoreAntarctica4);
}

void	region_MoreAntartica5(void)
{
	writeLocation(MoreAntarctica5);
}

void	region_MoreAntartica6(void)
{
	writeLocation(MoreAntarctica6);
}

void	region_wtf(void)
{
	writeLocation(wtf);
}

void	region_wtf2(void)
{
	writeLocation(wtf2);
}

void	region_wtf3(void)
{
	writeLocation(wtf3);
}

void	region_Unknown(void)
{
	writeLocation(Unknown);
}

void	region_SpaghettiNoppers(void)
{
	writeLocation(SpaghettiNoppersRegionSetting);
}

void	flag_AntiguaAndBarbuda(void)
{
	writeFlag(AntiguaAndBarbuda);
}

void	flag_Argentina(void)
{
	writeFlag(Argentina);
}

void	flag_Australia(void)
{
	writeFlag(Australia1);
}

void	flag_Belize(void)
{
	writeFlag(Belize);
}

void	flag_Brazil(void)
{
	writeFlag(Brazil);
}

void	flag_BritishVirginIslands(void)
{
	writeFlag(BritishVirginIslands);
}

void	flag_Canada(void)
{
	writeFlag(Canada);
}

void	flag_Chile(void)
{
	writeFlag(Chile);
}

void	flag_China(void)
{
	writeFlag(China);
}

void	flag_Dominica(void)
{
	writeFlag(Dominica);
}

void	flag_Denmark(void)
{
	writeFlag(Denmark);
}

void	flag_Ecuador(void)
{
	writeFlag(Ecuador);
}

void	flag_Finland(void)
{
	writeFlag(Finland);
}

void	flag_France(void)
{
	writeFlag(France1);
}

void	flag_Germany(void)
{
	writeFlag(Germany);
}

void	flag_Greece(void)
{
	writeFlag(Greece);
}

void	flag_Haiti(void)
{
	writeFlag(Haiti1);
}

void	flag_Iceland(void)
{
	writeFlag(Iceland1);
}

void	flag_Italy(void)
{
	writeFlag(Italy);
}

void	flag_India(void)
{
	writeFlag(India);
}

void	flag_Japan(void)
{
	writeFlag(Japan);
}

void	flag_NewZealand(void)
{
	writeFlag(NewZealand);
}

void	flag_Panama(void)
{
	writeFlag(Panama);
}

void	flag_Russia(void)
{
	writeFlag(Russia);
}

void	flag_SouthAfrica(void)
{
	writeFlag(SouthAfrica);
}

void	flag_SouthKorea(void)
{
	writeFlag(SouthKorea);
}

void	flag_SaudiArabia(void)
{
	writeFlag(SaudiArabia1);
}

void	flag_Taiwan(void)
{
	writeFlag(Taiwan);
}

void	flag_UnitedStates(void)
{
	writeFlag(UnitedStates1);
}

void	flag_UnitedKingdom(void)
{
	writeFlag(UnitedKingdom);
}

void	flag_Uruguay(void)
{
	writeFlag(Uruguay);
}

void	flag_USVirginIslands(void)
{
	writeFlag(USVirginIslands);
}

/////////////////////////////////////////////////////////    Limiter codes    /////////////////////////////////////////////////////////

void	lightningLimiterOnline(void)
{
	u32 offset;
	u32 data;
	if (is_pressed(0x00000400)) {
		WRITEU32(offset + 0x02BA648, 0xE3A03001);
		WRITEU32(offset + 0x02BA678, 0xE5900038);
		WRITEU32(offset + 0x02BA69C, 0xE3A03001);
		WRITEU32(offset + 0x02BA6A4, 0xE3A0100A);
		WRITEU32(offset + 0x02BE2C0, 0xE3A0500E);
		WRITEU32(offset + 0x05062B8, 0xE1A00000);
		offset = 0x14000000;
		if (READU16(offset + 0x07909F4) == 0x0001) {
			if (READU32(offset + 0x3782494) != 0x00000000) {
				offset = READU32(offset + 0x3782494);
				offset = READU32(offset + 0x00027AC);
				WRITEU8(offset + 0x0000040, 0xFF);
			}
		}
	}
	offset = 0;
	data = 0;
}

/////////////////////////////////////////////////////////    End of codes    /////////////////////////////////////////////////////////