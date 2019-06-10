#include "busca.h"
#include "indice_invertido_.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>

using std::vector;
using std::ifstream;
using std::cout;


rankingCos::rankingCos() {};

rankingCos::rankingCos(const string& busca, indice_invertido e){
	rankear(e);
}

double rankingCos::tf(const string& filename, const string& Pt) {
	ifstream dj(filename);
	if (dj.fail()) {
		cout << "\nInput file opening failed.\n";
		exit(1);
	}

	double tf = 0;
	string palavra;
	while (dj >> palavra) {
		for (int i = 0; i < palavra.length(); i++) {
			if ((palavra[i] >= 'A') && (palavra[i] <= 'Z'))
				palavra[i] += 32;
			if ((palavra[i] >= 'a') && (palavra[i] <= 'z')) {}
			//do nothing
			else
				palavra.erase(palavra.begin() + i);
		}
		if (palavra == Pt)
			tf++;
	}
	return tf;
}

double rankingCos::idf(indice_invertido e, const string& Pt) {       //como passar o objeto indice criado no meu programa? (RESOLVIDO)
	return log(e.nrodocs() / e.ocorrencia(Pt));
}

double rankingCos::coord(const string& filename, const string& Pt, indice_invertido e) {
	return tf(filename, Pt)*idf(e, Pt);
}

void rankingCos::criarEspaço(indice_invertido e) {
	vector<string> docs = e.listadocs();
	for (int i = 0; i < docs.size(); i++) {
		coordenadas[docs[i]];
		for (int j = 0; j < e.tamanho(); j++) {
			if (e.pertence(docs[i], j))
				coordenadas[docs[i]].push_back(coord(docs[i], e.percorre(j), e));
			else
				coordenadas[docs[i]].push_back(0);
		}
	}
}

double rankingCos::sim(const string& filename) {
	double numerador = 0;
	double tamanhof = 0, tamanhob = 0;
	for (int i = 0; i < coordenadas[filename].size(); i++) {
		numerador += coordenadas[filename][i]*coordenadas["busca.txt"][i];//*vetor busca = consulta do usuario;
		tamanhof += coordenadas[filename][i] * coordenadas[filename][i];
		tamanhob += coordenadas["busca.txt"][i] * coordenadas["busca.txt"][i];
	}
	tamanhof = sqrt(tamanhof);
	tamanhob = sqrt(tamanhob);

	return numerador / (tamanhob*tamanhof);
}

void rankingCos::rankear(indice_invertido e) {
	vector<string> docs = e.listadocs();
	for (int i = 0; i < docs.size(); i++) {
		if (docs[i] == "busca.txt") {}
		//do nothing
		else
			rankingCos_[sim(docs[i])].push_back( docs[i]);
	}
}

void rankingCos::imprimir() {
	int count = 1;
	map<double, vector<string>>::iterator it;
	for (it = rankingCos_.begin(); it != rankingCos_.end(); it++) {
		if (it->second.size() > 1) {
			for (string i : it->second) {
				cout << count << ")" << i << " ,";
			}
			cout << std::endl;
		}
		else
			cout << count << ")" << it->second[0] << std::endl;
	}
}