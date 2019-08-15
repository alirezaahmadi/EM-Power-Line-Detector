/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% by: Alireza Ahmadi                                     %
% University of Bonn- MSc Robotics & Geodetic Engineering%
% Alireza.Ahmadi@uni-bonn.de                             %
% AlirezaAhmadi.xyz                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void Gain_Menu(void)
{
  _Status = 4;
  for(;;)
  {
    if(GA_status==0)
    {
      for(;;)
      {
        Header();
        Pointer(0,&Gain_menu_index[0], &Gain_menu_index[1], Gain_menu_index[0], Gain_menu_index[1], 1, 4, 2);
        
        myGLCD.print("220V ",5, 9);
        myGLCD.print("4KV  ",5, 9 + 8);
        myGLCD.print("20KV ",5, 9 + 8 * 2);
        myGLCD.print("33KV ",5, 9 + 8 * 3);
        myGLCD.print("63KV ",5, 9 + 8 * 4);
        myGLCD.print("132KV",46, 9);
        myGLCD.print("230KV",46, 9 + 8);
        myGLCD.print("400KV",46, 9 + 8 * 2);

        myGLCD.update();
  
        if (Gain_menu_index[0] == 0)
        {
          switch (Gain_menu_index[1])
          {
            case 0:
              Power_line = 7;
              break;
            case 1:
              Power_line = 6;
              break;
            case 2:
              Power_line = 5;
              break;
            case 3:
              Power_line = 4;
              break;
            case 4:
              Power_line = 3;
              break;
          }
        }
        if (Gain_menu_index[0] == 1)
        {
          switch (Gain_menu_index[1])
          {
            case 0:
              Power_line = 2;
              break;
            case 1:
              Power_line = 1;
              break;
            case 2:
              Power_line = 0;
              break;
          }
        }
        if (button_press(Select_Btn, 150) == false)
        {
          GA_status=1;
          myGLCD.clrScr();
          myGLCD.update();
          break;
        }
        if (button_press(Setting_Btn, 150) == false)
        {
          GA_status=0;
          myGLCD.clrScr();
          myGLCD.update();
          _break=1;
          break;
        }
      }
    }
    
    if(_break==1){_break=0;break;}
    
    if(GA_status==1)
    {
      for(;;)
      {
        Header();
        Pointer(0,&Gain_menu_index[0], &Gain_menu_index[1], Gain_menu_index[0], Gain_menu_index[1], 1, 4, 2);
        
        myGLCD.print("%100",5, 9);
        myGLCD.print("%70 ",5, 9 + 8);
        myGLCD.print("%50 ",5, 9 + 8 * 2);
        myGLCD.print("%25 ",5, 9 + 8 * 3);
        myGLCD.print("%10 ",5, 9 + 8 * 4);
        myGLCD.print("%5  ",46, 9);
        myGLCD.print("%2.5",46, 9 + 8);
        myGLCD.print("%0  ",46, 9 + 8 * 2);

        myGLCD.update();
  
        if (Gain_menu_index[0] == 0)
        {
          switch (Gain_menu_index[1])
          {
            case 0:
              Gain_index = 7;
              break;
            case 1:
              Gain_index = 6;
              break;
            case 2:
              Gain_index = 5;
              break;
            case 3:
              Gain_index = 4;
              break;
            case 4:
              Gain_index = 3;
              break;
          }
        }
        if (Gain_menu_index[0] == 1)
        {
          switch (Gain_menu_index[1])
          {
            case 0:
              Gain_index = 2;
              break;
            case 1:
              Gain_index = 1;
              break;
            case 2:
              Gain_index = 0;
              break;
          }
        }
        if (button_press(Select_Btn, 150) == false)
        {
          GA_status=0;
          EEPROM.write(Power_line + GA_EEPROM_ADD,Gain_index);
          EEPROM.write((Power_line + GA_EEPROM_ADD)+30,Gain_index);
          break;
        }
      }
    }
  }
}
