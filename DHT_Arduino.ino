
#include <dht.h>
#include <LiquidCrystal.h>

#define dht_dpin 2              //Data from Pin 2
#define led_dpin 13             //LED PIN
#define Interval_Read     500   //500ms
#define en_Display        0
#define en_LED            1

dht DHT;
LiquidCrystal lcd(12, 11, 3, 4, 5, 6);  // RS, E, D4, D5, D6, D7 pin of LCD
int time_tick = 0;

void setup() {
  Serial.begin(9600);
  delay(300);             //Let system settle
  //Serial.println("Humidity and temperature\n\n");
  if (en_Display) lcd.begin(16, 2);
  if (en_LED) pinMode(led_dpin, OUTPUT);
  delay(700);             //Wait rest of 1000ms recommended delay before accessing sensor
}

void loop() {

  String str_humidity;
  String str_temperature;
  int DHT_Status = 0;

  if (DHT.read11(dht_dpin) == 0)
  {
    str_humidity = "H:" + String(int(DHT.humidity)) + "%";
    str_temperature = "T:" + String(int(DHT.temperature)) + "C";
  }
  else
  {
    str_humidity = "H:--%";
    str_temperature = "T:--C";
    DHT_Status = 1;
  }

  Serial.println(str_humidity + ", " + str_temperature);

  if (en_Display) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(str_humidity + ", " + str_temperature);
    if (time_tick == 0) lcd.print("_");
  }

  if (en_LED) {
    if (time_tick == 0 && DHT_Status == 0) digitalWrite(led_dpin, HIGH);
    else digitalWrite(led_dpin, LOW);
  }

  if (time_tick) time_tick = 0;
  else time_tick = 1;

  delay(Interval_Read);
}



