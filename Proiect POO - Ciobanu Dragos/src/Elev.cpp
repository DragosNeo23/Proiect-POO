#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Elev.h"

using namespace std;

void Elev::init() {
	nume = NULL;
	prenume = NULL;
	numeComplet = NULL;
	nrMatricol = NULL;
	_toStringBuff = NULL;
	varsta = 14;
	anStudiu = 1;
}

Elev::Elev(void) {
	init();
}

Elev::Elev(char *nume, char *prenume, char *nrMatricol, int anStudiu, int varsta) {

	init();
	setNume(nume);
	setPrenume(prenume);
	setNrMatricol(nrMatricol);
	setAnStudiu(anStudiu);
	setVarsta(varsta);
	numeComplet = NULL;
	_toStringBuff = NULL;
}

Elev::~Elev(void) {
	free(nume);
	free(prenume);
	free(numeComplet);
	free(nrMatricol);
	free(_toStringBuff);
}

char *Elev::getNume() {
	return nume;
}

char *Elev::getPrenume() {
	return prenume;
}

char *Elev::getNumeComplet() {
	int ncDim = strlen(nume) + 1 + strlen(prenume) + 1;
	numeComplet = (char *)realloc(numeComplet, ncDim);


	strcpy(numeComplet, nume);
	strcat(numeComplet, " ");
	strcat(numeComplet, prenume);

	return numeComplet;
}

char *Elev::getNrMatricol() {
	return nrMatricol;
}

int Elev::getVarsta() {
	return varsta;
}

int Elev::getAnStudiu() {
	return anStudiu;
}

void Elev::setNume(char *val) {
	nume = (char *)realloc(nume, strlen(val) + 1);
	strcpy(nume, val);
}

void Elev::setPrenume(char *val) {
	prenume = (char *)realloc(prenume, strlen(val) + 1);
	strcpy(prenume, val);
}

void Elev::setNrMatricol(char *val) {
	nrMatricol = (char *)realloc(nrMatricol, strlen(val) + 1);
	strcpy(nrMatricol, val);
}

void Elev::setAnStudiu(int val) {
	if (val < 1)
		val = 1;
	else if (val > 5)
		val = 5;

	anStudiu = val;
}

void Elev::setVarsta(int val) {
	if (val < 14)
		val = 14;

	varsta = val;
}

void Elev::afiseaza() {
	cout << "Elevul se numeste: " << getNumeComplet() << "; ";
	cout << "Elevul are urmatorul numar matricol: " << getNrMatricol() << "; ";
	cout << "Elevul studiaza in anul: " << getAnStudiu() << "; ";
	cout << "Elevul are varsta: " << getVarsta() << endl;
}

