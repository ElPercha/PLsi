

extern uint16_t ShowingNetwork;
extern uint16_t NetworkFlagsOnline[NET_COLUMNS - 1];

extern void execNop (int n, int c, int r, int f);
extern void execConn (int n, int c, int r, int f);
extern void execNeg (int n, int c, int r, int f);
extern void execNO (int n, int c, int r, int f);
extern void execNC (int n, int c, int r, int f);
extern void execRE (int n, int c, int r, int f);
extern void execFE (int n, int c, int r, int f);
extern void execCoil (int n, int c, int r, int f);
extern void execCoilL (int n, int c, int r, int f);
extern void execCoilU (int n, int c, int r, int f);
extern void execTON (int n, int c, int r, int f);
extern void execTOFF (int n, int c, int r, int f);
extern void execTP (int n, int c, int r, int f);
extern void execCTU (int n, int c, int r, int f);
extern void execCTD (int n, int c, int r, int f);
extern void execMOVE (int n, int c, int r, int f);
extern void execSUB (int n, int c, int r, int f);
extern void execADD (int n, int c, int r, int f);
extern void execMUL (int n, int c, int r, int f);
extern void execDIV (int n, int c, int r, int f);
extern void execMOD (int n, int c, int r, int f);
extern void execSHL (int n, int c, int r, int f);
extern void execSHR (int n, int c, int r, int f);
extern void execROL (int n, int c, int r, int f);
extern void execROR (int n, int c, int r, int f);
extern void execAND (int n, int c, int r, int f);
extern void execOR (int n, int c, int r, int f);
extern void execXOR (int n, int c, int r, int f);
extern void execNOT (int n, int c, int r, int f);

