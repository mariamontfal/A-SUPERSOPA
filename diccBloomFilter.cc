#ifndef DICC_BLOOM_FILTER
#define DICC_BLOOM_FILTER

#include <iostream>
#include <string.h>
#include <vector>
#include<math.h>
#include "ED.cc"
using namespace std;

class diccBloomFilter : EstructuraDades {
    private:

        vector<bool> bitsArray;

        //Mida del vector
        int m;

        //Numero de funcions de hash
        int k;

        //Numero d'elements esperats a ser insertats al filtre
        int n;

        //Probabilitat d'error
        double p;

        //Vector amb les paraules del diccionari
        vector<string> wordsToAdd;

    public:
        //Constructora per defecte
        diccBloomFilter(){
            this->bitsArray = vector<bool>();
            this->n=0;
            this->m=0;
            this->k=0;
            this->p = 0.01;
        }

        //Constructora
        diccBloomFilter(vector<string> wordsToAdd){
            this->p = 0.01;
            this->n = wordsToAdd.size();
            this->m = lengthOfArray();
            this->k = numberOfKFunctions();
            this->wordsToAdd=wordsToAdd;
            this->bitsArray = vector<bool>(m,0);

            modifyBitsArray();
        }

        //Destructora
        ~diccBloomFilter(){}

        //Funcio que calcula la longitud que ha de tenir el filtre
        int lengthOfArray(){
            return -(this->n * log(this->p))/(pow(log(2),2));
        }

        //Funcio que calcula el nombre de funcions de hash adients
        int numberOfKFunctions(){
            return int((this->m/this->n)*log(2));
        }

        //Funcio que calcula la probabilitat de fals positiu
        double calculateProbability(){
            double aux = 1.0-1.0/this->m;
            aux = pow(aux, this->k*this->n);
            return pow(1.0 - aux, this->k);
        }

        // Funcio de hash 1
        int h1(string s){
            unsigned long long hash = 0;
            for (int i = 0; i < s.size(); i++)
            {
                hash = (hash + ((int)s[i]));
                hash = hash % this->m;
            }
            return hash;
        }

        // Funcio de hash 2
        int h2(string s){
            unsigned long long hash = 1;
            for (int i = 0; i < s.size(); i++)
            {
                hash = hash + pow(19, i) * s[i];
                hash = hash % this->m;
            }
            return hash % this->m;
        }

        // Funcio de hash 3
        int h3(string s){
            unsigned long long hash = 7;
            for (int i = 0; i < s.size(); i++)
            {
                hash = (hash * 31 + s[i]) % this->m;
            }
            return hash % this->m;
        }

        // Funcio de hash 4
        int h4(string s){
            unsigned long long hash = 3;
            int p = 7;
            for (int i = 0; i < s.size(); i++) {
                hash += hash * 7 + s[0] * pow(p, i);
                hash = hash % this->m;
            }
            return hash;
        }

        // Funcio de hash 5
        int h5(string s){
            unsigned long long hash = 1;
            for (int i = 0; i < s.size(); i++)
            {
                hash = hash + pow(17, i) * s[i];
                hash = hash % this->m;
            }
            return hash % this->m;
        }

        // Funcio de hash 6
        int h6(string s){
            unsigned long long hash = 13;
            for (int i = 0; i < s.size(); i++)
            {
                hash = (hash * 71 + s[i]) % this->m;
            }
            return hash % this->m;
        }

        // Funcio que modifica el filtre per un conjunt de paraules
        void modifyBitsArray(){
            int i = 0;
            while(i<wordsToAdd.size()){
                bitsArray[h1(wordsToAdd[i])]=1;
                bitsArray[h2(wordsToAdd[i])]=1;
                bitsArray[h3(wordsToAdd[i])]=1;
                bitsArray[h4(wordsToAdd[i])]=1;
                bitsArray[h5(wordsToAdd[i])]=1;
                bitsArray[h6(wordsToAdd[i])]=1;
            ++i;
            }
        }

        //Funcio que retorna el nombre de funcions de hash
        int getK(){
            return this->k;
        }

        //Funcio que retorna la mida del filtre
        int getM(){
            return this->m;
        }

        //Funcio que retorna el nombre de paraules afegides
        int getN(){
            return this->n;
        }

        //Funcio que retorna la probabilitat de fals positiu
        double getProbability(){
            return calculateProbability();
        }


        vector<string> getWordsToAdd(){
            return this->wordsToAdd;
        }

        vector<bool> getBitsArray(){
            return this->bitsArray;
        }

        //Funcio que retorna si una paraula esta emmagatzemada a l'estructura
        SearchResult findWord(string word){
            bool found = bitsArray[h1(word)] &&
               bitsArray[h2(word)] &&
               bitsArray[h3(word)] &&
               bitsArray[h4(word)] &&
               bitsArray[h5(word)] &&
               bitsArray[h6(word)];
            if(found) return SearchResult::WORD_FOUND;
            return SearchResult::WORD_NOT_FOUND;
        }

        //Funcio que afegeix una paraula a l'estructura
        void addWord(string word){
            bool exists = 0;
            if(m!=0){
                exists = bitsArray[h1(word)] and bitsArray[h2(word)] and bitsArray[h3(word)]
                            and bitsArray[h4(word)] and bitsArray[h5(word)] and bitsArray[h6(word)];
            }
            if (!exists){
                this->wordsToAdd.push_back(word);
                this->n = wordsToAdd.size();
                //Probabilitat massa alta, es reseteja el vector dels hash
                if(m==0 || (calculateProbability()>0.05 and lengthOfArray()!=this->m)){
                    this->p=0.01;
                    this->m=lengthOfArray();
                    this->k=numberOfKFunctions();
                    int i=0;
                    for(i=0; i<bitsArray.size(); ++i) this->bitsArray[i] = 0;
                    while(i<m) {this->bitsArray.push_back(0); ++i;}
                    //if(bitsArray.size()!=m) cout<<"PANIC"<<endl;
                    modifyBitsArray();
                }

                //Nomes es mofica el bitsArray
                else{
                    bitsArray[h1(word)]=1;
                    bitsArray[h2(word)]=1;
                    bitsArray[h3(word)]=1;
                    bitsArray[h4(word)]=1;
                    bitsArray[h5(word)]=1;
                    bitsArray[h6(word)]=1;
                }
            }
        }
};
#endif