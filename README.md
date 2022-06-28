# BelandiTree
Questo progetto è una mia implementazione di un albero decisionale (Decision Tree) in C++ per un esercizio all'università.

Questa implementazione utilizza 2 struct principali
###### Arc
Rappresenta una condizione che porta ad un nodo dell'albero (es. '>23'):
```c++
struct Arc{
   string cond; // simbolo
   string var; // variabile
};
```

###### TreeNode
Rappresenta il singolo nodo dell'albero:
```c++
struct treeNode{ // Rappresenta i nodi dell'albero
  Label label;
  Cond cond;
  
  treeNode *firstChild;
  treeNode *nextSibling;
};
```

