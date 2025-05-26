/*
 * mididecode.c
 *
 *  Created on: 2025/05/21
 *      Author: M.Akino
 */

#include "DebugMonitorUsbMidi.h"
#include "mididecode.h"

static void midiDecodeOut(uint8_t sts, uint8_t dt1, uint8_t dt2)
{
	switch (sts & 0xf0)
	{
	case 0x80:
		break;
	case 0x90:
		break;
	case 0xa0:
		break;
	case 0xb0:
		break;
	case 0xc0:
		break;
	case 0xd0:
		break;
	case 0xe0:
		break;
	case 0xf0:
		switch (sts)
		{
		case 0xf1:
			break;
		case 0xf2:
			break;
		case 0xf3:
			break;
		case 0xf6:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	DebugMonitor_entryUsbMidi(sts, dt1, dt2);

	return;
}

void midiDecode(uint8_t data)
{
	static uint8_t sts = 0;
	static uint8_t f3b = 0;
	static uint8_t dt1 = 0;
	static uint8_t clr = 0;

	if (data >= 0x80)
	{
		if (data >= 0xf8)
		{
			midiDecodeOut(data, 0, 0);
		}
		else
		{
			sts = data;
			f3b = 0;
			if (data == 0xf6)
			{
				midiDecodeOut(data, 0, 0);
			}
		}
	}
	else
	{
		if (f3b)
		{
			f3b = 0;
			midiDecodeOut(sts, dt1, data);
			if (clr)
			{
				sts = 0;
			}
		}
		else if (sts)
		{
			int type = 0;

			clr = 0;
			if (sts < 0xc0)
			{
				type = 3;
			}
			else if (sts < 0xe0)
			{
				type = 2;
			}
			else if (sts < 0xf0)
			{
				type = 3;
			}
			else
			{
				clr = 1;
				if (sts == 0xf2)
				{
					type = 3;
				}
				else if ((sts == 0xf3) || (sts == 0xf1))
				{
					type = 2;
				}
			}
			if (type == 2)
			{
				midiDecodeOut(sts, data, 0);
				if (clr)
				{
					sts = 0;
				}
			}
			else if (type == 3)
			{
				f3b = 1;
				dt1 = data;
			}
			else if (clr)
			{
				sts = 0;
			}
		}
	}

	return;
}
