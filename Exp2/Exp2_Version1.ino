
//Zekiye Dogan - 2017510025

//define button pin
const int buttonPin = 5;
//define 7-segment-display pins
const int a = 7;
const int b = 6;
const int c = 8;
const int d = 11;
const int e = 10;
const int f = 12;
const int g = 13;

//to hold current button status
int currentButtonState = 0;
//to hold old button status
int oldButtonState = 0;
//to keep which number to show on display
int numberToShow = 0;

int TIME_DISPLAY = 200;
//to increase the number according to the value we select 
//when the button is pressed
int COUNTER_VALUE = 7;

void setup()
{
  //define button pin as input
  pinMode(buttonPin, INPUT_PULLUP);
  //define 7-segment-display pins as output
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  //initially print 0 until button pressed
  printNumber(numberToShow);
}

void loop()
{
  currentButtonState = digitalRead(buttonPin);//current button status
  //check if the current and previous button state is different &
  //the current button state is HIGH
  //allows only one change even if we keep the button pressed
  if (oldButtonState != currentButtonState && currentButtonState == HIGH) {//button is pressed
    //increase number by COUNTER_VALUE
    numberToShow = COUNTER_VALUE + numberToShow;
    //to return to the beginning by taking the mode 
    //when the number is greater than 15
    if(numberToShow > 15){
      numberToShow = numberToShow % 16;
    }
    ledOff();//to avoid confusion of numbers
    delay(TIME_DISPLAY);
    //prints the number until button pressed again
    printNumber(numberToShow);
  }
  oldButtonState = currentButtonState;//old button status
}

//to reset display for the next operations
void ledOff() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

//computes which legs(a,b,c,d,e,f,g) of the display will be high 
//for the parts of the numbers that need to be lit
void printNumber(int value){
  //10(A),11(B),12(C),13(D),14(E),15(F)
  if(value!=1 && value!=4 && value!=11 && value!=13)
    digitalWrite(a,HIGH);
  
  if(value!=5 && value!=6 && value!=11 && value!=12 &&
    value!=14 && value!=15)
    digitalWrite(b,HIGH);
    
   if(value!=2 && value!=12 && value!=14 && value!=15)
    digitalWrite(c,HIGH);   
    
  if(value!=1 && value!=4 && value!=7 && value!=10 && value!=15)
    digitalWrite(d,HIGH);    
    
  if(value!=1 && value!=3 && value!=4 && value!=5 &&
    value!=7 && value!=9)
    digitalWrite(e,HIGH);    
    
  if(value!=1 && value!=2 && value!=3 && value!=7 && value!=13)
    digitalWrite(f,HIGH);
  
  if(value!=0 && value!=1 && value!=7 && value!=12)
    digitalWrite(g,HIGH);  
}
