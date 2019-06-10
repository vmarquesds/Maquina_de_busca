#ifndef INDICE_EX
#define INDICE_EX

#include <string>
#include <map>
#include <set>
#include <fstream>
#include <vector>

using std::string;
using std::map;
using std::set;
using std::ifstream;
using std::vector;

class indice_invertido
{
public:
	//cria um indice vazio
	indice_invertido();

	//cria um indice com as palavras do documento
	indice_invertido(const string& filename);

	//insere as palavras de um novo documento ao indice
	void inserir(const string& filename);

	//tamanho do indice (quantas palavras possui)
	double tamanho();

	//nro de documentos onde certa palavra ocorreu
	double ocorrencia(const string& palavra);

	//retorna o nro de documentos da coleção
	double nrodocs();

	//retorna a lista dos documentos
	vector<string> listadocs();

	//verifica se um certo documento possui a palavra da posição i ou não (começa a conta de 0)
	bool pertence(const string& dj, const int& i);

	//retorna a palavra da posição i
	string percorre(const int& i);

	//insere o documento criado para a consulta do usuario dentro do indice (ATENCAO! NOMEAR O NOME DO ARQUIVO COMO SENDO BUSCA)
	void insereConsulta(const string& filenamec);

	void imprimirr();


	~indice_invertido();

private:

	double nrodocs_;

	vector<string> listadocs_;

	map<string, set<string>> indice; //mapa em que a chave eh a palavra e o valor eh uma lista de documentos nos quais essa palavra aparece!
	map<string, set<string>>::iterator it; //iterator

	//int quantidade_; //numero de palavras no indice
	
	friend class teste;
};

#endif INDICE_EX