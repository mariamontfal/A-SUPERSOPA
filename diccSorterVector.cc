#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> Dictionary;

void CreateDictionary(){
	char cadena[128];
	ifstream fe("./EjemploDic.txt");

	while(!fe.eof()){
		fe >> cadena;
		Dictionary.push_back(cadena);
	}
}

bool CompareStrings(string a, string b){ 
	if(a.size() != b.size()) {
		return false;
	}
	for(int i=0; i < a.size();++i){
		int va, vb;

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
			vb = a[i] - 'A';
		}

		if(va != vb) return false;
	}
	return true;
}

int RecalculateInf(int inf,int sup,int pivote,string n){
	cout << "RecalculateInf " << inf << " " << sup << " " << pivote << " " << n << endl;
	if(inf > sup){
		return -1;
	}
	else{
		int central = (inf+sup)/2;
		cout << "central " << central << endl;
		cout << "palabra " << Dictionary[central] << endl << endl;
		if(n == Dictionary[central] && Dictionary[central].size() >= pivote && Dictionary[central][pivote] - Dictionary[central-1][pivote] == 1)
			return central;
		else{
			if(Dictionary[central].size() >= pivote && n <= Dictionary[central][pivote]){
				return RecalculateInf(inf,central-1,pivote,n);
			}
			else {
				return RecalculateInf(central+1,sup,pivote,n); 
			}
		}
	}
}

int RecalculateSup(int inf,int sup,int pivote,char n){
	cout << "RecalculateSup " << inf << " " << sup << " " << pivote << " " << n << endl;
	if(inf > sup){
		return -1;
	}
	else{
		int central = (inf+sup)/2;
		cout << "central " << central << endl;
		cout << "palabra " << Dictionary[central] << endl;
		if(n - Dictionary[central][pivote] == -1)
			return central;
		else{
			if(n < Dictionary[central][pivote]){
				return RecalculateSup(central+1,sup,pivote,n);
			}
			else
				return RecalculateSup(inf,central-1,pivote,n);
		}
	}
}

void WriteDicctionary(){
	cout << "Escribimos diccionario" << endl;
	for(int i = 0; i < Dictionary.size();++i){
		cout << Dictionary[i] << endl;
	}
}

/*
Pre:
	inf: valor minimo de la búsqueda
	sup: valor máximo de la búsqueda
	n: es la palabra a buscar
	pivote: pivote de comparación con el string 
Post:
	-1 si la palabra no esta en el diccionario
	>=0 si la palabra esta en el diccionario
Coste:
	log(n)
Certeca: 
	Nos aseguramos de buscar la palabra en todo el diccionario.
*/
int FindDicctionary(int inf, int sup, string n, int pivote){
	cout << "valores " << inf << " " << sup << " " << n << " " << pivote << endl; 
	if(inf > sup)
		return -1;
	else {
		int central;
		central = (inf + sup)/2;
		cout << "central " << central << endl; 
		cout << "palabra central " << Dictionary[central] << endl;  
		cout << "palabra inferior " << Dictionary[inf] << endl;  
		cout << "palabra superior " << Dictionary[sup] << endl;  
		if(CompareStrings(n, Dictionary[central])){
			return central;
		}
		else{
			cout << endl;
			if(n[pivote] == Dictionary[central][pivote]){
				int newinf = RecalculateInf(inf,sup,pivote,n[pivote]);
				cout << "inf " << newinf << endl;
				int newsup = RecalculateSup(newinf,sup,pivote,n[pivote]);
				cout << "sup " << newsup << endl;
				++pivote;
				return FindDicctionary(newinf,newsup,n,pivote);
			}
			else if(n[pivote] > Dictionary[central][pivote])
				return FindDicctionary(central+1,sup,n,pivote);
			else
				return FindDicctionary(inf,central-1,n,pivote);
		}
	}
}
/*
Problemas:
	Tengo un problema, cuando me muevo por el pivote, tengo que volver a recalcular
	los inf y sup, para asegurarme de que las palabras que comparon estan dentro
	de Dicctionary[inf] y Dictionaty[sup] 
*/



int FindDicctionaryIterative(string n){
	for(int i=0;i < Dictionary.size(); ++i){
		if(CompareStrings(n,Dictionary[i])){
			return i;
		}
	}
	return -1;
}

int main(){
	CreateDictionary();
	//WriteDicctionary();
	cout << "Escribe una palabra para buscar" << endl;
	string word;
	bool end = false;
	while(!end && cin >> word){
		if(word == "!quit"){
			end = true;
		}
		else{
			int n;
			n = FindDicctionary(0,Dictionary.size(),word,0);
			if(n >= 0){
				cout << "Encontrada" << endl;
				cout << "La palabra esta en la posición " <<  n << endl;
			}
			else{
				cout << "Esta palabra no existe" << endl;
			}
			cout << "Escribe otra palabra si queires saber si existe" << endl;
			cout << "!quit para salir" << endl;
		}
	}

	cout << "Hemos acabado, adios!" << endl;
	return 0;
}
