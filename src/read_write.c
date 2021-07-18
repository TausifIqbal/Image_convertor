#include "calc.h"

void writePPM( char *filename, PPMImage *img){
    FILE *fp;
    fp = fopen(filename, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", filename);
         exit(1);
    }
    fprintf(fp, "P6\n");
    fprintf(fp, "# Created by %s\n",CREATOR);
    fprintf(fp, "%d %d\n",img->x,img->y);
    fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);
    fwrite(img->data, 3*img->x*sizeof(unsigned char), img->y, fp);
    fclose(fp);
}

PPMImage *readPPM( char *filename){
   // char path[]="./input/";
    //strcat(path,filename);
     char buff[16];
     PPMImage *img;
     FILE *fp;
     int c, rgb_comp_color;
     fp = fopen(filename, "rb");
     if (!fp) {
          fprintf(stderr, "Unable to open file '%s'\n",filename);
          exit(1);
     }
     if (!fgets(buff, sizeof(buff), fp)) {  
          perror(filename);
          exit(1);
     }
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Image format is not P6\n");
         exit(1);
    }
    img = (PPMImage *)malloc(sizeof(PPMImage));
    if (!img) {
         fprintf(stderr, "unable to allocate memory\n");
         exit(1);
    }
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }
    ungetc(c, fp);
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }
    if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    img->data = (unsigned char*)malloc(3*img->x * img->y * sizeof(unsigned char));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }
    if (fread(img->data, 3*img->x*sizeof(unsigned char), img->y, fp) != img->y) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }
    fclose(fp);
    return img;
}
