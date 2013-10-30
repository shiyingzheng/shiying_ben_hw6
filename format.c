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
#define PARAGRAPH_SIZE 10000
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
 * gets the next word in the line
 */
char* get_next_word(){
	int c;
	int position=0;
	char* buffer;
	char* word;
	if((buffer=(char*)malloc((BUFFER_SIZE+1)*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
	while((c=getchar())!=EOF && c!='\n' && c!=' '){
		buffer[position]=c;
		++position;
	}
	buffer[position]=0;
	if((word=(char*)malloc((position+1)*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
        strcpy(word, buffer);
        free(buffer);
        return word;
}
/*
 * gets the next line
 * ignores whitespaces in each line
 * returns a character array with words in the line and 
 * whitespace characters to signal word boundries
 */
char* get_next_line(){
	int c;
	int position=0;
	char* buffer;
	if((buffer=(char*)malloc((BUFFER_SIZE+1)*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
        char* string;
	//TODO rewrite!
	//1.ask get_next_word for the next word and add to the current
	//  buffer. put spaces between words and at end of line 
	//2.handle weird spacing including more than one space between
	//  words and space between the last word and the end of line.
	while((c=getchar())!=EOF){
                if(c=='\n'){
			buffer[position++]=' ';
			buffer[position]=0;
			if((string=(char*)malloc((position+1)*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
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
	if((string=(char*)malloc((position+1)*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
        strcpy(string, buffer);
        free(buffer);
        return string;
}
/*
 * Reads input from standard input and returns the next paragraph
 */
char* get_next_paragraph(){
	char *c;
	int position=0;
	char *paragraph;
	int b;
	int h;
	char* line;
	if ((c=(char *)malloc(sizeof(char)*PARAGRAPH_SIZE))==NULL) fprintf(stderr, "out of memory");
	while ((b=is_empty_line())!=EOF&&!b){
		line=get_next_line();
		while (*line!=0){
	      		c[position]=*line;
			line++;
			position++;
		}
	}
	c[position]=0;
	if((paragraph=(char*)malloc(sizeof(char)*(position+1)))==NULL)  fprintf(stderr, "out of memory");
	strcpy(paragraph,c);
	free(c);
	return paragraph;
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
 * format one paragraph in the correct mode, assuming words are 
 * seperated by spaces
 */
char* format_paragraph(char* par,char mode, int width){
        char* c;
        //TODO not implemented yet
        return c;
}
int main(){
	printf("%s",get_next_paragraph());
}
