/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    09-September-2013
  * @brief   RHID demo main file
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"

/* Private variables ---------------------------------------------------------*/
__IO uint8_t PrevXferComplete = 1;

/* Private functions ---------------------------------------------------------*/

void Delay(volatile uint32_t nCount) {
	for (; nCount != 0; nCount--);
}

/*******************************************************************************
* Function Name  : main.
* Description    : main routine.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
int main(void)
{
  Set_System();

  USB_Interrupts_Config();

  Set_USBClock();

  USB_Init();


  while (1)
  {

    if (bDeviceState == CONFIGURED)
    {
      if (PrevXferComplete)
      {
        RHIDCheckState();
      }
    }
  }
}

#ifdef  USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
