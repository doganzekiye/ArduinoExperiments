
//2017510025 - Zekiye Doğan

//library for using lcd functions
#include <LiquidCrystal.h>
//define lcd pins
//rs=register, en=enable, d4 = 4.data pin, d5 = 5.data pin, d6 = 6.data pin, d7 = 7.data pin
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//to set the connections of the lcn pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//define ultrasonic sonsor pins
//listens for the returning signal
#define echoPin 6
//sends the audio signal to the object
#define trigPin 7
//define buzzer pin
#define buzzerPin 8

long distance;//to hold the distance value of the object from the sensor
int passedTime;//to keep track of the elapsed time during transactions

String date = "2021.09.31"; //given date
String time = "14:26:45"; //given time
int year,month,day,hour,min,sec; //min=minute, sec=second

void setup()
{
  pinMode(echoPin,INPUT);//from sensor to arduino
  pinMode(trigPin,OUTPUT);//from arduino to sensor
  pinMode(buzzerPin,OUTPUT);//from arduino to buzzer
  splitDateTime();//to get year-month-day-hour-minute-second values
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  distance = calculateDistance();//calculate distance
  buzzerSound();//make buzzer sounds according to distance
  lcdPrint();//print lcd screen
  printDateTime(); //get year-month-day-hour-minute-second values
  serialPrint();//print serian monitor
  
  //to make sure that the time elapsed through transactions increases every two seconds
  while(true){
    if(passedTime >= 2000){
      sec = sec+2;
      passedTime = passedTime-2000;//reduce passedTime by 2 seconds
      break;
    }
    delay(1);
    passedTime++;//increase until reaches to 2 seconds
  }

}

//to make a sound from the buzzer according to the distance value
void buzzerSound(){
  
  if(distance<5){//for game over sound
    //tone(pin,frequency) -- generates a square wave of the specified frequency on a pin.
    //noTone() -- stops the generation of a square wave triggered by tone().
    tone(buzzerPin,500);
    delay(100);
    tone(buzzerPin,1200);
    delay(100);
    tone(buzzerPin,300);
    delay(100);
    tone(buzzerPin,1000);
    delay(100);
    tone(buzzerPin,400);
    delay(100);
    tone(buzzerPin,1100);
    delay(100);
    noTone(buzzerPin);
    delay(100);
    passedTime += 700;//increase passedTime by delay value
  }
  else{
    tone(buzzerPin,(10000/distance));
    //directly proportional to distance value
    delay(distance*10);
    noTone(buzzerPin);
    delay(distance*10);
    passedTime += (distance*20);//increase passedTime by delay value
  }
}

//to calculate distance based on values from ultrasonic sensor
//return distance value
int calculateDistance(){
  
  //triggers the trigPin to send a signal
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  
  //wait until echoPin is high
  long duration = pulseIn(echoPin,HIGH);//hold elapsed time until echoPin goes high
  long dist = duration/58.2;//calculate distance taking into account time and speed of sound
  delay(50);
  passedTime += 50;//increase passedTime by delay value
  
  return dist;
  
}

//to specify what the distance value means for lcd display
//display lcd screen
void lcdPrint(){
  lcd.clear();//clear screen for better results
  lcd.setCursor(0,0);
  lcd.print(distance);
  lcd.setCursor(0, 1);
  if(distance<5){
    lcd.print("Crashed");
  }
  else if(5<=distance && distance<=20){
    lcd.print("Too Close");
  }
  else if(21<=distance && distance<=50){
    lcd.print("Close");
  }
  else if(51<=distance && distance<=100){
    lcd.print("Far");
  }
  else{
    lcd.print("Too Far");
  }
  
}
//to specify what the distance value means for serial monitor
//print serial monitor
void serialPrint()
{
  Serial.print("Distance: ");
  Serial.println(distance);//print distance
  
  if(distance<5){
    Serial.println("It is crashed.");
  }
  else if(5<=distance && distance<=20){
    Serial.println("It is too close.");
  }
  else if(21<=distance && distance<=50){
    Serial.println("It is close.");
  }
  else if(51<=distance && distance<=100){
    Serial.println("It is far.");
  }
  else{
    Serial.println("It is too far");
  }

  Serial.println("-------------------------------------------");
}

void printDateTime(){
  changeDate();//update date and time
  
  //printing date
  Serial.print("Date: ");
  small(day);//print day
  Serial.print(".");
  small(month);//print month
  Serial.print(".");
  Serial.print(year);//print year
  Serial.print(" - ");

  //printing time
  Serial.print("Hour: ");
  small(hour);////print hour
  Serial.print(":");
  small(min);////print minute
  Serial.print(":");
  small(sec);////print second
  Serial.print(" - ");
}

//to put 0 in front of numbers less than 10
void small(int val){
  if(val<10)
    Serial.print("0");
  Serial.print(val);
}

//as the seconds increase, the date will change over time.
//to ensure that the date is changed correctly.
void changeDate(){
  //Increase the minute if the second is 60, the hour if the minute is 60, 
  //the day if the hour is 24, the month if the day is (28-30-31), the year if the month is 12.
  if(sec>=60){
    min++;
    sec=sec-60;
    if(min==60){
      hour++;
      min=0;
      if(hour==24){
        day++;
        hour=0;
        if(day==31&& month==1|| month==3|| month==5|| month==7|| month==8|| month==10|| month==12){
          month++;
          day=1;
          if(month==13){
            year++;
            month=1;
          }
        }
        else if(day==30&& month==4|| month==6|| month==9|| month==11){
          month++;
          day=1;
        }
        else if(day==28&& month==2){
          month++;
          day=1;
        }
      }
    }
  }
}
//to get year-month-day-hour-minute-second values by taking substrings of time and date values
void splitDateTime(){
  //find year
  year = date.substring(0, 4).toInt();
  //find month
  month = date.substring(5, 7).toInt();
  //find day
  day = date.substring(8,10).toInt();
  //find hour
  hour = time.substring(0, 2).toInt();
  //find minute
  min = time.substring(3,5).toInt();
  //find second
  sec = time.substring(6,8).toInt();
}
// useful links
//https://www.youtube.com/watch?v=UKj6qtSBXMQ
//https://www.youtube.com/watch?v=_GWE4qINY80&list=PLDRcccSktQd5mfXDtGv975V77RCrW6H7U&index=28
