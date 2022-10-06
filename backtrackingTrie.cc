#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
//#include <bits/stdc++.h>

const int N = 10;
const int ch_MAX = 26;

vector < vector<char> > superSopa;
vector <string> wordsFound;


void generateSopa(){
    char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };

    for(int i=0; i<N; ++i){
        superSopa.push_back(vector<char>());
        for(int j=0; j<N; ++j){
            superSopa[i].push_back(alpha[rand() % ch_MAX]);
        }
    }
}

void printSopa(){
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            cout<<superSopa[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool posOk(int i, int j){
    return i>=0 and i<=N and j>=0 and j<=N;
}

bool isWord(string mot){
    //BUSQUEDA ARBRE TERNARI DE CERCA
    return true;
}


void backtracking(vector < vector <bool> > &visited, string mot, int i, int j){
    if (isWord(mot)) wordsFound.push_back(mot);

    if(posOk(i+1,j) and !visited[i+1][j]){
        mot+=superSopa[i+1][j];
        visited[i+1][j]=1;
        backtracking(visited, mot, i+1, j);
        visited[i+1][j]=0;
    }

    if(posOk(i,j+1) and !visited[i][j+1]){
        mot+=superSopa[i][j+1];
        visited[i][j+1]=1;
        backtracking(visited, mot, i, j+1);
        visited[i][j+1]=0;
    }

    if(posOk(i+1,j+1) and !visited[i+1][j+1]){
        mot+=superSopa[i+1][j+1];
        visited[i+1][j+1]=1;
        backtracking(visited, mot, i+1, j+1);
        visited[i+1][j+1]=0;
    }

    if(posOk(i-1,j) and !visited[i-1][j]){
        mot+=superSopa[i-1][j];
        visited[i-1][j]=1;
        backtracking(visited, mot, i-1, j);
        visited[i-1][j]=0;
    }

    if(posOk(i,j-1)){
        mot+=superSopa[i][j-1];
        visited[i][j-1]=1;
        backtracking(visited, mot, i, j-1);
        visited[i][j-1]=0;
    }

    if(posOk(i-1,j-1)){
        mot+=superSopa[i-1][j-1];
        visited[i-1][j-1]=1;
        backtracking(visited, mot, i-1, j-1);
        visited[i-1][j-1]=0;
    }

    if(posOk(i-1,j+1)){
        mot+=superSopa[i-1][j+1];
        visited[i-1][j+1]=1;
        backtracking(visited, mot, i-1, j+1);
        visited[i-1][j+1]=0;
    }

    if(posOk(i+1,j-1)){
        mot+=superSopa[i+1][j-1];
        visited[i+1][j-1]=1;
        backtracking(visited, mot, i+1, j-1);
        visited[i+1][j-1]=0;
    }
}


int main(){
    generateSopa();
    printSopa();
    vector < vector <bool> > visited(N, vector<bool>(N, 0));
    string mot = "";
    backtracking(visited,mot,0,0);
}