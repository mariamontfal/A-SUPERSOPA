#include <iostream>
#include <string.h>
using namespace std;

#define LAST_CHAR '\0'

//ESTRUCTURA NODE
struct Node {
    char str;
    bool endOfWord;
    Node* leftChild;
    Node* rightChild;
    Node* eqChild;
};

enum SearchResult {
    WORD_FOUND,
    WORD_NOT_FOUND_BUT_EXIST_SUBWORD,
    WORD_NOT_FOUND_AND_SUBWORD_DOESNT_EXIST
};

//CLASSE ARBRE TERNARI DE CERCA
class TernarySearchTree {
    private:
        Node* root;

    public:

        TernarySearchTree(){
            this->root = nullptr;
        }

        TernarySearchTree(Node** root){
            this->root = *root;
        }

        Node* insertWord(char* word){
            return insertWord(&(this->root), word);
        }

        Node* insertWord(Node** node, char* word){
            if( (*node)==nullptr){
                (*node) = new Node();
                (*node)->str = *word;
                (*node)->leftChild=nullptr;
                (*node)->rightChild=nullptr;
                (*node)->eqChild=nullptr;
                (*node)->endOfWord=false;
            }

            if(*word < (*node)->str) (*node)->leftChild = insertWord(&(*node)->leftChild, word);
            else if(*word > (*node)->str) (*node)->rightChild = insertWord(&(*node)->rightChild, word);
            else {
                if(*word!=LAST_CHAR) {
                    (*node)->eqChild = insertWord(&(*node)->eqChild, ++word);
                    if(*(word)==LAST_CHAR) (*node)->endOfWord = true;
                }
                else return nullptr;
            }
            return (*node);
        }

        SearchResult findWord(char* word){
            return findWord(&(this->root),word);
        }

        SearchResult findWord(Node** node, char* word){
            if((*node)==nullptr) return SearchResult::WORD_NOT_FOUND_AND_SUBWORD_DOESNT_EXIST;
            if(*word < (*node)->str) return findWord(&(*node)->leftChild,word);
            else if(*word > (*node)->str) return findWord(&(*node)->rightChild,word);
            else{
                char* nextChar = ++word;
                if(*nextChar == LAST_CHAR) {
                    if((*node)->endOfWord == true) return SearchResult::WORD_FOUND;
                    else return SearchResult::WORD_NOT_FOUND_BUT_EXIST_SUBWORD;
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


int main(){

    string wordsToAdd[] = {"up","bug"};
    string wordsToFind[] = {"up","bug","cut", "cup","bag","b","u","bu"};

    TernarySearchTree tst = TernarySearchTree();
    for(string word : wordsToAdd) tst.insertWord(&word[0]);
    tst.printTree();

    for(string word : wordsToFind) {
        switch(tst.findWord(&word[0]))
        {
            case SearchResult::WORD_FOUND:
                cout << word << " found!" << endl;
                break;
            case SearchResult::WORD_NOT_FOUND_BUT_EXIST_SUBWORD:
                cout << word << " not found but exist subword!" << endl;
                break;
            case SearchResult::WORD_NOT_FOUND_AND_SUBWORD_DOESNT_EXIST:
                cout << word << " doesnt exist subword!" << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}