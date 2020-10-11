#include "calc.h"

void Product(matrix P,matrix A,matrix B){
	for(int i=0;i<P->n;i++){
		for(int j=0;j<P->m;j++){			
			float ansr=0;			
			for(int l=0;l<3;l++){
				for(int k=0;k<3;k++){
					int ofs= 3*((i+l)*(A->m) + j+k);
					ansr+=  (  *(*A->A +ofs) ) * (*(*B->A +l*3+k));
				}
			}
			*(*P->A +3*(i*(P->m)+j))=ansr;

			float ansg=0;			
			for(int l=0;l<3;l++){
				for(int k=0;k<3;k++){
					int ofs= 3*((i+l)*(A->m) + j+k)+1;
					ansg+=  (  *(*A->A +ofs) ) * (*(*B->A +l*3+k));
				}
			}
			*(*P->A +3*(i*(P->m)+j)+1)=ansg;

			float ansb=0;			
			for(int l=0;l<3;l++){
				for(int k=0;k<3;k++){

					int ofs= 3*((i+l)*(A->m) + j+k)+2;
					ansb+=  (  *(*A->A +ofs) ) * (*(*B->A +l*3+k));
				}
			}
			*(*P->A +3*(i*(P->m)+j)+2)=ansb;
		}
	}
	
}