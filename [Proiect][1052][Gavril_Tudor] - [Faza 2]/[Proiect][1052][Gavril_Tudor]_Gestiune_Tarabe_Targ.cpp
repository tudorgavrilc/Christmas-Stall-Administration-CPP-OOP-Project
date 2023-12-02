#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <map>
using namespace std;




class OperareFisiereBinare
{
	virtual void scriereInFisierBin(fstream& f) = 0;

};

class OperareFisiereText
{
	virtual void citireDinFisierText() = 0;
};







class Taraba :OperareFisiereBinare, OperareFisiereText
{

private:

	static const int editieTarg = 2022;
	float dimensiuneMetriPatrati = 0;
	char* numeTaraba = NULL;
	int nrClientiZi[5];
	int profit = 0;


public:

	virtual void afisareDescriereTaraba()
	{
		cout << "\nAceasta este o taraba simpla, o taraba cu de toate am putea spune, care nu are o tematica anume si care va poate oferi multe chestii variate.";
	}


	void citireDinFisierText()
	{
		ifstream f;
		f.open("tarabaluimarcu.txt", ifstream::in);
		if (f.is_open())
		{
			f >> *this;
			f.close();
		}
	}


	void scriereInFisierBin(fstream& f)
	{
		f.write((char*)&Taraba::editieTarg, sizeof(int));
		f.write((char*)&this->dimensiuneMetriPatrati, sizeof(float));
		int lg = strlen(this->numeTaraba) + 1;
		f.write(this->numeTaraba, lg);
		for (int i = 0; i < 5; i++)
		{
			f.write((char*)&this->nrClientiZi[i], sizeof(int));
		}
		f.write((char*)&this->profit, sizeof(int));
	}


	Taraba()
	{
		//cout << "\nApel constructor cu niciun parametru";
		this->numeTaraba = new char[strlen("FaraNume") + 1];
		strcpy(this->numeTaraba, "FaraNume");
		for (int i = 0; i < 5; i++)
			this->nrClientiZi[i] = 0;
	}


	Taraba(char* numeTaraba)
	{
		//cout << "\nApel constructor cu 1 parametru";
		this->numeTaraba = new char[strlen(numeTaraba) + 1];
		strcpy(this->numeTaraba, numeTaraba);
		for (int i = 0; i < 5; i++)
			this->nrClientiZi[i] = 0;
	}


	Taraba(float dimensiuneMetriPatrati, char* numeTaraba, int nrClientiZi[], int profit)
	{
		//cout << "\nApel constructor cu toti parametri";
		this->dimensiuneMetriPatrati = dimensiuneMetriPatrati;
		this->numeTaraba = new char[strlen(numeTaraba) + 1];
		strcpy(this->numeTaraba, numeTaraba);
		for (int i = 0; i < 5; i++)
			this->nrClientiZi[i] = nrClientiZi[i];
		this->profit = profit;
	}


	Taraba(const Taraba& t)
	{
		//cout << "\nApel constructor copiere";
		this->dimensiuneMetriPatrati = t.dimensiuneMetriPatrati;
		this->numeTaraba = new char[strlen(t.numeTaraba) + 1];
		strcpy(this->numeTaraba, t.numeTaraba);
		for (int i = 0; i < 5; i++)
			this->nrClientiZi[i] = t.nrClientiZi[i];
		this->profit = t.profit;
	}


	~Taraba()
	{
		//cout << "\nApel destructor";
		delete this->numeTaraba;
	}


	friend istream& operator>>(istream& in, Taraba& t)
	{
		cout << "\nIntroduceti dimensiunea tarabei in metri patrati: ";
		in >> t.dimensiuneMetriPatrati;

		delete[] t.numeTaraba;
		char aux[100];
		cout << "\nIntroduceti numele tarabei: ";
		in >> aux;
		t.numeTaraba = new char[strlen(aux) + 1];
		strcpy(t.numeTaraba, aux);

		cout << "\nIntroduceti nr. de clienti zilnici in cele 5 zile de targ: ";
		for (int i = 0; i < 5; i++)
			in >> t.nrClientiZi[i];

		cout << "\nIntroduceti profitul: ";
		in >> t.profit;
		return in;
	}


	friend ostream& operator<<(ostream& out, const Taraba& t)
	{
		out << "\n--------------------";
		out << "\nEditie targ: " << editieTarg;
		out << "\nDimensiune taraba in metri patrati: " << t.dimensiuneMetriPatrati;
		out << "\nNume taraba: " << t.numeTaraba;
		out << "\nNr. clienti pe zi: ";
		for (int i = 0; i < 5; i++)
			out << t.nrClientiZi[i] << " ";
		out << "\nProfit: " << t.profit;
		out << "\n--------------------";
		return out;
	}


	Taraba& operator=(const Taraba& t)
	{
		if (this != &t)
		{
			delete[] this->numeTaraba;
			this->dimensiuneMetriPatrati = t.dimensiuneMetriPatrati;
			this->numeTaraba = new char[strlen(t.numeTaraba) + 1];
			strcpy(this->numeTaraba, t.numeTaraba);
			for (int i = 0; i < 5; i++)
				this->nrClientiZi[i] = t.nrClientiZi[i];
			this->profit = t.profit;
		}
		return *this;
	}


	int& operator[] (int index)
	{
		if (index >= 0 && index < 5)
			return this->nrClientiZi[index];
	}


	Taraba operator+(int i)
	{
		Taraba aux;
		aux = *this;
		aux.profit += i;
		return aux;
	}


	Taraba& operator++()
	{
		this->profit += 100;
		return *this;
	}


	Taraba operator++(int)
	{
		Taraba rez = *this;
		this->profit += 100;
		return rez;
	}


	operator int()
	{
		return this->dimensiuneMetriPatrati;
	}


	bool operator!()
	{
		if (this->profit == 0) return true;
		else return false;
	}


	bool operator>(Taraba t)
	{
		return this->profit > t.profit;
	}


	bool operator==(Taraba t)
	{
		return this->profit == t.profit;
	}


	void afisare()
	{
		cout << "\n--------------------";
		cout << "\nEditie targ: " << editieTarg;
		cout << "\nDimensiune taraba in metri patrati: " << this->dimensiuneMetriPatrati;
		cout << "\nNume taraba: " << this->numeTaraba;
		cout << "\nNr. clienti pe zi: ";
		for (int i = 0; i < 5; i++)
			cout << this->nrClientiZi[i] << " ";
		cout << "\nProfit: " << this->profit;
		cout << "\n--------------------";
	}


	void cresteProfitul(int i)
	{
		this->profit += i;
	}


	void adaugareClientInZiuaX(int x)
	{
		if (x >= 1 && x <= 5)
			this->nrClientiZi[x - 1]++;
	}


	float getDimensiuneMetriPatrati()
	{
		return this->dimensiuneMetriPatrati;
	}


	void setDimensiuneMetriPatrati(float dimensiuneMetriPatrati)
	{
		if (dimensiuneMetriPatrati > 0)
			this->dimensiuneMetriPatrati = dimensiuneMetriPatrati;
	}


	char* getNumeTaraba()
	{
		return this->numeTaraba;
	}


	void setNumeTaraba(char* numeTaraba)
	{
		if (numeTaraba != NULL)
		{
			delete[] this->numeTaraba;
			this->numeTaraba = new char[strlen(numeTaraba) + 1];
			strcpy(this->numeTaraba, numeTaraba);
		}
	}


	int* getNrClientiZi()
	{
		return this->nrClientiZi;
	}


	void setNrClientiZi(int* nrClientiZi)
	{
		bool ok = true;
		for (int i = 0; i < 5; i++)
			if (nrClientiZi[i] < 0) ok = false;

		if (ok)
			for (int i = 0; i < 5; i++)
				this->nrClientiZi[i] = nrClientiZi[i];
	}


	int getProfit()
	{
		return this->profit;
	}


	void setProfit(int profit)
	{
		if (profit > 0) this->profit = profit;
	}


};









class Proprietar : public OperareFisiereBinare, OperareFisiereText
{

private:

	static const int anAutorizatie = 2022;
	char* nume = NULL;
	int cnp[13];
	int zilePrezent[5];
	float profitProprietar = 0;

public:

	void citireDinFisierText()
	{
		ifstream f;
		f.open("proprietarjohn.txt", ifstream::in);
		if (f.is_open())
		{
			f >> *this;
			f.close();
		}
	}


	void scriereInFisierBin(fstream& f)
	{
		f.write((char*)&Proprietar::anAutorizatie, sizeof(int));
		int lg = strlen(this->nume) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->nume, lg);
		for (int i = 0; i < 13; i++)
			f.write((char*)&this->cnp[i], sizeof(int));
		for (int i = 0; i < 5; i++)
			f.write((char*)&this->zilePrezent[i], sizeof(int));
		f.write((char*)&this->profitProprietar, sizeof(float));
	}


	Proprietar()
	{
		for (int i = 0; i < 13; i++) this->cnp[i] = 0;
		for (int i = 0; i < 5; i++) this->zilePrezent[i] = 0;
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
	}


	Proprietar(char* nume, int cnp[], int zilePrezent[], float profitProprietar)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		for (int i = 0; i < 13; i++) this->cnp[i] = cnp[i];
		for (int i = 0; i < 5; i++) this->zilePrezent[i] = zilePrezent[i];
		this->profitProprietar = profitProprietar;
	}


	Proprietar(const Proprietar& p)
	{
		this->nume = new char[strlen(p.nume) + 1];
		strcpy(this->nume, p.nume);
		for (int i = 0; i < 13; i++) this->cnp[i] = p.cnp[i];
		for (int i = 0; i < 5; i++) this->zilePrezent[i] = p.zilePrezent[i];
		this->profitProprietar = p.profitProprietar;
	}


	Proprietar& operator=(const Proprietar& p)
	{
		if (this != &p)
		{
			delete[] this->nume;
			this->nume = new char[strlen(p.nume) + 1];
			strcpy(this->nume, p.nume);
			for (int i = 0; i < 13; i++) this->cnp[i] = p.cnp[i];
			for (int i = 0; i < 5; i++) this->zilePrezent[i] = p.zilePrezent[i];
			this->profitProprietar = p.profitProprietar;
		}

		else
		{
			this->nume = NULL;
			for (int i = 0; i < 13; i++) cnp[i] = 0;
			for (int i = 0; i < 5; i++) this->zilePrezent[i] = 0;
		}
		return *this;
	}


	~Proprietar()
	{
		delete[] this->nume;
	}


	friend istream& operator>>(istream& in, Proprietar& p)
	{
		delete[] p.nume;
		cout << "Introduceti nume proprietar: \n";
		char aux[100];
		in >> aux;
		p.nume = new char[strlen(aux) + 1];
		strcpy(p.nume, aux);
		cout << "Introduceti CNP proprietar: \n";
		for (int i = 0; i < 13; i++) in >> p.cnp[i];
		cout << "Introduceti zilele in care proprietarul a fost prezent(0 pt absent 1 pt prezent): \n";
		for (int i = 0; i < 5; i++) in >> p.zilePrezent[i];
		cout << "Introduceti profit proprietar: \n";
		in >> p.profitProprietar;

		return in;
	}


	friend ostream& operator<<(ostream& out, const Proprietar& p)
	{
		out << "\n--------------------";
		out << "\nAn autorizatie: " << p.anAutorizatie;
		out << "\nNume proprietar: " << p.nume;
		out << "\nCNP proprietar: ";

		for (int i = 0; i < 13; i++) out << p.cnp[i];
		out << "\nZile in care proprietarul a fost prezent: ";

		for (int i = 0; i < 5; i++)
			if (p.zilePrezent[i] == 1) out << "\nZiua " << i + 1 << " prezent";
			else out << "\nZiua " << i + 1 << " absent";

		out << "\nProfit proprietar: " << p.profitProprietar;
		out << "\n--------------------";

		return out;
	}


	int operator[](int index)
	{
		if (index > 0 && index <= 5) return this->zilePrezent[index - 1];
	}


	Proprietar operator+(float x)
	{
		this->profitProprietar += x;
		return *this;
	}


	Proprietar& operator++()
	{
		this->profitProprietar += 100;
		return *this;
	}


	Proprietar operator++(int)
	{
		Proprietar aux = *this;
		this->profitProprietar += 100;
		return aux;
	}


	operator float()
	{
		return this->profitProprietar;
	}


	bool operator!()
	{
		if (this->profitProprietar == 0) return true;
		else return false;
	}


	bool operator>(const Proprietar& p)
	{
		if (this->profitProprietar > p.profitProprietar) return true;
		else return false;
	}


	bool operator==(const Proprietar& p)
	{
		if (this->profitProprietar == p.profitProprietar) return true;
		else return false;
	}


	int* getCnp()
	{
		return this->cnp;
	}


	void setCnp(int* cnp)
	{
		for (int i = 0; i < 13; i++) this->cnp[i] = cnp[i];
	}


	char* getNume()
	{
		return this->nume;
	}


	void setNume(const char* nume)
	{
		delete[] this->nume;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}


	int* getZilePrezent()
	{
		return this->zilePrezent;
	}


	void setZilePrezent(int* cnp)
	{
		for (int i = 0; i < 5; i++) this->zilePrezent[i] = zilePrezent[i];
	}


	float getProfitProprietar()
	{
		return this->profitProprietar;
	}


	void setProfitProprietar(int profitProprietar)
	{
		this->profitProprietar = profitProprietar;
	}


	void prezentaTotalaProprietar()
	{
		for (int i = 0; i < 5; i++) this->zilePrezent[i] = 1;
	}

};









class TarabaOrnamente : private Taraba
{

private:
	int nrTipuriOrnamente = 0;
	string* numeOrnament = NULL;
	int pretOrnament[100];


public:

	void afisareDescriereTaraba()
	{
		cout << "Aceasta este o taraba plina cu ornamente. Aici veti gasi tot ce aveti nevoie pentru a va orna pomul si casa in cele mai placute moduri.";
	}


	TarabaOrnamente()
	{
		//cout << "\nApel constructor cu niciun parametru TarabaOrnamente ";
		for (int i = 0; i < 100; i++) this->pretOrnament[i] = 0;
	}


	TarabaOrnamente(float dimensiuneMetriPatrati, char* numeTaraba, int nrClientiZi[], int profit, int nrTipuriOrnamente, string* numeOrnament, int pretOrnament[]) :
		Taraba(dimensiuneMetriPatrati, numeTaraba, nrClientiZi, profit)
	{
		//cout << "\nApel constructor cu toti parametri TarabaOrnamente 1";

		if (numeOrnament != NULL && nrTipuriOrnamente > 0)
		{
			this->nrTipuriOrnamente = nrTipuriOrnamente;
			this->numeOrnament = new string[this->nrTipuriOrnamente + 1];

			for (int i = 0; i < this->nrTipuriOrnamente; i++)
			{
				this->numeOrnament[i] = numeOrnament[i];
				this->pretOrnament[i] = pretOrnament[i];
			}

			for (int i = nrTipuriOrnamente; i < 100; i++)
				this->pretOrnament[i] = 0;
		}
	}


	TarabaOrnamente(Taraba t, int nrTipuriOrnamente, string* numeOrnament, int pretOrnament[]) :Taraba(t)
	{
		//cout << "\nApel constructor cu toti parametri TarabaOrnamente 2";

		if (numeOrnament != NULL && nrTipuriOrnamente > 0)
		{
			this->nrTipuriOrnamente = nrTipuriOrnamente;
			this->numeOrnament = new string[this->nrTipuriOrnamente + 1];

			for (int i = 0; i < this->nrTipuriOrnamente; i++)
			{
				this->numeOrnament[i] = numeOrnament[i];
				this->pretOrnament[i] = pretOrnament[i];
			}

			for (int i = nrTipuriOrnamente; i < 100; i++)
				this->pretOrnament[i] = 0;
		}
	}


	TarabaOrnamente(const TarabaOrnamente& t) :Taraba(t)
	{
		//cout << "\nApel constructor cu niciun parametru TarabaOrnamente 1";

		if (t.numeOrnament != NULL && t.nrTipuriOrnamente > 0)
		{
			this->nrTipuriOrnamente = t.nrTipuriOrnamente;
			this->numeOrnament = new string[this->nrTipuriOrnamente + 1];

			for (int i = 0; i < this->nrTipuriOrnamente; i++)
			{
				this->numeOrnament[i] = t.numeOrnament[i];
				this->pretOrnament[i] = t.pretOrnament[i];
			}

			for (int i = t.nrTipuriOrnamente; i < 100; i++)
				this->pretOrnament[i] = 0;
		}
	}


	TarabaOrnamente& operator=(const TarabaOrnamente& t)
	{
		this->Taraba::operator=(t);

		if (t.numeOrnament != NULL && t.nrTipuriOrnamente > 0)
		{
			this->nrTipuriOrnamente = t.nrTipuriOrnamente;
			this->numeOrnament = new string[this->nrTipuriOrnamente + 1];

			for (int i = 0; i < this->nrTipuriOrnamente; i++)
			{
				this->numeOrnament[i] = t.numeOrnament[i];
				this->pretOrnament[i] = t.pretOrnament[i];
			}

			for (int i = t.nrTipuriOrnamente; i < 100; i++)
				this->pretOrnament[i] = 0;
		}
		return *this;
	}


	bool operator>(TarabaOrnamente t)
	{
		return this->nrTipuriOrnamente > t.nrTipuriOrnamente;
	}

	bool operator==(TarabaOrnamente t)
	{
		return this->nrTipuriOrnamente == t.nrTipuriOrnamente;
	}


	bool operator!()
	{
		if (this->numeOrnament == NULL) return true;
		else return false;
	}


	TarabaOrnamente operator+(int i)
	{
		TarabaOrnamente aux;
		aux = *this;
		aux.pretOrnament[aux.nrTipuriOrnamente - 1] += i;
		return aux;
	}


	TarabaOrnamente& operator++()
	{
		this->pretOrnament[this->nrTipuriOrnamente - 1] += 10;
		return *this;
	}


	TarabaOrnamente operator++(int)
	{
		TarabaOrnamente rez = *this;
		this->pretOrnament[this->nrTipuriOrnamente - 1] += 10;
		return rez;
	}


	string& operator[](int index)
	{
		if (index > 0 && index <= this->nrTipuriOrnamente)
			return this->numeOrnament[index - 1];
	}


	~TarabaOrnamente()
	{
		//cout <<"\nApel destructor TabaraOrnamente";
		delete[] this->numeOrnament;
	}


	friend ostream& operator<<(ostream& out, const TarabaOrnamente& t)
	{
		out << (Taraba)t;
		out << "\nNr. tipuri ornamente: " << t.nrTipuriOrnamente;
		out << "\nNume si pret ornamente: ";
		for (int i = 0; i < t.nrTipuriOrnamente; i++)
			out << t.numeOrnament[i] << "(" << t.pretOrnament[i] << ") ";
		out << "\n--------------------";
		return out;
	}


	friend istream& operator>>(istream& in, const TarabaOrnamente& t)
	{

	}


	int getNrTipuriOrnamente()
	{
		return this->nrTipuriOrnamente;
	}


	void setNrTipuriOrnamente(int nrTipuriOrnamente)
	{
		if (nrTipuriOrnamente > 0)
			this->nrTipuriOrnamente = nrTipuriOrnamente;
	}


	string* getNumeOrnament()
	{
		return this->numeOrnament;
	}


	void setNumeOrnament(string* numeOrnament)
	{
		delete[] this->numeOrnament;
		this->numeOrnament = new string[this->nrTipuriOrnamente + 1];
		for (int i = 0; i < this->nrTipuriOrnamente; i++)
			this->numeOrnament[i] = numeOrnament[i];
	}


	int* getPretOrnament()
	{
		return this->pretOrnament;
	}


	void setPretOrnament(int* pretOrnament)
	{
		for (int i = 0; i < 100; i++) this->pretOrnament[i] = 0;
		for (int i = 0; i < this->nrTipuriOrnamente; i++) this->pretOrnament[i] = pretOrnament[i];
	}


	void adaugareOrnament(string numeOrnament, int pretOrnament)
	{
		string* aux = new string[this->nrTipuriOrnamente + 2];
		for (int i = 0; i < this->nrTipuriOrnamente; i++) aux[i] = this->numeOrnament[i];
		this->nrTipuriOrnamente++;
		delete[] this->numeOrnament;
		this->numeOrnament = new string[this->nrTipuriOrnamente + 1];
		for (int i = 0; i < this->nrTipuriOrnamente - 1; i++) this->numeOrnament[i] = aux[i];
		this->numeOrnament[this->nrTipuriOrnamente - 1] = numeOrnament;
		this->pretOrnament[this->nrTipuriOrnamente - 1] = pretOrnament;
	}


	void stergereUltimulOrnament()
	{
		string* aux = new string[this->nrTipuriOrnamente];
		for (int i = 0; i < this->nrTipuriOrnamente; i++) aux[i] = this->numeOrnament[i];
		this->nrTipuriOrnamente--;
		delete[] this->numeOrnament;
		this->numeOrnament = new string[this->nrTipuriOrnamente + 1];
		for (int i = 0; i < this->nrTipuriOrnamente; i++) this->numeOrnament[i] = aux[i];
		this->pretOrnament[this->nrTipuriOrnamente] = 0;
	}

};









class TarabaDulciuri :private Taraba
{
private:
	int nrTipuriDulciuri = 0;
	string* numeDulciuri = NULL;
	int pretDulciuri[100];


public:

	void afisareDescriereTaraba()
	{
		cout << "Aceasta este o taraba plina cu dulciuri. Aici veti gasi toate tipurile de dulciuri cu care sa va rupeti dintii pentru ca parintii vostri sa va trimita la stomatolog.";
	}


	TarabaDulciuri()
	{
		//cout << "\nApel constructor cu niciun parametru TarabaDulciuri ";
		for (int i = 0; i < 100; i++) this->pretDulciuri[i] = 0;
	}


	TarabaDulciuri(float dimensiuneMetriPatrati, char* numeTaraba, int nrClientiZi[], int profit, int nrTipuriDulciuri, string* numeDulciuri, int pretDulciuri[]) :
		Taraba(dimensiuneMetriPatrati, numeTaraba, nrClientiZi, profit)
	{
		//cout << "\nApel constructor cu toti parametri TarabaDulciuri 1";

		if (numeDulciuri != NULL && nrTipuriDulciuri > 0)
		{
			this->nrTipuriDulciuri = nrTipuriDulciuri;
			this->numeDulciuri = new string[this->nrTipuriDulciuri + 1];

			for (int i = 0; i < this->nrTipuriDulciuri; i++)
			{
				this->numeDulciuri[i] = numeDulciuri[i];
				this->pretDulciuri[i] = pretDulciuri[i];
			}

			for (int i = nrTipuriDulciuri; i < 100; i++)
				this->pretDulciuri[i] = 0;
		}
	}


	TarabaDulciuri(Taraba t, int nrTipuriDulciuri, string* numeDulciuri, int pretDulciuri[]) :Taraba(t)
	{
		//cout << "\nApel constructor cu toti parametri TarabaDulciuri 2";

		if (numeDulciuri != NULL && nrTipuriDulciuri > 0)
		{
			this->nrTipuriDulciuri = nrTipuriDulciuri;
			this->numeDulciuri = new string[this->nrTipuriDulciuri + 1];

			for (int i = 0; i < this->nrTipuriDulciuri; i++)
			{
				this->numeDulciuri[i] = numeDulciuri[i];
				this->pretDulciuri[i] = pretDulciuri[i];
			}

			for (int i = nrTipuriDulciuri; i < 100; i++)
				this->pretDulciuri[i] = 0;
		}
	}


	TarabaDulciuri(const TarabaDulciuri& t) :Taraba(t)
	{
		//cout << "\nApel constructor cu niciun parametru TarabaDulciuri 1";

		if (t.numeDulciuri != NULL && t.nrTipuriDulciuri > 0)
		{
			this->nrTipuriDulciuri = t.nrTipuriDulciuri;
			this->numeDulciuri = new string[this->nrTipuriDulciuri + 1];

			for (int i = 0; i < this->nrTipuriDulciuri; i++)
			{
				this->numeDulciuri[i] = t.numeDulciuri[i];
				this->pretDulciuri[i] = t.pretDulciuri[i];
			}

			for (int i = t.nrTipuriDulciuri; i < 100; i++)
				this->pretDulciuri[i] = 0;
		}
	}


	TarabaDulciuri& operator=(const TarabaDulciuri& t)
	{
		this->Taraba::operator=(t);

		if (t.numeDulciuri != NULL && t.nrTipuriDulciuri > 0)
		{
			this->nrTipuriDulciuri = t.nrTipuriDulciuri;
			this->numeDulciuri = new string[this->nrTipuriDulciuri + 1];

			for (int i = 0; i < this->nrTipuriDulciuri; i++)
			{
				this->numeDulciuri[i] = t.numeDulciuri[i];
				this->pretDulciuri[i] = t.pretDulciuri[i];
			}

			for (int i = t.nrTipuriDulciuri; i < 100; i++)
				this->pretDulciuri[i] = 0;
		}
		return *this;
	}


	bool operator>(TarabaDulciuri t)
	{
		return this->nrTipuriDulciuri > t.nrTipuriDulciuri;
	}


	bool operator==(TarabaDulciuri t)
	{
		return this->nrTipuriDulciuri == t.nrTipuriDulciuri;
	}


	bool operator!()
	{
		if (this->numeDulciuri == NULL) return true;
		else return false;
	}


	TarabaDulciuri operator+(int i)
	{
		TarabaDulciuri aux;
		aux = *this;
		aux.pretDulciuri[aux.nrTipuriDulciuri - 1] += i;
		return aux;
	}


	TarabaDulciuri& operator++()
	{
		this->pretDulciuri[this->nrTipuriDulciuri - 1] += 10;
		return *this;
	}


	TarabaDulciuri operator++(int)
	{
		TarabaDulciuri rez = *this;
		this->pretDulciuri[this->nrTipuriDulciuri - 1] += 10;
		return rez;
	}


	string& operator[](int index)
	{
		if (index > 0 && index <= this->nrTipuriDulciuri)
			return this->numeDulciuri[index - 1];
	}


	~TarabaDulciuri()
	{
		//cout <<"\nApel destructor TabaraDulciuri";
		delete[] this->numeDulciuri;
	}


	friend ostream& operator<<(ostream& out, const TarabaDulciuri& t)
	{
		out << (Taraba)t;
		out << "\nNr. tipuri Dulciuri: " << t.nrTipuriDulciuri;
		out << "\nNume si pret Dulciuri: ";
		for (int i = 0; i < t.nrTipuriDulciuri; i++)
			out << t.numeDulciuri[i] << "(" << t.pretDulciuri[i] << ") ";
		out << "\n--------------------";
		return out;
	}


	friend istream& operator>>(istream& in, const TarabaDulciuri& t)
	{

	}


	int getNrTipuriDulciuri()
	{
		return this->nrTipuriDulciuri;
	}


	void setNrTipuriDulciuri(int nrTipuriDulciuri)
	{
		if (nrTipuriDulciuri > 0)
			this->nrTipuriDulciuri = nrTipuriDulciuri;
	}


	string* getNumeDulciuri()
	{
		return this->numeDulciuri;
	}


	void setNumeDulciuri(string* numeDulciuri)
	{
		delete[] this->numeDulciuri;
		this->numeDulciuri = new string[this->nrTipuriDulciuri + 1];
		for (int i = 0; i < this->nrTipuriDulciuri; i++)
			this->numeDulciuri[i] = numeDulciuri[i];
	}


	int* getPretDulciuri()
	{
		return this->pretDulciuri;
	}


	void setPretDulciuri(int* pretDulciuri)
	{
		for (int i = 0; i < 100; i++) this->pretDulciuri[i] = 0;
		for (int i = 0; i < this->nrTipuriDulciuri; i++) this->pretDulciuri[i] = pretDulciuri[i];
	}


	void adaugareDulciuri(string numeDulciuri, int pretDulciuri)
	{
		string* aux = new string[this->nrTipuriDulciuri + 2];
		for (int i = 0; i < this->nrTipuriDulciuri; i++) aux[i] = this->numeDulciuri[i];
		this->nrTipuriDulciuri++;
		delete[] this->numeDulciuri;
		this->numeDulciuri = new string[this->nrTipuriDulciuri + 1];
		for (int i = 0; i < this->nrTipuriDulciuri - 1; i++) this->numeDulciuri[i] = aux[i];
		this->numeDulciuri[this->nrTipuriDulciuri - 1] = numeDulciuri;
		this->pretDulciuri[this->nrTipuriDulciuri - 1] = pretDulciuri;
	}


	void stergereUltimulDulciuri()
	{
		string* aux = new string[this->nrTipuriDulciuri];
		for (int i = 0; i < this->nrTipuriDulciuri; i++) aux[i] = this->numeDulciuri[i];
		this->nrTipuriDulciuri--;
		delete[] this->numeDulciuri;
		this->numeDulciuri = new string[this->nrTipuriDulciuri + 1];
		for (int i = 0; i < this->nrTipuriDulciuri; i++) this->numeDulciuri[i] = aux[i];
		this->pretDulciuri[this->nrTipuriDulciuri] = 0;
	}

};









class TarabaCadouri :private Taraba
{
private:
	int nrTipuriCadouri = 0;
	string* numeCadouri = NULL;
	int pretCadouri[100];


public:

	void afisareDescriereTaraba()
	{
		cout << "Aceasta este o taraba plina cu dulciuri. Aici veti gasi cadourile perfecte pentru familia si pentru prietenii vostri, la preturi accesibile si corecte.";
	}


	TarabaCadouri()
	{
		//cout << "\nApel constructor cu niciun parametru TarabaCadouri ";
		for (int i = 0; i < 100; i++) this->pretCadouri[i] = 0;
	}


	TarabaCadouri(float dimensiuneMetriPatrati, char* numeTaraba, int nrClientiZi[], int profit, int nrTipuriCadouri, string* numeCadouri, int pretCadouri[]) :
		Taraba(dimensiuneMetriPatrati, numeTaraba, nrClientiZi, profit)
	{
		//cout << "\nApel constructor cu toti parametri TarabaCadouri 1";

		if (numeCadouri != NULL && nrTipuriCadouri > 0)
		{
			this->nrTipuriCadouri = nrTipuriCadouri;
			this->numeCadouri = new string[this->nrTipuriCadouri + 1];

			for (int i = 0; i < this->nrTipuriCadouri; i++)
			{
				this->numeCadouri[i] = numeCadouri[i];
				this->pretCadouri[i] = pretCadouri[i];
			}

			for (int i = nrTipuriCadouri; i < 100; i++)
				this->pretCadouri[i] = 0;
		}
	}


	TarabaCadouri(Taraba t, int nrTipuriCadouri, string* numeCadouri, int pretCadouri[]) :Taraba(t)
	{
		//cout << "\nApel constructor cu toti parametri TarabaCadouri 2";

		if (numeCadouri != NULL && nrTipuriCadouri > 0)
		{
			this->nrTipuriCadouri = nrTipuriCadouri;
			this->numeCadouri = new string[this->nrTipuriCadouri + 1];

			for (int i = 0; i < this->nrTipuriCadouri; i++)
			{
				this->numeCadouri[i] = numeCadouri[i];
				this->pretCadouri[i] = pretCadouri[i];
			}

			for (int i = nrTipuriCadouri; i < 100; i++)
				this->pretCadouri[i] = 0;
		}
	}


	TarabaCadouri(const TarabaCadouri& t) :Taraba(t)
	{
		//cout << "\nApel constructor cu niciun parametru TarabaCadouri 1";

		if (t.numeCadouri != NULL && t.nrTipuriCadouri > 0)
		{
			this->nrTipuriCadouri = t.nrTipuriCadouri;
			this->numeCadouri = new string[this->nrTipuriCadouri + 1];

			for (int i = 0; i < this->nrTipuriCadouri; i++)
			{
				this->numeCadouri[i] = t.numeCadouri[i];
				this->pretCadouri[i] = t.pretCadouri[i];
			}

			for (int i = t.nrTipuriCadouri; i < 100; i++)
				this->pretCadouri[i] = 0;
		}
	}


	TarabaCadouri& operator=(const TarabaCadouri& t)
	{
		this->Taraba::operator=(t);

		if (t.numeCadouri != NULL && t.nrTipuriCadouri > 0)
		{
			this->nrTipuriCadouri = t.nrTipuriCadouri;
			this->numeCadouri = new string[this->nrTipuriCadouri + 1];

			for (int i = 0; i < this->nrTipuriCadouri; i++)
			{
				this->numeCadouri[i] = t.numeCadouri[i];
				this->pretCadouri[i] = t.pretCadouri[i];
			}

			for (int i = t.nrTipuriCadouri; i < 100; i++)
				this->pretCadouri[i] = 0;
		}
		return *this;
	}


	bool operator>(TarabaCadouri t)
	{
		return this->nrTipuriCadouri > t.nrTipuriCadouri;
	}


	bool operator==(TarabaCadouri t)
	{
		return this->nrTipuriCadouri == t.nrTipuriCadouri;
	}


	bool operator!()
	{
		if (this->numeCadouri == NULL) return true;
		else return false;
	}


	TarabaCadouri operator+(int i)
	{
		TarabaCadouri aux;
		aux = *this;
		aux.pretCadouri[aux.nrTipuriCadouri - 1] += i;
		return aux;
	}


	TarabaCadouri& operator++()
	{
		this->pretCadouri[this->nrTipuriCadouri - 1] += 10;
		return *this;
	}


	TarabaCadouri operator++(int)
	{
		TarabaCadouri rez = *this;
		this->pretCadouri[this->nrTipuriCadouri - 1] += 10;
		return rez;
	}


	string& operator[](int index)
	{
		if (index > 0 && index <= this->nrTipuriCadouri)
			return this->numeCadouri[index - 1];
	}


	~TarabaCadouri()
	{
		//cout <<"\nApel destructor TabaraCadouri";
		delete[] this->numeCadouri;
	}


	friend ostream& operator<<(ostream& out, const TarabaCadouri& t)
	{
		out << (Taraba)t;
		out << "\nNr. tipuri Cadouri: " << t.nrTipuriCadouri;
		out << "\nNume si pret Cadouri: ";
		for (int i = 0; i < t.nrTipuriCadouri; i++)
			out << t.numeCadouri[i] << "(" << t.pretCadouri[i] << ") ";
		out << "\n--------------------";
		return out;
	}


	friend istream& operator>>(istream& in, const TarabaCadouri& t)
	{

	}


	int getNrTipuriCadouri()
	{
		return this->nrTipuriCadouri;
	}


	void setNrTipuriCadouri(int nrTipuriCadouri)
	{
		if (nrTipuriCadouri > 0)
			this->nrTipuriCadouri = nrTipuriCadouri;
	}


	string* getNumeCadouri()
	{
		return this->numeCadouri;
	}


	void setNumeCadouri(string* numeCadouri)
	{
		delete[] this->numeCadouri;
		this->numeCadouri = new string[this->nrTipuriCadouri + 1];
		for (int i = 0; i < this->nrTipuriCadouri; i++)
			this->numeCadouri[i] = numeCadouri[i];
	}


	int* getPretCadouri()
	{
		return this->pretCadouri;
	}


	void setPretCadouri(int* pretCadouri)
	{
		for (int i = 0; i < 100; i++) this->pretCadouri[i] = 0;
		for (int i = 0; i < this->nrTipuriCadouri; i++) this->pretCadouri[i] = pretCadouri[i];
	}


	void adaugareCadouri(string numeCadouri, int pretCadouri)
	{
		string* aux = new string[this->nrTipuriCadouri + 2];
		for (int i = 0; i < this->nrTipuriCadouri; i++) aux[i] = this->numeCadouri[i];
		this->nrTipuriCadouri++;
		delete[] this->numeCadouri;
		this->numeCadouri = new string[this->nrTipuriCadouri + 1];
		for (int i = 0; i < this->nrTipuriCadouri - 1; i++) this->numeCadouri[i] = aux[i];
		this->numeCadouri[this->nrTipuriCadouri - 1] = numeCadouri;
		this->pretCadouri[this->nrTipuriCadouri - 1] = pretCadouri;
	}


	void stergereUltimulCadou()
	{
		string* aux = new string[this->nrTipuriCadouri];
		for (int i = 0; i < this->nrTipuriCadouri; i++) aux[i] = this->numeCadouri[i];
		this->nrTipuriCadouri--;
		delete[] this->numeCadouri;
		this->numeCadouri = new string[this->nrTipuriCadouri + 1];
		for (int i = 0; i < this->nrTipuriCadouri; i++) this->numeCadouri[i] = aux[i];
		this->pretCadouri[this->nrTipuriCadouri] = 0;
	}

};






class Meniu
{

public:
	static void afisareMeniu()
	{
		cout << "\n";
		cout << "\n1. Afisare in consola si scriere in fisier text a clasei Taraba";
		cout << "\n2. Afisare in consola si scriere in fisier text a clasei TarabaOrnamente";
		cout << "\n3. Afisare in consola si scriere in fisier text a clasei Proprietar";
		cout << "\n4. Citire din fisier CSV a CNP-ului proprietarului si modificarea acestuia";
		cout << "\n5. Afisare in consola si scriere in fisier binar a clasei Proprietar";
		cout << "\n6. Afisare in consola si scriere in fisier binar a clasei Taraba";
		cout << "\n7. Citire din fisier text si afisare in consola a clasei Taraba";
		cout << "\n8. Raport comenzi introduse corect de utilizator";
		cout << "\n9. Raport comenzi introduse gresit de utilizator";
		cout << "\n0. Iesire din program";
		cout << "\n";
		cout << "\n";
	}

};








int main()
{

	cout << "\n  _____ _   ___  ___   ___  ___    ___ ___    _   ___ ___ _   _ _  _ ";
	cout << "\n |_   _/_\\ | _ \\/ __| |   \\| __|  / __| _ \\  /_\\ / __|_ _| | | | \\| |";
	cout << "\n   | |/ _ \\|   / (_ | | |) | _|  | (__|   / / _ \\ (__ | || |_| | .` |";
	cout << "\n   |_/_/ \\_\\_|_\\\\___| |___/|___|  \\___|_|_\\/_/ \\\_\\\___|___|\\___/|_|\\_|";
	cout << "\n                                                                     ";
	cout << "\n";
	cout << "\n";



	cout << "Testare pentru implementarea claselor";
	cout << "\n";
	cout << "\n";



	system("pause");



	cout << "\n//////////////////////";
	cout << "\nTESTARE CLASA TARABA:";
	cout << "\n//////////////////////";



	char nume[100];
	int nrclientizi[5] = { 1,2,3,4,5 };
	bool ok;



	cout << "\nConstructor fara parametri: ";
	Taraba t1;
	t1.afisare();


	cout << "\nConstructor cu 1 parametru: ";
	strcpy(nume, "TarabaDeArama");
	Taraba t2(nume);
	cout << t2;


	cout << "\nConstructor cu 4 parametri: ";
	Taraba t3(5, nume, nrclientizi, 200);
	cout << t3;


	cout << "\n____operator =____  ";
	t2 = t3;
	cout << t2;


	cout << "\n____operator +____  ";
	t3 = t2 + 100;
	cout << t3;


	cout << "\n" << t3[2];


	cout << "\n____operator ==____  ";
	t2 = t3;
	ok = t3 == t2;
	cout << ok;



	cout << "\n____operator >____  ";
	ok = t3 > t2;
	cout << ok;



	cout << "\n____operator !____  ";
	ok = !t3;
	cout << ok;


	cout << "\nGETTERI, SETTERI, METODE DE PRELUCRARE";


	cout << "\n____dimensiune metri patrati____  ";
	t1.setDimensiuneMetriPatrati(10);
	cout << t1.getDimensiuneMetriPatrati();


	cout << "\n____nr clienti zi____  ";
	for (int i = 0; i < 5; i++) { nrclientizi[i] = i + 2; }
	t1.setNrClientiZi(nrclientizi);
	int* aux;
	aux = t1.getNrClientiZi();
	for (int i = 0; i < 5; i++) cout << aux[i] << " ";


	cout << "\n____nume taraba____  ";
	strcpy(nume, "NUME NOU");
	t1.setNumeTaraba(nume);
	cout << t1.getNumeTaraba();


	cout << "\n____creste profitul____  ";
	t2.cresteProfitul(300);
	cout << t2.getProfit();


	cout << "\n____profit____  ";
	t1.setProfit(1000);
	cout << t1.getProfit();


	cout << "\n____adaugare client in ziua x____  ";
	t2.adaugareClientInZiuaX(2);
	aux = t2.getNrClientiZi();
	for (int i = 0; i < 5; i++) cout << aux[i] << " ";








	cout << "\n//////////////////////";
	cout << "\nTESTARE CLASA TARABA ORNAMENTE:";
	cout << "\n//////////////////////";


	string* numeOrnamente = new string[3];
	numeOrnamente[0] = "Globuri";
	numeOrnamente[1] = "Betea";
	numeOrnamente[2] = "Stea";
	int preturiOrnamente[3] = { 5,20,50 };


	cout << "\nConstructor cu toti parametri: ";
	TarabaOrnamente to_1(5, nume, nrclientizi, 200, 3, numeOrnamente, preturiOrnamente);
	cout << to_1;


	cout << "\nConstructor cu 4 parametri: ";
	TarabaOrnamente to_2(t2, 3, numeOrnamente, preturiOrnamente);
	cout << to_2;


	cout << "\nConstructor de copiere: ";
	TarabaOrnamente to_3(to_2);
	cout << to_3;


	cout << "\n____operator =____  ";
	to_2 = to_1;
	cout << to_2;


	cout << "\n____operator >____  ";
	ok = to_1 > to_2;
	cout << '\n' << ok;


	cout << "\n____operator ==____  ";
	ok = to_1 == to_2;
	cout << '\n' << ok;


	cout << "\n____operator !____  ";
	ok = !to_1;
	cout << '\n' << ok;


	cout << "\n____operator +____  ";
	cout << to_1;
	to_1 = to_1 + 30;
	cout << to_1;


	cout << "\n____operator ++ pre____  ";
	cout << to_1;
	cout << ++to_1;


	cout << "\n____operator ++ post____  ";
	cout << to_1++;
	cout << to_1;


	cout << "\n____operator []____  ";
	cout << '\n' << to_1[3];


	cout << "\nGETTERI, SETTERI, METODE DE PRELUCRARE";

	cout << "\n____nr. tipuri ornamente____  ";
	cout << "\n____nume ornament____  ";
	cout << "\n____pret ornament____  ";


	delete[] numeOrnamente;
	numeOrnamente = new string[4];
	numeOrnamente[0] = "Globuri";
	numeOrnamente[1] = "Betea";
	numeOrnamente[2] = "Stea";
	numeOrnamente[3] = "Lumini";
	int preturiOrnamente2[4] = { 5,20,50,35 };


	to_1.setNrTipuriOrnamente(4);
	to_1.setNumeOrnament(numeOrnamente);
	to_1.setPretOrnament(preturiOrnamente2);


	cout << to_1;


	cout << '\n' << to_1.getNrTipuriOrnamente();
	cout << '\n';


	string* aux1 = new string[4];
	aux1 = to_1.getNumeOrnament();
	for (int i = 0; i < 4; i++) cout << aux1[i] << " ";


	cout << '\n';
	int* preturiOrnamente3 = new int[4];
	preturiOrnamente3 = to_1.getPretOrnament();
	for (int i = 0; i < 4; i++) cout << preturiOrnamente3[i] << " ";


	cout << "\n____adaugare ornament____";
	to_1.adaugareOrnament("Fulgi", 100);
	cout << to_1;


	cout << "\n____stergere ultimul ornament____";
	to_1.stergereUltimulOrnament();
	cout << to_1;



	cout << "\n//////////////////////";
	cout << "\nTESTARE CLASA TARABA DULCIURI IDENTICA CU CLASA ORNAMENTE";
	cout << "\n//////////////////////";


	cout << "\n//////////////////////";
	cout << "\nTESTARE CLASA TARABA CADOURI IDENTICA CU CLASA ORNAMENTE";
	cout << "\n//////////////////////";






	cout << "\n//////////////////////";
	cout << "\nTESTARE CLASA TARABA PROPRIETAR:";
	cout << "\n//////////////////////";

	int cnp[13] = { 5,0,2,0,3,2,0,2,9,7,6,4,2 };
	int zilePrezent[5] = { 1,1,1,1,1 };
	float profitPLus = 20;
	char* numee = new char[strlen("Adrian") + 1];
	strcpy(numee, "Adrian");


	cout << "\nConstructor cu toti parametri: ";
	Proprietar p1(numee, cnp, zilePrezent, 500);
	cout << p1;


	cout << "\nConstructor de copiere: ";
	Proprietar p2(p1);
	cout << p2;


	cout << "\nConstructor fara parametri: ";
	Proprietar p3;
	cout << p3;


	cout << "\n____operator =____  ";
	p3 = p2;
	cout << p3;


	/*cout << "\n____operator >>____  ";
	Proprietar p4;
	cin >> p4;
	cout << p4;*/


	cout << "\n____operator []____  ";
	cout << '\n' << p2[2];


	cout << "\n____operator +____  ";
	p1 = p1 + profitPLus;
	cout << p1;


	cout << "\n____operator ++____  ";
	cout << ++p1;


	cout << "\n____operator !____  ";
	cout << '\n' << !p1;


	cout << "\n____operator >____  ";
	bool ok2 = p1 > p2;
	cout << '\n' << ok2;


	cout << "\n____operator ==____  ";
	ok2 = p1 == p2;
	cout << '\n' << ok2;


	cout << "\nGETTERI, SETTERI, METODE DE PRELUCRARE";

	cout << "\n____cnp____  ";
	int cnp2[13] = { 6,0,2,0,3,2,0,2,9,7,6,4,1 };
	p1.setCnp(cnp2);
	int* cnp3 = p1.getCnp();
	cout << '\n';
	for (int i = 0; i < 13; i++) cout << cnp3[i] << " ";


	cout << "\n____nume____  ";
	char* numee2 = new char[strlen("George") + 1];
	strcpy(numee2, "George");
	p1.setNume(numee2);


	cout << "\n____zile prezent____  \n";
	p1.setZilePrezent(zilePrezent);
	int* zilePrez = p1.getZilePrezent();
	for (int i = 0; i < 5; i++) cout << zilePrez[i] << " ";


	cout << "\n____profit proprietar____  \n";
	p1.setProfitProprietar(800);
	cout << p1.getProfitProprietar();


	cout << "\n____prezenta totala proprietar____  \n";
	p1.prezentaTotalaProprietar();
	cout << p1;


	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";

	//VECTOR
	vector<Proprietar> Proprietari;

	Proprietari.push_back(p1);

	Proprietari.push_back(p2);

	Proprietari.push_back(p3);




	////SET

	//set<TarabaOrnamente> SetTarabeOrnamente;

	//
	//SetTarabeOrnamente.insert(to_1);

	//SetTarabeOrnamente.insert(to_2);

	//SetTarabeOrnamente.insert(to_3);




	//LIST

	list<TarabaOrnamente> ListTarabeOrnamente;

	ListTarabeOrnamente.push_back(to_1);

	ListTarabeOrnamente.push_back(to_2);

	ListTarabeOrnamente.push_back(to_3);




	//MAP
	map<int, Taraba> MapTarabe;

	MapTarabe[1] = t1;

	MapTarabe[2] = t2;

	MapTarabe[3] = t3;



	
	int comenzi_introduse_corect = 0;
	int comenzi_introduse_gresit = 0;


	cout << "\nMeniu de utilizare: Introduceti tasta corespunzatoare actiunii dorite.";

	Meniu::afisareMeniu();

	int comanda = 10;
	while (comanda != 0)
	{
		cin >> comanda;


		if (comanda == 1)
		{
			comenzi_introduse_corect++;

			system("cls");
			cout << t2;

			ofstream g("taraba.txt");
			g << t2;
			g.close();

			cout << "\n";
			cout << "\nAfisarea clasei Taraba a fost de asemenea realizata in fisierul text taraba.txt";
			cout << "\n";
			Meniu::afisareMeniu();
		}

		if (comanda == 2)
		{
			comenzi_introduse_corect++;

			system("cls");
			cout << to_2;

			ofstream g("tarabaornamente.txt");
			g << to_2;
			g.close();

			cout << "\n";
			cout << "\nAfisarea clasei TarabaOrnamente a fost de asemenea realizata in fisierul text tarabaornamente.txt";
			cout << "\n";
			Meniu::afisareMeniu();
		}

		if (comanda == 3)
		{
			comenzi_introduse_corect++;

			system("cls");
			cout << p3;

			ofstream g("proprietar.txt");
			g << p3;
			g.close();

			cout << "\n";
			cout << "\nAfisarea clasei Proprietar a fost de asemenea realizata in fisierul text proprietar.txt";
			cout << "\n";
			Meniu::afisareMeniu();
		}

		if (comanda == 4)
		{
			comenzi_introduse_corect++;

			system("cls");
			ifstream f;
			f.open("cnp.csv");
			int cnp_nou[13];
			int aux, i = 0;
			while (f >> aux)
			{
				cnp_nou[i++] = aux;
			}

			p2.setCnp(cnp_nou);
			cout << p2;
			cout << "\n";
			Meniu::afisareMeniu();
		}

		if (comanda == 5)
		{
			comenzi_introduse_corect++;

			system("cls");
			OperareFisiereBinare* pf;
			fstream fOut("proprietar_bin.txt", ios::out | ios::binary);
			p2.scriereInFisierBin(fOut);
			fOut.close();

			cout << p2;
			cout << '\n';
			cout << "Afisarea clasei Proprietar a fost de asemenea realizata in binar  fisierul text proprietar_bin.txt";
			cout << '\n';
			Meniu::afisareMeniu();
		}

		if (comanda == 6)
		{
			comenzi_introduse_corect++;

			system("cls");
			OperareFisiereBinare* pf;
			fstream fOut("taraba_bin.txt", ios::out | ios::binary);
			t2.scriereInFisierBin(fOut);
			fOut.close();

			cout << t2;
			cout << '\n';
			cout << "Afisarea clasei Taraba a fost de asemenea realizata in binar  fisierul text taraba_bin.txt";
			cout << '\n';
			Meniu::afisareMeniu();
		}

		if (comanda == 7)
		{
			comenzi_introduse_corect++;

			system("cls");
			Taraba tlm;
			tlm.citireDinFisierText();
			tlm.afisare();
			cout << '\n';
			Meniu::afisareMeniu();
		}

		if (comanda == 8)
		{
			system("cls");
			cout << comenzi_introduse_corect << " comenzi corecte au fost introduse de catre utilizator.";
			Meniu::afisareMeniu();
		}

		if (comanda == 9)
		{
			system("cls");
			cout << comenzi_introduse_gresit << " comenzi gresite au fost introduse de catre utilizator.";
			Meniu::afisareMeniu();
		}

		if (comanda == 0)
		{
			system("cls");
			cout << "\nVa multumim pentru utilizarea programului de gestiune a tarabelor din cadrul targului de Craciun.";
			cout << "\nProiect realizat de Tudor Gavril, grupa 1052C";
			cout << '\n';
			cout << '\n';
			return 0;
		}

		if (comanda != 1 && comanda != 2 && comanda != 3 && comanda != 4 && comanda != 5 && comanda != 6 && comanda != 7 && comanda != 8 && comanda != 9 && comanda != 0)
			comenzi_introduse_gresit++;

	}
	return 0;
}