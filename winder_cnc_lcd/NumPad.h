
class NumPad: public Screen {

public:
int touch_x = 0;
int touch_y = 0;

 int numeric_pad_elements = 14;
 int numeric_pad_elements_sel = 1;
 int numeric_pad_width = 7;
 int numeric_pad_width_between = 15;
 int numeric_pad_rect_y_from = 10;
 int numeric_pad_rect_y_numpad_from = numeric_pad_rect_y_from + 60;

 int numeric_pad_rect_x_from = 120;

 int numeric_pad_rect_y_to = 380;
 int numeric_pad_rect_x_to = 380;
String numeric_pad_value = "0";


int numeric_pad [14][9] {
  // container
{
   numeric_pad_rect_x_from ,
   numeric_pad_rect_y_from,
   numeric_pad_rect_x_to,
   numeric_pad_rect_y_to,
   5,             //4 - corner radius
   2,             //5 - text size
   5,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW, 4= WHITE, 5=BLACK)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   1              //8 - value when selected
},
// number rectanble
{
   numeric_pad_rect_x_from + 15,
   numeric_pad_rect_y_from + 10,
   numeric_pad_rect_x_to - 20,
   numeric_pad_rect_y_from + 70,
   2,             //4 - corner radius
   2,             //5 - text size
   4,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW, 4= WHITE, 5=BLACK)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   1              //8 - value when selected
},

  // first line
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*0, //0 - x from
   numeric_pad_rect_y_numpad_from + 30,            //1 - y from
   numeric_pad_rect_x_from + 30  - numeric_pad_width_between  + 480/numeric_pad_width*1, //2 - x to 
   numeric_pad_rect_y_numpad_from +70,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   1              //8 - value when selected
},
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*1, //0 - x from
   numeric_pad_rect_y_numpad_from +30,            //1 - y from
   numeric_pad_rect_x_from + 30  -numeric_pad_width_between + 480/numeric_pad_width*2, //2 - x to 
   numeric_pad_rect_y_numpad_from +70,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   2              //8 - value when selected
},
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*2, //0 - x from
   numeric_pad_rect_y_numpad_from +30,            //1 - y from
   numeric_pad_rect_x_from + 30  -numeric_pad_width_between + 480/numeric_pad_width*3, //2 - x to 
   numeric_pad_rect_y_numpad_from +70,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   3              //8 - value when selected
},
// second line
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*0, //0 - x from
   numeric_pad_rect_y_numpad_from +80,            //1 - y from
   numeric_pad_rect_x_from + 30  - numeric_pad_width_between  + 480/numeric_pad_width*1, //2 - x to 
   numeric_pad_rect_y_numpad_from +120,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   4              //8 - value when selected
},
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*1, //0 - x from
   numeric_pad_rect_y_numpad_from +80,            //1 - y from
   numeric_pad_rect_x_from + 30  -numeric_pad_width_between + 480/numeric_pad_width*2, //2 - x to 
   numeric_pad_rect_y_numpad_from +120,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   5              //8 - value when selected
},
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*2, //0 - x from
   numeric_pad_rect_y_numpad_from +80,            //1 - y from
   numeric_pad_rect_x_from + 30  -numeric_pad_width_between + 480/numeric_pad_width*3, //2 - x to 
   numeric_pad_rect_y_numpad_from +120,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   6              //8 - value when selected
},
// third line
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*0, //0 - x from
   numeric_pad_rect_y_numpad_from +130,            //1 - y from
   numeric_pad_rect_x_from + 30  - numeric_pad_width_between  + 480/numeric_pad_width*1, //2 - x to 
   numeric_pad_rect_y_numpad_from +170,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   7              //8 - value when selected
},
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*1, //0 - x from
   numeric_pad_rect_y_numpad_from +130,            //1 - y from
   numeric_pad_rect_x_from + 30  -numeric_pad_width_between + 480/numeric_pad_width*2, //2 - x to 
   numeric_pad_rect_y_numpad_from +170,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   8              //8 - value when selected
},
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*2, //0 - x from
   numeric_pad_rect_y_numpad_from +130,            //1 - y from
   numeric_pad_rect_x_from + 30  -numeric_pad_width_between + 480/numeric_pad_width*3, //2 - x to 
   numeric_pad_rect_y_numpad_from +170,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   9              //8 - value when selected
},
// fourth line
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*0, //0 - x from
   numeric_pad_rect_y_numpad_from +180,            //1 - y from
   numeric_pad_rect_x_from + 30  - numeric_pad_width_between + 480/numeric_pad_width*1, //2 - x to 
   numeric_pad_rect_y_numpad_from +220,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   0              //8 - value when selected
},
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*1, //0 - x from
   numeric_pad_rect_y_numpad_from +180,            //1 - y from
   numeric_pad_rect_x_from + 30  -numeric_pad_width_between + 480/numeric_pad_width*2, //2 - x to 
   numeric_pad_rect_y_numpad_from +220,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   10              //8 - value when selected
},
{
   numeric_pad_rect_x_from + 30 + 480/numeric_pad_width*2, //0 - x from
   numeric_pad_rect_y_numpad_from +180,            //1 - y from
   numeric_pad_rect_x_from + 30  -numeric_pad_width_between + 480/numeric_pad_width*3, //2 - x to 
   numeric_pad_rect_y_numpad_from +220,            //3 - y to
   5,             //4 - corner radius
   2,             //5 - text size
   1,             //6 - default color  ( 1=GREY, 2= MAGENTA,3 = YELLOW)
   3,             //7 - color when pressed ( 1=GREY, 2= MAGENTA,3 = YELLOW)  
   20              //8 - value when selected
}


};

String numeric_pad_desc[14] ={ "0", "", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "C", "OK"};



String show(void){
  Serial.println("numpad show ");
  for ( int i = 0; i < numeric_pad_elements ; ++i ) {
      Serial.println(i);
      if (i ==1 ) {
        char * value_selected_numpad_uuint8 = new char [numeric_pad_value.length() + 1];
        strcpy (value_selected_numpad_uuint8, numeric_pad_value.c_str());
        draw_button(value_selected_numpad_uuint8, // uint8_t *desc,
                  numeric_pad[i][0],   // int16_t x_from, 
                  numeric_pad[i][1],   // int16_t y_from, 
                  numeric_pad[i][2],   // int16_t x_to, 
                  numeric_pad[i][3],   // int16_t y_to, 
                  numeric_pad[i][4],   // int16_t corner_radius, 
                  numeric_pad[i][5],   //int16_t text_dimension ,
                  numeric_pad[i][6]    //int16_t button_color
                );
        
        }
         else {
          draw_button(numeric_pad_desc[i], // uint8_t *desc,
                    numeric_pad[i][0],   // int16_t x_from, 
                    numeric_pad[i][1],   // int16_t y_from, 
                    numeric_pad[i][2],   // int16_t x_to, 
                    numeric_pad[i][3],   // int16_t y_to, 
                    numeric_pad[i][4],   // int16_t corner_radius, 
                    numeric_pad[i][5],   //int16_t text_dimension ,
                    numeric_pad[i][6]    //int16_t button_color
                  );
       }       
    }


    boolean confirmation = false;
    while (confirmation == false){
      while (is_pressed() == false) {}
      convert_point();
      int selected = -1;
      for ( int i = 0; i < numeric_pad_elements ; ++i ) {
          // Serial.println(i);
          if(numeric_pad[i][0] < touch_x && touch_x < numeric_pad[i][2] &&
            numeric_pad[i][1] < touch_y && touch_y < numeric_pad[i][3]  
            ){
              selected  = i;
            }
      }

      int value_selected_numpad = numeric_pad[selected][8];
      // Serial.println(value_selected_numpad);
      if (value_selected_numpad >= 0 && value_selected_numpad <= 9) { 

        String value_selected_numpad_str = String(value_selected_numpad);
        if (numeric_pad_value == "0") {
          numeric_pad_value = value_selected_numpad_str;      
        } else{        
        numeric_pad_value = numeric_pad_value + value_selected_numpad_str;      
        };
      } else if (value_selected_numpad ==10 ){
        // Serial.println("case 10");

        // numeric_pad_value = numeric_pad_value.substring(0,numeric_pad_value.length() - 1 ) ;  
        // Serial.println(numeric_pad_value);
        // Serial.println("case 20");
        numeric_pad_value = "0";

      } else if (value_selected_numpad == 20 ){

        confirmation = true;
      };

       if (confirmation == false){
        char * value_selected_numpad_uuint8 = new char [numeric_pad_value.length() + 1];
        strcpy (value_selected_numpad_uuint8, numeric_pad_value.c_str());

        draw_button(value_selected_numpad_uuint8, // uint8_t *desc,
                    numeric_pad[1][0],   // int16_t x_from, 
                    numeric_pad[1][1],   // int16_t y_from, 
                    numeric_pad[1][2],   // int16_t x_to, 
                    numeric_pad[1][3],   // int16_t y_to, 
                    numeric_pad[1][4],   // int16_t corner_radius, 
                    numeric_pad[1][5],   //int16_t text_dimension ,
                    numeric_pad[1][6]    //int16_t button_color
                                  );

        delay(100);
       }

    }
    return numeric_pad_value;
    // show_main_menu();

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


