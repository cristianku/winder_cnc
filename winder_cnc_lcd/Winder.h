class Winder : public Screen {

private:

uint8_t selected = -1;
int total_turns_sent = 0;
//1 grey
//2 magenta
//3 yellow
//4 white
//5 black

int start_y_pos = 230;
int button_height = 50;

int buttons [2] [4]= { {5,
                        start_y_pos,
                        160,
                        start_y_pos + button_height},
                       {170,
                        start_y_pos,
                        460,
                        start_y_pos+button_height}
};

String desc [2] = { "Run Winder" , "0 completed"};

// void draw(void){

//     for ( uint8_t i = 0; i < ArrayCount(buttons) ; ++i ) {

//       // my_lcd.Fill_Round_Rectangle(buttons[i][0], buttons[i][1], buttons[i][2],buttons[i][3], buttons[i][4]);

//       // show_string(buttons_desc[i], buttons[i][0] + 20,get_y_text_pos (buttons[i][3] , buttons[i][1],buttons[i][5]) ,buttons[i][5],BLACK, BLACK,1);
//       String desc;
//       if ( i ==1 ){
//         desc = String(completed_turns) +" completed";

//       } else
//       {
//         desc = desc[i];

//       }

//       desc ="123";


//       if ( i == selected  ){

//               draw_button(desc, // uint8_t *desc,
//                   buttons[i][0],   // int16_t x_from,
//                   buttons[i][1],   // int16_t y_from,
//                   buttons[i][2],   // int16_t x_to,
//                   buttons[i][3],   // int16_t y_to,
//                   5,   // int16_t corner_radius,
//                   2,   //int16_t text_dimension ,
//                   3   //int16_t button_color
//                 );
//       }else {
//       draw_button(desc, // uint8_t *desc,
//                   buttons[i][0],   // int16_t x_from,
//                   buttons[i][1],   // int16_t y_from,
//                   buttons[i][2],   // int16_t x_to,
//                   buttons[i][3],   // int16_t y_to,
//                   5,   // int16_t corner_radius,
//                   2,   //int16_t text_dimension ,
//                   1    //int16_t button_color
//                 );
//       }
//     }

// }

void draw(int i, boolean selected){

      String desc2;
      if ( i ==1 ){
        desc2 = String(completed_turns) +" completed";

      } else
      {
        desc2 = desc[i];

      }
       if ( selected ){
              draw_button(desc2, // uint8_t *desc,
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
         draw_button(desc2, // uint8_t *desc,
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
int completed_turns = 0;

String grbl_out;


void draw_completed(){

        draw_button(String(completed_turns) + " completed", // uint8_t *desc,
            buttons[1][0],   // int16_t x_from,
            buttons[1][1],   // int16_t y_from,
            buttons[1][2],   // int16_t x_to,
            buttons[1][3],   // int16_t y_to,
            5,   // int16_t corner_radius,
            2,   //int16_t text_dimension ,
            1    //int16_t button_color
            );
}
void draw_all(void){

    for ( int i = 0; i < ArrayCount(buttons) ; ++i ) {
      if ( i == selected  ){draw(i, true);} else {draw(i, false);}
    }
}

boolean do_actions(int x, int y){
   boolean found = false;

  if(buttons[0][0] < x && x < buttons[0][2] &&
     buttons[0][1] < y && y < buttons[0][3]
    ){
      if ( selected == 0){
      } else
      {
        selected = 0;
        draw_all();
        found = true;
      }
    }

  return found;

}

int get_Turns_per_scatter_level(int scatter_level){
        switch (scatter_level) {
        case 1:
          return 100;
          break;
        case 2:
          return 200;
          break;
        case 3:
          return 350;
          break;
        case 4:
          return 900;
          break;
      };

}

int query_completed_turns (){
  Serial.println("?");
  // delay(10);

  grbl_out = Serial.readString();
  int mpos_from = grbl_out.indexOf("MPos")  + 5;
  int mpos_to = grbl_out.indexOf(".",mpos_from);


  if (grbl_out.substring(mpos_from, mpos_to) != "" ){
    completed_turns = grbl_out.substring(mpos_from, mpos_to).toInt()   ;
  }

}

boolean isIdle(){

  // char * grbl_out_uuint8 = new char [grbl_out.length() + 1];
  // strcpy (grbl_out_uuint8, grbl_out.c_str());

   if ( grbl_out.indexOf("Idle") > 0 ){
     return true;
  //   show_string("idle trovato !! ", 1 + 20,10,2,WHITE, BLACK,1);
  } else
  {
  // show_string(grbl_out_uuint8, 1 + 20,10,2,WHITE, BLACK,1);
    return false;
  };


}


void send_gcode( float turns_x, float movement_y , int speed){
  Serial.print("G1 X");
  Serial.print(turns_x);
  Serial.print(" Y");
  Serial.print(movement_y);
  Serial.print(" F" );
  Serial.print(speed );
  Serial.println("" );
  delay(100);

  String grbl_out = Serial.readString();
  query_completed_turns();
  draw_completed ();

  total_turns_sent += turns_x;

}

void run_scattering_1 (int speed){

  send_gcode(30, 0.9, speed);
  send_gcode(30, -0.9, speed);

  send_gcode(15, 0.9 ,speed);
  send_gcode(15, -0.9,speed);

  send_gcode(5, 0.9,speed);
  send_gcode(5, -0.9,speed);

}

void run_scattering_2 (int speed){
  send_gcode(50, 0.9,speed);
  send_gcode(50, -0.9,speed);

  send_gcode(30, 0.9,speed);
  send_gcode(30, -0.9,speed);

  send_gcode(20, 0.9,speed);
  send_gcode(20, -0.9,speed);
}

void run_scattering_3 (int speed){
  send_gcode(100, 0.9, speed);
  send_gcode(100, -0.9, speed);

  send_gcode(50, 0.9, speed);
  send_gcode(50, -0.9, speed);

  send_gcode(25, 0.9, speed);
  send_gcode(25, -0.9, speed);


}

void run_scattering_4 (int speed){
    // # scatter level 3 - 350 turns

    send_gcode(100, 0.9, speed);
    send_gcode(100, -0.9, speed);

    send_gcode(50, 0.9, speed);
    send_gcode(50, -0.9, speed);

    send_gcode(25,0.9, speed);
    send_gcode(25,-0.9, speed);

    // # scatter level 1 - 100 turns repeated 2 times
    // # first repeat
    send_gcode(30, 0.9, speed);
    send_gcode(30, -0.9, speed);

    send_gcode(15, 0.9, speed);
    send_gcode(15, -0.9, speed);

    send_gcode(5, 0.9, speed);
    send_gcode(5, -0.9, speed);

    // # second repeat
    send_gcode(30, 0.9, speed);
    send_gcode(30, -0.9, speed);

    send_gcode(15, 0.9, speed);
    send_gcode(15, -0.9, speed);

    send_gcode(5, 0.9, speed);
    send_gcode(5, -0.9, speed);

    // #scatter level 3 - 350 turns

    send_gcode(100, 0.9, speed);
    send_gcode(100, -0.9, speed);

    send_gcode(50, 0.9, speed);
    send_gcode(50, -0.9, speed);

    send_gcode(25, 0.9 , speed);
    send_gcode(25, -0.9, speed);



}


void  run(int turns, int scattering, int speed){
  total_turns_sent = 0;

  // Serial.print ("****** RUN !!!!!");
  int turns_per_iteration = get_Turns_per_scatter_level(scattering);

  int iterations = int(turns / turns_per_iteration);
  // Serial.print("turns : "); Serial.println(turns);
  // Serial.print("turns_per_iteration : "); Serial.println(turns_per_iteration);

  // Serial.print("iterations : "); Serial.println(iterations);
  for ( int i = 0; i < iterations ; ++i ) {

    switch (scattering){
      case 1:
          run_scattering_1(speed);
          break;
      case 2:
          run_scattering_2(speed);
          break;
      case 3:
          run_scattering_3(speed);
          break;
      case 4:
          run_scattering_4(speed);
          break;
    }

  }

  selected = -1;
  draw(0, false);
  query_completed_turns();
  draw_completed ( );

  while (isIdle() == false ) {
    // my_lcd.Fill_Screen(background);

    // show_string(grbl_out, 10,10 ,2,WHITE, BLACK,1);

    query_completed_turns();
    delay(50);
  }
  delay(400);

}


};
