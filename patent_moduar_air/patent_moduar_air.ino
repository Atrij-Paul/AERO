#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN D4
#define buzzer D5
#define S0 D1
#define S1 D2
#define S2 D3
#define GREEN D7
#define RED D6
#define analogpin A0

int MQ2=0;
int MQ5=0;
int MQ7=0;
int MQ8=0;
int MQ135=0;

int mq2_limit=700;
int mq5_limit=700;
int mq7_limit=700;
int mq8_limit=700;
int mq135_limit=700;

char auth[] = "CbA3LFSJ-rsxH2Fzq4QIMdElUPrg874J";
char ssid[] = "IEM IEDC LAB";
char pass[] = "IEMIEDC501";

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  if(isnan(h)||isnan(t)){
    Serial.println("Failed to read from DHT");
    return;
  }
  
  Blynk.virtualWrite(V0,t);
  Blynk.virtualWrite(V1,h);
  Blynk.virtualWrite(V2,MQ2);
  Blynk.virtualWrite(V3,MQ5);
  Blynk.virtualWrite(V4,MQ7);
  Blynk.virtualWrite(V5,MQ8);
  Blynk.virtualWrite(V6,MQ135);
  
}

void setup()
{
  Serial.begin(115200);

  Blynk.begin(auth,ssid,pass);

  dht.begin();
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(A0,INPUT);
  timer.setInterval(1000L,sendSensor);
}

void loop()
{
  //Address 000
  digitalWrite(S0,LOW);
  digitalWrite(S1,LOW);
  digitalWrite(S2,LOW);
  MQ2=analogRead(analogpin);
  Serial.print("Gas - ");
  Serial.println(MQ2);
  if (mq2_limit<MQ2)
  {
    digitalWrite(buzzer, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    Serial.print("Gas - ");
    Serial.println(MQ2);
    Blynk.notify("Alert Methane, Butane, LPG, smoke level High");
    Blynk.email("udaysankar2003@gmail.com","MQ2","Alert Methane, Butane, LPG, smoke level High");
  }
  
  //Address 001
  digitalWrite(S0,LOW);
  digitalWrite(S1,LOW);
  digitalWrite(S2,HIGH);
  MQ5=analogRead(analogpin);
  Serial.print("Gas1 - ");
  Serial.println(MQ5);
  if (mq5_limit<MQ5){
    digitalWrite(buzzer, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    Serial.print("Gas - ");
    Serial.println(MQ5);
    Blynk.notify("Alert  Natural gas, LPG Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ5","Alert Natural gas, LPG level High");
  }
  else{
    digitalWrite(buzzer, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  }
  
  //Address 010
  digitalWrite(S0,LOW);
  digitalWrite(S1,HIGH);
  digitalWrite(S2,LOW);
  MQ7=analogRead(analogpin);
  Serial.print("Gas2 - ");
  Serial.println(MQ7);
   if ( mq7_limit<MQ7)
  {
    digitalWrite(buzzer, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    Serial.print("Gas - ");
    Serial.println(MQ7);
    Blynk.notify("Alert Carbon Monoxide Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ7","Alert Carbon Monoxide Level High");
  }
  else{
    digitalWrite(buzzer, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  }
  
    //Address 011
  digitalWrite(S0,LOW);
  digitalWrite(S1,HIGH);
  digitalWrite(S2,HIGH);
  MQ8=analogRead(analogpin);
  Serial.print("Gas2 - ");
  Serial.println(MQ8);
   if (mq8_limit<MQ8)
  {
    digitalWrite(buzzer, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    Serial.print("Gas - ");
    Serial.println(MQ8);
    Blynk.notify("Alert Hydrogen Gas Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ8","Alert Hydrogen Gas Level High");
  }
  else{
    digitalWrite(buzzer, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  }
  
    //Address 100
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(S2,LOW);
  MQ135=analogRead(analogpin);
  Serial.print("Gas2 - ");
  Serial.println(MQ135);
   if (mq135_limit<MQ135)
  {
    digitalWrite(buzzer, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    Serial.print("Gas - ");
    Serial.println(MQ135);
    Blynk.notify("Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
    Blynk.email("udaysankar2003@gmail.com","MQ7","Alert CO, Ammonia, Benzene, Alcohol, smoke Level High");
  }
  else{
    digitalWrite(buzzer, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  }
  
  
  Blynk.run();
  timer.run();
  
}
