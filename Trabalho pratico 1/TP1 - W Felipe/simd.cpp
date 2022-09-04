#include <iostream>
#include "simd.h"
#include "cripto.h"


//Funções:
unsigned int armazena(int a, int b, int c, int d);
unsigned int soma(int a, int b, int c);
unsigned int mult(int a, int b, int c);
unsigned short primeiro(int a);
unsigned short segundo(int a);
unsigned short terceiro(int a);
unsigned short quarto(int a);

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//função armazena;
 unsigned int armazena(int a, int b, int c, int d)
{
	unsigned char num1, num2, num3, num4;
	int bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, blocofinal = 0; //Blocos com estado 0 para 32 bits;

	//Levando numeros para 8 bits;
	num1 = a;
	num2 = b;
	num3 = c;
	num4 = d;


	//Inserindo em blocos de apoio;
	bloco1 = bloco1 | num1;
	bloco2 = bloco2 | num2;
	bloco3 = bloco3 | num3;
	bloco4 = bloco4 | num4;

	//Inserindo no blocofinal com OR e em suas respectivas posições;
	blocofinal = blocofinal  | (bloco1 << 24);
	blocofinal = blocofinal | (bloco2 << 16);
	blocofinal = blocofinal | (bloco3 << 8);
	blocofinal = blocofinal | bloco4;



	return blocofinal;

}

 /////////////////////////////////////////////////////////////////////////////////////////
 //função soma:
 unsigned int soma(int a, int b, int c)
{

	 using namespace std;
	 unsigned char soma1, soma2, soma3, soma4;

	 soma1 = primeiro(a) + primeiro(b); 
	 soma2 = segundo(a) + segundo(b); 
	 soma3 = terceiro(a) + terceiro(b); 
	 soma4 = quarto(a) + quarto(b); 

	 //while ira retornar valores separados:
	 if (c == 0)
	 {		 
		 return soma1;
	 }
	 if (c == 1)
	 {
		 return soma2;
	 }
	 if (c == 2)
	 {
		 return soma3;
	 }
	 if (c == 3)
	 {
		 return soma4;
	 }
	 if (c == 4)
	 {
		 armazena(soma1, soma2, soma3, soma4);
	 }
}
 /////////////////////////////////////////////////////////////////////////////////////////
 //Função multiplicar:
 unsigned int mult(int a, int b, int c)
{
	 using namespace std;
	 unsigned char mult1, mult2, mult3, mult4;

	 mult1 = primeiro(a) * primeiro(b); 
	 mult2 = segundo(a) * segundo(b); 
	 mult3 = terceiro(a) * terceiro(b); 
	 mult4 = quarto(a) * quarto(b); 

	 if (c == 0)
	 {
		 return mult1;
	 }
	 if (c == 1)
	 {
		 return mult2;
	 }
	 if (c == 2)
	 {
		 return mult3;
	 }
	 if (c == 3)
	 {
		 return mult4;
	 }
	 if (c == 4)
	 {
		 armazena(mult1, mult2, mult3, mult4);
	 }
}
 /////////////////////////////////////////////////////////////////////////////////////////

 unsigned short primeiro(int a)
 {
	 int resultado = 0, bloco0 = 0;

	 //blocos de apoio;
	 bloco0 = bloco0 | a;
	 resultado = resultado | (bloco0 >> 24);

	 //resultado:
	 return resultado;
	
 }
 /////////////////////////////////////////////////////////////////////////////////////////

 unsigned short segundo(int a)
 {
	 int resultado = 0, bloco0 = 0, bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0;

	 //blocos de apoio:
	 bloco0 = bloco0 | a;
	 bloco1 = bloco1 | (bloco0 << 5);
	 bloco2 = bloco2 | (bloco1 >> 5);
	 bloco3 = bloco3 | (bloco2 >> 5);
	 bloco4 = bloco4 | (bloco3 >> 5);
	 bloco5 = bloco5 | (bloco4 >> 5);
	 //resultado:
	 resultado = resultado | (bloco5 >> 1);

	 return resultado;
	
 }

 unsigned short terceiro(int a)
 {
	 int resultado = 0, bloco0 = 0, bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0;

	 //blocos de apoio:
	 bloco0 = bloco0 | a;
	 bloco1 = bloco1 | (bloco0 << 10);
	 bloco2 = bloco2 | (bloco1 >> 10);
	 bloco3 = bloco3 | (bloco2 >> 5);
	 bloco4 = bloco4 | (bloco3 >> 3);

	 //resultado:
	 resultado = resultado | (bloco4);

	 return resultado;


 }

 unsigned short quarto(int a)
 {
	 int resultado = 0, bloco0 = 0, bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0;

	 //blocos de apoio:
	 bloco0 = bloco0 | a;
	 bloco1 = bloco1 | (bloco0 << 24);
	 bloco2 = bloco2 | (bloco1 >> 24);
	

	 //resultado:
	 resultado = resultado | (bloco2);

	 return resultado;


 }


