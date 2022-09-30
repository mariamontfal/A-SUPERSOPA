#include <iostream>
using namespace std;

#define LAST_CHAR '0'

//ESTRUCTURA NODE
struct Node {
    char* str;
    Node* leftChild, rightChild, eqChild;
};

//CLASSE ARBRE TERNARI DE CERCA
class TernarySearchTree {
    private:
        Node* root;

    public:

        TernarySearchTree(){
            this->root = nullptr;
        }

        insertWord(Node* node, char* word){
            if(node==nullptr){
                node->str = word;
                node->leftChild=nullptr;
                node->rightChild=nullptr;
                node->eqChild=nullptr;
            }

            if(*word < node->str) node->leftChild = insertWord(node->leftChild, word);
            else if(*word > node->str) node->rightChild = insertWord(node->rightChild, word);
            else {
                if(*word!=LAST_CHAR) node->eqChild = insertWord(node->eqChild, ++word);
            }

        }


};

int main(){

}