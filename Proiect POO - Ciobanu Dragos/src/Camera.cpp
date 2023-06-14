#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Camera.h"

using namespace std;

void Camera::redimElevi(int dim) {
	elevi = (Elev **)realloc(elevi, sizeof(Elev *) * dim);
}

int Camera::getNrCamera() {
	return nrCamera;
}

int Camera::getSuprafata() {
	return suprafata;
}

int Camera::getEtaj() {
	return etaj;
}

Camera::Camera(int nrCamera, int suprafata, int etaj) {
	this->nrCamera = nrCamera;
	this->suprafata = suprafata;
	this->etaj = etaj;
	elevi = NULL;
	nrElevi = 0;
}

bool Camera::adaugaElev(Elev *elev) {
	if ((nrElevi == nrMaxElevi) || areElev(elev))
		return false;

	redimElevi(nrElevi + 1);
	elevi[nrElevi] = elev;
	nrElevi++;

	return true;
}

bool Camera::stergeElev(Elev *elev) {
	if (!areElev(elev))
		return false;

	int index = cautaElev(elev);
	stergeElev(index);

	return true;
}

bool Camera::stergeElev(int index) {
	if ((index < 0) || (index >= nrElevi))
		return false;

	for (int i = index; i < nrElevi - 1; i++)
		elevi[i] = elevi[i + 1];
	redimElevi(nrElevi - 1);
	nrElevi--;

	return true;
}

void Camera::stergeTotiElevii() {
	redimElevi(0);
	nrElevi = 0;
}

int Camera::cautaElev(Elev *elev) {
	for (int i = 0; i < nrElevi; i++)
		if (elevi[i] == elev)
			return i;

	return -1;
}

int Camera::cautaElev(char *numeComplet) {
	for (int i = 0; i < nrElevi; i++)
		if (strcmp(elevi[i]->getNumeComplet(), numeComplet) == 0)
			return i;

	return -1;
}

int Camera::cautaElevNrMatricol(char *nrMatricol) {
	for (int i = 0; i < nrElevi; i++)
		if (strcmp(elevi[i]->getNrMatricol(), nrMatricol) == 0)
			return i;

	return -1;
}

bool Camera::areElev(Elev *elev) {
	return cautaElev(elev) != -1;
}

int Camera::getNrElevi() {
	return nrElevi;
}

bool Camera::completOcupata() {
	return (getNrElevi() == nrMaxElevi);
}

void Camera::afiseaza() {
	cout << "Camera selectata este: " << nrCamera << "; Etajul selectat este: " << etaj;
	cout << "; Suprafata este:" << suprafata << endl;
	cout << "Elevi cazati sunt urmatorii:" << nrElevi << endl;
	afiseazaElevii();
}

void Camera::afiseazaElevii() {
	for (int i = 0; i < nrElevi; i++)
		elevi[i]->afiseaza();
}

Elev *Camera::operator[](int index) {
	if ((index < 0) || (index > nrElevi))
		return NULL;

	return elevi[index];
}
