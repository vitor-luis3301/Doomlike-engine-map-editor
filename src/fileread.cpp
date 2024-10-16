#include "fileread.h"

FILE *fp;

char *strremove(char *str, const char *sub)
{
    char *p, *q, *r;
    if (*sub && (q = r = strstr(str, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            while (p < r)
                *q++ = *p++;
        }
        while ((*q++ = *p++) != '\0')
            continue;
    }
    return str;
}

int fileRead::init(char *filepath, char *filename)
{
    char *file = strcat(strremove(filepath, "main.exe"), "/data/");
    file = strcat(file, filename);
    
    fp = fopen(file, "r");

    if (fp == NULL)
    {
        printf("Error: Could not open file %s. Make sure it's in there you dumb fucking cretin!", filename);
        return 1;
    }

    return 0;
}

Global fileRead::interpret()
{
    Global global;

    char sectorCountData[20];

    fgets(sectorCountData, 20, fp);
    
    if (strstr(sectorCountData, "# SECTOR COUNT: "))
        strremove(sectorCountData, "# SECTOR COUNT: ");

    int sectorCount = atoi(sectorCountData);
    global.sectorCount = sectorCount;

    char sectorData[100];
    
    sector sectors[sectorCount];
    secAdData sectorsAdditionalData[sectorCount];

    int numSector = 0;

    while(fgets(sectorData, 100, fp))
    {
        if (0==strcmp(sectorData, "[WALLS]\n"))
            break;
        else if (0!=strcmp(sectorData, "[SECTORS]\n"))
        {
            int nums[9];
            unsigned int colors[3];

            char *token;

            int i = 0;

            token = strtok(sectorData, ",");

            while (token != NULL)
            {
                if (strstr(token, "0x"))
                    sscanf(token, "%x", &colors[i-2]);
                else
                    nums[i] = atoi(token);
                i++;
                token = strtok(NULL, ",");
            }
            //printf("%d: [%d, %d, %u, %u, %u, %s, %d, %d, %d]\n", numSector, nums[0], nums[1], colors[0], colors[1], colors[2], nums[5] ? "true" : "false", nums[6], nums[7], nums[8]);
            sectors[numSector].height = nums[0];
            sectors[numSector].elevation = nums[1];
            sectors[numSector].color = colors[0];
            sectors[numSector].ceiling_color = colors[1];
            sectors[numSector].floor_color = colors[2];
            sectors[numSector].num_walls = nums[8];
            
            sectorsAdditionalData[numSector].isPortal = nums[5];
            sectorsAdditionalData[numSector].th = nums[6];
            sectorsAdditionalData[numSector].bh = nums[7];

            numSector++;
        }
    }
    char wall_vertices[100];
    int wallCoords[sectorCount][sectorCount*4];

    int wallNum = 0;
    int secNum = -1;

    while(fgets(wall_vertices, 100, fp))
    {
        if (strstr(wall_vertices, "# SECTOR: "))
        {
            secNum++; wallNum = 0;
            strremove(wall_vertices, "# SECTOR: ");
        }

        char *token;

        token = strtok(wall_vertices, ",");

        while( token != NULL ) 
        {
            wallCoords[secNum][wallNum] = atoi(token);
            wallNum++;
            token = strtok(NULL, ",");
        }
    }   

    fclose(fp);


    global.sectors = sectors;
    global.sectorsAdditionalData = sectorsAdditionalData;

    global.walls = new int*[sectorCount];

    for (int i = 0; i < sectorCount; i++)
        global.walls[i] = new int[sectorCount*4];
    

    for (int i = 0; i < sectorCount; i++)
        for (int j = 0; j < sectorCount*4; j++)
            global.walls[i][j] = wallCoords[i][j];
    
    return global;
}