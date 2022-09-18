#include"../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include"DCM_interface.h"
#include"DCM_private.h"
#include"DCM_config.h"

void DCM_voidRotateCW(void)
{
	DIO_voidSetPinValue(DCM_TRANSISTOR2_PORT,DCM_TRANSISTOR2_PIN, LOW);
	DIO_voidSetPinValue(DCM_TRANSISTOR1_PORT,DCM_TRANSISTOR1_PIN, HIGH);
}

void DCM_voidRotateCCW(void)
{
	DIO_voidSetPinValue(DCM_TRANSISTOR1_PORT,DCM_TRANSISTOR1_PIN, LOW);
	DIO_voidSetPinValue(DCM_TRANSISTOR2_PORT,DCM_TRANSISTOR2_PIN, HIGH);
}

void DCM_voidInit(void)
{
	DIO_voidSetPinDirection(DCM_TRANSISTOR1_PORT,DCM_TRANSISTOR1_PIN, OUTPUT);
	DIO_voidSetPinDirection(DCM_TRANSISTOR2_PORT,DCM_TRANSISTOR2_PIN, OUTPUT);
}

void DCM_voidStop(void)
{
	DIO_voidSetPinValue(DCM_TRANSISTOR1_PORT,DCM_TRANSISTOR1_PIN, LOW);
	DIO_voidSetPinValue(DCM_TRANSISTOR2_PORT,DCM_TRANSISTOR2_PIN, LOW);
}




