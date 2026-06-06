/*
 * control.h
 *
 *  Created on: Jun 3, 2026
 *      Author: ChienLe
 */

#ifndef CONTROL_H_
#define CONTROL_H_

// control.h
#include <stdint.h>

typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} ControlMode;

void Control_Init(void);
void Control_Process(void);
void Control_SetMode(ControlMode mode);
ControlMode Control_GetMode(void);
void Control_ProcessCommand(char* cmd);

#endif /* CONTROL_H_ */
