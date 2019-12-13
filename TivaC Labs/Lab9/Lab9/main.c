#include <stdint.h>
#include <stdbool.h>
#include <math.h> //code uses sinf() function which is in this header file
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h" //support for floating point unit
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

//Just in case the M_PI is not already defined this will do it for us
#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

#define SERIES_LENGTH 1000 //depth of our data buffer
float gSeriesData[SERIES_LENGTH]; //an array of floats SERIES_LENGTH long (100)

int32_t i32DataCount = 0; //counter for our computation loop

int main(void)
{
    float fRadians, fRadians1, fRadians2; //need a variable of type float to calculate sine
    ROM_FPULazyStackingEnable();//turn on lazy stacking
    ROM_FPUEnable();//Turn on the FPU

    //Set the system clock to 50MHz
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    fRadians1 = (2*M_PI*50)/SERIES_LENGTH;
    fRadians2 = (2*M_PI*200)/SERIES_LENGTH;

    //calculate the sine value for each of the 100 values of the angle and place them in our data array
    while(i32DataCount < SERIES_LENGTH)
    {
        gSeriesData[i32DataCount] = 1.5+(1.0*sinf(fRadians1 * i32DataCount)+0.5*cosf(fRadians2 * i32DataCount));
        i32DataCount++;
    }

    //endless loop
    while(1)
    {
    }
}
