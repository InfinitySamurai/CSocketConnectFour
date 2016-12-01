#include <stdio.h>


int main(){
	FILE *fp;
	fp = fopen("test.txt", "w");
	fprintf(fp, "Writing to this file\n");
	close(fp);
	return 0;




}
