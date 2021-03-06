#include<Servo.h>
#include<EEPROM.h>
#include<SD.h>

/*
manometer wires to analog input 3 and gnd
servo.. brown=gnd, red=5v, orange=digital pin 8
*/
int hall = 9;
int done = 7;
int clockpin = 3;
int throtpin = 8;
boolean hstate = true;
boolean stopped = false;
long count = 0; // total number of rotations before car stops
int closed = 15;
int minAngle = 80;
int maxAngle = 130;
int clockCutoff = 10;
float RPM = 0;
long target_speed = 240;
int throttle_init = 110;
int inc_rate = 2;
int dec_rate = 2;
int sensitivity = 10;
double circum = 39.9;
int angle;
long startTime;
long endTime;

long howLongToRun = 10000;
long starting;

Servo throttle;
char filename[] = "datafile.txt";
File data;

void setup()
{
  throttle.attach(throtpin); 
  Serial.begin(9600);
  throttle.write(throttle_init);
  angle = throttle_init;
  pinMode(hall, INPUT);
  pinMode(done, INPUT);
  pinMode(clockpin, INPUT);
  pinMode(10, OUTPUT); //for SD card
  SD.begin(10);
  data = SD.open(filename, FILE_WRITE);
  data.println("~~~~~~~~~~~");
  data.close();
  starting = millis();
}

String floatPrint(float x){
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}

void SDWriteLn(){
    data = SD.open(filename, FILE_WRITE);
    data.println(String(angle, DEC) + ", " + floatPrint(RPM));
    data.close();
}

void checkEndAndRecord()
{
  if ((millis() - starting) >= howLongToRun) //end switch flipped or iodine end
  {
    throttle.write(closed);
    stopped = true;
    long distance = count*circum / 2;
    data = SD.open(filename, FILE_WRITE);
    data.println(String(distance, DEC));
    data.close();
    digitalWrite(done, HIGH); 
  }
}

void updateThrottle()
{
  if ((hstate==false)&&(stopped==false))
   {
     if ((RPM+sensitivity)<target_speed)
      {
        if(angle > maxAngle){
          angle = maxAngle;
        }
        else{
          //we're going too slow
          angle+=inc_rate;
        }
      }
     if ((RPM-sensitivity)>target_speed)
      {
        //we're going too fast
        if(angle < minAngle){
          angle = minAngle;
        }
        else{
          angle-=dec_rate; 
        }
      }
     throttle.write(angle);
     Serial.print("Angle = ");
     Serial.println(angle);
   }
}
void updateRotations()
{
  ++count; //count revolution for distance
  Serial.print("Count = ");
  Serial.println(count);
}

void calculateRPM(){
  float timeHalf = endTime - startTime;
  float fullRotateTime = timeHalf / 500; // 2 / 1000, 2 because 2 hall effect sensors, 1000 milliseconds to a second
  RPM = 60 / fullRotateTime;
  Serial.print("RPM = ");
  Serial.println(RPM);
}

void loop()
{
  checkEndAndRecord();
  //RPM and Revolution Monitoring
  if(digitalRead(hall)==HIGH) //magnet hasnt passed
  {
    hstate = false; //prevent multiple revolution counts in next block
    startTime = millis();
    while (digitalRead(hall)==HIGH)
    {
      checkEndAndRecord();
    }
    endTime = millis();    
  }
  //magnet crosses hall effect
  if (hstate==false)
   {
      updateRotations();
      calculateRPM();
   }
  updateThrottle();
  SDWriteLn(); //record angle and RPM
  hstate=true;   
 }
  
