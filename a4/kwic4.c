#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "linkedlist.h"

int lineCount = 0;
wordnode_t *sentence = NULL;
wordnode_t *sentenceTemp = NULL;
wordnode_t *sentenceTemp2 = NULL;
wordnode_t *notKeyWord = NULL;
wordnode_t *notKeyWordTemp = NULL;
wordnode_t *output = NULL;
wordnode_t *printOut = NULL;

void printword(wordnode_t *n, void *arg) {
    char *format = (char *)arg;

    printf(format, n->w);
}

//this method extracted KeyWord from sentence
wordnode_t *extractKeyWord(){

	wordnode_t *keyWord = NULL;
	int ifKeyWord = 0;
	while(sentenceTemp != NULL){
		//apply(temp, printword, "%s\n");
		char *token;
		token = strtok(sentenceTemp -> w," ");
		while(token != NULL){
			//printf("%s ", token);
			while(notKeyWordTemp != NULL){
				//char *temp3 = notKeyWord -> w;
				//printf("%s\n", temp3->w);
				if(strncasecmp(token, notKeyWordTemp -> w, strlen(token)) == 0){
					ifKeyWord = 1;
				}
				notKeyWordTemp = notKeyWordTemp -> next;
			}
			notKeyWordTemp = notKeyWord;
			if(ifKeyWord == 0){
				keyWord = add_end(keyWord , new_word(token, 0));
			}
			ifKeyWord = 0;
			token = strtok (NULL, " ");
		}
		sentenceTemp  = sentenceTemp  -> next;
	}
	return keyWord;
}

//use bubble to sort the keywords
void sortKeyWord(wordnode_t *keyWord){
	wordnode_t *temp1;
	wordnode_t *temp2;
	char *temp3;
	for(temp1 = keyWord; temp1->next != NULL; temp1 = temp1 ->next){
		for(temp2 = temp1 -> next; temp2 != NULL; temp2 = temp2 ->next){
			if(strcasecmp(temp1 -> w, temp2 -> w) > 0){
				temp3 = temp1->w;
				temp1 -> w = temp2 -> w;
				temp2 -> w = temp3;
			}
		}
	}
}

//read the first part of text file
wordnode_t *readNotKeyWord(){
	char buffer[20];
	fgets(buffer, 20, stdin);
	fgets(buffer, 20, stdin);
	/*read each exclusion word*/
	while(fgets(buffer, 20, stdin)){
		size_t length = strlen(buffer);
		buffer[length-1] = '\0';
		if(strncmp(buffer, "::" , 2) == 0){
			break;
		}
		notKeyWord = add_end(notKeyWord, new_word(buffer, 0));
		notKeyWordTemp = add_end(notKeyWordTemp, new_word(buffer, 0));
	}
	return notKeyWord;
}

//read the second part of textfile
wordnode_t *readSentence(){
	char contentBuffer[100];
	while(fgets(contentBuffer, 100, stdin)){
		contentBuffer[strlen(contentBuffer)-1] = '\0';
		sentence = add_end(sentence, new_word(contentBuffer, 0));
		sentenceTemp = add_end(sentenceTemp, new_word(contentBuffer, 0));
		sentenceTemp2 = add_end(sentenceTemp2, new_word(contentBuffer, 0));
		lineCount++;
	}
	return sentence;
}

//capitalze the keywords in the sentences
void formatting(wordnode_t* keyWord){
	char temp2[100];
	wordnode_t *temp = keyWord;
	while(output != NULL){
		temp2[0] = 0;
		char *token;
		token = strtok(output -> w," ");
		while(token != NULL){
			if(strcasecmp(token, temp -> w) == 0){
				unsigned char *temp3 = (unsigned char *)token;
				while(*temp3){
					*temp3 = toupper((unsigned char)*temp3);
					temp3++;
				}
				strcat(temp2, " ");
				strcat(temp2, token);
			}else{
				strcat(temp2, " ");
				strcat(temp2, token);
			}
			token = strtok(NULL, " ");
		}
		printOut = add_end(printOut, new_word(temp2, 0));
		output = output -> next;
		temp = temp -> next;
	}
}

//create space arear in front of the sentence
void space(wordnode_t *keyWord){
	int iskeyWord = 0;
	while(printOut != NULL){
		iskeyWord = 0;
		char *token2;
		wordnode_t *list1 = NULL;
		wordnode_t *list2 = NULL;
		wordnode_t *list2R = NULL;
		token2 = strtok(printOut -> w," ");
		while(token2 != NULL){
			if(strcasecmp(token2, keyWord -> w) == 0){
				iskeyWord = 1;
			}
			if(iskeyWord == 0){
				list1 = add_end(list1, new_word(token2, 0));
			}else if(iskeyWord == 1){
				list2 = add_front(list2, new_word(token2, 0));
			}
			token2 = strtok(NULL, " ");
		}
		while(length(list1) > 19){
			wordnode_t *del;
			del = peek_front(list1);
			list1 = remove_front(list1);
			free_word(del);
		}
		while(length(list2) > 31){
			wordnode_t *del;
			del = peek_front(list2);
			list2 = remove_front(list2);
			free_word(del);
		}
		if(list1 == NULL){
			list1 = add_end(list1, new_word(" ", 0));
		}
		list2R = reverse(list2);
		int spaceArea = 27 - length(list1);
		while(list2R != NULL){
			list1 = add_end(list1, new_word(list2R -> w, 0));
			list2R = list2R -> next;
		}
		int i = 0;
		for(i = 0; i < spaceArea; i++){
			printf(" ");
		}
		apply(list1, printword, " %s");
		printf("\n");
		printOut = printOut -> next;
		keyWord = keyWord -> next;
	}
}

int main(int argc, char *argv[]) {
	readNotKeyWord();
	//apply(notKeyWord, printword, "%s\n");
	readSentence();
	//apply(sentence, printword, "%s\n");
	wordnode_t *keyWord = extractKeyWord();
	//apply(keyWord, printword, "%s\n");
	sortKeyWord(keyWord);
	free(sentenceTemp);
	free(sentenceTemp2);
	free(notKeyWordTemp);
	//apply(keyWord, printword, "%s\n");
	int wordIndex[100][100];
	int i = 0;
	//create an index to prevent the repetition of the same words
	for(i=0; i<lineCount; i++){
		int countWord = 0;
		char *token;
		token = strtok(sentenceTemp2 -> w," ");
		while(token != NULL){
			wordIndex[i][countWord] = 0;
			token = strtok (NULL, " ");
			countWord += 1;
		}
		sentenceTemp2 = sentenceTemp2 -> next;
	}
	wordnode_t *temp1 = sentence;
	wordnode_t *temp3 = keyWord;
	int j = 0;
	int k =0;
	while(temp3 != NULL){
		j = 0;
		int ifLocated = 0;
		temp1 = sentence;
		while(temp1 != NULL){
			k = 0;
			char *token2;
			char temp2[100];
			strncpy(temp2, temp1->w, 100);
			token2 = strtok(temp2, " ");
			while(token2 != NULL){
				if(ifLocated == 0){
					if(strncasecmp(token2, temp3 -> w, strlen(token2)) == 0){
						if(wordIndex[j][k] == 0){
							output = add_end(output, new_word(temp1 -> w, 0));
							wordIndex[j][k] = 1;
						}
					}
				}
				k++;
				token2 = strtok (NULL, " ");
			}
			j++;
			temp1 = temp1-> next;
		}
		temp3 = temp3 -> next;
	}
	//apply(output, printword, "%s\n");
	formatting(keyWord);
	//apply(printOut, printword, "%s\n");
	space(keyWord);
	exit(0);
}
