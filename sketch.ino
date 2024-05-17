#include <LiquidCrystal_I2C.h>
#include <DHT.h> 
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
DHT dht(5, DHT22);
float temperature ;
float  humidity;
int counter;

LiquidCrystal_I2C lcd(0x27, 20, 4);

int relay1=2;
int relay2=4;
int relay3=15;
String data;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  lcd.setCursor(7,0);
  lcd.print("renu");
  lcd.setCursor(4,1);
  lcd.print("kavya");
  lcd.setCursor(3,2);
  lcd.print("sindhu");
  delay(1500);
  lcd.clear();
   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  }
void loop()
 {
   relaycontrol();
  htvalues();
  rtcstatus();
  }
  void relaycontrol()
 {
  if(Serial.available()>0)
  {
    data=Serial.readString();
    Serial.println(data);
    data.trim();
   
    if(data== "motor1 on")
    {
      digitalWrite(relay1, HIGH);
    }
    if(data=="motor1 off")
    {
      digitalWrite(relay1, LOW);
    }
     if(data== "motor2 on")
    {
      digitalWrite(relay2, HIGH);
    }
    if(data=="motor2 off")
    {
      digitalWrite(relay2, LOW);
    }
     if(data== "motor3 on")
    {
      digitalWrite(relay3, HIGH);
    }
    if(data=="motor3 off")
    {
      digitalWrite(relay3, LOW);
    }
    
  }
}
void htvalues()
{
  
   temperature  = dht.readTemperature();
  humidity     = dht.readHumidity();
  Serial.println("Data: "+ String(counter));
  // Print the values of temperature in Celsus
  Serial.print("Temperatue:\t");
  Serial.print(dht.readTemperature(false));
  Serial.println("C");
   // Print the values of temperature in Fahrenheit
  Serial.print("Temperatue:\t");
  Serial.print(dht.readTemperature(true));
  Serial.println("F");
  // print Humidity in perscent 
  Serial.println("Humidity: \t"+String(humidity)+ "%");
  // Print the values of the heat Index for both Units
  Serial.print("Heat Index In Celsus: ");
  Serial.println(dht.computeHeatIndex(temperature, humidity, false));
  
  Serial.print("Heat Index In Fahrenheit: ");
  Serial.println(dht.computeHeatIndex(temperature, humidity, true));
  Serial.println(" ");
  delay(1000);
  lcd.setCursor(6,0);
  lcd.print("temp=");
  lcd.print(temperature);
  lcd.setCursor(6,1);
  lcd.print("hum=");
  lcd.print(humidity); // this speeds up the simulation
  counter++;
}
void rtcstatus()
{
   DateTime time = rtc.now();

 //Full Timestamp
 Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+time.timestamp(DateTime::TIMESTAMP_FULL));
 //Date Only
 Serial.println(String("DateTime::TIMESTAMP_DATE:\t")+time.timestamp(DateTime::TIMESTAMP_DATE));
 //Full Timestamp
 Serial.println(String("DateTime::TIMESTAMP_TIME:\t")+time.timestamp(DateTime::TIMESTAMP_TIME));
 Serial.println("\n");
 lcd.setCursor(0,1);
  lcd.print("time.timestamp(DateTime::TIMESTAMP_FULL");
  lcd.setCursor(0,2);
  lcd.print("time.timestamp(DateTime::TIMESTAMP_DATE");

 //Delay 5s
 delay(500);
}
