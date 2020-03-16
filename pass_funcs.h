#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
char symbols[] = { '>', '<', '!', '@', '#', '$', '%', '^', '&', '*', '/', '?', '_', '+', '-', '=', '\0'};
char numbers[] = {'1', '2', '3', '4' , '5', '6', '7', '8', '9', '0'};
char alphabet[100] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
int hasNum, hasSym , hasLet;
int aCM;
int checks = 16;
int alpha_size = 52;

int len(char str[]) {
	int i;
	for(i = 0; str[i]!=0; i++) {
		
	}
	return i;
}

void def()
{
	hasNum = 0;
	hasSym = 0;
	hasLet = 0;
	aCM = 0;
	strcat(alphabet, numbers);
	strcat(alphabet, symbols);
	checks = fmax(10, len(symbols));
	alpha_size = len(symbols) + 10 + 52;
}


void store_pass(char pass[], int size){
	srand(time(NULL));
	def();
	while(!hasLet || !hasNum || !hasSym){
		strcpy(pass, "");
		for(int i = 0; i < size;i++)
		{
			pass[i] = alphabet[rand() % alpha_size];
		}
		for(int j = 0; j < checks;j++){
			for(int i = 0; i < size;i++)
			{
				if(pass[i] == symbols[j]) hasSym = 1;
				else if(j <= 10 && pass[i] == numbers[j])
				{
					hasNum = 1;
				}
				else
				{
					hasLet = 1;
				}
			}
		}

	}
}

