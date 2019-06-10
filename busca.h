#ifndef BUSCA_ex
#define BUSCA_ex

#include<cmath>
#include<string>
#include<fstream>  
#include<vector>
#include "indice_invertido_.h"

//COMO ARMAZENAR AS COORDENADAS?

using std::string;
using std::ifstream;
using std::vector;
using std::map;

class rankingCos {

public:

	//cria um ranking vazio
	rankingCos();

	//cria um ranking cosseno para um determinada busca e para uma certa colecao de documentos
	rankingCos(const string& busca, indice_invertido e);

	//formas de se achar a coordenada de um documento
	//frequencia do termo dentro de um documento dj qualquer
	double tf(const string& filename, const string& Pt);

	//inverso da frequencia nos documentos, idf=log(N/nt) N = nro total de docs, nt = nro de docs onde a palavra Pt ocorreu, Pt eh a palavra
	double idf(indice_invertido e, const string& Pt);

	//calcula a coordenada do documento dj no eixo Pt
	double coord(const string& filename, const string& Pt, indice_invertido e);

	//cria o espaço vetorial dos documentos, ou seja, calcula suas coordenadas as armazena
	void criarEspaço(indice_invertido e);


	//rankear os documentos
	//calcula o cosseno entre os documentos
	double sim(const string& filename);

	//cria a estrutura de dados do ranking
	void rankear( indice_invertido e );

	//imprime a estrutura do ranking
	void imprimir();

private:

	//estrutura de dados para as coordenadas dos documentos
	map<string, vector<double>> coordenadas;

	//estrutura de dados para o ranking cosseno
	map<double, vector<string>> rankingCos_;

	friend class teste;
};


#endif BUSCA_ex