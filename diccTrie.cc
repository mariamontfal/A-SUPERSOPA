#include <iostream>
using namespace std;

#define LAST_CHAR '\0'

//ESTRUCTURA NODE
struct Node {
    char str;
    Node* leftChild;
    Node* rightChild;
    Node* eqChild;
};

//CLASSE ARBRE TERNARI DE CERCA
class TernarySearchTree {
    private:
        Node* root;

    public:
        TernarySearchTree(){
            this->root = nullptr;
        }
        
        TernarySearchTree(Node* root){
            this->root = root;
        }

        Node* insertWord(char* word){
            return insertWord(&(this->root), word);
        }

        Node* insertWord(Node** node, char* word){
            if((*node)==nullptr){
                (*node) = new Node();
                (*node)->str = *word;
                (*node)->leftChild=nullptr;
                (*node)->rightChild=nullptr;
                (*node)->eqChild=nullptr;
            }

            if(*word < (*node)->str) (*node)->leftChild = insertWord(&(*node)->leftChild, word);
            else if(*word > (*node)->str) (*node)->rightChild = insertWord(&(*node)->rightChild, word);
            else {
                if(*word!=LAST_CHAR) (*node)->eqChild = insertWord(&(*node)->eqChild, ++word);
                else return nullptr; // s'ha de retornar null perque sino afageix el valor LAST_CHAR
            }
            return (*node);
        }

        bool findWord(char* word){
            return findWord(&(this->root),word);
        }
        
        bool findWord(Node** node, char* word){
            if(*word==LAST_CHAR) return 1;
            if((*node)==nullptr) return 0;
            if(*word < (*node)->str) return findWord(&(*node)->leftChild,word);
            else if(*word > (*node)->str) return findWord(&(*node)->rightChild,word);
            return findWord(&(*node)->eqChild, ++word);
        }

        void printTree() {
            printTree(&(this->root));
        }

        void printTree(Node** node, int h = 0, string prefix = "rot") {
            cout << '(' << prefix << ')';
            for(int i=0; i<h*2; i++) cout << "-";
            if((*node)==nullptr) cout << "()" << endl;
            else{
                cout << (*node)->str << endl;
                printTree(&(*node)->leftChild,h+1,"lft");
                printTree(&(*node)->eqChild,h+1,"eql");
                printTree(&(*node)->rightChild,h+1,"rgt");
            }
        }

};

int main(){
    
    TernarySearchTree tst = TernarySearchTree();
    tst.insertWord("b");
    tst.insertWord("a");
    tst.insertWord("c");
    tst.insertWord("bZ");
    tst.printTree();
    cout << tst.findWord("bZ") << endl;
    
    cout << "Fi de programa..." << endl;
    return 0;
}






