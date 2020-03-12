#include <stdio.h>
#include <stdlib.h>
#include "pass_funcs.h"


int read_data(char data[][50], char dataname[]) {
	FILE* fp = fopen(dataname, "r+");
	char c;
	int itter = 0;
	int data_section = 0;
	while((c = fgetc(fp)) != EOF) {
		if(c == '\n' || c == 0) {
			data_section++;
			itter = 0;
		}
		else {
			data[data_section][itter] = c;
			itter++;
		}
	}
	fclose(fp);
}

int find_pass(char name[], char data[][50], char val[]) {
	char current_name[50] = {0};
	char name_end = 0;
	char current_pass[50] = {0};
	int finding_name = 1;
	for(int i = 0; strcmp(data[i], "") > 0; i++) {
		finding_name = 1;
		name_end = 0;
		for(int j = 0; current_name[j] != 0; j++){
			current_name[j] = 0;
		}
		for(int j = 0; current_pass[j] != 0; j++){
			current_pass[j] = 0;
		}
		for(int currc = 0; data[i][currc] != 0; currc++) {
			if(data[i][currc] == ' ') {
				if(strcmp(current_name, name) == 0){
					finding_name = 0;
					name_end = currc+1;
				}
			}
			else if(finding_name) {
				current_name[currc] = data[i][currc];
			}
			else {
				current_pass[currc-name_end] = data[i][currc];
			}
		}
	}
	if(strcmp(current_pass, "") == 0) { 
		return 1;
	}		
	strcpy(val, current_pass);
	return 0;
} 

int get_defaults(int* size, char* syms) {
	char data[50][50] = {""};
	read_data(data, "config.cfg");
	*size = atoi(data[0]);
	strcpy(syms, data[1]);
}
int set_defaults(int size, char* syms) {
	FILE* fp = fopen("config.cfg", "w");
	char* sizestr = malloc(50);
	sprintf(sizestr, "%d", size);
	printf("%s = %d", sizestr, size);
	fputs(sizestr, fp);
	fputc('\n', fp);
	fputs(syms, fp);
}


int main(int argc, char *argv[]){
	char* command = malloc(50);
	char* pass_name = malloc(50);
	char  pass_names[50][50] = {""};
	read_data(pass_names, "pass.txt");
	
	//printf("%s\n", pass_names[0]);
	if(argc < 2) {
		printf("Command? ");
		scanf("%s", command);
	} else {
		command = argv[1];
	}
	
	if(strcmp(command, "init") == 0) {
		FILE* fp = fopen("pass.txt", "w");
		fclose(fp);
		set_defaults(20, "><!@#$%^&*/?_+-=");
	}
	
	if(strcmp(command, "get") == 0) {
		if(argc < 3) {
			printf("Which Password? ");
			scanf("%s", pass_name); 
		} else {
			pass_name = argv[2];
		}
		
		char pass_val[50] = {0};
		int ret = find_pass(pass_name, pass_names, pass_val);
		if(ret == 1) {
			printf("You don't have that password!");
		}
		printf(pass_val);	
	}
	if(strcmp(command, "set") == 0) {
		if(argc < 3) {
			printf("Set which password? ");
			scanf("%s", pass_name); 
		} else {
			pass_name = argv[2];
		}
		char* pass_val = malloc(50);
		if(argc < 4) {
			printf("New password: ");
			scanf("%s", pass_val); 
		} else {
			pass_val = argv[3];
		}
		
		
		FILE* fp = fopen("pass.txt", "a");
		fputs(pass_name, fp);
		
		fputc(' ', fp);
		
		fputs(pass_val, fp);
		
		fputc('\n', fp);
		
		fclose(fp);
	}
	if(strcmp(command, "setpd") == 0) {
		int   size = 0;
		char* syms = malloc(50);
		if(argc < 3) {
			scanf("%d", &size);
			//printf("Size: %d", size); 
		} else {
			size = atoi(argv[2]);
		}
		printf("Symbols: ");
		scanf("%s", syms); 
		
		set_defaults(size, syms);
	}
	if(strcmp(command, "add") == 0) {
		if(argc < 3) {
			printf("Name the new password: ");
			scanf("%s", pass_name); 
		} else {
			pass_name = argv[2];
		}
		int size = 20;
		if(argc < 4) {
			
			
			printf("How long? ");
			scanf("%d", &size);
			printf("What symbols do you want to use? ");
			scanf("%s", symbols);
		}
		else if(argc > 3 && strcmp(argv[3], "-d") && strcmp(argv[3], "-pd")) {
			
			
			printf("How long? ");
			scanf("%d", &size);
			printf("What symbols do you want to use? ");
			scanf("%s", symbols);
		}
		else if(strcmp(argv[3], "-pd") == 0) {
			for(int i = 0; symbols[i] != 0; i++) {
				symbols[i] = 0;
			}
			get_defaults(&size, symbols);
		}
		printf("%d, %s\n", size, symbols);
		
		FILE* fp = fopen("pass.txt", "a");
		char pass_val[50] = {0};
		fputs(pass_name, fp);
		printf("%d, %s\n", size, symbols);
		
		store_pass(pass_val, size);
		fputc(' ', fp);
		
		fputs(pass_val, fp);
		
		fputc('\n', fp);
		
		fclose(fp);
	}
}