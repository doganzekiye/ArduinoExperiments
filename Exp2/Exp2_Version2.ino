
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

int TIME_DISPLAY = 200;
//to hold generated random numbers
int RANDOM = 0;

void setup()
{
  //define button pin as output
  pinMode(buttonPin, INPUT_PULLUP);
  //define 7-segment-display pins as input
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  
  //initially print 0 until button pressed
  printNumber(RANDOM);
  //allows create different random seqeuences
  randomSeed(analogRead(0));
}

void loop()
{
  currentButtonState = digitalRead(buttonPin);//current button status
  
  //check if the current and previous button state is different
  //check if the current button state is HIGH
  //allows only one change even if we keep the button pressed
  if (oldButtonState != currentButtonState && currentButtonState == HIGH) {//button is pressed
    //A random number between min and max-1
    RANDOM = random(0, 16);
    ledOff();//to avoid confusion of numbers
    delay(TIME_DISPLAY);
    //prints the number until button pressed again
    printNumber(RANDOM);
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
