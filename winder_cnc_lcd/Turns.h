class Turns : public Screen {

private:

int value = 0;

//1 grey
//2 magenta
//3 yellow
//4 white
//5 black

int start_x_pos = 190;

uint8_t button_height = 40;
uint8_t button_width = 100;


int buttons [1] [4]= { {  start_x_pos ,  // x from
                           40,     // y from
                          start_x_pos + button_width,    // x to      
                          40 +  button_height }    // y to
                     };

String desc [1] = { "0" };


public:

void setValue(int value_input){
  value = value_input;

}

int getValue(void){
  return value;

}

void draw_all(void){
    show_string("Turns to do:", 10,buttons[0][1] +15 ,2,WHITE, BLACK,1);

    for ( uint8_t i = 0; i < ArrayCount(buttons) ; ++i ) {

      draw_button(String(value), // uint8_t *desc,
                  buttons[i][0],   // int16_t x_from, 
                  buttons[i][1],   // int16_t y_from, 
                  buttons[i][2],   // int16_t x_to, 
                  buttons[i][3],   // int16_t y_to, 
                  5,   // int16_t corner_radius, 
                  2,   //int16_t text_dimension ,
                  1    //int16_t button_color
                );

    }

}
boolean do_actions(int x, int y){
   boolean found = false;
   for ( uint8_t i = 0; i < ArrayCount(buttons) ; ++i ) {
      // Serial.println(i);
      if(buttons[i][0] < x && x < buttons[i][2] &&
        buttons[i][1] < y && y < buttons[i][3]  
        ){

          // draw_all();
          found = true;
          break;
        }

  }

  return found;

}




};

