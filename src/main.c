/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h> 
#include <math.h> 
#include "stm32f4xx.h" 
#include "leds.h" 
#include "main.h" 
#include "dac_lowlevel.h" 

extern uint16_t *curDMAData;
extern uint16_t ZomboFileDataStart;
extern uint16_t ZomboFileDataEnd;

void phasewrap(float *phase)
{
    while (*phase > 1.) { *phase -= 1.; }
    while (*phase < 0.) { *phase += 1.; }
}

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f4xx.c file
     */

    /* Enable LEDs so we can toggle them */
    LEDs_Init();

    curDMAData = NULL;
    
    /* Enable DAC */
    DAC_Setup();

    float phase = 0;
    float slowphase = 0;
    float freq = 440.;
    float slowfreq = 0.1;
    int lastval = 0;
    uint16_t *curSample = &ZomboFileDataStart;

    while (1) {
        while (curDMAData == NULL);/* wait for request to fill with data */
        size_t numIters = DAC_DMA_BUF_SIZE;
        while (numIters--) {
            /*
            *curDMAData = (uint16_t)(0xfff 
                    * ((1. + sinf(phase * M_PI * 2.)) * 0.5)
                    * ((1. + sinf(slowphase * M_PI * 2.)) * 0.5));
            phase += freq / DAC_SAMPLE_RATE;
            slowphase += slowfreq / DAC_SAMPLE_RATE;
            phasewrap(&phase);
            phasewrap(&slowphase);
            curDMAData++;
            */
//            *curDMAData = (uint16_t)(0xfff * lastval);
//            lastval = 1 - lastval;
//            curDMAData++;

            *(curDMAData++) = (uint16_t)(*curSample >> 4);
            if (++curSample >= &ZomboFileDataEnd) {
                curSample = &ZomboFileDataStart;
            }
        }
        curDMAData = NULL;
    }
}
