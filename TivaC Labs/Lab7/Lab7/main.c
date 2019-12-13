#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/adc.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"

void UART_OutUDec(uint32_t);
void UART_OutChar(char data);

uint32_t ui32ADC0Value[1];

//volatile so that each variable cannot be optimized out by the compiler
volatile uint32_t ui32TempAvg;
volatile uint32_t ui32TempValueC;
volatile uint32_t ui32TempValueF;

int main(void)
{
    //set up the system clock
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    //enable UART0 and GPIOA peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //configure pins PA0 as reciever and PA1 as the transmitter using GPIOPinConfig
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //initialize the GPIO peripheral and pin for the LEDS
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    //Enable ADC0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    //hardware average of 32
    ADCHardwareOversampleConfigure(ADC0_BASE, 32);


    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);

    //ADC will run at default rate of 1Msps
    //Configure ADC sequencer 3
    //want the processor to trigger the sequence and use highest priority
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //Enabling UART interrupts
    IntMasterEnable();
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    //Enabling ADC interrupts
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntEnable(ADC0_BASE, 3);

    while (1)
    {
    }
}

void UARTIntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts

    //Turn on Blue LED
    if(UARTCharGet(UART0_BASE) == 'B')
    {
        UARTCharPut(UART0_BASE, 'B');
        UARTCharPut(UART0_BASE, 'l');
        UARTCharPut(UART0_BASE, 'u');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'n');
        UARTCharPut(UART0_BASE, '\n');
        UARTCharPut(UART0_BASE, '\r');

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //blink LED
        SysCtlDelay(10000000);
    }
    //Turn off Blue LED
    if(UARTCharGet(UART0_BASE) == 'b')
    {
        UARTCharPut(UART0_BASE, 'B');
        UARTCharPut(UART0_BASE, 'l');
        UARTCharPut(UART0_BASE, 'u');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'f');
        UARTCharPut(UART0_BASE, 'f');
        UARTCharPut(UART0_BASE, '\n');
        UARTCharPut(UART0_BASE, '\r');

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); //blink LED
        SysCtlDelay(10000000);
    }
    //Turn on Red LED
    if(UARTCharGet(UART0_BASE) == 'R')
    {
        UARTCharPut(UART0_BASE, 'R');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, 'd');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'n');
        UARTCharPut(UART0_BASE, '\n');
        UARTCharPut(UART0_BASE, '\r');

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 2); //blink LED
        SysCtlDelay(10000000);
    }
    //Turn off Red LED
    if(UARTCharGet(UART0_BASE) == 'r')
    {
        UARTCharPut(UART0_BASE, 'R');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, 'd');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'f');
        UARTCharPut(UART0_BASE, 'f');
        UARTCharPut(UART0_BASE, '\n');
        UARTCharPut(UART0_BASE, '\r');

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0); //blink LED
        SysCtlDelay(10000000);
    }
    //Turn on Green LED
    if(UARTCharGet(UART0_BASE) == 'G')
    {
        UARTCharPut(UART0_BASE, 'G');
        UARTCharPut(UART0_BASE, 'r');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, 'n');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'n');
        UARTCharPut(UART0_BASE, '\n');
        UARTCharPut(UART0_BASE, '\r');

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 8); //blink LED
        SysCtlDelay(10000000);
    }
    //Turn off Green LED
    if(UARTCharGet(UART0_BASE) == 'g')
    {
        UARTCharPut(UART0_BASE, 'G');
        UARTCharPut(UART0_BASE, 'r');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, 'n');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'f');
        UARTCharPut(UART0_BASE, 'f');
        UARTCharPut(UART0_BASE, '\n');
        UARTCharPut(UART0_BASE, '\r');

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0); //blink LED
        SysCtlDelay(10000000);
    }
    //Display Temp if T is pressed
    if(UARTCharGet(UART0_BASE) == 'T')
    {
        //clear interrupt flags
        ADCIntClear(ADC0_BASE, 3);
        //trigger ADC conversion with software
        ADCProcessorTrigger(ADC0_BASE, 3);

        //wait for conversion
        while (!ADCIntStatus(ADC0_BASE, 3, false))
        {
        }

        //get data from a buffer in memory
        ADCSequenceDataGet(ADC0_BASE, 3, ui32ADC0Value);

        //Calculates temp
        ui32TempValueC = (1475 - ((2475 * ui32ADC0Value[0])) / 4096) / 10;
        ui32TempValueF = ((ui32TempValueC * 9) + 160) / 5;

        UARTCharPut(UART0_BASE, 'T');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, 'm');
        UARTCharPut(UART0_BASE, 'p');
        UARTCharPut(UART0_BASE, 'F');
        UARTCharPut(UART0_BASE, ':');
        UARTCharPut(UART0_BASE, ' ');
        UART_OutUDec(ui32TempValueF);
        UARTCharPut(UART0_BASE, '\n');
        UARTCharPut(UART0_BASE, '\r');
    }
}

void UART_OutUDec(uint32_t n)
{
    if (n >= 10) {
        UART_OutUDec(n / 10);
        n = n % 10;
    }
    UART_OutChar(n + '0');
}

void UART_OutChar(char data)
{
    while ((UART0_FR_R&UART_FR_TXFF) != 0);
    UART0_DR_R = data;
}
