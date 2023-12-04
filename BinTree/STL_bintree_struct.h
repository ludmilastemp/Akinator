#ifndef STL_bintree_struct_
#define STL_bintree_struct_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>
#include <assert.h>

#include "../../Onegin/STL_file_open.h"

const int  NULL_POINTER_LEN = 3;
const char NULL_POINTER[] = "nil";

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
    char* buf;
};

enum BinTreeError
{                       // NO not not
    ERROR_NOT_BIN_TREE_POINTER  = 1 << 10,
    ERROR_NOT_NODE_POINTER      = 1 << 0,
    ERROR_NOT_FILE_POINTER      = 1 << 1,
    ERROR_NOT_FILE              = 1 << 2,
    ERROR_NOT_MEMORY            = 1 << 3,
};

NodeBinTree*
NodeBinTreeCtor (BIN_TREE_DATA_T data  = nullptr,
                 NodeBinTree* left     = nullptr,
                 NodeBinTree* right    = nullptr,
                 NodeBinTree* parent   = nullptr,
                 BinTree*     binTree  = nullptr);

NodeBinTree*
NodeBinTreeDtor (NodeBinTree* node);

BinTree*
BinTreeCtor (NodeBinTree* root = nullptr,
             int size          = 1,
             char* buf         = nullptr);

BinTree*
BinTreeDtor (BinTree* binTree);

NodeBinTree*
NodeBinTreeDataCtor (BIN_TREE_DATA_T data,
                     NodeBinTree* left    = nullptr,
                     NodeBinTree* right   = nullptr,
                     NodeBinTree* parent  = nullptr,
                     BinTree*     binTree = nullptr);

NodeBinTree*
BinTreeCopy (NodeBinTree* node);

int
SubtreeDump (NodeBinTree* node);


int
BinTreePrintPreorder (NodeBinTree* node,
                      const char* const fileName);

BinTree*
BinTreeReadPreorder (struct File* file);


#endif /* STL_bintree_struct_ */
