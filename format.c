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
int eof=0;
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
        eof=1;
        return EOF;
}

/*
 * gets the next word in the line
 * skips the next whitespaces
 * returns only a newline if it is called at the end of a line
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
        if(c==EOF){
                eof=1;
        }
        else if(c=='\n'&&position==0){
                free(buffer);
                return "\n";
        }
        else{
                while(c==' '){
                               if((c=getchar())==EOF) eof=1;
                       }
                if(!eof)ungetc(c,stdin);//if there was either a \n or another character after ([alpha]\ *) unget it
        }
        buffer[position]=0;
        if((word=(char*)malloc((position+1)*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
        strcpy(word, buffer);
        free(buffer);
        return word;
}
/*
 * left justify input
 */
void format_left_align(int width){
        int b=0;
        char* word;
        char buffer[BUFFER_SIZE];
        buffer[0]=0;
        int position=0;
        while(!eof){
                word=get_next_word();
                if(!strcmp(word,"\n")){
                        while((b=is_empty_line())&&b!=EOF){
                                word=get_next_word();
                                strcat(buffer,word);
                                printf("%s\n",buffer);
                                position=0;
                                buffer[0]=0;
                        }
                }
                else{
                        if(position+strlen(word)<width){
                                if(position){
                                        strcat(buffer," ");
                                        position++;
                                }
                                strcat(buffer,word);
                                position+=strlen(word);
                        }
                        else if(position!=0){
                                printf("%s\n",buffer);
                                position=0;
                                buffer[0]=0;
                                strcat(buffer,word);
                                position+=strlen(word);
                                free(word);
                        }
                        else{
                                printf("%s\n",word);
                                free(word);
                        }
                }
        }
        printf("%s",buffer);
        if(b==EOF) printf("\n");
}
/*
 * right justify input
 */
void format_right_align(int width){
	int b=0;
        char* word;
        char buffer[BUFFER_SIZE];
        buffer[0]=0;
        int position=0;
	int cur=0;
        while(!eof){
                word=get_next_word();
                if(!strcmp(word,"\n")){
                        while((b=is_empty_line())&&b!=EOF){
                                word=get_next_word();
                                strcat(buffer,word);
				while(cur<width-position && width>position){
					printf(" ");
					cur++;
				}
				cur=0;
                                printf("%s\n",buffer);
                                position=0;
                                buffer[0]=0;
                        }
                }
                else{
                        if(position+strlen(word)<width){
                                if(position){
                                        strcat(buffer," ");
                                        position++;
                                }
                                strcat(buffer,word);
                                position+=strlen(word);
                        }
                        else if(position!=0){
				while(cur<width-position && width>position){
					printf(" ");
					cur++;
				}
				cur=0;
                                printf("%s\n",buffer);
                                position=0;
                                buffer[0]=0;
                                strcat(buffer,word);
                                position+=strlen(word);
                                free(word);
                        }
                        else{
				while(cur<width-strlen(word) && width>strlen(word)){
					printf(" ");
					cur++;
				}
				cur=0;
                                printf("%s\n",word);
                                free(word);
                        }
                }
        }
	while(cur<width-position && width>position){
		printf(" ");
		cur++;
	}
        printf("%s",buffer);
        if(b==EOF) printf("\n");

}
/*
 * fully justify input
 */
void format_justified(int width){
        //TODO not implemented yet
}

/*
 * format one paragraph in the correct mode, assuming words are 
 * seperated by spaces
 * The format functions should print the formatted paragraph.
 */
void format(char mode, int width){
        if(mode=='l') format_left_align(width);
        else if(mode=='r') format_right_align(width);
        else if(mode=='j') format_justified(width);
}
int main(){
	format('l',72); 
}

