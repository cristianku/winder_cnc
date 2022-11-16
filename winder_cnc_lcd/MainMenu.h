//show main menu
class MainMenu :public Screen {

  private:
    int turns_to_do_field [9] {200 ,  // x from
                            80,     // y from
                            300,    // x to      
                            120};    // y to


  public:

  Scattering my_scattering;
  Rpm my_rpm;
  Winder my_winder;
  Turns my_turns;
  NumPad my_numpad;

  int turns_to_do = 0;

  show(){
    my_scattering.draw_all();
    my_rpm.draw_all();
    my_winder.draw_all();
    my_turns.draw_all();

  }

  void do_actions(){
      my_scattering.do_actions(touch_x, touch_y);
      my_rpm.do_actions(touch_x, touch_y);
      if ( my_winder.do_actions(touch_x, touch_y) ) {
        
        my_winder.run(my_turns.getValue(), 
                      my_scattering.get_selected_value(),
                      my_rpm.get_selected_value());

      };

      if ( my_turns.do_actions(touch_x, touch_y) ) {
        
        int numeric_pad_value = my_numpad.show();
        my_turns.setValue (numeric_pad_value);
        my_lcd.Fill_Screen(background);
        show();

      };


      }


  //  my_lcd.Fill_Round_Rectangle(5, 0, (my_lcd.Get_Display_Width()-20)/3+5,COLORBOXSIZE/2+20, 5);
  //  my_lcd.Fill_Round_Rectangle((my_lcd.Get_Display_Width()-20)/3*2+15, 0, (my_lcd.Get_Display_Width()-20)/3*3+15,COLORBOXSIZE/2+20, 5);
  //  my_lcd.Set_Draw_color(MAGENTA);
  //  my_lcd.Fill_Round_Rectangle((my_lcd.Get_Display_Width()-20)/3+10, 0, (my_lcd.Get_Display_Width()-20)/3*2+10,COLORBOXSIZE/2+20, 5);
  //  show_string("RUN",5+((my_lcd.Get_Display_Width()-20)/3-72)/2-1,((COLORBOXSIZE/2+20)-16)/2,2,BLUE, BLACK,1);
  //  show_string("SPEED 300",(my_lcd.Get_Display_Width()-20)/3+10+((my_lcd.Get_Display_Width()-20)/3-60)/2-1,((COLORBOXSIZE/2+20)-16)/2,2,WHITE, BLACK,1);
  //  show_string("SPEED 500",(my_lcd.Get_Display_Width()-20)/3*2+15+((my_lcd.Get_Display_Width()-20)/3-84)/2-1,((COLORBOXSIZE/2+20)-16)/2,2,BLUE, BLACK,1);

  // entry box number of winds
  // char * value_selected_numpad_uuint8 = new char [numeric_pad_value.length() + 1];
  // strcpy (value_selected_numpad_uuint8, numeric_pad_value.c_str());
  // show_string("Turns to wind:", 5, 95 ,2,WHITE, BLACK,1);

  // draw_button(value_selected_numpad_uuint8, // uint8_t *desc,
  //           turns_to_wind_field[0],   // int16_t x_from, 
  //           turns_to_wind_field[1],   // int16_t y_from, 
  //           turns_to_wind_field[2],   // int16_t x_to, 
  //           turns_to_wind_field[3],   // int16_t y_to, 
  //           turns_to_wind_field[4],   // int16_t corner_radius, 
  //           turns_to_wind_field[5],   //int16_t text_dimension ,
  //           turns_to_wind_field[6]    //int16_t button_color
  //         );

  // // show scattering
  // show_string("Scattering:", 5, 145 ,2,WHITE, BLACK,1);

  // draw_scattering_buttons();
        // scattering

  // for ( int i = 0; i < total_menu_elements ; ++i ) {

  //     // my_lcd.Fill_Round_Rectangle(buttons[i][0], buttons[i][1], buttons[i][2],buttons[i][3], buttons[i][4]);
    
  //     // show_string(buttons_desc[i], buttons[i][0] + 20,get_y_text_pos (buttons[i][3] , buttons[i][1],buttons[i][5]) ,buttons[i][5],BLACK, BLACK,1);
  //     Serial.println(buttons_desc[i]);
  //     draw_button(buttons_desc[i], // uint8_t *desc,
  //                 buttons[i][0],   // int16_t x_from, 
  //                 buttons[i][1],   // int16_t y_from, 
  //                 buttons[i][2],   // int16_t x_to, 
  //                 buttons[i][3],   // int16_t y_to, 
  //                 buttons[i][4],   // int16_t corner_radius, 
  //                 buttons[i][5],   //int16_t text_dimension ,
  //                 buttons[i][6]    //int16_t button_color
  //               );
  //   }
        // scattering


  // show_string("+200 turns", button_200_turns[0] + 5,button_200_turns[1] + 10 ,2,BLUE, BLACK,1);

  // show_string("+200 turns",my_lcd.Get_Display_Width()/3 + 15,40,2,BLUE, BLACK,1);

  // show_string("+350 turns",my_lcd.Get_Display_Width()/3*2 + 15,40,2,BLUE, BLACK,1);


  // show_string("+900 turns",15,90,2,BLUE, BLACK,1);

  // Serial.println(my_lcd.Get_Display_Width());
  // Serial.println(my_lcd.Get_Display_Height());

 };
