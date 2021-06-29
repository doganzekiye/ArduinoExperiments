
//Zekiye Dogan - 2017510025

//define potentiometer pin
const int potPin = A0;
//define button pin
const int buttonPin = 13;
//define pins of motor driver
const int input1 = 3;//input1
const int input2 = 4;//input2
const int speedPin = 5;//enable

int motorSpeed = 0;//to hold speed for dc motor
int currentButtonState = 0;//to hold current button status
int checkPoint;//to control the button change

void setup()
{
  //define button pin as output
  pinMode(buttonPin, INPUT_PULLUP);
  //define potentiometer pin as input
  pinMode(potPin, INPUT);
  //define pins of motor driver as output
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(speedPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //read potentiometer value from analog input
  motorSpeed = analogRead(potPin);
  //Re-maps a number from one range to another
  //so it can be used in the analogWrite function
  motorSpeed = map(motorSpeed, 0, 1023, 0, 255);
  //current button status before start operations
  currentButtonState = digitalRead(buttonPin);
  //rotating clockwise
  modeCW();
  //To see the change more clearly
  delay(100);
  //rotating counterclockwise
  modeCCW();

}
//function for rotating the dc motor clockwise
void modeCW(){
  //for loop has been created to check the button status more frequently.
  //3 seconds total
  for(int i=0; i<30;i++){
    //LOW and HIGH values are given to determine the direction of voltage.
    //If the direction of voltage changes, the direction also changes.
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    //to send the speed value to dc motor
    analogWrite(speedPin, motorSpeed);
    delay(100);
    
    //to check if button is pressed, if it is then stop the process
    //if current button status is not the same with checkpoint, then means button pressed
    //allows only one change even if we keep the button pressed
    checkPoint = digitalRead(buttonPin);
    if (currentButtonState != checkPoint && checkPoint == HIGH){
      break;
    }
  }
}
//function for rotating the dc motor counterclockwise
void modeCCW(){
  for(int i=0; i<30;i++){
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    analogWrite(speedPin, motorSpeed);
    delay(100);
    
    checkPoint = digitalRead(buttonPin);
    if (currentButtonState != checkPoint && checkPoint == HIGH){
      break;
    }
  }
}
//useful links
/*
https://bc-robotics.com/tutorials/controlling-dc-motor-arduino/
https://surtrtech.com/2018/01/27/control-dc-motor-speed-using-potentiometer-l298n-arduino/
https://www.youtube.com/watch?v=D0UuJGqi_NA&list=PLDRcccSktQd5mfXDtGv975V77RCrW6H7U&index=5
https://www.youtube.com/watch?v=UtZtdLg0jFM
https://www.youtube.com/watch?v=LlSco_2ILoY
https://www.youtube.com/watch?v=bp2wwwOFlZQ
*/
