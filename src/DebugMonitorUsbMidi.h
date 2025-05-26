/*
 * DebugMonitorUsbMidi.h
 *
 *  Created on: 2025/05/21
 *      Author: M.Akino
 */

#ifndef DEBUGMONITORUSBMIDI_H_
#define DEBUGMONITORUSBMIDI_H_

#include <stdint.h>

void DebugMonitor_putsUsbMidi(uint8_t *str, uint8_t n);
void DebugMonitor_entryUsbMidi(uint8_t sts, uint8_t dt1, uint8_t dt2);
void DebugMonitor_idleUsbMidi(void);

#endif /* DEBUGMONITORUSBMIDI_H_ */
