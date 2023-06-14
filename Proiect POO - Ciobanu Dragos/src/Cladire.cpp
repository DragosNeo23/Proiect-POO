#include "Cladire.h"

Cladire::Cladire() {
	lungime = 0;
	latime = 0;
	etaje = 0;
}

int Cladire::getLungime()
{
	return lungime;
}

int Cladire::getLatime()
{
	return latime;
}

int Cladire::getEtaje()
{
	return etaje;
}

int Cladire::getSuprafata()
{
	return getLungime() * getLatime();
}

void Cladire::setLungime(int val)
{
	lungime = val;
}

void Cladire::setLatime(int val)
{
	latime = val;
}

void Cladire::setEtaje(int val)
{
	etaje = val;
}

bool Cladire::existaEtaj(int etaj)
{
	return ((0 <= etaj) && (etaj < getEtaje()));
}
