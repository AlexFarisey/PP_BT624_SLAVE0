/*
 * RxTxSci.c
 *
 *  Created on: 22 серп. 2019 р.
 *      Author: Саня
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
    if (SciaRegs.SCIRXST.bit.RXRDY == 1){       // перевіряэмо, чи було отримано знак
        sys.uart.SerialCommsTime = 0;           // Ініціювати лічильник затримки до початкового стану
        return SciaRegs.SCIRXBUF.bit.RXDT;      // Зберігаємо буфер
        }
    else if (SciaRegs.SCIRXST.bit.BRKDT == 1 || sys.uart.SerialCommsTime > 2500){ // Скидання УАРТ по прапору переривання чи по таймаут
        // Перевіряємо налаштування каналу та додатково здійснюєм переривання
        SciaRegs.SCICCR.all =0x0027;            // Ввімкнено: Довжини символів 8 біт. Контроль парності паритету - непарний. Стоп-бітів = 1
        SciaRegs.SCICCR.bit.LOOPBKENA = 0;      // Замикання петлі. 0-test mode disabled, 1-test mode enabled
        SciaRegs.SCICTL1.all =0x0003;           // Виконуємо скидання всіх прапорів до початкового стану
        SciaRegs.SCICTL2.all =0x0003;           // Виставляємо налаштування бітів переривання
        SciaRegs.SCICTL1.all =0x0023;           // Відновлюємо налаштування ліній звязку після скидання

        sys.uart.SerialCommsTime = 0;           // Ініціювати лічильник затримки до початкового стану
        }
    return 0;
}
void TxChar(Uint16 Tx){
    if(SciaRegs.SCICTL2.bit.TXRDY == 1){        // перевіряэмо Чи пустий буфер TXBUF,  прапор пустого буферу TXRDY = 1
        SciaRegs.SCITXBUF=Tx;                   // Якщо так то відправляємо символ
        sys.uart.SerialCommsTime = 0;           // Ініціювати лічильник затримки до початкового стану
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
    if(SciaRegs.SCIRXST.bit.RXRDY == 1){                // Флаг готовности приймача
        sys.uart.pkg.flag = GetByteOk;                 // діагностика. Прапор успішно прийнятого байта
        sys.uart.SerialCommsTime = 0;                   // Лічильник затримки прийому
        return SciaRegs.SCIRXBUF.bit.RXDT;              // зчитуємо прийнятий символ та зберігаємо до RxChar
        }
    else if (SciaRegs.SCIRXST.bit.BRKDT == 1 || sys.uart.SerialCommsTime > Sec0_25){ // скидання по прапору чи по timeout 0,25 c
        SciaRegs.SCICCR.all = 0x0007;                   // 1 stop bit, Не має контролю парності, 8-bit char, асинхронна передача
        SciaRegs.SCICTL1.all = 0x0003;                  // Дозвіл на скидання - TX, RX, Внутрішнього SCICLK.  Вимкнуто - RX ERR, SLEEP, TXWAKE
        SciaRegs.SCICTL2.all = 0x0083;
        SciaRegs.SCICTL2.bit.TXINTENA = 0;
        SciaRegs.SCICTL1.all = 0x23;                    // Відмовляємось від скидання SCI-A
        sys.uart.SerialCommsTime = 0;                   // Скидання лічильника
        goto end;
    }
    end: return sys.uart.pkg.flag = GetByteError;      // повернутися назад і чекати нового CMD
}

void GetAddr(void){
    sys.uart.RxChar = GetByte();                        // Зберігаємо отриманий символ для подальшоо опрацювання
    if(sys.uart.RxChar == slave1){                      // Порівнюємо прийнятий символ з адресою пристрою
        sys.uart.pkg.access.byte.Addr = sys.uart.RxChar; // Символ адреси збережено
        sys.uart.pkg.flag = AddrOk;                     // діагностика
        RcvTaskPointer = &GetCmd;                       // якщо адреса співпадає з пристроєм переходимо до зчитування команди
        }
    else{
        sys.uart.pkg.flag = AddrError;                  // діагностика
        RcvTaskPointer = &GetAddr;                      // Прийнятий символ не є адресою, повторюємо процедуру прийняття кадру повідомлення
        }
}
void GetCmd(void){
    sys.uart.RxChar = GetByte();                        // Зберігаємо отриманий символ для подальшоо опрацювання
    if(sys.uart.RxChar == write){                       // Виявляэмо команду на запит считування даних
        sys.uart.pkg.access.byte.Cmd = sys.uart.RxChar;  // Символ команди збережено
        sys.uart.RxList[0] = (Uint16*)sys.uart.pkg.access.byte.Cmd; // Символ команди збережено для отримання Crc
        sys.uart.pkg.flag = CmdOk;                      // діагностика
        RcvTaskPointer = &GetSize;                      // Переходимо до отримання ємності кількості байт повідомлення
        }
    else{                                               // Запит на считування даних не виявлено
        sys.uart.pkg.flag = CmdError;                   // діагностика
        RcvTaskPointer = &GetAddr;                      // Прийнятий символ не є командою, повторюємо процедуру прийняття кадру повідомлення
        }
}
void GetSize(void){
    if(sys.uart.pkg.access.all == Open){                // Додаткова перевірка чи співпадає адреса та команда запиту
        sys.uart.pkg.size = GetByte();                  // Зберігаємо символ кількості переданих байт повідомлення
        sys.uart.RxList[1] = (Uint16*)sys.uart.pkg.size;// Символ ємності збережено для отримання Crc
        sys.uart.pkg.flag = SizeOk;                     // діагностика
        RcvTaskPointer = &GetId;                        // Переходимо до отримання повідомлення
    }
    else{
        sys.uart.pkg.flag = SizeError;                  // діагностика
        RcvTaskPointer = &GetAddr;                      // Прийняті символи не є кодом авторизації пристрою, повторюємо процедуру прийняття кадру повідомлення
        }
}
void GetId(void){
    Uint16 i;
    for (i = 0; i <= BYTE_1; i++){                      // Зберігаємо byte0 ідентифікатор
        if(i == 0)sys.uart.pkg.id.byte.b0 = GetByte();
        else sys.uart.pkg.id.byte.b1 = GetByte();
    }
    if(sys.uart.pkg.id.all == sys.idm){                 // Перевіряємо  ідентифікатор за списком відомих ідентифікаторів повідомлень
        sys.uart.RxList[2] = (Uint16*)sys.uart.pkg.id.all;// Символ ідентифікаторa відомий та збережений для подальшого отримання Crc
        sys.uart.pkg.flag = IdOk;                       // діагностика
        RcvTaskPointer = &GetData;                      // якщо адреса співпадає з пристроєм переходимо до зчитування даних
        }
    else{
        sys.uart.pkg.flag = IdError;                    // діагностика
        RcvTaskPointer = &GetAddr;                      // Прийнятий символ не є ідентифікатором, повторюємо процедуру прийняття кадру повідомлення
        }
}
void GetData(void){
    Uint16 d;
    for (d = 0; d <= sys.uart.pkg.size; d++){
        sys.uart.RxList[d+2] = (Uint16*)GetByte();       // Зберігаємо отримані дані в залежності від кількості переданих пакетів
        sys.uart.pkg.flag = DataError;                  // діагностика
    }
    sys.uart.pkg.flag = DataOk;                         // діагностика
    RcvTaskPointer = &GetCrc;                           // Прийнятий символ є даними для зитування, переходимо до процедури перевірки контрольної суми
}
void GetCrc(void){
    Uint16 c;
    for(c = 0; c <= BYTE_1; c++){
        if(c == 0) sys.uart.pkg.crc.byte.b0 = GetByte();// Зберігаємо отриману контрольну суму
        else sys.uart.pkg.crc.byte.b1 = GetByte();      // Зберігаємо отриману контрольну суму
        sys.uart.pkg.flag = CrcError;                   // діагностика
    }
    sys.uart.pkg.flag = CrcOk;                          // діагностика
    RcvTaskPointer = &GetExt;                           // Прийнятий символ є даними для зчитування, переходимо до процедури перевірки кіця повідомлення
}
void GetExt(void){
    sys.uart.RxChar = GetByte();                        // Зберігаємо отриманий символ для подальшоо опрацювання
    if(sys.uart.RxChar == yes){                         // Процедурка кіця повідомлення
        sys.uart.pkg.flag = ExtOk;                      // діагностика
        RcvTaskPointer = &CheckCrc;                     // Пререхід до перевірки контрольної суми
        }
    else{
        sys.uart.pkg.flag = ExtError;                   // діагностика
        RcvTaskPointer = &GetAddr;                      // Прийнятий символ не є адресою, повторюємо процедуру прийняття кадру повідомлення
        }
}
void CheckCrc(void){
    if(Crc_16_CCITT(&sys.uart.RxList, sys.uart.pkg.size) == sys.uart.pkg.crc.all){  // Звіряємо контрольні суми вираховану з отриманою

    }
}
*/
