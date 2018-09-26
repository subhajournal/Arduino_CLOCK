#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float temp;
float reading=0;
const int tempPin = A1;
String date[]={"Sun","Mon","Tues","Wed","Thur","Fri","Sat"};
int i=0;         //Day increment count
int dt=1;        //Variable for date
int mnth=1;      //Variable for month
int year=18;     //Variable for year
char time[17];
char dmy[17];    //Print DDMMYY
int h=0;
int m=0;
int s=0;
int it=0;      //<=AM PM Iteration or Complete day iterarion count
const int sw1=6;    //Increment Hour
const int sw2=7;    //Increment Minute
const int sw3=8;    //Increment Day
const int sw4=9;    //Increment date
const int sw5=10;    //Increment month
const int sw6=13;    //Increment year
int s1;
int s2;
int s3;
int s4; 
int s5;
int s6;
void setup() {
analogReference(INTERNAL);
pinMode(sw1,INPUT);
pinMode(sw2,INPUT);
pinMode(sw3,INPUT);
pinMode(sw4,INPUT);
pinMode(sw5,INPUT);
pinMode(sw6,INPUT);
lcd.begin(16, 2);
Serial.begin(9600);
}
void loop() 
{
  int i=0;
  s1=digitalRead(sw1);      //Hour Modification Switch
  s2=digitalRead(sw2);      //Minute Modification Switch
  s3=digitalRead(sw3);      //Day Modification Switch
  s4=digitalRead(sw4);      //Date Modification Switch
  s5=digitalRead(sw5);      //Month Modification Switch
  s6=digitalRead(sw6);      //Year Modification Switch
  reading= analogRead(tempPin); 
  if(s1==HIGH && s2==LOW && s3==LOW && s4==LOW && s5==LOW && s6==LOW)
  {
    h=h+1;
  }
  if(s2==HIGH && s1==LOW && s3==LOW && s4==LOW && s5==LOW && s6==LOW)
  {
    m=m+1;
  }
  if(s3==HIGH && s1==LOW && s2==LOW && s4==LOW && s5==LOW && s6==LOW)
  {
    i=i+1;
  }
  if(s==60)     //<==
  {
    s=0;
    m=m+1;
  }
  if(m==60)     //<==
  {
    m=0;
    h=h+1;
  }
  if(h==12)     //<==
  {
    h=0;
    it=it+1;     //<=Demonstration of 12 hrs:: h==12:: it=it+1
  }
  lcd.setCursor(0,0);
  sprintf(time, "%02i:%02i:%02i", h, m, s);
  lcd.print(time);
  if(it==0)
  {
    lcd.setCursor(8,0);
    lcd.print("AM");
  }
  if(it==1)        
  {
    lcd.setCursor(8,0);
    lcd.print("PM");
  }
  if(it==2)
  {
    it=0;
    i++;
    dt++;
  }
  //DDMMYY Calculation
  if(s4==HIGH && s5==LOW && s6==LOW && s1==LOW && s2==LOW && s3==LOW)
  {
  dt++;
  }
  if(s5==HIGH && s4==LOW && s6==LOW && s1==LOW && s2==LOW && s3==LOW)
  {
    mnth++;
  } 
  if(s6==HIGH && s4==LOW && s5==LOW && s1==LOW && s2==LOW && s3==LOW)
  {
    year++;
  }
  
  if(mnth==1 || mnth==3 || mnth==5 || mnth==7 || mnth==8 || mnth==10 || mnth==12)      //For month with 31days
  {
    if(dt==32)
    {
      dt=1;
      mnth++;
    }
  }

  if(mnth==4 || mnth==6 || mnth==9 || mnth==11)      //For month with 30 days
  {
    if(dt==31)
    {
      dt=1;
      mnth++;
    }
  }
  if(mnth==2)
  {
    if(year%4==0 || year%400==0)
    {
      if(dt==30)
      {
        dt=1;
        mnth++;
      }
    }
    else
    {
      if(dt==29)
      {
        dt=1;
        mnth++;
      }
    }
  }
  if(mnth==12)    //<==
  {
    dt=1;
    mnth=1;
    year++;
  }

  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.setCursor(0,1);
  lcd.print(date[i]);
  lcd.setCursor(5,1);
  lcd.print("            ");
  lcd.setCursor(5,1);
  sprintf(dmy,"%02i-%02i-%02i", dt, mnth, year);
  lcd.print(dmy);
  
  temp = (((reading/1024.0)*5000)/10)+100;
  //temp=temp/1.1;
  lcd.setCursor(12,0);
  lcd.print("    ");
  lcd.setCursor(12,0);
  lcd.print(temp);
  lcd.setCursor(14,0);
  lcd.print((char)223);
  lcd.setCursor(15,0);
  lcd.print("C");
  
  if(i==8)      //original: i==8 then i=0;
  {
    i=0;
  }
  delay(500);
  s=s+1;           //<== *********** Controlling Instruction **************
  if(h==2)
  {
    h=0;
    //it=it+1;     //<=Demonstration of 12 hrs:: h==12:: it=it+1
  }
  //Add Switch section for DDMMYY To complete the code
}
