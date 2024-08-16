// *****************************************************************************
//  概要
//    : 赤外線通信を制御クラスのソースファイルです。
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
#include "Infrared.h"
#include<string.h>

#if DEBUG
unsigned long debug_time[BUF_SIZE];
unsigned long startTime = 0;
unsigned long endTime = 0;
#endif

// *****************************************************************************
// ■ InfraredInfoクラス
// *****************************************************************************

//-----------------------------------------
// 関数名　： InfraredInfo
// 引数　　： -
// 戻値　　： -
// 備考　　：
//-----------------------------------------
InfraredInfo::InfraredInfo()
{
    memset(this->SignalBuffer, 0, sizeof(this->SignalBuffer));
    memset(this->Time50usBuffer, 0, sizeof(this->Time50usBuffer));
    this->Index = 0;
}

// *****************************************************************************
// ■ InfraredControllerクラス
// *****************************************************************************

//-----------------------------------------
// 関数名　： InfraredController
// 引数　　： ピン
// 戻値　　： -
// 備考　　：
//-----------------------------------------
InfraredController::InfraredController(int pin)
{
    this->pinNo = pin;
}

//-----------------------------------------
// 関数名　： Initialize
// 引数　　： -
// 戻値　　： -
// 備考　　：
//-----------------------------------------
void InfraredController::Initialize()
{
    memset(debug_time, 0, sizeof(debug_time));
    this->SignalTime = 0;
    this->signalTimeOut = TIME_OUT_MS * (1000 / TIMER_INTERVAL_US);
    this->Signal = OFF;
    this->IsReceive = OFF;
    // GPIOピンを入力モードに設定
    pinMode(this->pinNo, INPUT);
    this->timer = timerBegin(TIMER_HZ);
    if(this->timer == NULL)
        return;
    // タイマーの割り込みを登録
    timerAttachInterruptArg(this->timer, InfraredController::OnTimerCallback, (void*)this);
    // 1秒(1000000us)ごとにタイマーを発生させる
    timerAlarm(this->timer, TIMER_INTERVAL_VALUE, true, INFRARED_TIMER_CH);
    
}

//-----------------------------------------
// 関数名　： Initialize
// 引数　　： -
// 戻値　　： -
// 備考　　：
//-----------------------------------------
void InfraredController::ReceiveProcess()
{
    unsigned char preSignal = OFF;
    this->SignalTime = 0;
    this->Info.Index = 0;
    if(this->Signal == OFF)
    {
        Serial.println("受信");
        InfraredInfo info;
        this->IsReceive = ON;
        while(this->SignalTime < this->signalTimeOut)
        {   
#if DEBUG
            // 処理の開始時間を記録
            startTime = micros();
#endif
            if(preSignal != this->Signal)
            {
                preSignal = this->Signal;
                this->SignalTime = 0;
                info.Index++;
            }
            info.SignalBuffer[info.Index] = this->Signal;
            info.Time50usBuffer[info.Index] = this->SignalTime;
#if DEBUG
            // 処理の終了時間を記録
            endTime = micros();
            debug_time[info.Index] = endTime - startTime;
#endif
        }
        this->Info = info;
        this->IsReceive = OFF;

#if DEBUG
        unsigned long sumTime = 0;
        unsigned long sumSignal = 0;
        unsigned long procAveTime = 0;
        unsigned long procMaxTime = 0;
        Serial.print("Signal = [");
        for(int i = 0; i < BUF_SIZE; i++)
        {
            sumSignal += this->Info.SignalBuffer[i];
            Serial.print(this->Info.SignalBuffer[i]);
            Serial.print(", ");
        }
        Serial.println("]");

        Serial.print("Time = [");
        for(int i = 0; i < BUF_SIZE; i++)
        {
            sumTime += this->Info.Time50usBuffer[i];
            Serial.print(this->Info.Time50usBuffer[i]);
            Serial.print(", ");

            procAveTime += debug_time[i];
            if(procMaxTime < debug_time[i])
                procMaxTime = debug_time[i];
        }
        Serial.println("]");
        Serial.print("Sum Signal = ");
        Serial.println(sumSignal);
        Serial.print("Sum Time = ");
        Serial.println(sumTime);
        Serial.print("Proc max Time = ");
        Serial.println(procMaxTime);
        Serial.print("Proc ave Time = ");
        Serial.println(procAveTime / this->Info.Index);

#endif
    }
}

//-----------------------------------------
// 関数名　： GetinNo
// 引数　　： -
// 戻値　　： Pin
// 備考　　：
//-----------------------------------------
unsigned char InfraredController::GetPinNo()
{
    return this->pinNo;
}

//-----------------------------------------
// 関数名　： OnTimerCallback
// 引数　　： -
// 戻値　　： -
// 備考　　：
//-----------------------------------------
void IRAM_ATTR InfraredController::OnTimerCallback(void *arg)
{
    InfraredController* controller = (InfraredController*)arg;
    if(controller->IsReceive)
        controller->SignalTime++;
    controller->Signal = (int)digitalRead(controller->GetPinNo());
}