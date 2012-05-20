#ifndef SCORES_H
#define SCORES_H


void loadscores(void);
void showtable(void);
void zeroscores(void);
void writecurscore(int col);
void drawscores(void);
void initscores(void);
void endofgame(void);
void scorekill(int n);
void scorekill2(void);
void scoreemerald(int n);
void scoreoctave(int n);
void scoregold(int n);
void scorebonus(int n);
void scoreeatm(int n, int msc);
void addscore(int n, int16_t score);
void maingetinitials(void);

#ifdef INTDRF
int32_t getscore0(void);
#endif

extern uint16_t bonusscore;
extern int32_t scoret;

extern char scoreinit[11][4];

#endif // SCORES_H
