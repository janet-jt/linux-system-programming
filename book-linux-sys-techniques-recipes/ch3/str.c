#include <stdio.h>

int main(int argc, char* argv[]){
	//char a[] = "hello";
	char a[10] = "hello";
	char *s;
	s = "hello hello hello hello helllo";

	printf("a %ld\n", sizeof(a));
	printf("s %ld\n", sizeof(s));
	printf("%p\n", s);
	printf("%p\n", a);
	printf("%p\n", &s);

	return 0;
}
