#include <iostream>
#include <string.h>
#include <vector>
#include<math.h>
using namespace std;

class BloomFilter{

    private:

        vector<bool> bitsArray;

        //Mida del vector
        int m;

        //Número de funcions de hash
        int k;

        //Número d'elements esperats a ser insertats al filtre
        int n;

        //Probabilitat d'error
        double p;

        //Vector amb les paraules del diccionari
        vector<string> wordsToAdd;

        int lengthOfArray(){
            return -(this->n * log(this->p))/(pow(log(2),2));
        }

        int numberOfKFunctions(){
            return int((this->m/this->n)*log(2));
        }

        double calculateProbability(){
            double aux = 1.0-1.0/this->m;
            aux = pow(aux, this->k*this->n);
            return pow(1.0 - aux, this->k);
        }

        // Funcio de hash 1
        int h1(string s)
        {
            long long int hash = 0;
            for (int i = 0; i < s.size(); i++)
            {
                hash = (hash + ((int)s[i]));
                hash = hash % this->m;
            }
            return hash;
        }

        // Funcio de hash 2
        int h2(string s)
        {
            long long int hash = 1;
            for (int i = 0; i < s.size(); i++)
            {
                hash = hash + pow(19, i) * s[i];
                hash = hash % this->m;
            }
            return hash % this->m;
        }

        // Funcio de hash 3
        int h3(string s)
        {
            long long int hash = 7;
            for (int i = 0; i < s.size(); i++)
            {
                hash = (hash * 31 + s[i]) % this->m;
            }
            return hash % this->m;
        }

        // Funcio de hash 4
        int h4(string s)
        {
            long long int hash = 3;
            int p = 7;
            for (int i = 0; i < s.size(); i++) {
                hash += hash * 7 + s[0] * pow(p, i);
                hash = hash % this->m;
            }
            return hash;
        }

        // Funcio de hash 5
        int h5(string s)
        {
            long long int hash = 1;
            for (int i = 0; i < s.size(); i++)
            {
                hash = hash + pow(17, i) * s[i];
                hash = hash % this->m;
            }
            return hash % this->m;
        }

        // Funcio de hash 6
        int h6(string s)
        {
            long long int hash = 13;
            for (int i = 0; i < s.size(); i++)
            {
                hash = (hash * 71 + s[i]) % this->m;
            }
            return hash % this->m;
        }

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

    public:

        BloomFilter(){
            this->bitsArray = vector<bool>();
            this->n=0;
            this->m=0;
            this->k=0;
            this->p = 0.01;
        }

        BloomFilter(vector<string> wordsToAdd){
            this->p = 0.01;
            this->n = wordsToAdd.size();
            this->m = lengthOfArray();
            this->k = numberOfKFunctions();
            this->wordsToAdd=wordsToAdd;
            this->bitsArray = vector<bool>(m,0);

            modifyBitsArray();
        }

        int getK(){
            return this->k;
        }

        int getM(){
            return this->m;
        }

        int getN(){
            return this->n;
        }

        double getProbability(){
            return calculateProbability();
        }

        bool findWord(string word){
            bool found=1;
            for(int i=0; i<this->k; ++i){
                switch (i)
                {
                case 0:
                    found=found&&bitsArray[h1(word)];
                    break;
                case 1:
                    found=found&&bitsArray[h2(word)];
                    break;
                case 2:
                    found=found&&bitsArray[h3(word)];
                    break;
                case 3:
                    found=found&&bitsArray[h4(word)];
                    break;
                case 4:
                    found=found&&bitsArray[h5(word)];
                    break;
                case 5:
                    found=found&&bitsArray[h6(word)];
                    break;
                default:
                    break;
                }
            }

            return found;
        }

        void addWord(string word){
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
};

int main(){
    vector<string> entrada = { "abound",   "abounds",       "abundance",
            "abundant", "accessible",    "bloom",
            "blossom",  "bolster",       "bonny",
            "bonus",    "bonuses",       "coherent",
            "cohesive", "colorful",      "comely",
            "comfort",  "gems",          "generosity",
            "generous", "generously",    "genial",
            "bluff",    "cheater",       "hate",
            "war",      "humanity",      "racism",
            "hurt",     "nuke",          "gloomy",
            "facebook", "geeksforgeeks", "twitter" };

    BloomFilter bm = BloomFilter(entrada);
    cout<<bm.findWord("facebook")<<endl;
    cout<<bm.findWord("face")<<endl;
    cout<<bm.findWord("generous")<<endl;
    cout<<bm.findWord("hola")<<endl;

    cout<<bm.getN()<<endl;
    bm.addWord("hola");
   /*bm.addWord("holap");
    bm.addWord("holat");
    bm.addWord("holaf");
    bm.addWord("holag");
    bm.addWord("holad");
    bm.addWord("holas");
    bm.addWord("holaa");
    bm.addWord("holaaaa");
    bm.addWord("holaaaaaa");
    bm.addWord("holqqqqa");
    bm.addWord("howla");
    bm.addWord("hoela");
    bm.addWord("hotttla");
    bm.addWord("holttttta");
    bm.addWord("holtttttttta");
    cout<<bm.getProbability()<<endl;
    cout<<bm.getM()<<endl;
    cout<<bm.getK()<<endl;
    cout<<bm.getN()<<endl;

    bm.addWord("holplfa");
    cout<<bm.getProbability()<<endl;
    cout<<bm.getM()<<endl;
    cout<<bm.getK()<<endl;
    cout<<bm.getN()<<endl;
    bm.addWord("holllla");
    bm.addWord("holaaaaaa");
    bm.addWord("holxxxa");
    bm.addWord("holcccca");
    bm.addWord("holvvvva");
    bm.addWord("holaqqqq");
    bm.addWord("houiola");
    bm.addWord("holsjdla");
    bm.addWord("holqlwjea");

    cout<<bm.getN()<<endl;
    cout<<bm.getProbability()<<endl;
    cout<<bm.findWord("hola")<<endl;*/
}
