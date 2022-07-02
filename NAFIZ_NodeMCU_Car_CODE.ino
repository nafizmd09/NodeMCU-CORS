//Nafiz Md Imtiaz Uddin
//ID: 2520190011 - CST2019 [江西理工大学]
/*Micro-USB: NodeMCU can be powered through the USB port
3.3V: Regulated 3.3V can be supplied to this pin to power the board
GND: Ground pins
Vin: External Power Supply*/

#define ENA   14          
#define ENB   12          
#define IN_1  15         
#define IN_2  13          
#define IN_3  2         
#define IN_4  0         

#include <ESP8266WiFi.h> 
//This library provides ESP8266 specific Wi-Fi routines
#include <WiFiClient.h>  
//Library for Arduino Wifi shield
#include <ESP8266WebServer.h>
//simple web-server. Supports only one simultaneous client, 
//knows how to handle GET and POST

String injunction;            
int robot_car = 900;         // 400 - 1023.[Speed of car]
int SpeedCoefficient = 3;

const char* ssid = "NodeMCU Nafiz"; //Wifi name
const char* password = "Nafiz_2022"; //Enter Password
ESP8266WebServer server(80);
void setup() {
 pinMode(ENA, OUTPUT); 
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
 Serial.begin(115200);//Sets the data rate in bits per second (baud)  for serial data transmission. 
 //For USB baudrate is fixed on 115200 bps

// Now we connecting wifi system
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("IP address is ");
  Serial.println(myIP);
 
 // Now we start the WEB-server 
     server.on ( "/", HTTP_handleRoot ); //
     server.onNotFound ( HTTP_handleRoot ); //if not found wifi
     server.begin();//Tells the server to begin listening for incoming connections    
}

//Forward funtion
void Forward_func(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, robot_car);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, robot_car);
  }
  
//Backward funtion
void back_func(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, robot_car);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, robot_car);
  }

////Right button funtion
void right_func(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, robot_car);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, robot_car);
  }

////Left button funtion
void left_func(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, robot_car);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, robot_car);
  }

void Forward_funcRight(){   
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, robot_car/SpeedCoefficient);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, robot_car);
   }

void Forward_funcLeft(){
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, robot_car);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, robot_car/SpeedCoefficient);
  }

void back_funcRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, robot_car/SpeedCoefficient);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, robot_car);
  }

void back_funcLeft(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, robot_car);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, robot_car/SpeedCoefficient);
  }

void stopCar(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, robot_car);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, robot_car);
 }

void loop() {
    server.handleClient();
    
      injunction = server.arg("State");
      if (injunction == "F") Forward_func();
      else if (injunction == "B") back_func();
      else if (injunction == "L") left_func();
      else if (injunction == "R") right_func();
      else if (injunction == "I") Forward_funcRight();
      else if (injunction == "G") Forward_funcLeft();
      else if (injunction == "J") back_funcRight();
      else if (injunction == "H") back_funcLeft();
      else if (injunction == "0") robot_car = 500;
      else if (injunction == "1") robot_car = 490;
      else if (injunction == "2") robot_car = 640;
      else if (injunction == "3") robot_car = 610;
      else if (injunction == "4") robot_car = 780;
      else if (injunction == "5") robot_car = 790;
      else if (injunction == "6") robot_car = 820;
      else if (injunction == "7") robot_car = 990;
      else if (injunction == "8") robot_car = 860;
      else if (injunction == "9") robot_car = 1021;
      else if (injunction == "S") stopCar();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "index/html", "" );
  delay(1);
}
