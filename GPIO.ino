//GPIO
/*
 * D4 - // Обратная связь от переключателя модема
 * D3 - // переключение модема
 * 
 * 
 */

  const int d4_GPIO_pin = 4; // Обратная связь от переключателя модема
  const int d3_GPIO_pin = 3; // переключение модема
  const int d2_GPIO_pin = 2; // кнопка
  const int a3_GPIO_pin = A3; // м1лед
  const int a2_GPIO_pin = A2; // м2лед
  const int a1_GPIO_pin = A1;
  const int a0_GPIO_pin = A0;

void gpioInit(){
  pinMode(d4_GPIO_pin,  INPUT);
  pinMode(d3_GPIO_pin, OUTPUT);
  pinMode(d2_GPIO_pin, INPUT);
  pinMode(a3_GPIO_pin, OUTPUT);
  pinMode(a2_GPIO_pin, OUTPUT);
  pinMode(a1_GPIO_pin, OUTPUT);
  pinMode(a0_GPIO_pin, OUTPUT);

  digitalWrite(d3_GPIO_pin, LOW);
  digitalWrite(d2_GPIO_pin, HIGH);
  digitalWrite(a3_GPIO_pin, LOW);
  digitalWrite(a2_GPIO_pin, LOW);
  digitalWrite(a1_GPIO_pin, LOW);
  digitalWrite(a0_GPIO_pin, LOW);
}


void watchDogStopReboot(){
  static bool flagInit = false;
  if(!flagInit){
    pinMode(a0_GPIO_pin, INPUT);
    digitalWrite(a0_GPIO_pin, HIGH);
    flagInit = true;
  }else{
    if(digitalRead(a0_GPIO_pin) == LOW){
      globalState[9] = 1;
    }else{
      globalState[9] = 0;
    }
  }
}


void modemSwitch(int M){
  switch (M){
    case 1:
     //digitalWrite(d3_GPIO_pin, LOW);
     setNewValueChanel(0);
    break;
    case 2:
     //digitalWrite(d3_GPIO_pin, HIGH);
     setNewValueChanel(1);
    break;
  }
};
