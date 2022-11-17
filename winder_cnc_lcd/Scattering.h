
class Scattering : public Screen {

//1 grey
//2 magenta
//3 yellow
//4 white
//5 black

        
private:

int selected = 0;

// int color_when_selected = 3;
// int default_color = 1;


int start_y_pos = 100;
int button_height = 40;

int buttons [4][5] = {
                        {480/8 +90,        //x from 
                         start_y_pos ,             // y from
                         480/8 * 2 +90 ,   // x to   
                         start_y_pos + button_height ,              // y to
                         1},               // value when selected
                        {480/8*2 +90 + 5, 
                         start_y_pos,   
                         480/8 * 3 +90 + 5,   
                         start_y_pos + button_height,  
                         2}, //scattering 2
                        {480/8*3 +90 + 10, 
                         start_y_pos,  
                         480/8 * 4 +90 + 10,  
                         start_y_pos + button_height,  
                         3}, //scattering 3
                        {480/8*4 +90 + 15, 
                        start_y_pos,  
                        480/8 * 5 +90 + 15,  
                        start_y_pos + button_height,  
                        4}, //scattering 4
                      };

String desc[4] = { 
                        "1",
                        "2",
                        "3",
                        "4"};


void draw(int i, boolean selected){
       
       if ( selected ){
              draw_button(desc[i], // uint8_t *desc,
                  buttons[i][0],   // int16_t x_from, 
                  buttons[i][1],   // int16_t y_from, 
                  buttons[i][2],   // int16_t x_to, 
                  buttons[i][3],   // int16_t y_to, 
                  5,   // int16_t corner_radius, 
                  2,   //int16_t text_dimension ,
                  3   //int16_t button_color
                );
        }     else
        {
         draw_button(desc[i], // uint8_t *desc,
                  buttons[i][0],   // int16_t x_from, 
                  buttons[i][1],   // int16_t y_from, 
                  buttons[i][2],   // int16_t x_to, 
                  buttons[i][3],   // int16_t y_to, 
                  5,   // int16_t corner_radius, 
                  2,   //int16_t text_dimension ,
                  1    //int16_t button_color
         ); }

 }     
    
public:

int get_selected_value (void ){
  return buttons[selected][4];

}


void draw_all(void){
    show_string("Scattering:", 10,buttons[0][1] +15  ,2,WHITE, BLACK,1);

    for ( int i = 0; i < ArrayCount(buttons) ; ++i ) {
      if ( i == selected  ){draw(i, true);} else {draw(i, false);}     
    }
}

void do_actions(int x, int y){
   for ( int i = 0; i < ArrayCount(buttons) ; ++i ) {
      Serial.println(i);
      if(buttons[i][0] < x && x < buttons[i][2] &&
        buttons[i][1] < y && y < buttons[i][3]  
        ){
          selected = i;
          draw_all();
          break;
        }

  }
}

};
