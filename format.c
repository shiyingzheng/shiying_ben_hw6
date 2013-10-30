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
 *if it encounters EOF, it returns EOF
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
 * if it encounters EOF, it stops
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
 * print one paragraph formatted left aligned
 * the paragraph must have a null character at the end
 */
void format_left_align(char* par, int width){
	char exit=0;//tells the loop when to exit
	char* word=par;//this pointer is inside paragraph, and is moved every time we reach a new word
	char* word_buffer;//holds a word before we figure out how long it is.
	if((word_buffer=malloc(BUFFER_SIZE*sizeof(char)))==NULL) fprintf(stderr,"Out of memory");
	int line_position=0;//tells us how many characters we have already put in our line
	int position=0;//the position inside word. If position is 0 we are at the beginning of a new word.
	//gets reset to 0 every time we hit a space
	while(!exit){
		word_buffer[position]=word[position];
		if(word[position]==' '||word[position]==0){//word is finished
			word_buffer[position+1]=0;//make word_buffer a string
			if(line_position+position>width) printf("%c",'\n');//if the next word would overflow the line, print a newline
			printf("%s",word_buffer);//print the word. It has either a space or a null char at the end.
			if(word[position]==' '){
				word+=position+1;//make word be the next word in the paragraph
				position=0;//reset position
			}
			else exit=1;//because we will have hit the end of paragraph
		}
		++position;
	}
	free(word_buffer);
}
/*
 * print one paragraph formatted right aligned
 */
void format_right_align(char* par, int width){
        //TODO not implemented yet
}
/*
 * print one formatted paragraph justified.
 */
void format_justified(char* par, int width){
        //TODO not implemented yet
}

/*
 * format one paragraph in the correct mode, assuming words are 
 * seperated by spaces
 * The format functions should print the formatted paragraph.
 */
void format_paragraph(char* par,char mode, int width){
        if(mode='l') format_left_align(par,width);
	else if(mode='r') format_right_align(par,width);
	else if(mode='j') format_justified(par,width);
}
int main(){
	//while(1){
		printf("%s",get_next_line());
		printf("%s",get_next_line());
		printf("%s",get_next_line());
	//}
}
