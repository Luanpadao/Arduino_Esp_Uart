#include <ArduinoJson.h>
#include <Wire.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 2
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(DHTPIN, DHTTYPE);
int x=0;
int nutNhan = 4;
//float t,h;
//long g;
StaticJsonBuffer<1000>jsonBuffer;
void setup()
{
  Serial.begin(115200);
  dht.begin();
//  lcd.clear();
//  lcd.init();  //khoi dong LCD
//  lcd.backlight(); //mở đèn
  pinMode(13,OUTPUT);   //TB1
  pinMode(12,OUTPUT);   //TB2
  pinMode(11,OUTPUT);   //TB3
  pinMode(10,OUTPUT);   //TB4
  pinMode(9,OUTPUT);   //TB5
  pinMode(8,OUTPUT);   //TB6
  pinMode(7,OUTPUT);   //TB7
  pinMode(6,OUTPUT);   //TB8
  pinMode(nutNhan,INPUT_PULLUP);
  digitalWrite(13,0);
  digitalWrite(12,0);
  digitalWrite(11,0);
  digitalWrite(10,0);
  digitalWrite(9,0);
  digitalWrite(8,0);
  digitalWrite(7,0);
  digitalWrite(6,0); 
}
void loop()
{
  //---------------------------------y tuong 1
//  if(x==0)
//  {
//    Arduino_ESP();
//    in_LCD();
//    delay(1500);
//    x=1;
//  }
//  if(x==1)
//  {
//    ESP_Arduino();
//  }
//--------------------------------------test gui du lieu cam bien
//  Arduino_ESP();
//  in_LCD();
//-------------------------------test_nguoc lai: nhan du lieu dk thiet bi
//      ESP_Arduino();
//-------------------------------------y tuong 2
//  if(x==0)
//  {
//    Arduino_ESP();
//    in_LCD();
//    x=1;
//  }
//  else if(x==1)
//  {
//    ESP_Arduino();
//  }
//--------------------------------------y tuong 3
//  Arduino_ESP();
//  delay(1000);
//  ESP_Arduino();
//  delay(200);
//------------------------------------y tuong 4
  if(x==0)
  {
    ESP_Arduino();
  }
  else if(x==1)
  {
    Serial.println();
    delay(200);
    Serial.println("ok");
    x=2;
    delay(5);
  }
  else if(x==2)
  {
    Arduino_ESP();
    if(Serial.available())
    {
      if(Serial.readString()=="ko\r\n")
        x=0;
    }
  }
}
//---------------------------------------------gui du lieu qua esp
void Arduino_ESP()
{
  JsonObject& root = jsonBuffer.createObject();  
  //doc_cam_bien();
  float t = dht.readTemperature(); // đo nhiệt độ
  float h = dht.readHumidity();    // đo độ ẩm
  long g = analogRead(A0);        // đo khí gas
  root["temp"] = t;
  root["hum"] = h;
  root["gas"] = g;
  root["x"] = 2;
  if (!Serial.available())
  {
   root.printTo(Serial);
   Serial.println();
   delay(1000);
  }
  jsonBuffer.clear();
}
//---------------------------------------nhan du lieu tu esp gui qua arduino
void ESP_Arduino() 
{
  JsonObject& root = jsonBuffer.parseObject(Serial);
    if(root == JsonObject::invalid())
    return;
    root.prettyPrintTo(Serial);
    String data1 = root["DEN_KHACH"];
    String data2 = root["DEN_NGU"];
    String data3 = root["DEN_BEP"];
    String data4 = root["DEN-VESINH"];
    String data5 = root["QUAT_KHACH"];
    String data6 = root["QUAT_NGU"];
    String data7 = root["QUAT_BEP"];
    x = root["y"];
    if(data1 == "1")
      digitalWrite(13,1);
    else
      digitalWrite(13,0);
    
    if(data2 == "1")
      digitalWrite(12,1);
    else
      digitalWrite(12,0);
    
    if(data3 == "1")
      digitalWrite(11,1);
    else
      digitalWrite(11,0);
    
    if(data4 == "1")
      digitalWrite(10,1);
    else
      digitalWrite(10,0);
    
    if(data5 == "1")
      digitalWrite(9,1);
    else
      digitalWrite(9,0);
    
    if(data6 == "1")
      digitalWrite(8,1);
    else
      digitalWrite(8,0);
      
    if(data7 == "1")
      digitalWrite(7,1);
    else
      digitalWrite(7,0);
      
    jsonBuffer.clear();
}
//--------------------------------------------in ra man hinh
//void in_LCD()
//{
//  lcd.setCursor(0,0);  // con trở vị trí 0 hiển thị ô 1
//  lcd.print(t);        // in giá trị nhiệt độ có ( 00.00) chiếm 5 ô
//  lcd.setCursor(5,0);
//  lcd.print(" (C) ");
//  
//  // In độ ẩm ra màn hình LCD
//  lcd.setCursor(10,0);
//  lcd.print(h);
//  lcd.setCursor(15,0);
//  lcd.print("%");
//  
//  // In khí gas ra màn hình LCD
//  lcd.setCursor(0,1);
//  lcd.print("Gas: ");
//  lcd.setCursor(6,1);
//  lcd.print(g);
//  lcd.setCursor(10,1);
//  lcd.print("PPM");
//}
//void doc_cam_bien()
//{
//  
//}
