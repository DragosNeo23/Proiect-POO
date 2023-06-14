#ifndef ELEV_H
#define ELEV_H

class Elev
{
private:
	char *nume;
	char *prenume;
	char *numeComplet;
	char *nrMatricol;
	char *_toStringBuff;
	int anStudiu;
	int varsta;

	void init();
public:
	Elev(void);
	Elev(char *nume, char *prenume, char *nrMatricol, int anStudiu, int varsta);
	~Elev(void);

	char *getNume();
	char *getPrenume();
	char *getNumeComplet();
	char *getNrMatricol();
	int getAnStudiu();
	int getVarsta();

	void setNume(char *val);
	void setPrenume(char *val);
	void setNrMatricol(char *val);
	void setAnStudiu(int val);
	void setVarsta(int val);


	void afiseaza();


};

#endif
