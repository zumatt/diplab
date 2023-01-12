void serverReceive(){
  server.on("/string", HTTP_GET, [] (AsyncWebServerRequest *request) {

    // GET input1 value on <ESP_IP>/string?state
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
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
    // GET input5 value on <ESP_IP>/string?ab3
    if (request->hasParam(PARAM_INPUT_5)) {
      inputMessage5 = request->getParam(PARAM_INPUT_5)->value();
    }
    else {
      inputMessage5 = "No message sent";
    }
    // GET input6 value on <ESP_IP>/string?name
    if (request->hasParam(PARAM_INPUT_6)) {
      inputMessage6 = request->getParam(PARAM_INPUT_6)->value();
    }
    else {
      inputMessage6 = "No message sent";
    }
     // GET input7 value on <ESP_IP>/string?classcode
    if (request->hasParam(PARAM_INPUT_7)) {
      inputMessage7 = request->getParam(PARAM_INPUT_7)->value();
    }
    else {
      inputMessage7 = "No message sent";
    }

    //Check state
    if(inputMessage1 == "0")      {request->send(SD, "/index.html", "text/html");state0();}
      else if(inputMessage1 == "1") {request->send(SD, "/index.html", "text/html");state1();}
      else if(inputMessage1 == "2") {request->send(SD, "/index.html", "text/html");state2();}
      else if(inputMessage1 == "3") {request->send(SD, "/index.html", "text/html");state3();}
      else if(inputMessage1 == "4") {request->send(SD, "/index.html", "text/html");state4();}
      else if(inputMessage1 == "5") {request->send(SD, "/index.html", "text/html");state5();}
      else if(inputMessage1 == "6") {request->send(SD, "/index.html", "text/html");state6();}
      else if(inputMessage1 == "7") {request->send(SD, "/index.html", "text/html");state7();}
      else if(inputMessage1 == "8") {request->send(SD, "/index.html", "text/html");state8();}
      else if(inputMessage1 == "9") {request->send(SD, "/index.html", "text/html");state9();}
      else if(inputMessage1 == "10"){request->send(SD, "/index.html", "text/html");state10();}
      else if(inputMessage1 == "11"){request->send(SD, "/index.html", "text/html");state11();}
      else if(inputMessage1 == "12"){request->send(SD, "/index.html", "text/html");state12();}

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
    Serial.print(" - Name: ");
    Serial.println(inputMessage6);
    Serial.print(" - Class Code: ");
    Serial.println(inputMessage7);
  });
}