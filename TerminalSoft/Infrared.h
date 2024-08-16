// *****************************************************************************
//  概要
//    : 赤外線通信を制御クラスのヘッダーファイルです。
//  備考
//    : 
//  ---------------------------------------------------------------------------
//  No   : 日時      : 内容
//  ---------------------------------------------------------------------------
//  1    :2024/08/16 : 初版
// *****************************************************************************

#ifndef INFRARED_H
#define INFRARED_H

// *****************************************************************************
// ■ インクルード
// *****************************************************************************
#include "system.h"

// *****************************************************************************
// ■ defines
// *****************************************************************************
#define BUF_SIZE                  (512)
#define TIME_OUT_MS               (10)      // [ms]
#define TIMER_INTERVAL_US         (15)      // [us]
#define TIMER_INTERVAL_VALUE      (TIMER_INTERVAL_US * 10)    // [us]→[100ns]

// *****************************************************************************
// ■ クラス
// *****************************************************************************

class InfraredInfo
{
  public:

  InfraredInfo();

  // member
  unsigned char SignalBuffer[BUF_SIZE];
  unsigned short Time50usBuffer[BUF_SIZE];
  unsigned char Index;

  private:
};

class InfraredController
{
  public:

   InfraredController(int pin);

  // member
  InfraredInfo Info;

  unsigned char Signal;

  unsigned char IsReceive;

  unsigned short SignalTime;

  // func
  void Initialize();

  void ReceiveProcess();

  void SendProcess();

  unsigned char GetPinNo();

  static void IRAM_ATTR OnTimerCallback(void *arg);

  private:

  // member
  unsigned char pinNo;

  hw_timer_t *timer;

  unsigned short signalTimeOut;

  // func


};

#endif // INFRARED_H