class Rpm : public Screen {

private:

int selected = 0;

//1 grey
//2 magenta
//3 yellow
//4 white
//5 black

int start_y_pos = 165;
int button_height = 40;


int buttons [4] [5]= { 

                        {5          ,   //x from                  0
                        start_y_pos,            //y from                  1
                        480/4   -5   ,  //x to                    2
                        start_y_pos + button_height,            //y to                    3
                        300},           // value when selected    8

                        {5 + 480/4 , 
                         start_y_pos,   
                         480/4*2 -5   ,       
                         start_y_pos + button_height,  
                         450}, 
                         
                        {5 + 480/4*2,      
                        start_y_pos,   
                        480/4*3 -5   ,       
                        start_y_pos + button_height,  
                        500}, // speed
                        
                        {5 + 480/4*3,      
                        start_y_pos,   
                        480/4*4 -5   ,       
                        start_y_pos + button_height,  
                        600}, // speed


                      } ;

String desc [4] = { 

                        "300 rpm",
                        "450 rpm",
                        "500 rpm",
                        "600 rpm",

};



void draw(int i, boolean selected){
       
       if ( selected ){
              draw_button(desc[i], // uint8_t *desc,
                  buttons[i][0],   // int16_t x_from, 
                  buttons[i][1],   // int16_t y_from, 
                  buttons[i][2],   // int16_t x_to, 
                  buttons[i][3],   // int16_t y_to, 
                  5,   // int16_t corner_radius, 
                  2,   //int16_t text_dimension ,
                  3    //int16_t button_color                
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

    for ( int i = 0; i < ArrayCount(buttons)  ; ++i ) {
      if ( i == selected  ){draw(i, true);} else {draw(i, false);}     
    }
}

void do_actions(int x, int y){
   for ( int i = 0; i < ArrayCount(buttons)  ; ++i ) {
      // Serial.println(i);
      if(buttons[i][0] < x && x < buttons[i][2] &&
        buttons[i][1] < y && y < buttons[i][3]  
        ){
          if (selected == i){
            break;
          }else {
            draw(selected, false);
            selected = i;
            draw(selected, true);
            break;
          }
        }

  }
}


};

