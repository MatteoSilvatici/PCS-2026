# include <iostream>

int main()
{
double ad[4] = {0.0, 1.1, 2.2, 3.3};
float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
int ai[3] = {0, 1, 2};

int x = 1;
float y = 1.1;

std::cout << "Indirizzi array 'ad' (double, solitamente 8 byte):\n";
for(int i = 0; i < 4; i++) std::cout << &ad[i] << "\n";

std::cout << "\nIndirizzi array 'af' (float, solitamente 4 byte):\n";
for(int i = 0; i < 8; i++) std::cout << &af[i] << "\n";

std::cout << "\nIndirizzi array 'ai' (int, solitamente 4 byte):\n";
for(int i = 0; i < 3; i++) std::cout << &ai[i] << "\n";

std::cout << "\nIndirizzi variabili scalari:\n";
std::cout << "Indirizzo di x: " << &x << "\n";
std::cout << "Indirizzo di y: " << &y << "\n";

(&y)[1] = 0; // clang mette la y subito prima della x
std::cout << "Valore di x finale: " << x << "\n";

 return 0;
 
 // obiettivo esercizio: capire posizione relativa tra x e y, capire come
 // il compilatore mette in memoria le variabili
}