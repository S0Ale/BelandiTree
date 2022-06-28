#include "tree.h"

using namespace tree;

//---AUXILIARY FUNCTIONS---

//-----------------------------------------
// Crea un nuovo nodo
Tree createNode(const Label l, const Cond& t, Tree first){
	treeNode* newNode = new treeNode;
	newNode->label = l;
	newNode->cond = t;
	newNode->firstChild = first;
	newNode->nextSibling = emptyTree;

	return newNode;
}

//-----------------------------------------
// Cerca un nodo all'interno dell'albero
Tree getNode(Label l, const Tree& t){
	if(isEmpty(t) || l == emptyLabel) return emptyTree;
	if(t->label == l) return t;

	Tree aux = t->firstChild;
	while(!isEmpty(aux)){
		Tree result = getNode(l, aux);
		if(result != emptyTree) return result;
		aux = aux->nextSibling;
	}

	return emptyTree;
}

//-----------------------------------------
// Restituisce il padre di un nodo
Label father(const Tree& t, const Label l){
    if(isEmpty(t) || l == emptyLabel) return emptyLabel;

    Tree aux = t->firstChild;
    while(!isEmpty(aux)) {
        if(aux->label == l) return t->label;
        aux = aux->nextSibling;
    }

    aux = t->firstChild;
    while(!isEmpty(aux)) {
        Label result = father(aux, l);
        if(result != emptyLabel) return result;
        aux = aux->nextSibling;
    }
    return emptyLabel;
}

//-----------------------------------------
// Ausiliaria che stabilisce se il nodo in input e' padre di una foglia (etichetta END)
Tree isLast(Tree t){
	if(isEmpty(t)) return emptyTree;

	Tree aux = t->firstChild;
	while(!isEmpty(aux)){
		if(arc::format(aux->label) == END) return aux;
		aux = aux->nextSibling;
	}

	return emptyTree;
}

//---TDD FUNCTIONS---

//-----------------------------------------
// Stabilisce se un albero e' vuoto
bool tree::isEmpty(const Tree& t){
	return t == emptyTree;
}

//-----------------------------------------
// Crea un albero vuoto
Tree tree::createEmpty(){
	return emptyTree;
}

//-----------------------------------------
// Aggiunge un elemento all'albero
bool tree::addElem(const Label fatherToAdd, const Label newLabel, const string newCond, Tree& t){
	if(isEmpty(t)){ // il nodo da inserire è la radice
		t = createNode(newLabel, arc::createEmptyArc(), emptyTree);
		return true;
	}

	Cond c = arc::createArc(newCond);
	if(!arc::isValid(c)) return false; // validità della condizione

	Tree father = getNode(fatherToAdd, t); // controllo del padre
	if(father == emptyTree) return false;

	// il padre non ha figli: il nodo diventa il firstchild
	if(!father->firstChild){
		father->firstChild = createNode(newLabel, c, emptyTree);
		return true;
	}

	// caso base: inserimento del nodo come ultimo fratello
	Tree current = father->firstChild;
	while(!isEmpty(current->nextSibling)) current = current->nextSibling;

	Tree aux = createNode(newLabel, c, emptyTree);
	current->nextSibling = aux;
	return true;
}

//-----------------------------------------
// Modifica un elemento dell'albero
bool tree::modifyElem(const Label toModify, const Label toAdd, const string newCond, const Tree& t){
	Cond c = arc::createArc(newCond);
	if(!arc::isValid(c)) return false;

	Tree node = getNode(toModify, t);
	if(node == emptyTree) return false;

	node->label = toAdd;
	node->cond = c;
	return true;
}

//-----------------------------------------
// Elimina un elemento dall'albero
bool tree::deleteElem(const Label l, Tree& t){
	treeNode* toDelete = getNode(l, t);
	Label fLabel = father(t, l);
	if(toDelete == emptyTree || fLabel == emptyLabel && toDelete->firstChild) return false;

	if(fLabel == emptyLabel){ // radice senza figli
		t = emptyTree;
		delete toDelete;
		return true;
	}

	treeNode* father = getNode(fLabel, t);
	if(toDelete->firstChild){ // se ha figli li attacco al padre
		treeNode* lastChild = father->firstChild;
		while (lastChild->nextSibling != emptyTree) lastChild = lastChild->nextSibling;
		lastChild->nextSibling = toDelete->firstChild;
	}

	if(father->firstChild->label == toDelete->label){ // to delete è il firstChild
		father->firstChild = toDelete->nextSibling;
		delete toDelete;
		return true;
	}

	// caso base: to delete è in mezzo ai sibling -> c'è bisogno di un puntatore al nodo precedente
	treeNode* prev = father->firstChild;
	while(prev->nextSibling->nextSibling != emptyTree && prev->nextSibling->label != l) prev = prev->nextSibling;

	prev->nextSibling = toDelete->nextSibling;
	delete toDelete;
	return true;
}

//-----------------------------------------
// Stabilisce se un elemento è un membro dell'albero oppure no
bool tree::member(const Label l, const Tree& t){
	return !(!isEmpty(t) && getNode(l, t) == emptyTree);
}

//-----------------------------------------
// Determina il grado di un nodo
int tree::degree(const Tree& t){
	if(isEmpty(t)) return -1;

	int count = 0;
	Tree aux = t->firstChild;
	while (isEmpty(aux)){
		count++;
		aux = aux->nextSibling;
	}

	return count;
}

//-----------------------------------------
// Effettua una predizione su un singolo nodo dell'albero
Tree tree::predictOne(const string val, Tree& t){
	if(arc::format(t->label) == END) return t;

	Tree trueList[degree(t)];
	Tree aux = t->firstChild;
	int size = 0;
	while(!isEmpty(aux)){
		if(arc::eval(val, aux->cond)){
			trueList[size] = aux; // conto delle condizioni vere
			size++;
		}
		aux = aux->nextSibling;
	}

	if(size > 0){
		Tree toReturn;
		if(size == 1) toReturn = trueList[0]; // una sola condizione vera
		else toReturn = trueList[util::random(0, size - 1)]; // scelta randomica

		Tree result = isLast(toReturn); // constrollo se il nodo è l'ultimo (fine predizione)
		if(result != emptyTree) return result;

		return toReturn;
	}

	// non ci sono condizioni vere
	return emptyTree;
}

//-----------------------------------------
// Effettua una predizione completa partendo da una lista in input
Tree tree::predictList(const list::List l, const Tree& t){
	Tree tree = t;
	bool endPred = false;
	while(!endPred){
		int index = list::indexOf(arc::format(tree->label), l);
		if(index < 0) return emptyTree;

		string elem = list::get(index, l);
		string *couple = util::splitTwo(elem, " ");

		tree = predictOne(couple[1], tree);
		if(tree != emptyTree && arc::format(tree->label) == END) endPred = true;
		else if(tree == emptyTree) endPred = true;
	}

	return tree;
}

//-----------------------------------------
// Stampa l'albero

// Ausiliaria
void printAux(int depth, const Tree& t){
	if(isEmpty(t)) return;

	for(int i = 0; i < depth; i++) cout <<  "--";
	cout  << t->label;
	if(!arc::isEmpty(t->cond)){
		std::cout << ", ";
		arc::printArc(t->cond);
	}
	cout << ";\n";

	Tree aux = t->firstChild;
	while(!isEmpty(aux)){
		printAux(depth+1, aux);
		aux = aux->nextSibling;
	}
}

void tree::printTree(const Tree& t){
	cout << "--------------------------" << '\n';
	printAux(0, t);
	cout << "\n";
}

//-----------------------------------------
// Stampa tutte le variabili dell'Albero

// Ausiliaria
void printVarAux(const Tree& t, string& str){
	if(isEmpty(t)) return;

	Label l = arc::format(t->label);
	l[0] -= 32;
	if(str.find(l) == string::npos && t->firstChild != emptyTree && l != emptyLabel){
		str = str + ", " + l;
	}

	printVarAux(t->firstChild, str);
	printVarAux(t->nextSibling, str);
}

void tree::printVariables(const Tree& t){
	cout << "--------------------------" << '\n';
	string str;
	printVarAux(t, str);
	cout << str.substr(2, string::npos) << "\n";
}
