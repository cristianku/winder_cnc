class Rpm : public Screen {

private:

int selected = 0;

int elements = 4;
//1 grey
//2 magenta
//3 yellow
//4 white
//5 black

int color_when_selected = 3;

int text_size = 2;

int default_color = 1;
int corner_radius = 5;

int buttons [4] [8]= { 

                        {5          ,   //x from                  0
                        180,            //y from                  1
                        480/4   -5   ,  //x to                    2
                        220,            //y to                    3
                        300},           // value when selected    8

                        {5 + 480/4 , 
                         180,   
                         480/4*2 -5   ,       
                         220,  
                         450}, 
                         
                        {5 + 480/4*2,      
                        180,   
                        480/4*3 -5   ,       
                        220,  
                        500}, // speed
                        
                        {5 + 480/4*3,      
                        180,   
                        480/4*4 -5   ,       
                        220,  
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
                  corner_radius,   // int16_t corner_radius, 
                  text_size,   //int16_t text_dimension ,
                  color_when_selected    //int16_t button_color                
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
                  default_color    //int16_t button_color
         ); }

 }     
    
public:

int get_selected_value (void ){
  return buttons[selected][4];

}


void draw_all(void){

    for ( int i = 0; i < elements ; ++i ) {
      if ( i == selected  ){draw(i, true);} else {draw(i, false);}     
    }
}

void do_actions(int x, int y){
   for ( int i = 0; i < elements ; ++i ) {
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

