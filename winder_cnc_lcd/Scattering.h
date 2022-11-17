
class Scattering : public Screen {

//1 grey
//2 magenta
//3 yellow
//4 white
//5 black

        
private:

int selected = 0;

// int color_when_selected = 3;

int text_size = 2;

// int default_color = 1;
int corner_radius = 5;


int buttons [4][9] = {
                        {480/8 +90,        //x from 
                         130 ,             // y from
                         480/8 * 2 +90 ,   // x to   
                         175,              // y to
                         1},               // value when selected
                        {480/8*2 +90 + 5, 
                         130,   
                         480/8 * 3 +90 + 5,   
                         175,  
                         2}, //scattering 2
                        {480/8*3 +90 + 10, 
                         130,  
                         480/8 * 4 +90 + 10,  
                         175,  
                         3}, //scattering 3
                        {480/8*4 +90 + 15, 
                        130,  
                        480/8 * 5 +90 + 15,  
                        175,  
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
                  corner_radius,   // int16_t corner_radius, 
                  text_size,   //int16_t text_dimension ,
                  3   //int16_t button_color
                );
        }     else
        {
         draw_button(desc[i], // uint8_t *desc,
                  buttons[i][0],   // int16_t x_from, 
                  buttons[i][1],   // int16_t y_from, 
                  buttons[i][2],   // int16_t x_to, 
                  buttons[i][3],   // int16_t y_to, 
                  corner_radius,   // int16_t corner_radius, 
                  text_size,   //int16_t text_dimension ,
                  1    //int16_t button_color
         ); }

 }     
    
public:

int get_selected_value (void ){
  return buttons[selected][4];

}


void draw_all(void){
    show_string("Scattering:", 10,145 ,2,WHITE, BLACK,1);

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
