/*/////////////////////////////////////////////////////
/ # Just God!!                                       #/
/ # ElectroMagnetic-Baised-PowerLineDetector...      #/
/ # Company    : Elecat Co.                          #/
/ # Website    : http://AhmadiAlireza.webs.com       #/
/ # Editor     : Alireza Ahmadi                      #/
/ # Date       : 2.13.2016                           #/
/ # Version    : 0.1                                 #/
/////////////////////////////////////////////////////*/

/*
 # Connect your LCD to the following Arduino pins:
 # pin 7 - Serial clock out (SCLK)
 # pin 5 - Serial data out (DIN)
 # pin 4 - Data/Command select (D/C)
 # pin 3 - LCD chip select (CS)
 # pin 2 - LCD reset (RST)
*/

#include <LCD5110_Graph.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>

//LCD init Command
LCD5110 myGLCD(7,5,4,2,3);
//Defins and Variables
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
extern uint8_t USB_ok_Fotor [];
extern unsigned char TinyFont[];
extern uint8_t flesh_down[];
extern uint8_t flesh_up[];
extern uint8_t flesh[];
extern uint8_t Level3_battery[];
extern uint8_t Level2_battery[];
extern uint8_t Level1_battery[];
extern uint8_t Empty_battery[];

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#define Setting_Btn 9
#define Up_Btn 12
#define Down_Btn 11
#define Select_Btn 13
#define Search_Btn 8

#define GA_EEPROM_ADD 16
#define Pow_Setting_EEPROM_ADD 24

byte brightness=240;
byte Contrast=55;
float battery=0;
//byte tmp=0;
byte cnt=0;
byte Buz_Main=20;
int menu_index[2]={0};
int Gain_menu_index[2]={0};
int Power_menu_index[2]={0};
int Ad_menu_index[2]={0};
int Pow_BL_menu_index[2]={0};
byte _Status=0;
unsigned short elapsed=0;
byte _press=0;
byte GA_status=0;
byte Gain_index=0;
float Signal[2]={0};
byte Power_line=0;
int AD_i[3]={0};
float tmp=0;
int analog_value=0;
byte _break=0;
byte _Reset=0;
int MS_i=0;
float Signal_00 = 0;
float Signal_10 = 0;
byte limit[8][2]=
{
  0,0,
  0,0,
  0,0,
  0,0,
  0,0,
  0,0,
  0,0,
  0,0,
};
byte limit_tmp[8][2];
byte Ad_tmp[3]={0};

void setup()   
{
  myGLCD.InitLCD(60);
  myGLCD.setFont(SmallFont);
  Serial.begin(115200);
  Serial.setTimeout(1);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A0, INPUT);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  digitalWrite(10, LOW); 
  brightness=EEPROM.read(Pow_Setting_EEPROM_ADD);
  analogWrite(6,brightness );
  myGLCD.clrScr();
  //setContrast(Contrast);
  testdrawcircle();
  myGLCD.clrScr();
myGLCD.update();
  //mode_change(7);
  Buzzer(100,255, 2);
  //Reset_EEPROM(); 
  EEPROM_Read(0);
  TMP_to_Main_EEPROM(0);
}

void loop() {
  _Status=0;
  if(button_press(Setting_Btn,150)==false){Menu();}
  if(button_press(Search_Btn,150)==false){Auto_Search_M();}
 
  Header();
 
  analog_value=analogRead(A7);
  tmp=(analog_value*5.0)/1024.0;
  myGLCD.printNumF(tmp*2.0,1,0,9+8*4);
  
  delay(5);
  myGLCD.printNumI(millis(),0,9+8*3);
  myGLCD.update();
  
  /*for(byte EE_cnt=0 ; EE_cnt<100 ; EE_cnt++)
  {
    Serial.print(EE_cnt);
    Serial.print(":\t");
    Serial.println(EEPROM.read(EE_cnt));
  }*/
pinMode(11, INPUT_PULLUP);
}

