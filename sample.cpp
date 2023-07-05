#include <Arduino.h>

const int dir = 4;      //モーター回転方向
const int pwm = 0;      //モーター速度
const int pwmch = 0;    //PWMチャンネル

void mrun(int t);       //モーターを動かす関数のプロトタイプ宣言

void setup(){
    pinMode(dir, OUTPUT);
    pinMode(pwm, OUTPUT);

    ledcSetup(pwmch, 20000, 8);
    ledcAttachPin(pwm, pwmch);
}

void loop(){
    const int t = 10;           // [ms]
    digitalWrite(dir, HIGH);    //正転
    mrun(t);
    digitalWrite(dir, LOW);     //逆転
    mrun(t);
    ledcWrite(pwmch, 0);        //停止
    delay(5000);
}

void mrun(int t){                       //だんだん加速して、だんだん減速する
    const int resolution = 256;         //PWMは256段階
    for (int i = 0; i < resolution; ++i){
        ledcWrite(pwmch, i / resolution);  //i/256の出力が行われる
        delay(t);
    }
    for (int i = resolution; i > 0; --i){
        ledcWrite(pwmch, i / resolution);
        delay(t);
    }
}