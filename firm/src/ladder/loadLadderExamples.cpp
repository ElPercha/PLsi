#include <globals.h>

void DebugCreateNetworks(Network Networks[]){
  Networks[0].Cells[0][0].Code = 3;
  Networks[0].Cells[0][0].Data = 0;
  Networks[0].Cells[0][0].Type = 2;

  Networks[0].Cells[0][1].Code = 4;
  Networks[0].Cells[0][1].Data = 1;
  Networks[0].Cells[0][1].Type = 2;

  Networks[0].Cells[1][0].Code = 3;
  Networks[0].Cells[1][0].Data = 3;
  Networks[0].Cells[1][0].Type = 1;

  Networks[0].Cells[0][2].Code = 7;
  Networks[0].Cells[0][2].Data = 3;
  Networks[0].Cells[0][2].Type = 1;

  Networks[0].Bars[0] = 9;
  
  Networks[0].Cells[3][0].Code = 3;
  Networks[0].Cells[3][0].Data = 3;
  Networks[0].Cells[3][0].Type = 2;

  Networks[0].Cells[3][1].Code = 4;
  Networks[0].Cells[3][1].Data = 4;
  Networks[0].Cells[3][1].Type = 2;

  Networks[0].Cells[3][2].Code = 7;
  Networks[0].Cells[3][2].Data = 5000;
  Networks[0].Cells[3][2].Type = 0;

  Networks[0].Cells[4][0].Code = 3;
  Networks[0].Cells[4][0].Data = 5000;
  Networks[0].Cells[4][0].Type = 0;

  Networks[1].Cells[0][0].Code = 4;
  Networks[1].Cells[0][0].Data = 100;
  Networks[1].Cells[0][0].Type = 0;

  Networks[1].Cells[2][0].Code = 3;
  Networks[1].Cells[2][0].Data = 101;
  Networks[1].Cells[2][0].Type = 0;
          
  Networks[1].Cells[0][3].Code = 7;
  Networks[1].Cells[0][3].Data = 101;
  Networks[1].Cells[0][3].Type = 0;

  Networks[1].Cells[3][4].Code = 7;
  Networks[1].Cells[3][4].Data = 100;
  Networks[1].Cells[3][4].Type = 0;

  Networks[1].Cells[0][1].Code = 10;
  Networks[1].Cells[0][1].Data = 11;
  Networks[1].Cells[0][1].Type = 10;
  //Networks[1].Cells[1][1].Code = 0;
  Networks[1].Cells[1][1].Data = 6500;
  Networks[1].Cells[1][1].Type = 1;

  Networks[1].Cells[2][1].Code = 10;   //TON
  Networks[1].Cells[2][1].Data = 57;   //Timer number
  Networks[1].Cells[2][1].Type = 10;   //TypeTimer always 10
  //Networks[1].Cells[3][1].Code = 0;  //
  Networks[1].Cells[3][1].Data = 80;   //Setpoint
  Networks[1].Cells[3][1].Type = 1000; //Scale


  Networks[1].Cells[3][3].Code = 10;
  Networks[1].Cells[3][3].Data = 299;
  Networks[1].Cells[3][3].Type = 10;
  //Networks[1].Cells[4][3].Code = 0;
  Networks[1].Cells[4][3].Data = 777;
  Networks[1].Cells[4][3].Type = 10;


      
  Networks[1].Cells[0][2].Code = 1;
  Networks[1].Cells[1][2].Code = 1;
  Networks[1].Cells[2][2].Code = 1;

  Networks[1].Bars[2] = 4;


  Networks[2].Cells[0][0].Code = 3;
  Networks[2].Cells[0][0].Data = 3;
  Networks[2].Cells[0][0].Type = 2;

  Networks[2].Cells[0][1].Code = 11;
  Networks[2].Cells[0][1].Data = 15;
  Networks[2].Cells[0][1].Type = 10;
  //Networks[2].Cells[1][1].Code = 0;
  Networks[2].Cells[1][1].Data = 800;
  Networks[2].Cells[1][1].Type = 1;

  Networks[2].Cells[0][2].Code = 1;
  Networks[2].Cells[1][2].Code = 1;

  Networks[3].Cells[0][0].Code = 3;
  Networks[3].Cells[0][0].Data = 1;
  Networks[3].Cells[0][0].Type = 2;

  Networks[3].Cells[0][1].Code = 12;
  Networks[3].Cells[0][1].Data = 16;
  Networks[3].Cells[0][1].Type = 10;
  //Networks[3].Cells[1][1].Code = 0;
  Networks[3].Cells[1][1].Data = 90;
  Networks[3].Cells[1][1].Type = 10;

  Networks[3].Cells[0][2].Code = 1;
  Networks[3].Cells[1][2].Code = 1;


  Networks[4].Cells[0][0].Code = 3;
  Networks[4].Cells[0][0].Data = 0;
  Networks[4].Cells[0][0].Type = 2;

  Networks[4].Cells[1][0].Code = 3;
  Networks[4].Cells[1][0].Data = 1;
  Networks[4].Cells[1][0].Type = 2;

  Networks[4].Cells[2][0].Code = 3;
  Networks[4].Cells[2][0].Data = 2;
  Networks[4].Cells[2][0].Type = 2;

  Networks[4].Cells[3][0].Code = 3;
  Networks[4].Cells[3][0].Data = 3;
  Networks[4].Cells[3][0].Type = 2;

  Networks[4].Cells[4][0].Code = 3;
  Networks[4].Cells[4][0].Data = 4;
  Networks[4].Cells[4][0].Type = 2;

  Networks[4].Cells[0][1].Code = 7;
  Networks[4].Cells[0][1].Data = 0;
  Networks[4].Cells[0][1].Type = 1;

  Networks[4].Cells[1][1].Code = 7;
  Networks[4].Cells[1][1].Data = 1;
  Networks[4].Cells[1][1].Type = 1;

  Networks[4].Cells[2][1].Code = 7;
  Networks[4].Cells[2][1].Data = 2;
  Networks[4].Cells[2][1].Type = 1;

  Networks[4].Cells[3][1].Code = 7;
  Networks[4].Cells[3][1].Data = 5;
  Networks[4].Cells[3][1].Type = 1;

  Networks[4].Cells[4][1].Code = 7;
  Networks[4].Cells[4][1].Data = 4;
  Networks[4].Cells[4][1].Type = 1;

  Networks[4].Cells[4][2].Code = 7;
  Networks[4].Cells[4][2].Data = 5;
  Networks[4].Cells[4][2].Type = 1;

  Networks[4].Cells[1][2].Code = 3;
  Networks[4].Cells[1][2].Data = 5;
  Networks[4].Cells[1][2].Type = 2;

  Networks[4].Cells[2][2].Code = 3;
  Networks[4].Cells[2][2].Data = 6;
  Networks[4].Cells[2][2].Type = 2;

  Networks[4].Cells[3][2].Code = 3;
  Networks[4].Cells[3][2].Data = 7;
  Networks[4].Cells[3][2].Type = 2;

  Networks[5].Cells[0][0].Code = 3;
  Networks[5].Cells[0][0].Data = 1;
  Networks[5].Cells[0][0].Type = 2;

  Networks[5].Cells[0][1].Code = 15;
  Networks[5].Cells[0][1].Data = -32100;
  Networks[5].Cells[0][1].Type = 12;

  Networks[5].Cells[1][1].Code = 0;
  Networks[5].Cells[1][1].Data = 0;
  Networks[5].Cells[1][1].Type = 8;

  Networks[5].Cells[3][0].Code = 3;
  Networks[5].Cells[3][0].Data = 0;
  Networks[5].Cells[3][0].Type = 2;

  Networks[5].Cells[3][1].Code = 15;
  Networks[5].Cells[3][1].Data = 0;
  Networks[5].Cells[3][1].Type = 7;

  Networks[5].Cells[4][1].Code = 0;
  Networks[5].Cells[4][1].Data = 0;
  Networks[5].Cells[4][1].Type = 8;

  Networks[6].Cells[0][0].Code = 4;
  Networks[6].Cells[0][0].Data = 130;
  Networks[6].Cells[0][0].Type = 5;

  Networks[6].Cells[0][1].Code = 10;
  Networks[6].Cells[0][1].Data = 130;
  Networks[6].Cells[0][1].Type = 10;

  Networks[6].Cells[1][1].Code = 0;
  Networks[6].Cells[1][1].Data = 256;
  Networks[6].Cells[1][1].Type = 10;

  Networks[6].Cells[0][2].Code = 15;
  Networks[6].Cells[0][2].Data = 130;
  Networks[6].Cells[0][2].Type = 10;

  Networks[6].Cells[1][2].Code = 0;
  Networks[6].Cells[1][2].Data = 0;
  Networks[6].Cells[1][2].Type = 8;

  Networks[6].Bars[1] = 1;

  Networks[7].Cells[0][0].Code = 15;
  Networks[7].Cells[0][0].Data = 49;
  Networks[7].Cells[0][0].Type = 7;

  Networks[7].Cells[1][0].Code = 0;
  Networks[7].Cells[1][0].Data = 100;
  Networks[7].Cells[1][0].Type = 11;

  Networks[7].Cells[0][1].Code = 15;
  Networks[7].Cells[0][1].Data = 48;
  Networks[7].Cells[0][1].Type = 7;

  Networks[7].Cells[1][1].Code = 0;
  Networks[7].Cells[1][1].Data = 101;
  Networks[7].Cells[1][1].Type = 11;

  Networks[8].Cells[1][1].Code = 16;
  Networks[8].Cells[1][1].Data = 23;
  Networks[8].Cells[1][1].Type = 11;

  Networks[8].Cells[1][2].Code = 17;
  Networks[8].Cells[1][2].Data = 23;
  Networks[8].Cells[1][2].Type = 11;
  
  Networks[9].Cells[0][1].Code = 13;
  Networks[9].Cells[0][1].Data = 92;
  Networks[9].Cells[0][1].Type =  9;
  Networks[9].Cells[1][1].Code =  0;
  Networks[9].Cells[1][1].Data = 30;
  Networks[9].Cells[1][1].Type =  0;
 
  Networks[9].Cells[2][1].Code = 14;
  Networks[9].Cells[2][1].Data = 93;
  Networks[9].Cells[2][1].Type =  9;
  Networks[9].Cells[3][1].Code =  0;
  Networks[9].Cells[3][1].Data = 30;
  Networks[9].Cells[3][1].Type =  0;

  Networks[9].Cells[0][0].Code = 3;
  Networks[9].Cells[0][0].Data = 0;
  Networks[9].Cells[0][0].Type = 2;

  Networks[9].Cells[1][0].Code = 3;
  Networks[9].Cells[1][0].Data = 1;
  Networks[9].Cells[1][0].Type = 2;

  Networks[9].Cells[2][0].Code = 3;
  Networks[9].Cells[2][0].Data = 2;
  Networks[9].Cells[2][0].Type = 2;

  Networks[9].Cells[3][0].Code = 3;
  Networks[9].Cells[3][0].Data = 3;
  Networks[9].Cells[3][0].Type = 2;

  Networks[9].Cells[4][0].Code = 3;
  Networks[9].Cells[4][0].Data = 92;
  Networks[9].Cells[4][0].Type = 3;

  Networks[9].Cells[4][1].Code = 3;
  Networks[9].Cells[4][1].Data = 93;
  Networks[9].Cells[4][1].Type = 3;

  Networks[10].Cells[0][0].Code = 16;
  Networks[10].Cells[0][0].Data = 130;
  Networks[10].Cells[0][0].Type =  10;
  Networks[10].Cells[1][0].Code =  0;
  Networks[10].Cells[1][0].Data = 93;
  Networks[10].Cells[1][0].Type =  9;
  Networks[10].Cells[2][0].Code =  0;
  Networks[10].Cells[2][0].Data =200;
  Networks[10].Cells[2][0].Type = 11;

  Networks[10].Cells[0][1].Code = 17;
  Networks[10].Cells[0][1].Data = 130;
  Networks[10].Cells[0][1].Type =  10;
  Networks[10].Cells[1][1].Code =  0;
  Networks[10].Cells[1][1].Data = 93;
  Networks[10].Cells[1][1].Type =  9;
  Networks[10].Cells[2][1].Code =  0;
  Networks[10].Cells[2][1].Data =201;
  Networks[10].Cells[2][1].Type = 11;

  Networks[10].Cells[0][2].Code = 18;
  Networks[10].Cells[0][2].Data = 92;
  Networks[10].Cells[0][2].Type =  9;
  Networks[10].Cells[1][2].Code =  0;
  Networks[10].Cells[1][2].Data = 93;
  Networks[10].Cells[1][2].Type =  9;
  Networks[10].Cells[2][2].Code =  0;
  Networks[10].Cells[2][2].Data =202;
  Networks[10].Cells[2][2].Type = 11;
  
  Networks[10].Cells[0][3].Code = 19;
  Networks[10].Cells[0][3].Data = 92;
  Networks[10].Cells[0][3].Type =  9;
  Networks[10].Cells[1][3].Code =  0;
  Networks[10].Cells[1][3].Data = 93;
  Networks[10].Cells[1][3].Type =  9;
  Networks[10].Cells[2][3].Code =  0;
  Networks[10].Cells[2][3].Data =203;
  Networks[10].Cells[2][3].Type = 11;

  Networks[10].Cells[0][4].Code = 20;
  Networks[10].Cells[0][4].Data = 92;
  Networks[10].Cells[0][4].Type =  9;
  Networks[10].Cells[1][4].Code =  0;
  Networks[10].Cells[1][4].Data = 93;
  Networks[10].Cells[1][4].Type =  9;
  Networks[10].Cells[2][4].Code =  0;
  Networks[10].Cells[2][4].Data =204;
  Networks[10].Cells[2][4].Type = 11;

  //Networks[10].Bars[0] = 3;

  Networks[11].Cells[0][0].Code = 25;
  Networks[11].Cells[0][0].Data = 92;
  Networks[11].Cells[0][0].Type =  9;
  Networks[11].Cells[1][0].Code =  0;
  Networks[11].Cells[1][0].Data = 93;
  Networks[11].Cells[1][0].Type =  9;
  Networks[11].Cells[2][0].Code =  0;
  Networks[11].Cells[2][0].Data =205;
  Networks[11].Cells[2][0].Type = 11;

  Networks[11].Cells[0][1].Code = 26;
  Networks[11].Cells[0][1].Data = 92;
  Networks[11].Cells[0][1].Type =  9;
  Networks[11].Cells[1][1].Code =  0;
  Networks[11].Cells[1][1].Data = 93;
  Networks[11].Cells[1][1].Type =  9;
  Networks[11].Cells[2][1].Code =  0;
  Networks[11].Cells[2][1].Data =206;
  Networks[11].Cells[2][1].Type = 11;
  
  Networks[11].Cells[0][2].Code = 27;
  Networks[11].Cells[0][2].Data = 92;
  Networks[11].Cells[0][2].Type =  9;
  Networks[11].Cells[1][2].Code =  0;
  Networks[11].Cells[1][2].Data = 93;
  Networks[11].Cells[1][2].Type =  9;
  Networks[11].Cells[2][2].Code =  0;
  Networks[11].Cells[2][2].Data =207;
  Networks[11].Cells[2][2].Type = 11;

  Networks[11].Cells[0][3].Code = 28;
  Networks[11].Cells[0][3].Data = 92;
  Networks[11].Cells[0][3].Type =  9;
  Networks[11].Cells[1][3].Code =  0;
  Networks[11].Cells[1][3].Data =208;
  Networks[11].Cells[1][3].Type = 11;

  
  Networks[11].Cells[3][0].Code = 21;
  Networks[11].Cells[3][0].Data = 92;
  Networks[11].Cells[3][0].Type =  9;
  Networks[11].Cells[4][0].Code =  0;
  Networks[11].Cells[4][0].Data = 300;
  Networks[11].Cells[4][0].Type =  11;
  
  Networks[11].Cells[3][1].Code = 22;
  Networks[11].Cells[3][1].Data = 92;
  Networks[11].Cells[3][1].Type =  9;
  Networks[11].Cells[4][1].Code =  0;
  Networks[11].Cells[4][1].Data = 301;
  Networks[11].Cells[4][1].Type =  11;

  Networks[11].Cells[3][2].Code = 23;
  Networks[11].Cells[3][2].Data = 92;
  Networks[11].Cells[3][2].Type =  9;
  Networks[11].Cells[4][2].Code =  0;
  Networks[11].Cells[4][2].Data = 302;
  Networks[11].Cells[4][2].Type =  11;

  Networks[11].Cells[3][3].Code = 24;
  Networks[11].Cells[3][3].Data = 92;
  Networks[11].Cells[3][3].Type =  9;
  Networks[11].Cells[4][3].Code =  0;
  Networks[11].Cells[4][3].Data = 303;
  Networks[11].Cells[4][3].Type =  11;

  // FlashNetworks[0].put(0, Networks);
  // FlashNetworks[0].commit();
  // FlashNetworks[0].end();
  Serial.println("Testing program loaded...");
}

