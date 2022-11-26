
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


const uint8_t start_y_pos = 100;
const uint8_t start_x_pos = 190;

const uint8_t button_height = 40;
const uint8_t button_width = 50;
const uint8_t distance_between = 15;

int buttons [4][5] = {
                        {start_x_pos,        //x from 
                         start_y_pos ,             // y from
                         button_width * 1 +start_x_pos ,   // x to   
                         start_y_pos + button_height ,              // y to
                         1},               // value when selected
                        {button_width*1 +start_x_pos + distance_between, 
                         start_y_pos,   
                         button_width * 2 +start_x_pos + distance_between,   
                         start_y_pos + button_height,  
                         2}, //scattering 2
                        {button_width*2 +start_x_pos + distance_between *2, 
                         start_y_pos,  
                         button_width * 3 +start_x_pos + distance_between * 2,  
                         start_y_pos + button_height,  
                         3}, //scattering 3
                        {button_width*3 +start_x_pos + distance_between * 3, 
                        start_y_pos,  
                        button_width * 4 +start_x_pos + distance_between * 3,  
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

void show_scattering_help(int scatter_level){
  String desc = "";

  switch (scatter_level) { 
  case 0:
    desc ="Level 1 - highest scattering (min. 100 turns)";   
    break;
  case 1:
    desc ="Level 2 - medium scattering (min. 200 turns)";   
    break;
  case 2:
    desc ="Level 3 - lowest scattering  (min. 350 turns)";
    break;
  case 3:
    desc ="Level 4 - High + Low scatter (min. 900 turns)";
    break;

  };    
  if ( desc > "") {
    my_lcd.Set_Draw_color(background);

    my_lcd.Fill_Round_Rectangle(200, 150, 480,160, 2);

    show_string(desc, 200,150 ,1,WHITE, background,1);
  }

}

void draw_all(void){
    show_string("Scattering:", 10,buttons[0][1] +15  ,2,WHITE, BLACK,1);

    for ( int i = 0; i < ArrayCount(buttons) ; ++i ) {
      if ( i == selected  )
      {
        show_scattering_help(i);
        draw(i, true);
      } 
      else {draw(i, false);}     
    }
}

void do_actions(int x, int y){
   for ( int i = 0; i < ArrayCount(buttons) ; ++i ) {

      if(buttons[i][0] < x && x < buttons[i][2] &&
        buttons[i][1] < y && y < buttons[i][3]  
        ){
          if (selected == i){
            break;
          }else {
            selected = i;
            draw_all();
            break;
          }  
        }

  }
}

};
