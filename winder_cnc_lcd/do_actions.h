
void do_actions(void){

   if(turns_to_wind_field[0] < touch_x && touch_x < turns_to_wind_field[2] &&
      turns_to_wind_field[1] < touch_y && touch_y < turns_to_wind_field[3]  
      ){
        show_numpad();
        return;
      }

   for ( int i = 0; i < scattering_elements ; ++i ) {
      Serial.println(i);
      if(scattering_buttons[i][0] < touch_x && touch_x < scattering_buttons[i][2] &&
        scattering_buttons[i][1] < touch_y && touch_y < scattering_buttons[i][3]  
        ){
           draw_scattering_buttons();
        }
      }


  //  for ( int i = 0; i < total_menu_elements ; ++i ) {
  //     Serial.println(i);
  //     if(buttons[i][0] < touch_x && touch_x < buttons[i][2] &&
  //       buttons[i][1] < touch_y && touch_y < buttons[i][3]  
  //       ){
  //         ritorno = i;
  //       }
  //     }
 
    // if ( ritorno > 0){
    //   if ( buttons[ritorno][7] ==  buttons[ritorno][6] ){
    //     //take color when pressed
    //     buttons[ritorno][7] =buttons[ritorno][8] ;
    //   }       
    //   else {
    //     // back to the defined color - release
    //     buttons[ritorno][7] =    buttons[ritorno][6];
    //   }
    //   // buttons[ritorno][7] =2;
    //   draw_button(buttons_desc[ritorno], // uint8_t *desc,
    //             buttons[ritorno][0],   // int16_t x_from, 
    //             buttons[ritorno][1],   // int16_t y_from, 
    //             buttons[ritorno][2],   // int16_t x_to, 
    //             buttons[ritorno][3],   // int16_t y_to, 
    //             buttons[ritorno][4],   // int16_t corner_radius, 
    //             buttons[ritorno][5],   //int16_t text_dimension ,
    //             buttons[ritorno][7]   //buttons[21][6]    //int16_t button_color
    //           );
    // }        
    
      // run_winder
    //     if ( ritorno == 20 ){
    //       // buttons[ritorno][7] =2;
    //       draw_button(buttons_desc[ritorno], // uint8_t *desc,
    //                 buttons[ritorno][0],   // int16_t x_from, 
    //                 buttons[ritorno][1],   // int16_t y_from, 
    //                 buttons[ritorno][2],   // int16_t x_to, 
    //                 buttons[ritorno][3],   // int16_t y_to, 
    //                 buttons[ritorno][4],   // int16_t corner_radius, 
    //                 buttons[ritorno][5],   //int16_t text_dimension ,
    //                 buttons[ritorno][8]   // -- color when selected
    //               );
    //   }        
    //  // scattering 
    //  if ( ritorno >= 12 && ritorno <=15  ){
    //  // grey out the old scattering
    //     draw_button(buttons_desc[scattering + 12 -1], // uint8_t *desc,
    //               buttons[scattering + 12 -1][0],   // int16_t x_from, 
    //               buttons[scattering + 12 -1][1],   // int16_t y_from, 
    //               buttons[scattering + 12 -1][2],   // int16_t x_to, 
    //               buttons[scattering + 12 -1][3],   // int16_t y_to, 
    //               buttons[scattering + 12 -1][4],   // int16_t corner_radius, 
    //               buttons[scattering + 12 -1][5],   //int16_t text_dimension ,
    //               buttons[scattering + 12 -1][6] );  // color when not selected , default color
    //     scattering = ritorno - 12 + 1;
    //     Serial.print("scattering : ");
    //     Serial.println(scattering);
    //     draw_button(buttons_desc[scattering + 12 -1], // uint8_t *desc,
    //               buttons[scattering + 12 -1][0],   // int16_t x_from, 
    //               buttons[scattering + 12 -1][1],   // int16_t y_from, 
    //               buttons[scattering + 12 -1][2],   // int16_t x_to, 
    //               buttons[scattering + 12 -1][3],   // int16_t y_to, 
    //               buttons[scattering + 12 -1][4],   // int16_t corner_radius, 
    //               buttons[scattering + 12 -1][5],   //int16_t text_dimension ,
    //               buttons[scattering + 12 -1][8]);   // color when selected

    //  }



}

