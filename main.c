/*
 * main.c
 */
#include "DSP280x_Device.h"
//------------------------------------------------------------------------------

    void (*Alpha_State_Ptr)(void);                                              // ϳ���������� ���������� ������
    volatile struct SYSTEM sys;
    Uint16 VTimer0[4];                                                          // ������ ������ �����/����
    Uint16 VTimer1[4];                                                          // ������ ������ ���
//    Uint16 VTimer2[4];                                                          //

    void (*RcvTaskPointer)(void);

//------------------------------------------------------------------------------
//                          ���� 100�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                          ��������
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                          ������
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

int main(void) {

	DeviceInit();
#ifdef FLASH 																	// ��� ������������ Flash
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart); 			 // ���������� �������� ������� � ����


	InitFlash();																// ������������ ����� �����
#endif
    CpuTimer0Regs.PRD.all =  Sec0_1;                                            // ����� ������� ��� ������ A
    CpuTimer1Regs.PRD.all =  Sec0_1;                                            // ����� ������� ��� ������ B
//    CpuTimer2Regs.PRD.all =  Sec0_1;                                          // ����� ������� ��� ������ C

    VTimer0[0] = 0;
    VTimer1[0] = 0;
//    VTimer2[0] = 0;


    InitScilHost(Ch_A, Rate_921_kB_s);
    Alpha_State_Ptr = &A0;                                                      //                                                         //
//----------------------------³��������� ���� � ��----------------------------
//-------------------------��������� ���������� ����--------------------------


for (;;){ /*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/

   //===========================================================
    (*Alpha_State_Ptr)();   // (A0,B0,...)
    //===========================================================
}/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>  for END  <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
}/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>  mine END <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/

void A0(void){
    if(CpuTimer0Regs.TCR.bit.TIF == 1){
        CpuTimer0Regs.TCR.bit.TIF = 1;
/**********ϳ��������� ���������� USB *****************************************/
        (*RcvTaskPointer)();
        sys.uart.SerialCommsTime++;

/*****************************************************************************/
        VTimer0[0]++;}           // ������ ����������  0
    Alpha_State_Ptr = &B0;}      //

void B0(void){
    if(CpuTimer1Regs.TCR.bit.TIF == 1){
        CpuTimer1Regs.TCR.bit.TIF = 1;

        VTimer1[0]++;}           // ������ ����������  1
    Alpha_State_Ptr = &A0;}      //










