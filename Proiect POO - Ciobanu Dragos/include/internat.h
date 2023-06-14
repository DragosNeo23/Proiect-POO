#ifndef INTERNAT_H
#define INTERNAT_H

#include "Cladire.h"
#include "Camera.h"

class Internat : public Cladire
{
private:
	Camera **camere;
	int nrCamere;
	char *nume;
	char *adresa;
	char *programVizita;
protected:
	void redimCamere(int dim);
public:
	Internat(void);
	~Internat(void);


	char *getNume();
	char *getAdresa();
	char *getProgramVizita();


	void setNume(char *val);
	void setAdresa(char *val);
	void setProgramVizita(char *val);


	int adaugaCamera(int nrCamera, int suprafata, int etaj);
	bool stergeCamera(int index);
	void stergeToateCamerele();
	void stergeTotiElevii();

	int cautaCamera(int nrCamera);
	int cautaElev(Elev *elev);
	int cautaElev(char *numeComplet);
	int cautaElevNrMatricol(char *nrMatricol);

	void afiseazaToateCamerele();
	bool afiseazaEtaj(int etaj);


	int getNrCamere();
	int getNrCamerePeEtaj(int etaj);

	Camera *operator[](int index);
};

#endif
