#include <sstream>
#include <fstream>
#include "tree.h"

using namespace tree;
using namespace arc;
using namespace util;

Tree readFromStream(istream&);
Tree readFromFile(string);

int main(){
	Tree tree = createEmpty();
	int scelta;
	bool end = false;
	const string LOW = "B", HIGH = "A"; // rischio

	while(!end){
		cout << endl;
		cout << "1. Lettura albero di decisione da file\n";
		cout << "2. Inserimento di un nodo etichettato labelChild attaccato a un padre etichettato labelFather\n";
		cout << "3. Cancellazione di un nodo dall'albero\n";
		cout << "4. Modifica di un nodo dall'albero\n";
		cout << "5. Visualizzazione dell'albero di decisione\n";
		cout << "6. Stampa le variabili dell'albero di decisione\n";
		cout << "7. Effettua predizioni inserendo i valori uno alla volta\n";
		cout << "8. Effettua predizioni inserendo tutti i valori all'inizio\n";
		cout << "0. Exit\n";
		cout << "\nFornisci la tua scelta ---> ";
		cin >> scelta;

		switch(scelta){
			case 1:{ // lettura da file
				string file;
				cout << "Inserisci il nome del file:" << "\n" << "- ";
				cin >> file;

				tree = readFromFile(file);
				break;
			}
			case 2:{ // inserimento nodo
				string father, newLabel, value;

				cout << "Inserisci il label del padre:" << "\n" << "- ";
				cin >> father;
				if(!member(father, tree)){
					cout << "Il nodo inserito non esiste" << "\n";
					break;
				}

				cout << "Inserisci il label da aggiungere:" << "\n" << "- ";
				cin >> newLabel;
				cout << "Inserisci la nuova condizione del nodo (es: \'=Familiare\', \'=A\', \'<=23\'):" << "\n" << "- ";
				cin >> value;

				if(addElem(father, newLabel, value, tree)) cout << "Nodo aggiunto con successo" << "\n";
				else cout << "Operazione fallita" << "\n";
				break;
			}
			case 3:{ // cancellazione elemento
				string label;

				cout << "Inserisci il label da eliminare:" << "\n" << "- ";
				cin >> label;

				if(deleteElem(label, tree)) cout << "Nodo eliminato con successo" << '\n';
				else cout << "Operazione fallita" << "\n";
				break;
			}
			case 4:{ // modifica elemento
				string toModify, toAdd, cond;

				cout << "Inserisci il nodo da modificare:" << "\n" << "- ";
				cin >> toModify;
				cout << "Inserisci l'etichetta da aggiungere:" << "\n" << "- ";
				cin >> toAdd;
				cout << "Inserisci la nuova condizione:" << "\n" << "- ";
				cin >> cond;

				if(modifyElem(toModify, toAdd, cond, tree)) cout << "Nodo modificato con successo" << "\n";
				else cout << "Operazione fallita" << "\n";
				break;
			}
			case 5:{ // stampa albero
				printTree(tree);
				break;
			}
			case 6:{ // stampa variabili
				printVariables(tree);
				break;
			}
			case 7:{ // predizione uno alla volta
				bool endPred = false;
				int input;
				Tree t = tree;

				while(!endPred){
					cout << endl;
					cout << "1. Effettua predizione\n";
					cout << "0. Exit\n";
					cout << "\nScegli opzione --> ";
					cin >> input;
					cout << "-----------------" << "\n";

					switch(input){
						case 1:{
							if(isEmpty(t)){
								cout << "Albero vuoto." << "\n";
								break;
							}

							string val, toPrint;
							cout << "Inserisci " << arc::format(t->label) << ":" << "\n" << "- ";
							cin >> val;

							Tree result = predictOne(val, t);
							if(result != emptyTree){
								if(arc::format(result->label) == END){
									if(result->cond.var == LOW) toPrint = "BASSO";
									else if(result->cond.var == HIGH) toPrint = "ALTO";

									cout << "\nPredizione effettuata. Rischio: " << toPrint << '\n';
									endPred = true;
								}
								t = result;
							} else{
								cout << "\nPredizione fallita." << "\n";
								endPred = true;
							}

							break;
						}
						case 0:
							endPred = true;
							break;
					}
				}

				break;
			}
			case 8:{ // predizione completa
				list::List l = list::createEmpty();

				bool endPred = false;
				int input;

				while(!endPred){
					cout << endl;
					cout << "1. Inserisci coppia\n";
					cout << "2. Effettua predizione\n";
					cout << "0. Exit\n";
					cout << "\nScegli opzione --> ";
					cin >> input;
					cout << "-----------------" << "\n";

					switch (input) {
						case 1:{
							string line;

							cout << "Inserisci due valori separati da uno spazio (es. \'Eta 49\'):" << "\n" << "- ";
							cin.ignore();
							getline(cin, line);

							string *couple = splitTwo(line, " ");
							normalize(couple[0]);
							normalize(couple[1]);

							list::addBack(list::createElement(couple[0], couple[1]), l);
							break;
						}
						case 2:{
							if(isEmpty(tree)){
								cout << "Albero vuoto." << "\n";
								break;
							}

							string toPrint;

							Tree result = predictList(l, tree);
							if(result != emptyTree){
								if(arc::format(result->label) == END){
									if(result->cond.var == LOW) toPrint = "BASSO";
									else if(result->cond.var == HIGH) toPrint = "ALTO";

									cout << "Predizione effettuata. Rischio: " << toPrint << '\n';
								}
							} else{
								cout << "Predizione fallita." << "\n";
							}

							endPred = true;
							break;
						}
						case 0:
							endPred = true;
							break;
					}
				}
				break;
			}
			case 0: // exit
				end = true;
				break;
		}

		cout << "\n" << "--------------------------------------------" << '\n';
	}

	return 0;
}

//---FILE FUNCTIONS---

//-----------------------------------------
// Compone un albero leggendo da uno stream
Tree readFromStream(istream& stream){
	Tree t = createEmpty();
	string line;
	Label root, father, child, cond;
	getline(stream, line);

	istringstream instream; // input stream
	instream.clear();
	instream.str(line);

	instream >> root; // lettura radice
	addElem(arc::emptyLabel, root, "", t);

	getline(stream, line);
	instream.clear();
	instream.str(line);
	while(!stream.eof()){
		instream >> father; // lettura nodo padre
		normalize(father);

		while(!instream.eof()){
			instream >> child;
			instream >> cond;
			if(arc::format(child) != END) normalize(child); // l'etichetta END non va normalizzata

			addElem(father, child, cond, t);
		}

		getline(stream, line);
		instream.clear();
		instream.str(line);
	}
	stream.clear();
	return t;
}

//-----------------------------------------
// Legge da file
Tree readFromFile(string filename){
	ifstream ifs(filename.c_str());
	if(!ifs){
		cout << "\nErrore apertura file\n";
		return createEmpty();
	}
	return readFromStream(ifs);
}
