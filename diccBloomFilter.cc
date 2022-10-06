#include "diccBloomFilter.h"


//Constructora per defecte
BloomFilter::BloomFilter(){
    this->bitsArray = vector<bool>();
    this->n=0;
    this->m=0;
    this->k=0;
    this->p = 0.01;
}

//Constructora
BloomFilter::BloomFilter(vector<string> wordsToAdd){
    this->p = 0.01;
    this->n = wordsToAdd.size();
    this->m = lengthOfArray();
    this->k = numberOfKFunctions();
    this->wordsToAdd=wordsToAdd;
    this->bitsArray = vector<bool>(m,0);

    modifyBitsArray();
}

//Destructora
BloomFilter::~BloomFilter(){}

//Funcio que calcula la longitud que ha de tenir el filtre
int BloomFilter::lengthOfArray(){
    return -(this->n * log(this->p))/(pow(log(2),2));
}

//Funcio que calcula el nombre de funcions de hash adients
int BloomFilter::numberOfKFunctions(){
    return int((this->m/this->n)*log(2));
}

//Funcio que calcula la probabilitat de fals positiu
double BloomFilter::calculateProbability(){
    double aux = 1.0-1.0/this->m;
    aux = pow(aux, this->k*this->n);
    return pow(1.0 - aux, this->k);
}

// Funcio de hash 1
int BloomFilter::h1(string s){
    long long int hash = 0;
    for (int i = 0; i < s.size(); i++)
    {
        hash = (hash + ((int)s[i]));
        hash = hash % this->m;
    }
    return hash;
}

// Funcio de hash 2
int BloomFilter::h2(string s){
    long long int hash = 1;
    for (int i = 0; i < s.size(); i++)
    {
        hash = hash + pow(19, i) * s[i];
        hash = hash % this->m;
    }
    return hash % this->m;
}

// Funcio de hash 3
int BloomFilter::h3(string s){
    long long int hash = 7;
    for (int i = 0; i < s.size(); i++)
    {
        hash = (hash * 31 + s[i]) % this->m;
    }
    return hash % this->m;
}

// Funcio de hash 4
int BloomFilter::h4(string s){
    long long int hash = 3;
    int p = 7;
    for (int i = 0; i < s.size(); i++) {
        hash += hash * 7 + s[0] * pow(p, i);
        hash = hash % this->m;
    }
    return hash;
}

// Funcio de hash 5
int BloomFilter::h5(string s){
    long long int hash = 1;
    for (int i = 0; i < s.size(); i++)
    {
        hash = hash + pow(17, i) * s[i];
        hash = hash % this->m;
    }
    return hash % this->m;
}

// Funcio de hash 6
int BloomFilter::h6(string s){
    long long int hash = 13;
    for (int i = 0; i < s.size(); i++)
    {
        hash = (hash * 71 + s[i]) % this->m;
    }
    return hash % this->m;
}

// Funcio que modifica el filtre per un conjunt de paraules
void BloomFilter::modifyBitsArray(){
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
int BloomFilter::getK(){
    return this->k;
}

//Funcio que retorna la mida del filtre
int BloomFilter::getM(){
    return this->m;
}

//Funcio que retorna el nombre de paraules afegides
int BloomFilter::getN(){
    return this->n;
}

//Funcio que retorna la probabilitat de fals positiu
double BloomFilter::getProbability(){
    return calculateProbability();
}

//Funcio que retorna si una paraula esta emmagatzemada a l'estructura
bool BloomFilter::findWord(string word){
    return bitsArray[h1(word)] &&
           bitsArray[h2(word)] &&
           bitsArray[h3(word)] &&
           bitsArray[h4(word)] &&
           bitsArray[h5(word)] &&
           bitsArray[h6(word)];
}

//Funcio que afegeix una paraula a l'estructura
void BloomFilter::addWord(string word){
    bool exists = 1;
    exists = exists and bitsArray[h1(word)] and bitsArray[h2(word)] and bitsArray[h3(word)]
            and bitsArray[h4(word)] and bitsArray[h5(word)] and bitsArray[h6(word)];

    if (!exists){
        this->wordsToAdd.push_back(word);
        this->n = wordsToAdd.size();
        //Probabilitat massa alta, es reseteja el vector dels hash
        if(calculateProbability()>0.05 and lengthOfArray()!=this->m){
            this->m=lengthOfArray();
            this->p=calculateProbability();
            fill(bitsArray.begin(), bitsArray.end(), 0);
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