/*
 * RxTxSci.c
 *
 *  Created on: 22 ����. 2019 �.
 *      Author: ����
 */
#include "DSP280x_Device.h"     // DSP28 Headerfile Include File

extern void (*RcvTaskPointer)(void);
void TxChar(Uint16 Tx);
void GetAddr(void);
void GetCmd(void);
void GetId(void);
void GetSize(void);
void GetData(void);
void GetCrc(void);
void GetExt(void);
void CheckCrc(void);
void EchoByte(void);
unsigned short Crc_16_CCITT(unsigned char quantity_byte, unsigned short len);



Uint16 RxChar(void){
    if (SciaRegs.SCIRXST.bit.RXRDY == 1){       // ����������, �� ���� �������� ����
        sys.uart.SerialCommsTime = 0;           // ��������� �������� �������� �� ����������� �����
        return SciaRegs.SCIRXBUF.bit.RXDT;      // �������� �����
        }
    else if (SciaRegs.SCIRXST.bit.BRKDT == 1 || sys.uart.SerialCommsTime > 2500){ // �������� ���� �� ������� ����������� �� �� �������
        // ���������� ������������ ������ �� ��������� �������� �����������
        SciaRegs.SCICCR.all =0x0027;            // ��������: ������� ������� 8 ��. �������� ������� �������� - ��������. ����-��� = 1
        SciaRegs.SCICCR.bit.LOOPBKENA = 0;      // ��������� ����. 0-test mode disabled, 1-test mode enabled
        SciaRegs.SCICTL1.all =0x0003;           // �������� �������� ��� ������� �� ����������� �����
        SciaRegs.SCICTL2.all =0x0003;           // ����������� ������������ ��� �����������
        SciaRegs.SCICTL1.all =0x0023;           // ³��������� ������������ ��� ������ ���� ��������

        sys.uart.SerialCommsTime = 0;           // ��������� �������� �������� �� ����������� �����
        }
    return 0;
}
void TxChar(Uint16 Tx){
    if(SciaRegs.SCICTL2.bit.TXRDY == 1){        // ���������� �� ������ ����� TXBUF,  ������ ������� ������ TXRDY = 1
        SciaRegs.SCITXBUF=Tx;                   // ���� ��� �� ����������� ������
        sys.uart.SerialCommsTime = 0;           // ��������� �������� �������� �� ����������� �����
        }
}

Uint16 Check(void){
    Uint16 ReceivedChar;
    ReceivedChar = RxChar();
    if(ReceivedChar == "ok"){

    }

}

Uint16 ChecSSSk(Uint16 quantity_byte){
    Uint16 arrayChar[4];
    Uint16 Ch;
    if(RxChar() != ('Ok')){
    }
    else if(RxChar() == 'ERROR_CRC'){
    }
    else{
        for(Ch = 0; Ch <= 4; Ch ++){

        }
    }

    //   switch(RxChar()){
//    case 'OK'
//    case 'ERROR_CRC'

//    }


    return arrayChar;
}



/*
Uint16 GetByte(void){
    if(SciaRegs.SCIRXST.bit.RXRDY == 1){                // ���� ���������� ��������
        sys.uart.pkg.flag = GetByteOk;                 // ����������. ������ ������ ���������� �����
        sys.uart.SerialCommsTime = 0;                   // ˳������� �������� �������
        return SciaRegs.SCIRXBUF.bit.RXDT;              // ������� ��������� ������ �� �������� �� RxChar
        }
    else if (SciaRegs.SCIRXST.bit.BRKDT == 1 || sys.uart.SerialCommsTime > Sec0_25){ // �������� �� ������� �� �� timeout 0,25 c
        SciaRegs.SCICCR.all = 0x0007;                   // 1 stop bit, �� �� �������� �������, 8-bit char, ���������� ��������
        SciaRegs.SCICTL1.all = 0x0003;                  // ����� �� �������� - TX, RX, ����������� SCICLK.  �������� - RX ERR, SLEEP, TXWAKE
        SciaRegs.SCICTL2.all = 0x0083;
        SciaRegs.SCICTL2.bit.TXINTENA = 0;
        SciaRegs.SCICTL1.all = 0x23;                    // ³����������� �� �������� SCI-A
        sys.uart.SerialCommsTime = 0;                   // �������� ���������
        goto end;
    }
    end: return sys.uart.pkg.flag = GetByteError;      // ����������� ����� � ������ ������ CMD
}

void GetAddr(void){
    sys.uart.RxChar = GetByte();                        // �������� ��������� ������ ��� ��������� �����������
    if(sys.uart.RxChar == slave1){                      // ��������� ��������� ������ � ������� ��������
        sys.uart.pkg.access.byte.Addr = sys.uart.RxChar; // ������ ������ ���������
        sys.uart.pkg.flag = AddrOk;                     // ����������
        RcvTaskPointer = &GetCmd;                       // ���� ������ ������� � �������� ���������� �� ���������� �������
        }
    else{
        sys.uart.pkg.flag = AddrError;                  // ����������
        RcvTaskPointer = &GetAddr;                      // ��������� ������ �� � �������, ���������� ��������� ��������� ����� �����������
        }
}
void GetCmd(void){
    sys.uart.RxChar = GetByte();                        // �������� ��������� ������ ��� ��������� �����������
    if(sys.uart.RxChar == write){                       // ��������� ������� �� ����� ���������� �����
        sys.uart.pkg.access.byte.Cmd = sys.uart.RxChar;  // ������ ������� ���������
        sys.uart.RxList[0] = (Uint16*)sys.uart.pkg.access.byte.Cmd; // ������ ������� ��������� ��� ��������� Crc
        sys.uart.pkg.flag = CmdOk;                      // ����������
        RcvTaskPointer = &GetSize;                      // ���������� �� ��������� ������ ������� ���� �����������
        }
    else{                                               // ����� �� ���������� ����� �� ��������
        sys.uart.pkg.flag = CmdError;                   // ����������
        RcvTaskPointer = &GetAddr;                      // ��������� ������ �� � ��������, ���������� ��������� ��������� ����� �����������
        }
}
void GetSize(void){
    if(sys.uart.pkg.access.all == Open){                // ��������� �������� �� ������� ������ �� ������� ������
        sys.uart.pkg.size = GetByte();                  // �������� ������ ������� ��������� ���� �����������
        sys.uart.RxList[1] = (Uint16*)sys.uart.pkg.size;// ������ ������ ��������� ��� ��������� Crc
        sys.uart.pkg.flag = SizeOk;                     // ����������
        RcvTaskPointer = &GetId;                        // ���������� �� ��������� �����������
    }
    else{
        sys.uart.pkg.flag = SizeError;                  // ����������
        RcvTaskPointer = &GetAddr;                      // ������� ������� �� � ����� ����������� ��������, ���������� ��������� ��������� ����� �����������
        }
}
void GetId(void){
    Uint16 i;
    for (i = 0; i <= BYTE_1; i++){                      // �������� byte0 �������������
        if(i == 0)sys.uart.pkg.id.byte.b0 = GetByte();
        else sys.uart.pkg.id.byte.b1 = GetByte();
    }
    if(sys.uart.pkg.id.all == sys.idm){                 // ����������  ������������� �� ������� ������ �������������� ����������
        sys.uart.RxList[2] = (Uint16*)sys.uart.pkg.id.all;// ������ �������������a ������ �� ���������� ��� ���������� ��������� Crc
        sys.uart.pkg.flag = IdOk;                       // ����������
        RcvTaskPointer = &GetData;                      // ���� ������ ������� � �������� ���������� �� ���������� �����
        }
    else{
        sys.uart.pkg.flag = IdError;                    // ����������
        RcvTaskPointer = &GetAddr;                      // ��������� ������ �� � ���������������, ���������� ��������� ��������� ����� �����������
        }
}
void GetData(void){
    Uint16 d;
    for (d = 0; d <= sys.uart.pkg.size; d++){
        sys.uart.RxList[d+2] = (Uint16*)GetByte();       // �������� ������� ��� � ��������� �� ������� ��������� ������
        sys.uart.pkg.flag = DataError;                  // ����������
    }
    sys.uart.pkg.flag = DataOk;                         // ����������
    RcvTaskPointer = &GetCrc;                           // ��������� ������ � ������ ��� ���������, ���������� �� ��������� �������� ���������� ����
}
void GetCrc(void){
    Uint16 c;
    for(c = 0; c <= BYTE_1; c++){
        if(c == 0) sys.uart.pkg.crc.byte.b0 = GetByte();// �������� �������� ���������� ����
        else sys.uart.pkg.crc.byte.b1 = GetByte();      // �������� �������� ���������� ����
        sys.uart.pkg.flag = CrcError;                   // ����������
    }
    sys.uart.pkg.flag = CrcOk;                          // ����������
    RcvTaskPointer = &GetExt;                           // ��������� ������ � ������ ��� ����������, ���������� �� ��������� �������� ��� �����������
}
void GetExt(void){
    sys.uart.RxChar = GetByte();                        // �������� ��������� ������ ��� ��������� �����������
    if(sys.uart.RxChar == yes){                         // ���������� ��� �����������
        sys.uart.pkg.flag = ExtOk;                      // ����������
        RcvTaskPointer = &CheckCrc;                     // �������� �� �������� ���������� ����
        }
    else{
        sys.uart.pkg.flag = ExtError;                   // ����������
        RcvTaskPointer = &GetAddr;                      // ��������� ������ �� � �������, ���������� ��������� ��������� ����� �����������
        }
}
void CheckCrc(void){
    if(Crc_16_CCITT(&sys.uart.RxList, sys.uart.pkg.size) == sys.uart.pkg.crc.all){  // ������� ��������� ���� ���������� � ���������

    }
}
*/
