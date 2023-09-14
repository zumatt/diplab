/*
    -----------------------------------------------------------
                      EXPERIENCE CONTROLLER
    -----------------------------------------------------------
*/
void expState(int sNum){
  if(sNum == 0){
    state0();
  } else if(sNum == 1){
    state1();
  } else if(sNum == 6){
    state6();
  } else if(sNum == 7){
    state7();
  } else if(sNum == 8){
    state8();
  } else if(sNum == 9){
    state9();
  } else if(sNum == 10){
    state10();
  } else if(sNum == 11){
    state11();
  } else if(sNum == 12){
    state12();
  }
}

/*
    -----------------------------------------------------------
                          STATE FUNCTIONS
    -----------------------------------------------------------
*/

void state0() {
  graphicLanding();
}

void state1() {
  graphicConnected();
}

void state6(){
  //Reset AB position for later
  ab1_x = 0;
  ab1_y = 0;
  ab2_x = 0;
  ab2_y = 0;
  ab3_x = 0;
  ab3_y = 0;

  //Reset resistance value for later
  //ab1_resistance = 0;
  //ab2_resistance = 0;
  //ab3_resistance = 0;

  //Reset value of j_controlCenter & j_readingAB
  j_readingAB = 0;
  j_controlCenter = "";

  graphicNameClasscodeReceived();
  sleep(2.5);
  graphicWaitingBact();
}

void state7(){
}

void state8(){
  //Bacteria spreading (everything is in the loop)
  accX = 0;
  accY = 0;
  display.clearDisplay();
  display.display();
  readyToSpread = 1;
  Serial.println("State 8 activated!");
}

void state9(){
  //Reset controller
  readyToSpread = 0;
  graphicWaitingAb();
}

void state10(){
  //Insert of Antibiotic (Touchscreen)
  accX = 0;
  accY = 0;
  display.clearDisplay();
  display.fillScreen(BLACK);
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(3);
  display.display();
  Serial.println("State 10 activated!");
}

void state11(){
  //Control center (History/Reading mode)
    ab1_xWeb = 100*ab1_x/dispW;
    ab1_yWeb = 100*ab1_y/dispH;
    ab2_xWeb = 100*ab2_x/dispW;
    ab2_yWeb = 100*ab2_y/dispH;
    ab3_xWeb = 100*ab3_x/dispW;
    ab3_yWeb = 100*ab3_y/dispH;
    Serial.print("Ab 1 x web: ");
    Serial.println(ab1_xWeb);
    Serial.print("Ab 1 y web: ");
    Serial.println(ab1_yWeb);
    Serial.print("Ab 2 x web: ");
    Serial.println(ab2_xWeb);
    Serial.print("Ab 2 y web: ");
    Serial.println(ab2_yWeb);
    Serial.print("Ab 3 x web: ");
    Serial.println(ab3_xWeb);
    Serial.print("Ab 2 y web: ");
    Serial.println(ab3_yWeb);

    checkResistance();
  if(j_controlCenter == "history"){
    Serial.println("We are in history mode!");
    historyHours = 0;
    historyMode();
    historyCondition();
  }else if(j_controlCenter == "reading"){
    Serial.println("We are in reading mode!");
    readingMode();
  } else{Serial.println("Error in state11");}
}

void state12(){
  //Save the experience
    historyBase(500);
}