#include <iostream>
using namespace std;

/*Vitrina unui magazin*/

class Erou {
public:
	string nume;
	float pretErou;
	static float TVA;
	const int anAparitie;
	int nrCutii;
	int* bucati;

	Erou() :anAparitie(2012) {
		this->nume = "Spiderman";
		this->pretErou = 45;
		this->nrCutii = 3;
		this->bucati = new int[this->nrCutii];
		for (int i = 0; i < this->nrCutii; i++) {
			this->bucati[i] = 2 + i;
		}
	}

	Erou(string nume, float pretErou, const int anAparitie, int nrCutii, int* bucati):anAparitie(anAparitie){
		this->nume = nume;
		this->pretErou = pretErou;
		this->nrCutii = nrCutii;
		this->bucati = new int[this->nrCutii];
		for (int i = 0; i < nrCutii; i++) {
			this->bucati[i] = bucati[i];
		}
	}

	Erou(string nume, float pretErou, int* bucati) :anAparitie(1998), nrCutii(1) {
		this->nume = nume;
		this->pretErou = pretErou;
		this->bucati = new int[this->nrCutii];
		for (int i = 0; i < nrCutii; i++) {
			this->bucati[i] = bucati[i];
		}
	}
	
	void afisare() {
		int totalBuc=0;
		cout << "Nume erou: " << this->nume << "\nPret: " << this->pretErou << endl;
		cout << "An aparitie: " << this->anAparitie << "\nNr cutii: " << this->nrCutii << "\nBucati: ";
		for (int i = 0; i < this->nrCutii; i++) {
			cout << this->bucati[i] << " ";
			totalBuc = totalBuc + this->bucati[i];
		}
		cout << " Total: " << totalBuc;
		cout << "\nTVA: " << TVA << "\n----------" << endl;;
	}

	~Erou() {
		if (this->bucati != NULL) {
			delete[]this->bucati;
			this->bucati = NULL;
		}
	}

		static void setTVA(float TVAnou) {
			TVA = TVAnou;
		}
};
float Erou::TVA = 10;

/*-------------------------------------------------------*/

class Carte {
public:
	string titlu;
	float pretCarte;
	const string limba;
	string categorie;
	int nrVolume;
	int* nrCarti;
	static float TVA;

	Carte():limba("Romana") {
		this->titlu = "Morometii";
		this->pretCarte = 60;
		this->categorie = "Istoric";
		this->nrVolume = 2;
		this->nrCarti = new int[nrVolume];
		for (int i = 0; i < nrVolume; i++) {
			this->nrCarti[i] = 3;
		}
	}

	Carte(string titlu, float pretCarte,int* nrCarti) :categorie("Istoric"), nrVolume(1), limba("Romana") {
		this->titlu = titlu;
		this->pretCarte = pretCarte;
		this->nrCarti = new int[this->nrVolume];
		for (int i = 0; i < nrVolume; i++) {
			this->nrCarti[i] = nrCarti[i];
		}
	}

	Carte(string titlu, float pretCarte, const string limba,string categorie, int nrVolume, int* nrCarti) : limba(limba) {
		this->titlu = titlu;
		this->pretCarte = pretCarte;
		this->categorie = categorie;
		this->nrVolume = nrVolume;
		this->nrCarti = nrCarti;
		this->nrCarti = new int[this->nrVolume];
		for (int i = 0; i < nrVolume; i++) {
			this->nrCarti[i] = nrCarti[i];
		}
	}

	void afisare() {
		cout << "Titlu: " << this->titlu << "\nLimba: " << this->limba << "\nCategorie: " << this->categorie;
		cout << "\nPret: " << this->pretCarte << "\nNr volume: " << this->nrVolume << "\nNr carti/vol: ";
		for (int i = 0; i < nrVolume; i++) {
			cout << this->nrCarti[i] << " ";
		}
		cout << "\nTVA: " << TVA << "\n----------" << endl;
	}

	~Carte() {
		if (this->nrCarti != NULL) {
			delete[]this->nrCarti;
			this->nrCarti = NULL;
		}
	}

	static void setTVA(float TVAnou) {
		TVA = TVAnou;
	}
};
float Carte::TVA = 5;

/*-------------------------------------------------------*/

class JocVideo {
public:
	string denumire;
	const string productie;
	float pretJoc;
	int nrSeturi;
	int* setJocuri;
	static float reducere;

	JocVideo():productie("Rockstar") {
		this->denumire = "Grand Theft Auto";
		this->pretJoc = 89;
		this->nrSeturi = 4;
		this->setJocuri = new int[this->nrSeturi];
		for (int i = 0; i < this->nrSeturi; i++) {
			this->setJocuri[i] = i + 1;
		}
	}

	JocVideo(string denumire, const string prod, float pret, int* setJocuri) :nrSeturi(2),productie(prod) {
		this->denumire = denumire;
		this->pretJoc = pret;
		this->setJocuri = new int[this->nrSeturi];
		for (int i = 0; i < nrSeturi; i++) {
			this->setJocuri[i] = setJocuri[i];
		}
	}

	JocVideo(string denumire, int* setJocuri) :nrSeturi(3), productie("EA Games"), pretJoc(400) {
		this->denumire = denumire;
		this->setJocuri = new int[this->nrSeturi];
		for (int i = 0; i < nrSeturi; i++) {
			this->setJocuri[i] = setJocuri[i];
		}
	}

	void afisare() {
		cout << "Denumire joc: " << this->denumire << "\nProductie: " << this->productie << "\nPret de inceput / set: " << this->pretJoc;
		cout << "\nSeturi disponibile: " << this->nrSeturi << "\nJocuri/set: ";
		for (int i = 0; i < this->nrSeturi; i++) {
			cout << this->setJocuri[i] << " ";
		}
		cout << "\nReducere aplicata: " << reducere * 100 << "%";
		cout << "\n----------" << endl;
	}

	~JocVideo() {
		if (this->setJocuri != NULL) {
			delete[]this->setJocuri;
			this->setJocuri = NULL;
		}
	}
	
	static void setReducere(float reducereNoua) {
		reducere = reducereNoua;
	}
};
float JocVideo::reducere = 0.1;

void main() {
	cout << "Produse din vitrina: " << "\n\nMachete eroi\n" << endl;
	Erou e1;
	e1.afisare(); /*Eroul 1 creat cu constructorul 1*/
	
	int* bucati = new int[3];
	for (int i = 0; i < 3; i++) {
		bucati[i] = 1 + i;
	}
	
	Erou e2("Hulk", 50, 2010, 2, bucati);
	e2.afisare(); /*Eroul 2 creat cu constructorul 2*/
	Erou::setTVA(9);
	
	Erou e3("Batman", 125, bucati);
	e3.afisare(); /*Eroul 3 creat cu constructorul 3*/

	cout << "Carti\n" << endl;

	Carte c1;
	c1.afisare();

	int* nrCarti = new int[5];
	for (int i = 0; i < 5; i++) {
		nrCarti[i] = i+1;
	}

	Carte c2("Codul lui Da Vinci", 40, nrCarti);
	c2.afisare();
	Carte::setTVA(6);

	Carte c3("Poesii", 50, "Romana", "Poezii", 1, nrCarti);
	c3.afisare();

	cout << "Jocuri video\n" << endl;
	JocVideo j1;
	j1.afisare();

	int* setJocuri = new int[3];
	for (int i = 0; i < 3; i++) {
		setJocuri[i] = 1;
	}
	JocVideo j2("FC 24", "EA SPORTS", 250, setJocuri);
	j2.afisare();

	JocVideo::setReducere(0.05);
	JocVideo j3("Battlefield 1942", setJocuri);
	j3.afisare();
}
