// *****************************************************************************
//  概要
//    : システムの定義ファイルです。
//  備考
//    : 
//  ---------------------------------------------------------------------------
//  No   : 日時      : 内容
//  ---------------------------------------------------------------------------
//  1    :2024/08/16 : 初版
// *****************************************************************************

#ifndef SYSTEM_H
#define SYSTEM_H

// *****************************************************************************
// ■ インクルード
// *****************************************************************************
// #include <stdio.h>
// #include <stdlib.h>
#include <Arduino.h>
#include "driver/timer.h"


// *****************************************************************************
// ■ defines
// *****************************************************************************

// 独自定義
#define Public extern

// 汎用
#define OFF                                 (0)
#define ON                                  (1)

// デバッグ
#define DEBUG                               (OFF)

// GPIO関連
#define PIN_5                               (5)
#define PIN_14                              (14)
#define PIN_15                              (15)

// シリアル関連
#define SERIAL_CLOCK                        (115200)

// taimer関連
#define TIMER_CH                            (1)
#define TIMER_HZ                            (10000000)                          // 10MHz = 100ns
#define TIMER_ON_CALL_INTERVAL_US           (100)                               // [us]
#define TIMER_ON_CALL_INTERVAL_VALUE        (TIMER_ON_CALL_INTERVAL_US * 10)    // [us]→[100ns]

// 赤外線受信機関連
#define IR_RECEIVE_PIN PIN_15
#define INFRARED_TIMER_CH                    (0)

// app関連
#define DELAY_TIME                          (500)
#define TIME_1S_100US                       (10000)
#define TIME_1MS_100US                      (10)

// *****************************************************************************
// ■ 構造体
// *****************************************************************************

typedef struct on_time
{
    unsigned long Second;
    unsigned long MilliSecond;
}on_time;


typedef struct application
{
    on_time Time;
}application;


// *****************************************************************************
// ■ グローバル変数
// *****************************************************************************

Public application App;

#endif // SYSTEM_H