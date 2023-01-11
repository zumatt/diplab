/* MIT License 2023 Matteo Subet <hi@zumat.ch>
   
   Alpha Version 0.1 - DiPLaB
   Master Thesis Project from Matteo Subet
   SUPSI MAInD

   Based on Inkplate 6PLUS (ESP32)
*/

/*
    -----------------------------------------------------------
                            LIBRARIES
    -----------------------------------------------------------
*/
#include "Inkplate-mod.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

//The next 5 lines are needed to change the pins for SD Card reader
#define SCK  14
#define MISO  12
#define MOSI  13
#define CS  15
SPIClass spi = SPIClass(VSPI);

/*
    -----------------------------------------------------------
                            VARIABLES
    -----------------------------------------------------------
*/

//Here you can insert your network credentials
const char* ssid = "DiPLab";
const char* password = "AMRawareness23";

//Here you can choose the URI parameters used in the HTML page
const char* PARAM_INPUT_1 = "state";
const char* PARAM_INPUT_2 = "bacteria";
const char* PARAM_INPUT_3 = "ab1";
const char* PARAM_INPUT_4 = "ab2";
const char* PARAM_INPUT_5 = "ab3";

//State variable to check where we are with the experience
int state = 0;

//Variables to display stuff on the E-Ink display
int dispW = 1024;                                         //Display Width
int dispH = 758;                                          //Display Height
int petriD = (dispH/2)-10;                                //Petri dish diameter
int xC =  (dispW/2)-(petriD);                             //X position of left side of petri dish
int yC =  (dispH/2)-(petriD);                             //Y position of top side of petri dish

//Create a string where to save the Access Point IP address
IPAddress serverIP;

/*
    -----------------------------------------------------------
                    FUNCTIONS TO SETUP THE BOARD
    -----------------------------------------------------------
*/

//Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create an object on Inkplate library and also set library into 1 Bit mode (BW)
Inkplate display(INKPLATE_1BIT);

/*
    -----------------------------------------------------------
                      PERSONALISED FUNCTIONS
    -----------------------------------------------------------
*/

//With this function is it possible to check if everything is ok with the SD Card
void initSDCard(){
  if(!SD.begin(CS,spi,80000000)){
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

//With this function it will start the WiFi
void initWiFi() {
  WiFi.begin();
  WiFi.mode(WIFI_AP);               //WIFI_AP is equal of Access Point mode
  WiFi.softAP(ssid, password);      //AccessPoint ssid and pss
  Serial.print("IP Address: ");
  serverIP = WiFi.softAPIP();    
  Serial.println(serverIP);  //Here we print the IP Address of the AccessPoint
}

//After this comment state functions to control the experience
void state0() {
  display.clearDisplay();
  display.drawCircle(dispW/2, dispH/2, petriD, BLACK);
  display.setCursor(xC+100, yC+250);
  display.println("Connect to ");
  display.setCursor(xC+100, yC+300);
  display.print(ssid);
  display.println(" WiFi with pass: ");
  display.setCursor(xC+100, yC+350);
  display.println(password);
  display.setCursor(xC+100, yC+400);
  display.print("Open web browser and write");
  display.setCursor(xC+100, yC+450);
  display.print("http://");
  display.print(serverIP);
  display.println('/');
  display.display();
}

/*
    -----------------------------------------------------------
                          SETUP FUNCTION
    -----------------------------------------------------------
*/

void setup() {
  //Serial communication open to test
  Serial.begin(115200);
  //The next line is needed to change the SD Card reader with pins for Inkplate 6PLUS
  spi.begin(SCK, MISO, MOSI, CS);

  //Begin and clear display
  display.begin();
  display.clearDisplay();
  display.display();

  //Display settings
  display.setTextSize(3);
  display.setTextColor(BLACK, WHITE);
  display.setTextWrap(true);

  Serial.println("WiFi init:");
  initWiFi();
  Serial.println("WiFi init END");
  Serial.println("SD Card init:");
  initSDCard();
  Serial.println("SD Card init END");

  //Here we set what it need to happen after a client open the ESP32 IP address
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/index.html", "text/html");
  });
  //Load favicon, css and other files on the SD card
  server.serveStatic("/", SD, "/");

  //Do something when is received something from the query after "string"
  server.on("/string", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1; //state
    String inputMessage2; //bacteria
    String inputMessage3; //ab1
    String inputMessage4; //ab2
    String inputMessage5; //ab3

    // GET input1 value on <ESP_IP>/string?state
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      if(inputMessage1 == "0"){state0();}
      else if(inputMessage1 == "1"){//state1();}
      Serial.println("State 1");}
      else if(inputMessage1 == "2"){//state2();}
      Serial.println("State 2");}
    }
    else {
      inputMessage1 = "No message sent";
    }
    // GET input2 value on <ESP_IP>/string?bacteria
    if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
    }
    else {
      inputMessage2 = "No message sent";
    }
    // GET input3 value on <ESP_IP>/string?ab1
    if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage3 = request->getParam(PARAM_INPUT_3)->value();
    }
    else {
      inputMessage3 = "No message sent";
    }
    // GET input4 value on <ESP_IP>/string?ab2
    if (request->hasParam(PARAM_INPUT_4)) {
      inputMessage4 = request->getParam(PARAM_INPUT_4)->value();
    }
    else {
      inputMessage4 = "No message sent";
    }
    // GET input4 value on <ESP_IP>/string?ab3
    if (request->hasParam(PARAM_INPUT_5)) {
      inputMessage5 = request->getParam(PARAM_INPUT_5)->value();
    }
    else {
      inputMessage5 = "No message sent";
    }

    //Print on console the input messages
    Serial.print("State: ");
    Serial.print(inputMessage1);
    Serial.print(" - Bateria: ");
    Serial.println(inputMessage2);
    Serial.print(" - Antibiotic n°1: ");
    Serial.println(inputMessage3);
    Serial.print(" - Antibiotic n°2: ");
    Serial.println(inputMessage4);
    Serial.print(" - Antibiotic n°3: ");
    Serial.println(inputMessage5);
    
    //Here you send the action after receiving the input
    request->send(SD, "/index.html", "text/html");
  });

  //Start the server
  server.begin();

  //Start with the experience
  state0();
}

/*
    -----------------------------------------------------------
                          LOOP FUNCTION
    -----------------------------------------------------------
*/

void loop() {
  
}