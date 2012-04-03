#include "def.h"

int8_t leveldat[8][MHEIGHT][MWIDTH+1]=
{{"S   B     HHHHS",
  "V  CC  C  V B  ",
  "VB CC  C  V    ",
  "V  CCB CB V CCC",
  "V  CC  C  V CCC",
  "HH CC  C  V CCC",
  " V    B B V    ",
  " HHHH     V    ",
  "C   V     V   C",
  "CC  HHHHHHH  CC"},
 {"SHHHHH  B B  HS",
  " CC  V       V ",
  " CC  V CCCCC V ",
  "BCCB V CCCCC V ",
  "CCCC V       V ",
  "CCCC V B  HHHH ",
  " CC  V CC V    ",
  " BB  VCCCCV CC ",
  "C    V CC V CC ",
  "CC   HHHHHH    "},
 {"SHHHHB B BHHHHS",
  "CC  V C C V BB ",
  "C   V C C V CC ",
  " BB V C C VCCCC",
  "CCCCV C C VCCCC",
  "CCCCHHHHHHH CC ",
  " CC  C V C  CC ",
  " CC  C V C     ",
  "C    C V C    C",
  "CC   C H C   CC"},
 {"SHBCCCCBCCCCBHS",
  "CV  CCCCCCC  VC",
  "CHHH CCCCC HHHC",
  "C  V  CCC  V  C",
  "   HHH C HHH   ",
  "  B  V B V  B  ",
  "  C  VCCCV  C  ",
  " CCC HHHHH CCC ",
  "CCCCC CVC CCCCC",
  "CCCCC CHC CCCCC"},
 {"SHHHHHHHHHHHHHS",
  "VBCCCCBVCCCCCCV",
  "VCCCCCCV CCBC V",
  "V CCCC VCCBCCCV",
  "VCCCCCCV CCCC V",
  "V CCCC VBCCCCCV",
  "VCCBCCCV CCCC V",
  "V CCBC VCCCCCCV",
  "VCCCCCCVCCCCCCV",
  "HHHHHHHHHHHHHHH"},
 {"SHHHHHHHHHHHHHS",
  "VCBCCV V VCCBCV",
  "VCCC VBVBV CCCV",
  "VCCCHH V HHCCCV",
  "VCC V CVC V CCV",
  "VCCHH CVC HHCCV",
  "VC V CCVCC V CV",
  "VCHHBCCVCCBHHCV",
  "VCVCCCCVCCCCVCV",
  "HHHHHHHHHHHHHHH"},
 {"SHCCCCCVCCCCCHS",
  " VCBCBCVCBCBCV ",
  "BVCCCCCVCCCCCVB",
  "CHHCCCCVCCCCHHC",
  "CCV CCCVCCC VCC",
  "CCHHHCCVCCHHHCC",
  "CCCCV CVC VCCCC",
  "CCCCHH V HHCCCC",
  "CCCCCV V VCCCCC",
  "CCCCCHHHHHCCCCC"},
 {"HHHHHHHHHHHHHHS",
  "V CCBCCCCCBCC V",
  "HHHCCCCBCCCCHHH",
  "VBV CCCCCCC VBV",
  "VCHHHCCCCCHHHCV",
  "VCCBV CCC VBCCV",
  "VCCCHHHCHHHCCCV",
  "VCCCC V V CCCCV",
  "VCCCCCV VCCCCCV",
  "HHHHHHHHHHHHHHH"}};

int spriteDimensions[] = {
	0,0,0,0,
	/* Red digger */
	32,		16,		32,	30, /* 1 right - loaded */
	120,	16,		32,	30,
	208,	16,		32,	30,
	32,		72,		32,	30, /* 4 right - unloaded */
	120,	72,		32,	30,

	208,	72,		32,	30,
	560,	16,		32,	30, /* 7 up - loaded */
	648,	16,		32,	30,
	736,	16,		32,	30,
	560,	72,		32,	30, /* 10 up - unloaded */

	648,	72,		32,	30,
	736,	72,		32,	30,
	296,	16,		32,	30, /* 13 left - loaded */
	384,	16,		32,	30,
	472,	16,		32,	30,

	296,	72,		32,	30, /* 16 left - unloaded */
	384,	72,		32,	30,
	472,	72,		32,	30,
	824,	16,		32,	30, /* 19 down - loaded */
	912,	16,		32,	30,

	1000,	16,		32,	30,
	824,	72,		32,	30, /* 22 down - unloaded */
	912,	72,		32,	30,
	1000,	72,		32,	30,
	/*0,0,0,0, //  vgadiggerd, vgadiggerdmask,
	0,0,0,0, //	vgagrave1, vgagrave1mask,
	0,0,0,0, //	vgagrave2, vgagrave2mask,
	0,0,0,0, //	vgagrave3, vgagrave3mask,
	0,0,0,0, //	vgagrave4, vgagrave4mask,
	0,0,0,0,*/ //	vgagrave5, vgagrave5mask,

	/* 25 (32) Green digger */
	32,		128,		32,	30, /* right - loaded */
	120,	128,		32,	30,
	208,	128,		32,	30,
	32,		184,		32,	30, /* right - unloaded */
	120,	184,		32,	30,
	208,	184,		32,	30,
	560,	128,		32,	30, /* up - loaded */
	648,	128,		32,	30,
	736,	128,		32,	30,
	560,	184,		32,	30, /* up - unloaded */
	648,	184,		32,	30,
	736,	184,		32,	30,
	296,	128,		32,	30, /* left - loaded */
	384,	128,		32,	30,
	472,	128,		32,	30,
	296,	184,		32,	30, /* left - unloaded */
	384,	184,		32,	30,
	472,	184,		32,	30,
	824,	128,		32,	30, /* down - loaded */
	912,	128,		32,	30,
	1000,	128,		32,	30,
	824,	184,		32,	30, /* down - unloaded */
	912,	184,		32,	30,
	1000,	184,		32,	30,

	/* 48 Monsters */
	32,		240,		32,	30, /* first */
	120,	240,		32,	30,

	208,	240,		32,	30,
	296,	240,		32,	30,
	384,	240,		32,	30, /* second - right */
	472,	240,		32,	30,
	560,	240,		32,	30,

	648,	240,		32,	30,
	736,	240,		32,	30, /* second - left */
	824,	240,		32,	30,
	912,	240,		32,	30,
	1000,	240,		32,	30,

	/* 60 Various */
	32,		296,		32,	30, /* emerald */
	120,	296,		32,	30, /* bags */
	208,	296,		32,	30,
	296,	296,		32,	30,
	384,	296,		32,	30,
	472,	296,		32,	30, /* coins */

	560,	296,		32,	30,
	648,	296,		32,	30,
	736,	296,		32,	30, /* bonus */

	/* 69 (94) Level Backgrounds */
	8,		512,	40,	8,
	96,		512,	40,	8,
	184,	512,	40,	8,
	272,	512,	40,	8,
	360,	512,	40,	8,
	448,	512,	40,	8,
	536,	512,	40,	8,
	624,	512,	40,	8,

	/* 77 Blobs (holes after digger) */
	584,	406,		16,	36,
	640,	406,		16,	36,
	732,	406,		44,	12,
	820,	430,		44,	12,
	912,	408,		32,	30,
	1000,	408,		32,	30,

	/* 83/120 Text Font */
	8,		568,	20,	28, /* A */
	40,		568,	20,	28, /* B */
	72,		568,	20,	28, /* C */
	104,	568,	20,	28,	/* D */
	136,	568,	20,	28, /* E */
	168,	568,	20,	28, /* F */
	200,	568,	20,	28, /* G */
	232,	568,	20,	28, /* H */
	264,	568,	20,	28, /* I */
	296,	568,	20,	28, /* J */
	328,	568,	20,	28, /* K */
	360,	568,	20,	28, /* L */
	392,	568,	20,	28, /* M */
	424,	568,	20,	28, /* N */
	456,	568,	20,	28, /* O */
	488,	568,	20,	28, /* P */
	520,	568,	20,	28, /* Q */
	552,	568,	20,	28, /* R */
	584,	568,	20,	28, /* S */
	616,	568,	20,	28, /* T */
	648,	568,	20,	28, /* U */
	680,	568,	20,	28, /* V */
	712,	568,	20,	28, /* W */
	744,	568,	20,	28, /* X */
	776,	568,	20,	28, /* Y */
	808,	568,	20,	28, /* Z */
	840,	568,	20,	28, /* 0 */
	872,	568,	20,	28, /* 1 */
	904,	568,	20,	28, /* 2 */
	936,	568,	20,	28, /* 3 */
	968,	568,	20,	28, /* 4 */
	1000,	568,	20,	28, /* 5 */
	1032,	568,	20,	28, /* 6 */
	8,		600,	20,	34, /* 7 */
	40,		600,	20,	34, /* 8 */
	72,		600,	20,	34, /* 9 */
	104,	600,	20,	34, /* . */
	136,	600,	20,	34, /* : */
	168,	600,	20,	34, /* _ */
	200,	600,	20,	34, /* space */
};
