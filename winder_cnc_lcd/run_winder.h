void run_winder(int16_t turns, int16_t speed, int16_t scatter_level ){

  Serial.print("G1 X");
  Serial.print(turns);
  Serial.print(" F" );
  Serial.print(speed );
  Serial.println("" );

  // String speed_str = String(speed);
  
  // char * grbl_out_uuint8 = new char [speed_str.length() + 1];
  // strcpy (grbl_out_uuint8, speed_str.c_str());

  // draw_button(grbl_out_uuint8, // uint8_t *desc,
  //             buttons[21][0],   // int16_t x_from, 
  //             buttons[21][1],   // int16_t y_from, 
  //             buttons[21][2],   // int16_t x_to, 
  //             buttons[21][3],   // int16_t y_to, 
  //             buttons[21][4],   // int16_t corner_radius, 
  //             buttons[21][5],   //int16_t text_dimension ,
  //             buttons[21][6]    //int16_t button_color
  //           );

  // delay(1000);
  // wait to grbl to start
  int running = -1;
  while ( running == -1){
    // my_lcd.Fill_Screen(BLACK);  
      draw_button("waiting for start", // uint8_t *desc,
                  buttons[21][0],   // int16_t x_from, 
                  buttons[21][1],   // int16_t y_from, 
                  buttons[21][2],   // int16_t x_to, 
                  buttons[21][3],   // int16_t y_to, 
                  buttons[21][4],   // int16_t corner_radius, 
                  buttons[21][5],   //int16_t text_dimension ,
                  buttons[21][6]    //int16_t button_color
                );
    Serial.println("?");
    String grbl_out = Serial.readString();
    running = grbl_out.indexOf("Run");
    // char * grbl_out_uuint8 = new char [grbl_out.length() + 1];
    // strcpy (grbl_out_uuint8, grbl_out.c_str());

    delay (1000);
  }
  //

  draw_button("STARTED", // uint8_t *desc,
              buttons[21][0],   // int16_t x_from, 
              buttons[21][1],   // int16_t y_from, 
              buttons[21][2],   // int16_t x_to, 
              buttons[21][3],   // int16_t y_to, 
              buttons[21][4],   // int16_t corner_radius, 
              buttons[21][5],   //int16_t text_dimension ,
              buttons[21][6]    //int16_t button_color
            );
  delay (1000);

  int idle = -1;
  Serial.println("?");
  String grbl_out = Serial.readString();
  delay(100);

  while (idle == -1){
    Serial.println("?");

    String grbl_out = Serial.readString();
    // int mpos_index = grbl_out.indexOf("MPos") ;
    // int mpos_from = mpos_index + 5;
    // int mpos_to = grbl_out.indexOf(".",mpos_from);

    // idle = grbl_out.indexOf("Idle");

    // if (mpos_index > 1 && mpos_to > mpos_from ){
    //   String grbl_out_turns = grbl_out.substring(mpos_from, mpos_to) + " completed turns";

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
    //     
    my_lcd.Fill_Screen(background);
    char * grbl_out_uuint8 = new char [grbl_out.length() + 1];
    strcpy (grbl_out_uuint8, grbl_out.c_str());
    show_string(grbl_out_uuint8, 1 + 20,2 ,2,BLACK, BLACK,1);
    
    
  delay(300);

  }


  draw_button("FINISH", // uint8_t *desc,
              buttons[21][0],   // int16_t x_from, 
              buttons[21][1],   // int16_t y_from, 
              buttons[21][2],   // int16_t x_to, 
              buttons[21][3],   // int16_t y_to, 
              buttons[21][4],   // int16_t corner_radius, 
              buttons[21][5],   //int16_t text_dimension ,
              buttons[21][6]    //int16_t button_color
                  );



}