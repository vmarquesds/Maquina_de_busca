#include "pch.h"
#include "indice_invertido_.h"
#include <string>
#include <fstream>
#include <set>
#include <iostream>

using std::ifstream;
using std::cout;

indice_invertido::indice_invertido()
{
	nrodocs_ = 0;
}

indice_invertido::indice_invertido(const string& filename) {
	ifstream docum;
	docum.open(filename);
	if (docum.fail()) { 
		cout << "Input file opening failed.\n";      
		exit(1); 
	}

	
	string palavras;
	set<string> vocabulario;

	while (docum >> palavras) {
		for (int i = 0; i < palavras.length(); i++) {
			if (palavras[i] >= 'A' && palavras[i] <= 'Z')
				palavras[i] += 32;
			if(palavras[i] >= 'a' && palavras[i] <= 'z'){}
				//do nothing
			else
				palavras.erase(palavras.begin() + i);
		}
		vocabulario.insert(palavras);                //PARA FAZER: 1)converter os caracteres (feito, mas meia boca)
	}

	for (string e : vocabulario) {
		indice[e].insert(filename);					//alterar, como pegarei o nome do documento? (RESOLVIDO!)
	}
	docum.close();

	listadocs_.push_back(filename);
	nrodocs_++;
}

void indice_invertido::inserir(const string& filename) {
	ifstream docum;                      //abro o documento dentro da fução, dessa forma consigo o nome dele
	docum.open(filename);
	if (docum.fail()) {
		cout << "Input file opening failed.\n";
		exit(1);
	}

	string palavras;

	set<string> vocabulario;
	while (docum >> palavras) {     //garantia de que nao havera repetição de palavras dentro do map
		for (int i = 0; i < palavras.length(); i++) {
			if (palavras[i] >= 'A' && palavras[i] <= 'Z')
				palavras[i] += 32;
			if (palavras[i] >= 'a' && palavras[i] <= 'z') {}
			//do nothing
			else
				palavras.erase(palavras.begin() + i);
		}
		vocabulario.insert(palavras);
	}

	for (string e : vocabulario) {
		indice[e].insert(filename);   //sintaxe adequada para guardar os documentos nos quais a palavra aparece
	}
	docum.close();

	listadocs_.push_back(filename);
	nrodocs_++;
}

double indice_invertido::tamanho() {
	return indice.size();
}

double indice_invertido::ocorrencia(const string& palavra) {
	return indice[palavra].size();                       //tamanho do set de documentos daquela palavra
}

double indice_invertido::nrodocs() {
	return nrodocs_;
}

vector<string> indice_invertido::listadocs() {
	return listadocs_;
}

bool indice_invertido::pertence(const string& dj, const int& i) {
	//it = indice.find(k);
	int count = 0;
	set<string> lista;// = it->second;
	for (it = indice.begin(); it != indice.end(); it++) {
		lista = it->second;
		if (count == i) {
			if (lista.count(dj) != 0)
				return true;
			else
				return false;
		}

		count++;
	}
}

string indice_invertido::percorre(const int& i) {
	int count = 0;
	for (it = indice.begin(); it != indice.end(); it++) {
		if (count == i)
			return it->first;
		count++;
	}
}

void indice_invertido::insereConsulta(const string& filenamec) {
	inserir(filenamec);
}


void indice_invertido::imprimirr() {
	for (it = indice.begin(); it != indice.end(); it++) {
		cout << it->first << std::endl;
	}
}

indice_invertido::~indice_invertido()
{
}
