#include "Compilers.h"
#include "Ifx_Types.h"
#include "IfxCpu_Intrinsics.h"
#include "IfxStart.h"
#include "IfxPort_reg.h"

uint32         sys_Init ;


void Test_DD_Ex_BgTask (uint32 PwrEcu_RECU)
{
    volatile uint32 index ;
    volatile Ifx_P *port ;

    __enable ();

    port = (Ifx_P *)&MODULE_P33;
    /* The control should come here and the application code
     *  starts from here.
     */
    while(1)
    {
      for(index = 0 ; index < 50000 ; index ++);
      IfxPort_togglePin(port, 6);
      IfxPort_togglePin(port, 7);
      IfxPort_togglePin(port, 8);
      for(index = 0 ; index < 20000 ; index ++);
    }
}


void Test_DD_Ex_SysInit(uint32 PwrEcu_RECU )
{
    sys_Init = 1U ;
}

