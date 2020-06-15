// RSA.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "RSA.h"

const int rango = 78498;
const int tam_vec = 4;

RSA::RSA() {

    //p = Primo_Aleatorio();
    //q = Primo_Aleatorio();
    Primos_Criba();
    Generar_n();
    Generar_e();
    Generar_d();
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "n = " << n << endl;
    cout << "o_p = " << o_n << endl;
    cout << "e = " << e << endl;
    cout << "d = " << d << endl;
}

RSA::~RSA()
{
    //dtor
}

ZZ RSA::modulo(ZZ a, ZZ b)
{
    return a - ((a / b) * b);
}

ZZ RSA::Primo_Aleatorio() {

    return RandomPrime_ZZ(20, 10);

}

ZZ RSA::MaxComDiv(ZZ a, ZZ b)
{
    ZZ r = ZZ(a % b);
    while (r != 0)
    {
        //cout << a << " = " << a / b << " (" << b << ") + " << a - (b * (a / b)) << endl;
        a = b;
        b = r;
        r = a % b;
    }
    //cout << a << " = " << a / b << " (" << b << ") + " << a - (b * (a / b)) << endl;
    return b;
}

ZZ RSA::Extendido_Euclides(ZZ a, ZZ b)
{
    ZZ q;
    ZZ r, r1, r2;
    ZZ s, s1, s2;
    ZZ t, t1, t2;

    r1 = a;
    r2 = b;
    s1 = (1);
    s2 = (0);
    t1 = (0);
    t2 = (1);

    while (r2 > 0) {

        q = r1 / r2;
        r = r1 - (q * r2);
        r1 = r2;
        r2 = r;

        s = s1 - (q * s2);
        s1 = s2;
        s2 = s;

        t = t1 - (q * t2);
        t1 = t2;
        t2 = t;
    }
    r = r1;
    s = s1;
    t = t1;
    if (s < 0)
        s = s % b;
    if (t < 0)
        t = t % a;
    //cout << a << "(" << s << ") + " << b << "(" << t << ") = " << r << endl;
    return s;
}

ZZ RSA::Inversa(ZZ a, ZZ b) {

    ZZ r = ZZ(0);
    ZZ c;
    if (MaxComDiv(a, b) == 1) {

        c = Extendido_Euclides(a, b);
        if (c < 0)
            c = c % b;

    }
    else
    {
        cout << a << " No tiene inversa" << endl;
        return ZZ(0);
    }
    return c;
}

void RSA::Primos_Criba() {

    PrimeSeq a;
    ZZ Criba[78498];
    long b, c, d, e;
    c = 0;
    b = a.next();
    while (b <= 1000000) {
        //cout << b << " ";
        b = a.next();
        Criba[c] = b;
        c++;
    }
    d = 0;
    e = 0;
    srand(time(NULL));
    while (d == e && MaxComDiv(Criba[d], Criba[e]) != 1) {
        d = rand() % 78498;
        e = rand() % 78498;
    }
    d = rand() % 78498;
    this->p = Criba[d];
    this->q = Criba[e];
    /*cout << b << endl;
    cout << endl << endl;
    cout << "yo sor r = " << c << endl << endl;
    //delete[] Criba;
    //*/
}

ZZ RSA::Potencia_Modulo(ZZ p, ZZ e, ZZ n)
{
    if (e == 0) return ZZ(1);

    long k = NumBits(e);

    ZZ res;
    res = 1;

    for (long i = k - 1; i >= 0; i--) {
        res = SqrMod(res, n);
        if (bit(e, i) == 1) res = MulMod(res, p, n);
    }

    if (e < 0)
        return InvMod(res, n);
    else
        return res;
}

void RSA::Generar_n() {

    n = p * q;
    o_n = (p - 1) * (q - 1);
}

void RSA::Generar_e() {

    e = modulo(ZZ(rand()), (o_n - 1));
    //e = Primo_Aleatorio();
    int i = 0;
    while (MaxComDiv(e, o_n) != 1) {
        e = modulo(ZZ(rand()), (o_n - 1));
        i++;
    }
    //cout << "yo soy r = " << i << endl;
}

void RSA::Generar_d() {

    d = Inversa(e, o_n);
}

void RSA::Cifrar(string mensaje) {

    ZZ m;
    ZZ mensaje_cifrado [tam_vec];
    for (int i = 0; i < mensaje.size(); i++)
    {
        m = alfabeto.find(mensaje[i]);
        m = Potencia_Modulo(m, e, n);
        mensaje_cifrado[i] = m;
    }
    for (int i = 0; i < tam_vec; i++) {
        cout << "letra del mensaje " << i + 1 << " = " << mensaje_cifrado[i] << endl;
    }
    //return mensaje_cifrado;
    Descifrar(mensaje_cifrado);
}

string RSA::Descifrar(ZZ mensaje [4]) {

    ZZ m;
    int a = 0;
    int r = 0;
    string mensaje_cifrado;
    for (int i = 0; i < tam_vec; i++)
    {
        m = Potencia_Modulo(mensaje[i], d, n);
        cout << "m = " << m << endl;
        while (m > 0) {
            m--;
            a++;
        }
        mensaje_cifrado += alfabeto[a];
        a = 0;
    }
    cout << "mensaje descifrado = " << mensaje_cifrado << endl;
    return mensaje_cifrado;
}

int main()
{
    RSA a;
    a.Cifrar("Hola");

    /*int pos_letra = 0;
    string cifrado;
    ZZ base, exponente, modu, mensaje;
    cin >> base;
    cin >> exponente;
    cin >> modu;
    mensaje = a.Potencia_Modulo(base, exponente, modu);
    while (mensaje > 0) {
        mensaje--;
        pos_letra++;
    }
    cifrado += a.alfabeto[pos_letra];
    //*/
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
