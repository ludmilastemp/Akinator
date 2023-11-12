#include "Bintree/STL_bintree_struct.h"
#include "Bintree/STL_graphviz.h"

#include <stdio.h>

int main()
{
    NodeBinTree* n5 = NodeBinTreeCtor (5, 0, 0);
    NodeBinTree* n4 = NodeBinTreeCtor (15, 0, 0);
    NodeBinTree* n3 = NodeBinTreeCtor (20, 0, 0);
    NodeBinTree* n2 = NodeBinTreeCtor (17, n4, n3);
    NodeBinTree* n1 = NodeBinTreeCtor (10, n5, n2);

    BinTree* tree = BinTreeCtor (n1);

    NodeBinTree* n6 = InsertSaveSorting (12, tree->root);
    NodeBinTree* n7 = InsertSaveSorting (11, tree->root);

    SubtreeDump (tree->root);

    STL_GraphvizBinTree (tree->root);

    NodeBinTreeDtor (tree->root);

    return 0;
}
