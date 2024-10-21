#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

/*

**********************************************************************************
This is where all of the variables that are got from the `level.txt` file
(like the sectors' colors and walls' coordinates) are stored.

They are here so then I can get these variables whenever and wherever I need them.
**********************************************************************************

*/
typedef struct _sector 
{
    int num_walls;
    int height;
    int elevation;
    unsigned int color;
    unsigned int floor_color;
    unsigned int ceiling_color;
} sector;

typedef struct _sectorAdditionalData
{
    int isPortal;
    int th;
    int bh;
} secAdData;

typedef struct _wall
{
    int ax;
    int ay;
    int bx;
    int by;
} wall;

class Global {
    public:
        int sectorCount;
        secAdData *sectorsAdditionalData;

        sector *sectors;
        int** walls;
        int wallPoints;

        Global() { }
};

#endif