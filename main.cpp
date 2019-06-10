#include "indice_invertido_.h"
#include "busca.h"
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::ofstream;

int main(){
	string con;
	ofstream consulta;
	consulta.open("busca.txt");

	cout << "Digite a busca que deseja fazer: ";
	cin >> con;
	consulta << con;

	indice_invertido e("busca.txt");
	e.inserir("d1.txt");
	e.inserir("d2.txt");
	e.inserir("d3.txt");
	

	rankingCos c;
	c.rankear(e);
	c.imprimir();

	return 0;
}