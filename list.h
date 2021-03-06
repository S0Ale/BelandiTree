#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace list{

/**************************** Tipi e costanti *********************************************/
typedef string Elem;
const Elem emptyElem = "$#$#$";

struct list;
typedef list * List;

void clear(List&);          /* "smantella" la lista */
void set(int, Elem, List&); /* modifica l'elemento in posizione pos */
void add(int, Elem, List&); /* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
void addBack(Elem, List&);  /* inserisce l'elemento alla fine della lista */
void addFront(Elem, List&); /* inserisce l'elemento all'inizio della lista */
void removePos(int, List&); /* cancella l'elemento in posizione pos dalla lista  */
Elem get(int, const List&);	/* restituisce l'elemento in posizione pos */
int indexOf(Elem, const List&);
List createEmpty();         /* crea la lista vuota e la restituisce */
bool isEmpty(const List&);
int size(const List&);
}

void printList(const list::List&);
