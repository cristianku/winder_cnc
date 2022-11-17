
class NumPad: public Screen {

public:
int touch_x = 0;
int touch_y = 0;

 int numeric_pad_width = 480/7;
 int numeric_pad_rect_y_from = 10;

 int numeric_pad_rect_x_from = 120;

 int numeric_pad_rect_y_to = 380;
 int numeric_pad_rect_x_to = 380;
String numeric_pad_value = "0";


int numeric_pad [14][4] {
  // container
{
   numeric_pad_rect_x_from ,
   numeric_pad_rect_y_from,
   numeric_pad_rect_x_to,
   numeric_pad_rect_y_to

},
// number rectangle
{
   numeric_pad_rect_x_from + 15,
   numeric_pad_rect_y_from + 10,
   numeric_pad_rect_x_to - 20,
   numeric_pad_rect_y_from + 70

},

// FIRST LINE
{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*0,
   70 +30,
   numeric_pad_rect_x_from + 30  -15 + numeric_pad_width*1,
   70 +70

},

{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*1,
   70 +30,
   numeric_pad_rect_x_from + 30  -15 + numeric_pad_width*2,
   70 +70

},

{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*2,
   70 +30,
   numeric_pad_rect_x_from + 30  -15 + numeric_pad_width*3,
   70 +70

},

// second line
{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*0,
   70 +80,
   numeric_pad_rect_x_from + 30  - 15  + numeric_pad_width*1, 
   70 +120
},
{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*1,
   70 +80,
   numeric_pad_rect_x_from + 30  - 15  + numeric_pad_width*2,
   70 +120
},
{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*2,
   70 +80,
   numeric_pad_rect_x_from + 30  -15 + numeric_pad_width*3,
   70 +120

 },
// third line
{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*0,
   70 +130,
   numeric_pad_rect_x_from + 30  - 15  + numeric_pad_width*1,
   70 +170

},
{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*1,
   70 +130,
   numeric_pad_rect_x_from + 30  -15 + numeric_pad_width*2,
   70 +170

},
{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*2,
   70 +130,
   numeric_pad_rect_x_from + 30  -15 + numeric_pad_width*3,
   70 +170

},
// fourth line
{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*0,
   70 +180,
   numeric_pad_rect_x_from + 30  - 15 + numeric_pad_width*1, 
   70 +220

},
{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*1,
   70 +180,
   numeric_pad_rect_x_from + 30  -15 + numeric_pad_width*2,
   70 +220

},
{
   numeric_pad_rect_x_from + 30 + numeric_pad_width*2,
   70 +180,
   numeric_pad_rect_x_from + 30  -15 + numeric_pad_width*3,
   70 +220

}

};

String numeric_pad_desc[14] ={ "0", "", "1", "2", "3", "4", "5", "6", "7", "8", "9", "C", "0", "OK"};

int numeric_pad_values[14] ={ -1, -1, 1, 2, 3, 
4, 5, 6, 7, 8, 9, 10, 0, 20};


uint8_t which_pressed()
{
  // Serial.println( "*** which pressed ");
  // Serial.println( "*** touch_x " + String(touch_x));
  // Serial.println( "*** touch_y " + String(touch_y));

  for ( int i = 2; i < ArrayCount(numeric_pad) ; ++i ) {
      // Serial.println(i);
      if(numeric_pad[i][0] < touch_x && touch_x < numeric_pad[i][2] &&
        numeric_pad[i][1] < touch_y && touch_y < numeric_pad[i][3]){
          // Serial.println( "*** FOUND i " + String(i));

          return numeric_pad_values[i];
        }
  }
  
}


boolean isNumPadNumber(uint8_t value_selected_numpad) {

  if (value_selected_numpad >= 0 && value_selected_numpad <= 9) { 
    return true;    
  } else
  {
    return false;

  }
 
}


boolean isCancel(uint8_t value_selected_numpad) {

  if (value_selected_numpad ==10) { 
    return true;    
  } else
  {
    return false;

  }
 
}

boolean isOK(uint8_t value_selected_numpad) {

  if (value_selected_numpad ==20) { 
    return true;    
  } else
  {
    return false;

  }
 
}

void updateNumericPadValue(uint8_t value_selected_numpad) {
  // Serial.println("** entering updateNumericPadValue");
  // Serial.print("** numeric_pad_value : "); 
  // Serial.println(numeric_pad_value);

  // Serial.print("** value_selected_numpad : "); 
  // Serial.println(value_selected_numpad);

  if (numeric_pad_value == "0") {
    numeric_pad_value = String(value_selected_numpad);      
  } 
  else
  {        
    if (numeric_pad_value.length() < 4 ){  
      numeric_pad_value = numeric_pad_value + String(value_selected_numpad);    
    }  
  }

}


int show(void){
  // Serial.println("**********numpad show ");
  numeric_pad_value = "0";
  for ( int i = 0; i < ArrayCount(numeric_pad) ; ++i ) {

      // Serial.println(i);
      uint8_t color = 1;
      String value_to_show = "y";
      switch (i) 
      {
        case (0): // draw rectangle
          color = 5; // BLACK        
          break;
        case (1): // numpad number field
          color = 4; // white
          value_to_show = numeric_pad_value;
          break;
        default:
          color =1 ; // GREY
          value_to_show = numeric_pad_desc[i];
          break;

      };      

      // Serial.print ("Draw coordinates element i = " ); Serial.println(i);
      // Serial.print ("x from : ");Serial.println(numeric_pad[i][0]);
      // Serial.print ("y from : ");Serial.println(numeric_pad[i][1]);
      // Serial.print ("x to   : ");Serial.println(numeric_pad[i][2]);
      // Serial.print ("y to.  : ");Serial.println(numeric_pad[i][3]);

      draw_button(value_to_show, // uint8_t *desc,
                numeric_pad[i][0],   // int16_t x_from, 
                numeric_pad[i][1],   // int16_t y_from, 
                numeric_pad[i][2],   // int16_t x_to, 
                numeric_pad[i][3],   // int16_t y_to, 
                5,   // int16_t corner_radius, 
                2,   //int16_t text_dimension ,
                color    //int16_t button_color
              );

  };
    
  do_actions();

  return numeric_pad_value.toInt();
  // show_main_menu();

}

void do_actions(){

  boolean confirmation = false;
  while (confirmation == false){
    while (is_pressed() == false) {}
    convert_point();
    int selected = -1;
    uint8_t value_selected_numpad = which_pressed();

    // Serial.print(" --> value_selected_numpad : ");
    // Serial.println(value_selected_numpad);

    if (isNumPadNumber(value_selected_numpad)) { 
      updateNumericPadValue(value_selected_numpad); 
    } else if (isCancel(value_selected_numpad)){

      numeric_pad_value = "0";

    } else if (isOK(value_selected_numpad)){

      confirmation = true;

    };

    if (confirmation == false){
      draw_button(String(numeric_pad_value), // uint8_t *desc,
                  numeric_pad[1][0],   // int16_t x_from, 
                  numeric_pad[1][1],   // int16_t y_from, 
                  numeric_pad[1][2],   // int16_t x_to, 
                  numeric_pad[1][3],   // int16_t y_to, 
                  5,   // int16_t corner_radius, 
                  2,   //int16_t text_dimension ,
                  4    //int16_t button_color
                   );

      delay(100);
    }
  }; // end while confirmation

}

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
    { return true; }
    else
    {return false;}


}


void convert_point(void)
{

    touch_x = map(tp.y, TS_BOT, TS_TOP, 0, my_lcd.Get_Display_Width());

    touch_y = my_lcd.Get_Display_Height() - map(tp.x, TS_LEFT, TS_RT, 0, my_lcd.Get_Display_Height());

}



};


