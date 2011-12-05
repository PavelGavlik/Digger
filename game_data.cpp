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
	/* Red digger - loaded */
	32,		16,		32,	30, /* right */
	120,	16,		32,	30,
	208,	16,		32,	30,
	296,	16,		32,	30, /* left */
	384,	16,		32,	30,
	472,	16,		32,	30,

	560,	16,		32,	30, /* up */
	648,	16,		32,	30,
	736,	16,		32,	30,
	824,	16,		32,	30, /* down */
	912,	16,		32,	30,
	1000,	16,		32,	30,

	/* Red digger - unloaded */
	32,		72,		32,	30, /* right */
	120,	72,		32,	30,
	208,	72,		32,	30,
	296,	72,		32,	30, /* left */
	384,	72,		32,	30,
	472,	72,		32,	30,

	560,	72,		32,	30, /* up */
	648,	72,		32,	30,
	736,	72,		32,	30,
	824,	72,		32,	30, /* down */
	912,	72,		32,	30,
	1000,	72,		32,	30,

	/* Green digger - loaded */
	32,		128,		32,	30, /* right */
	120,	128,		32,	30,
	208,	128,		32,	30,
	296,	128,		32,	30, /* left */
	384,	128,		32,	30,
	472,	128,		32,	30,

	560,	128,		32,	30, /* up */
	648,	128,		32,	30,
	736,	128,		32,	30,
	824,	128,		32,	30, /* down */
	912,	128,		32,	30,
	1000,	128,		32,	30,

	/* Green digger - unloaded */
	32,		184,		32,	30, /* right */
	120,	184,		32,	30,
	208,	184,		32,	30,
	296,	184,		32,	30, /* left */
	384,	184,		32,	30,
	472,	184,		32,	30,

	560,	184,		32,	30, /* up */
	648,	184,		32,	30,
	736,	184,		32,	30,
	824,	184,		32,	30, /* down */
	912,	184,		32,	30,
	1000,	184,		32,	30,

	/* Monsters */
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

	/* Various */
	32,		296,		32,	30, /* emerald */
	120,	296,		32,	30, /* bags */
	208,	296,		32,	30,
	296,	296,		32,	30,
	384,	296,		32,	30,
	472,	296,		32,	30, /* coins */

	560,	296,		32,	30,
	648,	296,		32,	30,
	736,	296,		32,	30, /* bonus */

	/* Level Backgrounds */
	8,		512,	40,	8,
	96,		512,	40,	8,
	184,	512,	40,	8,
	272,	512,	40,	8,
	360,	512,	40,	8,
	448,	512,	40,	8,
	536,	512,	40,	8,
	624,	512,	40,	8,
};
