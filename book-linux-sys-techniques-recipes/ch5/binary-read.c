#include <stdio.h>

int main(void){
	FILE *fp;
	float x[2];

	if( (fp = fopen("my-binary-file", "rb")) == 0 ){
		fprintf(stderr, "Cannot open the file");
		return 1;
	}

	fread(&x, sizeof(float), sizeof(x)/sizeof(float), fp);
	printf("size of float: %ld, size of x: %ld, no of items: %ld\n", sizeof(float), sizeof(x), sizeof(x)/sizeof(float));
	printf("%f %f\n", x[0], x[1]);
	return 0;
}
