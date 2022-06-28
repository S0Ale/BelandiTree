#include "list.h"

using namespace list;

struct list::list {
    Elem info;
    list *prev;
    list *next;
};

/****************************************************************/
void list::clear(List& l){
    if(isEmpty(l)) return;
    list* aux = l->next;
    list* prev;
    while(aux != l) {
        prev = aux;
        aux = aux->next;
        delete prev;
    }
    l->next = l;
    l->prev = l;
}


/****************************************************************/
void list::set(int pos, Elem e, List& l)
{
  if(pos < 0 || pos > size(l) - 1) return;
  list* current = l->next;
	for(int i = 0; current != l && i < pos; i++) current = current->next;
	if(current != l) current->info = e;
}


/****************************************************************/
void list::add(int pos, Elem e, List& l) // aggiunge e nella posizione pos
{
    if(pos < 0 || pos > size(l)) return;
    list* aux = l->next;
    while(pos > 0 && aux->info != emptyElem) {
        aux = aux->next;
        pos--;
    }

    List newNode = new list;
    newNode->info = e;
    newNode->next = aux;
    newNode->prev = aux->prev;
    newNode->prev->next = newNode;
    aux->prev = newNode;
}

/****************************************************************/
void list::addBack(Elem e, List& l) // aggiunge e in coda
{
    list* aux = l->next;
    while (aux->next != l)
        aux= aux->next;

    list* newNode = new list;
    newNode->info = e;
    aux->next = newNode;
    newNode->prev = aux;
    newNode->next = l;
    l->prev = newNode;
}


/****************************************************************/
void list::addFront(Elem e, List& l) // aggiunge e in coda
{
  list* aux = l->next;

	list* newNode = new list;
	newNode->info = e;
	newNode->prev = l;
	newNode->next = aux;

	l->next = newNode;
	if(aux != l) aux->prev = newNode;
}

/****************************************************************/
void list::removePos(int pos, List& l)
{
    if(pos < 0) return;
	list* current = l->next;
	for(int i = 0; current != l && i < pos; i++) current = current->next;

	if(current != l){
		list* aux = current->prev;
		aux->next = current->next;
		current->next->prev = aux;

		delete current;
	}
}


List list::createEmpty()
{
  list* newNode = new list;
	newNode->info = emptyElem;
	newNode->prev = newNode;
	newNode->next = newNode;

	return newNode;
}

/****************************************************************/
Elem list::get(int pos, const List& l)
{
    list* aux = l->next;
    while(pos > 0) {
        if(aux->info == emptyElem) return emptyElem;
        aux = aux->next;
        pos--;
    }
    return aux->info;
}

/****************************************************************/
int list::indexOf(Elem l, const List& list){
	if(isEmpty(list)) return -1;

	int index = 0;
	List aux = list->next;
	while(aux != list){
		Elem str = aux->info;
		if(str.find(l) != string::npos) return index;
		aux = aux->next;
		index++;
	}

	return -1;
}

/****************************************************************/
bool list::isEmpty(const List& l)
{
   return l->next == l;
}

/****************************************************************/
int list::size(const List& l)
{
    if(l->next->info == emptyElem) return 0;
	return 1 + size(l->next);
}


/****************************************************************/
void printList(const List& l)
{
    List q = l->next;
    while (q != l) {
        cout << q->info << "; ";
        q = q->next;
    }
}
