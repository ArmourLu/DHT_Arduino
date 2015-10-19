
#include <dht.h>

#define led_dpin 13             //LED PIN
#define Interval_Read     1000  //1000ms
#define en_LED            1

int dht_dpin[] = {2,3,4};        //Data from Pin 2-4
dht DHT;
int time_tick = 0;

void setup() {
  Serial.begin(115200);
  delay(300);             //Let system settle
  //Serial.println("Humidity and temperature\n\n");
  if (en_LED) pinMode(led_dpin, OUTPUT);
  delay(700);             //Wait rest of 1000ms recommended delay before accessing sensor
}

void loop() {

  int DHT_Status = 0;
  int i;
  for(i=0;i<3;i++)
  {
    if (DHT.read22(dht_dpin[i]) == 0)
    {
      Serial.print("H:");
      Serial.print(DHT.humidity);
      Serial.print("%,");
      Serial.print("T:");
      Serial.print(DHT.temperature);
      Serial.print("C");
    }
    else
    {
      Serial.print("H:--%,");
      Serial.print("T:--C,");
      DHT_Status = 1;
    }
  }

  Serial.println();

  if (en_LED) {
    if (time_tick == 0 && DHT_Status == 0) digitalWrite(led_dpin, HIGH);
    else digitalWrite(led_dpin, LOW);
  }

  if (time_tick) time_tick = 0;
  else time_tick = 1;

  delay(Interval_Read);
}
