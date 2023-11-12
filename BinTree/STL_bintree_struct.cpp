#include "STL_bintree_struct.h"

NodeBinTree*
NodeBinTreeCtor (BIN_TREE_DATA_T data,
                 NodeBinTree* left,
                 NodeBinTree* right,
                 BinTree*     binTree)
{
    NodeBinTree* node = (NodeBinTree*) calloc (1, sizeof (NodeBinTree));
    assert (node);  // error

    node->data  = data;
    node->left  = left;
    node->right = right;

    if (binTree != nullptr) binTree->size++;

    return node;
}

NodeBinTree*
NodeBinTreeDtor (NodeBinTree* node)
{
    if (node == nullptr) return nullptr;  // dont work

    NodeBinTreeDtor (node->left);
    NodeBinTreeDtor (node->right);

    node->data  = 0;
    node->left  = nullptr;
    node->right = nullptr;

    free (node);

    return nullptr;
}

BinTree*
BinTreeCtor (NodeBinTree* root, int size)
{
    BinTree* binTree = (BinTree*) calloc (1, sizeof (BinTree));
    assert (binTree);    // error

    binTree->root = root;
    binTree->size = size;

    return binTree;
}

BinTree*
BinTreeDtor (BinTree* binTree)
{
    if (binTree == nullptr) return nullptr;  // error

    NodeBinTreeDtor (binTree->root);

    binTree->root = nullptr;
    binTree->size = 0;

    free (binTree);

    return nullptr;
}

int
SubtreeDump (NodeBinTree* node)
{
    if (node == nullptr)
    {
        printf ("nil ");
        return 0;
    }

    printf ("(");

    SubtreeDump (node->left);
    printf ("%d ", node->data);
    SubtreeDump (node->right);

    printf (") ");

    return 0;
}

NodeBinTree*
InsertSaveSorting (BIN_TREE_DATA_T data,
                   NodeBinTree* currentNode,
                   BinTree* binTree)
{
    NodeBinTree* nodeNew = NodeBinTreeCtor (data, 0, 0, binTree);

    while (currentNode != nullptr)
    {
        if (nodeNew->data < currentNode->data)
        {
            if (currentNode->left == nullptr)
            {
                currentNode->left = nodeNew;
                break;
            }
            else currentNode = currentNode->left;
        }
        else
        {
            if (currentNode->right == nullptr)
            {
                currentNode->right = nodeNew;
                break;
            }
            else currentNode = currentNode->right;
        }
    }

    return nodeNew;
}
