//////////////////////////////////////////////////////////////////////////////////////////////
//Bibliotecas:
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <cctype>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
//Registro:

struct Pizzaria {
	char nome[40]{};
	int qntd{};
	double preco{};
};

//Inicializações das Funções:

void menu();
void Pedir(Pizzaria*, int);
void Listar(Pizzaria*, int);
void Padronizar(Pizzaria*, int);
Pizzaria* Adicionar(Pizzaria*, int*, int*,int*);
Pizzaria* Excluir(Pizzaria*, int*, int);
void GerarRecibo(Pizzaria*, int, Pizzaria*, int, char*);
