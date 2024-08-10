#include <iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////
//Registros;
struct Datas{
	int dia{},
		mes{},
		ano{};
};

struct Biblioteca{
	Datas DatasEmprestimos{};
	char matricula[11]{},
		identificador[6]{};
};

//////////////////////////////////////////////////////////////////////////////////////////////
//funções com operator: 
istream& operator>>(istream&, Datas&);

ostream& operator<<(ostream&, Datas&);

istream& operator>>(istream&, Biblioteca&);

int operator-(Datas&, Datas&);

//////////////////////////////////////////////////////////////////////////////////////////////
//funções normais:
void linha(char, int);

void resumo(Biblioteca*, Datas*);

double SomaMultas(Biblioteca[], Datas ,int );
