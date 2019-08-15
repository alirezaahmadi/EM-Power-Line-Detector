/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% by: Alireza Ahmadi                                     %
% University of Bonn- MSc Robotics & Geodetic Engineering%
% Alireza.Ahmadi@uni-bonn.de                             %
% AlirezaAhmadi.xyz                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void Up_Down_logo(byte mode,byte x, byte y)
{
  if(mode==0)
  {
    myGLCD.drawBitmap(x,y,  flesh_up, 7, 4);
    myGLCD.drawBitmap(x,y+13,  flesh_down, 7, 4);
  }
  if(mode==1)
  {
    myGLCD.drawBitmap(x,y,  flesh_up, 7, 4);
    myGLCD.drawBitmap(x,y+23,  flesh_down, 7, 4);
  }
  myGLCD.update();
}

void Clear_Section(byte _x,byte _y,byte len_x, byte len_y)
{
  for(byte clear_cntx=_x; clear_cntx<len_x; clear_cntx++){
    for(byte clear_cnty=_y; clear_cnty<len_y; clear_cnty++){
        myGLCD.clrPixel(clear_cntx,clear_cnty);
         myGLCD.update();
    }
  }
  
}

void Anten_logo(byte Num, byte Debaouce )
{
 for(byte i=0;i<Num;i++)
  {
    Header();
    for (int16_t i=0; i<20; i+=2) {
      myGLCD.drawCircle((84/2)+20, (48/2)+5, i);
       myGLCD.update();
    }
    for (int16_t i=20; i>0; i-=2) {
      myGLCD.clrCircle((84/2)+20, (48/2)+5, i);
       myGLCD.update();
    }
  }
}

void Header(void)
{
  Battery_logo();
  if(EEPROM.read(Pow_Setting_EEPROM_ADD+2)==0)
  {
    if(battery < 7.5)
    {
      //Buzzer(100,255, 1);
    }
  }
  myGLCD.drawLine(0, 7,84,7);
  myGLCD.print("EMP",0,0);
  myGLCD.update();
  switch(_Status)
    {
      case 0:
      myGLCD.print("Main",38,0);
      myGLCD.update();
      break;
      case 1:
      myGLCD.print("Menu",38,0);
      myGLCD.update();
      break;
      case 2:
      myGLCD.print("AS",38,0);  
      break;
      case 3:
      myGLCD.print("MS",38,0);
      break;
      case 4:
      myGLCD.print("Ga",38,0);
      break;
      case 5:
      myGLCD.print("Ad",38,0);
      break;
      case 6:
      //myGLCD.print("USB",38,0);
      break;
      case 7:
      myGLCD.print("BL",38,0);
      break;
      case 8:
      myGLCD.print("Con",38,0);
      break;
      case 9:
      myGLCD.print("Buz",38,0);
      break;
      case 10:
      myGLCD.print("Pow",38,0);
      break;
    }
  myGLCD.update();
  
  
}

void testdrawcircle(void) {
  for (int16_t i=0; i<48; i+=2) {
    myGLCD.drawCircle((84/2), (48/2), i); 
    myGLCD.update();   
    delay(5);
  }
}

void Pointer(byte axis, int *cul_x, int *line_y, int go_cul_x, int go_line_y, int limit_x, int limit_y0, int limit_y1)
{
  int cul=0;
  int line=0;

  cul = go_cul_x;
  line = go_line_y;
  if(axis==0)
  {
    if(button_press(Up_Btn,150)==false){line--;}
    if(button_press(Down_Btn,150)==false){line++;}
    if(limit_x==0)
    {
      if(line<=-1 && cul==0 ){cul=0; line=limit_y0;}
      if(line>=limit_y0+1 && cul==0 ){cul=0; line=0;}
    }
    if(limit_x==1)
    {
      if((line <= -1) && (cul == 0) ){cul=1; line=limit_y1;}
      if((line >= limit_y0+1) && (cul == 0) ){cul=1; line=0;}
      if((line > limit_y1) && (cul == 1) ){cul=0; line=0;} 
      if((line <= -1) && (cul == 1) ){cul=0; line=limit_y0;}
    }
    myGLCD.drawBitmap(cul*40,9+line*8,  flesh,  4, 8);
    //myGLCD.update();
  }
  if(axis==1)
  {
    //if(button_press(Up_Btn,150)==false){cul++;myGLCD.clrScr();}
    //if(button_press(Down_Btn,150)==false){cul--;myGLCD.clrScr();}
    
    if(button_press(Select_Btn,150)==false){cul++;}
    
    Header();
    
    //if(cul<=-1){cul=limit_x;}
    if(cul>=limit_x+1){cul=0;}

    myGLCD.drawBitmap(cul*29,35,  flesh,  4, 8);
    //myGLCD.update();   
  }

   if(axis==2)
  {
    if(button_press(Up_Btn,150)==false){cul++;}
    if(button_press(Down_Btn,150)==false){cul--;}
    
    Header();
    
    if(cul<=-1){cul=limit_x;}
    if(cul>=limit_x+1){cul=0;}

    myGLCD.drawBitmap(cul*28,25,  flesh, 4, 8);
    //myGLCD.update();
    //(0,40);
    //print(cul);
    
  }
  

  myGLCD.update();
  *cul_x = cul;
  *line_y = line; 
}

void Battery_logo()
{
 analog_value=analogRead(A7);
 tmp=(analog_value*5.0)/1024.0;
 battery=tmp*2.0;
 //(60,9);
 //myGLCD.printNumI(battery);
 //
if(battery>=4.0)
 {
 myGLCD.drawBitmap(68, 0,  Empty_battery, 16, 6);
 }
  if(battery>=6.0 && battery<7.0)
 {
 myGLCD.drawBitmap(68, 0,  Level1_battery, 16, 6);
 }
  if(battery>=7.0 && battery<7.9)
 {
 myGLCD.drawBitmap(68, 0,  Level2_battery, 16, 6);
 } 
 if(battery>=7.9)
 {
 myGLCD.drawBitmap(68, 0,  Level3_battery, 16, 6);
 }
 myGLCD.update();
}

