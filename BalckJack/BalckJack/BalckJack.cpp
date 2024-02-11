#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include<cstdlib>

using namespace std;

int picas[13] = { 1,1,1,1,1,1,1,1,1,1,1,1,1 };
int corazones[13] = { 1,1,1,1,1,1,1,1,1,1,1,1,1 };
int diamantes[13] = { 1,1,1,1,1,1,1,1,1,1,1,1,1 };
int treboles[13] = { 1,1,1,1,1,1,1,1,1,1,1,1,1 };
string a;
string txt;

int* genCarta() {
	// REPARTIR CARTA (se reparte una carta 
	// a cualquiera de los dos  se usa 
	// tanto para el jugador y el croupier, 
	// registra las cartas ya usadas )
	// J Q K 
	srand(time(NULL));
	bool val = true;
	static int a[2];
	while (val){
		int opc = rand() % 4;
		int opc2 = rand() % 13;
		
		if (opc == 0) {
			if (picas[opc2] != 0)
			{
				picas[opc2] = 0;
				val = false;
				txt = to_string(opc2 +1) +" de picas\n";
			}
		}
		else if (opc == 1) {
			if (corazones[opc2] != 0)
			{
				corazones[opc2] = 0;
				val = false;
				txt = to_string(opc2 + 1) + " de corazones\n";
			}
		}
		else if (opc == 2) {
			if (treboles[opc2] != 0)
			{
				treboles[opc2] = 0;
				val = false;
				txt = to_string(opc2 + 1) + " de treboles\n";
			}
		}
		else if (opc == 3) {
			if (diamantes[opc2] != 0)
			{
				diamantes[opc2] = 0;
				val = false;
				txt = to_string(opc2 + 1) + " de treboles\n";
			}
		}
		if (val == false)
		{
			a[0] = opc;
			a[1] = opc2;			
			return a;
		}
	}	
}

void mostrarp(int cru,int jug) {
	cout << "\nTus puntos: " << cru << "\n";
	cout << "Puntos croupier: " << jug << "\n\n";
}

void esunAS(int& pJugador, int carta) {
	string opc = "";
	if (carta == 0) {
		cout << "\nQuieres que el AS cuente como 1 o 11?" << "\n";
		cin >> opc;
		if (opc == "11") {
			pJugador += 11;
		}
		else if (opc == "1") {
			pJugador += 1;
		}
		else {
			cout << "Número no valido";
		}
	}
	else {
		if (carta == 10 || carta == 11 || carta == 12)
		{
			pJugador += 10;
		}
		else {
			pJugador += carta + 1;
		}
	}


}

void turnocroupier(int& pCroupier, int& pJugador) {
	// INICIA EL TURNO DE LA BANCA (se ejecuta cuando en 
	// las primeras rondas se alcanza 21 por parte del 
	// jugador o en la siguiente fase el jugador deja 
	// de robar cartas o se pasa de 21)
	int* res;
	 
	while (pCroupier < 21 && pCroupier < pJugador)
	{
		res = genCarta();
		cout << "\nEl crupier se reparte una carta";
		cout << "\nCarta del crupier: " << txt;
		if (res[1] == 0) {

			if (pCroupier + 11 > 21)
			{
				pCroupier += 11;
			}
			else {
				pCroupier += 1;
			}
		}
		else {
			pCroupier += res[1] + 1;
		}

		mostrarp(pJugador, pCroupier);
		system("pause");
		system("cls");
	}

	if (pCroupier > 21)
	{
		cout << "\nGANA EL JUGADOR\n";
	}
	else if (pCroupier > pJugador)
	{
		cout << "\nGANA EL CROUPIER\n";
	}
	else
	{
		cout << "\nEMPATE\n";
	}
}

int main(){                      
	int* res;
	int pJugador = 0;
	int pCroupier = 0;


	cout << "\n\n==============================\n";
	cout << "        BIENVENIDO AL\n";
	cout << "      BLACK JACK MONLAU\n";
	cout << "==============================\n\n";
	system("pause");
	system("cls");


	cout << "El crupier te reparte dos cartas: \n\n";

	for (int i = 0; i < 2; i++)
	{
		res = genCarta();
		cout << "Tu carta es el " << txt ;
		esunAS(pJugador, res[1]); // COMPROBAR SI ES UN AS Y SUMAR PUNTUACION AL JUGADOR EN AMBOS CASOS
	}
	
	mostrarp(pJugador, pCroupier); 
	system("pause");
	system("cls");

	cout << "El crupier se reparte su carta\n";

	res = genCarta();
	cout << "\nCarta del crupier: " << txt;
	if (res[1] == 0) {
		pCroupier += 11;
	}
	else{
		if (res[1] == 10 || res[1] == 11 || res[1] == 12)
		{
			pCroupier += 10;
		}
		else {
			pCroupier += res[1] + 1;
		}
	}

	mostrarp(pJugador, pCroupier);

	if (pJugador == 21) {
		turnocroupier(pCroupier, pJugador);
	}
	else {
		string opccartas = "no";

		while (opccartas == "no" && pJugador < 21 )  // >_<
		{
			cout << "¿Quieres plantarte? (si/no): ";
			cin >> opccartas;
			system("cls");
			for (auto& x : opccartas) { // PASAR A MINUSCULAS LA OPCION SELECCIONADA
				x = tolower(x);
			}

			if (opccartas == "no"){

				res = genCarta();
				cout << "Tu carta es el " << txt;
				esunAS(pJugador, res[1]);
				mostrarp(pJugador, pCroupier);
			}
		}

		if (pJugador > 21)
		{
			cout << "\nGANA EL CROUPIER\n";
		}
		else
		{
			turnocroupier(pCroupier,pJugador);
		}
	}
}