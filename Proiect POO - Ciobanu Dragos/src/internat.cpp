#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "internat.h"

using namespace std;

void Internat::redimCamere(int dim) {
	camere = (Camera **)realloc(camere, sizeof(Camera *) * dim);
}

Internat::Internat(void)
{
	camere = NULL;
	nrCamere = 0;
	nume = NULL;
	adresa = NULL;
	programVizita = NULL;
}

Internat::~Internat(void)
{
	for (int i = 0; i < getNrCamere(); i++)
		delete camere[i];

	free(camere);
	free(nume);
	free(adresa);
	free(programVizita);
}

char *Internat::getNume()
{
	return nume;
}

char *Internat::getAdresa()
{
	return adresa;
}

char *Internat::getProgramVizita()
{
	return programVizita;
}

void Internat::setNume(char *val)
{
	nume = (char *)realloc(nume, strlen(val) + 1);
	strcpy(nume, val);
}

void Internat::setAdresa(char *val)
{
	adresa = (char *)realloc(adresa, strlen(val) + 1);
	strcpy(adresa, val);
}

void Internat::setProgramVizita(char *val)
{
	programVizita = (char *)realloc(programVizita, strlen(val) + 1);
	strcpy(programVizita, val);
}

int Internat::adaugaCamera(int nrCamera, int suprafata, int etaj)
{
	if (!existaEtaj(etaj))
		return -1;

	redimCamere(nrCamere + 1);
	camere[nrCamere] = new Camera(nrCamera, suprafata, etaj);
	nrCamere++;

	return nrCamere - 1;
}

bool Internat::stergeCamera(int index) {
	if ((index < 0) || (index >= nrCamere))
		return false;

	delete camere[index];
	for (int i = index; i < nrCamere - 1; i++)
		camere[i] = camere [i + 1];
	redimCamere(nrCamere - 1);
	nrCamere--;

	return true;
}

void Internat::stergeToateCamerele() {
	redimCamere(0);
	nrCamere = 0;
}

void Internat::stergeTotiElevii() {
	for (int i = 0; i < getNrCamere(); i++)
		camere[i]->stergeTotiElevii();
}

int Internat::cautaCamera(int nrCamera) {
	for (int i = 0; i < nrCamere; i++)
		if (camere[i]->getNrCamera() == nrCamera)
			return i;

	return -1;
}

int Internat::cautaElev(Elev *elev) {
	for (int i = 0; i < nrCamere; i++)
		if (camere[i]->cautaElev(elev) != -1)
			return i;

	return -1;
}

int Internat::cautaElev(char *numeComplet) {
	for (int i = 0; i < nrCamere; i++)
		if (camere[i]->cautaElev(numeComplet) != -1)
			return i;

	return -1;
}

int Internat::cautaElevNrMatricol(char *nrMatricol) {
	for (int i = 0; i < nrCamere; i++)
		if (camere[i]->cautaElevNrMatricol(nrMatricol) != -1)
			return i;

	return -1;
}

void Internat::afiseazaToateCamerele() {
	for (int i = 0; i < getNrCamere(); i++) {
		cout << "[" << i << "] ";
		camere[i]->afiseaza();
	}
}

bool Internat::afiseazaEtaj(int etaj) {
	if (!existaEtaj(etaj))
		return false;

	for (int i = 0; i < getNrCamere(); i++)
		if (camere[i]->getEtaj() == etaj) {
			cout << "[" << i << "] ";
			camere[i]->afiseaza();
		}
	return true;
}

int Internat::getNrCamere() {
	return nrCamere;
}

int Internat::getNrCamerePeEtaj(int etaj) {
	if (!existaEtaj(etaj))
		return 0;

	int total = 0;
	for (int i = 0; i < nrCamere; i++)
		if (camere[i]->getEtaj() == etaj)
			total++;

	return total;
}

Camera *Internat::operator[](int index) {
	if ((index < 0) || (index >= nrCamere))
		return NULL;

	return camere[index];
}
