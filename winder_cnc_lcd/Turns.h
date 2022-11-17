class Turns : public Screen {

private:

int value = 0;

//1 grey
//2 magenta
//3 yellow
//4 white
//5 black

int color_when_selected = 3;

int text_size = 2;

int default_color = 1;
int corner_radius = 5;

int buttons [1] [4]= { {  200 ,  // x from
                           80,     // y from
                          300,    // x to      
                          120}    // y to
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
    show_string("Turns to do:", 10,95 ,2,WHITE, BLACK,1);

    for ( int i = 0; i < ArrayCount(buttons) ; ++i ) {

      draw_button(String(value), // uint8_t *desc,
                  buttons[i][0],   // int16_t x_from, 
                  buttons[i][1],   // int16_t y_from, 
                  buttons[i][2],   // int16_t x_to, 
                  buttons[i][3],   // int16_t y_to, 
                  corner_radius,   // int16_t corner_radius, 
                  text_size,   //int16_t text_dimension ,
                  default_color    //int16_t button_color
                );

    }

}
boolean do_actions(int x, int y){
   boolean found = false;
   for ( int i = 0; i < ArrayCount(buttons) ; ++i ) {
      Serial.println(i);
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

