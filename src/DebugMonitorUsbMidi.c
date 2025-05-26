/*
 * DebugMonitorUsbMidi.c
 *
 *  Created on: 2025/05/21
 *      Author: M.Akino
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "tusb.h"
#include "DebugMonitor.h"
#include "circure.h"
#include "usbmidi.h"

#define POLYKEYPRESS (10)

#define BUFFERSIZE 128

static uint8_t rxbuf[BUFFERSIZE];
static circure_t rxccr = {0, 0, BUFFERSIZE, rxbuf};

static void send_midi_blocking(uint8_t dt)
{
    void idlecall(void);
    static SSTREAMMIDI sStrMidi = {0,0,0,0};
	SUSBMIDI sUsbMidi = {.ulData=StreamToPacket(&sStrMidi, dt)};

    if (sUsbMidi.ulData) {
        uint8_t packet[4] = {sUsbMidi.sPacket.CN_CIN,
                             sUsbMidi.sPacket.MIDI_0,
                             sUsbMidi.sPacket.MIDI_1,
                             sUsbMidi.sPacket.MIDI_2};
        while (tud_midi_packet_write(packet) == false) {
            idlecall();
        }
    }

    return;
}

static void send_char2(uint8_t dt1st, uint8_t dt2nd)
{
	const uint8_t sts = (POLYKEYPRESS << 4) | 12 | (dt1st & 0x80 ? 1 : 0) | (dt2nd & 0x80 ? 2 : 0);
	const uint8_t dt1 = dt1st & 0x7f;
	const uint8_t dt2 = dt2nd & 0x7f;

	send_midi_blocking(sts);
	send_midi_blocking(dt1);
	send_midi_blocking(dt2);

	return;
}

static void send_char1(uint8_t dt)
{
	const uint8_t sts = (POLYKEYPRESS << 4) | 11;
	const uint8_t dt1 = dt & 0x7f;
	const uint8_t dt2 = dt >> 7;

	send_midi_blocking(sts);
	send_midi_blocking(dt1);
	send_midi_blocking(dt2);

	return;
}

void DebugMonitor_putsUsbMidi(uint8_t *str, uint8_t n)
{
	while (n > 1)
	{
		uint8_t dt1 = *str++;
		uint8_t dt2 = *str++;

		send_char2(dt1, dt2);
		n -= 2;
	}
	if (n > 0)
	{
		send_char1(*str);
	}

	return;
}

void DebugMonitor_entryUsbMidi(uint8_t sts, uint8_t dt1, uint8_t dt2)
{
	if ((sts >> 4) == POLYKEYPRESS)
	{
		if ((sts & 0xf) == 11)
		{
			const uint8_t dt = dt1 | (dt2 << 7);

//			DebugMonitor_entry(eDebugMonitorInterface_UsbMidi, dt, 1);
            circure_put(&rxccr, dt);
		}
		else if ((sts & 0xf) > 11)
		{
            const uint8_t dt1h = sts & 1 ? 0x80 : 0;
            const uint8_t dt2h = sts & 2 ? 0x80 : 0;
            const uint8_t dt1st = dt1h | dt1;
            const uint8_t dt2nd = dt2h | dt2;

//			DebugMonitor_entry(eDebugMonitorInterface_UsbMidi, dt1, 1);
//			DebugMonitor_entry(eDebugMonitorInterface_UsbMidi, dt2, 1);
            circure_put(&rxccr, dt1st);
            circure_put(&rxccr, dt2nd);
		}
	}

	return;
}

void DebugMonitor_idleUsbMidi(void)
{
    static bool bActive = false;

    if (!bActive) {
        int dt = circure_get(&rxccr);

        if (dt >= 0) {
            bActive = true;
            DebugMonitor_entry(eDebugMonitorInterface_UsbMidi, dt, 1);
            bActive = false;
        }
    }

    return;
}
