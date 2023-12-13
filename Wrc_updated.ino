#include "PS2X_lib.h"  //for v1.6

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;

int joy1x ;
int joy1y ;
int joy2x ;
int joy2y ;
int pwm;

int Ena = 5;
//int Enb = ;
int M1a = 4;
int M1b = 2;
int M2a = 6;
int M2b = 3;


void Left()
{
  digitalWrite(M1a,LOW);
  digitalWrite(M1b,HIGH);
  digitalWrite(M2a,HIGH);
  digitalWrite(M2b,LOW);
  }

  
void Right()
{
  digitalWrite(M1a,HIGH);
  digitalWrite(M1b,LOW);
  digitalWrite(M2a,LOW);
  digitalWrite(M2b,HIGH);
  }

void Fwd()
{
  digitalWrite(M1a,HIGH);
  digitalWrite(M1b,LOW);
  digitalWrite(M2a,HIGH);
  digitalWrite(M2b,LOW);
  }

void Bwd()
{
  digitalWrite(M1a,LOW);
  digitalWrite(M1b,HIGH);
  digitalWrite(M2a,LOW);
  digitalWrite(M2b,HIGH);
  }

void Stop()
{
  digitalWrite(M1a,LOW);
  digitalWrite(M1b,LOW);
  digitalWrite(M2a,LOW);
  digitalWrite(M2b,LOW);
  }

void setup() {
   Serial.begin(115200);
  
  error = ps2x.config_gamepad(9,11,10,12, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  
  if(error == 0){
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

 else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
  type = ps2x.readType(); 
    
  switch(type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
    default:
      break;
  }

  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(2,OUTPUT);
  //digitalWrite(1,LOW);
  
}

void loop() {


   ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
     
         
   // if(ps2x.Button(PSB_PAD_UP)) 
   {         //will be TRUE as long as button is pressed
    //  Serial.println("UP is being held");
    }
 /*   if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.println("Right is being held");
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.println("LEFT is being held");
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.println("DOWN is being held");
    }   
*/
         
   joy1x= ps2x.Analog(PSS_LX);
   joy1y= ps2x.Analog(PSS_LY);
   joy2x= ps2x.Analog(PSS_RX);
   joy2y= ps2x.Analog(PSS_RY);
   
  if(joy1x<128 && joy2x==128){
  pwm = map(joy1x,128,0,0,255);

  }
  if(joy1x>128 ){
  pwm=  map(joy1x,128,255,0,255);
  }
  if(joy1y<128 ){
  pwm = map(joy1y,128,0,0,255);

  }
  if(joy1y>128){
  pwm=  map(joy1y,128,255,0,255);
  }
 if(joy1x==128 && joy2x==128 && joy1y==128 && joy2y==128)
  {
    pwm=0;
  }
  
 /* if(joy1y<128 && joy2y<128) 
    {
      pwm=255;
      }  

  if(joy1y>128 && joy2y>128) 
    {
      pwm=255;
      }
*/
 if(joy1x<128 && joy2x<128){
  pwm = 128;

  }
  if(joy1x>128 && joy2x>128){
  pwm=  128;
  }
        
//Serial.print("pwm1 = ");
  //  Serial.println(pwm);
 Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); // LY
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); // LX
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); // RY
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); // RX
    
  analogWrite(Ena,pwm);
  // analogWrite(Enb,pwm);

  
  if(joy1x<128 || joy2x<128)
  {
   Right();
   }
  
  if(joy1x>128 || joy2x>128)
  {
   Left();
   }
  
  if(joy1y<128)
  {
   Fwd();
   }
  
  if(joy1y>128){
   Bwd();
   }
  
  if((joy1x==128 && joy1y==128)||(joy1x==255 && joy1y==255)||(joy2x==255))
  {
   Stop();
   
   }
      
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); // LY
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); // LX
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); // RY
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); // RX
    } 
    
 delay(100);
 }
