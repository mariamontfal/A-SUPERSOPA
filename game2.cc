#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <chrono>
#include<tuple>

using namespace std;
using namespace std::chrono;

struct Edge {
	int i;
	int j;
	char a;
};

vector<string> palabras;
vector<vector<Edge>> Edges;

vector<vector<char>> Wordsearch 
{
{'N','O','E'},
{'E','V','S'},
{'X','B','K'}
};


/*{
{'a','b','c'},
{'d','e','f'},
{'g','h','i'}
};*/



struct Edge CreateEdge(int x, int y, char a) {
	struct Edge edge;
	edge.i = x;
	edge.j = y;
	edge.a = a;
	return edge;
}

/*
PRE:
	a,b son de strings no vacios
POST:
	El resultado es la comparación de dos palabras
	si a > b = 1
	si a = b = 0
	si a < b = -1
*/

/*
int CompareStrings(char a, char b){
	//cout << "CompararString " << a << " " << b << endl;
	int va, vb;
	if(a >= 'a' && a <= 'z'){
		va = a - 'a';
	}
	else if(a >= 'A' && a <= 'Z'){
		va = a - 'A';
	}
	if(b >= 'a' && b <= 'z'){
		vb = b - 'a';
	}
	else if(b >= 'A' && b <= 'Z'){
		vb = b - 'A';
	}

	if(va == vb)
		return 0;
	if(va > vb)
		return 1;

	return -1;
}

pair<int,int> FindWordIterative(string word) {
	for(int i = 0; i < Wordsearch.size(); ++i){
		for(int j = 0; j < Wordsearch.size(); ++j){
			if(Wordsearch.size()-j > word.size()){
				if(Wordsearch[i][j] == word[0]){
					cout << endl << "Entro aqui" << endl;
					cout << "i y j " << i << " " << j << endl;
					if(recorrer(word,i,j))
						return make_pair(i,j);
				}
			}
		}
	}
	return make_pair(-1,-1);

}

bool recorrer(string word, int x, int y){
	cout << "Recorrer" << endl;
	int yy;
	for(int i=0; i < word.size(); ++i){
		yy = y+i;
		cout << "word: " << word[i] << " letra " << Wordsearch[x][yy] << endl;  
		if(CompareStrings(word[i],Wordsearch[x][yy]) != 0){
			return false;
		}
	}
	return true;
}

*/

void WriteWordSearch(){
	for (int i = 0; i < Wordsearch.size(); ++i)
	{
		for (int j = 0; j < Wordsearch.size(); ++j)
		{
			if(j == 0) cout << i << " ";
			if(j == 0 && i < 10) cout << " ";
			cout << Wordsearch[i][j];
			if(j < Wordsearch.size()-1){
				cout << ", ";
			}
		}
		cout << endl;
	}
}

bool InMatrix(int x, int y)
{
	return x >= 0 && y >= 0 && x < Wordsearch.size() && y < Wordsearch.size(); 
}

vector<string> FindWordBackTracking(int n, vector<vector<bool>> &visit,int x,int y) {
	vector<string> combinations;
	if(n == 0){
		for(auto a : Edges[x+y]){
			if(!visit[a.i][a.j]){
				string word;
				word.push_back(Wordsearch[x][y]);
				word.push_back(Wordsearch[a.i][a.j]);
				combinations.push_back(word);
			}
		}
		return combinations;
	}
	else{
		vector<vector<bool>> visitcopy;
		visitcopy.insert(visitcopy.end(),visit.begin(),visit.end());
		visitcopy[x][y] = true;
		for(auto a : Edges[x+y]){
			if(!visit[a.i][a.j]){
				for(auto comb : FindWordBackTracking(n-1,visitcopy,a.i,a.j)){
					string word;
					word.push_back(Wordsearch[x][y]);
					word += comb;
					combinations.push_back(word);
				}
			}
		}
		return combinations;
	}
}

void printEdge(Edge x)
{
	cout << "posicion x: " << x.i << endl;
	cout << "posicion y: " << x.j << endl;
	cout << "char: " << x.a << endl;  
}


void CreateEdges(){
	Edges.resize(Wordsearch.size()*Wordsearch.size()); // NOTA: No es Wordsearch[0].size() * Wordsearch[0].size() ??? 
	for(int i = 0; i < Wordsearch.size(); ++i){
		for(int j = 0; j < Wordsearch[i].size(); ++j){
			if(InMatrix(i-1,j)){
				Edges[i+j].push_back(CreateEdge(i-1,j,Wordsearch[i-1][j]));
			}
			if(InMatrix(i+1,j)) {
				Edge edge = CreateEdge(i+1,j,Wordsearch[i+1][j]);
				Edges[i+j].push_back(edge);
			}
			if(InMatrix(i,j+1)) {
				Edges[i+j].push_back(CreateEdge(i,j+1,Wordsearch[i][j+1]));
			}
			if(InMatrix(i,j-1)){
			 Edges[i+j].push_back(CreateEdge(i,j-1,Wordsearch[i][j-1]));
			}
			if(InMatrix(i-1,j-1)) {
				Edges[i+j].push_back(CreateEdge(i-1,j-1,Wordsearch[i-1][j-1]));
			}
			if(InMatrix(i-1,j+1)) {
				Edges[i+j].push_back(CreateEdge(i-1,j+1,Wordsearch[i-1][j+1]));
			}
			if(InMatrix(i+1,j-1)) {
				Edges[i+j].push_back(CreateEdge(i+1,j-1,Wordsearch[i+1][j-1]));
			}
			if(InMatrix(i+1,j+1)) {
				Edges[i+j].push_back(CreateEdge(i+1,j+1,Wordsearch[i+1][j+1]));
			}
		}
	}
}


void WritePalabras(){
	for(string s : palabras){
		cout << s << endl;
	}
}

void WriteVectorString(vector<string> p){
	for(string pp : p){
		cout << pp << endl;
	}
}


int main(){
	cout << Wordsearch.size();
	return 0;
	auto start = high_resolution_clock::now();
	cout << "Este Juego encunetra las palabras en la sopa de letras" << endl;
	CreateEdges();
	int total = Wordsearch.size() * Wordsearch.size();
	total = total > 50 ? 50 :  total;
	for(int n=0;n < total; ++n){
		for(int i= 0; i < Wordsearch.size(); ++i){
			for(int j = 0; j < Wordsearch[i].size(); ++j){
				vector<vector<bool>> Visited(Wordsearch.size(),vector<bool>(Wordsearch[i].size(),false));
				auto sortP = FindWordBackTracking(n,Visited,i,j);
				palabras.insert(palabras.end(),sortP.begin(),sortP.end());		
			}
		}
	}
	WritePalabras();

	auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
			    cout << endl;
}
