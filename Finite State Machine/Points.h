/**----------------------------------------------------------------------
// @Define: Points
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Define all the need macro
//----------------------------------------------------------------------**/

#ifndef POINTS_H
#define POINTS_H

//color
#define COLOR_WHITE makecol(255,255,255)
#define COLOR_BLACK makecol(0,0,0)
#define COLOR_RED makecol(255,0,0)
#define COLOR_GRAY makecol(120,120,120)
#define COLOR_BLUE makecol(0,0,255)
#define COLOR_GREEN makecol(0,255,0)
#define COLOR_ORANGE makecol(255,125,0)
#define COLOR_YELLOW makecol(255,255,0)

//State representation
#define STEP 23
#define BARH  20
#define BARW  100

//key coordinates
#define Y16 Y17+STEP
#define Y1  Y17+2*STEP
#define Y2  Y17+3*STEP
#define Y3  Y17+4*STEP
#define Y4  Y17+5*STEP
#define Y5  Y17+6*STEP
#define Y6  Y17+7*STEP
#define Y7  Y17+10*STEP
#define Y8  Y17+12*STEP
#define Y9  Y17+13*STEP
#define Y10 Y17+14*STEP
#define Y11 Y17+15*STEP
#define Y12 Y17+16*STEP
#define Y13 Y17+17*STEP
#define Y14 Y17+18*STEP
#define Y15 Y17+19*STEP
#define Y17  5

#define X2  X1+STEP
#define X3  X1+2*STEP
#define X4  X1+3*STEP
#define X5  X1+7*STEP
#define X6  X1+8*STEP
#define X7  X1+9*STEP
#define X8  X1+13*STEP
#define X9  X1+14*STEP
#define X10  X1+15*STEP
#define X11 X1+16*STEP
#define X1  5

const int tab_x[2][9]={{X10,X10,X10,X6,X2,X2,X6,X6,X6},{X9,X9,X9,X6,X3,X3,X6,X6,X6}};
const int tab_y[2][9]={{Y2,Y7,Y12,Y12,Y12,Y2,Y2,Y14,Y16},{Y3,Y7,Y11,Y11,Y11,Y3,Y3,Y9,Y5}};


//Percentage limit to go refuel/repair
#define PERCENT_FUEL 20
#define PERCENT_REPAIR 20

#endif

