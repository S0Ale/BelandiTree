// Implementa LIST con strutture indicizzate e tipo base Elem dotato di ordinamento
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

namespace list{

/**************************** Tipi e costanti *********************************************/
const int BLOCKDIM = 100;
struct Elem{
	string label;
	string val;
};      // tipo base, compatibile con il tipo Label dell'albero

const string emptyLabel = "$$$";
const string emptyValue = "###";
struct list {
    Elem* list;
    int size;
    int maxsize;
};

typedef list List;


// Operazioni sugli elementi
Elem createElement(string, string);

/************************* operazioni stateful (con side effect) ******************************************/

void clear(List&);          /* "smantella" la lista */
void set(int, Elem, List&); /* modifica l'elemento in posizione pos */
void add(int, Elem, List&); /* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
void addBack(Elem, List&);  /* inserisce l'elemento alla fine della lista */
void addFront(Elem, List&); /* inserisce l'elemento all'inizio della lista */
void removePos(int, List&); /* cancella l'elemento in posizione pos dalla lista  */

/************************* operazioni stateless (funzionali) ******************************************/

int search(string, const List&);	/* restituisce l'indirizzo di un elemento nella lista */
Elem get(int, const List&);	      /* restituisce l'elemento in posizione pos */
List createEmpty();               /* crea la lista vuota e la restituisce */
bool isEmpty(const List&);
int size(const List&);
}

//void printList(const list::List&);
