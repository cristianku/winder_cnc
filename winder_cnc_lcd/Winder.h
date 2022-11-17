class Winder : public Screen {

private:

int selected = -1;
int total_turns_sent = 0;
int elements = 2;
//1 grey
//2 magenta
//3 yellow
//4 white
//5 black

int color_when_selected = 3;

int text_size = 2;

int default_color = 1;
int corner_radius = 5;

int buttons [2] [4]= { {5,                250,  160,                 300},
                      {170,               250,  460,                 300}  
};

String desc [2] = { "Run Winder" , "0"};

void draw(void){

    for ( int i = 0; i < elements ; ++i ) {

      // my_lcd.Fill_Round_Rectangle(buttons[i][0], buttons[i][1], buttons[i][2],buttons[i][3], buttons[i][4]);
    
      // show_string(buttons_desc[i], buttons[i][0] + 20,get_y_text_pos (buttons[i][3] , buttons[i][1],buttons[i][5]) ,buttons[i][5],BLACK, BLACK,1);
      if ( i == selected  ){

              draw_button(desc[i], // uint8_t *desc,
                  buttons[i][0],   // int16_t x_from, 
                  buttons[i][1],   // int16_t y_from, 
                  buttons[i][2],   // int16_t x_to, 
                  buttons[i][3],   // int16_t y_to, 
                  corner_radius,   // int16_t corner_radius, 
                  text_size,   //int16_t text_dimension ,
                  color_when_selected   //int16_t button_color
                );
      }else {
      draw_button(desc[i], // uint8_t *desc,
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

}

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

void draw_completed(int completed){
       
        draw_button(String(completed), // uint8_t *desc,
            buttons[1][0],   // int16_t x_from, 
            buttons[1][1],   // int16_t y_from, 
            buttons[1][2],   // int16_t x_to, 
            buttons[1][3],   // int16_t y_to, 
            corner_radius,   // int16_t corner_radius, 
            text_size,   //int16_t text_dimension ,
            default_color    //int16_t button_color                
            );
}
void draw_all(void){

    for ( int i = 0; i < elements ; ++i ) {
      if ( i == selected  ){draw(i, true);} else {draw(i, false);}     
    }
}

boolean do_actions(int x, int y){
   boolean found = false;
   for ( int i = 0; i < elements ; ++i ) {
      Serial.println(i);
      if(buttons[i][0] < x && x < buttons[i][2] &&
        buttons[i][1] < y && y < buttons[i][3]  
        ){

          selected = i;
          draw_all();
          found = true;
          break;
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
  delay(10);
  int completed_turns = 0;

  String grbl_out = Serial.readString();
  int mpos_from = grbl_out.indexOf("MPos")  + 5;
  int mpos_to = grbl_out.indexOf(".",mpos_from);

  // int idle = 0;
  // idle = grbl_out.indexOf("Idle");
  

  // char * grbl_out_uuint8 = new char [grbl_out.length() + 1];
  // strcpy (grbl_out_uuint8, grbl_out.c_str());
  
  // if ( idle > 0 ){
  //   show_string("idle trovato !! ", 1 + 20,10,2,WHITE, BLACK,1);  
  // } else
  // {
  // show_string(grbl_out_uuint8, 1 + 20,10,2,WHITE, BLACK,1);
  // }


  if (grbl_out.substring(mpos_from, mpos_to) != "" ){
    completed_turns = grbl_out.substring(mpos_from, mpos_to).toInt()   ;
  }  


  return completed_turns;

  //   char * grbl_out_uuint8 = new char [grbl_out_turns.length() + 1];
  //   strcpy (grbl_out_uuint8, grbl_out_turns.c_str());



  //   draw_button(grbl_out_uuint8, // uint8_t *desc,
  //               buttons[21][0],   // int16_t x_from, 
  //               buttons[21][1],   // int16_t y_from, 
  //               buttons[21][2],   // int16_t x_to, 
  //               buttons[21][3],   // int16_t y_to, 
  //               buttons[21][4],   // int16_t corner_radius, 
  //               buttons[21][5],   //int16_t text_dimension ,
  //               buttons[21][6]    //int16_t button_color
  //             );
  // }
  // delay(100);



}



void send_gcode( float turns_x, float movement_y , int speed){
  Serial.print("");
  Serial.print(turns_x);
  Serial.print(" Y");
  Serial.print(movement_y);
  Serial.print(" F" );
  Serial.print(speed );
  Serial.println("" );
  delay(100);

  draw_completed ( query_completed_turns());

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


int  run(int turns, int scattering, int speed){
  total_turns_sent = 0;

  Serial.print ("****** RUN !!!!!");
  int turns_per_iteration = get_Turns_per_scatter_level(scattering);

  int iterations = int(turns / turns_per_iteration);
  Serial.print("turns : "); Serial.println(turns);
  Serial.print("turns_per_iteration : "); Serial.println(turns_per_iteration);

  Serial.print("iterations : "); Serial.println(iterations);
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

  return total_turns_sent;
}


};

// void run_winder(int16_t turns, int16_t speed, int16_t scatter_level ){

//   Serial.print(");
//   Serial.print(turns);
//   Serial.print(" F" );
//   Serial.print(speed );
//   Serial.println("" );

//   // String speed_str = String(speed);
  
//   // char * grbl_out_uuint8 = new char [speed_str.length() + 1];
//   // strcpy (grbl_out_uuint8, speed_str.c_str());

//   // draw_button(grbl_out_uuint8, // uint8_t *desc,
//   //             buttons[21][0],   // int16_t x_from, 
//   //             buttons[21][1],   // int16_t y_from, 
//   //             buttons[21][2],   // int16_t x_to, 
//   //             buttons[21][3],   // int16_t y_to, 
//   //             buttons[21][4],   // int16_t corner_radius, 
//   //             buttons[21][5],   //int16_t text_dimension ,
//   //             buttons[21][6]    //int16_t button_color
//   //           );

//   // delay(1000);
//   // wait to grbl to start
//   int running = -1;
//   while ( running == -1){
//     // my_lcd.Fill_Screen(BLACK);  
//       draw_button("waiting for start", // uint8_t *desc,
//                   buttons[21][0],   // int16_t x_from, 
//                   buttons[21][1],   // int16_t y_from, 
//                   buttons[21][2],   // int16_t x_to, 
//                   buttons[21][3],   // int16_t y_to, 
//                   buttons[21][4],   // int16_t corner_radius, 
//                   buttons[21][5],   //int16_t text_dimension ,
//                   buttons[21][6]    //int16_t button_color
//                 );
//     Serial.println("?");
//     String grbl_out = Serial.readString();
//     running = grbl_out.indexOf("Run");
//     // char * grbl_out_uuint8 = new char [grbl_out.length() + 1];
//     // strcpy (grbl_out_uuint8, grbl_out.c_str());

//     delay (1000);
//   }
//   //

//   draw_button("STARTED", // uint8_t *desc,
//               buttons[21][0],   // int16_t x_from, 
//               buttons[21][1],   // int16_t y_from, 
//               buttons[21][2],   // int16_t x_to, 
//               buttons[21][3],   // int16_t y_to, 
//               buttons[21][4],   // int16_t corner_radius, 
//               buttons[21][5],   //int16_t text_dimension ,
//               buttons[21][6]    //int16_t button_color
//             );
//   delay (1000);

//   int idle = -1;
//   Serial.println("?");
//   String grbl_out = Serial.readString();
//   delay(100);

//   while (idle == -1){
//     Serial.println("?");

//     String grbl_out = Serial.readString();
//     // int mpos_index = grbl_out.indexOf("MPos") ;
//     // int mpos_from = mpos_index + 5;
//     // int mpos_to = grbl_out.indexOf(".",mpos_from);

//     // idle = grbl_out.indexOf("Idle");

//     // if (mpos_index > 1 && mpos_to > mpos_from ){
//     //   String grbl_out_turns = grbl_out.substring(mpos_from, mpos_to) + " completed turns";

//     //   char * grbl_out_uuint8 = new char [grbl_out_turns.length() + 1];
//     //   strcpy (grbl_out_uuint8, grbl_out_turns.c_str());

//     //   draw_button(grbl_out_uuint8, // uint8_t *desc,
//     //               buttons[21][0],   // int16_t x_from, 
//     //               buttons[21][1],   // int16_t y_from, 
//     //               buttons[21][2],   // int16_t x_to, 
//     //               buttons[21][3],   // int16_t y_to, 
//     //               buttons[21][4],   // int16_t corner_radius, 
//     //               buttons[21][5],   //int16_t text_dimension ,
//     //               buttons[21][6]    //int16_t button_color
//     //             );
//     //     
//     my_lcd.Fill_Screen(background);
//     char * grbl_out_uuint8 = new char [grbl_out.length() + 1];
//     strcpy (grbl_out_uuint8, grbl_out.c_str());
//     show_string(grbl_out_uuint8, 1 + 20,2 ,2,BLACK, BLACK,1);
    
    
//   delay(300);

//   }


//   draw_button("FINISH", // uint8_t *desc,
//               buttons[21][0],   // int16_t x_from, 
//               buttons[21][1],   // int16_t y_from, 
//               buttons[21][2],   // int16_t x_to, 
//               buttons[21][3],   // int16_t y_to, 
//               buttons[21][4],   // int16_t corner_radius, 
//               buttons[21][5],   //int16_t text_dimension ,
//               buttons[21][6]    //int16_t button_color
//                   );



// }
