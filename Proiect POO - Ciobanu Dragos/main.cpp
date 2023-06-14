#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "internat.h"
#include "Cladire.h"
#include "Camera.h"
#include "Elev.h"

using namespace std;

char inBuff[100];
Elev **elevi = NULL;
int nrTotalElevi = 0;
Internat *internat = new Internat();


void MeniuGestionareElevi();
void MeniuConfigInternat();
void MeniuCazare();
void stergeElevi();


char intreabaDaNu(char *intrebare) {
	char rasp;
	do
    {
		cout << intrebare; cin >> rasp;
	}
	while ((rasp != 'D') && (rasp != 'N'));

	return rasp;
}

void redimElevi(int dim)
{
	elevi = (Elev **)realloc(elevi, sizeof(Elev *) * dim);
}


int cautaElevNrMatricolInLista(char *nrMatricol) {
	for (int i = 0; i < nrTotalElevi; i++)
    {
		if (strcmp(elevi[i]->getNrMatricol(), nrMatricol) == 0)
			return i;
	}

	return -1;
}


void creeazaListaPredefElevi() {
	stergeElevi();

	nrTotalElevi = 10;
	elevi = (Elev **)malloc(sizeof(Elev *) * nrTotalElevi);
	elevi[0] = new Elev("Toma", "Sebastian", "12745578", 1, 14);
	elevi[1] = new Elev("Muresan", "Catalin", "45789134", 1, 15);
	elevi[2] = new Elev("Dinescu", "David", "75127895", 2, 16);
	elevi[3] = new Elev("Dimitrescu", "Victoria", "53246231", 2, 16);
	elevi[4] = new Elev("Chirita", "Carla", "34525472", 2, 17);
	elevi[5] = new Elev("Vlasceanu", "Clara", "98542345", 3, 17);
	elevi[6] = new Elev("Dumitru", "Florin", "87961357", 4, 18);
	elevi[7] = new Elev("Radu", "Elvira", "54639714", 4, 18);
	elevi[8] = new Elev("Manolache", "Larisa", "53123631", 2, 17);
	elevi[9] = new Elev("Stefan", "Daria", "23416523", 1, 14);
}

void adaugaUnElev()
{
	int iVal = 0;
	Elev *elev = new Elev();
	cout << "Numele elevului este: "; cin >> inBuff;
	elev->setNume(inBuff);
	cout << "Prenumele elevului este: "; cin >> inBuff;
	elev->setPrenume(inBuff);
	cout << "Numarul matricol al elevului este: "; cin >> inBuff;
	elev->setNrMatricol(inBuff);
	cout << "Anul de studiu este: "; cin >> iVal;
	elev->setAnStudiu(iVal);
	cout << "Varsta elevului este: "; cin >> iVal;
	elev->setVarsta(iVal);

	redimElevi(nrTotalElevi + 1);
	elevi[nrTotalElevi] = elev;
	nrTotalElevi++;
}

bool stergeElev()
{
	int index;

	cout << "Introduceti indexul elevului pe care doriti sa-l stergeti sau tastati -1 pentru a anula stergerea" << endl;
	while (true) {
		cout << "Indexul elevului este urmatorul: "; cin >> index;

		if (index == -1)
			return false;
		else if ((index < 0) || (index >= nrTotalElevi))
			cout << "Introduceti indexul corect al elevului pe care doriti sa-l stergeti sau tastati -1 pentru a anula stergerea" << endl;
		else {
			delete elevi[index];
			for (int i = index; i < nrTotalElevi - 1; i++)
				elevi[i] = elevi[i + 1];
			redimElevi(nrTotalElevi - 1);
			nrTotalElevi--;

			return true;
		}
	}
}

void stergeElevi() {
	for (int i = 0; i < nrTotalElevi; i++)
		delete elevi[i];
	free(elevi);

	elevi = NULL;
	nrTotalElevi = 0;
}

void OptiuneAfiseazaTotiElevii() {
	cout << endl;

	for (int i = 0; i < nrTotalElevi; i++) {
		cout << "[" << i << "] ";
		elevi[i]->afiseaza();
	}
	cout << "Numarul elevilor este: " << nrTotalElevi << endl;

	cout << endl;
}

void OptiuneAfiseazaToateCamerele() {
	cout << endl;

	internat->afiseazaToateCamerele();
	cout << "Numarul camerelor este: " << internat->getNrCamere() << endl;
    cout << endl;
}

void OptiuneAfiseazaEtaj() {
	int iEtaj;

	cout << endl;
    cout << "Numarul etajului: "; cin >> iEtaj;
	if (internat->existaEtaj(iEtaj)) {
		internat->afiseazaEtaj(iEtaj);
		cout << "Numarul camerelor de pe etaj este: " << internat->getNrCamerePeEtaj(iEtaj) << endl;
	}
	else
		cout << "Etajul nu exista in aceasta cladire!!!!" << endl;

	cout << endl;
}

void OptiuneCazeazaElev() {
	int iVal, idxElev, idxCamera;

	cout << endl;

	cout << "Numarul matricol al elevului este urmatorul: "; cin >> inBuff;
	idxElev = cautaElevNrMatricolInLista(inBuff);
	if (idxElev == -1) {
		cout << "Nu exista elev cu acest numar matricol!!!!" << endl << endl;
		return;
	}

	idxCamera = internat->cautaElevNrMatricol(inBuff);
	if (idxCamera != - 1) {
		cout << "Elevul este cazat deja"
			 << (*internat)[idxCamera]->getNrCamera() << endl << endl;
		return;
	}

	cout << "Numarul camerei in care urmeaza sa fie cazat elevul este: "; cin >> iVal;
	idxCamera = internat->cautaCamera(iVal);
	if ((*internat)[idxCamera]->completOcupata()) {
		cout << "Camera este ocupata la capacitate maxima!!!" << endl << endl;
		return;
	}

	(*internat)[idxCamera]->adaugaElev(elevi[idxElev]);
	cout << "Elevul a fost cazat cu succes in camera aleasa" << endl;

	cout << endl;
}

void OptiuneDecazeazaElev() {
	int idxElev, idxCamera;

	cout << endl;

	cout << "Numarul matricol al elevului este urmatorul "; cin >> inBuff;
	idxElev = cautaElevNrMatricolInLista(inBuff);
	if (idxElev == -1) {
		cout << "Nu exista elev cu acest numar matricol!!!" << endl << endl;
		return;
	}

	idxCamera = internat->cautaElevNrMatricol(inBuff);
	if (idxCamera == - 1) {
		cout << "Elevul nu a fost cazat!!!" << endl << endl;
		return;
	}

	(*internat)[idxCamera]->stergeElev(elevi[idxElev]);
	cout << "Elevul s-a decazat"
		 << (*internat)[idxCamera]->getNrCamera() << endl;

	cout << endl;
}

void configurarePredefInternat() {
	internat->setNume("Internatul Liceului Teoretic \"Regina Maria\"");
	internat->setAdresa("Bulevardul Victoriei");
	internat->setProgramVizita("8:00-20:00");
	internat->setLungime(22);
	internat->setLatime(16);
	internat->setEtaje(2);

	internat->stergeToateCamerele();
	for (int i = 0; i < 4; i++)
		internat->adaugaCamera(1 + i, 40, 0);

	if (nrTotalElevi >= 10) {
		Camera *cam = (*internat)[0];
		cam->adaugaElev(elevi[0]);
		cam->adaugaElev(elevi[1]);
		cam->adaugaElev(elevi[3]);

		cam = (*internat)[1];
		cam->adaugaElev(elevi[2]);
		cam->adaugaElev(elevi[4]);

		cam = (*internat)[2];
		cam->adaugaElev(elevi[5]);

		cam  = (*internat)[3];
		cam->adaugaElev(elevi[6]);
		cam->adaugaElev(elevi[7]);
		cam->adaugaElev(elevi[8]);
		cam->adaugaElev(elevi[9]);
	}
}


void MeniuPrincipal() {
	int opt;
	bool reafiseaza = true;

	while (true) {
		if (reafiseaza) {
            cout << ".....Cazarea elevilor in internatul scolar....." << endl;
			cout << "1. Gestiunea elevilor" << endl;
			cout << "2. Optiuni internat" << endl;
			cout << "3. Cazare" << endl;
			cout << "4. Exit" << endl;
			cout << "Selectati optiunea dorita: ";
		}
		cin >> opt;

		switch (opt) {
			case 1:
				cout << endl;
				MeniuGestionareElevi();
				cout << endl;
				reafiseaza = true;
				break;
			case 2:
				cout << endl;
				MeniuConfigInternat();
				cout << endl;
				reafiseaza = true;
				break;
			case 3:
				cout << endl;
				MeniuCazare();
				cout << endl;
				reafiseaza = true;
				break;
			case 4:
				return;
			default:
				cout << "Alege o optiune: ";
				reafiseaza = false;
		}
	}
}

void MeniuGestionareElevi() {
	int opt;
	bool reafiseaza = true;

	while (true) {
		if (reafiseaza) {
			cout << "1. Salveaza lista de elevi" << endl;
			cout << "2. Adaugare elev" << endl;
			cout << "3. Stergere elev" << endl;
			cout << "4. Stergere toti elevii" << endl;
			cout << "5. Afisare toti elevii" << endl;
			cout << "6. Meniul precedent" << endl;
			cout << "Alege optiunea dorita: ";
		}
		cin >> opt;

		switch (opt) {
			case 1:
				cout << endl;
				creeazaListaPredefElevi();
				cout << "Lista de elevi a fost incarcata" << endl;
				cout << endl;
				reafiseaza = true;
				break;
			case 2:
				cout << endl;
				adaugaUnElev();
				cout << "Noul elev a fost adaugat in lista" << endl;
				cout << endl;
				reafiseaza = true;
				break;
			case 3:
				cout << endl;
				if (stergeElev())
					cout << "Elevul dorit a fost sters din lista." << endl;
				cout << endl;
				reafiseaza = true;
				break;
			case 4:
				cout << endl;

				char rasp;
				rasp = intreabaDaNu("Sunteti sigur ca doriti sa stergeti toti elevii? [D]a/[N]u: ");
				if (rasp == 'D') {
					internat->stergeTotiElevii();
					stergeElevi();
					cout << "Toti elevii au fost stersi" << endl;
				}

				cout << endl;
				reafiseaza = true;
				break;
			case 5:
				OptiuneAfiseazaTotiElevii();

				reafiseaza = true;
				break;
			case 6:
				return;
			default:
				cout << "Alege o optiune";
				reafiseaza = false;
		}
	}
}

void MeniuConfigInternat() {
	bool reafiseaza = true;
	int opt;
	int iVal, index;
	int iNrCamera, iSuprafata, iEtaj;

	while (true) {
		if (reafiseaza) {
			cout << "1. Incarca setari predefinite pentru internat" << endl;
			cout << "2. Seteaza numele, adresa si programul de vizita" << endl;
			cout << "3. Seteaza lungimea, latimea si numarul de etaje" << endl;
			cout << "4. Adaugare camera" << endl;
			cout << "5. Stergere camera" << endl;
			cout << "6. Sterge toate camerele" << endl;
			cout << "7. Afisare date generale despre internat" << endl;
			cout << "8. Afisare toate camerele" << endl;
			cout << "9. Afiseaza camerele de pe un singur etaj" << endl;
			cout << "10. Meniul precedent" << endl;
			cout << "Alege optiunea dorita: ";
		}
		cin >> opt;

		switch (opt) {
			case 1:
				cout << endl;
				configurarePredefInternat();
				cout << "Setarile au fost incarcate cu succes!!!!" << endl;
				cout << endl;
				reafiseaza = true;
				break;
			case 2:
				cout << endl;

				cout << "Nume: "; cin >> inBuff;
				internat->setNume(inBuff);
				cout << "Adresa: "; cin >> inBuff;
				internat->setAdresa(inBuff);
				cout << "Program de vizita: "; cin >> inBuff;
				internat->setProgramVizita(inBuff);
				cout << "Setarile au fost efectuate cu succes!!!!" << endl;

				cout << endl;
				reafiseaza = true;
				break;
			case 3:
				cout << endl;

				cout << "Lungime: "; cin >> iVal;
				internat->setLungime(iVal);
				cout << "Latime: "; cin >> iVal;
				internat->setLatime(iVal);
				cout << "Etaje: "; cin >> iVal;
				internat->setEtaje(iVal);
				cout << "Setarile au fost efectuate cu succes!!!" << endl;

				cout << endl;
				reafiseaza = true;
				break;
			case 4:
				cout << endl;

				cout << "Numarul camerei este: "; cin >> iNrCamera;
				cout << "Suprafata este: "; cin >> iSuprafata;
				cout << "Etajul este: "; cin >> iEtaj;
				if (internat->existaEtaj(iEtaj)) {
					internat->adaugaCamera(iNrCamera, iSuprafata, iEtaj);
					cout << "Camera a fost adaugata." << endl;
				}
				else {
					cout << "Etajul nu exista!!!" << endl;
					cout << "Camera nu a fost adaugata!!!!" << endl;
				}

				cout << endl;
				reafiseaza = true;
				break;
			case 5:
				cout << endl;

				cout << "Alege indexul coresupunzator camerei sau apasa -1 pentru a anula stergerea" << endl;
				while (true) {
					cout << "Indexul camerei este urmatorul "; cin >> index;
                    if (index == -1)
						break;
					else if ((index < 0) || (index >= internat->getNrCamere()))
						cout << "Alege indexul coresupunzator sau apasa -1 pentru a anula stergerea" << endl;
					else {
						internat->stergeCamera(index);
						cout << "Camera a fost stearsa cu succes!!!!" << endl;
						break;
					}
				}

				cout << endl;
				reafiseaza = true;
				break;
			case 6:
				cout << endl;

				char rasp;
				rasp = intreabaDaNu("Sigur doresti sa stergi toate camerele? [D]a/[N]u: ");
				if (rasp == 'D') {
					internat->stergeToateCamerele();
					cout << "Camerele au fost sterse" << endl;
				}

				cout << endl;
				reafiseaza = true;
				break;
			case 7:
				cout << endl;

				cout << "Numele internatului este: " << internat->getNume() << endl;
				cout << "Adresa internatului este: " << internat->getAdresa() << endl;
				cout << "Programul de vizita este: " << internat->getProgramVizita() << endl;
				cout << "Lungimea este: " << internat->getLungime() << endl;
				cout << "Latimea este: " << internat->getLatime() << endl;
				cout << "Suprafata este: " << internat->getSuprafata() << endl;
				cout << "Etajele sunt: " << internat->getEtaje() << endl;

				cout << endl;
				reafiseaza = true;
				break;
			case 8:
				OptiuneAfiseazaToateCamerele();

				reafiseaza = true;
				break;
			case 9:
				OptiuneAfiseazaEtaj();

				reafiseaza = true;
				break;
			case 10:
				return;
			default:
				cout << "Alege o optiune:";
				reafiseaza = false;
		}
	}
}

void MeniuCazare() {
	bool reafiseaza = true;
	bool OK;
	int opt;
	int iVal, index;

	while (true) {
		if (reafiseaza) {
			cout << "1. Afisare camere" << endl;
			cout << "2. Afisare camere pe un etaj" << endl;
			cout << "3. Afisare toti elevii" << endl;
			cout << "4. Afisare toti elevii dintr-o camera" << endl;
			cout << "5. Cazeaza un elev" << endl;
			cout << "6. Decazeaza un elev" << endl;
			cout << "7. Meniul precedent" << endl;
			cout << "Alege optiunea dorita: ";
		}
		cin >> opt;

		switch (opt) {
			case 1:
				OptiuneAfiseazaToateCamerele();

				reafiseaza = true;
				break;
			case 2:
				OptiuneAfiseazaEtaj();

				reafiseaza = true;
				break;
			case 3:
				OptiuneAfiseazaTotiElevii();

				reafiseaza = true;
				break;
			case 4:
				cout << endl;

				cout << "Numarul camerei este urmatorul: "; cin >> iVal;
				index = internat->cautaCamera(iVal);
				if (index != -1)
					(*internat)[index]->afiseazaElevii();
				else
					cout << "Nu exista camera cu acest numar!!!" << endl;

				cout << endl;
				reafiseaza = true;
				break;
			case 5:
				OptiuneCazeazaElev();

				reafiseaza = true;
				break;
			case 6:
				OptiuneDecazeazaElev();

				reafiseaza = true;
				break;
			case 7:
				return;
			default:
				cout << "Alege o optiune ";
				reafiseaza = false;
		}
	}
}

int main(int argc, char* argv[])
{
	MeniuPrincipal();

	delete internat;
	stergeElevi();

	return 0;
}
