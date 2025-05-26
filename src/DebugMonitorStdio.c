/*
 * DebugMonitorStdio.c
 *
 *  Created on: 2025/05/19
 *      Author: M.Akino
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "DebugMonitor.h"
#include "circure.h"

#define BUFFERSIZE 128

static uint8_t rxbuf[BUFFERSIZE];
static circure_t rxccr = {0, 0, BUFFERSIZE, rxbuf};

void DebugMonitor_putsStdio(uint8_t *str, uint8_t n)
{
	while (n--) {
		stdio_putchar_raw(*str++);	// blocking ?
	}

	return;
}

int DebugMonitor_getcStdio(void)
{
    int c = stdio_getchar_timeout_us(0);	// not blocking !
	return c != PICO_ERROR_TIMEOUT ? c : -1;
}

void DebugMonitor_entryStdio(uint8_t c)
{
	DebugMonitor_entry(eDebugMonitorInterface_Stdio, c, 1);

	return;
}

void DebugMonitor_idleStdio(void)
{
	static bool bActive = false;
	int c = DebugMonitor_getcStdio();

	if (bActive) {
		if (c >= 0) {
			circure_put(&rxccr, c);
		}
	}
	else {
		int b = circure_get(&rxccr);

		if (b >= 0) {
			if (c >= 0) {
				circure_put(&rxccr, c);
			}
			c = b;
		}
		if (c >= 0) {
			bActive = true;
			DebugMonitor_entryStdio(c);
			bActive = false;
		}
	}

	return;
}
