// TI File $Revision: /main/7 $
// Checkin $Date: April 5, 2007   15:14:19 $
//###########################################################################
//
// FILE:   DSP280x_GlobalPrototypes.h
//
// TITLE:  Global prototypes for DSP280x Examples
// 
//###########################################################################
// $TI Release: DSP280x C/C++ Header Files V1.70 $
// $Release Date: July 27, 2009 $
//###########################################################################

#ifndef DSP280X_GLOBALPROTOTYPES_H
#define DSP280X_GLOBALPROTOTYPES_H


#ifdef __cplusplus
extern "C" {
#endif

/*---- shared global function prototypes -----------------------------------*/
extern void InitAdc(void);
extern void InitPeripherals(void);
#if DSP28_ECANA
extern void InitECan(void);
extern void InitECana(void);
extern void InitECanGpio(void);
extern void InitECanaGpio(void);
#endif // endif DSP28_ECANA
#if DSP28_ECANB
extern void InitECanb(void);
extern void InitECanbGpio(void);
#endif // endif DSP28_ECANB
extern void InitECap(void);
extern void InitECapGpio(void);
extern void InitECap1Gpio(void);
extern void InitECap2Gpio(void);
#if DSP28_ECAP3 
extern void InitECap3Gpio(void);
#endif // endif DSP28_ECAP3
#if DSP28_ECAP4
extern void InitECap4Gpio(void);
#endif // endif DSP28_ECAP4
extern void InitEPwm(void);
extern void InitEPwmGpio(void);
extern void InitEPwm1Gpio(void);
extern void InitEPwm2Gpio(void);
extern void InitEPwm3Gpio(void);
#if DSP28_EPWM4
extern void InitEPwm4Gpio(void);
#endif // endif DSP28_EPWM4
#if DSP28_EPWM5
extern void InitEPwm5Gpio(void);
#endif // endif DSP28_EPWM5
#if DSP28_EPWM6
extern void InitEPwm6Gpio(void);
#endif // endif DSP28_EPWM6
#if DSP28_EQEP1
extern void InitEQep(void);
extern void InitEQepGpio(void);
extern void InitEQep1Gpio(void);
#endif // if DSP28_EQEP1
#if DSP28_EQEP2
extern void InitEQep2Gpio(void);
#endif // endif DSP28_EQEP2
extern void InitGpio(void);
extern void InitI2CGpio(void);
extern void InitI2C(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void InitSci(void);
extern void InitSciGpio(void);
extern void InitSciaGpio(void);
#if DSP28_SCIB
extern void InitScibGpio(void);
#endif // endif DSP28_SCIB
extern void InitSpi(void);
extern void InitSpiGpio(void);
extern void InitSpiaGpio(void);
#if DSP28_SPIB
extern void InitSpibGpio(void);
#endif // endif DSP28_SPIB
#if DSP28_SPIC
extern void InitSpicGpio(void);
#endif // endif DSP28_SPIC
#if DSP28_SPID
extern void InitSpidGpio(void);
#endif // endif DSP28_SPID
extern void InitSysCtrl(void);
extern void InitTzGpio(void);
extern void InitXIntrupt(void);
extern void InitPll(Uint16 pllcr, Uint16 clkindiv);
extern void InitPeripheralClocks(void);
extern void EnableInterrupts(void);
extern void DSP28x_usDelay(Uint32 Count);
#define KickDog ServiceDog     // For compatiblity with previous versions
extern void ServiceDog(void);
extern void DisableDog(void);
extern Uint16 CsmUnlock(void);
// DSP28_DBGIER.asm
extern void SetDBGIER(Uint16 dbgier);
//---------------------------------------------------------------------------
extern void DeviceInit(void);
extern void ISR_ILLEGAL(void);
extern void Led_ON1(void);
extern void Led_OFF1(void);
extern void Led_ON2(void);
extern void Led_OFF2(void);
extern void DeviceInitBlink(Uint32 tLite_on);
extern void Led_Blink(Uint16 num_Blink, Uint32 t_s_Light_on, Uint32 t_s_Light_off);
extern void InitADC(void);
extern void ADC_SOC_CNF(int ChSel[], int Trigsel[], int ACQPS[], int IntChSel, int mode, int TEMPCORE);
extern void PWM_1ch_UpDwnCnt_CNF(int16 n, Uint16 period, int16 duty, int16 mode, int16 phase);
extern void tCPU(void);
extern void PID_Blink(void);
extern void pingPong (void);
extern void MultiLed (void);
extern void PWMBlink (void);
extern void ePWMiSR (void);
extern void ledblinky(void);
//---------------------------------------------------------------------------
//									SCI
//---------------------------------------------------------------------------
extern void InitScilHost(Uint16 n, Uint32 speed);

//---------------------------------------------------------------------------
//                                  CPU
//---------------------------------------------------------------------------
extern void InitCpuTimerT0(Uint32 PRD);

//---------------------------------------------------------------------------
//									CRC
//---------------------------------------------------------------------------
///extern void CRC16(unsigned short int *crc,unsigned char c);
extern void CRCxorSum(unsigned int crc, unsigned int *array[], unsigned char numberbyte);
Uint16 checkSumm(unsigned int array[], unsigned char arrayLength);
//---------------------------------------------------------------------------
//									CAN
//---------------------------------------------------------------------------
extern void InitCanHost (void);
extern void CanHost(void);
extern void MailRead(void);
extern void MailCheck(void);
//---------------------------------------------------------------------------
//									RS-422
//---------------------------------------------------------------------------
extern void RS422Canal(int channel);
extern void CTRL1_ON (void);
extern void CTRL2_ON (void);
extern void CTRL1_OFF (void);
extern void CTRL2_OFF (void);
//---------------------------------------------------------------------------
extern void Pulse(int on_off);
extern void Impedance(int on_off);
extern void Amplitude(int on_off);
extern void Led (int on_off);
//---------------------------------------------------------------------------
//extern void Led7V(int on_off);
//extern void Led100V(int on_off);
//extern void Led250V(int on_off);
//extern void LedRotation (Uint16 on_off);
//extern void Test (void);
//---------------------------------------------------------------------------
//extern void Blink (Uint16 on_off, Uint32 time);
//---------------------------------------------------------------------------
extern void A0(void);           //state A0
extern void A1(void);           //state A1
extern void A2(void);           //state A2
extern void A3(void);           //state A3
extern void A4(void);           //state A4
extern void B0(void);           //state B0
extern void B1(void);           //state B1
extern void B2(void);           //state B2
extern void B3(void);           //state B3
extern void B4(void);           //state B4
extern void C0(void);           //state C0
extern void C1(void);           //state C1
extern void C2(void);           //state C2
extern void C3(void);           //state C3
extern void C4(void);           //state C4

//                 CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results
extern void InitFlash(void);
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);


//---------------------------------------------------------------------------
// External symbols created by the linker cmd file
// DSP28 examples will use these to relocate code from one LOAD location 
// in either Flash or XINTF to a different RUN location in internal
// RAM
//extern Uint16 *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;
extern Uint16 *RamfuncsLoadStart;
extern Uint16 *RamfuncsLoadEnd;
extern Uint16 *RamfuncsRunStart;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of DSP280X_GLOBALPROTOTYPES_H

//===========================================================================
// End of file.
//===========================================================================
