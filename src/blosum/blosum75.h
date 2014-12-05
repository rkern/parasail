/**
 * @author jeff.daily@pnnl.gov
 *
 * Copyright 2012 Pacific Northwest National Laboratory. All rights reserved.
 */
#ifndef _PGRAPH_BLOSUM75_H_
#define _PGRAPH_BLOSUM75_H_

static const int8_t blosum75__[] = {
/*       A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   Z   X   * */
/* A */  4, -2, -2, -2, -1, -1, -1,  0, -2, -2, -2, -1, -1, -3, -1,  1,  0, -3, -2,  0, -2, -1, -1, -5, 
/* R */ -2,  6, -1, -2, -4,  1,  0, -3,  0, -3, -3,  2, -2, -3, -2, -1, -1, -3, -2, -3, -1,  0, -1, -5, 
/* N */ -2, -1,  6,  1, -3,  0, -1, -1,  0, -4, -4,  0, -3, -4, -3,  0,  0, -4, -3, -3,  3,  0, -1, -5, 
/* D */ -2, -2,  1,  6, -4, -1,  1, -2, -1, -4, -4, -1, -4, -4, -2, -1, -1, -5, -4, -4,  4,  1, -2, -5, 
/* C */ -1, -4, -3, -4,  9, -3, -5, -3, -4, -1, -2, -4, -2, -2, -4, -1, -1, -3, -3, -1, -4, -4, -2, -5, 
/* Q */ -1,  1,  0, -1, -3,  6,  2, -2,  1, -3, -3,  1,  0, -4, -2,  0, -1, -2, -2, -2,  0,  3, -1, -5, 
/* E */ -1,  0, -1,  1, -5,  2,  5, -3,  0, -4, -4,  1, -2, -4, -1,  0, -1, -4, -3, -3,  1,  4, -1, -5, 
/* G */  0, -3, -1, -2, -3, -2, -3,  6, -2, -5, -4, -2, -3, -4, -3, -1, -2, -3, -4, -4, -1, -2, -2, -5, 
/* H */ -2,  0,  0, -1, -4,  1,  0, -2,  8, -4, -3, -1, -2, -2, -2, -1, -2, -2,  2, -4, -1,  0, -1, -5, 
/* I */ -2, -3, -4, -4, -1, -3, -4, -5, -4,  4,  1, -3,  1,  0, -3, -3, -1, -3, -2,  3, -4, -4, -2, -5, 
/* L */ -2, -3, -4, -4, -2, -3, -4, -4, -3,  1,  4, -3,  2,  0, -3, -3, -2, -2, -1,  1, -4, -3, -1, -5, 
/* K */ -1,  2,  0, -1, -4,  1,  1, -2, -1, -3, -3,  5, -2, -4, -1,  0, -1, -4, -2, -3, -1,  1, -1, -5, 
/* M */ -1, -2, -3, -4, -2,  0, -2, -3, -2,  1,  2, -2,  6,  0, -3, -2, -1, -2, -2,  1, -3, -2, -1, -5, 
/* F */ -3, -3, -4, -4, -2, -4, -4, -4, -2,  0,  0, -4,  0,  6, -4, -3, -2,  1,  3, -1, -4, -4, -2, -5, 
/* P */ -1, -2, -3, -2, -4, -2, -1, -3, -2, -3, -3, -1, -3, -4,  8, -1, -1, -5, -4, -3, -2, -2, -2, -5, 
/* S */  1, -1,  0, -1, -1,  0,  0, -1, -1, -3, -3,  0, -2, -3, -1,  5,  1, -3, -2, -2,  0,  0, -1, -5, 
/* T */  0, -1,  0, -1, -1, -1, -1, -2, -2, -1, -2, -1, -1, -2, -1,  1,  5, -3, -2,  0, -1, -1, -1, -5, 
/* W */ -3, -3, -4, -5, -3, -2, -4, -3, -2, -3, -2, -4, -2,  1, -5, -3, -3, 11,  2, -3, -5, -3, -3, -5, 
/* Y */ -2, -2, -3, -4, -3, -2, -3, -4,  2, -2, -1, -2, -2,  3, -4, -2, -2,  2,  7, -2, -3, -3, -2, -5, 
/* V */  0, -3, -3, -4, -1, -2, -3, -4, -4,  3,  1, -3,  1, -1, -3, -2,  0, -3, -2,  4, -4, -3, -1, -5, 
/* B */ -2, -1,  3,  4, -4,  0,  1, -1, -1, -4, -4, -1, -3, -4, -2,  0, -1, -5, -3, -4,  4,  0, -2, -5, 
/* Z */ -1,  0,  0,  1, -4,  3,  4, -2,  0, -4, -3,  1, -2, -4, -2,  0, -1, -3, -3, -3,  0,  4, -1, -5, 
/* X */ -1, -1, -1, -2, -2, -1, -1, -2, -1, -2, -1, -1, -1, -2, -2, -1, -1, -3, -2, -1, -2, -1, -1, -5, 
/* * */ -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,  1
};

static const int blosum75[24][24] = {
/*       A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   Z   X   * */
/* A */{ 4, -2, -2, -2, -1, -1, -1,  0, -2, -2, -2, -1, -1, -3, -1,  1,  0, -3, -2,  0, -2, -1, -1, -5}, 
/* R */{-2,  6, -1, -2, -4,  1,  0, -3,  0, -3, -3,  2, -2, -3, -2, -1, -1, -3, -2, -3, -1,  0, -1, -5}, 
/* N */{-2, -1,  6,  1, -3,  0, -1, -1,  0, -4, -4,  0, -3, -4, -3,  0,  0, -4, -3, -3,  3,  0, -1, -5}, 
/* D */{-2, -2,  1,  6, -4, -1,  1, -2, -1, -4, -4, -1, -4, -4, -2, -1, -1, -5, -4, -4,  4,  1, -2, -5}, 
/* C */{-1, -4, -3, -4,  9, -3, -5, -3, -4, -1, -2, -4, -2, -2, -4, -1, -1, -3, -3, -1, -4, -4, -2, -5}, 
/* Q */{-1,  1,  0, -1, -3,  6,  2, -2,  1, -3, -3,  1,  0, -4, -2,  0, -1, -2, -2, -2,  0,  3, -1, -5}, 
/* E */{-1,  0, -1,  1, -5,  2,  5, -3,  0, -4, -4,  1, -2, -4, -1,  0, -1, -4, -3, -3,  1,  4, -1, -5}, 
/* G */{ 0, -3, -1, -2, -3, -2, -3,  6, -2, -5, -4, -2, -3, -4, -3, -1, -2, -3, -4, -4, -1, -2, -2, -5}, 
/* H */{-2,  0,  0, -1, -4,  1,  0, -2,  8, -4, -3, -1, -2, -2, -2, -1, -2, -2,  2, -4, -1,  0, -1, -5}, 
/* I */{-2, -3, -4, -4, -1, -3, -4, -5, -4,  4,  1, -3,  1,  0, -3, -3, -1, -3, -2,  3, -4, -4, -2, -5}, 
/* L */{-2, -3, -4, -4, -2, -3, -4, -4, -3,  1,  4, -3,  2,  0, -3, -3, -2, -2, -1,  1, -4, -3, -1, -5}, 
/* K */{-1,  2,  0, -1, -4,  1,  1, -2, -1, -3, -3,  5, -2, -4, -1,  0, -1, -4, -2, -3, -1,  1, -1, -5}, 
/* M */{-1, -2, -3, -4, -2,  0, -2, -3, -2,  1,  2, -2,  6,  0, -3, -2, -1, -2, -2,  1, -3, -2, -1, -5}, 
/* F */{-3, -3, -4, -4, -2, -4, -4, -4, -2,  0,  0, -4,  0,  6, -4, -3, -2,  1,  3, -1, -4, -4, -2, -5}, 
/* P */{-1, -2, -3, -2, -4, -2, -1, -3, -2, -3, -3, -1, -3, -4,  8, -1, -1, -5, -4, -3, -2, -2, -2, -5}, 
/* S */{ 1, -1,  0, -1, -1,  0,  0, -1, -1, -3, -3,  0, -2, -3, -1,  5,  1, -3, -2, -2,  0,  0, -1, -5}, 
/* T */{ 0, -1,  0, -1, -1, -1, -1, -2, -2, -1, -2, -1, -1, -2, -1,  1,  5, -3, -2,  0, -1, -1, -1, -5}, 
/* W */{-3, -3, -4, -5, -3, -2, -4, -3, -2, -3, -2, -4, -2,  1, -5, -3, -3, 11,  2, -3, -5, -3, -3, -5}, 
/* Y */{-2, -2, -3, -4, -3, -2, -3, -4,  2, -2, -1, -2, -2,  3, -4, -2, -2,  2,  7, -2, -3, -3, -2, -5}, 
/* V */{ 0, -3, -3, -4, -1, -2, -3, -4, -4,  3,  1, -3,  1, -1, -3, -2,  0, -3, -2,  4, -4, -3, -1, -5}, 
/* B */{-2, -1,  3,  4, -4,  0,  1, -1, -1, -4, -4, -1, -3, -4, -2,  0, -1, -5, -3, -4,  4,  0, -2, -5}, 
/* Z */{-1,  0,  0,  1, -4,  3,  4, -2,  0, -4, -3,  1, -2, -4, -2,  0, -1, -3, -3, -3,  0,  4, -1, -5}, 
/* X */{-1, -1, -1, -2, -2, -1, -1, -2, -1, -2, -1, -1, -1, -2, -2, -1, -1, -3, -2, -1, -2, -1, -1, -5}, 
/* * */{-5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,  1}
};

/*                                     A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   Z   X   * */
static const int b75_01[24] = /* A */{ 4, -2, -2, -2, -1, -1, -1,  0, -2, -2, -2, -1, -1, -3, -1,  1,  0, -3, -2,  0, -2, -1, -1, -5}; 
static const int b75_02[24] = /* R */{-2,  6, -1, -2, -4,  1,  0, -3,  0, -3, -3,  2, -2, -3, -2, -1, -1, -3, -2, -3, -1,  0, -1, -5}; 
static const int b75_03[24] = /* N */{-2, -1,  6,  1, -3,  0, -1, -1,  0, -4, -4,  0, -3, -4, -3,  0,  0, -4, -3, -3,  3,  0, -1, -5}; 
static const int b75_04[24] = /* D */{-2, -2,  1,  6, -4, -1,  1, -2, -1, -4, -4, -1, -4, -4, -2, -1, -1, -5, -4, -4,  4,  1, -2, -5}; 
static const int b75_05[24] = /* C */{-1, -4, -3, -4,  9, -3, -5, -3, -4, -1, -2, -4, -2, -2, -4, -1, -1, -3, -3, -1, -4, -4, -2, -5}; 
static const int b75_06[24] = /* Q */{-1,  1,  0, -1, -3,  6,  2, -2,  1, -3, -3,  1,  0, -4, -2,  0, -1, -2, -2, -2,  0,  3, -1, -5}; 
static const int b75_07[24] = /* E */{-1,  0, -1,  1, -5,  2,  5, -3,  0, -4, -4,  1, -2, -4, -1,  0, -1, -4, -3, -3,  1,  4, -1, -5}; 
static const int b75_08[24] = /* G */{ 0, -3, -1, -2, -3, -2, -3,  6, -2, -5, -4, -2, -3, -4, -3, -1, -2, -3, -4, -4, -1, -2, -2, -5}; 
static const int b75_09[24] = /* H */{-2,  0,  0, -1, -4,  1,  0, -2,  8, -4, -3, -1, -2, -2, -2, -1, -2, -2,  2, -4, -1,  0, -1, -5}; 
static const int b75_10[24] = /* I */{-2, -3, -4, -4, -1, -3, -4, -5, -4,  4,  1, -3,  1,  0, -3, -3, -1, -3, -2,  3, -4, -4, -2, -5}; 
static const int b75_11[24] = /* L */{-2, -3, -4, -4, -2, -3, -4, -4, -3,  1,  4, -3,  2,  0, -3, -3, -2, -2, -1,  1, -4, -3, -1, -5}; 
static const int b75_12[24] = /* K */{-1,  2,  0, -1, -4,  1,  1, -2, -1, -3, -3,  5, -2, -4, -1,  0, -1, -4, -2, -3, -1,  1, -1, -5}; 
static const int b75_13[24] = /* M */{-1, -2, -3, -4, -2,  0, -2, -3, -2,  1,  2, -2,  6,  0, -3, -2, -1, -2, -2,  1, -3, -2, -1, -5}; 
static const int b75_14[24] = /* F */{-3, -3, -4, -4, -2, -4, -4, -4, -2,  0,  0, -4,  0,  6, -4, -3, -2,  1,  3, -1, -4, -4, -2, -5}; 
static const int b75_15[24] = /* P */{-1, -2, -3, -2, -4, -2, -1, -3, -2, -3, -3, -1, -3, -4,  8, -1, -1, -5, -4, -3, -2, -2, -2, -5}; 
static const int b75_16[24] = /* S */{ 1, -1,  0, -1, -1,  0,  0, -1, -1, -3, -3,  0, -2, -3, -1,  5,  1, -3, -2, -2,  0,  0, -1, -5}; 
static const int b75_17[24] = /* T */{ 0, -1,  0, -1, -1, -1, -1, -2, -2, -1, -2, -1, -1, -2, -1,  1,  5, -3, -2,  0, -1, -1, -1, -5}; 
static const int b75_18[24] = /* W */{-3, -3, -4, -5, -3, -2, -4, -3, -2, -3, -2, -4, -2,  1, -5, -3, -3, 11,  2, -3, -5, -3, -3, -5}; 
static const int b75_19[24] = /* Y */{-2, -2, -3, -4, -3, -2, -3, -4,  2, -2, -1, -2, -2,  3, -4, -2, -2,  2,  7, -2, -3, -3, -2, -5}; 
static const int b75_20[24] = /* V */{ 0, -3, -3, -4, -1, -2, -3, -4, -4,  3,  1, -3,  1, -1, -3, -2,  0, -3, -2,  4, -4, -3, -1, -5}; 
static const int b75_21[24] = /* B */{-2, -1,  3,  4, -4,  0,  1, -1, -1, -4, -4, -1, -3, -4, -2,  0, -1, -5, -3, -4,  4,  0, -2, -5}; 
static const int b75_22[24] = /* Z */{-1,  0,  0,  1, -4,  3,  4, -2,  0, -4, -3,  1, -2, -4, -2,  0, -1, -3, -3, -3,  0,  4, -1, -5}; 
static const int b75_23[24] = /* X */{-1, -1, -1, -2, -2, -1, -1, -2, -1, -2, -1, -1, -1, -2, -2, -1, -1, -3, -2, -1, -2, -1, -1, -5}; 
static const int b75_24[24] = /* * */{-5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,  1};
static const int * const restrict blosum75_[24] = {
b75_01,
b75_02,
b75_03,
b75_04,
b75_05,
b75_06,
b75_07,
b75_08,
b75_09,
b75_10,
b75_11,
b75_12,
b75_13,
b75_14,
b75_15,
b75_16,
b75_17,
b75_18,
b75_19,
b75_20,
b75_21,
b75_22,
b75_23,
b75_24
};

#endif /* _PGRAPH_BLOSUM75_H_ */
