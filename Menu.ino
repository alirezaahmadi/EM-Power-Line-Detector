void Menu()
{
  _Status=1;
  for (;;)
  {
    _Status=1;
    Header();   
    Pointer(0,&menu_index[0], &menu_index[1], menu_index[0], menu_index[1], 1, 4, 1);
    
    myGLCD.print("AS",5, 9);
    //
    myGLCD.print("MS",5, 9 + 8);
    //
    myGLCD.print("Ga",5, 9 + 8 * 2);
    //
    myGLCD.print("Ad",5, 9 + 8 * 3);
    //
    myGLCD.print("USB",5, 9 + 8 * 4);
    //
    myGLCD.print("BL",46, 9);
    //
    //myGLCD.print("Con",46, 9 + 8);
    //
    //myGLCD.print("Buz",46, 9 + 8 * 2);
    //
    myGLCD.print("Pow",46, 9 + 8);
    //

    myGLCD.update();

    if (button_press(Select_Btn, 150) == false)
    {
      if (menu_index[0] == 0)
      {
        switch (menu_index[1])
        {
          case 0:
            Auto_Search_M();
            break;
          case 1:
            Manual_Search();
            break;
          case 2:
            Gain_Menu();
            break;
          case 3:
            Adjust();
            break;
          case 4:
            USB_Connection();
            break;
        }
      }
      if (menu_index[0] == 1)
      {
        switch (menu_index[1])
        {
          case 0:
            Backlight_Setup();
            break;
          case 1:
            Power_Setup();
            break;
        }
      }
    }
    if (button_press(Setting_Btn, 150) == false && _Status == 1) {
      _Status = 0;
      break;
    }
    if (button_press(Search_Btn, 150) == false && _Status == 1) {
      Auto_Search_M();
    }
  }
}

void buzzer_Setup()
{
  _Status = 9;
  byte Buz_tmp = 20;
  for (;;)
  {
    if (button_press(Up_Btn, 150) == false) {
      Buz_tmp+=2;
      Buzzer(5, Buz_tmp, 1);
    }
    if (button_press(Down_Btn, 150) == false) {
      Buz_tmp-=2;
      Buzzer(5, Buz_tmp, 1);
    }
    if (button_press(Select_Btn, 150) == false) {
      Buz_Main = Buz_tmp;
      break;
    }
  }
}

void Contrast_Setup()
{
  _Status = 8;
  for (;;)
  {
    if (Contrast < 68) {
      if (button_press(Up_Btn, 150) == false) {
        Contrast = Contrast + 2;
      }
    }
    if (Contrast > 45) {
      if (button_press(Down_Btn, 150) == false) {
        Contrast = Contrast - 2;
      }
    }
    if (button_press(Select_Btn, 150) == false) {
      break;
    }
  }
}

void Backlight_Setup()
{
  _Status = 7;
  for (;;)
  {
    if (brightness < 250) {
      if (button_press(Down_Btn, 150) == false) {
        brightness = brightness + 10;
      }
    }
    if (brightness > 10) {
      if (button_press(Up_Btn, 150) == false) {
        brightness = brightness - 10;
      }
    }
    //if(EEPROM.read(Pow_Setting_EEPROM_ADD)==1){brightness=256;break;}
    analogWrite(6, brightness);
    EEPROM.write(Pow_Setting_EEPROM_ADD,brightness);
    EEPROM.write(Pow_Setting_EEPROM_ADD+30,brightness);
    if (button_press(Select_Btn, 150) == false) {
      break;
    }
    delay(5);
  }
}

void Power_Setup(void)
{
  _Status = 10;
  for (;;)
  {
    Header();
    Pointer(0,&Power_menu_index[0], &Power_menu_index[1], Power_menu_index[0], Power_menu_index[1], 0, 3, 0);

    myGLCD.print("Backlight",5, 9);
    myGLCD.print("Sound",5, 9 + 8);
    myGLCD.print("LP Alarm",5, 9 + 8 * 2);
    myGLCD.print("EEPROM",5,9 + 8 * 3);

    myGLCD.update();

    if (button_press(Select_Btn, 150) == false)
    {
      if (Power_menu_index[0] == 0)
      {
        switch (Power_menu_index[1])
        {
          case 0:
            myGLCD.clrScr();
            for(;;)
            {
              Header();
              Pointer(2, &Pow_BL_menu_index[0], &Pow_BL_menu_index[1], Pow_BL_menu_index[0], Pow_BL_menu_index[1], 1, 0, 0);
              myGLCD.print("Backlight:",5, 9);
              myGLCD.print("ON",5, 25);
              myGLCD.print("OFF",34, 25);

              myGLCD.update();
              
              if (button_press(Select_Btn, 150) == false) {
                if(Pow_BL_menu_index[0]==1)
                {
                  brightness=255;
                  analogWrite(6, brightness);
                  EEPROM.write(Pow_Setting_EEPROM_ADD,255);
                  EEPROM.write(Pow_Setting_EEPROM_ADD+30,255);
                }
                if(Pow_BL_menu_index[0]==0)
                {
                  brightness=240;
                  EEPROM.write(Pow_Setting_EEPROM_ADD,240);
                  EEPROM.write(Pow_Setting_EEPROM_ADD+30,240);
                  analogWrite(6, brightness);
                }
                break;
              }
            }
            break;
          case 1:
            for(;;)
            {
              Header();
              Pointer(2, &Pow_BL_menu_index[0], &Pow_BL_menu_index[1], Pow_BL_menu_index[0], Pow_BL_menu_index[1], 1, 0, 0);
              myGLCD.print("Sound:",5, 9);
              myGLCD.print("ON",5, 25);
              myGLCD.print("OFF",34, 25);

              myGLCD.update();
              
              if (button_press(Select_Btn, 150) == false) {
                EEPROM.write(Pow_Setting_EEPROM_ADD+1,Pow_BL_menu_index[0]);
                EEPROM.write((Pow_Setting_EEPROM_ADD+1)+30,Pow_BL_menu_index[0]);
                break;
              }
            }
            break;
          case 2:
            for(;;)
            {
              Header();
              Pointer(2, &Pow_BL_menu_index[0], &Pow_BL_menu_index[1], Pow_BL_menu_index[0], Pow_BL_menu_index[1], 1, 0, 0);
              myGLCD.print("LP Alarm:",5, 9);
              myGLCD.print("ON",5, 25);
              myGLCD.print("OFF",34, 25);

              myGLCD.update();
              
              if (button_press(Select_Btn, 150) == false) {
                EEPROM.write(Pow_Setting_EEPROM_ADD+2,Pow_BL_menu_index[0]);
                EEPROM.write((Pow_Setting_EEPROM_ADD+2)+30,Pow_BL_menu_index[0]);
                break;
              }
            }
            break;
            case 3:
            for(;;)
            {
              Header();
              Pointer(2, &Pow_BL_menu_index[0], &Pow_BL_menu_index[1], Pow_BL_menu_index[0], Pow_BL_menu_index[1], 1, 0, 0);
              myGLCD.print("EEPROM:",5, 9);
              myGLCD.print("Clr",5, 25);
              myGLCD.print("Load",34, 25);

              myGLCD.update();
                           
              if (button_press(Select_Btn, 150) == false) {
                if(Pow_BL_menu_index[0]==1)
                {
                  Backup_to_Main_EE();
                }
                if(Pow_BL_menu_index[0]==0)
                {
                  Reset_EEPROM();
                }
                break;
              }
            }
            break;
        }
      }
    }
    if (button_press(Setting_Btn, 150) == false ) 
    {
      myGLCD.clrScr();
      myGLCD.update();
      break;
    }
  }
}

void USB_Connection(void)
{
  _Status = 6;
  myGLCD.drawBitmap(0, 0,  USB_ok_Fotor, 84, 48);
  myGLCD.update();
  for(;;)
  {
    if(Serial.read()==255)
      if(Serial.read()==255)
        if(Serial.read()==195)
        {
          if (button_press(Setting_Btn, 300) == false ) 
          {
            myGLCD.clrScr();
            myGLCD.update();
            break;
          }
          myGLCD.invert(true);
          delay(500);
          if (button_press(Setting_Btn, 300) == false ) 
          {
            myGLCD.invert(false);
            myGLCD.clrScr();
            myGLCD.update();
            break;
          }
          myGLCD.invert(false);
          delay(500);
          //myGLCD.invert(false);
          //myGLCD.update();
        }
  if (button_press(Setting_Btn, 300) == false ) 
    {
      myGLCD.clrScr();
      myGLCD.update();
      _Status=1;
      break;
    }
  }
}


