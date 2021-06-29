//Zekiye Dogan - 2017510025

boolean on=true;//to control button status
int buttonPin = 7;//declare button pin
int ledPin[] = {11,10,9,8};//declare led pins
int buttonState = 0;//initial button status
int oldButtonState;//to control button changes
int checkPoint;////to control button changes
int TIME_LED_COUNTER = 500;
int TIME_LED_SLIDER = 200;

void setup()
{
  for (int i =0;i<4;i++)
  {
    pinMode(ledPin[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
}

void loop()
{
  ledOff();//to star over the operations
  buttonState = digitalRead(buttonPin);//current button status
  
  //switch the operation when button pressed and not the same with old button status
  //to prevent switching the operations while button still pressed
  if (oldButtonState != buttonState && buttonState == 1) {
    if(on==true){//change button status if it pressed
      on=false;
    }
    else{
      on=true;
    }
  }
  oldButtonState = buttonState;
  if (on==true){//default mode is binary counter
    counter();
  }
  else {
    pattern();
  }
}

void counter()//to show binary counting 0 to 15
{
  for (byte counter =0;counter<=15; counter++)
  {
    binaryCounter(counter);
    delay(TIME_LED_COUNTER);
    
    //to check if button is pressed, if it is then stop the process
    //if current button status is not the same with old, then means button pressed
    checkPoint = digitalRead(buttonPin);
    if (buttonState != checkPoint)
      break;
  }
}

//to turn on the appropriate led according to the value, others low
void binaryCounter(byte led)
{
  for (int i =0;i<4;i++)
  {
    if (bitRead(led, i)==1)//if values are match led will be on
    {
      digitalWrite(ledPin[i], HIGH);
    }
    else
    {
      digitalWrite(ledPin[i], LOW);
    }
    
  }
}

void pattern()//to show sliding led pattern
{
  for(int i=0; i<4; i++) {//to turn on the leds left to right
    digitalWrite(ledPin[i],HIGH);
    delay(TIME_LED_SLIDER);
    digitalWrite(ledPin[i],LOW);
    
    //to check if button is pressed, if it is then stop the process
    //if current button status is not the same with old, then means button pressed
    checkPoint = digitalRead(buttonPin);
    if (buttonState != checkPoint)
      break;
  }
  
  //if the button pressed while leds are on left to right
  //then it can not continue right to left
  if  (buttonState == checkPoint){
    for(int i=2; i>0; i--) {//to turn on the leds right to left
      digitalWrite(ledPin[i],HIGH);
      delay(TIME_LED_SLIDER);
      digitalWrite(ledPin[i],LOW);
      
      checkPoint = digitalRead(buttonPin);
      if (buttonState != checkPoint)
        break;
    }
  }
}

//to reset leds for the next operations
void ledOff() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPin[i], LOW);
  }
}
