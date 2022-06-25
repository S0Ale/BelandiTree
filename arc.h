#include <iostream>
#include <string>

using namespace std;

// Rappresenta l'arco (la variabile) verso un nodo dell'albero (=Familiare, <=23)

namespace arc{
	struct Arc{
		string cond; // simbolo
		string var; // variabile
	};

	const string emptyCond = "#";
	const string emptyLabel = "%%%%";

	// Funzioni

	bool isEmpty(const Arc&);
	Arc createEmptyArc();
	Arc createArc(string);
	bool isValid(const Arc&);
	bool areEqual(const Arc&, const Arc&);
	bool eval(const string, const Arc&);
	void printArc(const Arc&);

	string format(string);
}
