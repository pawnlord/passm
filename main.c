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

void find_pass(char name[], char data[][50], char val[]) {
	char current_name[50] = {0};
	char name_end = 0;
	char current_pass[50] = {0};
	int finding_name = 1;
	for(int i = 0; strcmp(data[i], "") > 0; i++) {
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
		finding_name = 1;
		name_end = 0;
		for(int j = 0; current_name[j] != 0; j++){
			current_name[j] = 0;
		}
		for(int j = 0; current_pass[j] != 0; j++){
			current_name[j] = 0;
		}
	}
			
	strcpy(val, current_pass);
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
		fputs("HELLO PPP\n", fp);
		fclose(fp);
	}
	
	if(strcmp(command, "get") == 0) {
		if(argc < 3) {
			printf("Which Password? ");
			scanf("%s", pass_name); 
		} else {
			pass_name = argv[2];
		}
		
		char pass_val[50] = {0};
		find_pass(pass_name, pass_names, pass_val);
		printf(pass_val);	
	}
	if(strcmp(command, "set") == 0) {
		if(argc < 3) {
			printf("Set which password? ");
			scanf("%s", pass_name); 
		} else {
			pass_name = argv[2];
		}
		char pass_val[50] = {0};
		if(argc < 4) {
			printf("New password: ");
			scanf("%s", pass_val); 
		} else {
			pass_name = argv[3];
		}
		
		
		FILE* fp = fopen("pass.txt", "a");
		fputs(pass_name, fp);
		
		fputc(' ', fp);
		
		fputs(pass_val, fp);
		
		fputc('\n', fp);
		
		fclose(fp);
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
			printf("Size: %d", size);
			printf("What symbols do you want to use? ");
			scanf("%s", symbols);
		}
		if(argc > 3 && strcmp(argv[3], "-d")) {
			
			
			printf("How long? ");
			scanf("%d", &size);
			printf("Size: %d", size);
			printf("What symbols do you want to use? ");
			scanf("%s", symbols);
		}
		
		FILE* fp = fopen("pass.txt", "a");
		char pass_val[50] = {0};
		fputs(pass_name, fp);
		
		store_pass(pass_val, size);
		fputc(' ', fp);
		
		fputs(pass_val, fp);
		
		fputc('\n', fp);
		
		fclose(fp);
	}
}