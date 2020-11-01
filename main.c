#include <stdio.h>
#include <stdlib.h>
#include "pass_funcs.h"
#include <string.h>
#define STRING(x) char* x = malloc(200)


int read_data(char** data, char* filename) {
	FILE* fp = fopen(filename, "r");
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


int write_data(char** data, char* filename) {
	FILE* fp = fopen(filename, "w");
	for(int i = 0; strcmp("", data[i]) != 0; i++){
		fputs(data[i], fp);
		fputs("\n", fp);
	}
	fclose(fp);
}


int main(int argc, char** argv){
	/* set up data */
	char** data = malloc(sizeof(char**) * 200); // TODO: change this to be flexible
	for(int i = 0; i < 200; i++){
		data[i] = malloc(sizeof(char*) * 400);
		strcpy(data[i], "");
	}
	
	/* get command */
	STRING(command);
	if(argc < 2){
		printf("no command, exiting. type -h or --help for help\n");
		return 1;
	}
	strcpy(command, argv[1]);
	
	/* parse command*/
	if(strcmp(command, "-h") == 0 || strcmp(command, "--help") == 0){
		/* print help message */
		printf("Welcome to passm, a cli for password storage. This is not overly serious, and should not be taken as such.\nCommands:\n  -h/--help: Get help on all commands.");
	} else if(strcmp(command, "get") == 0){
		/* get name of password */
		if(argc < 3){
			printf("I need a name!\n");
			return 1;
		}
		
		/* get data*/
		read_data(data, "pass.txt");
		
		/* get the password and print it out */
		STRING(pass);
		if(!get_pass(argv[2], pass, data)){
			printf("no such password!\n");
			return 0;
		}
		printf("%s\n", pass);
	} else if(strcmp(command, "set") == 0){
		/* get name of password */
		if(argc < 4){
			printf("I need a name and a new password!\n");
			return 1;
		}
		STRING(name);
		STRING(pass);
		strcpy(name, argv[2]);
		strcpy(pass, argv[3]);
		
		read_data(data, "pass.txt");
		
		if(!set_pass(name, pass, data)){
			printf("no such password!\n");
			return 1;
		}
		write_data(data, "pass.txt");
	} else if(strcmp(command, "add") == 0){
		/* get name of password */
		if(argc < 3){
			printf("I need a name\n");
			return 1;
		}
		STRING(name);
		strcpy(name, argv[2]);
		STRING(pass);
		settings s;
		s.min_length = 8;
		s.max_length = 20;
		s.use_upper = 1;
		s.use_alpha = 1;
		s.use_nums = 1;
		s.symbols = malloc(strlen("!@#$%^&*(()|\\:;,.<>/?"));
		strcpy(s.symbols, "!@#$%^&*(()|\\:;,.<>/?");
		read_data(data, "pass.txt");
		
		if(!new_pass(pass, s)){
			printf("no such password!\n");
			return 1;
		}
		add_pass(name, pass, data);
		write_data(data, "pass.txt");
	}
}