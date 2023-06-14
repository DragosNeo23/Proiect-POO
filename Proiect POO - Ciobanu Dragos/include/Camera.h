
#ifndef CAMERA_H
#define CAMERA_H


#include "Elev.h"

class Camera
{
private:
	Elev **elevi;
	int nrElevi;
	int nrCamera;
	int suprafata;
	int etaj;
protected:
	void redimElevi(int dim);
public:
	static const int nrMaxElevi = 5;

	Camera(int nrCamera, int suprafata, int etaj);
	int getNrCamera();
	int getSuprafata();
	int getEtaj();
	bool adaugaElev(Elev *elev);
	bool stergeElev(Elev *elev);
	bool stergeElev(int index);
	void stergeTotiElevii();
	int cautaElev(Elev *elev);
	int cautaElev(char *numeComplet);
	int cautaElevNrMatricol(char *nrMatricol);
	bool areElev(Elev *elev);
	int getNrElevi();
	bool completOcupata();
	void afiseaza();
	void afiseazaElevii();

	Elev *operator[](int index);
};

#endif

