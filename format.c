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
#define WORD_SIZE 100
int eof=0;
int merge_empty_lines=0;
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
        if((buffer=(char*)malloc((WORD_SIZE+1)*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
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
        char buffer[BUFFER_SIZE+1];
        buffer[0]=0;
        int position=0;
        while(!eof){
                word=get_next_word();
                if(!strcmp(word,"\n")){
			if (position!=0){
                        	if((b=is_empty_line())&&b!=EOF){
                                	word=get_next_word();
                           	     	strcat(buffer,word);
                                	printf("%s\n",buffer);
                                	position=0;
                                	buffer[0]=0;
                        	}
			}
			else if (!merge_empty_lines) {
				printf("\n");
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
				free(word);
                        }
                        else if(position!=0){
                                printf("%s\n",buffer);
                                buffer[0]=0;
                                strcat(buffer,word);
                                position=strlen(word);
                                free(word);
                        }
                        else{
                                printf("%s\n",word);
                                free(word);
                        }
                }
        }
        printf("%s",buffer);
	printf("\n");
}
/*
 * right justify input
 */
void format_right_align(int width){
	int b=0;
        char* word;
        char buffer[BUFFER_SIZE+1];
        buffer[0]=0;
        int position=0;
	int cur=0;
        while(!eof){
                word=get_next_word();
                if(!strcmp(word,"\n")){
                        if(position!=0){
				if((b=is_empty_line())&&b!=EOF){
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
			else if (!merge_empty_lines){
				printf("\n");
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
				free(word);
                        }
                        else if(position!=0){
				while(cur<width-position && width>position){
					printf(" ");
					cur++;
				}
				cur=0;
                                printf("%s\n",buffer);
                                buffer[0]=0;
                                strcat(buffer,word);
                                position=strlen(word);
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
	printf("\n");
}
/*
 * print out a line fully justified
 * called by format_justified(int)
 */
void print_fjustified(char* line, int width){
        int num_of_words=0;
	int total_word_length=0;
	int spaces_so_far=0;
	int gaps_so_far=0;
	int i=0;
	int k;
	int cur_char=0;
	char word_buffer[WORD_SIZE+1];
	int word_pos=0;
	int cur_spaces=0;
	for(i=0;line[i];i++){
		if(line[i]==' '){
			num_of_words++;
		}
		else{
			if(num_of_words==0) num_of_words=1;
			total_word_length++;
		}
	}
	int total_spaces=width-total_word_length;
        int total_gaps=num_of_words-1;
	for(i=0;i<num_of_words;i++){
		while(line[cur_char]!=' ' && cur_char<strlen(line)){
			word_buffer[word_pos]=line[cur_char];
			word_pos++;
			cur_char++;
		}
		if(i!=num_of_words-1){
			gaps_so_far++;
			word_buffer[word_pos]=0;
			cur_char++;
			printf("%s",word_buffer);
			cur_spaces=gaps_so_far*total_spaces/total_gaps-spaces_so_far;
			for(k=0;k<cur_spaces;k++){
				printf(" ");
				spaces_so_far++;
			}
			word_pos=0;
		}
		else{
			word_buffer[word_pos]=0;
			printf("%s",word_buffer);
		}
	}
	printf("\n");
}

/*
 * fully justify input
 */
void format_justified(int width){
	char* line_buffer;
	if((line_buffer=(char*)malloc(sizeof(char)*(BUFFER_SIZE+1)))==NULL) fprintf(stderr, "out of memory");
	int position=0;
	char* word;
	int b;
	while(!eof){
		word=get_next_word();
		if(!strcmp(word,"\n")){
			if (position!=0){
				if((b=is_empty_line())&&b!=EOF){
                                	word=get_next_word();
                                	print_fjustified(line_buffer, width);
					printf("\n");
                                	position=0;
                                	line_buffer[0]=0;
                        	}
			}
			else if (!merge_empty_lines){
				printf("\n");
			}
		}
		else{
			if(position+strlen(word)<width){
                                if(position){
                                        strcat(line_buffer," ");
                                        position++;
                                }
                                strcat(line_buffer,word);
                                position+=strlen(word);
                                free(word);
                        }

/*			if(position+strlen(word)<width){
				strcat(line_buffer,word);
				position+=strlen(word);
				free(word);
			}*/
			else{
				print_fjustified(line_buffer, width);
				line_buffer[0]=0;
				strcat(line_buffer,word);
				position=strlen(word);
				free(word);
			}
		}
	}
	print_fjustified(line_buffer, width);
//	printf("\n");
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
int main(int argc, char *argv[]){
	int width=72;
	char mode='l';
	char** p=NULL;
	int error=0;
	
	int i;
	for (i=1;i<argc;i++){
		if (!strcmp(argv[i],"-j")){
			mode='j';
		}
		else if (!strcmp(argv[i],"-r")){
			mode='r';
		}
		else if (!strcmp(argv[i],"-w")){
			if (i==argc-1 || strtol(argv[i+1], p, 10)==0){
				printf("Invalid width specification - ignoring\n\n");
				error=1;
			}
			else{
				width=atoi(argv[i+1]);
				i++;
			}
		}
		else if (!strcmp(argv[i],"-s")){
			merge_empty_lines=1;
		}
		else{
			printf("Unknown flag %s\n\n", argv[i]);
			error=1;
			break;
		}
	}
	if(error){
		printf("Usage %s [-w #] [-r] [-j] [-s]\n\n", argv[0]);
		printf("Reformats stdin into paragraphs separated by blank lines\n\n");
		printf("	-w #    Specify the width of the output lines\n");
		printf("	-r      Align the text to the right side\n");
		printf("	-j      Fully justify all text\n");
		printf("	-s      Ignore multiple blank lines\n");
		printf("	-h/-?   This message\n\n");
	}
	else{
		format(mode,width);
	}
}

