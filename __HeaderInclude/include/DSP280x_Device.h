// TI File $Revision: /main/6 $
// Checkin $Date: December 17, 2007   13:13:48 $
//###########################################################################
//
// FILE:   DSP280x_Device.h
//
// TITLE:  DSP280x Device Definitions.
//
//###########################################################################
// $TI Release: DSP280x C/C++ Header Files V1.70 $
// $Release Date: July 27, 2009 $
//###########################################################################

//#ifndef DSP280x_DEVICE_H
//#define DSP280x_DEVICE_H


#ifdef __cplusplus
extern "C" {
#endif


#define   TARGET   1
//---------------------------------------------------------------------------
// User To Select Target Device:

#define   DSP28_28015  0
#define   DSP28_28016  0
#define   DSP28_2809   TARGET
#define   DSP28_2808   0
#define   DSP28_2806   0
#define   DSP28_2802   0
#define   DSP28_2801   0

//---------------------------------------------------------------------------
// Common CPU Definitions:
//

extern cregister volatile unsigned int IFR;
extern cregister volatile unsigned int IER;

#define  EINT   asm(" clrc INTM")
#define  DINT   asm(" setc INTM")
#define  ERTM   asm(" clrc DBGM")
#define  DRTM   asm(" setc DBGM")
#define  EALLOW asm(" EALLOW")
#define  EDIS   asm(" EDIS")
#define  ESTOP0 asm(" ESTOP0")

#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

#define BIT0    0x0001
#define BIT1    0x0002
#define BIT2    0x0004
#define BIT3    0x0008
#define BIT4    0x0010
#define BIT5    0x0020
#define BIT6    0x0040
#define BIT7    0x0080
#define BIT8    0x0100
#define BIT9    0x0200
#define BIT10   0x0400
#define BIT11   0x0800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000

#define BYTE_1   0x0001
#define BYTE_2   0x0002
#define BYTE_3   0x0004
#define BYTE_4   0x0008
#define BYTE_5   0x0010
#define BYTE_6   0x0020
#define BYTE_7   0x0040
#define BYTE_8   0x0080
#define BYTE_9   0x0100
#define BYTE_10  0x0200
#define BYTE_11  0x0400
#define BYTE_12  0x0800
#define BYTE_13  0x1000
#define BYTE_14  0x2000
#define BYTE_15  0x4000

#define    Rate_3000_B_s      300
#define    Rate_6000_B_s      600
#define    Rate_12000_B_s     1200
#define    Rate_24000_B_s     2400
#define    Rate_48000_B_s     4800
#define    Rate_96000_B_s     9600
#define    Rate_19_kB_s      19200
#define    Rate_38_kB_s      38400
#define    Rate_57_kB_s      57600
#define    Rate_115_kB_s     115200
#define    Rate_230_kB_s     230400
#define    Rate_460_kB_s     460800
#define    Rate_512_kB_s     512000
#define    Rate_921_kB_s     921600

#define     Ch_A  0x0001
#define     Ch_B  0x0002
#define     Ch_C  0x0003
#define     Ch_D  0x0004
#define     Ch_E  0x0005
#define     Ch_F  0x0006
#define     Ch_G  0x0007

#define error   0x0
#define done    0x1
#define full    0xFFFFFFFF
#define empty   0x00000000

//---------------------------------------------------------------------------
// For Portability, User Is Recommended To Use Following Data Type Size
// Definitions For 16-bit and 32-Bit Signed/Unsigned Integers:
//

#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef enum
{
  FALSE,
  TRUE
} boolean;
typedef char				int8;		// 8-біта,	[-127, +127]
typedef unsigned char		Uint8;		// 8-біта,	[0, 255]
typedef int                 int16;		// 16-біта, [-32767, 32767]
typedef long                int32;		// 32-біта, [−2 147 483 647, +2 147 483 647]
typedef long long           int64;		// 64-біта, [−9 223 372 036 854 775 807, +9 223 372 036 854 775 807]
typedef unsigned int        Uint16;		// 16-біт,  [0, +4294967295]
typedef unsigned short int  Ushort;     //           0, +65535
typedef unsigned long       Uint32;		// 32-біта, [0, +4 294 967 295]
typedef unsigned long long  Uint64;		// 64-біта, [0, 18 446 744 073 709 551 615]
typedef float               float32;	// 32-біта, [-2 139 095 039, +2 139 095 039], бінарний формат з плаваючою комою одинарної точності
typedef long double         float64;	// 64-біта, [-3.14159265358979323846264338327950288419716939937510, + 3.14159265358979323846264338327950288419716939937510] бінарний формат з плаваючою комою чотирикратної точності
#endif

// typedef BOOLEAN unsigned char; /* 0 = false, 0xFF = true */
// typedef INT8 char; /* 8-bit signed integer */
// typedef INT16 short int; /* 16-bit signed integer */
// typedef INT32 long int; /* 32-bit signed integer */
// typedef UINT8 unsigned char; /* 8-bit unsigned integer */
// typedef UINT16 unsigned short int; /* 16-bit unsigned integer */
// typedef UINT32 unsigned long int; /* 32-bit unsigned integer */
// typedef FP32 float; /* 32-bit IEEE floating point */
// typedef FP64 double; /* 64-bit double-prec IEEE floating


//---------------------------------------------------------------------------
// Include All Peripheral Header Files:
//

#include "DSP280x_Adc.h"                // ADC Registers
#include "DSP280x_DevEmu.h"             // Device Emulation Registers
#include "DSP280x_CpuTimers.h"          // 32-bit CPU Timers
#include "DSP280x_ECan.h"               // Enhanced eCAN Registers
#include "DSP280x_ECap.h"               // Enhanced Capture
#include "DSP280x_EPwm.h"               // Enhanced PWM
#include "DSP280x_EQep.h"               // Enhanced QEP
#include "DSP280x_Gpio.h"               // General Purpose I/O Registers
//#include "DSP280x_HRCap.h"              // High Resolution Capture
#include "DSP280x_I2c.h"                // I2C Registers
//#include "DSP280x_Lin.h"                // LIN Registers
//#include "DSP280x_NmiIntrupt.h"         // NMI Interrupt Registers
#include "DSP280x_PieCtrl.h"            // PIE Control Registers
#include "DSP280x_PieVect.h"            // PIE Vector Table
#include "DSP280x_Spi.h"                // SPI Registers
#include "DSP280x_Sci.h"                // SCI Registers
#include "DSP280x_SysCtrl.h"            // System Control/Power Modes
#include "DSP280x_XIntrupt.h"           // External Interrupts
#include "DSP280x_GlobalPrototypes.h"	 // Global Prototyps
#include "DSP280x_Examples.h"			 // Device Definitions
#include "IQmathLib.h"
#include "structures.h"

#if DSP28_2809 || DSP28_2808
#define DSP28_EPWM1 1
#define DSP28_EPWM2 1
#define DSP28_EPWM3 1
#define DSP28_EPWM4 1
#define DSP28_EPWM5 1
#define DSP28_EPWM6 1
#define DSP28_ECAP1 1
#define DSP28_ECAP2 1
#define DSP28_ECAP3 1
#define DSP28_ECAP4 1
#define DSP28_EQEP1 1
#define DSP28_EQEP2 1
#define DSP28_ECANA 1
#define DSP28_ECANB 1
#define DSP28_SPIA  1
#define DSP28_SPIB  1
#define DSP28_SPIC  1
#define DSP28_SPID  1
#define DSP28_SCIA  1
#define DSP28_SCIB  1
#define DSP28_I2CA  1
#endif  // end DSP28_2809 || DSP_2808


#if DSP28_2806
#define DSP28_EPWM1 1
#define DSP28_EPWM2 1
#define DSP28_EPWM3 1
#define DSP28_EPWM4 1
#define DSP28_EPWM5 1
#define DSP28_EPWM6 1
#define DSP28_ECAP1 1
#define DSP28_ECAP2 1
#define DSP28_ECAP3 1
#define DSP28_ECAP4 1
#define DSP28_EQEP1 1
#define DSP28_EQEP2 1
#define DSP28_ECANA 1
#define DSP28_ECANB 0
#define DSP28_SPIA  1
#define DSP28_SPIB  1
#define DSP28_SPIC  1
#define DSP28_SPID  1
#define DSP28_SCIA  1
#define DSP28_SCIB  1
#define DSP28_I2CA  1
#endif  // end DSP28_2806


#if DSP28_2802 || DSP28_2801
#define DSP28_EPWM1 1
#define DSP28_EPWM2 1
#define DSP28_EPWM3 1
#define DSP28_EPWM4 0
#define DSP28_EPWM5 0
#define DSP28_EPWM6 0
#define DSP28_ECAP1 1
#define DSP28_ECAP2 1
#define DSP28_ECAP3 0
#define DSP28_ECAP4 0
#define DSP28_EQEP1 1
#define DSP28_EQEP2 0
#define DSP28_ECANA 1
#define DSP28_ECANB 0
#define DSP28_SPIA  1
#define DSP28_SPIB  1
#define DSP28_SPIC  0
#define DSP28_SPID  0
#define DSP28_SCIA  1
#define DSP28_SCIB  0
#define DSP28_I2CA  1
#endif  // end DSP28_2802 || DSP_2801


#if DSP28_28016
#define DSP28_EPWM1 1
#define DSP28_EPWM2 1
#define DSP28_EPWM3 1
#define DSP28_EPWM4 1
#define DSP28_EPWM5 0
#define DSP28_EPWM6 0
#define DSP28_ECAP1 1
#define DSP28_ECAP2 1
#define DSP28_ECAP3 0
#define DSP28_ECAP4 0
#define DSP28_EQEP1 0
#define DSP28_EQEP2 0
#define DSP28_ECANA 1
#define DSP28_ECANB 0
#define DSP28_SPIA  1
#define DSP28_SPIB  0
#define DSP28_SPIC  0
#define DSP28_SPID  0
#define DSP28_SCIA  1
#define DSP28_SCIB  0
#define DSP28_I2CA  1
#endif  // end DSP28_28016

#if DSP28_28015
#define DSP28_EPWM1 1
#define DSP28_EPWM2 1
#define DSP28_EPWM3 1
#define DSP28_EPWM4 1
#define DSP28_EPWM5 0
#define DSP28_EPWM6 0
#define DSP28_ECAP1 1
#define DSP28_ECAP2 1
#define DSP28_ECAP3 0
#define DSP28_ECAP4 0
#define DSP28_EQEP1 0
#define DSP28_EQEP2 0
#define DSP28_ECANA 0
#define DSP28_ECANB 0
#define DSP28_SPIA  1
#define DSP28_SPIB  0
#define DSP28_SPIC  0
#define DSP28_SPID  0
#define DSP28_SCIA  1
#define DSP28_SCIB  0
#define DSP28_I2CA  1
#endif  // end DSP28_28015

// Timer definitions based 100MHz System Clock
#if (DSP28_2801 || DSP_2802 || DSP_28044 ||  DSP28_2806 || DSP28_2808 || DSP28_2809)
#define	uSec0_5					500         // Мікросекунд
#define	uSec0_075				750         // Мікросекунд
#define	mSec0_1					1000        // Мілісекунд
#define	mSec0_25				2500        // Мілісекунд
#define	mSec0_5					5000        // Мілісекунд
#define	mSec0_75				7500        // Мілісекунд
#define	Sec0_01					10000       // Секунд
#define	Sec0_05					50000       // Секунд
#define	Sec0_075				75000       // Секунд
#define	Sec0_1					100000      // Секунд
#define	Sec0_25					250000      // Секунд
#define	Sec0_5					500000      // Секунд
#define	Sec0_75					750000      // Секунд
#define	Sec1					1000000     // Секунд
#define	Sec1_25					1250000     // Секунд
#define	Sec1_5					1500000     // Секунд
#define	Sec1_75					1750000     // Секунд
#define	Sec2					2000000     // Секунд
#define	Sec5					5000000     // Секунд
#define	Sec7_5					7500000     // Секунд
#define	Sec10					100000000	// Секунд
// Timer definitions based on 80MHz System Clock
// 	if not using a 80MHz clock define a different set of constants elsewhere
#if (DSP28_28062PZ || DSP28_28063PZ || DSP28_28064PZ || DSP28_28065PZ || DSP28_28066PZ || DSP28_28067PZ || DSP28_28068PZ || DSP28_28069PZ)
    #define      mSec0_5          40000           // 0.5 mS
    #define      mSec0_75         60000           // 0.75 mS
    #define      mSec1            80000           // 1.0 mS
    #define      mSec2            160000          // 2.0 mS
    #define      mSec5            400000          // 5.0 mS
    #define      mSec7_5          600000          // 7.5 mS
    #define      mSec10           800000          // 10 mS
    #define      mSec20           1600000         // 20 mS
    #define      mSec50           4000000         // 50 mS
    #define      mSec75           6000000         // 75 mS
    #define      mSec100          8000000         // 100 mS
    #define      mSec200          16000000        // 200 mS
    #define      mSec500          40000000        // 500 mS
    #define      mSec750          60000000        // 750 mS
    #define      mSec1000         80000000        // 1000 mS
    #define      mSec2000         160000000       // 2000 mS
    #define      mSec5000         400000000       // 5000 mS
#endif
// 60 MHz devices (28027/28026)
#if (DSP28_28026PT||DSP28_28026DA||DSP28_28027PT||DSP28_28027DA)
    #define      mSec0_5          30000           // 0.5 mS
    #define      mSec0_75         45000           // 0.75 mS
    #define      mSec1            60000           // 1.0 mS
    #define      mSec2            120000          // 2.0 mS
    #define      mSec5            300000          // 5.0 mS
    #define      mSec7_5          450000          // 7.5 mS
    #define      mSec10           600000          // 10 mS
    #define      mSec20           1200000         // 20 mS
    #define      mSec50           3000000         // 50 mS
    #define      mSec75           4500000         // 75 mS
    #define      mSec100          6000000         // 100 mS
    #define      mSec200          12000000        // 200 mS
    #define      mSec500          30000000        // 500 mS
    #define      mSec750          45000000        // 750 mS
    #define      mSec1000         60000000        // 1000 mS
    #define      mSec2000         120000000       // 2000 mS
    #define      mSec5000         300000000       // 5000 mS
#endif

// 50 MHz devices (28023/28022)
#if (DSP28_28022PT||DSP28_28022DA||DSP28_28023PT||DSP28_28023DA)
    #define      mSec0_5          25000           // 0.5 mS
    #define      mSec0_75         37500           // 0.75 mS
    #define      mSec1            50000           // 1.0 mS
    #define      mSec2            100000          // 2.0 mS
    #define      mSec5            250000          // 5.0 mS
    #define      mSec7_5          375000          // 7.5 mS
    #define      mSec10           500000          // 10 mS
    #define      mSec20           1000000         // 20 mS
    #define      mSec50           2500000         // 50 mS
    #define      mSec75           3750000         // 75 mS
    #define      mSec100          5000000         // 100 mS
    #define      mSec200          10000000        // 200 mS
    #define      mSec500          25000000        // 500 mS
    #define      mSec750          37500000        // 750 mS
    #define      mSec1000         50000000        // 1000 mS
    #define      mSec2000         100000000       // 2000 mS
    #define      mSec5000         250000000       // 5000 mS
#endif

//40 MHz devices (28021/28020/280200)
#if (DSP28_280200PT||DSP28_280200DA||DSP28_28020PT||DSP28_28020DA||DSP28_28021PT ||DSP28_28021DA)
    #define      mSec0_5          20000           // 0.5 mS
    #define      mSec0_75         30000           // 0.75 mS
    #define      mSec1            40000           // 1.0 mS
    #define      mSec2            80000           // 2.0 mS
    #define      mSec5            200000          // 5.0 mS
    #define      mSec7_5          300000          // 7.5 mS
    #define      mSec10           400000          // 10 mS
    #define      mSec20           800000          // 20 mS
    #define      mSec50           2000000         // 50 mS
    #define      mSec75           3000000         // 75 mS
    #define      mSec100          4000000         // 100 mS
    #define      mSec200          8000000         // 200 mS
    #define      mSec500          20000000        // 500 mS
    #define      mSec750          30000000        // 750 mS
    #define      mSec1000         40000000        // 1000 mS
    #define      mSec2000         80000000        // 2000 mS
    #define      mSec5000         200000000       // 5000 mS
#endif

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP280x_DEVICE_H definition


//===========================================================================
// End of file.
//===========================================================================
