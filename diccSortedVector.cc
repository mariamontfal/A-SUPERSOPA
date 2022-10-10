#ifndef DICC_SORTED_VECTOR
#define DICC_SORTED_VECTOR

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include "ED.cc"


using namespace std;

class diccSortedVector : EstructuraDades {

private:

    vector<string> Dictionary;

    /*
    PRE:
        a,b son de strings no vacios
    POST:
        El resultado es la comparación de dos palabras
        si a > b = 1
        si a = b = 0
        si a < b = -1
    */
    int CompareStrings(string a, string b){
        int va, vb; 
        for(int i=0; i < a.size();++i){
            va = 0;
            vb = 0;
            if(a[i] >= 'a' && a[i] <= 'z'){
                va = a[i] - 'a';
            }
            else if(a[i] >= 'A' && a[i] <= 'Z'){
                va = a[i] - 'A';
            }
            if(b[i] >= 'a' && b[i] <= 'z'){
                vb = b[i] - 'a';
            }
            else if(b[i] >= 'A' && b[i] <= 'Z'){
                vb = b[i] - 'A';
            }
            if(va > vb || b.size() <= i){
                return 1;
            }
            if(va < vb)
                return -1;
        }
        if(a.size() == b.size())
            return 0;
        return -1;
    }

    /*
    Pre:
        inf: valor minimo de la búsqueda
        sup: valor máximo de la búsqueda
        n: es la palabra a buscar
    Post:
        -1 si la palabra no esta en el diccionario
        >=0 si la palabra esta en el diccionario
    */
    SearchResult FindDicctionary(int inf, int sup, string n){
        //cout << "valores " << inf << " " << sup << " " << n << " " << endl; 
        if(inf > sup)
        return SearchResult::WORD_NOT_FOUND;
        else {
            int central;
            central = (inf + sup)/2;
            int cpm = n.compare(Dictionary[central]);
            /*cout << "central " << central << endl; 
            cout << "comparar " << cpm << endl;
            cout << "palabra central " << Dictionary[central] << endl;  
            cout << "palabra inferior " << Dictionary[inf] << endl;  
            cout << "palabra superior " << Dictionary[sup] << endl;*/
            if(cpm == 0){
                return SearchResult::WORD_FOUND;
            }
            else{
                if(cpm > 0)
                    return FindDicctionary(central+1,sup,n);
                else
                    return FindDicctionary(inf,central-1,n);
            }
        }
    }

public:

    diccSortedVector() { 
        Dictionary = vector<string>();
    }

    void addWord(string word) {
        Dictionary.push_back(word);
    }

    void CreateDictionary(){
        char cadena[128];
        ifstream fe("./EjemploDic.txt");

        while(!fe.eof()){
            fe >> cadena;
            Dictionary.push_back(cadena);
        }
    }

    void WriteDicctionary(){
        cout << "Escribimos diccionario" << endl;
        for(int i = 0; i < Dictionary.size();++i){
            cout << Dictionary[i] << endl;
        }
    }

    SearchResult findWord(string n){
        return FindDicctionary(0,Dictionary.size()-1,n);
    }

    vector<string> data() {
        return Dictionary;
    }

};

#endif