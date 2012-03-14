#include <QApplication>
#include <QTime>
#include "main.h"
#include "bags.h"
#include "def.h"
#include "digger.h"
#include "hardware.h"
#include "input.h"
#include "monster.h"
#include "sound.h"
#include "record.h"
#include "scores.h"
#include "sprite.h"

extern int8_t leveldat[8][MHEIGHT][MWIDTH+1];

char pldispbuf[14];
int16_t curplayer = 0, nplayers = 1, penalty = 0, diggers = 1, startlev = 1;
bool unlimlives = false, gauntlet = false, timeout = false, synchvid = false;
int gtime = 0;

static struct game
{
	int16_t level;
	bool levdone;
} gamedat[2];

static bool levnotdrawn = false, alldead = false, started;

char levfname[132];
bool levfflag = false;
//static bool biosflag = false;
//static int32_t delaytime = 0;


void shownplayers(void);
void switchnplayers(void);
void drawscreen(void);
void initchars(void);
void checklevdone(void);
int16_t levno(void);
void testpause(void);
void calibrate(void);
void parsecmd(int argc, char *argv[]);
void patchcga(void);
void initlevel(void);
void finish(void);
void inir(void);
void redefkeyb(bool allf);
int getalllives(void);

int16_t getlevch(int16_t x, int16_t y, int16_t l)
{
	//if ((l==3 || l==4) && !levfflag && diggers==2 && y==9 && (x==6 || x==8))
	//	return 'H';
	return leveldat[l-1][y][x];
}

void game(void)
{
	int16_t t, c, i;
	bool flashplayer = false;
	if (gauntlet)
	{
		cgtime = gtime * 1193181l;
		timeout = false;
	}
	initlives();
	gamedat[0].level = startlev;
	if (nplayers == 2)
		gamedat[1].level = startlev;
	alldead = false;
	gclear();
	curplayer = 0;
	initlevel();
	curplayer = 1;
	initlevel();
	zeroscores();
	bonusvisible = true;
	if (nplayers == 2)
		flashplayer = true;
	curplayer = 0;
	while (getalllives() != 0 && !escape && !timeout)
	{
		while (!alldead && !escape && !timeout)
		{
			initmbspr();

			if (playing)
				randv = playgetrand();
			else
				randv = getlrt();
#ifdef INTDRF
			fprintf(info, "%lu\n", randv);
			frame = 0;
#endif
			recputrand(randv);
			if (levnotdrawn)
			{
				levnotdrawn = false;
				drawscreen();
				if (flashplayer)
				{
					flashplayer = false;
					strcpy(pldispbuf, "PLAYER ");
					if (curplayer == 0)
						strcat(pldispbuf, "1");
					else
						strcat(pldispbuf, "2");
					cleartopline();
					for (t = 0; t < 15; t++)
						for (c = 1; c <= 3; c++)
						{
							outtext(pldispbuf, 108, 0, c);
							writecurscore(c);
							newframe();
							if (escape)
								return;
						}
					drawscores();
					for (i = 0; i < diggers; i++)
						addscore(i, 0);
				}
			}
			else
				initchars();
			outtext("        ", 108, 0, 3);
			initscores();
			drawlives();
			music(1);

			flushkeybuf();
			for (i = 0; i < diggers; i++)
				readdirect(i);
			while (!alldead && !gamedat[curplayer].levdone && !escape &&
				   !timeout)
			{
				penalty = 0;
				dodigger();
				domonsters();
				dobags();
				if (penalty > 8)
					incmont(penalty - 8);
				testpause();
				checklevdone();
			}
			erasediggers();
			musicoff();
			t = 20;
			while ((getnmovingbags() != 0 || t != 0) && !escape && !timeout)
			{
				if (t != 0)
					t--;
				penalty = 0;
				dobags();
				dodigger();
				domonsters();
				if (penalty < 8)
					t = 0;
			}
			soundstop();
			for (i = 0; i < diggers; i++)
				killfire(i);
			erasebonus();
			cleanupbags();
			savefield();
			erasemonsters();
			recputeol();
			if (playing)
				playskipeol();
			if (escape)
				recputeog();
			if (gamedat[curplayer].levdone)
				soundlevdone();
			if (countem() == 0 || gamedat[curplayer].levdone)
			{
#ifdef INTDRF
				fprintf(info, "%i\n", frame);
#endif
				for (i = curplayer; i < diggers + curplayer; i++)
					if (getlives(i) > 0 && !digalive(i))
						declife(i);
				drawlives();
				gamedat[curplayer].level++;
				if (gamedat[curplayer].level > 1000)
					gamedat[curplayer].level = 1000;
				initlevel();
			}
			else if (alldead)
			{
#ifdef INTDRF
				fprintf(info, "%i\n", frame);
#endif
				for (i = curplayer; i < curplayer + diggers; i++)
					if (getlives(i) > 0)
						declife(i);
				drawlives();
			}
			if ((alldead && getalllives() == 0 && !gauntlet && !escape) ||
				timeout)
				endofgame();
		}
		alldead = false;
		if (nplayers == 2 && getlives(1 - curplayer) != 0)
		{
			curplayer = 1 - curplayer;
			flashplayer = levnotdrawn = true;
		}
	}
#ifdef INTDRF
	fprintf(info, "-1\n%lu\n%i", getscore0(), gamedat[0].level);
#endif
}

int mainprog(void)
{
	int16_t frame, t, x = 0;
	loadscores();
	escape = false;
	do
	{
		soundstop();
		creatembspr();
		detectjoy();
		gclear();
		gtitle();
		outtext("D I G G E R", 100, 0, 3);
		shownplayers();
		showtable();
		started = false;
		frame = 0;
		newframe();
		teststart();
		while (!started)
		{
			started = teststart();
			if ((akeypressed == 27 || akeypressed == 'n' || akeypressed == 'N')
				&& !gauntlet && diggers == 1)
			{
				switchnplayers();
				shownplayers();
				akeypressed = 0;
			}
			if (frame == 0)
				for (t = 54; t < 174; t += 12)
					outtext("            ", 164, t, 0);
			if (frame == 50)
			{
				movedrawspr(FIRSTMONSTER, 292, 63);
				x = 292;
			}
			if (frame > 50 && frame <= 77)
			{
				x -= 4;
				drawmon(0, 1, DIR_LEFT, x, 63);
			}
			if (frame > 77)
				drawmon(0, 1, DIR_RIGHT, 184, 63);
			if (frame == 83)
				outtext("NOBBIN", 216, 64, 2);
			if (frame == 90)
			{
				movedrawspr(FIRSTMONSTER + 1, 292, 82);
				drawmon(1, 0, DIR_LEFT, 292, 82);
				x = 292;
			}
			if (frame > 90 && frame <= 117)
			{
				x -= 4;
				drawmon(1, 0, DIR_LEFT, x, 82);
			}
			if (frame > 117)
				drawmon(1, 0, DIR_RIGHT, 184, 82);
			if (frame == 123)
				outtext("HOBBIN", 216, 83, 2);
			if (frame == 130)
			{
				movedrawspr(FIRSTDIGGER, 292, 101);
				drawdigger(0, DIR_LEFT, 292, 101, 1);
				x = 292;
			}
			if (frame > 130 && frame <= 157)
			{
				x -= 4;
				drawdigger(0, DIR_LEFT, x, 101, 1);
			}
			if (frame > 157)
				drawdigger(0, DIR_RIGHT, 184, 101, 1);
			if (frame == 163)
				outtext("DIGGER", 216, 102, 2);
			if (frame == 178)
			{
				movedrawspr(FIRSTBAG, 184, 120);
				drawgold(0, 0, 184, 120);
			}
			if (frame == 183)
				outtext("GOLD", 216, 121, 2);
			if (frame == 198)
				drawemerald(184, 141);
			if (frame == 203)
				outtext("EMERALD", 216, 140, 2);
			if (frame == 218)
				drawbonus(184, 158);
			if (frame == 223)
				outtext("BONUS", 216, 159, 2);
			newframe();
			frame++;
			if (frame > 250)
				frame = 0;

			// TODO: remove
			if (frame == 195)
				break;
		}
		if (savedrf)
		{
			if (gotgame)
			{
				recsavedrf();
				gotgame = false;
			}
			savedrf = false;
			continue;
		}
		if (escape)
			break;
		recinit();
		//game();
		gotgame = true;
		if (gotname)
		{
			recsavedrf();
			gotgame = false;
		}
		savedrf = false;
		escape = false;

		break;
	} while (!escape);
	finish();
	return 0;
}


void finish(void)
{
	killsound();
	soundoff();
	soundkillglob();
	restorekeyb();
	graphicsoff();
}

void shownplayers(void)
{
	if (diggers == 2)
		if (gauntlet)
		{
			outtext("TWO PLAYER", 180, 25, 3);
			outtext("GAUNTLET", 192, 39, 3);
		}
		else
		{
			outtext("TWO PLAYER", 180, 25, 3);
			outtext("SIMULTANEOUS", 170, 39, 3);
		}
	else if (gauntlet)
	{
		outtext("GAUNTLET", 192, 25, 3);
		outtext("MODE", 216, 39, 3);
	}
	else if (nplayers == 1)
	{
		outtext("ONE", 220, 25, 3);
		outtext(" PLAYER ", 192, 39, 3);
	}
	else
	{
		outtext("TWO", 220, 25, 3);
		outtext(" PLAYERS", 184, 39, 3);
	}
}

int getalllives(void)
{
	int t = 0, i;
	for (i = curplayer; i < diggers + curplayer; i++)
		t += getlives(i);
	return t;
}

void switchnplayers(void)
{
	nplayers = 3 - nplayers;
}

void initlevel(void)
{
	gamedat[curplayer].levdone = FALSE;
	makefield();
	makeemfield();
	initbags();
	levnotdrawn = TRUE;
}

void drawscreen(void)
{
	creatembspr();
	drawstatics();
	drawbags();
	drawemeralds();
	initdigger();
	initmonsters();
}

void initchars(void)
{
	initmbspr();
	initdigger();
	initmonsters();
}

void checklevdone(void)
{
	if ((countem() == 0 || monleft() == 0) && isalive())
		gamedat[curplayer].levdone = true;
	else
		gamedat[curplayer].levdone = false;
}

void incpenalty(void)
{
	penalty++;
}

void cleartopline(void)
{
	outtext("                          ", 0, 0, 3);
	outtext(" ", 308, 0, 3);
}

int16_t levplan(void)
{
	int16_t l = levno();
	if (l > 8)
		l = (l & 3) + 5;		// Level plan: 12345678, 678, (5678) 247 times, 5 forever
	return l;
}

int16_t levof10(void)
{
	if (gamedat[curplayer].level > 10)
		return 10;
	return gamedat[curplayer].level;
}

int16_t levno(void)
{
	return gamedat[curplayer].level;
}

void setdead(bool df)
{
	alldead = df;
}

void testpause(void)
{
	int i;
	if (pausef)
	{
		soundpause();
		sett2val(40);
		setsoundt2();
		cleartopline();
		outtext("PRESS ANY KEY", 80, 0, 1);
		getkey();
		cleartopline();
		drawscores();
		for (i = 0; i < diggers; i++)
			addscore(i, 0);
		drawlives();
		if (!synchvid)
			curtime = gethrt();
		pausef = false;
	}
	else
		soundpauseoff();
}

void calibrate(void)
{
	volume = (int16_t) (getkips() / 291);
	if (volume == 0)
		volume = 1;
}

uint16_t sound_device, sound_port, sound_irq, sound_dma, sound_rate,
	sound_length;

void parsecmd(int argc, char *argv[])
{
	char *word;
	int16_t arg, i = 0, j, speedmul = 1;
	bool sf, gs = false, norepf = false, quiet = false;
	FILE *levf;

	for (arg = 1; arg < argc; arg++)
	{
		word = argv[arg];
		if (word[0] == '/' || word[0] == '-')
		{
			if (word[1] == 'L' || word[1] == 'l' || word[1] == 'R' ||
				word[1] == 'r' || word[1] == 'P' || word[1] == 'p' ||
				word[1] == 'S' || word[1] == 's' || word[1] == 'E' ||
				word[1] == 'e' || word[1] == 'G' || word[1] == 'g' ||
				word[1] == 'A' || word[1] == 'a' || word[1] == 'I' ||
				word[1] == 'i')
			{
				if (word[2] == ':')
					i = 3;
				else
					i = 2;
			}
			if (word[1] == 'L' || word[1] == 'l')
			{
				j = 0;
				while (word[i] != 0)
					levfname[j++] = word[i++];
				levfname[j] = word[i];
				levfflag = true;
			}
//			if (word[1] == 'R' || word[1] == 'r')
//				recname(word + i);
//			if (word[1] == 'P' || word[1] == 'p' || word[1] == 'E' ||
//				word[1] == 'e')
//			{
//				openplay(word + i);
//				if (escape)
//					norepf = true;
//			}
//			if (word[1] == 'E' || word[1] == 'e')
//			{
//				finish();
//				if (escape)
//					exit(0);
//				exit(1);
//			}
			if ((word[1] == 'O' || word[1] == 'o') && !norepf)
			{
				arg = 0;
				continue;
			}
			if (word[1] == 'S' || word[1] == 's')
			{
				speedmul = 0;
				while (word[i] != 0)
					speedmul = 10 * speedmul + word[i++] - '0';
				ftime = speedmul * 2000l;
				gs = true;
			}
			if (word[1] == 'I' || word[1] == 'i')
				sscanf(word + i, "%hi", &startlev);
			if (word[1] == 'U' || word[1] == 'u')
				unlimlives = true;

			if (word[1] == '?' || word[1] == 'h' || word[1] == 'H')
			{
				finish();
				printf("DIGGER - Copyright (c) 1983 Windmill software\n"
					   "Restored 1998 by AJ Software\n"
#ifdef ARM
					   "Acorn port by Julian Brown\n"
#endif
					   "http://www.digger.org\n"
					   "Version: " DIGGER_VERSION "\n\n"
					   "Command line syntax:\n"
					   "  DIGGER [[/S:]speed] [[/L:]level file] [/C] [/B] [/Q] [/M] "
					   "[/P:playback file]\n"
					   "         [/E:playback file] [/R:record file] [/O] [/K[A]] "
					   "[/G[:time]] [/2]\n"
					   "         [/A:device,port,irq,dma,rate,length] [/V] [/U] "
					   "[/I:level]\n\n"
#ifndef UNIX
					   //"/C = Use CGA graphics\n"
					   //"/B = Use BIOS palette functions for CGA (slow!)\n"
#endif
					   //"/Q = Quiet mode (no sound at all)       "
					   //"/M = No music\n"
					   //"/R = Record graphics to file\n"
					   //"/P = Playback and restart program       "
					   //"/E = Playback and exit program\n"
					   "/O = Loop to beginning of command line\n"
					   //"/K = Redefine keyboard\n"
					   "/G = Gauntlet mode\n"
					   "/2 = Two player simultaneous mode\n"
					   //"/A = Use alternate sound device\n"
#ifndef UNIX
					   "/V = Synchronize timing to vertical retrace\n"
#endif
					   "/U = Allow unlimited lives\n"
					   "/I = Start on a level other than 1\n");
				exit(1);
			}

//			if (word[1] == 'Q' || word[1] == 'q')
//				soundflag = false;
//			if (word[1] == 'M' || word[1] == 'm')
//				musicflag = false;
			if (word[1] == '2')
				diggers = 2;

//			if (word[1] == 'B' || word[1] == 'b' || word[1] == 'C' ||
//				word[1] == 'c')
//			{
//				ginit = cgainit;
//				gpal = cgapal;
//				ginten = cgainten;
//				gclear = cgaclear;
//				ggetpix = cgagetpix;
//				gputi = cgaputi;
//				ggeti = cgageti;
//				gputim = cgaputim;
//				gwrite = cgawrite;
//				gtitle = cgatitle;
//				if (word[1] == 'B' || word[1] == 'b')
//					biosflag = true;
//				ginit();
//				gpal(0);
//			}
//			if (word[1] == 'K' || word[1] == 'k')
//			{
//				if (word[2] == 'A' || word[2] == 'a')
//					redefkeyb(true);
//				else
//					redefkeyb(false);
//			}
//			if (word[1] == 'A' || word[1] == 'a')
//				sscanf(word + i, "%hu,%hx,%hu,%hu,%hu,%hu", &sound_device,
//					   &sound_port, &sound_irq, &sound_dma, &sound_rate,
//					   &sound_length);
			if (word[1] == 'Q' || word[1] == 'q')
				quiet = true;
			if (word[1] == 'V' || word[1] == 'v')
				synchvid = true;

			if (word[1] == 'G' || word[1] == 'g')
			{
				gtime = 0;
				while (word[i] != 0)
					gtime = 10 * gtime + word[i++] - '0';
				if (gtime > 3599)
					gtime = 3599;
				if (gtime == 0)
					gtime = 120;
				gauntlet = true;
			}
		}
		else
		{
			i = strlen(word);
			if (i < 1)
				continue;
			sf = true;
			if (!gs)
				for (j = 0; j < i; j++)
					if (word[j] < '0' || word[j] > '9')
					{
						sf = false;
						break;
					}
			if (sf)
			{
				speedmul = 0;
				j = 0;
				while (word[j] != 0)
					speedmul = 10 * speedmul + word[j++] - '0';
				gs = true;
				ftime = speedmul * 2000l;
			}
			else
			{
				j = 0;
				while (word[j] != 0)
				{
					levfname[j] = word[j];
					j++;
				}
				levfname[j] = word[j];
				levfflag = true;
			}
		}
	}

	if (!quiet)
	{
//		killsound();
//		volume = 1;
//		setupsound = s1setupsound;
//		killsound = s1killsound;
//		fillbuffer = s1fillbuffer;
//		initint8 = s1initint8;
//		restoreint8 = s1restoreint8;
//		soundoff = s1soundoff;
//		setspkrt2 = s1setspkrt2;
//		settimer0 = s1settimer0;
//		timer0 = s1timer0;
//		settimer2 = s1settimer2;
//		timer2 = s1timer2;
//		soundinitglob(sound_port, sound_irq, sound_dma, sound_length,
//					  sound_rate);
//		initsound();
	}

	if (levfflag)
	{
		levf = fopen(levfname, "rb");
		if (levf == NULL)
		{
			strcat(levfname, ".DLF");
			levf = fopen(levfname, "rb");
		}
		if (levf == NULL)
			levfflag = false;
		else
		{
//			fread(&bonusscore, 2, 1, levf);
			fread(leveldat, 1200, 1, levf);
			fclose(levf);
		}
	}
	ftime = speedmul * 2000l;
}

int32_t randv;

int16_t randno(int16_t n)
{
	randv = randv * 0x15a4e35l + 1;
	return (int16_t) ((randv & 0x7fffffffl) % n);
}


MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f) :
	QMainWindow(parent, f)
{
	menu = menuBar();
	QMenu* menu_game = new QMenu("G&ame", menu);
	menu_game->addAction("End game", qApp, SLOT(quit()), QKeySequence::Quit);
	menu->addMenu(menu_game);

	scene = new GraphicsScene;
	view = new GraphicsView(scene);

	setWindowTitle(QObject::tr("D I G G E R"));
	setCentralWidget(view);
	setMinimumSize(640, 400);


//	gamedat[0].level = startlev;
//	initlevel();
//	initlives();
//	initdigger();
//	drawscreen();
//	dodigger();
	show();
	mainprog();
}


int main(int argc, char *argv[])
{
//	calibrate();
//	ginit();
//	gpal(0);
//	setretr(true);
	initkeyb();
//	detectjoy();
//	inir();
//	initsound();
//	recstart();
	inittimer();

	parsecmd(argc, argv);
//	return mainprog();

	QApplication app(argc, argv);
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	MainWindow window;

	return app.exec();
}
