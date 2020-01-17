#include <stdio.h>
#include <malloc.h>

//This is a function that takes a 
//		char func(char, char)
//	and a
//		char n
//	as parameters and returns a
//		char func_c(char)
char (*curry(char (*func)(char,char), char n))(char){
	//Allocate a byte buffer to store the assembly code
	char* newFunction = malloc(11);

	//Insert the instructions
	newFunction[0] = 0x58;				//pop eax
	newFunction[1] = 0x6a;				//push
	newFunction[2] = n;					//n
	newFunction[3] = 0x50;				//push eax
	newFunction[4] = 0xb8;				//mov eax,
	
	//The address for the jump has to be stored in the reverse order
	long funcAddr = (long) func;
	newFunction[8] = (funcAddr >> 24) & 0xFF;
	newFunction[7] = (funcAddr >> 16) & 0xFF;
	newFunction[6] = (funcAddr >> 8) & 0xFF;
	newFunction[5] = funcAddr & 0xFF;

	newFunction[9] = 0xff;				//jmp
	newFunction[10] = 0xe0;				//eax
	
	//Cast the array to a function pointer and return it
	return (char (*)(char))newFunction;
}

//Test function
char add(char a, char b){
	return a+b;
}

int main(){
	char a = 42;
	char b = 88;
	
	//Pass the first parameter and get the curried function
	char (*addA)(char) = curry(add, a);
	
	//Use the curried function and print the result
	printf("%d+%d=%d\n", a, b, addA(b));
	return 0;
}
