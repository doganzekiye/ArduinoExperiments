//library for using lcd functions
#include <LiquidCrystal.h>
//define lcd pins
//rs=register, en=enable, d4 = 4.data pin, d5 = 5.data pin, d6 = 6.data pin, d7 = 7.data pin
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//to set the connections of the lcn pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//define button pin
const int buttonPin = 13;
int currentButtonState=0;//to hold current button status
int checkPoint=0;//to control the button change
int oldButtonState=0;//to hold old button status
bool buttonPressed = false;//false if the button was not pressed, true if the button was pressed

int TIME_SCREEN_CLOCK = 2000;
int TIME_SCREEN_INFO = 1000;

String TIME_STRING = "2021.12.31 - 23:59:45";
//y=year, m=month, d=day, h=hour, min=minute, s=second
int y,m,d,h,min,s;
int weekday;//to keep track of what day of the week
String weekOfDayEnglish;//to hold week of the day for english
String weekOfDayTurkish;//to hold week of the day for turkish

void setup()
{
  //define button pin as input
  pinMode(buttonPin, INPUT_PULLUP);
  //to split and arrage the time string
  splitTimeString();
  //to find out what day of the week
  findDayOfWeek(d,m,y);
  lcd.begin(16, 2);
}

void loop()
{

  currentButtonState = digitalRead(buttonPin);//current button status
  //switch the operation when button pressed
  //allows only one change even if we keep the button pressed
  if (oldButtonState != currentButtonState && currentButtonState == HIGH) {
    //change button status if button is pressed
    if(buttonPressed==true){
      buttonPressed=false;
    }
    else{
      buttonPressed=true;
    }
  }
  oldButtonState = currentButtonState;//old button status
  if (buttonPressed==false){//default mode is english format
    english();
  }
  else {
    turkish();
  }
}

//display english format
void english(){
  
  //for loop has been created to check the button status more frequently, TIME_SCREEN_CLOCK total
  for(int i=1; i<(TIME_SCREEN_CLOCK/10)+1;i++){
    if(i%100==0){//If i reached 100 and its multiples, this indicates that 1 second has passed.
      s++;//increase second value
      //to find the current date and day of the week according to the changing values
      changeDate();
      
      //print english clock screen
      lcd.clear();//clear screen for better results
      //if the hour is greater than or equal to 12 print pm,if less than 12 print am
      int midCheck = h;
      if(h>11 && h<24){
        midCheck = h-12;
        lcd.setCursor(9,0);
        lcd.print("PM");
      }
      else if(h<12 && h>-1){
        lcd.setCursor(9,0);
        lcd.print("AM");
      }
      lcd.setCursor(0,0);
      if(midCheck<10)
        lcd.print("0");
      lcd.print(midCheck);//hour
      lcd.print(":");
      if(min<10)
        lcd.print("0");
      lcd.print(min);//minute
      lcd.print(":");
      if(s<10)
        lcd.print("0");
      lcd.print(s);//second
      lcd.setCursor(13,0);
      lcd.print("ENG");//language
      lcd.setCursor(0, 1);
      if(d<10)
        lcd.print("0");
      lcd.print(d);//day
      lcd.print(".");
      if(m<10)
        lcd.print("0");
      lcd.print(m);//month
      lcd.print(".");
      lcd.print(y);//year
      lcd.setCursor(13,1);
      lcd.print(weekOfDayEnglish);//day of the week in english
    }
    delay(10);
    
    //to check if button is pressed, if it is then stop the process
    //if current button status is not the same with checkpoint, then means button pressed
    checkPoint = digitalRead(buttonPin);
    if (currentButtonState != checkPoint){
        break;
    }
  }
  
  //print english info screen
  //If the button is pressed, the Turkish format should be printed 
  //without continuing the operation.
  if(currentButtonState == checkPoint){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HH");
    lcd.print(":");
    lcd.print("MM");
    lcd.print(":");
    lcd.print("SS");
    lcd.setCursor(9,0);
    lcd.print("12H");
    lcd.setCursor(13,0);
    lcd.print("LNG");
    lcd.setCursor(0, 1);
    lcd.print("DD");
    lcd.print(".");
    lcd.print("MM");
    lcd.print(".");
    lcd.print("YYYY");
    lcd.setCursor(13,1);
    lcd.print("DOW");
    
    for(int i=1; i<(TIME_SCREEN_INFO/10)+1;i++){
      delay(10);
      if(i%100==0){
        s++;
        changeDate();
      }
      checkPoint = digitalRead(buttonPin);
      if (currentButtonState != checkPoint){
          break;
      }
    }
  }
}

//display turkish format
//same operations as english format
void turkish(){
  for(int i=1; i<(TIME_SCREEN_CLOCK/10+1);i++){
    if(i%100==0){
      s++;
      changeDate();
      //turkish clock screen
      lcd.clear();
      lcd.setCursor(0,0);
      if(h<10)
        lcd.print("0");
      lcd.print(h);
      lcd.print(":");
      if(min<10)
        lcd.print("0");
      lcd.print(min);
      lcd.print(":");
      if(s<10)
        lcd.print("0");
      lcd.print(s);
      lcd.setCursor(13,0);
      lcd.print("TUR");
      lcd.setCursor(0, 1);
      if(d<10)
        lcd.print("0");
      lcd.print(d);
      lcd.print(".");
      if(m<10)
        lcd.print("0");
      lcd.print(m);   
      lcd.print(".");
      lcd.print(y);
      lcd.setCursor(13,1);
      lcd.print(weekOfDayTurkish);//day of the week in turkish
    }
    delay(10);
    checkPoint = digitalRead(buttonPin);
    if (currentButtonState != checkPoint){
      break;
    }
  }
  
  //turkish info screen
  if(currentButtonState == checkPoint){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SA");
    lcd.print(":");
    lcd.print("DA");
    lcd.print(":");
    lcd.print("SN");
    lcd.setCursor(9,0);
    lcd.print("24H");
    lcd.setCursor(13,0);
    lcd.print("DIL");
    lcd.setCursor(0, 1);
    lcd.print("GG");
    lcd.print(".");
    lcd.print("AA");   
    lcd.print(".");
    lcd.print("YYYY");
    lcd.setCursor(13,1);
    lcd.print("GUN");
    
    for(int i=1; i<(TIME_SCREEN_INFO/10+1);i++){
      delay(10);
      if(i%100==0){
        s++;
        changeDate();
      }
      checkPoint = digitalRead(buttonPin);
      if (currentButtonState != checkPoint){
        break;
      }
    }
  }
}

//to find out what day of the week the date is
void findDayOfWeek(int day, int month, int year){
  //day calculation
  weekday  = (day+=month<3?year--:year-2,23*month/9+day+4+year/4-year/100+year/400)%7;
  //To find out what day is the day according to weekday results
  if(weekday == 0){
    weekOfDayEnglish="SUN";
    weekOfDayTurkish="PAZ";
  }
  else if(weekday == 1){
    weekOfDayEnglish="MON";
    weekOfDayTurkish="PZT";
  }
  else if(weekday == 2){
    weekOfDayEnglish="TUE";
    weekOfDayTurkish="SAL";
  }
  else if(weekday == 3){
    weekOfDayEnglish="WED";
    weekOfDayTurkish="CAR";
  }
  else if(weekday == 4){
    weekOfDayEnglish="THU";
    weekOfDayTurkish="PER";
  }
  else if(weekday == 5){
    weekOfDayEnglish="FRI";
    weekOfDayTurkish="CUM";
  }
  else if(weekday == 6){
    weekOfDayEnglish="SAT";
    weekOfDayTurkish="CMT";
  }
}

//as the seconds increase, the date will change over time.
//to ensure that the date is changed correctly.
void changeDate(){
  //Increase the minute if the second is 60, the hour if the minute is 60, 
  //the day if the hour is 24, the month if the day is (28-30-31), the year if the month is 12.
  if(s==60){
    min++;
    s=0;
    if(min==60){
      h++;
      min=0;
      if(h==24){
        d++;
        h=0;
        if(d==31&& m==1|| m==3|| m==5|| m==7|| m==8|| m==10|| m==12){
          m++;
          d=1;
          if(m==13){
            y++;
            m=1;
          }
        }
        else if(d==30&& m==4|| m==6|| m==9|| m==11){
          m++;
          d=1;
        }
        else if(d==28&& m==2){
          m++;
          d=1;
        }
      }
    }
  }
  //find the day of the week according to the new date
  findDayOfWeek(d,m,y);
}

//to split the given date
void splitTimeString(){
  //to remove the blanks
  TIME_STRING.replace(" ","");
  //to hold delimiter locations in string
  int delimiter,delimiterFirst_1,delimiterFirst_2,delimiterSecond_1,delimiterSecond_2;
  
  //to divide the o'clock and the date
  delimiter = TIME_STRING.indexOf("-");
  String first = TIME_STRING.substring(0, delimiter);//date
  String second = TIME_STRING.substring(delimiter + 1);//o'clock
  
  //to pieces the date
  delimiterFirst_1 = first.indexOf(".");
  delimiterFirst_2 = first.indexOf(".", delimiterFirst_1 + 1);
  //find year with delimiter locations
  String year = first.substring(0, delimiterFirst_1);
  y = year.toInt();
  //find month with delimiter locations
  String month = first.substring(delimiterFirst_1 + 1, delimiterFirst_2);
  m = month.toInt();
  //find day with delimiter locations
  String day = first.substring(delimiterFirst_2 + 1);
  d = day.toInt();
  
  //to pieces the clock
  delimiterSecond_1 = second.indexOf(":");
  delimiterSecond_2 = second.indexOf(":", delimiterSecond_1 + 1);
  //find hour with delimiter locations
  String hour = second.substring(0, delimiterSecond_1);
  h = hour.toInt();
  //find minute with delimiter locations
  String minute = second.substring(delimiterSecond_1 + 1, delimiterSecond_2);
  min = minute.toInt();
  //find second with delimiter locations
  String sec = second.substring(delimiterSecond_2 + 1);
  s = sec.toInt();
}

// useful links
//https://www.youtube.com/watch?v=vwt-13cfEkU&list=PLDRcccSktQd5mfXDtGv975V77RCrW6H7U&index=18
//https://www.youtube.com/watch?v=_tMxt4wO6wU
//https://www.youtube.com/watch?v=zWAhsRdUHi8
//https://www.youtube.com/watch?v=wczn1qgphdc&t=282s
//https://www.theamplituhedron.com/articles/How-to-split-strings-in-Arduino-IDE-to-glean-information-as-substrings/
//https://gist.github.com/bharathyes/b9b0f90c71ddc78d02a7
