#include "arc.h"

using namespace arc;
using namespace std;

//---AUXILIARY FUNCTIONS---

//-----------------------------------------
// Controlla se una stringa contiene caratteri dell'alfabeto
bool containsAlphabet(string str){
	for(int i = 0; i < str.size(); i++)
		if(str[i] >= 'A' && str[i] <= 'z') return true;

	return false;
}

//-----------------------------------------
// Stabilisce se ina stringa è una condizione (=, !=, <, ...)
bool isCondition(string str){
	return (str[0] == '=' || (str[0] == '!' && str[1] == '=') || str[0] == '<' || str[0] == '>');
}

//-----------------------------------------
// Formatta la stringa togliendo l'ultimo carattere
string arc::format(string str){
	return str.substr(0, str.size() - 1);
}

//---TDD FUNCTIONS---

//-----------------------------------------
// Stabilisce se l'arco è vuoto
bool arc::isEmpty(const Arc& t){
	return t.cond == emptyCond || t.var == emptyLabel;
}

//-----------------------------------------
// Crea un nuovo arco vuoto
arc::Arc arc::createEmptyArc(){
	Arc* t = new Arc;
	t->cond = emptyCond;
	t->var = emptyLabel;

	return *t;
}

//-----------------------------------------
// Crea un nuovo arco
arc::Arc arc::createArc(string str){
	string cond;

	int index = 1;
	if(str[1] == '=') index = 2;

	cond = str.substr(0, index);
	string l = str.substr(index, str.size());

	Arc* t = new Arc;
	t->cond = cond;
	t->var = l;

	return *t;
}

//-----------------------------------------
// Verifica se l'arco e' valido
bool arc::isValid(const Arc& a){
	return isCondition(a.cond) && !containsAlphabet(a.cond) && !isEmpty(a);
}

//-----------------------------------------
// Verifica se due archi sono uguali
bool arc::areEqual(const Arc& t1, const Arc& t2){
	return t1.cond == t2.cond && t1.var == t2.var;
}

//-----------------------------------------
// Stampa l'arco
void arc::printArc(const Arc& t){
	cout << t.cond << "|" << t.var;
}

//-----------------------------------------
// Valuta la condizione dell'arco in base agli input
bool arc::eval(const string toEval, const Arc& t){
	if(isEmpty(t) || containsAlphabet(t.cond)) return false;

	bool result = false;
	if(t.cond == "!=") result = toEval != t.var;
	else if(t.cond[0] == '<') result = stoi(toEval) < stoi(t.var);
	else if(t.cond[0] == '>') result = stoi(toEval) > stoi(t.var);
	else if(t.cond == "=") result = toEval == t.var;

	// <=, >=
	if(t.cond[1] == '=' && t.cond[0] != '!'){
		bool equal = t.var == toEval;
		return result || equal;
	}

	return result;
}
