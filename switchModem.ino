unsigned int newValueChanel = 0;
unsigned int oldValueChanel = 0;
bool blinkFlag = false;

void modemChenelLedWatcher(){
  static unsigned long t = 0;
  static bool ledFlag = false;
  const int timeOutBlink = 500;
  if(blinkFlag){
    if((millis() - t) > timeOutBlink){
      t = millis();
      ledFlag = !ledFlag;
      setLed(newValueChanel, ledFlag);
    }
  }else{
    setLed(globalState[10], true);
  } 
}

void setNewValueChanel(int newValue){
  newValueChanel = newValue;
}

void setLed(int numChanel, bool ledFlag){
  switch(numChanel){
      case 0:
        digitalWrite(a3_GPIO_pin, ledFlag);
        digitalWrite(a2_GPIO_pin, LOW);
      break;
      case 1:
        digitalWrite(a3_GPIO_pin, LOW);
        digitalWrite(a2_GPIO_pin, ledFlag);
      break;
    }
}


void switchChanelWatcher(int timeOutTransition){
static unsigned long t = 0;
static bool transitionFlag = false;

  if(digitalRead(d4_GPIO_pin)){
    globalState[10] = 1;
  }else{
    globalState[10] = 0;
  }

  if(oldValueChanel != newValueChanel){
    if(!transitionFlag){
      t = millis();
      transitionFlag = true;
      blinkFlag = true;
    }else if((millis() - t) > timeOutTransition){
      oldValueChanel = newValueChanel;
      blinkFlag = false;
      transitionFlag = false;
      if(oldValueChanel == 0){
        digitalWrite(d3_GPIO_pin, LOW);
      }else if(oldValueChanel == 1){
        digitalWrite(d3_GPIO_pin, HIGH);
      }
    }
  }else{
    transitionFlag = false;
    blinkFlag = false;
  }
}

void pressedButtonWatcher(){
  static unsigned long t = 0;
  static bool pressedFlag = false;
  if(!digitalRead(d2_GPIO_pin)){
    if(!pressedFlag){
      pressedFlag = true;
      t = millis();
    }else if((millis() - t) > 400){
      pressedFlag = false;
      newValueChanel++;
      if(newValueChanel > 1){ 
        newValueChanel = 0;
      }
      return;  
    }
  }else{
    pressedFlag = false;
  }
}
