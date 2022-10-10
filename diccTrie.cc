#ifndef DICC_TRIE
#define DICC_TRIE

#include <iostream>
#include <string.h>
#include "ED.cc"
using namespace std;

#define LAST_CHAR '\0'

struct Node {
    char str;
    bool endOfWord;
    Node* leftChild;
    Node* rightChild;
    Node* eqChild;
};

class diccTrie : EstructuraDades {
    
private:
    Node* root;

public:

    diccTrie(){
        this->root = nullptr;
    }

    diccTrie(Node** root){
        this->root = *root;
    }

    Node* addWord(string word){
        return addWord(&(this->root), &word[0]);
    }

    Node* addWord(Node** node, char* word){
        if( (*node)==nullptr){
            (*node) = new Node();
            (*node)->str = *word;
            (*node)->leftChild=nullptr;
            (*node)->rightChild=nullptr;
            (*node)->eqChild=nullptr;
            (*node)->endOfWord=false;
        }

        if(*word < (*node)->str) (*node)->leftChild = addWord(&(*node)->leftChild, word);
        else if(*word > (*node)->str) (*node)->rightChild = addWord(&(*node)->rightChild, word);
        else {
            if(*word!=LAST_CHAR) {
                (*node)->eqChild = addWord(&(*node)->eqChild, ++word);
                if(*(word)==LAST_CHAR) (*node)->endOfWord = true;
            }
            else return nullptr;
        }
        return (*node);
    }

    SearchResult findWord(string word){
        return findWord(&(this->root),&word[0]);
    }

    SearchResult findWord(Node** node, char* word){
        if((*node)==nullptr) return SearchResult::SUBWORD_NOT_FOUND;
        if(*word < (*node)->str) return findWord(&(*node)->leftChild,word);
        else if(*word > (*node)->str) return findWord(&(*node)->rightChild,word);
        else{
            char* nextChar = ++word;
            if(*nextChar == LAST_CHAR) {
                if((*node)->endOfWord == true) return SearchResult::WORD_FOUND;
                else return SearchResult::WORD_NOT_FOUND;
            }
            else return (findWord(&(*node)->eqChild, nextChar));
        }
    }

    bool findSubWord(char* word){
        return findSubWord(&(this->root),word);
    }

    bool findSubWord(Node** node, char* word){
        if((*word)==LAST_CHAR) return 1;
        if((*node)==nullptr) return 0;
        if(*word < (*node)->str) return findSubWord(&(*node)->leftChild,word);
        else if(*word > (*node)->str) return findSubWord(&(*node)->rightChild,word);
        else return (findSubWord(&(*node)->eqChild, ++word));
    }

    void printTree(int h = 0) {
        printTree(&(this->root), 0);
    }

    void printTree(Node** node, int h = 0, string prefix = "rot") {
        cout << '(' << prefix << ')';
        for(int i=0; i<h*2; i++) cout << "-";
        if((*node)==nullptr) cout << "x" << endl;
        else{
            cout << (*node)->str << (*node)->endOfWord << endl;
            printTree(&(*node)->leftChild,h+1,"lft");
            printTree(&(*node)->eqChild,h+1,"eql");
            printTree(&(*node)->rightChild,h+1,"rgt");
        }
    }

};

#endif