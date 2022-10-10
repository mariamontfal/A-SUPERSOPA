#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <time.h>
#include <chrono>
#include "diccSortedVector.cc"
#include "diccTrie.cc"
#include "diccBloomFilter.cc"
#include "diccDHashing.cc"
using namespace std;

string FICHERO_ENTRADA;
unsigned int N = 8;
uint64_t SEED = -1;
unsigned int maxWordLength = 10;
const unsigned int ch_MAX = 26;

enum ED {
    ED_SORTED_VECTOR,
    ED_TERNARY_SEARCH_TREE,
    ED_BLOOM_FILTER,
    ED_DOUBLE_HASHING
};

ED EstructuraDatosEnUso;

diccSortedVector obj_diccSortedVector = diccSortedVector();
diccTrie obj_diccTrie = diccTrie();
diccDHashing obj_diccDHashing = diccDHashing();
diccBloomFilter obj_diccBloomFilter = diccBloomFilter();

char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                      'h', 'i', 'j', 'k', 'l', 'm', 'n',
                      'o', 'p', 'q', 'r', 's', 't', 'u',
                      'v', 'w', 'x', 'y', 'z' };

vector <vector<char> > superSopa;
vector <vector<bool> > visited;
set <string> wordsFound;

void generateSopa(){
    if(SEED == uint64_t(-1)) SEED = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    srand(SEED);    
    for(int i=0; i<N; ++i){
        superSopa.push_back(vector<char>());
        visited.push_back(vector<bool>());
        for(int j=0; j<N; ++j){
            superSopa[i].push_back(alpha[rand() % ch_MAX]);
            visited[i].push_back(0);
        }
    }
}

void printSopa(){
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            std::cout<<superSopa[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool posOk(int i, int j){
    return i>=0 and i<N and j>=0 and j<N;
}

SearchResult findWord(string mot) {
    return SearchResult::WORD_NOT_FOUND;
}

void backtracking(string mot, int i, int j){

    if(!posOk(i,j) || visited[i][j] || mot.size() >= maxWordLength) return;

    SearchResult sr;
    switch(EstructuraDatosEnUso) {
        case ED::ED_SORTED_VECTOR:
            sr = obj_diccSortedVector.findWord(mot + superSopa[i][j]);
            break;
        case ED::ED_TERNARY_SEARCH_TREE:
            sr = obj_diccTrie.findWord(mot + superSopa[i][j]);
            break;
        case ED::ED_BLOOM_FILTER:
            sr = obj_diccBloomFilter.findWord(mot + superSopa[i][j]);
            break;
        case ED::ED_DOUBLE_HASHING:
            sr = obj_diccDHashing.findWord(mot + superSopa[i][j]);
            break;
        default:
            sr = obj_diccSortedVector.findWord(mot);   
            break;
    }

    switch(EstructuraDades::evalSearchResult(sr)) {
        case BacktrackingAction::ADD_WORD_AND_SEARCH:
            wordsFound.insert(mot + superSopa[i][j]);
        case BacktrackingAction::CONTINUE_SEARCHING:
            visited[i][j] = true;
            backtracking(mot + superSopa[i][j], i+1, j);
            backtracking(mot + superSopa[i][j], i+1, j+1);
            backtracking(mot + superSopa[i][j], i,   j+1);
            backtracking(mot + superSopa[i][j], i+1, j-1);
            backtracking(mot + superSopa[i][j], i,   j-1);
            backtracking(mot + superSopa[i][j], i-1, j-1);
            backtracking(mot + superSopa[i][j], i-1, j);
            backtracking(mot + superSopa[i][j], i-1, j+1);
            visited[i][j] = false;
            break;
        case BacktrackingAction::END_SEARCH:
            return;
        default:
            return;
    }
    
}

void SearchSoup(bool debugPrints = true) {
    
    if(debugPrints) printSopa();
    
    wordsFound = set<string>();
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            visited = vector<vector<bool> >(N, vector<bool>(N, 0));
            string mot = "";
            backtracking(mot,i,j);
        }
    }

    if(debugPrints) {
        cout << "Found " << wordsFound.size() << " words." << endl;
    }
    
}

void initializeProgram() {

    double initializeDuration = 0.0;  

    // Inicializacion del programa

    clock_t begin_initialization = clock();

    string newWord;
    ifstream file(FICHERO_ENTRADA);

    if(!file) throw invalid_argument("El fichero de entrada no se ha encontrado...");

    while(!file.eof()){
        file >> newWord;
        obj_diccSortedVector.addWord(newWord);
        obj_diccTrie.addWord(newWord);
        obj_diccDHashing.addWord(newWord);
    }
    //obj_diccBloomFilter = diccBloomFilter(obj_diccSortedVector.data());

    generateSopa();

    clock_t end_initialization = clock();

    cout << "Time initialization: " << initializeDuration << " seconds."  << endl;


}

void executeProgram() {
  
    double executionDuration = 0.0;

    // Ejecucion del programa

    clock_t begin_execution = clock();

    SearchSoup();
 
    clock_t end_execution = clock();
 
    executionDuration = (double)(end_execution - begin_execution) / CLOCKS_PER_SEC;
 
    cout << "Time execution: " << executionDuration << " seconds." << endl;

}

void WriteFile(){
    fstream my_file;
    string nameFile;
    switch(EstructuraDatosEnUso) {
        case ED::ED_SORTED_VECTOR:
            nameFile = "./Ejemplos/Vector/VectorN" + to_string(N) + "M" + to_string(maxWordLength) +"Words.txt";
            break;
        case ED::ED_TERNARY_SEARCH_TREE:
            nameFile = "./Ejemplos/Trie/TrieN" + to_string(N) + "M" + to_string(maxWordLength) +"Words.txt";
            break;
        case ED::ED_BLOOM_FILTER:
            nameFile = "./Ejemplos/Blom/BlomN" + to_string(N) + "M" + to_string(maxWordLength) +"Words.txt";
            break;
        case ED::ED_DOUBLE_HASHING:
            nameFile = "./Ejemplos/DHash/DhasN" + to_string(N) + "M" + to_string(maxWordLength) +"Words.txt";
            break;
        default:
            nameFile = "./Ejemplos/Vector/VectorN" + to_string(N) + "M" + to_string(maxWordLength) +"Words.txt";
            break;
    }
    my_file.open(nameFile, ios::out);
    if (!my_file) {
        cout << "File not created!";
    }
    else {
        for(string a : wordsFound){
            my_file << a << endl;
        }
        my_file.close();
    }
}

int main(int argc, char *argv[]){

    if(argc > 5) throw invalid_argument("Demasiados argumentos de programa...");
    if(argc > 4) SEED = std::atoi(argv[4]);
    if(argc > 3) maxWordLength = std::atoi(argv[3]);
    if(argc > 2) N = std::atoi(argv[2]);
    if(argc > 1) FICHERO_ENTRADA = argv[1];

    initializeProgram();
    EstructuraDatosEnUso = ED::ED_TERNARY_SEARCH_TREE;
    executeProgram();
    WriteFile();

    return 0;

}