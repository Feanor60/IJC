/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 1
 * @23.4.2020
 * @gcc 9.3.1
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#define MAX_LINE_LEN 1023
FILE *global_file_ptr; //global file pointer for closing when error occurs

//reads from file pointed to by fp, and prints number of lines, according to the option '-n'
int read_from_file(FILE *fp, int read_from_top, int print_lines);

//if option '-n' is set this function takes its argument and decidec if its valid (if its number), and returns error or number
int get_digit(char *str);

//closes the file at exit, so it wont stay open if error occurs
void do_at_exit();

int main (int argc, char **argv)
{	
	atexit(do_at_exit);//closes file if error occured during runtime

	if(argc > 4){
		fprintf(stderr,"invalid number of arguments: %d\n", argc);
		return 1;
	}

	int nflag = 0;
  	int index;
  	int c;

	char *option;

  	opterr = 0; //getopt deosnt return zero, handled by '?' option

  	while ((c = getopt (argc, argv, "n:")) != -1){
    	switch (c){
      	  case 'n':
        	nflag = 1;
			option = optarg;
        	break;

    	  case '?':
        	if (optopt == 'n')
          		fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        	else if (isprint (optopt))
          		fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        	else
          		fprintf (stderr, "Unknown option character `\\x%x'.\n",optopt);
        	return 1;

      	  default:
        	break;
    	}
  	}
	
	int read_from_top = 0;
	int print_lines = 0;
	
	if(nflag == 1){

		if(option[0] == '+')
			read_from_top = 1;

		print_lines = get_digit(option);
		if(print_lines == -1){
			return 1;
		}
		
	}else{
		print_lines = 10;
	}	

  	index = optind;


	FILE *fp = NULL;

	if(argc > 1){
   		fp = fopen((argv[index]),"r");
		global_file_ptr = fp; //copy local pointer to global pointer
		if(fp == NULL){
			fprintf(stderr,"tail: cannot open '%s' for reading: No such file or directory\n", argv[index]);
		}
	}


			
	if(fp != NULL){

		if(read_from_file(fp, read_from_top, print_lines) != 0){
			return 1;
		}
		return 0;
	}

	if((nflag == 0 && argc == 1) || (nflag == 1 && argc == 3)){

		fp = stdin;
		
		if(read_from_file(fp, read_from_top, print_lines) != 0){
			return 1;
		}

		return 0;
	}
	


  return 0;
}


int read_from_file(FILE *fp, int read_from_top, int print_lines){


	char c;
	int rows;
	int chars_printed;
	int beyond_limit = 0;
	int error_msg = 0;
	int print_lines_inc = print_lines + 1;

	if(read_from_top){ //if '+' for option '-n' is set
		print_lines--;
		while((c = fgetc(fp)) != EOF){
			

			if(rows >= print_lines){
				if(chars_printed >= MAX_LINE_LEN && !error_msg){
					fprintf(stderr,"Error: line too long\n");
					error_msg++;
				}else if (chars_printed <= MAX_LINE_LEN)
				{
					putchar(c);
				}else{
					if(beyond_limit == 0){
						beyond_limit = 1;//if going through chars beyond implementation limit
					}
				}			
			}


			if(chars_printed == MAX_LINE_LEN && beyond_limit){
				printf("\n");
			}

			if(c == '\n'){
				rows++;
				chars_printed = 0;
			}else{
				chars_printed++;
			}

		}
	}else{// if '+' isnt set for option '-n'
		int line = 0;
		int error_line = -1;
		int current_buffer_arr = 0;
		char buffer[print_lines_inc][MAX_LINE_LEN];

		for(int i = 0; i<print_lines_inc; i++){
			strcpy(buffer[i],"");

		}

		
		while(fgets(buffer[current_buffer_arr], MAX_LINE_LEN, fp) != 0){ //store n + 1 last lines

			line++;
		

			if(buffer[current_buffer_arr][strlen(buffer[current_buffer_arr])-1] != '\n' && !error_msg){
				error_line = line;
				error_msg++;
			}
			
			if(buffer[current_buffer_arr][strlen(buffer[current_buffer_arr])-1] == '\n')
				buffer[current_buffer_arr][strlen(buffer[current_buffer_arr])-1] = '\0';

			current_buffer_arr = current_buffer_arr + 1;
			
	
			if(current_buffer_arr >= print_lines_inc){ //reset to rewrite the oldest lines
		
				current_buffer_arr = 0;
			}else{
				continue;
			}
		}

	
		if(line != error_line && error_line != -1){ //if error has been set and it wasnt on last line
			fprintf(stderr,"Error: line too long\n");
		}

		current_buffer_arr++;

		for(int i = 0; i < print_lines_inc; i++){


			// printf("reading from buffer %d\n", current_buffer_arr);
		
			if(strcmp(buffer[current_buffer_arr],"") != 0)//if not trying to print empty string
				printf("%s\n",buffer[current_buffer_arr]);

			current_buffer_arr++;

			if(current_buffer_arr > print_lines_inc){ //reset to rewrite the oldest lines
					current_buffer_arr = 0;
			}
		}
		return 0;
	}	

	return 1;
}

int get_digit(char *str){

	char c;
	unsigned int i = 0;
	int digit = 0;
	int number = 0;

	c = str[0];
	if(c != '+' && c != '-'){
		if(!(c >= '0' && c <= '9')){
			fprintf(stderr,"invalid argument for option -n\n");
			return -1;
		}else{
			digit = c - '0';
			number = number*10 + digit;
		}
	}

	for(i = 1; i < (strlen(str)); i++)
	{
		
		c = str[i];
		if(c >= '0' && c <= '9') //to confirm it's a digit
		{
			digit = c - '0';
			number = number*10 + digit;
		}else{
			fprintf(stderr,"invalid argument for option -n\n");
			return -1;
		}
	}

	return number;
}


void do_at_exit(){

	if(global_file_ptr != NULL){
	fclose(global_file_ptr);
	}
	
}