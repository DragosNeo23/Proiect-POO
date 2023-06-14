#ifndef CLADIRE_H
#define CLADIRE_H

class Cladire {
private:
	int latime;
	int lungime;
	int etaje;
public:
	Cladire();

	int getLatime();
	int getLungime();
    int getEtaje();
    int getSuprafata();

	void setLatime(int val);
	void setLungime(int val);
	void setEtaje(int val);

	bool existaEtaj(int etaj);
};

#endif
