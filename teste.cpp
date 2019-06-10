#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "indice_invertido_.h"
#include "busca.h"
#include <cmath>


class teste {
   public:

	   static map<string, set<string>> indic(const indice_invertido &e) {
		   return e.indice;
	   }

	   static vector<string> listadocs(const indice_invertido &e) {
		   return e.listadocs_;
	   }

	   static double nrdocs(const indice_invertido &e) {
		   return e.nrodocs_;
	   }

	   static map<string, vector<double>> coordena(const rankingCos &c) {
		   return c.coordenadas;
	   }

	   static map<double, vector<string>> rankinCoss(const rankingCos& c) {
		   return c.rankingCos_;
	   }
};

TEST_SUITE("indice_invertido") {
	TEST_CASE("construtor com 1 arquivo") {
		indice_invertido e("d1.txt");
		//e.imprimirr();
		CHECK(teste::indic(e).count("quem"));
		CHECK(teste::indic(e).count("casa"));
		CHECK(teste::indic(e).count("quer"));
		CHECK(teste::indic(e).count("apartamento"));
		CHECK(teste::indic(e).count("porem"));
		CHECK(teste::listadocs(e)[0] == "d1.txt");
		CHECK(teste::nrdocs(e) == 1);
	}

	TEST_CASE("funcao inserir 1 arquivo") {
		indice_invertido e("d1.txt");
		e.inserir("d2.txt");
		CHECK(teste::indic(e).count("saram"));
		CHECK(teste::indic(e).count("todos"));
		CHECK(teste::indic(e).count("entrar"));
		CHECK(teste::indic(e).count("quem"));
		CHECK(teste::indic(e).count("em"));
		CHECK(teste::listadocs(e)[1] == "d2.txt");
		CHECK(teste::nrdocs(e) == 2);
	}

	TEST_CASE("teste da funcao tamanho") {
		indice_invertido e("d1.txt");
		CHECK(e.tamanho() == 7);
	}

	TEST_CASE("teste da funcao ocorrencia") {
		indice_invertido e("d1.txt");
		e.inserir("d2.txt");
		e.inserir("d3.txt");
		CHECK(e.ocorrencia("casa") == 2);
		CHECK(e.ocorrencia("apartamento") == 2);
		CHECK(e.ocorrencia("quem") == 3);
		CHECK(e.ocorrencia("ningum") == 3);
	}

	TEST_CASE("teste da funcao pertence") {
		indice_invertido e("d1.txt");
		e.inserir("d2.txt");
		e.inserir("d3.txt");
		CHECK(e.pertence("d1.txt", 2) == 0);
		CHECK(e.pertence("d2.txt", 0) == 0);
		CHECK(e.pertence("d1.txt", 5) == 1);
		CHECK(e.pertence("d3.txt", 0) == 1);
	}

	TEST_CASE("teste da funcao percorre") {
		indice_invertido e("d1.txt");
		e.inserir("d2.txt");
		e.inserir("d3.txt");
		CHECK(e.percorre(0) == "apartamento");
		CHECK(e.percorre(6) == "no");
	}
}


TEST_SUITE("BUSCA") {
	indice_invertido k("d1.txt");//declaracao de indice "global" para as funcoes de busca

	TEST_CASE("term frequency (tf) ") {
		rankingCos c;
		CHECK(c.tf("d1.txt", "apartamento") == 1);
		CHECK(c.tf("d1.txt", "casa") == 4);
		CHECK(c.tf("d1.txt", "quer") == 3);
		CHECK(c.tf("d1.txt", "ningum") == 2);
	}

	TEST_CASE("inverso da frequencia (idf)") {
		rankingCos c;
		k.inserir("d2.txt");
		k.inserir("d3.txt");
		CHECK(c.idf(k, "casa") == log(3.0 / 2.0));
		
	}

	TEST_CASE("calculo da coordenada") {
		rankingCos c;
		CHECK(c.coord("d1.txt", "casa", k) == 4.0 * log(3.0 / 2));

	}

	TEST_CASE("criacao do espaço vetorial") {
		rankingCos c;
		c.criarEspaço(k);
		CHECK(teste::coordena(c).count("d1.txt") == 1);
		CHECK(teste::coordena(c)["d1.txt"].size() == k.tamanho());

	}

	TEST_CASE("funcao similaridade") {
		rankingCos c;
		k.insereConsulta("busca.txt");
		c.criarEspaço(k);
		//CHECK(c.sim("d1.txt") == 0.54);
	}

	TEST_CASE("rakear!") {
		rankingCos c;
		k.insereConsulta("busca.txt");
		c.criarEspaço(k);
		c.rankear(k);
		c.imprimir();
		CHECK_FALSE(teste::rankinCoss(c).size() == 0);
	}
}