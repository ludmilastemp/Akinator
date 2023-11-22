#ifndef STL_bintree_struct_
#define STL_bintree_struct_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef const char* BIN_TREE_DATA_T;

#define BIN_TREE_DATA_PRINT_SPECIFIER "%s"

struct NodeBinTree
{
    BIN_TREE_DATA_T data;
    NodeBinTree* left;
    NodeBinTree* right;
    NodeBinTree* parent;
};

struct BinTree
{
    NodeBinTree* root;
    int size;
};

NodeBinTree*
NodeBinTreeCtor (BIN_TREE_DATA_T data,
                 NodeBinTree* left    = nullptr,
                 NodeBinTree* right   = nullptr,
                 NodeBinTree* parent  = nullptr,
                 BinTree*     binTree = nullptr);

NodeBinTree*
NodeBinTreeDtor (NodeBinTree* node);

BinTree*
BinTreeCtor (NodeBinTree* root,
             int size = 1);

BinTree*
BinTreeDtor (BinTree* binTree);

int
SubtreeDump (NodeBinTree* node);

NodeBinTree*
InsertSaveSorting (BIN_TREE_DATA_T data,
                   NodeBinTree* node,
                   BinTree* binTree  = nullptr);

int
BinTreePrintPreorder (NodeBinTree* node,
                      const char* const fileName);

BinTree*
NodeBinTreeReadPreorder (const char* const fileName);

#endif /* STL_bintree_struct_ */
