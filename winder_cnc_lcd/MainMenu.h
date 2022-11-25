//show main menu
class MainMenu :public Screen {

  private:
    int turns_to_do_field [4] {200 ,  // x from
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
    my_lcd.Fill_Screen(background);

    show_string("WINDER CNC", 10,10 ,2,WHITE, BLACK,1);

    my_scattering.draw_all();
    my_rpm.draw_all();
    my_winder.draw_all();
    my_turns.draw_all();

  }

  void do_actions(){
    my_scattering.do_actions(touch_x, touch_y);
    my_rpm.do_actions(touch_x, touch_y);
    if ( my_winder.do_actions(touch_x, touch_y) ) {
      
      // int turns_to_go = my_turns.getValue() - my_winder.query_completed_turns() ;
      int turns_to_go = my_turns.getValue();

      // Serial.println("turns to go :" + String(turns_to_go));
      if ( turns_to_go >= 50){
          my_winder.run(turns_to_go,
                        my_scattering.get_selected_value(),
                        my_rpm.get_selected_value());
          my_winder.query_completed_turns();
          my_winder.draw_completed (my_winder.query_completed_turns() );
      }
      // }
    };

    if ( my_turns.do_actions(touch_x, touch_y) ) {

      int numeric_pad_value = my_numpad.show();
      my_turns.setValue (numeric_pad_value);
      show();

    };
  }



 };
