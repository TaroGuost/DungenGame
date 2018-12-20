# ifndef RLFILE_H
# define RLFILE_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>


void WriteFile(int size, int playerloco[2] ,  point Base[21][80],  room *r , char *fname);

void loadFile( point p[21][80],  room *r , int *size , char *fname ,int PlayLocation[2]);

void ConvertToEndian(uint32_t *i);

void ConvertToHost(uint32_t *i);

void hardnessMerge( point p[21][80] , uint8_t hardness[1680]);

#endif
