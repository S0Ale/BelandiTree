# BelandiTree
My implementation of the decision tree structure made for an university project.

This implementation uses two main data structures:
###### Arc
Represents the nodes' conditions:
```c++
struct Arc{
	string cond; // simbolo
	string var; // variabile
};
```

###### TreeNode
Represents each tree node:
```c++
struct treeNode{ // Rappresenta i nodi dell'albero
  Label label;
  Cond cond;
  
  treeNode *firstChild;
  treeNode *nextSibling;
};
```

