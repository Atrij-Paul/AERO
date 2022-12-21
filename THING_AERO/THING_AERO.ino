#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
//#include <DHT.h>
#include <SPI.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
 
char auth[] = "CbA3LFSJ-rsxH2Fzq4QIMdElUPrg874J";
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
BlynkTimer timer;

/*
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
*/
int gas_limit=700;
 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors
 
int firstVal, secondVal,thirdVal,fourthVal,fifthVal,sixthVal,seventhVal,eighthVal; // sensors 
void myTimerEvent(){
 Blynk.virtualWrite(V1, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(9600); 
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  Blynk.begin(auth, ssid, pass);
    // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
 //  dht.begin();
    timer.setInterval(1000L,sensorvalue1); 
     timer.setInterval(1000L,sensorvalue2);
     timer.setInterval(1000L,sensorvalue3);
     timer.setInterval(1000L,sensorvalue4);
     timer.setInterval(1000L,sensorvalue5);
     timer.setInterval(1000L,sensorvalue6);
     timer.setInterval(1000L,sensorvalue7);
     timer.setInterval(1000L,sensorvalue8);
    // timer.setInterval(1000L,sendSensor);    
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
    }
  }
}
//MQ2
void sensorvalue1(){
int sdata_1 = firstVal;
  Serial.print("Gas1 -  ");
  Serial.println(sdata_1);
  Blynk.virtualWrite(V2,sdata_1);
  int x = ThingSpeak.writeField(myChannelNumber, 1, sdata_1, myWriteAPIKey); //data sent to thingspeak cloud
  /*
  if (gas_limit<sdata_1){
   Serial.print("Gas - ");
   Serial.println(sdata_1);
   Blynk.virtualWrite(V2,sdata_1);
   Blynk.notify("Alert Methane, Butane, LPG, smoke level High");
   Blynk.email("udaysankar2003@gmail.com","MQ2","Alert Methane, Butane, LPG, smoke level High");
  } */
}

//MQ3
void sensorvalue2(){
int sdata_2 = secondVal;
  Blynk.virtualWrite(V3,sdata_2);
  Serial.print("Gas2 - ");
  Serial.println(sdata_2);
  int x = ThingSpeak.writeField(myChannelNumber, 2, sdata_2, myWriteAPIKey); //data sent to thingspeak cloud
  /*
  if (gas_limit<sdata_2){
    Blynk.virtualWrite(V3,sdata_2);
    Serial.print("Gas1 - ");
    Serial.println(sdata_2);
   Blynk.notify("Alert  Natural gas, LPG Level High");
   Blynk.email("udaysankar2003@gmail.com","MQ5","Alert Natural gas, LPG level High");
  } */
}

//MQ4
void sensorvalue3(){
int sdata_3 = thirdVal;
  Blynk.virtualWrite(V4,sdata_3);
  Serial.print("Gas3 - ");
  Serial.println(sdata_3);
  int x = ThingSpeak.writeField(myChannelNumber, 3, sdata_3, myWriteAPIKey); //data sent to thingspeak cloud
  /*
   if (gas_limit<sdata_3)
  {
    Blynk.virtualWrite(V4,sdata_3);
    Serial.print("Gas2 - ");
    Serial.println(sdata_3);
  Blynk.notify("Alert Carbon Monoxide Level High");
  Blynk.email("udaysankar2003@gmail.com","MQ7","Alert Carbon Monoxide Level High");
  } */
}
//MQ5
void sensorvalue4(){
int sdata_4 = fourthVal;
  Blynk.virtualWrite(V5,sdata_4);
  Serial.print("Gas4 - ");
  Serial.println(sdata_4);
  int x = ThingSpeak.writeField(myChannelNumber, 4, sdata_4, myWriteAPIKey); //data sent to thingspeak cloud
  /*
   if (gas_limit<sdata_4)
  {
     Blynk.virtualWrite(V5,sdata_4);
    Serial.print("Gas3 - ");
    Serial.println(sdata_4);
   Blynk.notify("Alert  Natural gas, LPG Level High");
   Blynk.email("udaysankar2003@gmail.com","MQ5","Alert Natural gas, LPG level High");;
  } */
}

//MQ7
void sensorvalue5(){
int sdata_5 = fifthVal;
  Blynk.virtualWrite(V6,sdata_5);
  Serial.print("Gas5 - ");
  Serial.println(sdata_5);
  int x = ThingSpeak.writeField(myChannelNumber, 5, sdata_5, myWriteAPIKey); //data sent to thingspeak cloud
  /*
   if (gas_limit<sdata_5)
  {
      Blynk.virtualWrite(V6,sdata_5);
      Serial.print("Gas4 - ");
    Serial.println(sdata_5);
  Blynk.notify("Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
   Blynk.email("udaysankar2003@gmail.com","MQ7","Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
  }  */
}

//MQ8
void sensorvalue6(){
int sdata_6 = sixthVal;
Blynk.virtualWrite(V8,sdata_6);
  Serial.print("Gas6 - ");
  Serial.println(sdata_6);
  int x = ThingSpeak.writeField(myChannelNumber, 6, sdata_6, myWriteAPIKey); //data sent to thingspeak cloud
  /*
   if (gas_limit<sdata_6)
  {
      Blynk.virtualWrite(V9,sdata_6);
      Serial.print("Gas6 - ");
    Serial.println(sdata_6);
 Blynk.notify("Alert Hydrogen Gas Level High");
  Blynk.email("udaysankar2003@gmail.com","MQ8","Alert Hydrogen Gas Level High");
  } */
}

//MQ9
void sensorvalue7(){
int sdata_7 = seventhVal;
Blynk.virtualWrite(V8,sdata_7);
  Serial.print("Gas7 - ");
  Serial.println(sdata_7);
  int x = ThingSpeak.writeField(myChannelNumber, 7, sdata_7, myWriteAPIKey); //data sent to thingspeak cloud
  /*
   if (gas_limit<sdata_7)
  {
      Blynk.virtualWrite(V9,sdata_7);
      Serial.print("Gas7 - ");
    Serial.println(sdata_7);
  Blynk.notify("Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
  Blynk.email("udaysankar2003@gmail.com","MQ9","Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
  }*/
}

//MQ135
void sensorvalue8(){
int sdata_8 = eighthVal;
  Blynk.virtualWrite(V8,sdata_8);
  Serial.print("Gas8 - ");
  Serial.println(sdata_8);
  int x = ThingSpeak.writeField(myChannelNumber, 8, sdata_8, myWriteAPIKey); //data sent to thingspeak cloud
  /*
   if (gas_limit<sdata_8)
  {
      Blynk.virtualWrite(V9,sdata_5);
      Serial.print("Gas8 - ");
    Serial.println(sdata_8);
  Blynk.notify("Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
 Blynk.email("udaysankar2003@gmail.com","MQ7","Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
  } */
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
