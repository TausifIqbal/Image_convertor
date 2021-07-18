
#include "calc.h"
PPMImage *blurRGB(PPMImage *img){
	//kernel matrix for original image
	// float num[3][3] = {
	//     	{0, 0,  0},
	//     	{0,  1,  0},
	//     	{0, 0,  0}
	//  	};
	// kernel matrix for edgedetection image	
	// float num[3][3] = {
	//     	{0, -1,  0},
	//     	{-1,  4,  -1},
	//     	{0, -1,  0}
	//  	};	

	// kernel matrix for blur image	
	float num[3][3] = {
	    	{0.0625, 0.125, 0.0625 },
	    	{0.125,  0.25,  0.125},
	    	{0.0625, 0.125,  0.0625}
	 	};	
	float *pb=(float*)malloc(3*3*sizeof(float));
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			*(pb+ i*3 +j )=num[i][j];
		}
	}
	matrix B=(matrix)malloc(sizeof(matrix));
	B->n=3;
	B->m=3;
	B->A=&pb;
	matrix A=(matrix)malloc(sizeof(matrix));
	A->n=img->y; // height
	A->m=img->x; // width
	float *pa=(float*)malloc(3*(A->n)*(A->m)*sizeof(float));
	for(int i=0;i<A->n;i++){
		for(int j=0;j<A->m;j++){
			int ofs= 3*(i*A->m + j);
			for(int l=0;l<3;l++){
				*(pa+ ofs+l )=(float) img->data[ofs+l];
			}
		}
	}
	A->A=&pa;

	matrix P=(matrix)malloc(sizeof(matrix));
	P->n=img->y-2; // reduced height
	P->m=img->x-2; // reduced width
	float *pc=(float*)malloc(3*(P->n)*(P->m)*sizeof(float));
	P->A=&pc;

	Product(P,A,B);

	PPMImage *blurred_image;
	blurred_image = (PPMImage *)malloc(sizeof(PPMImage));
	blurred_image->x =img->x-2;//reduced width
	blurred_image->y =img->y-2;//reduced height
	blurred_image->data = (unsigned char*)malloc(3* blurred_image->x * blurred_image->y * sizeof(unsigned char));
	for(int i=0;i<P->n;i++){
		for(int j=0;j<P->m;j++){
			int ofs= 3*(i*P->m + j);
			for(int l=0;l<3;l++){
				blurred_image->data[ofs+l]=(unsigned char)*(*P->A+ ofs+l );
			}
		}
	}
	return blurred_image;
}
