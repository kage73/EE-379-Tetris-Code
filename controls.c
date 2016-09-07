#include "controls.h"
#include "GLCD.h"
#include "LPC17xx.h"

uint8_t joystickVal;

int controls_isJoystickLeftPressed() {
	joystickVal = (LPC_GPIO1->FIOPIN >> 25) & 0x1F;  
	if (~joystickVal & 0x04){
		return 1;
	}
	return 0;
}

int controls_isJoystickRightPressed()  {
	joystickVal = (LPC_GPIO1->FIOPIN >> 25) & 0x1F;  
	if (~joystickVal & 0x08){
		return 1;
	}
	return 0;
}

int controls_isJoystickUpPressed()  {
	joystickVal = (LPC_GPIO1->FIOPIN >> 25) & 0x1F;  
	if (~joystickVal & 0x10){
		return 1;
	}
	return 0;
}

int controls_isJoystickDownPressed()  {
	joystickVal = (LPC_GPIO1->FIOPIN >> 25) & 0x1F;  
	if (~joystickVal & 0x02){
		return 1;
	}
	return 0;
}

int controls_isResetPressed()  {
	return 0;
}

