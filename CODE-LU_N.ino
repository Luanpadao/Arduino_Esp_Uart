#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
FirebaseData dulieufirebase;

String DB,DK,DN,DVS,QB,QKHACH,QKHI,QN;
int x=0;
void setup() {
  Serial.begin(115200);
  ketnoiwifi();
  Firebase.begin("testappesp8266firebase-default-rtdb.firebaseio.com","l1JbgPw9XsATqjEhPizk9TjhkRE3SyyhwA0lE5cr"); 
}
StaticJsonBuffer<1000> jsonBuffer;
void loop() 
{
  //-------------------------------y tuong 1
//  if(x==0)
//  {
//    nhanData();
//  }
//  if(x==1)
//  {
//    check_data_firebase();
//    delay(1500);
//    x=0;
//  }
//---------------------------------test nhan du lieu cam bien
//  nhanData();
//--------------------------------test_nguoc lai: gui du lieu dk thiet bi
//check_data_firebase();
//--------------------------------- y tuong 2
//  if(x==0)
//  {
//    nhanData();
//  }
//  if(x==1)
//  {
//    check_data_firebase();
//    x=0;
//  }
//---------------------------------y tuong 3
//  nhanData();
//  delay(200);
//  check_data_firebase();
//  delay(1000);
//------------------------------------y tuong 4
  if(Serial.readString()=="ok\r\n")
    {
      Serial.println("a");
      x=1;
    }
  else if(x==0)
  {
  check_data_firebase();
  }
  if (x==1)
  {
    nhanData();
  }
  else if(x==2)
  {
    delay(200);
    Serial.println("ko");
    x=0;
    delay(5);
  } 
}
//------------------------------------ket noi wifi
void ketnoiwifi()
{
  WiFi.begin("Co Hong ( p.lanh)","123467890");
  while (!(WiFi.status() == WL_CONNECTED))
  {
    delay(500);
    Serial.print("...");
  }
    Serial.print("");
    Serial.println("ket noi thanh cong");
}
//------------------------------------------gui du lieu qua Arduino
void check_data_firebase()
{
  if(Firebase.getInt(dulieufirebase,"/DEN-BEP"))
    DB = dulieufirebase.stringData();
  
  if(Firebase.getInt(dulieufirebase, "/DEN-KHACH"))
    DK = dulieufirebase.stringData();

   if(Firebase.getInt(dulieufirebase, "/DEN-NGU"))
    DN = dulieufirebase.stringData();

    if(Firebase.getInt(dulieufirebase, "/DEN-VSINH"))
    DVS = dulieufirebase.stringData();
  
    if(Firebase.getInt(dulieufirebase, "/QUAT-BEP"))
    QB = dulieufirebase.stringData();

   if(Firebase.getInt(dulieufirebase, "/QUAT-KHACH"))
    QKHACH = dulieufirebase.stringData();

   if(Firebase.getInt(dulieufirebase, "/QUAT-KHI"))
    QKHI = dulieufirebase.stringData();

   if(Firebase.getInt(dulieufirebase, "/QUAT-NGU"))
    QN = dulieufirebase.stringData();
    
  JsonObject& root1 = jsonBuffer.createObject();
  root1["DEN_KHACH"] = DK;
  root1["DEN_BEP"] = DB;
  root1["DEN_NGU"] = DN;
  root1["DEN_VESINH"] = DVS;
  root1["QUAT_BEP"] = QB;
  root1["QUAT_KHACH"] = QKHACH;
  root1["QUAT_NGU"] = QN;
  root1["y"] = 1;
  if(!Serial.available()) //nếu dữ liệu kh có sẵn thì gửi biến root1 ra cổng com
  {
    root1.printTo(Serial);
    Serial.println("");
  }
  jsonBuffer.clear(); // xóa dữ liệu trong bộ nhớ jsonbuffer
}
//-------------------------------------------nhan du lieu tu arduino
void nhanData()
 {
  JsonObject& root = jsonBuffer.parseObject(Serial); // nhận dữ liệu (parse) từ biến root kiểu dữ liệu json object
  if (root == JsonObject::invalid()) // nếu root kh có giá trị thì sẽ trả về giá trị lưu trước đó;
  return;
  root.prettyPrintTo(Serial); // Cho phép nhận dữ liệu root từ cổng com
  float data1 = root["temp"];
  float data2 = root["hum"];
  float data3 = root["gas"];
  x = root["x"];
  Firebase.setFloat(dulieufirebase,"/Nhietdo",data1);
  Firebase.setFloat(dulieufirebase,"/Doam",data2);
  Firebase.setFloat(dulieufirebase,"/gas",data3);
  jsonBuffer.clear();
 }
