#include <iostream>
#include "simd.h"
#include "cripto.h"

int main()
{
	using namespace std;
	setlocale(LC_ALL, "portuguese");

	int n1, n2, n3, n4, n5, n6, n7, n8;
	char parentese1, virgula, parentese2;

	//Entrada de dados;
	cin >> parentese1 >> n1 >> virgula >> n2 >> virgula >> n3 >> virgula >> n4 >> parentese2; // [002,010,015,030]  teste :[100,010,015,030]
	cin >> parentese1 >> n5 >> virgula >> n6 >> virgula >> n7 >> virgula >> n8 >> parentese2; // [001,005,008,002]
	cout << endl;
	cout << endl;

	cout << "Operandos em 32 bits = " << armazena(n1, n2, n3, n4) << endl; //chamada da função armazena para o primeiro bloco
	cout << "Operandos em 32 bits = " << armazena(n5, n6, n7, n8) << endl; //chamada da função armazena para o segundo bloco
	cout << endl << endl;

	cout << "Soma em 32 bits = ";
	cout << soma(armazena(n1, n2, n3, n4), armazena(n5, n6, n7, n8), 4); // chamando função soma para somar os dois blocos
	cout << endl;

	cout << "Mult em 32 bits = ";
	cout << mult(armazena(n1, n2, n3, n4), armazena(n5, n6, n7, n8), 4); // chamando função mult para multiplicar os dois blocos
	cout << endl << endl << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Whiles irão printar os valores inteiros de soma e mult com chamada de função da simd.h
	int contador = 0;
	cout << "[";
	while (contador <= 3)
	{
		cout.width(3); cout.fill('0');
		cout << soma(armazena(n1, n2, n3, n4), armazena(n5, n6, n7, n8), contador);
		contador++;
		if (contador <= 3)
		{
			cout << ",";
		}
	}
	cout << "] = Somas" << endl;

	contador = 0;
	cout << "[";
	while (contador <= 3)
	{
		cout.width(3); cout.fill('0');
		cout << mult(armazena(n1, n2, n3, n4), armazena(n5, n6, n7, n8), contador);
		contador++;
		if (contador <= 3)
		{
			cout << ",";
		}
	}
	cout << "] = Multiplicações" << endl << endl << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//codificando valores com chamada de função do cripto.h

	unsigned long long codificadoSoma = codificar(soma(armazena(n1, n2, n3, n4), armazena(n5, n6, n7, n8), 4)); 
	unsigned long long codificadoMult = codificar(mult(armazena(n1, n2, n3, n4), armazena(n5, n6, n7, n8), 4)); 

	cout << "Soma Cripto 64 bits = " << codificadoSoma <<endl;
	cout << "Mult Cripto 64 bits = " << codificadoMult << endl << endl << endl;
	
	cout << "Valor codificado = " << decodificar(codificadoSoma, 0);
	contador = 1;
	while (contador <= 6)
	{
		if (contador == 1)
		{
			cout << " (";
		}
		cout << decodificar(codificadoSoma, contador);
		if (contador >= 1 && contador < 6)
		{
			cout << " ";
		}
		

		contador++;
	}
	cout << ")" << endl;
	cout << "Soma decodificada = " << decodificar(codificadoSoma, 7) << endl << endl << endl;


	cout << "Valor codificado = " << decodificar(codificadoMult, 0);
	contador = 1;
	while (contador <= 6)
	{
		if (contador == 1)
		{
			cout << " (";
		}
		cout << decodificar(codificadoMult, contador);
		if (contador >= 1 && contador < 6)
		{
			cout << " ";
		}


		contador++;
	}
	cout << ")" << endl;
	cout << "Mult decodificada = " << decodificar(codificadoMult, 7) << endl << endl;



}