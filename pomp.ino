
#define PIN_RELAY 5 // пин для подключения реле
#define PIN_DT_WATER 3// пин подключения микровыключателя
#define TIME_TO_WORK 20000 //время включения реле в мс

#include "GyverButton.h"
#include "GyverTimer.h" 

GTimer myTimer(MS); 
GButton dtWater(PIN_DT_WATER);

boolean isStartTimer = false;


void setup()
{
  Serial.begin(9600);
  while (!Serial);
  pinMode(PIN_RELAY, OUTPUT); // Объявляем пин реле как выход
  digitalWrite(PIN_RELAY, LOW); // Выключаем реле - посылаем низкий сигнал
  myTimer.setTimeout(TIME_TO_WORK); 
  myTimer.stop();
  Serial.println("init");
}

void loop()
{
  dtWater.tick();
  goOutWater();
  if (dtWater.isHolded()& !isStartTimer) {
      Serial.println("holded");
      myTimer.start();
      isStartTimer = true;
  }
  if (myTimer.isReady()){
      Serial.println("timer stop");
      myTimer.stop();
      isStartTimer = false;
  }
}

void goOutWater(){
  if (isStartTimer) {
    digitalWrite(PIN_RELAY, HIGH);  
  } else {
    digitalWrite(PIN_RELAY, LOW); 
  }
  
}
