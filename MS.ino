/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% by: Alireza Ahmadi                                     %
% University of Bonn- MSc Robotics & Geodetic Engineering%
% Alireza.Ahmadi@uni-bonn.de                             %
% AlirezaAhmadi.xyz                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void Manual_Search(void)
{
  MS_i=0;
  _Status = 3;
  while (true)
  {
    if (button_press(Setting_Btn, 150) == false && _Status== 3) 
    {
      break;
    }
    if (button_press(Up_Btn, 150) == false && MS_i < 7 ) 
    {
      MS_i++;
    }
    if (button_press(Down_Btn, 150) == false && MS_i >= 1) 
    {
      MS_i--;
    }

    Up_Down_logo(0,70,20);
    Signal_show_value(3, 2, 10,0,17, 2);
    
    switch ((byte)MS_i)
    {
      case 0:
        myGLCD.print("220 ",65, 25);
        Power_line=7;
        mode_change(EEPROM.read(GA_EEPROM_ADD + Power_line));
        break;
      case 1:
        myGLCD.print("4K  ",67, 25);
        Power_line=6;
        mode_change(EEPROM.read(GA_EEPROM_ADD + Power_line));
        break;
      case 2:
        myGLCD.print("20K ",65, 25);
        Power_line=5;
        mode_change(EEPROM.read(GA_EEPROM_ADD + Power_line));
        break;
      case 3:
        myGLCD.print("33K ",65, 25);
        Power_line=4;
        mode_change(EEPROM.read(GA_EEPROM_ADD + Power_line));
        break;
      case 4:
        myGLCD.print("63K ",65, 25);
        Power_line=3;
        mode_change(EEPROM.read(GA_EEPROM_ADD + Power_line));
        break;
      case 5:
        myGLCD.print("132K",60, 25);
        Power_line=2;
        mode_change(EEPROM.read(GA_EEPROM_ADD + Power_line));
        break;
      case 6:
        myGLCD.print("230K",60, 25);
        Power_line=1;
        mode_change(EEPROM.read(GA_EEPROM_ADD + Power_line));
        break;
      case 7:
        myGLCD.print("400K",60, 25);
        Power_line=0;
        mode_change(EEPROM.read(GA_EEPROM_ADD + Power_line));
        break;
    }
    Header();
  }
}
