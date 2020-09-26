// descrition of tail from shell man:
//   Print the last 10 lines of each FILE to standard output.  With more
//   than one FILE, precede each with a header giving the file name. 
//   With no FILE, or when FILE is -, read standard input.
// Options:
//	 -n, --lines=[+]NUM
//    	output the last NUM lines, instead of the last 10; or use -n
//      +NUM to output starting with line NUM

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE_LEN 1023
FILE *gfp;

int read_from_file(FILE *fp, int lines_number, int read_from_top, int print_lines);
int read_from_stdin(int line_number, int read_from_top, int print_lines);
int get_digit(char *str);
int count_lines(FILE *fp);
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
	int lines_number;
	int print_lines;
	
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

    FILE *fp = fopen((argv[index]),"r");
	gfp = fp; //copy local pointer to global pointer
			
	if(fp != NULL){
		lines_number = count_lines(fp);
		rewind(fp);
		if(read_from_file(fp, lines_number, read_from_top, print_lines) != 0){
			return 1;
		}
		return 0;
	}

	if((nflag == 0 && argc == 1) || (nflag == 1 && argc == 3)){
		fp = stdin;	
		lines_number = count_lines(fp);
		rewind(fp);
		if(read_from_file(fp,lines_number, read_from_top, print_lines) != 0){
			//chybove hlaseni
			return 1;
		}
		fclose(fp);

		return 0;
	}

  return 0;
}


int read_from_file(FILE *fp, int lines_number, int read_from_top, int print_lines){

	char c;
	int line_count = 0;
	int line_size = 0;


	if(read_from_top){
		print_lines--;
		while((c = fgetc(fp)) != EOF){

			if(line_size < MAX_LINE_LEN){
				if(line_count >= print_lines){
					printf("%c",c);
				}
			}
			
			
			if(c == '\n'){
				line_count++;
				line_size = 0;
			}else{
				line_size++;
			}	
		}
	}else{
		int line_diff = lines_number - print_lines;
		

		while((c = fgetc(fp)) != EOF){


			if(line_size < MAX_LINE_LEN){
				if(line_diff <= line_count){
					printf("%c",c);
				}
			}

			if(c == '\n'){
				line_count++;
				line_size = 0;
			}else{
				line_size++;
			}	


		
		}
	}

	

	return 1;
}

int get_digit(char *str){

	char c;
	int i = 0;
	int digit = 0;
	int number = 0;

	c = str[0];
	if(c != '+' && c != '-'){
		if(!(c >= '0' && c <= '9')){
			fprintf(stderr,"invalid argument for option -n1\n");
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

int count_lines(FILE *fp){

	char c;
	int lines_number = 0;

	while((c = fgetc(fp)) != EOF){
		if(c == '\n'){
			lines_number++;
		}
	}

	return lines_number;
}

void do_at_exit(){

	if(gfp != NULL){
	fclose(gfp);
	}
}