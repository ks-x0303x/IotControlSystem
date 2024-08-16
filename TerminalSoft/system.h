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
// 汎用
#define OFF                                 (0)
#define ON                                  (1)

// デバッグ
#define DEBUG                               (ON)

// GPIO関連
#define PIN_15                              (15)
#define PIN_5                               (5)

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

// *****************************************************************************
// ■ グローバル変数
// *****************************************************************************


#endif // SYSTEM_H