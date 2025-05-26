/*
 * DebugMonitorStdio.h
 *
 *  Created on: 2025/05/19
 *      Author: M.Akino
 */

#ifndef DEBUGMONITORSTDIO_H_
#define DEBUGMONITORSTDIO_H_

#include <stdint.h>

void DebugMonitor_putsStdio(uint8_t *str, uint8_t n);
int DebugMonitor_getcStdio(void);
void DebugMonitor_entryStdio(uint8_t c);
void DebugMonitor_idleStdio(void);

#endif /* DEBUGMONITORSTDIO_H_ */
