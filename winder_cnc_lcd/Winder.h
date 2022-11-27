class Winder : public Screen {

public:

uint8_t selected = -1;
int total_turns_sent = 0;
int total_turns_sent_from_start = 0;

int total_turns_done_grbl = 0;


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


void draw(int i, boolean selected){
       if (i == 1){
         desc[i] = String(query_completed_turns()) + " completed";
       }

       if ( selected ){
              draw_button(desc[i], // uint8_t *desc,
                  buttons[i][0],   // int16_t x_from, 
                  buttons[i][1],   // int16_t y_from, 
                  buttons[i][2],   // int16_t x_to, 
                  buttons[i][3],   // int16_t y_to, 
                  5,   // int16_t corner_radius, 
                  2,   //int16_t text_dimension ,
                  2    //int16_t button_color        2=MAGENTA, 3=YELLOW         
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

void draw_completed(int completed){
       
      //  printout_completed();
        // draw_button(String(completed) + "sent= " + String(total_turns_sent) , // uint8_t *desc,
  draw_button(String(completed) + " completed", // uint8_t *desc,

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
        case 50:
          return 50;
          break;

      };

}

String send_query(){

  Serial.println("?");
  delay(50);
  return Serial.readString();

}

boolean query_idle(){

  String grbl_out = send_query();

  int idle = 0;
  idle = grbl_out.indexOf("Idle");
  // Serial.println("grbl_out" + grbl_out + "idle = " + String(idle)); 
  if ( idle == -1  ){
    return false;
    // show_string("non trovato" + grbl_out, 1 + 20,10,2,WHITE, BLACK,1);  
  } else
  {
  // show_string("trovato "+ grbl_out, 1 + 20,10,2,WHITE, BLACK,1);
    return true;
  }

}


int query_completed_turns (){

  int completed_turns = 0;

  String grbl_out = send_query();

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
    total_turns_done_grbl = completed_turns;
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

  boolean gcode_delayed = false;
  while ( (total_turns_sent_from_start - total_turns_done_grbl)  > 400){
    draw_completed ( query_completed_turns());
    gcode_delayed= true;
    show_info_message("DELAYING GCODE...");
    delay(200);
  }
  if (gcode_delayed){ show_info_message("RUNNING...");  }

  Serial.println("G1 X"+String(turns_x) + " Y"+ String(movement_y)+ " F"+ String(speed));
  // Serial.print(turns_x);
  // Serial.print(" Y");
  // Serial.print(movement_y);
  // Serial.print(" F" );
  // Serial.println(speed );
  // Serial.println("" );
  delay(10);

  String risposta = Serial.readString();
  // draw_completed ( query_completed_turns());
  // printout_completed();

  total_turns_sent += turns_x;
  total_turns_sent_from_start += turns_x;

}

void run_scattering_50turns (int speed){

  send_gcode(25, 0.9, speed);
  send_gcode(25, -0.9, speed);
}


void run_scattering_1 (int speed){

  send_gcode(30, 0.9, speed);
  send_gcode(30, -0.9, speed);

  send_gcode(15, 0.9 ,speed);
  send_gcode(15, -0.9,speed);

  send_gcode(5, 0.9,speed);
  send_gcode(5, -0.9,speed);

  draw_completed ( query_completed_turns());


}

void run_scattering_2 (int speed){
  send_gcode(50, 0.9,speed);
  send_gcode(50, -0.9,speed);

  send_gcode(30, 0.9,speed);
  send_gcode(30, -0.9,speed);

  send_gcode(20, 0.9,speed);
  send_gcode(20, -0.9,speed);

  draw_completed ( query_completed_turns());

}

void run_scattering_3 (int speed){
  send_gcode(100, 0.9, speed);
  send_gcode(100, -0.9, speed);

  send_gcode(50, 0.9, speed);
  send_gcode(50, -0.9, speed);

  send_gcode(25, 0.9, speed);
  send_gcode(25, -0.9, speed);

  draw_completed ( query_completed_turns());


}

void run_scattering_4 (int speed){
    // # scatter level 3 - 350 turns

    run_scattering_3(speed);

    // # scatter level 1 - 100 turns repeated 2 times
    // # first repeat
    run_scattering_1(speed);

    // # second repeat
    run_scattering_1(speed);

    // #scatter level 3 - 350 turns

    run_scattering_3(speed);

    draw_completed ( query_completed_turns());

}


void  run(int turns, int scattering, int speed){
  total_turns_sent = 0;

  int turns_per_iteration = get_Turns_per_scatter_level(scattering);

  int iterations = int(turns / turns_per_iteration);
  show_info_message("RUNNING...");
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

  // multiple of 100 remaining using Scattering level 1
  int remaining = turns - total_turns_sent;
  if ( remaining >= 50 ){
    // my_lcd.Fill_Screen(background);
    show_info_message("RUNNING PATCH 1");

    iterations = int(remaining / get_Turns_per_scatter_level(1));

    // do scattering_1 for the remaining
    for ( int i = 0; i < iterations ; ++i ) {
      run_scattering_1(speed);
          
    }
  } 

  // multiple of 50 remaining using Scattering for 50 turns
  remaining = turns - total_turns_sent;
  if ( remaining >= 50 ){
    // my_lcd.Fill_Screen(background);
    show_info_message("RUNNING PATCH 2");

    iterations = int(remaining / get_Turns_per_scatter_level(50));

    // do scattering_1 for the remaining
    for ( int i = 0; i < iterations ; ++i ) {
      run_scattering_50turns(speed);
          
    }
  }

  // my_lcd.Fill_Screen(background);
  show_info_message("IDLE");

  while ( query_idle() == false){
    // printout_completed();

    draw_completed ( query_completed_turns());
    delay(500);
  }
  // printout_completed();

  // draw_completed ( query_completed_turns());
  while (Serial.readString() > "" ){};
  draw_completed ( query_completed_turns());
  show_info_message("COMPLETED...");

;
}


};
