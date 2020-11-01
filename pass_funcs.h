#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct{
	int min_length;
	int max_length;
	int use_alpha;
	int use_upper;
	int use_nums;
	char* symbols;
} settings;

int get_pass(char* name, char* pass, char** data){
	/* return condition */
	int was_gotten = 0;
	
	/* go through every line, set pass if we have the right name */
	for(int i = 0; strcmp("", data[i]) != 0; i++){
		int j = 0;
		for(; data[i][j] != 0 && data[i][j] != ' '; j++);
		char* temp_name = malloc(200);
		char t = data[i][j];
		
		data[i][j] = 0;
		strcpy(temp_name, data[i]);
		
		
		if(strcmp(temp_name, name) == 0){
			strcpy(pass, data[i]+j+1);
			was_gotten = 1;
		}
		
		data[i][j] = t;
		
		free(temp_name);
	}
	
	return was_gotten;
}
int set_pass(char* name, char* pass, char** data){
	/* return condition */
	int was_gotten = 0;
	
	/* go through every line, set pass if we have the right name */
	for(int i = 0; strcmp("", data[i]) != 0; i++){
		int j = 0;
		for(; data[i][j] != 0 && data[i][j] != ' '; j++);
		char* temp_name = malloc(200);
		char t = data[i][j];
		
		data[i][j] = 0;
		strcpy(temp_name, data[i]);
		
		
		if(strcmp(temp_name, name) == 0){
			strcpy(data[i]+j+1, pass);
			was_gotten = 1;
		}
		
		data[i][j] = t;
		
		free(temp_name);
	}
	
	return was_gotten;
}

int new_pass(char* pass, settings s){
	srand(time(NULL));
	static char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	static char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static char numbers[] = "123457890";
	int len = rand()%(s.max_length-s.min_length)+s.min_length;
	for(int i = 0; i < len; i++){
		char new_c;
		char* usable_set = malloc(200);
		for(int i = 0; i < 200; i++){
			usable_set[i] = 0;
		}
		if(s.use_alpha){
			strcat(usable_set, alphabet);
		}
		if(s.use_upper){
			strcat(usable_set, uppercase);
		}
		if(s.use_nums){
			strcat(usable_set, numbers);
		}
		strcat(usable_set, s.symbols);
		new_c = usable_set[rand()%strlen(usable_set)];
		pass[i] = new_c;
		free(usable_set);
	}
}
int add_pass(char* name, char* pass, char** data){
	int i;
	for(i = 0; strcmp("", data[i]) != 0; i++);
	strcat(data[i], name);
	strcat(data[i], " ");
	strcat(data[i], pass);
}