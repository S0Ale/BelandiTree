#include "arc.h"
#include "list-array.h"
#include "utility.h"

//---TDD TREE---

namespace tree{
	typedef string Label;
	typedef arc::Arc Cond;

	typedef struct treeNode{ // Rappresenta i nodi dell'albero
	    Label label;
			Cond cond;

	    treeNode *firstChild;
	    treeNode *nextSibling;
	}* Tree;

	const Tree emptyTree = nullptr;
	const Label emptyLabel = "###";
	const Label END = "END";

	// Funzioni

	bool isEmpty(const Tree&);
	Tree createEmpty();
	bool addElem(const Label, const Label, const string, Tree&);
	bool modifyElem(const Label, const Label, const string, const Tree&);
	bool deleteElem(const Label, Tree&);
	bool member(const Label, const Tree&);

	Tree predictOne(const string, Tree&);
	Tree predictList(const list::List, const Tree&);

	void printTree(const Tree&);
	void printVariables(const Tree&);
}
