#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Trie{
    int flag;
    struct Trie *children[26];
}Trie;

void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);


int main(void)
{
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure

    //initialize the Trie ***use calloc ****
    Trie *trie = calloc(1,sizeof(Trie));
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    for (int i = 0; i<5;i++){
        insert (&trie, pWords[i]);
    }

    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}

void insert(struct Trie **ppTrie, char *word){
    if (*ppTrie == NULL){
        return;
    }
    Trie *temp = *ppTrie;
    int length = strlen(word);
    for (int i = 0; i<length; i++) {
        int index = word[i] - 'a';

        if (temp->children[index] == NULL) {
            temp->children[index] = calloc(1, sizeof(Trie));
        }
        temp = temp->children[index];
    }
    temp->flag++;
}

int numberOfOccurances(struct Trie *pTrie, char *word){
    if(pTrie == NULL){
        return 0;
    }

    Trie *temp = pTrie;
    int length = strlen(word);
    int i = 0;
    for (i = 0; i < length  ; i++) {
        int index = word[i] - 'a';
        if (temp->children[index] != NULL) {
            temp = temp->children[index];
        }
        else{
            break;
        }
    }
    if (i==length){
        return temp->flag;
    }
    else{
        return 0;
    }
}
struct Trie *deallocateTrie(struct Trie *pTrie){
    if (pTrie == NULL){
        return pTrie;
    }
    for (int i = 0; i<26; i++){
        if (pTrie->children[i]!= NULL) {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
}

//**********CLASS NOTES******

//A TRIE is used for a collection of strings
//How does it work?
//initialize the trie as one single trie node
//try to add a word → UCF
//  each node in the trie has 26 children
//since u has been init  o→o'u'
// you create a root ptr to not move the root
//traverse down the str and add the following letters to the nodes as children
//use boolean flag to know if word exists
//use an int when you care about duplicate words
//ADD UCO
//since uc are already there just add 'o' as a new child
//to search use a for loop to navigate through the trie