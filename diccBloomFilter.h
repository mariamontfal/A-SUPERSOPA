       #ifndef DICCBLOOMFILTER_H
       #define DICCBLOOMFILTER_H

       #include "config.h"

       #include <iostream>
       #include <string.h>
       #include <vector>
       #include <math.h>

       class BloomFilter {
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

                   int lengthOfArray();

                   int numberOfKFunctions();

                   double calculateProbability();

                   // Funcio de hash 1
                   int h1(string s);

                   // Funcio de hash 2
                   int h2(string s);

                   // Funcio de hash 3
                   int h3(string s);

                   // Funcio de hash 4
                   int h4(string s);

                   // Funcio de hash 5
                   int h5(string s);

                   // Funcio de hash 6
                   int h6(string s);

                   void modifyBitsArray();

               public:

                   BloomFilter();

                   ~BloomFilter();

                   BloomFilter(vector<string> wordsToAdd);

                   int getK();

                   int getM();

                   int getN();

                   double getProbability();

                   bool findWord(string word);

                   void addWord(string word);
       };
       #endif

