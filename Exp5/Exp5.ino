
//2017510025 - Zekiye Doğan

#include "DHT.h" //add library for dht11 usage
#define DHTPIN 8 //define dht11 pin
#define DHTTYPE DHT11 //define dht's type as dht11
DHT dht(DHTPIN, DHTTYPE); //initialize dht sensor

#define LDRPIN A0 //define ldr pin
int ldr; //to hold light value
bool isDay; //to hold day or night
float humidity; //to hold humidity value
float temperature; //to hold temperature value
String date = "2021.09.31"; //given date
String time = "14:26:56"; //given time
int year,month,day,hour,min,sec; //min=minute, sec=second

void setup()
{
  splitDateTime();
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  printDateTime(); //get year-month-day-hour-minute-second values
  humidity = dht.readHumidity(); //read humidity value from dht11 sensor
  temperature = dht.readTemperature(); //read temperature value from dht11 sensor
  ldr = analogRead(LDRPIN); //read ldr light value through the pot
  //print light-temperature-humidity info panel
  Serial.print("Light: ");
  Serial.print(ldr);//print ldr
  Serial.print(" - Temperature: ");
  Serial.print(temperature);//print temperature
  Serial.print("°C - Humidity: ");
  Serial.print(humidity);//print humidity
  Serial.println("%");
  dayOrNight();//decide day or night
  hotOrCold();//decide hot or cold temperature
  lowOrHigh();//decide low or high humidity
  delay(3000);
  sec = sec+3;
  Serial.println("-------------------------------------------");
  
}
//decide day or night according to ldr value
void dayOrNight()
{
  if(ldr<400){
    isDay=false;
    Serial.print("Night - ");
  }
  else{
    isDay=true;
    Serial.print("Day - ");
  }
}
//decide hot or cold according to isDay value
void hotOrCold()
{
  //if it is day (20-24)
  if(isDay==true){
    if(temperature<20){
      Serial.print("Cold - ");
    }
    else if(temperature>24){
      Serial.print("Hot - ");
    }
    else{
      Serial.print("Optimal Temperature - ");
    }
  }

  //if it is night (18-21)
  else{
    if(temperature<18){
      Serial.print("Cold - ");
    }
    else if(temperature>21){
      Serial.print("Hot - ");
    }
    else{
      Serial.print("Optimal Temperature - ");
    }
  } 
}
//decide low or high humidity according to humidity value (30-50)(50-70)
void lowOrHigh()
{
  if(humidity<50){
    Serial.println("Low Humidity");
  }
  else if(humidity>70){
    Serial.println("High Humidity");
  }
  else{
    Serial.println("Optimal Humidity");
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
  if(sec>59){
    min++;
    sec=sec-59;
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

/* usefull links
https://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-an-arduino/
https://www.youtube.com/watch?v=TBbtEqFV-p0
https://www.youtube.com/watch?v=9d8P6_HrgUY&list=PLDRcccSktQd5mfXDtGv975V77RCrW6H7U&index=9
*/
