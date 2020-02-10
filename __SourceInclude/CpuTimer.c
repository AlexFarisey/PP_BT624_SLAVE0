/*
 * CpuTimer.c
 *
 *  Created on: 24 ����. 2017 �.
 *      Author: ����
 */
#include "DSP280x_Device.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------

void InitCpuTimerT0(Uint32 PRD)
{
    CpuTimer0Regs.TCR.bit.TSS = 1;                                                  // 1 = Stop timer, 0 = Start/Restart Timer
    CpuTimer0Regs.PRD.all  = PRD;                                                   // ������������ �������+������
    CpuTimer0Regs.TPR.all  = 0;                                                     // x = 0, 1, 2. PSC ������ - ������ ��������� ����������� � TDDR + 1
    CpuTimer0Regs.TPRH.all = 0;                                                     // -//-
    CpuTimer0Regs.TCR.bit.TRB = 0;                                                  // ��� ����������������. 0 - ����������� ����������������. 1 - ������������������ ��� ������� Ҳ� = PRD
    CpuTimer0Regs.TCR.bit.TSS =0;                                                   // ��������� CpuTimer
    CpuTimer0Regs.TCR.bit.SOFT = 1;
    CpuTimer0Regs.TCR.bit.FREE = 1;                                                 // Timer Free Run
    CpuTimer0Regs.TCR.bit.TIE = 1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
