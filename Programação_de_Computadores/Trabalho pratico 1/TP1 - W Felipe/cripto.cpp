#include <iostream>
#include <random>
#include "simd.h"
#include "cripto.h"

unsigned long long codificar(unsigned int a);
unsigned int decodificar(long long a, int b);
unsigned int ligarBit(unsigned int a, int bit);
unsigned int desligarBit(unsigned int a, int bit);
bool testarBit(unsigned int a, int bit);


unsigned long long codificar(unsigned int a)
{
	using namespace std;
	unsigned int p1, p2, p3, p4, p5, p6;
	long long resultado = 0;
	unsigned int bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0, bloco6 = 0, blococodificado = 0; //blocos de apoio para codificação;
	unsigned int blocop1 = 0, blocop2 = 0, blocop3 = 0, blocop4 = 0, blocop5 = 0, blocop6 = 0, blocosorteado = 0; // blocos de apoio para  sorteados;

	//Geração de numeros aleatorios usando a bibliote <random>;
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, 31);

	p1 = dist(mt);
	p2 = dist(mt);
	p3 = dist(mt);
	p4 = dist(mt);
	p5 = dist(mt);
	p6 = dist(mt);

	//criptografia usando testar bits
	if (testarBit(a, p1) == true)
	{
		bloco1 = desligarBit(a, p1);
	}
	else
	{ 
		bloco1 = ligarBit(a, p1);

	}
	if (testarBit(bloco1, p2) == true)
	{
		bloco2 =  desligarBit(bloco1, p2);
	}
	else
	{
		bloco2 = ligarBit(bloco1, p2);

	}
	if (testarBit(bloco2, p3) == true)
	{
		bloco3 = desligarBit(bloco2, p3);
	}
	else
	{
		bloco3 =  ligarBit(bloco2, p3);

	}
	if (testarBit(bloco3, p4) == true)
	{
		bloco4 =  desligarBit(bloco3, p4);
	}
	else
	{
		bloco4 =  ligarBit(bloco3, p4);

	}
	if (testarBit(bloco4, p5) == true)
	{
		bloco5 =  desligarBit(bloco4, p5);
	}
	else
	{
		bloco5 =  ligarBit(bloco4, p5);

	}
	if (testarBit(bloco5, p6) == true)
	{
		bloco6 = desligarBit(bloco5, p6);
	}
	else
	{
		bloco6 = ligarBit(bloco5, p6);

	}

	blocop1 = blocop1 | (p1 << 27);
	blocop2 = blocop2 | (p2 << 22);
	blocop3 = blocop3 | (p3 << 17);
	blocop4 = blocop4 | (p4 << 12);
	blocop5 = blocop5 | (p5 << 7);
	blocop6 = blocop6 | (p6 << 2);

	blocosorteado = (blocosorteado | blocop1 | blocop2 | blocop3 | blocop4 | blocop5 | blocop6);
	blococodificado = blococodificado | bloco6; 
	resultado = (resultado | blococodificado) << 32;
	resultado = resultado | blocosorteado;
	
	return resultado;

}

unsigned int decodificar(long long a, int b)
{
	unsigned int bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0, bloco6 = 0, bloco7 = 0, codificado = 0, decodificado = 0; //blocos de apoio;
	unsigned int blocop1 = 0, blocop2 = 0, blocop3 = 0, blocop4 = 0, blocop5 = 0, blocop6 = 0, sorteado = 0; //blocos de posição dos numeros aleatorios;
	unsigned long long bloco64 = a;

	 codificado = codificado | (bloco64 >> 32);

     ////////////////////////////////////////////////////////////////////////
	 //usando while será printado os valores sorteados que criptografaram o bloco, que serão tirados usando manipulação bit a bit como metodo:
	 //primeiro passo: levar todos para os primeiros 5 bits do bloco de 32;
	 //segundo passo: trazer para o os ultimos 5 bits do bloco de 32.

	if (b == 0)
	{
		return codificado;
	}
	///////////////////////////////////////////////////////////////////////
	sorteado = bloco64;
	sorteado = (sorteado >> 2);

	///////////////////////////////////////////////////////////////////////

	blocop1 = blocop1 | (sorteado >> 25); 
	if (b == 1)
	{
		return blocop1;
	}

	///////////////////////////////////////////////////////////////////////
	bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0, bloco6 = 0;

	bloco1 = (sorteado << 5);
	bloco2 = (bloco1 << 2);
	bloco3 = (bloco2 >> 2);
	blocop2 = (bloco3 >> 25); 

	if (b == 2)
	{
		return blocop2;
	}


	///////////////////////////////////////////////////////////////////////
	bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0, bloco6 = 0;

	bloco1 = (sorteado << 5);
	bloco2 = (bloco1 << 5);
	bloco3 = (bloco2 << 2);
	bloco4 = (bloco3 >> 2);
	blocop3 = (bloco4 >> 25); 

	if (b == 3)
	{
		return blocop3;
	}

	///////////////////////////////////////////////////////////////////////
	bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0, bloco6 = 0;

	bloco1 = (sorteado << 5);
	bloco2 = (bloco1 << 5);
	bloco3 = (bloco2 << 5);
	bloco4 = (bloco3 << 2);
	bloco5 = (bloco4 >> 2);
	blocop4 = (bloco5 >> 25); 

	if (b == 4)
	{
		return blocop4;
	}

	///////////////////////////////////////////////////////////////////////
	bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0, bloco6 = 0;

	bloco1 =  (sorteado << 5);
	bloco2 =  (bloco1 << 5);
	bloco3 =  (bloco2 << 5);
	bloco4 =  (bloco3 << 5);
	bloco5 =  (bloco4 << 2);
	bloco6 =  (bloco5 >> 2);
	blocop5 =  (bloco6 >> 25); 

	if (b == 5)
	{
		return blocop5;
	}

	///////////////////////////////////////////////////////////////////////
	bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0, bloco6 = 0;

	bloco1 = (sorteado << 5);
	bloco2 = (bloco1 << 5);
	bloco3 = (bloco2 << 5);
	bloco4 = (bloco3 << 5);
	bloco5 = (bloco4 << 5);
	bloco6 = (bloco5 << 2);
	bloco7 = (bloco6 >> 2);
	blocop6 = (bloco7 >> 25); 
	if (b == 6)
	{
		return blocop6;
	}

	////////////////////////////////////////////////////////////////////////	
	// Descriptografia:
	bloco1 = 0, bloco2 = 0, bloco3 = 0, bloco4 = 0, bloco5 = 0, bloco6 = 0;

	if (b == 7)
	{
		if (testarBit(codificado, blocop1) == true)
		{
			bloco1 =  desligarBit(codificado, blocop1);
		}
		else
		{
			bloco1 =  ligarBit(codificado, blocop1);

		}
		if (testarBit(bloco1, blocop2) == true)
		{
			bloco2 = desligarBit(bloco1, blocop2);
		}
		else
		{
			bloco2 =  ligarBit(bloco1, blocop2);

		}
		if (testarBit(bloco2, blocop3) == true)
		{
			bloco3 =  desligarBit(bloco2, blocop3);
		}
		else
		{
			bloco3 =  ligarBit(bloco2, blocop3);

		}
		if (testarBit(bloco3, blocop4) == true)
		{
			bloco4 =  desligarBit(bloco3, blocop4);
		}
		else
		{
			bloco4 =  ligarBit(bloco3, blocop4);

		}
		if (testarBit(bloco4, blocop5) == true)
		{
			bloco5 =  desligarBit(bloco4, blocop5);
		}
		else
		{
			bloco5 = ligarBit(bloco4, blocop5);

		}
		if (testarBit(bloco5, blocop6) == true)
		{
			bloco6 = desligarBit(bloco5, blocop6);
		}
		else
		{
			bloco6 = ligarBit(bloco5, blocop6);

		}

		decodificado =  bloco6;
	

		return decodificado;

	
	}
	
}

unsigned int ligarBit(unsigned int a, int bit)
{

	unsigned int mascara = 1 << bit;
	unsigned int estado = a;
      estado = estado | mascara;

	return estado;
}

unsigned int desligarBit(unsigned int a, int bit)
{

	unsigned int mascara = ~(1 << bit);
	unsigned int estado = a;
	estado = estado & mascara;

	return estado;
}

bool testarBit(unsigned int a, int bit)
{

	unsigned int mascara = 1 << bit;

	unsigned int estado = a;

	if (estado & mascara)
	{
		return true;
	}
	else
	{
		return false;
	}

}