/*
F2803x_DevInit.c
   Created on: 2017
       Author: Farisey
*/
#include "DSP280x_Device.h"
//#include "DSP2803x_GlobalPrototypes.h"	 // Global Prototyps
#pragma CODE_SECTION(InitFlash, "ramfuncs");
#define ADC_usDELAY  1000L

//---------------------------------------------------------------------------
// InitSysCtrl:
//---------------------------------------------------------------------------
void DeviceInit(void){
    	DisableDog();							// �������� ����������� �������.
        InitPll(DSP28_PLLCR,DSP28_CLKINDIV); 	// ������������ PLL �� ��������� DSP28_PLLCR/DSP28_CLKINDIV ���. �. DSP2803x_Examples.h
        InitPeripheralClocks();					// ������� �������� �������� ���������� �������
        InitGpio();								// ������� ������������ ��.
    	DINT;									// �������� INTM ��� �������� �����������
	InitPieCtrl();
	IER = 0x0000; 								// ��������� ������ ����������
	IFR = 0x0000; 								// ���������  ����� �����������
	InitPieVectTable();							// �����������  ������� ������� ���������� �� �������� ����������
//    Test();                                 // ������ �������� �� ��� �����������, �� ��������� ��������!
}

/*
 * 												ServiceDog: ��������� ����������� �������.
 */
void ServiceDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}

/*
 *												DisableDog: �������� ����������� �������.
 */
void DisableDog(void)
{
    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;
    EDIS;
}

/*
 *												InitPll:
 */
void InitPll(Uint16 val, Uint16 divsel)
{
   volatile Uint16 iVol;
   if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)		// �������� ��������� ������
   {
      EALLOW;
      SysCtrlRegs.PLLSTS.bit.MCLKCLR = 1;		// ���� �������� ������� ����� PLL ������ � ��������� �����.
      EDIS;
      asm("        ESTOP0");					// Uncomment for debugging purposes
   }
   if (SysCtrlRegs.PLLSTS.bit.CLKINDIV != 0)	// �������� DIVSEL>>DSP28_DIVSEL � "0"
   {
       EALLOW;
       SysCtrlRegs.PLLSTS.bit.CLKINDIV = 0;
       EDIS;
   }
   if (SysCtrlRegs.PLLCR.bit.DIV != val)		// ����� �������� �������� �������
   {
      EALLOW;
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;		// ��������� ����� �� ������ ������ PLLSTS.  (1 - ��������, 0 - ���� ������� �������� ���������)
      SysCtrlRegs.PLLCR.bit.DIV = val;			// �������� ��������� �� ��������� val (��������) PLL.
      EDIS;
      DisableDog();								// �������� ����������� �������.
   while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)	// Գ������ PLL >   PLLSTS = PLLLOCKS = 1. PLL ������� ��������� ����.
      {
          // ServiceDog();						// ��������� ����������� �������.
      }
      EALLOW;
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
      SysCtrlRegs.PLLSTS.bit.CLKINDIV = divsel;
    }
}

//---------------------------------------------------------------------------
//												������� �� ����������
//---------------------------------------------------------------------------
/*
 * 												�������� ��������� �� ��.
 */

/*
 * 												InitPeripheralClocks:
 * 												��������� �� ���� ������� ������� �������
 */
void InitPeripheralClocks(void)
{
   EALLOW;
   SysCtrlRegs.HISPCP.all = 0x0001;				// ����������� High-Speed ���������
   SysCtrlRegs.LOSPCP.all = 0x0002;				// ����������� Low-Speed ���������
   	   	   	   	   	   	   	   	   	   	   	   	// 000 Low speed clock = SYSCLKOUT/1	0
   	   											// 001 Low speed clock= SYSCLKOUT/2		1
   	   											// 010 Low speed clock= SYSCLKOUT/4 	2 ->>> 25���
   	   											// 011 Low speed clock= SYSCLKOUT/6		3
   	   											// 100 Low speed clock= SYSCLKOUT/8		4
   	   											// 101 Low speed clock= SYSCLKOUT/10	5
   	   											// 110 Low speed clock= SYSCLKOUT/12	6
   	   											// 111 Low speed clock= SYSCLKOUT/14	7
	SysCtrlRegs.XCLK.bit.XCLKOUTDIV=0x0002;		// ĳ�����  XCLKOUT = 1/� SYSCLKOUT
   												// 00 XCLKOUT = SYSCLKOUT/4				0
   												// 01 XCLKOUT = SYSCLKOUT/2				1
   												// 10 XCLKOUT = SYSCLKOUT				2
   												// 11 XCLKOUT = Off             		3
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0; 		// ��� clock
/*
 * 												Peripheral clock
 */
	//------------------------------------
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;      	// ADC
	//------------------------------------
	SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;    	// eCAP1
	SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 0;  	// eCAP2
	SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = 0;  	// eCAP3
	SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK = 0;  	// eCAP4
	//------------------------------------
	SysCtrlRegs.PCLKCR0.bit.ECANAENCLK = 0;    	// eCAN-A
	SysCtrlRegs.PCLKCR0.bit.ECANBENCLK = 0;		// eCAN-B
	//------------------------------------
	SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 0;    	// eQEP1
	SysCtrlRegs.PCLKCR1.bit.EQEP2ENCLK = 0;  	// eQEP2
	//------------------------------------
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 0;    	// ePWM1
	SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 0;    	// ePWM2
	SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;    	// ePWM3
	SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 0;    	// ePWM4
	SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 0;    	// ePWM5
	SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 0;    	// ePWM6
	//------------------------------------
	SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 0;     	// I2C
	//------------------------------------
	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 0;     	// SCI-A
	SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 0;		// SCI-B
	//------------------------------------
	SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 0;     	// SPI-A
	SysCtrlRegs.PCLKCR0.bit.SPIBENCLK = 0;     	// SPI-B
	SysCtrlRegs.PCLKCR0.bit.SPICENCLK = 0;   	// SPI-C
	SysCtrlRegs.PCLKCR0.bit.SPIDENCLK = 0;   	// SPI-D
	//------------------------------------
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;     	// ��������� ��������� ePWM. ��� ������� PCLKCR1 == EQEP1ENCLK = 1, ePWM ���� ���������.
	//------------------------------------
	EDIS;
}

//---------------------------------------------------------------------------
// 												������� ���������
//---------------------------------------------------------------------------
void InitPieCtrl(void)
{
 	DINT;										// �������� INTM ��� �������� �����������
    //------------------------------------
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;			// �������� ����������
    //------------------------------------
	PieCtrlRegs.PIEIER1.all = 0;
	PieCtrlRegs.PIEIER2.all = 0;
	PieCtrlRegs.PIEIER3.all = 0;
	PieCtrlRegs.PIEIER4.all = 0;
	PieCtrlRegs.PIEIER5.all = 0;
	PieCtrlRegs.PIEIER6.all = 0;
	PieCtrlRegs.PIEIER7.all = 0;
	PieCtrlRegs.PIEIER8.all = 0;
	PieCtrlRegs.PIEIER9.all = 0;
	PieCtrlRegs.PIEIER10.all = 0;
	PieCtrlRegs.PIEIER11.all = 0;
	PieCtrlRegs.PIEIER12.all = 0;
	//------------------------------------
	PieCtrlRegs.PIEIFR1.all = 0;
	PieCtrlRegs.PIEIFR2.all = 0;
	PieCtrlRegs.PIEIFR3.all = 0;
	PieCtrlRegs.PIEIFR4.all = 0;
	PieCtrlRegs.PIEIFR5.all = 0;
	PieCtrlRegs.PIEIFR6.all = 0;
	PieCtrlRegs.PIEIFR7.all = 0;
	PieCtrlRegs.PIEIFR8.all = 0;
	PieCtrlRegs.PIEIFR9.all = 0;
	PieCtrlRegs.PIEIFR10.all = 0;
	PieCtrlRegs.PIEIFR11.all = 0;
	PieCtrlRegs.PIEIFR12.all = 0;
}

void InitPieVectTable(void)
{
	int16	i;
	Uint32 *Source = (void *) &ISR_ILLEGAL;
	Uint32 *Dest = (void *) &PieVectTable;

	EALLOW;
	for(i=0; i < 128; i++)
		*Dest++ = *Source;
	EDIS;
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;					// ����� ������� ����������
}
interrupt void ISR_ILLEGAL(void)
{
  asm("          ESTOP0");
  for(;;);
}
//---------------------------------------------------------------------------
// 												������� �����
//---------------------------------------------------------------------------
#ifdef 	FLASH
void InitFlash(void)							// !!! ����� !!! ���������� ����� � ���
{
   EALLOW;
   FlashRegs.FOPT.bit.ENPIPE = 1;				// Enable Flash Pipeline mode
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 3;		// ��������� ����������
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 3;
   FlashRegs.FOTPWAIT.bit.OTPWAIT = 5;
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
   EDIS;
   asm(" RPT #7 || NOP");
}
#endif
//---------------------------------------------------------------------------
//                                              ����� ������
//---------------------------------------------------------------------------
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    {
       *DestAddr++ = *SourceAddr++;
    }
    return;
}

//---------------------------------------------------------------------------
// ������� ϲ� ���������
//---------------------------------------------------------------------------
void InitGpio(void){
	EALLOW;											// ��������� ������ �� ������
//--------------------------------------------------------------------------------------
//  GPIO-00 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    			// Disable pull-up on GPIO0
//	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;				// 0=GPIO,  1=EPWM1A,  2=��������������,  3=��������������
//	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO0 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-01 - ������� �����  = --!!���������!!--
//  GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    			// Disable pull-up on GPIO0
//	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;				// 0=GPIO,  1=EPWM1B,  2=��������������,  3=COMP1OUT
//	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO1 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-02 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    			// Disable pull-up on GPIO0
//	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;				// 0=GPIO,  1=EPWM2A,  2=��������������,  3=��������������
//	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO2 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-03 - ������� �����  = -- MOSFET 1--
//	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    			// Disable pull-up on GPIO0
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;				// 0=GPIO,  1=EPWM2B,  2=SPISOMI-A,  3=COMP2OUT
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO3 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-04 - ������� �����  = --��� A --
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;              // Disable pull-up on GPIO0
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;				// 0=GPIO,  1=EPWM3A,  2=��������������,  3=��������������
//	GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO4 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-05 - ������� �����  = --��� B--
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;              // Disable pull-up on GPIO0
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;				// 0=GPIO,  1=EPWM3B,  2=SPISIMO-A,  3=ECAP1
//	GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO5 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-06 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    			// Disable pull-up on GPIO6
//	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;				// 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
//	GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO6 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-07 - ������� �����  = -- MOSFET 2--
//	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;              // Disable pull-up on GPIO7
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;				// 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=��������������
	GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO7 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-08 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;				// 0=GPIO,  1=EPWM5A,  2=��������������,  3=ADCSOC-A
//	GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO8 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-09 - ������� �����  = --MOSFET 3--
//    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;              // Disable pull-up on GPIO7
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;				// 0=GPIO,  1=EPWM5B,  2=LINTX-A,  3=��������������
	GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO9 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-10 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;			// 0=GPIO,  1=EPWM6A,  2=��������������,  3=ADCSOC-B
//	GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO10 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-11 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;			// 0=GPIO,  1=EPWM6B,  2=LINRX-A,  3=��������������
//	GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;			//�������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO11 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-12 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    			// pull-up on GPIO
//	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;			// 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
//	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO12 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-13 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    			// pull-up on GPIO
//	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 2;			// 0=GPIO,  1=TZ2,  2=��������������,  3=SPISOMI-B
//	GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; 			// Asynch qual for GPIO13 (CANRXB)
//	GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO13 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-14 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    			// Disable pull-up on GPIO14
//	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2;			// 0=GPIO,  1=TZ3,  2=LINTX-A,  3=SPICLK-B
//	GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO14 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-15 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  			// ����������� GPIO(SCIRXDB)
//	GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    			// Disable pull-up on GPIO0
//	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;			// 0=GPIO,  1=TZ1,  2=LINRX-A,  3=SPISTE-B
//	GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO15 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//  GPIO-16 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;			// 0=GPIO,  1=SPISIMO-A,  2=��������������,  3=TZ2
//	GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO16 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-17 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;			// 0=GPIO,  1=SPISOMI-A,  2=��������������,  3=TZ3
//	GpioCtrlRegs.GPADIR.bit.GPIO17 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO17 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-18 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;			// 0=GPIO,  1=SPICLK-A,  2=LINTX-A,  3=XCLKOUT
//	GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO18 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-19 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;			// 0=GPIO,  1=SPISTE-A,  2=LINRX-A,  3=ECAP1
//	GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO19 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-20 - ������� �����  = --��������� ���� 1--
//    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;           // Disable pull-up on GPIO22
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;			// 0=GPIO,  1=EQEPA-1,  2=��������������,  3=COMP1OUT
	GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO20 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-21 - ������� �����  = --!!���������!!--
//    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;           // Disable pull-up on GPIO21
//	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;			// 0=GPIO,  1=EQEPB-1,  2=��������������,  3=COMP2OUT
//	GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO21 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-22 - ������� �����  = --��������� ���� 2--
//  GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;             // Disable pull-up on GPIO22
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;			// 0=GPIO,  1=EQEPS-1,  2=��������������,  3=LINTX-A
	GpioCtrlRegs.GPADIR.bit.GPIO22 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO22 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-23 - ������� �����  = --��������� ���� 3--
//  GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;             // Disable pull-up on GPIO23
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;			// 0=GPIO,  1=EQEPI-1,  2=��������������,  3=LINRX-A
	GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO23 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-24 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;			// 0=GPIO,  1=ECAP1,  2=��������������,  3=SPISIMO-B
//	GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO24 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-25 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;			// 0=GPIO,  1=��������������,  2=��������������,  3=SPISOMI-B
//	GpioCtrlRegs.GPADIR.bit.GPIO25 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO25 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-26 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;			// 0=GPIO,  1=��������������,  2=��������������,  3=SPICLK-B
//	GpioCtrlRegs.GPADIR.bit.GPIO26 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO26 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-27 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 3;			// 0=GPIO,  1=��������������,  2=��������������,  3=SPISTE-B
//	GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO27 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-28 - ������� �����  = SCI-RX A
//	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  			// ����������� GPIO(SCIRXDB)
//	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    			// Disable pull-up on GPIO28
//	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;			// 0=GPIO,  1=SCIRX-A,  2=I2CSDA-A,  3=TZ2
//	GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO28 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-29 - ������� �����  = SCI-TX A
//	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    			// Disable pull-up on GPIO29
//	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;			// 0=GPIO,  1=SCITXD-A,  2=I2CSCL-A,  3=TZ3
//	GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO29 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-30 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;			// 0=GPIO,  1=CANRX-A,  2=��������������,  3=��������������
//	GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO30 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-31 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;			// 0=GPIO,  1=CANTX-A,  2=��������������,  3=��������������
//	GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPASET.bit.GPIO31 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//  GPIO-32 - ������� �����  = --������ �����--
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;			// 0=GPIO,  1=I2CSDA-A,  2=SYNCI,  3=ADCSOCA
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPBSET.bit.GPIO32 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-33 - ������� �����  = --������ ����--
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;			// 0=GPIO,  1=I2CSCL-A,  2=SYNCO,  3=ADCSOCB
	GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPBSET.bit.GPIO33 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-34 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;			// 0=GPIO,  1=��������������,  2=��������������,  3=��������������
//	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPBSET.bit.GPIO34 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// GPIO 35-38 ���������������� �� JTAG
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//  GPIO-39 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;			// 0=GPIO,  1=��������������,  2=��������������,  3=��������������
//	GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPBSET.bit.GPIO39 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-40 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1;			// 0=GPIO,  1=EPWM7A,  2=��������������,  3=��������������
//	GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPBSET.bit.GPIO40 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-41 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1;			// 0=GPIO,  1=EPWM7B,  2=��������������,  3=��������������
//
//	GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;				// 1=���.,  0=��.
//	GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPBSET.bit.GPIO41 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-42 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1;			// 0=GPIO,  1=��������������,  2=��������������,  3=COMP1OUT
//	GpioCtrlRegs.GPBDIR.bit.GPIO42 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPBSET.bit.GPIO42 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-43 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;			// 0=GPIO,  1=��������������,  2=��������������,  3=COMP2OUT
//	GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPBSET.bit.GPIO43 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//  GPIO-44 - ������� �����  = --!!���������!!--
//	GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;			// 0=GPIO,  1=��������������,  2=��������������,  3=��������������
//	GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;				// 1=���.,  0=��.
//	GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;			// �������������� ���� ������� --> ������� �����
//	GpioDataRegs.GPBSET.bit.GPIO44 = 1;				// �������������� ���� ������� --> ������� �����
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	EDIS;											// ���������� ������ �� �������.
}


