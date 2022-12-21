#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <SPI.h>
 
char auth[] = "CbA3LFSJ-rsxH2Fzq4QIMdElUPrg874J";
char ssid[] = "IEM IEDC LAB";
char pass[] = "IEMIEDC501";
 
BlynkTimer timer;
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void sendSensor()
{
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  if(isnan(h)||isnan(t)){
    Serial.println("Failed to read from DHT");
    return;
  }
  Blynk.virtualWrite(V7,t);
  Blynk.virtualWrite(V8,h);
}
int gas_limit=700;


//int Relay = D4; // you can connect a dc or ac water pump
 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors
 
int firstVal, secondVal,thirdVal,fourthVal,fifthVal,sixthVal,seventhVal,eighthVal; // sensors 
// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, millis() / 1000);
  
}

void setup()
{
  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);
   dht.begin();
    timer.setInterval(1000L,sensorvalue1); 
     timer.setInterval(1000L,sensorvalue2);
     timer.setInterval(1000L,sensorvalue3);
     timer.setInterval(1000L,sensorvalue4);
     timer.setInterval(1000L,sensorvalue5);
     timer.setInterval(1000L,sensorvalue6);
     timer.setInterval(1000L,sensorvalue7);
     timer.setInterval(1000L,sensorvalue8);
     timer.setInterval(1000L,sendSensor);    
}
 
void loop()
{
   if (Serial.available() == 0 ) 
   {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
   }
   
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
   //  Serial.println(myString); 
  // Serial.println("fahad");
// new code
String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2); 
String o = getValue(myString, ',', 3); 
String p = getValue(myString, ',', 4); 
String q = getValue(myString, ',', 5);
String r = getValue(myString, ',', 6);
String s = getValue(myString, ',', 7);
 
firstVal = l.toInt();
secondVal = m.toInt();
thirdVal = n.toInt();
fourthVal = o.toInt();
fifthVal = p.toInt();
sixthVal = p.toInt();
seventhVal = p.toInt();
eighthVal = p.toInt();
 
  myString = "";
// end new code
    }
  }
}
//MQ2
void sensorvalue1()
{
int sdata_1 = firstVal;
  Serial.print("Gas - 1 ");
  Serial.println(sdata_1);
  Blynk.virtualWrite(V2,sdata_1);
  if (gas_limit<sdata_1)
  {
    Serial.print("Gas - ");
    Serial.println(sdata_1);
    Blynk.virtualWrite(V2,sdata_1);
    Blynk.notify("Alert Methane, Butane, LPG, smoke level High");
    Blynk.email("udaysankar2003@gmail.com","MQ2","Alert Methane, Butane, LPG, smoke level High");
  }
}
//MQ3
void sensorvalue2()
{
int sdata_2 = secondVal;
  Blynk.virtualWrite(V3,sdata_2);
  Serial.print("Gas1 - ");
  Serial.println(sdata_2);
  if (gas_limit<sdata_2){
    Blynk.virtualWrite(V3,sdata_2);
    Serial.print("Gas1 - ");
    Serial.println(sdata_2);
    Blynk.notify("Alert  Natural gas, LPG Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ5","Alert Natural gas, LPG level High");
  }
}
//MQ4
void sensorvalue3()
{
int sdata_3 = thirdVal;
  Blynk.virtualWrite(V4,sdata_3);
  Serial.print("Gas2 - ");
  Serial.println(sdata_3);
   if (gas_limit<sdata_3)
  {
    Blynk.virtualWrite(V4,sdata_3);
    Serial.print("Gas2 - ");
    Serial.println(sdata_3);
    Blynk.notify("Alert Carbon Monoxide Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ7","Alert Carbon Monoxide Level High");
  }

}
//MQ5
void sensorvalue4()
{
int sdata_4 = fourthVal;
  Blynk.virtualWrite(V5,sdata_4);
  Serial.print("Gas3 - ");
  Serial.println(sdata_4);
   if (gas_limit<sdata_4)
  {
     Blynk.virtualWrite(V5,sdata_4);
    Serial.print("Gas3 - ");
    Serial.println(sdata_4);
    Blynk.notify("Alert  Natural gas, LPG Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ5","Alert Natural gas, LPG level High");;
  }
}
//MQ7
void sensorvalue5()
{
int sdata_5 = fifthVal;
  Blynk.virtualWrite(V6,sdata_5);
  Serial.print("Gas4 - ");
  Serial.println(sdata_5);
   if (gas_limit<sdata_5)
  {
      Blynk.virtualWrite(V6,sdata_5);
      Serial.print("Gas4 - ");
    Serial.println(sdata_5);
    Blynk.notify("Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ7","Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
  }
}
//MQ8
void sensorvalue6()
{
int sdata_6 = sixthVal;
Blynk.virtualWrite(V8,sdata_6);
  Serial.print("Gas6 - ");
  Serial.println(sdata_6);
   if (gas_limit<sdata_6)
  {
      Blynk.virtualWrite(V9,sdata_6);
      Serial.print("Gas6 - ");
    Serial.println(sdata_6);
    Blynk.notify("Alert Hydrogen Gas Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ8","Alert Hydrogen Gas Level High");
  }
}
//MQ9
void sensorvalue7()
{
int sdata_7 = seventhVal;
Blynk.virtualWrite(V8,sdata_7);
  Serial.print("Gas7 - ");
  Serial.println(sdata_7);
   if (gas_limit<sdata_7)
  {
      Blynk.virtualWrite(V9,sdata_7);
      Serial.print("Gas7 - ");
    Serial.println(sdata_7);
    Blynk.notify("Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ9","Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
  }
}
//MQ135
void sensorvalue8()
{
int sdata_8 = eighthVal;
  Blynk.virtualWrite(V8,sdata_8);
  Serial.print("Gas8 - ");
  Serial.println(sdata_8);
   if (gas_limit<sdata_8)
  {
      Blynk.virtualWrite(V9,sdata_5);
      Serial.print("Gas8 - ");
    Serial.println(sdata_8);
    Blynk.notify("Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ7","Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
  }

}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
