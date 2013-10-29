/*
 * Program: format.c
 * Usage:
 * CS241 hw6
 * Author Shiying Zheng and Ben Stern
 * Mon Oct 28 23:01:59 EDT 2013
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000
/*
 *returns true if standard input is on an empty line, false otherwise
 */
int is_empty_line(){
	int c;
	while((c=getchar())!=EOF){
		if(c=='\n'){
			ungetc(c,stdin);
			return 1;
		}
		if(c!=' '){
			ungetc(c,stdin);
			return 0;
		}
	}
	return EOF;
}
/*
 * gets the next line
 */
char* get_next_line(){
	int c;
	int position=0;
	char* buffer=(char*)malloc((BUFFER_SIZE+1)*sizeof(char));
        char* string;
	while((c=getchar())!=EOF){
                if(c=='\n'){
			buffer[position++]=' ';
			buffer[position]=0;
			string=(char*)malloc((position+1)*sizeof(char));
			strcpy(string, buffer);
			free(buffer);
			return string;
		}
                else{
			buffer[position]=c;
		}
		++position;
        }
        buffer[position]=0;
        string=(char*)malloc((position+1)*sizeof(char));
        strcpy(string, buffer);
        free(buffer);
        return string;
}
/*
 * Reads input from standard input and returns the next paragraph
 */
char* get_next_paragraph(){
	char* c;
	//TODO not implemented yet
	return c;
}
/*
 * returns a pointer to the next word
 */
char* next_word(char* c){
	char* word;
        //TODO not implemented yet
        return word;
}
/*
 * format one paragraph left aligned
 */
char* format_left_align(char* par, int width){
        char* c;
        //TODO not implemented yet
        return c;
}
/*
 * format one paragraph right aligned
 */
char* format_right_align(char* par, int width){
        char* c;
        //TODO not implemented yet
        return c;
}
/*
 * format one paragraph justified
 */
char* format_justified(char* par, int width){
        char* c;
        //TODO not implemented yet
        return c;
}

/*
 * format one paragraph in the correct mode
 */
char* format_paragraph(char* par,char mode, int width){
        char* c;
        //TODO not implemented yet
        return c;
}
int main(){
	int b;
	while((b=is_empty_line())!=EOF){
		printf("%s",get_next_line());
	}
}
