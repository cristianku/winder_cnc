class Screen {
  // LCDWIKI_KBV myLcd ;

  private:

int buttons [1] [4]= {{0,0,0,0}} ;

String desc [1] = {""};

  public:
  int touch_x;
  int touch_y;
  TouchScreen mytouch = TouchScreen(XP, YP, XM, YM, 300);
  TSPoint tp;                      //Touchscreen_due branch uses Point

  void Read_Resistive(void)
{
    tp = mytouch.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
}

bool is_pressed(void)
{
    bool state;
    Read_Resistive();

    if ( tp.z > MINPRESSURE && tp.z  < MAXPRESSURE)
    { convert_point(); 
      return true; }
    else
    {return false;}


}


void convert_point(void)
{

    touch_x = map(tp.y, TS_BOT, TS_TOP, 0, my_lcd.Get_Display_Width());

    touch_y = my_lcd.Get_Display_Height() - map(tp.x, TS_LEFT, TS_RT, 0, my_lcd.Get_Display_Height());

}


  int16_t get_y_text_pos( int16_t y_from,int16_t y_to , int16_t text_size){
    if ( text_size == 2 ){    
      switch (text_size) { 
        case 2:
          return ((y_to - y_from)  /2  + y_from - 5);   
          break;


        default: 
          // instruction
          break;
      }
    }

  }

  void show_string(String str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
  {
      my_lcd.Set_Text_Mode(mode);
      my_lcd.Set_Text_Size(csize);
      my_lcd.Set_Text_colour(fc);
      my_lcd.Set_Text_Back_colour(bc);
      my_lcd.Print_String(str,x,y);
  }


  void draw_button(String desc,
                  int16_t x_from, 
                  int16_t y_from, 
                  int16_t x_to, 
                  int16_t y_to, 
                  int16_t corner_radius, 
                  int16_t text_dimension ,
                  int16_t button_color
                  ){


        switch (button_color) { 
        case 1:
          my_lcd.Set_Draw_color(GREY);
          break;

        case 2:
          my_lcd.Set_Draw_color(MAGENTA);
          break;

        case 3:
          my_lcd.Set_Draw_color(YELLOW);
          break;

        case 4:
          my_lcd.Set_Draw_color(WHITE);
          break;

        case 5:
          my_lcd.Set_Draw_color(BLACK);
          break;

        default: 
          my_lcd.Set_Draw_color(GREY);
          break;
        }



        my_lcd.Fill_Round_Rectangle(x_from, y_from, x_to,y_to, corner_radius);
        // Serial.println("Screen: draw_button");
        show_string(desc, x_from + 20,get_y_text_pos (y_to , y_from,text_dimension) ,text_dimension,BLACK, BLACK,1);

  }

   

   

  

};  