#include <globals.h>

void loadDemoUserPogram(Network Networks[]){
  //--------------------------------------------------
  // NETWORK 0
  //--------------------------------------------------
  Networks[0].Cells[0][0].Code = 3;
  Networks[0].Cells[0][0].Data = 500;
  Networks[0].Cells[0][0].Type = 0;

  Networks[0].Cells[0][1].Code = 7;  
  Networks[0].Cells[0][1].Data = 0;  
  Networks[0].Cells[0][1].Type = 1;  

  Networks[0].Cells[1][0].Code = 3;  
  Networks[0].Cells[1][0].Data = 501;
  Networks[0].Cells[1][0].Type = 0;

  Networks[0].Cells[1][1].Code = 7;
  Networks[0].Cells[1][1].Data = 1;
  Networks[0].Cells[1][1].Type = 1;

  Networks[0].Cells[2][0].Code = 3;
  Networks[0].Cells[2][0].Data = 502;
  Networks[0].Cells[2][0].Type = 0;  

  Networks[0].Cells[2][1].Code = 7;  
  Networks[0].Cells[2][1].Data = 2;  
  Networks[0].Cells[2][1].Type = 1;  

  Networks[0].Cells[3][0].Code = 3;  
  Networks[0].Cells[3][0].Data = 510;
  Networks[0].Cells[3][0].Type = 0;  

  Networks[0].Cells[3][1].Code = 7;  
  Networks[0].Cells[3][1].Data = 3;  
  Networks[0].Cells[3][1].Type = 1;  

  Networks[0].Cells[4][0].Code = 3;  
  Networks[0].Cells[4][0].Data = 511;
  Networks[0].Cells[4][0].Type = 0;  

  Networks[0].Cells[4][1].Code = 7;  
  Networks[0].Cells[4][1].Data = 4;
  Networks[0].Cells[4][1].Type = 1;

  //--------------------------------------------------
  // NETWORK 1
  //--------------------------------------------------
  Networks[1].Cells[0][0].Code = 3;
  Networks[1].Cells[0][0].Data = 0;
  Networks[1].Cells[0][0].Type = 2;

  Networks[1].Cells[0][1].Code = 1;
  Networks[1].Cells[0][1].Data = 0;
  Networks[1].Cells[0][1].Type = 0;

  Networks[1].Cells[0][2].Code = 7;
  Networks[1].Cells[0][2].Data = 5;
  Networks[1].Cells[0][2].Type = 1;

  Networks[1].Cells[1][0].Code = 16;
  Networks[1].Cells[1][0].Data = 500;
  Networks[1].Cells[1][0].Type = 11;

  Networks[1].Bars[1] = 3;

  Networks[1].Cells[2][0].Code = 4112;
  Networks[1].Cells[2][0].Data = 50;
  Networks[1].Cells[2][0].Type = 12;

  Networks[1].Cells[2][1].Code = 1;
  Networks[1].Cells[2][1].Data = 0;
  Networks[1].Cells[2][1].Type = 0;

  Networks[1].Cells[3][0].Code = 8208;
  Networks[1].Cells[3][0].Data = 100;
  Networks[1].Cells[3][0].Type = 11;

  //--------------------------------------------------
  // NETWORK 2
  //--------------------------------------------------
  Networks[2].Cells[0][0].Code = 4;
  Networks[2].Cells[0][0].Data = 90;
  Networks[2].Cells[0][0].Type = 5;

  Networks[2].Cells[0][1].Code = 10;
  Networks[2].Cells[0][1].Data = 90;
  Networks[2].Cells[0][1].Type = 10;

  Networks[2].Cells[0][2].Code = 19;
  Networks[2].Cells[0][2].Data = 90;
  Networks[2].Cells[0][2].Type = 10;

  Networks[2].Cells[0][3].Code = 19;
  Networks[2].Cells[0][3].Data = 90;
  Networks[2].Cells[0][3].Type = 10;

  Networks[2].Cells[0][4].Code = 15;
  Networks[2].Cells[0][4].Data = 90;
  Networks[2].Cells[0][4].Type = 10;

  Networks[2].Cells[1][1].Code = 4106;
  Networks[2].Cells[1][1].Data = 5000;
  Networks[2].Cells[1][1].Type = 1;

  Networks[2].Cells[1][2].Code = 4115;
  Networks[2].Cells[1][2].Data = 10;
  Networks[2].Cells[1][2].Type = 12;

  Networks[2].Cells[1][3].Code = 4115;
  Networks[2].Cells[1][3].Data = 100;
  Networks[2].Cells[1][3].Type = 12;

  Networks[2].Cells[1][4].Code = 4111;
  Networks[2].Cells[1][4].Data = 517;
  Networks[2].Cells[1][4].Type = 11;

  Networks[2].Bars[1] = 1;

  Networks[2].Cells[2][2].Code = 8211;
  Networks[2].Cells[2][2].Data = 510;
  Networks[2].Cells[2][2].Type = 11;

  Networks[2].Cells[2][3].Code = 8211;
  Networks[2].Cells[2][3].Data = 511;
  Networks[2].Cells[2][3].Type = 11;

  //--------------------------------------------------
  // NETWORK 3
  //--------------------------------------------------
  Networks[3].Cells[0][0].Code = 4;
  Networks[3].Cells[0][0].Data = 108;
  Networks[3].Cells[0][0].Type = 5;

  Networks[3].Cells[0][1].Code = 10;
  Networks[3].Cells[0][1].Data = 100;
  Networks[3].Cells[0][1].Type = 10;

  Networks[3].Cells[0][2].Code = 10;
  Networks[3].Cells[0][2].Data = 101;
  Networks[3].Cells[0][2].Type = 10;

  Networks[3].Cells[0][3].Code = 10;
  Networks[3].Cells[0][3].Data = 102;
  Networks[3].Cells[0][3].Type = 10;

  Networks[3].Cells[0][4].Code = 10;
  Networks[3].Cells[0][4].Data = 103;
  Networks[3].Cells[0][4].Type = 10;

  Networks[3].Cells[0][5].Code = 10;
  Networks[3].Cells[0][5].Data = 104;
  Networks[3].Cells[0][5].Type = 10;

  Networks[3].Cells[1][1].Code = 4106;
  Networks[3].Cells[1][1].Data = 500;
  Networks[3].Cells[1][1].Type = 1;

  Networks[3].Cells[1][2].Code = 4106;
  Networks[3].Cells[1][2].Data = 500;
  Networks[3].Cells[1][2].Type = 1;

  Networks[3].Cells[1][3].Code = 4106;
  Networks[3].Cells[1][3].Data = 500;
  Networks[3].Cells[1][3].Type = 1;

  Networks[3].Cells[1][4].Code = 4106;
  Networks[3].Cells[1][4].Data = 500;
  Networks[3].Cells[1][4].Type = 1;

  Networks[3].Cells[1][5].Code = 4106;
  Networks[3].Cells[1][5].Data = 500;
  Networks[3].Cells[1][5].Type = 1;

  Networks[3].Cells[2][0].Code = 3;
  Networks[3].Cells[2][0].Data = 104;
  Networks[3].Cells[2][0].Type = 5;

  Networks[3].Cells[2][1].Code = 10;
  Networks[3].Cells[2][1].Data = 105;
  Networks[3].Cells[2][1].Type = 10;

  Networks[3].Cells[2][2].Code = 10;
  Networks[3].Cells[2][2].Data = 106;
  Networks[3].Cells[2][2].Type = 10;

  Networks[3].Cells[2][3].Code = 10;
  Networks[3].Cells[2][3].Data = 107;
  Networks[3].Cells[2][3].Type = 10;

  Networks[3].Cells[2][4].Code = 10;
  Networks[3].Cells[2][4].Data = 108;
  Networks[3].Cells[2][4].Type = 10;

  Networks[3].Cells[3][1].Code = 4106;
  Networks[3].Cells[3][1].Data = 500;
  Networks[3].Cells[3][1].Type = 1;

  Networks[3].Cells[3][2].Code = 4106;
  Networks[3].Cells[3][2].Data = 500;
  Networks[3].Cells[3][2].Type = 1;

  Networks[3].Cells[3][3].Code = 4106;
  Networks[3].Cells[3][3].Data = 500;
  Networks[3].Cells[3][3].Type = 1;

  Networks[3].Cells[3][4].Code = 4106;
  Networks[3].Cells[3][4].Data = 20;
  Networks[3].Cells[3][4].Type = 100;

  //--------------------------------------------------
  // NETWORK 4
  //--------------------------------------------------
  Networks[4].Cells[0][0].Code = 3;
  Networks[4].Cells[0][0].Data = 100;
  Networks[4].Cells[0][0].Type = 5;

  Networks[4].Cells[0][1].Code = 7;
  Networks[4].Cells[0][1].Data = 520;
  Networks[4].Cells[0][1].Type = 0;

  Networks[4].Cells[0][3].Code = 3;
  Networks[4].Cells[0][3].Data = 104;
  Networks[4].Cells[0][3].Type = 5;

  Networks[4].Cells[0][4].Code = 7;
  Networks[4].Cells[0][4].Data = 524;
  Networks[4].Cells[0][4].Type = 0;

  Networks[4].Cells[1][0].Code = 3;
  Networks[4].Cells[1][0].Data = 101;
  Networks[4].Cells[1][0].Type = 5;

  Networks[4].Cells[1][1].Code = 7;
  Networks[4].Cells[1][1].Data = 521;
  Networks[4].Cells[1][1].Type = 0;

  Networks[4].Cells[1][3].Code = 3;
  Networks[4].Cells[1][3].Data = 105;
  Networks[4].Cells[1][3].Type = 5;

  Networks[4].Cells[1][4].Code = 7;
  Networks[4].Cells[1][4].Data = 525;
  Networks[4].Cells[1][4].Type = 0;

  Networks[4].Cells[2][0].Code = 3;
  Networks[4].Cells[2][0].Data = 102;
  Networks[4].Cells[2][0].Type = 5;

  Networks[4].Cells[2][1].Code = 7;
  Networks[4].Cells[2][1].Data = 522;
  Networks[4].Cells[2][1].Type = 0;

  Networks[4].Cells[2][3].Code = 3;
  Networks[4].Cells[2][3].Data = 106;
  Networks[4].Cells[2][3].Type = 5;

  Networks[4].Cells[2][4].Code = 7;
  Networks[4].Cells[2][4].Data = 526;
  Networks[4].Cells[2][4].Type = 0;

  Networks[4].Bars[2] = 15;

  Networks[4].Cells[3][0].Code = 3;
  Networks[4].Cells[3][0].Data = 103;
  Networks[4].Cells[3][0].Type = 5;

  Networks[4].Cells[3][1].Code = 7;
  Networks[4].Cells[3][1].Data = 523;
  Networks[4].Cells[3][1].Type = 0;

  Networks[4].Cells[3][3].Code = 3;
  Networks[4].Cells[3][3].Data = 107;
  Networks[4].Cells[3][3].Type = 5;

  Networks[4].Cells[3][4].Code = 7;
  Networks[4].Cells[3][4].Data = 527;
  Networks[4].Cells[3][4].Type = 0;

  Networks[4].Cells[4][0].Code = 1;
  Networks[4].Cells[4][0].Data = 0;
  Networks[4].Cells[4][0].Type = 0;

  Networks[4].Cells[4][1].Code = 1;
  Networks[4].Cells[4][1].Data = 0;
  Networks[4].Cells[4][1].Type = 0;

  Networks[4].Cells[4][2].Code = 1;
  Networks[4].Cells[4][2].Data = 0;
  Networks[4].Cells[4][2].Type = 0;

  Serial.println("TaskLadder - Demo program loaded...");
  
  // Ladder Logic used to test performance (Boolean time execution)
  // for (uint16_t n = 0; n < TOTAL_NETWORKS; n++){
  // for (uint16_t n = 0; n < 67; n++){
  //   for (uint16_t r = 0; r < NET_ROWS; r++){

  //       Networks[n].Cells[r][0].Code = 3;
  //       Networks[n].Cells[r][0].Data = 520 + r + n*5;
  //       Networks[n].Cells[r][0].Type = 0;

  //       Networks[n].Cells[r][1].Code = 3;
  //       Networks[n].Cells[r][1].Data = 520 + r + n*5;
  //       Networks[n].Cells[r][1].Type = 0;

  //       Networks[n].Cells[r][2].Code = 3;
  //       Networks[n].Cells[r][2].Data = 520 + r + n*5;
  //       Networks[n].Cells[r][2].Type = 0;

  //       Networks[n].Cells[r][3].Code = 3;
  //       Networks[n].Cells[r][3].Data = 520 + r + n*5;
  //       Networks[n].Cells[r][3].Type = 0;

  //       Networks[n].Cells[r][4].Code = 3;
  //       Networks[n].Cells[r][4].Data = 520 + r + n*5;
  //       Networks[n].Cells[r][4].Type = 0;

  //       Networks[n].Cells[r][5].Code = 7;
  //       Networks[n].Cells[r][5].Data = 521 + r + n*5;
  //       Networks[n].Cells[r][5].Type = 0;
  //   }
  // }  
}

