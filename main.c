
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int calcParity(int *vec, int index, int max);
int *loadInput(int *in, int *max);

int main(){
	int x, y=0, z=0, p=0, d, w=0;
	int *input = NULL;
	int *output = NULL;
    input = loadInput(input, &d);

	// 2^p >= p + d + 1;
	while(!((int)pow((double) 2, (double) p)>=(d+p+1))){
		p++;
	}
	output = (int*) realloc(output, sizeof(int)*(p+d));

	for(x=0; x<(p+d); x++){
		if((x+1)==( (int) pow( (double) 2, (double) z))){
			output[x] = 0;
			z++;
		}else{
			output[x] = input[y];
			y++;
		}
	}

	z=0;
	for(x=0; x<(p+d); x++){
		y = ( (int) pow( (double) 2, (double) z));
		if((x+1)==y){
			output[x] = calcParity(output, y, (p+d));
			z++;
			printf("\n %d) *P%d = %d\n", x+1, z, output[x]);
		}else{
			w++;
			printf("\n %d)           D%d = %d\n", x+1, w, output[x]);
		}
	}

	free(output);
	free(input);
	output = NULL;
	input = NULL;
    system("pause");
    return 0;
}

int calcParity(int *vec, int index, int max){
	int ret=0, x;

	for(x=index+1; x<=max; x++){
		if(index&x){
			ret = ret ^ vec[x-1];
		}
	}

	return ret;
}

int *loadInput(int *in, int *max){
	char tmp[0xFF];
	int n = 0, x;

	printf("\n Ingrese un n\xA3mero binario: ");
	gets(tmp);
	fflush(stdin);
	n = (int) strlen(tmp);
	in = (int*) realloc(in, sizeof(int)*n);

    for(x=0; x<n; x++){
		if(tmp[x]==48 || tmp[x]==49){
			in[x] = (int) tmp[x]-48;
		}else{
			in[x] = 0;
		}
    }

	(*max) = n;

	return in;
}
