#define pedgreen 10
#define pedred 9
#define cargreen 5
#define caryellow 6
#define carred 3
#define st_cp 11
#define ds 12
#define sh_cp 13
#define led_1 7
#define led_2 8
#define button_auto 4
#define button_manual 1
#define button_change 2
int mode;
int temp1=0;
int temp2=0;
int button_state1=0;
int button_state3=0;
int button_state2;
int button_prev1 = 0;
int button_prev2 = 0;
//byte a[] = {0xF6,0xFE,0xE0,0xBE,0xB6,0x66,0xF2,0xDA,0x60,0xFC};
byte b[] = {0x6F,0x7F,0x07,0x7D,0x6D,0x66,0x4F,0x5B,0x06,0x3F};
void setup() 
{
  for (int i = 0; i<12; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}
void cargreentoyellow()
{
  analogWrite(cargreen, 200);
  //digitalWrite(cargreen, LOW);
  analogWrite(carred, 0);
}
void caryellowtored()
{
  analogWrite(pedred, 255);
  analogWrite(cargreen, 255);
  analogWrite(carred, 0);
  analogWrite(pedgreen, 0);
}
void blinklight()
{
    digitalWrite(pedgreen, HIGH);
    delay(200);
    digitalWrite(pedgreen, LOW);
    delay(200);
}
void timecount(int second)
{
   for (int j=99-second; j<100;j++)
  {
    for (int i=0; i< 370;i++) {
    digitalWrite(led_1, 1);
    digitalWrite(st_cp, LOW);
    shiftOut(ds, sh_cp, MSBFIRST, b[j%10]);
    digitalWrite(st_cp, HIGH);
    digitalWrite(led_2, 0);
    delay(1);
    digitalWrite(led_2, 1);
    digitalWrite(st_cp, LOW);
    shiftOut(ds, sh_cp, MSBFIRST, b[j/10]);
    digitalWrite(st_cp, HIGH);
    digitalWrite(led_1, 0);
    delay(1);
    /*if (carred == HIGH && j >96)
    {
      blinklight();
    }*/
    }
  }
}
void nonecrowd()
{
  analogWrite(carred, 255);
  analogWrite(pedgreen, 255);
  analogWrite(cargreen, 0);
  analogWrite(pedred, 0);
  timecount(10);
  cargreentoyellow();
  timecount(3);
  caryellowtored();
  timecount(10);
  analogWrite(carred, 255);
  analogWrite(cargreen, 255);
  analogWrite(pedgreen,255);
  analogWrite(pedgreen,255);
  delay(500);
}
void crowd()
{
  
  button_state2=digitalRead(button_change);
  if(button_state2==HIGH && button_prev2==LOW)
  {
    if (temp2==0)
    {
      analogWrite(cargreen, 0);
      analogWrite(pedred, 0);
      analogWrite(carred, 255);
      analogWrite(pedgreen, 255);
      temp2=1;
    }
    else
    {
      analogWrite(cargreen, 255);
      analogWrite(pedred, 255);
      analogWrite(carred, 0);
      analogWrite(pedgreen, 0);
      temp2=0;
    }
  }
  button_prev2=button_state2;
  
}
void loop()
{
  button_state1 = 0;
  button_state3 = 0;
  button_state1 = digitalRead(button_auto);
  button_state3 = digitalRead(button_manual);
  if(button_state1==HIGH && button_state3==LOW)
  {
    mode=1;
  }
  if(button_state3==HIGH)
  {
    mode=2;
  }
  if(mode==1)
  {
    nonecrowd();
  }
  else if (mode==2)
  {
    crowd();
  }
}
