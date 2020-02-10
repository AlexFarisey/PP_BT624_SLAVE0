/*
 * InitSci.c
 *
 *  Created on: 22 СЃРµСЂРї. 2019 СЂ.
 *      Author: РЎР°РЅСЏ
 */
#ifndef SOURCEINCLUDE_INITSCI_H_
#define SOURCEINCLUDE_INITSCI_H_

#include "DSP280x_Device.h"     // DSP28 Headerfile Include File

void InitScilHost(Uint16 n, Uint32 speed){
     volatile struct SCI_REGS *SCI[] ={
          &SciaRegs,
          &SciaRegs,
          &ScibRegs
    };
     /*******************************************************************************/
     //                             параметри повідомлення
     /*******************************************************************************/
         SCI[n]->SCICCR.bit.SCICHAR = 7;                                       //  0:2 Контроль довжини символів
     //                                                                                |                  SCI CHAR2−0 Bit Values (Binary)                      |
     //                                                                                |-----------------------------------------------------------------------|
     //                                                                                |   Код   | SCI CHAR2 | SCI CHAR1 | SCI CHAR0 | Character Length (Bits) |
     //                                                                                |-----------------------------------------------------------------------|
     //                                                                                |    0    |     0     |     0     |      0    |            1            |
     //                                                                                |    1    |     0     |     0     |      1    |            2            |
     //                                                                                |    2    |     0     |     1     |      0    |            3            |
     //                                                                                |    3    |     0     |     1     |      1    |            4            |
     //                                                                                |    4    |     1     |     0     |      0    |            5            |
     //                                                                                |    5    |     1     |     0     |      1    |            6            |
     //                                                                                |    6    |     1     |     1     |      0    |            7            |
     //                                                                                |    7    |     1     |     1     |      1    |            8            |
         SCI[n]->SCICCR.bit.ADDRIDLE_MODE = 0;                                      //    3 Управління режимами ADDR/IDLE. 0-Idle-line, 1-Address-bit mode
         SCI[n]->SCICCR.bit.LOOPBKENA = 0;                                          //    4 Замикання петлі. 0-test mode disabled, 1-test mode enabled
         SCI[n]->SCICCR.bit.PARITYENA = 1;                                          //    5 Контроль парності паритету.  0-disabled, 1-enabled
         SCI[n]->SCICCR.bit.PARITY = 0;                                             //    6 парний або непарний паритет. 0-Непарний,1-парний
         SCI[n]->SCICCR.bit.STOPBITS = 0;                                           //    7 Кількість стоп-бітів.  0-один,1-два
     /*******************************************************************************/
     //                       Керування лініями вх-вих
     /*******************************************************************************/
         SCI[n]->SCICTL1.bit.RXENA = 1;                                             //    0 Вмикання/вимикання приймача. 0-disabled, 1-enabled
         SCI[n]->SCICTL1.bit.TXENA = 1;                                             //    1 Вмикання/вимикання передавача. 0-disabled, 1-enabled
         SCI[n]->SCICTL1.bit.SLEEP = 0;                                             //    2 SCI sleep. 0-disabled, 1-enabled
         SCI[n]->SCICTL1.bit.TXWAKE = 0;                                            //    3 Метод пробудження передавача. 0-Функція передачі не вибрано, 1-Вибрана функція передачі залежить від режиму ADDR/IDLE
         SCI[n]->SCICTL1.bit.SWRESET = 1;                                           //    5 Скидання програмного забезпечення. 0-disabled, 1-enabled
         SCI[n]->SCICTL1.bit.RXERRINTENA = 0;                                       //    6 Переривання при помилці. 0-disabled, 1-enabled
     /*******************************************************************************/
     //                     Керування перериваннями ліній
     /*******************************************************************************/
         SCI[n]->SCICTL2.bit.TXINTENA = 1;                                          //    0 Переривання передавача. 0-Disable TXRDY interrupt, 1-Enable TXRDY interrupt
         SCI[n]->SCICTL2.bit.RXBKINTENA = 1;                                        //    1 Переривання буфера приймача. 0-Disable RXRDY/BRKDT interrupt, 1-Enable RXRDY/BRKDT interrupt
         SCI[n]->SCICTL2.bit.TXEMPTY = 0;                                           //    6 0-Буфер передавача або регістр зсуву або обидва завантажуються даними
                                                                                     //      1-Буфер передавача і регістри зсуву обидва порожні
         SCI[n]->SCICTL2.bit.TXRDY =0;                                              //    7 0-SCITXBUF повний
     /*******************************************************************************/
     //                              Біт-рейт
     //                  SCI ScibBRR = LSPCLK/(SCI BAUDx8) - 1
     /*******************************************************************************/
         SCI[n]->SCIHBAUD = 0x0000;
         SCI[n]->SCILBAUD = (SysCtrlRegs.LOSPCP.bit.LSPCLK/(speed*8)) - 1;
     /*******************************************************************************/
     //                              FIFO TX
     /*******************************************************************************/
         SCI[n]->SCIFFTX.bit.TXFFIL = 0;                                            //  0:4 Рівень переривання
         SCI[n]->SCIFFTX.bit.TXFFIENA = 0;                                          //    5 Включення переривання
         SCI[n]->SCIFFTX.bit.TXFFINTCLR = 1;                                        //    6 Очистити прапор INT
         SCI[n]->SCIFFTX.bit.TXFFINT = 0;                                           //    7 INT прапор
         SCI[n]->SCIFFTX.bit.TXFFST = 0;                                            // 8:12 FIFO статус
         SCI[n]->SCIFFTX.bit.TXFIFOXRESET = 0;                                      //   13 FIFO reset
         SCI[n]->SCIFFTX.bit.SCIFFENA = 0;                                          //   14 !!!!! Переривання виконуються по: 0-TXINTENA/RXBKINTENA, 1-RXFFIEN/TXFFIENA(FIFO)
         SCI[n]->SCIFFTX.bit.SCIRST = 1;                                            //   15 SCI скидання каналів rx / tx
     //    SCI[n]->SCIFFTX.all=0x8040;                                              //      Reset FIFO ліній rx/tx. Дозвіл роботи FIFO. Скидаєм FIFO. Очищуєм флаги.
     /*******************************************************************************/
     //                              FIFO RX
     /*******************************************************************************/
         SCI[n]->SCIFFRX.bit.RXFFIL = 1;                                            //  0:4 Рівень переривання
         SCI[n]->SCIFFRX.bit.RXFFIENA = 0;                                          //    5 Включення переривання
         SCI[n]->SCIFFRX.bit.RXFFINTCLR = 1;                                        //    6 Очистити прапор INT
         SCI[n]->SCIFFRX.bit.RXFFINT = 0;                                           //    7 INT прапор
         SCI[n]->SCIFFRX.bit.RXFFST = 0;                                            // 8:12 FIFO статус
         SCI[n]->SCIFFRX.bit.RXFIFORESET = 1;                                       //   13 FIFO reset
         SCI[n]->SCIFFRX.bit.RXFFOVRCLR = 0;                                        //   14 Очистити переповнення
         SCI[n]->SCIFFRX.bit.RXFFOVF = 0;                                           //   15 переповнення FIFO
     /*******************************************************************************///    SCI[n]->SCIFFRX.all=0x204f;
         SCI[n]->SCIFFCT.bit.FFTXDLY = 0;                                           //  0:7 FIFO передають затримку
         SCI[n]->SCIFFCT.bit.CDC = 0;                                               //   13 Увімкнення режиму автоматичного набору
         SCI[n]->SCIFFCT.bit.ABDCLR = 0;                                            //   14 Auto baud clear
     /*******************************************************************************/
         SCI[n]->SCIPRI.bit.FREE = 1;                                               //    3 Вільний режим призупинення емуляції
         SCI[n]->SCIPRI.bit.SOFT = 0;                                               //    4 Мякий режим призупинення
    }
#endif /* SOURCEINCLUDE_INITSCI_H_ */
