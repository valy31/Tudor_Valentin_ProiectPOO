#include <iostream>
#include <fstream>
using namespace std;

/*Vitrina unui magazin*/

class Vitrina {
public:
	virtual void afisareVitrina() = 0;
	virtual ~Vitrina() {}
};

class Magazin {
public:
	virtual void afisareMagazin() = 0;
	virtual ~Magazin() {}
};

class Erou: public Vitrina, public Magazin {
private:
	string nume;
	float pretErou;
	static float TVA;
	const int anAparitie;
	int nrCutii;
	int* bucati;

public:
	void afisareVitrina() {
		cout << "Eroul "<<nume<<" a fost pus in vitrina\n";
	}

	void afisareMagazin() {
		cout << "Eroul "<<nume<<" apare in magazin\n";
	}

	string getNume() {
		return this->nume;
	}

	void setNume(string nume) {
		if (nume.length() > 3) {
			this->nume = nume;
		}
	}

	float getPretErou() {
		return this->pretErou;
	}

	void setPretErou(float pret) {
		if (pret > 0) {
			this->pretErou = pret;
		}
	}

	int getAnAparitie() {
		return this->anAparitie;
	}

	int getNrCutii() {
		return this->nrCutii;
	}

	void setNrCutii(int nrc) {
		if (nrc > 0) {
			this->nrCutii = nrc;
		}
	}

	int getBucati(int c) {
		for (int i = 0; i < nrCutii; i++) {
			if (i == c) {
				return this->bucati[i];
			}
		}
	}

	void setBucati(int nrCutie, int nrBuc) {
		for (int i = 0; i < nrCutii; i++) {
			if (i == nrCutie) {
				this->bucati[i] = nrBuc;
			}
		}
	}

	Erou() :anAparitie(2012) {
		this->nume = "Spiderman";
		this->pretErou = 45;
		this->nrCutii = 3;
		this->bucati = new int[this->nrCutii];
		for (int i = 0; i < this->nrCutii; i++) {
			this->bucati[i] = 2 + i;
		}
	}

	Erou(string nume, float pretErou, const int anAparitie, int nrCutii, int* bucati) :anAparitie(anAparitie) {
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
		int totalBuc = 0;
		cout << "Nume erou: " << this->nume << "\nPret: " << this->pretErou << endl;
		cout << "An aparitie: " << this->anAparitie << "\nNr cutii: " << this->nrCutii << "\nBucati: ";
		for (int i = 0; i < this->nrCutii; i++) {
			cout << this->bucati[i] << " ";
			totalBuc = totalBuc + this->bucati[i];
		}
		cout << " Total: " << totalBuc;
		cout << "\nTVA: " << TVA << "\n----------" << endl;;
	}

	Erou(const Erou& erou) : anAparitie(erou.anAparitie) {
		this->nume = erou.nume;
		this->pretErou = erou.pretErou;
		this->nrCutii = erou.nrCutii;
		this->bucati = new int[this->nrCutii];
		for (int i = 0; i < this->nrCutii; i++) {
			this->bucati[i] = erou.bucati[i];
		}
	}

	~Erou() {
		if (this->bucati != NULL) {
			delete[]this->bucati;
			this->bucati = NULL;
		}
	}

	static float getTVA() {
		return TVA;
	}

	static void setTVA(float TVAnou) {
		TVA = TVAnou;
	}

	Erou& operator=(const Erou& e) {
		if (this != &e) {
			this->nume = e.nume;
			this->pretErou = e.pretErou;
			this->nrCutii = e.nrCutii;
			if (this->bucati != NULL) {
				delete[]this->bucati;
			}

			this->bucati = new int[this->nrCutii];
			for (int i = 0; i < this->nrCutii; i++)
			{
				this->bucati[i] = e.bucati[i];
			}
		}
		return *this;
	}

	bool operator<(Erou e) {
		return this->anAparitie < e.anAparitie;
	}

	bool operator>(Erou e) {
		return this->anAparitie > e.anAparitie;
	}

	friend istream& operator>>(istream& ist, Erou& e) {
		cout << "Nume: "; ist >> e.nume;
		cout << "Pret erou: "; ist >> e.pretErou;
		cout << "Nr cutii: "; ist >> e.nrCutii;
		if (e.bucati) {
			delete[]e.bucati;
		}
		e.bucati = new int[e.nrCutii];
		cout << "Nr bucati/cutie: ";
		for (int i = 0; i < e.nrCutii; i++) {
			ist >> e.bucati[i];
		}
		return ist;
	}

	int& operator[](int idx) {
		if (idx >= 0 && idx < nrCutii)
			return this->bucati[idx];
		throw 404;
	}

	int operator()() {
		int s = 0;
		for (int i = 0; i < this->nrCutii; i++)
			s = s + this->bucati[i];
		return s;
	} //returneaza nr de figurine total pentru un anumit erou

	friend int valoareErou(Erou e);

	void scrieErouInFisierBin(char* numeFisier) {
		ofstream fisier(numeFisier, std::ios::binary);

			Erou erou;
			fisier.write(erou.nume.c_str(), erou.nume.size() + 1);
			fisier.write((const char*)&erou.pretErou, sizeof(float));
			fisier.write((const char*)&erou.anAparitie, sizeof(int));
			fisier.write((const char*)&erou.nrCutii, sizeof(int));

			for (int i = 0; i < erou.nrCutii; i++) {
				fisier.write((const char*)&erou.bucati[i], sizeof(int));
			}

			fisier.close();
			std::cout << "Eroul a fost scris in fisierul binar.\n";
	}
};
float Erou::TVA = 10;

int valoareErou(Erou e) {
	float pret = e.getPretErou(); int totalBuc = 0, valoare;

	for (int i = 0; i < e.getNrCutii(); i++) {
		totalBuc = totalBuc + e.getBucati(i);
	}
	valoare = pret * totalBuc;

	return valoare;
}

/*-------------------------------------------------------*/

class Carte: public Vitrina, public Magazin {
private:
	string titlu;
	float pretCarte;
	const string limba;
	string categorie;
	int nrVolume;
	int* nrCarti;
	static float TVA;

public:
	void afisareVitrina() {
		cout << "Cartea " << titlu << " a fost pus in vitrina\n";
	}

	void afisareMagazin() {
		cout << "Cartea " << titlu << " apare in magazin\n";
	}

	string getTitlu() {
		return this->titlu;
	}

	void setTitlu(string titlu) {
		if (titlu.length() > 2) {
			this->titlu = titlu;
		}
	}

	float getPretCarte() {
		return this->pretCarte;
	}

	void setPretCarte(float pret) {
		if (pret > 10) {
			this->pretCarte = pret;
		}
	}

	string getLimba() {
		return this->limba;
	}

	string getCategorie() {
		return this->categorie;
	}

	void setCategorie(string categ) {
		if (categ.length() > 1) {
			this->categorie = categ;
		}
	}

	int getNrVolume() {
		return this->nrVolume;
	}

	void setNrVolume(int nrv) {
		if (nrv > 0) {
			this->nrVolume = nrv;
		}
	}

	int getNrCarti(int vol) {
		for (int i = 0; i < nrVolume; i++) {
			if (i == vol) {
				return this->nrCarti[i];
			}
		}
	}

	Carte() :limba("Romana") {
		this->titlu = "Morometii";
		this->pretCarte = 60;
		this->categorie = "Istoric";
		this->nrVolume = 2;
		this->nrCarti = new int[nrVolume];
		for (int i = 0; i < nrVolume; i++) {
			this->nrCarti[i] = 3;
		}
	}

	Carte(string titlu, float pretCarte, int* nrCarti) :categorie("Istoric"), nrVolume(1), limba("Romana") {
		this->titlu = titlu;
		this->pretCarte = pretCarte;
		this->nrCarti = new int[this->nrVolume];
		for (int i = 0; i < nrVolume; i++) {
			this->nrCarti[i] = nrCarti[i];
		}
	}

	Carte(string titlu, float pretCarte, const string limba, string categorie, int nrVolume, int* nrCarti) : limba(limba) {
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

	Carte(const Carte& carte) : limba(carte.limba) {
		this->titlu = carte.titlu;
		this->pretCarte = carte.pretCarte;
		this->categorie = carte.categorie;
		this->nrVolume = carte.nrVolume;
		this->nrCarti = new int[this->nrVolume];
		for (int i = 0; i < this->nrVolume; i++) {
			this->nrCarti[i] = carte.nrCarti[i];
		}
	}

	~Carte() {
		if (this->nrCarti != NULL) {
			delete[]this->nrCarti;
			this->nrCarti = NULL;
		}
	}

	static float getTVA() {
		return TVA;
	}

	static void setTVA(float TVAnou) {
		TVA = TVAnou;
	}

	Carte& operator=(const Carte& c) {
		if (this != &c) {
			this->titlu = c.titlu;
			this->pretCarte = c.pretCarte;
			this->categorie = c.categorie;
			this->nrVolume = c.nrVolume;
			if (this->nrCarti != NULL) {
				delete[]this->nrCarti;
			}

			this->nrCarti = new int[this->nrVolume];
			for (int i = 0; i < this->nrVolume; i++)
			{
				this->nrCarti[i] = c.nrCarti[i];
			}
		}
		return *this;
	}

	bool operator<(Carte c) {
		return this->nrVolume < c.nrVolume;
	}

	bool operator>(Carte c) {
		return this->nrVolume > c.nrVolume;
	}

	friend istream& operator>>(istream& ist, Carte& c) {
		cout << "Titlu: "; ist >> c.titlu;
		cout << "Pret carte: "; ist >> c.pretCarte;
		cout << "Categorie: "; ist >> c.categorie;
		cout << "Nr volume: "; ist >> c.nrVolume;
		if (c.nrCarti) {
			delete[]c.nrCarti;
		}
		c.nrCarti = new int[c.nrVolume];
		cout << "Nr carti/vol: ";
		for (int i = 0; i < c.nrVolume; i++) {
			ist >> c.nrCarti[i];
		}
		return ist;
	}

	int operator()() {
		int s = 0;
		for (int i = 0; i < this->nrVolume; i++)
			s = s + this->nrCarti[i];
		return s;
	} //returneaza nr total de carti disponibile pentru un anumit titlu

	int& operator[](int idx) {
		if (idx >= 0 && idx < nrVolume)
			return this->nrCarti[idx];
	}

	void scrieCarte(const char* fisier) {
		ofstream fout(fisier);

			fout << "Titlu: " << getTitlu() << "\n";
			fout << "Limba: " << getLimba() << "\n";
			fout << "Categorie: " << getCategorie() << "\n";
			fout << "Pret: " << getPretCarte() << "\n";
			fout << "Nr volume: " << getNrVolume() << "\n";
			fout << "Nr carti/vol: ";
			for (int i = 0; i < getNrVolume(); i++) {
				fout << getNrCarti(i) << " ";
			}
			fout << "\nTVA: " << Carte::getTVA() << "\n";
			fout << "----------\n";

			fout.close();
			cout << "Cartea a fost scrisa in fisier.\n";
	}

};
float Carte::TVA = 5;

/*-------------------------------------------------------*/

class JocVideo: public Vitrina, public Magazin {
private:
	string denumire;
	const string productie;
	float pretJoc;
	int nrSeturi;
	int* setJocuri;
	static float reducere;

public:
	void afisareVitrina() {
		cout << "Jocul " << denumire << " a fost pus in vitrina\n";
	}

	void afisareMagazin() {
		cout << "Jocul " << denumire << " apare in magazin\n";
	}

	string getDenumire() {
		return this->denumire;
	}

	void setDenumire(string den) {
		if (den.length() > 3) {
			this->denumire = den;
		}
	}

	string getProductie() {
		return this->productie;
	}

	float getPretJoc() {
		return this->pretJoc;
	}

	void setPretJoc(float pret) {
		if (pret > 10) {
			this->pretJoc = pret;
		}
	}

	int getNrSeturi() {
		return this->nrSeturi;
	}

	void setNrSeturi(int nrs) {
		if (nrs > 0) {
			this->nrSeturi = nrs;
		}
	}

	int getSetJocuri(int nrs) {
		for (int i = 0; i < nrSeturi; i++) {
			if (i == nrs) {
				return this->setJocuri[i];
			}
		}
	}

	JocVideo() :productie("Rockstar") {
		this->denumire = "Grand Theft Auto";
		this->pretJoc = 89;
		this->nrSeturi = 4;
		this->setJocuri = new int[this->nrSeturi];
		for (int i = 0; i < this->nrSeturi; i++) {
			this->setJocuri[i] = i + 1;
		}
	}

	JocVideo(string denumire, const string prod, float pret, int* setJocuri) :nrSeturi(2), productie(prod) {
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

	JocVideo(const JocVideo& joc) : productie(joc.productie) {
		this->denumire = joc.denumire;
		this->pretJoc = joc.pretJoc;
		this->nrSeturi = joc.nrSeturi;
		this->setJocuri = new int[this->nrSeturi];
		for (int i = 0; i < this->nrSeturi; i++) {
			this->setJocuri[i] = joc.setJocuri[i];
		}
	}

	~JocVideo() {
		if (this->setJocuri != NULL) {
			delete[]this->setJocuri;
			this->setJocuri = NULL;
		}
	}

	static float getReducere() {
		return reducere;
	}

	static void setReducere(float reducereNoua) {
		reducere = reducereNoua;
	}

	JocVideo operator=(const JocVideo& j) {
		if (this != &j) {
			this->denumire = j.denumire;
			this->pretJoc = j.pretJoc;
			this->nrSeturi = j.nrSeturi;
			if (this->setJocuri != NULL) {
				delete[]this->setJocuri;
			}

			this->setJocuri = new int[this->nrSeturi];
			for (int i = 0; i < this->nrSeturi; i++)
			{
				this->setJocuri[i] = j.setJocuri[i];
			}
		}
		return *this;
	}

	bool operator<(JocVideo j) {
		return this->pretJoc < j.pretJoc;
	}

	bool operator>(JocVideo j) {
		return this->pretJoc > j.pretJoc;
	}

	friend istream& operator>>(istream& ist, JocVideo& j) {
		cout << "Denumire joc: "; ist >> j.denumire;
		cout << "Pret joc: "; ist >> j.pretJoc;
		cout << "Nr seturi/joc: "; ist >> j.nrSeturi;
		if (j.setJocuri) {
			delete[]j.setJocuri;
		}
		j.setJocuri = new int[j.nrSeturi];
		cout << "Nr jocuri din fiecare set: ";
		for (int i = 0; i < j.nrSeturi; i++) {
			ist >> j.setJocuri[i];
		}
		return ist;
	}

	int operator()() {
		int s = 0;
		for (int i = 0; i < this->nrSeturi; i++)
			s = s + this->setJocuri[i];
		return s;
	} //returneaza nr total de jocuri disponibile pentru un anumit joc

	friend void jocPretMaiMicDe(JocVideo j, float pret);

	int& operator[](int idx) {
		if (idx >= 0 && idx < nrSeturi)
			return this->setJocuri[idx];
	}

	void scrieJocVideo(const char* fisier) {
		ofstream fout(fisier);

			fout << "Denumire joc: " << getDenumire() << "\n";
			fout << "Productie: " << getProductie() << "\n";
			fout << "Pret de inceput / set: " << getPretJoc() << "\n";
			fout << "Seturi disponibile: " << getNrSeturi() << "\n";
			fout << "Jocuri/set: ";
			for (int i = 0; i < getNrSeturi(); i++) {
				fout << getSetJocuri(i) << " ";
			}
			fout << "\nReducere aplicata: " << JocVideo::getReducere() * 100 << "%\n";
			fout << "----------\n";
			fout.close();
			std::cout << "Jocul video a fost scris in fisier.\n";
	}
};
float JocVideo::reducere = 0.1;

void jocPretMaiMicDe(JocVideo j, float pret) {
	if (j.getPretJoc() < pret) {
		cout << "Pretul jocului este mai mic de " << pret << " lei. Costa " << j.getPretJoc() << " lei" << endl;
	}
}

class Echipa {
private:
	Erou membruEchipa[5];
	string numeEchipa;
	int nrMembriMax;

public:
	Echipa() {
		this->numeEchipa = "Avengers";
		this->nrMembriMax = 10;
	}

	Echipa(string nume, int nrMax) {
		this->numeEchipa = nume;
		this->nrMembriMax = nrMax;
	}

	string getNumeEchipa() {
		return numeEchipa;
	}

	void setNumeEchipa(string nume) {
		this->numeEchipa = nume;
	}

	int getNrMembriMax() {
		return nrMembriMax;
	}

	void setNrMembriMax(int nrMax) {
		nrMembriMax = nrMax;
	}

	bool operator<(const Echipa& ech) {
		return this->nrMembriMax < ech.nrMembriMax;
	}

	bool operator>(const Echipa& ech) {
		return this->nrMembriMax > ech.nrMembriMax;
	}

	Echipa operator=(const Echipa& e) {
		if (this != &e) {
			this->numeEchipa = e.numeEchipa;
			this->nrMembriMax = e.nrMembriMax;
			
			for (int i = 0; i < this->nrMembriMax; i++)
			{
				this->membruEchipa[i] = e.membruEchipa[i];
			}
		}
		return *this;
	}

	void scrieEchipaInFisierBin(const char* numeFisier) {
		ofstream fisier(numeFisier, std::ios::binary);
			Echipa echipa;

			fisier.write(echipa.numeEchipa.c_str(), echipa.numeEchipa.length() + 1);
			fisier.write((const char*)(&echipa.nrMembriMax), sizeof(int));

			for (int i = 0; i < 5; i++) {
				// Scrie datele pentru fiecare membru al echipei
				fisier.write(echipa.membruEchipa[i].getNume().c_str(), echipa.membruEchipa[i].getNume().length() + 1);
				
				float pretErou = echipa.membruEchipa[i].getPretErou();
				fisier.write((const char*)&pretErou, sizeof(float));

				int anAparitie = echipa.membruEchipa[i].getAnAparitie();
				fisier.write((const char*)&anAparitie, sizeof(int));

				int nrCutii = echipa.membruEchipa[i].getNrCutii();
				fisier.write((const char*)&nrCutii, sizeof(int));

				for (int j = 0; j < echipa.membruEchipa[i].getNrCutii(); j++) {
					float nrBucati = echipa.membruEchipa[i].getBucati(j);
					fisier.write((const char*)&nrBucati, sizeof(int));
				}
			}

			fisier.close();
			std::cout << "Echipa a fost scrisa in fisierul binar.\n";
		}
};

class SuperErou : public Erou {
private:
	string superputere;
public:
	
	SuperErou(string nume, float pretErou, const int anAparitie, int nrCutii, int* bucati, string superputere)
		: Erou(nume, pretErou, anAparitie, nrCutii, bucati), superputere(superputere) {}

	SuperErou() : Erou(), superputere("Nu are.") {
	}

	string getSuperputere() const {
		return superputere;
	}

	void setSuperputere(string superputere) {
		this->superputere = superputere;
	}

	void afisareSuperputere() {
		cout << "Superputerea eroului " << getNume() << " este: " << superputere << endl;
	}

	SuperErou& operator=(const SuperErou& super) {
		if (this != &super) {
			Erou::operator=(super); 
			superputere = super.superputere;
		}
		return *this;
	}
};


class SerieJoc : public JocVideo {
private:
	string genJoc;

public:
	
	SerieJoc(string denumire, const string productie, float pretJoc, int* setJocuri, string genJoc)
		: JocVideo(denumire, productie, pretJoc, setJocuri), genJoc(genJoc) {}

	SerieJoc() : JocVideo(), genJoc("Adventure") {
	}

	string getGenJoc() {
		return genJoc;
	}

	void setGenJoc(string genJoc) {
		this->genJoc = genJoc;
	}

	void afisareGenJoc() {
		cout << "Genul jocului " << getDenumire() << " este: " << genJoc << endl;
	}
	
	SerieJoc& operator=(const SerieJoc& sj) {
		if (this != &sj) {
			JocVideo::operator=(sj); 
			genJoc = sj.genJoc;
		}
		return *this;
	}
};

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
		nrCarti[i] = i + 1;
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

	cout << e1.getNume(); e1.setNume("Spider-Man"); cout << " redenumit in " << e1.getNume() << endl;

	cout << "Nr carti din volumul 2 Morometii: " << c1.getNrCarti(1) << endl; /* Incepe de la 0 */

	cout << "Pretul jocului " << j2.getDenumire() << " -> " << j2.getPretJoc() << " creste cu 10 ron -> "; j2.setPretJoc(j2.getPretJoc() + 10);
	cout << j2.getPretJoc() << endl;

	cout << "Valoarea totala a figurinei 1 - " << e1.getNume() << " este de " << valoareErou(e1) << " ron" << endl;
	cout << "Pentru jocul 1 - " << j1.getDenumire() << endl; jocPretMaiMicDe(j1, 200);

	Erou e4 = e1;
	e4.afisare();

	Carte c4 = c3;
	c4.afisare();

	JocVideo j4 = j2;
	j2.afisare();

	if (c3 < c1) {
		cout << c3.getTitlu() << " are mai putine volume fata de " << c1.getTitlu() << endl;
	}
	else {
		cout << c3.getTitlu() << " are mai multe volume / acelasi nr de volume ca " << c1.getTitlu() << endl;
	}

	if (j1 > j2) {
		cout << j1.getDenumire() << " are pretul mai mare decat " << j2.getDenumire() << endl;
	}
	else {
		cout << j1.getDenumire() << " are pretul mai mic sau egal ca " << j2.getDenumire() << endl;
	}

	if (e2 < e3) {
		cout << e2.getNume() << " a aparut inainte lui " << e3.getNume() << endl;
	}
	else {
		cout << e2.getNume() << " a aparut dupa sau odata cu " << e3.getNume() << endl;
	}
	cout << "Citire erou 5:" << endl;
	Erou e5; cin >> e5;		cout << "-----" << endl;
	e5.afisare();			cout << endl;
	cout << "Nr figurine pentru " << e5.getNume() << ": " << e5() << endl;

	cout << "Citire carte 5:" << endl;
	Carte c5; cin >> c5;	cout << "-----" << endl;
	c5.afisare();			cout << endl;
	cout << "Nr carti pentru " << c5.getTitlu() << ": " << c5() << endl;

	cout << "Citire joc 5:" << endl;
	JocVideo j5; cin >> j5;	cout << "-----" << endl;
	j5.afisare();			cout << endl;
	cout << "Nr jocuri pentru " << j5.getDenumire() << ": " << j5() << endl;

	Erou erouVector[10];
	cout << "\nUrmeaza citirea a 3 eroi dintr-un vector:" << endl;
	for (int i = 0; i < 3; i++) {
		cin >> erouVector[i];
	}
	cout << "-----" << endl;
	for (int i = 0; i < 3; i++) {
		erouVector[i].afisare();
	}

	Carte carteVector[10];
	cout << "\nUrmeaza citirea a 3 carti dintr-un vector:" << endl;
	for (int i = 0; i < 3; i++) {
		cin >> carteVector[i];
	}
	cout << "-----" << endl;
	for (int i = 0; i < 3; i++) {
		carteVector[i].afisare();
	}

	JocVideo jocVector[10];
	cout << "\nUrmeaza citirea a 3 jocuri dintr-un vector:" << endl;
	for (int i = 0; i < 3; i++) {
		cin >> jocVector[i];
	}
	cout << "-----" << endl;
	for (int i = 0; i < 3; i++) {
		jocVector[i].afisare();
	}

	Carte carteMatrice[10][10];
	cout << "\nUrmeaza citirea a 4 carti dintr-o matrice:" << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << "Carte[" << i << "][" << j << "]:" << endl;
			cin >> carteMatrice[i][j];
		}
	}
	cout << "-----" << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			carteMatrice[i][j].afisare();
		}
		cout << endl;
	} 
	Carte c1;
	c1.scrieCarte("carti.txt");
	JocVideo j1;
	j1.scrieJocVideo("jocuri.txt");

	Echipa ech;
	ech.scrieEchipaInFisierBin("echipa.bin");

	Erou e;
	SuperErou super("Hulk", 25, 2003, 1, bucati, "Forta infinita");
	super.afisare();
	super.afisareSuperputere(); cout << endl;

	JocVideo j;
	SerieJoc sj1("Warcraft 3", "Blizzard", 50, setJocuri, "Strategy-MMORPG");
	sj1.afisare();
	sj1.afisareGenJoc(); cout << endl;
	
	SerieJoc sj2;
	sj2.afisare();
	sj2.setGenJoc("Action");
	sj2.afisareGenJoc();

	SuperErou supererou;
	Erou* erouP = &supererou; 
	erouP->afisare(); 
	supererou.afisareSuperputere(); cout << endl;

	SerieJoc seriejoc;
	JocVideo* JocVideoP = &seriejoc;
	JocVideoP->afisare(); 
	seriejoc.afisareGenJoc(); cout << endl;

	Magazin* produseMagazin[] = { new Erou("Hulk",25,bucati), new Carte("Morometii",25,nrCarti), new JocVideo("FC 24",setJocuri) };
	Vitrina* produseVitrina[] = { new Erou("Hulk",25,bucati), new Carte("Morometii",25,nrCarti), new JocVideo("FC 24",setJocuri) };
	
	for (int i = 0; i <= 2; i++) {
		produseMagazin[i]->afisareMagazin();
		produseVitrina[i]->afisareVitrina();
	}
	
}
