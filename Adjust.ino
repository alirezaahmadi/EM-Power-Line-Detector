/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% by: Alireza Ahmadi                                     %
% University of Bonn- MSc Robotics & Geodetic Engineering%
% Alireza.Ahmadi@uni-bonn.de                             %
% AlirezaAhmadi.xyz                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void Adjust(void)
{
  _Status = 5;
  
  AD_i[0]=0;
  AD_i[1]=0;
  AD_i[2]=0;
  
  for(;;)
  {
    
    AD_i[1] = limit[AD_i[0]][0];
    AD_i[2] = limit[AD_i[0]][1];

    if (button_press(Setting_Btn, 150) == false && _Status== 5) 
    {
      AD_i[0]=0;
      break;
    }
    Up_Down_logo(0,10,30);
    Up_Down_logo(0,40,30);
    Up_Down_logo(0,67,30);
    
    Header();
    
    Pointer(1, &Ad_menu_index[0], &Ad_menu_index[1], Ad_menu_index[0], Ad_menu_index[1], 2, 0, 0);   
    
    switch (Ad_menu_index[0])
    {
      case 0:
      if(AD_i[0] <= 7)
        if(AD_i[0] >=0 ){
          if (button_press(Up_Btn, 150) == false ) 
          {
            AD_i[0]++;
          }
          if (button_press(Down_Btn, 150) == false) 
          {
            AD_i[0]--;
          }
          if(AD_i[0] < 0)AD_i[0]=0;
          if(AD_i[0] > 7)AD_i[0]=7;
        }
          Ad_tmp[0] = adjeust_Power(AD_i[0]);
          Ad_tmp[1] = limit[Ad_tmp[0]][0];
          Ad_tmp[2] = limit[Ad_tmp[0]][1];
          Signal_show_value(2, 0, 9,36,0,1);
          break;
      case 1:
          if (button_press(Up_Btn, 150) == false ) 
          {
            AD_i[1]++;
          }
          if (button_press(Down_Btn, 150) == false) 
          {
            AD_i[1]--;
          }
          Ad_tmp[1] = adjust_Signal_limit(Ad_tmp[0],0,(byte)AD_i[1]);
          EEPROM.write(Ad_tmp[0]*2,Ad_tmp[1]);
          EEPROM.write((Ad_tmp[0]*2)+30,Ad_tmp[1]);
          break;
      case 2:
          if (button_press(Up_Btn, 150) == false ) 
          {
            AD_i[2]++;
          }
          if (button_press(Down_Btn, 150) == false) 
          {
            AD_i[2]--;
          }
          Ad_tmp[2] = adjust_Signal_limit(Ad_tmp[0],1,AD_i[2]);
          EEPROM.write((Ad_tmp[0]*2)+1,Ad_tmp[2]);
          EEPROM.write(((Ad_tmp[0]*2)+1)+30,Ad_tmp[2]);
          break;
    } 
    
    Header();
    switch (Ad_tmp[0])
    {
      case 0:
      myGLCD.print("220",5, 35);
      break;
      case 1:
      myGLCD.print("4K",5, 35);
      break;
      case 2:
      myGLCD.print("20K",5, 35);
      break;
      case 3:
      myGLCD.print("33K",5, 35);
      break;
      case 4:
      myGLCD.print("63K",5, 35);
      break;
      case 5:
      myGLCD.print("132K",4, 35);
      break;
      case 6:
      myGLCD.print("230K",4, 35);
      break;
      case 7:
      myGLCD.print("400K",4, 35);
      break;
    }
    
    myGLCD.printNumI(Ad_tmp[1],35, 35);
    myGLCD.printNumI(Ad_tmp[2],62, 35);
    myGLCD.update();
       
  }
}

byte adjust_Signal_limit(byte Power_num, byte _Signal_num,byte val)
{
  Signal_show_value(2, 0, 9,36,0,1);
  limit[Power_num][_Signal_num] = val;
  return limit[Power_num][_Signal_num];
}

byte adjeust_Power(byte _Power_num)
{
  if(_Power_num <= 7 && _Power_num >= 0)
  {
    switch (_Power_num)
    {
      case 0:        
        mode_change(7);
        return 0;
        break;
      case 1:      
        mode_change(6);
        return 1;
        break;
      case 2:        
        mode_change(5);
        return 2;
        break;
      case 3:
        mode_change(4);
        return 3;
        break;
      case 4:
        mode_change(3);
        return 4;
        break;
      case 5:
        mode_change(2);
        return 5;
        break;
      case 6:
        mode_change(1);
        return 6;
        break;
      case 7:
        mode_change(0);
        return 7;
        break;
    }
  }
}
