// AutoSearch functions
void Auto_Search_M(void)
{
  _Status = 2;
  while (true)
  { 
    _Reset=0;
    _break=0;
    Auto_Search(EEPROM.read(GA_EEPROM_ADD + 0), limit[7][0], limit[7][1], "400KV", "400", 5000, 2, 0);
    if(_break==1)break;
    if(_Reset==1)continue;
    Auto_Search(EEPROM.read(GA_EEPROM_ADD + 1), limit[6][0], limit[6][1], "230KV", "230", 5000, 2, 1);
    if(_break==1)break;
    if(_Reset==1)continue;
    Auto_Search(EEPROM.read(GA_EEPROM_ADD + 2), limit[5][0], limit[5][1], "132KV", "132", 5000, 2, 2);
    if(_break==1)break;
    if(_Reset==1)continue;
    Auto_Search(EEPROM.read(GA_EEPROM_ADD + 3), limit[4][0], limit[4][1], "63KV ", "63", 5000, 2, 3);
    if(_break==1)break;
    if(_Reset==1)continue;
    Auto_Search(EEPROM.read(GA_EEPROM_ADD + 4), limit[3][0], limit[3][1], "33KV ", "33", 5000, 2, 4);
    if(_break==1)break;
    if(_Reset==1)continue;
    Auto_Search(EEPROM.read(GA_EEPROM_ADD + 5), limit[2][0], limit[2][1], "20KV ", "20", 5000, 2, 5);
    if(_break==1)break;
    if(_Reset==1)continue;
    Auto_Search(EEPROM.read(GA_EEPROM_ADD + 6), limit[1][0], limit[1][1], "4KV  ", "4", 5000, 2, 6);
    if(_break==1)break;
    if(_Reset==1)continue;
    Auto_Search(EEPROM.read(GA_EEPROM_ADD + 7), limit[0][0], limit[0][1], "220V ", "220", 5000, 2, 7);
    if(_break==1)break; 
    if(_Reset==1)continue;
    
    if (button_press(Setting_Btn, 150) == false && _Status == 2) 
    {
      break;
    }
  }
}

byte Auto_Search(byte _Mode, float Signal0_limit, float Signal1_limit, char _name[],char _name1[], unsigned short debounce, byte buz_count,byte num)
{
  unsigned short _elapsed=0;
  myGLCD.clrScr(); 
  myGLCD.update();
  myGLCD.print(_name,10, 33);
  myGLCD.update();
  mode_change(_Mode);
  Signal_00 = Signal[0];
  Signal_10 = Signal[1];
  _elapsed =  (unsigned short)millis();
  for (;;)
  {
    if (button_press(Search_Btn, 150) == false) 
    {
      Header();
      delay(2000);
      _break=0;
      _Reset=1;
      break;
    }
    myGLCD.print("Please",5, 10);
    myGLCD.print(" wait! ",3, 19); 
    myGLCD.update(); 
    Anten_logo(1, 120);
    
    Update_Signals();
    
    if (Signal[0] >= Signal0_limit && Signal[1] >= Signal1_limit)
    {
      myGLCD.clrScr(); 
      myGLCD.update();
      Buzzer(50, 255, buz_count);
      Header();
      //setTextSize(1);
      myGLCD.print("Power Line",11, 9);
      myGLCD.print(" Detected!",9, 18);
      myGLCD.setFont(MediumNumbers);
      myGLCD.print(_name1,19, 30);
      myGLCD.update();   
      if(num==7)
      {
        myGLCD.setFont(SmallFont);
        myGLCD.print("V",75, 40);
        myGLCD.update(); 
      }
      else
      {
        myGLCD.setFont(SmallFont);
        myGLCD.print("KV",70, 40);
        myGLCD.update(); 
      }
      delay(5000);
      myGLCD.setFont(SmallFont);
      myGLCD.update(); 
      myGLCD.clrScr();      
      _break==1;
    }
    //Extending the Search time based on enhancement of input singal value
    if(Signal[1] > Signal_10)
    {
      debounce+=(debounce/5);
    }

    if(Signal[1] > 2 && _Mode!=7)
    {
      mode_change(_Mode+1);
      debounce+=(debounce/2);
    }
    
    if( (unsigned short)debounce <  (unsigned short)(millis() - _elapsed))
    {
      myGLCD.update();
      _elapsed=0;
      break;
    }
    
    if (button_press(Setting_Btn, 150) == false && _Status == 2) 
    {
      _break=1;
      break;
    }
  }
  return 0;
}

