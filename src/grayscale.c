#include "calc.h"

PPMImage *grayscale(PPMImage *img){
	PPMImage * gray;
    gray=malloc(sizeof(PPMImage));
    gray->x=img->x; gray->y=img->y;
    gray->data=(unsigned char *)malloc(3*img->x * img->y * sizeof(unsigned char));
    unsigned int x,y;
    double rc,gc,bc,l;
    unsigned int ofs;
    for(y=0; y < img->y; y++){
        for(x=0; x < img->x; x++){
            ofs = (y * img->x) + x;
            rc = (double) img->data[3*ofs+0];
            gc = (double) img->data[3*ofs+1];
            bc = (double) img->data[3*ofs+2];
            l = 0.2126*rc + 0.7152*gc + 0.0722*bc;
            //need to convert into grayscale image format
            // l=(rc+gc+bc)/3;
            gray->data[3*ofs]= (unsigned char) (l+0.5);
            gray->data[3*ofs+1]= (unsigned char) (l+0.5);
            gray->data[3*ofs+2]= (unsigned char) (l+0.5);
        }
    }
    return gray;

}
