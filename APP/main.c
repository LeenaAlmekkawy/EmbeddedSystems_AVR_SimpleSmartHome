#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"

#include"../MCAL/DIO/DIO_interface.h"
#include"../MCAL/ADC/ADC_interface.h"

#include"../HAL/LCD/LCD_interface.h"
#include"../HAL/KPD/KPD_interface.h"

#include"../HAL/DCM/DCM_interface.h"
#define  F_CPU  8000000UL
#include <util/delay.h>

#define STAR              12
#define WINDOW            13
#define VERY_LAW_TEMP     20
#define LAW_TEMP          50
#define MEDIUM_TEMP       110
#define HIGH_TEMP         150
#define SYS_OFF           0
#define SYS_ON            1
#define NUM_OF_TRIALS     3
#define NUM_OF_DIGITS     4
#define NO_CORRECT_PASS   0
#define CORRECT_PASS      1
#define NUM_OF_CHANCES    2



u16 Global_DoorPassword=1234;
u8 Global_u8State=0;


void App_ChangePassword(u32 Copy_u32NewPassword);
void main(void)
{
    // Set PA0 & PA1 to be analog input
    DIO_voidSetPinDirection (PORTA, PIN0, INPUT);
    DIO_voidSetPinValue     (PORTA, PIN0, LOW);

    DIO_voidSetPinDirection (PORTD, PIN0, OUTPUT);


    DIO_voidSetPinDirection (PORTA, PIN1, INPUT);
    DIO_voidSetPinValue     (PORTA, PIN1, LOW);

    DIO_voidSetPinDirection (PORTB, PIN3,  OUTPUT);
    DIO_voidSetPinDirection (PORTB, PIN4,  OUTPUT);
    DIO_voidSetPinDirection (PORTB, PIN5,  OUTPUT);
    DIO_voidSetPinDirection (PORTB, PIN6,  OUTPUT);
    DIO_voidSetPinDirection (PORTB, PIN7,  OUTPUT);

    KPD_voidInit();
    LCD_voidInit();
    DCM_voidInit();
    ADC_voidInit();
    u8 Local_u8PressedKey=0xAA;



    while(1)
    {
        Local_u8PressedKey=0xAA;


        do
        {
            if(Global_u8State==SYS_ON)
            {
                //Reading of Temperature sensor
                u8 digital=ADC_voidStartConversionSynchronous(1);
                u16  mvolt=(u16)(((u32)digital*5000UL)/256UL);
                u8 temp=mvolt/10;

                LCD_voidGoToXY(1,0);

                LCD_voidSendString("Temperature:");

                LCD_voidWriteNumber(temp, 1,13);
                LCD_voidGoToXY(1,15);
                LCD_voidSendString("c");

                //Reading of LDR sensor
                digital=ADC_voidStartConversionSynchronous(0);
                LCD_voidGoToXY(0,0);

                LCD_voidSendString("Light: ");


                LCD_voidGoToXY(0,7);
                if(digital<=VERY_LAW_TEMP)
                {
                    LCD_voidSendString("Very Law");
                    DIO_voidSetPinValue     (PORTB, PIN3, HIGH);
                    DIO_voidSetPinValue     (PORTB, PIN4, HIGH);
                    DIO_voidSetPinValue     (PORTB, PIN5, HIGH);
                    DIO_voidSetPinValue     (PORTB, PIN6, HIGH);
                    DIO_voidSetPinValue     (PORTB, PIN7, HIGH);
                }
                else if(digital<=LAW_TEMP && digital>VERY_LAW_TEMP)
                {
                    LCD_voidSendString("Law      ");
                    DIO_voidSetPinValue     (PORTB, PIN3, LOW);
                    DIO_voidSetPinValue     (PORTB, PIN4, HIGH);
                    DIO_voidSetPinValue     (PORTB, PIN5, HIGH);
                    DIO_voidSetPinValue     (PORTB, PIN6, HIGH);
                    DIO_voidSetPinValue     (PORTB, PIN7, HIGH);

                }
                else if(digital<=MEDIUM_TEMP && digital>LAW_TEMP)
                {
                    LCD_voidSendString("Medium     ");
                    DIO_voidSetPinValue     (PORTB, PIN3, LOW);
                    DIO_voidSetPinValue     (PORTB, PIN4, LOW);
                    DIO_voidSetPinValue     (PORTB, PIN5, HIGH);
                    DIO_voidSetPinValue     (PORTB, PIN6, HIGH);
                    DIO_voidSetPinValue     (PORTB, PIN7, HIGH);

                }
                else if(digital<=HIGH_TEMP && digital>MEDIUM_TEMP)
                {
                    LCD_voidSendString("High      ");
                    DIO_voidSetPinValue     (PORTB, PIN3, LOW);
                    DIO_voidSetPinValue     (PORTB, PIN4, LOW);
                    DIO_voidSetPinValue     (PORTB, PIN5, LOW);
                    DIO_voidSetPinValue     (PORTB, PIN6, HIGH);
                    DIO_voidSetPinValue     (PORTB, PIN7, HIGH);

                }
                else if(digital>HIGH_TEMP)
                {
                    LCD_voidSendString("Very High");
                    DIO_voidSetPinValue     (PORTB, PIN3, LOW);
                    DIO_voidSetPinValue     (PORTB, PIN4, LOW);
                    DIO_voidSetPinValue     (PORTB, PIN5, LOW);
                    DIO_voidSetPinValue     (PORTB, PIN6, LOW);
                    DIO_voidSetPinValue     (PORTB, PIN7, HIGH);

                }




            }

            Local_u8PressedKey=KPB_u8GetPressedKey();


        }
        while(Local_u8PressedKey==0xAA);

        //if The user pressed the star button
        if(Local_u8PressedKey==STAR && Global_u8State==SYS_OFF )
        {
            u8 Local_u8NumofTimes;
            u8 Local_u8CorrectPass=0;
            for(Local_u8NumofTimes=0; Local_u8NumofTimes<NUM_OF_TRIALS && Local_u8CorrectPass==NO_CORRECT_PASS; Local_u8NumofTimes++)
            {
                LCD_voidClear();
                LCD_voidGoToXY(0,0);
                LCD_voidSendString("EnterPass(4Nums)");
                u32 Local_u8TempPass=0;


                for(u8 Local_u8Counter=0; Local_u8Counter<NUM_OF_DIGITS;  Local_u8Counter++ )
                {
                    Local_u8TempPass*=10;
                    u8 Local_u8digit=0;

                    while(1)
                    {
                        Local_u8PressedKey=0xAA;
                        do
                        {
                            Local_u8PressedKey=KPB_u8GetPressedKey();
                        }
                        while(Local_u8PressedKey==0xAA);

                        Local_u8digit=Local_u8PressedKey;
                        LCD_voidGoToXY(1,Local_u8Counter);
                        LCD_voidSendString("*");



                        break;

                    }

                    Local_u8TempPass+=Local_u8digit;
                    LCD_voidGoToXY(1,Local_u8Counter);
                    LCD_voidSendString("*");

                }


                if(Local_u8TempPass==Global_DoorPassword)
                {
                    //Correct password
                    Local_u8CorrectPass=CORRECT_PASS;
                }
                else if(Local_u8NumofTimes<NUM_OF_CHANCES)
                {
                    //Wrong password
                    LCD_voidClear();
                    LCD_voidGoToXY(0,0);
                    LCD_voidSendString("Wrong pass,again");
                    _delay_ms(2000);

                }
                LCD_voidClear();
            }

            if(Local_u8CorrectPass==CORRECT_PASS)
            {
                Global_u8State=SYS_ON;

                LCD_voidClear();
                LCD_voidGoToXY(0,0);
                LCD_voidSendString("Correct pass ");
                _delay_ms(2000);
                LCD_voidClear();
                LCD_voidGoToXY(0,2);
                LCD_voidSendString("WELCOME :)");
                DCM_voidRotateCW();
                _delay_ms(2000);
                DCM_voidStop();
                _delay_ms(3000);
                DCM_voidRotateCCW();
                _delay_ms(2000);
                DCM_voidStop();
                LCD_voidClear();
            }
            else  if(Local_u8CorrectPass==NO_CORRECT_PASS)
            {
                //The user entered the password three times wrong
                LCD_voidClear();
                LCD_voidGoToXY(0,3);
                LCD_voidSendString("Warning!!");
                LCD_voidGoToXY(1,0);
                LCD_voidSendString("Unknown Person!!");
                while (1)
                {
                    DIO_voidSetPinValue     (PORTD, PIN0, HIGH);
                    _delay_ms(1000);
                    DIO_voidSetPinValue     (PORTD, PIN0, LOW);
                    _delay_ms(1000);
                }
            }


        }

        //The user want to close the system
        else if(Local_u8PressedKey==STAR && Global_u8State==SYS_ON)
        {
            Global_u8State=SYS_OFF;
            LCD_voidClear();
        }


        // The user want to change password of the system
        else if(Local_u8PressedKey==WINDOW && Global_u8State==SYS_ON)
        {

            LCD_voidClear();
            LCD_voidGoToXY(0,0);
            LCD_voidSendString("EnterPass:4Nums");
            u32 Local_u8TempPass=0;

            for(  u8 Local_u8Counter=0;  Local_u8Counter<4;  Local_u8Counter++ )
            {
                Local_u8TempPass*=10;
                u8 Local_u8digit=0;

                while(1)
                {
                    Local_u8PressedKey=0xAA;
                    do
                    {
                        Local_u8PressedKey=KPB_u8GetPressedKey();
                    }
                    while(Local_u8PressedKey==0xAA);
                    Local_u8digit=Local_u8PressedKey;

                    LCD_voidGoToXY(1,Local_u8Counter);
                    LCD_voidSendString("*");



                    break;

                }

                Local_u8TempPass+=Local_u8digit;
                LCD_voidGoToXY(1,Local_u8Counter);
                LCD_voidSendString("*");

            }
            if(Local_u8TempPass==Global_DoorPassword)
            {
                LCD_voidClear();
                LCD_voidGoToXY(0,0);
                LCD_voidSendString("Correct pass ");
                _delay_ms(2000);
                LCD_voidClear();
                LCD_voidGoToXY(0,0);
                LCD_voidSendString("Enter New Pass:-");
                u32 Local_u8NewPass=0;

                for(  u8 Local_u8Counter=0;  Local_u8Counter<NUM_OF_DIGITS;  Local_u8Counter++ )
                {
                    Local_u8NewPass*=10;
                    u8 Local_u8digit=0;

                    while(1)
                    {
                        Local_u8PressedKey=0xAA;
                        do
                        {
                            Local_u8PressedKey=KPB_u8GetPressedKey();
                        }
                        while(Local_u8PressedKey==0xAA);
                        Local_u8digit=Local_u8PressedKey;

                        break;

                    }

                    Local_u8NewPass+=Local_u8digit;
                    LCD_voidGoToXY(1,Local_u8Counter);
                    LCD_voidSendString("*");

                }
                App_ChangePassword(Local_u8NewPass);


            }
            else
            {
                LCD_voidClear();
                LCD_voidGoToXY(0,0);
                LCD_voidSendString("Wrong pass ");
                _delay_ms(2000);

            }
            LCD_voidClear();


        }



    }

}
void App_ChangePassword(u32 Copy_u32NewPassword)
{
    Global_DoorPassword=Copy_u32NewPassword;
}








