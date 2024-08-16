// *****************************************************************************
//  概要
//    : エントリーポイントです
//  備考
//    : 
//  ---------------------------------------------------------------------------
//  No   : 日時      : 内容
//  ---------------------------------------------------------------------------
//  1    :2024/08/16 : 初版
// *****************************************************************************

// *****************************************************************************
// ■ インクルード
// *****************************************************************************
#include "system.h"
#include "Infrared.h"
#include "Panel.h"

// *****************************************************************************
// ■ グローバル変数
// *****************************************************************************
hw_timer_t *g_timer = NULL;
unsigned long g_time_100us = 0;

application App;
InfraredController infraredController(PIN_15);
PanelController panelController;

// *****************************************************************************
// ■ 関数
// *****************************************************************************

//-----------------------------------------
// 関数名　： setup
// 引数　　： -
// 戻値　　： -
// 備考　　：
//-----------------------------------------
void setup() {
  Serial.begin(SERIAL_CLOCK);
  pinMode(PIN_5, OUTPUT);

  // シリアルモニターに"Hello"を表示
  Serial.println("Hello");

  // 0番のタイマーを80MHzのクロックを使用して初期化
  g_timer = timerBegin(TIMER_HZ);
  if(g_timer == NULL)
    return;
  // タイマーの割り込みを登録
  timerAttachInterrupt(g_timer, &OnTimerCallback);
  // 1秒(1000000us)ごとにタイマーを発生させる
  timerAlarm(g_timer, TIMER_ON_CALL_INTERVAL_VALUE, true, TIMER_CH);

  infraredController.Initialize();
  panelController.Initialize();
}

//-----------------------------------------
// 関数名　： loop
// 引数　　： -
// 戻値　　： -
// 備考　　：
//-----------------------------------------
void loop() {
  static int light = OFF;
  static int buttonState = OFF;
  static int preButtonState = OFF;

  if(g_time_100us >= TIME_1S_100US)
  {
    g_time_100us -= TIME_1S_100US;
    light = ~light;
    digitalWrite(PIN_5, light);
    // Serial.print("Power on time = ");
    // Serial.println(App.Time.Second);
  }
  panelController.MainProcess();
  infraredController.ReceiveProcess();
}

// *****************************************************************************
// ■ コールバック関数
// *****************************************************************************

//-----------------------------------------
// 関数名　： OnTimerCallback
// 引数　　： -
// 戻値　　： -
// 備考　　： 100us周期
//-----------------------------------------
IRAM_ATTR void OnTimerCallback()
{
  g_time_100us++;

  if((g_time_100us % TIME_1MS_100US) == 0)
    App.Time.MilliSecond++;

  if((g_time_100us % TIME_1S_100US) == 0)
    App.Time.Second++;
}