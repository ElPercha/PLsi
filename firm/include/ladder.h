#ifndef ladder_H
#define ladder_H

// Ladder logic instructions 
void execNop (int c, int r, int f);
void execConn (int c, int r, int f);
void execNeg (int c, int r, int f);
void execNO (int c, int r, int f);
void execNC (int c, int r, int f);
void execRE (int c, int r, int f);
void execFE (int c, int r, int f);
void execCoil (int c, int r, int f);
void execCoilL (int c, int r, int f);
void execCoilU (int c, int r, int f);
void execTON (int c, int r, int f);
void execTOFF (int c, int r, int f);
void execTP (int c, int r, int f);
void execCTU (int c, int r, int f);
void execCTD (int c, int r, int f);
void execMOVE (int c, int r, int f);
void execSUB (int c, int r, int f);
void execADD (int c, int r, int f);
void execMUL (int c, int r, int f);
void execDIV (int c, int r, int f);
void execMOD (int c, int r, int f);
void execSHL (int c, int r, int f);
void execSHR (int c, int r, int f);
void execROL (int c, int r, int f);
void execROR (int c, int r, int f);
void execAND (int c, int r, int f);
void execOR (int c, int r, int f);
void execXOR (int c, int r, int f);
void execNOT (int c, int r, int f);

void execBars (int c);


// Aux functions for ladder logic instructions
int GetDataValue (int r, int c);
int GetPreviousValue (int r, int c);
void SetDataValue(int r, int c, int Value);

#endif