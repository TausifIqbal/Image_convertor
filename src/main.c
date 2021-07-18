
#include "calc.h"

int main(){
    PPMImage *image,*image1,*image2;
    char name[50];
    char name_out[50];
    int select=0;
    printf("Enter the image name in ppm  format  present in input folder\n");
    scanf("%s",name);
    char src[]="./input/";
    strcat(src,name);
    image = readPPM(src);
    printf("Enter the output image name in ppm format  file (can be seen in output folder) \n");
    scanf("%s",name_out);
    printf("Select 1 to convert to grayscale\n");
    printf("Select 2 to convert to blur\n");
    printf("Select 3 to convert to grayscale and blur\n");
    scanf("%d",&select);
    
    char dest[]="./output/";
    strcat(dest,name_out);
    if(select==1){
    	image1 = grayscale(image);
    	writePPM(dest,image1);
    }
    else if(select==2){
    	PPMImage *blur = image;
        for(int i=0;i<5;i++){
            image2=blurRGB(blur);
            blur=image2;
        }
    	writePPM(dest,image2);
    }
    else if(select == 3){
    	image1 = grayscale(image);
        PPMImage *blur = image1;
        for(int i=0;i<5;i++){
            image2=blurRGB(blur);
            blur=image2;
        }
    	writePPM(dest,image2);
    }
    else{
    	printf("Please enter valid number\n");
    }
}
