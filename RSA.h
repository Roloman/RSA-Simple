#pragma once

#include <NTL/ZZ.h>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cmath>
#include <vector>
#include <time.h>


using namespace std;
using namespace NTL;

class RSA
{
	public:
		RSA();

		string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890";
		ZZ p;
		ZZ q;
		ZZ n;
		ZZ o_n;
		ZZ e;
		ZZ d;

		ZZ modulo(ZZ, ZZ);
		ZZ MaxComDiv(ZZ, ZZ);
		ZZ Extendido_Euclides(ZZ, ZZ);
		ZZ Inversa(ZZ, ZZ);
		ZZ Primo_Aleatorio();
		ZZ Potencia_Modulo(ZZ, ZZ, ZZ);
		void Primos_Criba();
		void Generar_n();
		void Generar_e();
		void Generar_d();
		void Cifrar(string);
		string Descifrar(ZZ mensaje[4]);

		virtual ~RSA();

	protected:
	private:
};

