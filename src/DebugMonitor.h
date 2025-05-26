/*
 * DebugMonitor.h
 *
 *  Created on: 2024/08/20
 *      Author: M.Akino
 */

#ifndef DEBUGMONITOR_H_
#define DEBUGMONITOR_H_

#include <stdint.h>

typedef enum {
	eDebugMonitorInterface_Stdio = 0,
	eDebugMonitorInterface_UsbMidi,

	eDebugMonitorInterfaceNumOf,
} eDebugMonitorInterface;

void dmprintf(eDebugMonitorInterface d, uint8_t *fmt, ...);	// with dflush()
void dmputc(eDebugMonitorInterface d, uint8_t c);			// without dflush()
void dmputs(eDebugMonitorInterface d, uint8_t *str);			// with dflush()
void dmflush(eDebugMonitorInterface d);

void DebugMonitor_entry(eDebugMonitorInterface d, uint8_t c, uint8_t echo);

#include "DebugMonitorStdio.h"
#include "DebugMonitorUsbMidi.h"

#define TIMINGLOGFNCCLR (0)
#define TIMINGLOGFNCSET (1)
#define TIMINGLOGFNCTGL (2)
#define TIMINGLOGFNCNUM (3)
extern uint64_t TimingLogGetCount(uint32_t *p);
extern void TimingLogClear(void);
extern void TimingLogWrite(uint8_t width, uint8_t func, uint8_t num, uint8_t dlt, uint32_t *p);
#define TIMINGLOGCLR()        TimingLogClear()

#endif /* DEBUGMONITOR_H_ */
