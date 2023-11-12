#ifndef STL_bintree_struct_
#define STL_bintree_struct_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int BIN_TREE_DATA_T;

struct NodeBinTree
{
    BIN_TREE_DATA_T data;
    NodeBinTree* left;
    NodeBinTree* right;
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

#endif /* STL_bintree_struct_ */
