#include <stdio.h>

//Write a C Program that receives as command line argument the name of a file, and reverses the order of the bytes in the file.

int main(int argc, char *argv[]) {
	FILE *f;
	long size, i;
	char a, b;
	
	if(argc != 2) {
		printf("Usage: %s filename\n", argv[0]);
		return 1;  
	}
	
	f = fopen(argv[1], "r+b");
	if(!f){
		printf("cannot open file\n");
		return 1;
	}
	
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	
	for(i = 0; i< size/2; i++){
		fseek(f, i, SEEK_SET);
		fread(&a, 1, 1, f);
		
		fseek(f, size -1 -i, SEEK_SET);
		fread(&b, 1, 1, f);
		
		fseek(f, i, SEEK_SET);
		fwrite(&b, 1, 1, f);
		
		fseek(f, size -1 -i, SEEK_SET);
		fwrite(&a, 1, 1, f);
		
	}

}
