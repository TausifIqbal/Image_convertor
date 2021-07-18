#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef _CALC_H
#define _CALC_H


#define CREATOR "TAUSIF"
#define RGB_COMPONENT_COLOR 255

typedef struct {
     unsigned char red,green,blue;
} PPMPixel;

typedef struct {
     int x, y;
     unsigned char *data;
} PPMImage;

struct matrix_t{
    int m;
    int n;
    float **A;
};
typedef struct  matrix_t * matrix;

PPMImage *readPPM( char *filename);

void writePPM( char *filename, PPMImage *img);

PPMImage *grayscale(PPMImage *img);

PPMImage *blurRGB(PPMImage *img);

void Product(matrix P, matrix A, matrix B);

#endif
