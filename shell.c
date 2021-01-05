
/********** Including Necessary Header Files **********/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

/********** Declaring Global variables **********/

int fd;
static char *args[512];
static char prompt[512];
char *history_file;
char *input_buffer;
char *cmd_exec[512];
int flag, len;
char cwd[1024];
int bckgrnd_flag;
pid_t pid;
int no_of_lines;
int environmment_flag;


/********** Declaring Function Prototypes **********/

void clear_variables(); 
void print_history_list ();
void environmment();
void set_environment_variables();
void change_directory();
char *skipwhite (char* );
void tokenize_by_space (char *);
char *skip_double_quote(char* );
void shell_prompt(); 
void sigintHandler(int );

/********** Function Definitions **********/

/* This function handles the interrupt signals */

void sigintHandler(int sig_num) {

    signal(SIGINT, sigintHandler);
    fflush(stdout);
    return;
}


/* This function initializes the global variables */

void clear_variables() {

	fd = 0;
	flag = 0;
	len = 0;
	no_of_lines = 0;
	flag_without_pipe = 0;
	output_redirection = 0;
	input_redirection = 0;
	cwd[0] = '\0';
	prompt[0] = '\0';
 	pid = 0;
	environmment_flag = 0;
}

/* This function prints the comand history when "history" command is given */

void print_history_list () {
  	
  	register HIST_ENTRY **the_list;
    register int i;

    the_list = history_list ();
    if (the_list)
    	for (i = 0; the_list[i]; i++)
            printf ("%d: %s\n", i + history_base, the_list[i]->line);
    return;
}
  
/* This function is used to create the Shell Prompt */

void shell_prompt() {

	if (getcwd(cwd, sizeof(cwd)) != NULL) {

		strcpy(prompt, "Our_Shell: ");
		strcat(prompt, cwd);
		strcat(prompt, "$ ");
	}
	else {

		perror("Error in getting curent working directory: ");
	}
	return;
}

/* This function is used to skip the white spaces in the input string */

char *skipwhite (char* str) {

	int i = 0, j = 0;
	char *temp;
	if (NULL == (temp = (char *) malloc(sizeof(str)*sizeof(char)))) {
		perror("Memory Error: ");
		return NULL;
	}

	while(str[i++]) {

		if (str[i-1] != ' ')
			temp[j++] = str[i-1];
	}
	temp[j] = '\0';
	return temp;
}

/* This function is used to skip the double quote characters (") in the
   input string */

char *skip_double_quote (char *str) {

	int i = 0, j = 0;
	char *temp;
	if (NULL == (temp = (char *) malloc(sizeof(str)*sizeof(char)))) {
		perror("Memory Error: ");
		return NULL;
	}

	while(str[i++]) {

		if (str[i-1] != '"')
			temp[j++] = str[i-1];
	}
	temp[j] = '\0';
	return temp;
}

/* This function is used to change directory when "cd" command is 
   executed */

void change_directory() {

	char *home_dir = "/home";

	if ((args[1]==NULL) || (!(strcmp(args[1], "~") && strcmp(args[1], "~/"))))
		chdir(home_dir);
	else if (chdir(args[1]) < 0)
		perror("No such file or directory: ");

}


/* This function tokenizes the input string based on white-space [" "] */

void tokenize_by_space (char *str) {

	int m = 1;

	args[0] = strtok(str, " ");
	while ((args[m] = strtok(NULL," ")) != NULL) m++;
	args[m] = NULL;
}

/* Main function begins here */

int main() {

	int status;
	system ("clear");
	signal(SIGINT, sigintHandler);
	char new_line = 0;
	using_history();

	do {

		clear_variables();
		shell_prompt();
		input_buffer = readline (prompt);


		if(strcmp(input_buffer,"\n"))
			add_history (input_buffer);

		if (!(strcmp(input_buffer, "\n") && strcmp(input_buffer,"")))
			continue;

		if (!(strncmp(input_buffer, "exit", 4) && strncmp(input_buffer, "quit", 4))) {

			flag = 1;
			break;
		}


		if (bckgrnd_flag == 0)
			waitpid(pid,&status,0);
		else
			status = 0;

	} while(!WIFEXITED(status) || !WIFSIGNALED(status));

	if (flag == 1) {

		printf("\nThank You... Closing Shell...\n");
		exit(0);
	}

	return 0;
}
