#include "STL_bintree_struct.h"

static int
SubtreePrintPreorderToFile (NodeBinTree* node,
                            FILE* fp);

static NodeBinTree*
NodeBinTreeCtorPreorder (char* const buf,
                         int* len,
                         NodeBinTree* parent = nullptr);
NodeBinTree*
NodeBinTreeCtor (BIN_TREE_DATA_T data,
                 NodeBinTree* left,
                 NodeBinTree* right,
                 NodeBinTree* parent,
                 BinTree*     binTree)
{
    NodeBinTree* node = (NodeBinTree*) calloc (1, sizeof (NodeBinTree));
    assert (node);  // error

    node->data   = data;
    node->left   = left;
    node->right  = right;
    node->parent = parent;

    if (binTree != nullptr) binTree->size++;

    return node;
}

NodeBinTree*
NodeBinTreeDtor (NodeBinTree* node)
{
    if (node == nullptr) return nullptr;

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
    printf (BIN_TREE_DATA_PRINT_SPECIFIER " ", node->data);
    SubtreeDump (node->right);

    printf (") ");

    return 0;
}

NodeBinTree*
InsertSaveSorting (BIN_TREE_DATA_T data,
                   NodeBinTree* currentNode,
                   BinTree* binTree)
{
    NodeBinTree* nodeNew = NodeBinTreeCtor (data, 0, 0, 0, binTree);

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

    nodeNew->parent = currentNode;

    return nodeNew;
}

static int
SubtreePrintPreorderToFile (NodeBinTree* node, FILE* fp)
{
    if (node == nullptr)
    {
        fprintf (fp, "nil");
        return 0;
    }

    fprintf (fp, "(");

    fprintf (fp, "\"" BIN_TREE_DATA_PRINT_SPECIFIER "\"", node->data);
    SubtreePrintPreorderToFile (node->left, fp);
    SubtreePrintPreorderToFile (node->right, fp);

    fprintf (fp, ")");

    return 0;
}

int
BinTreePrintPreorder (NodeBinTree* node, const char* const fileName)
{
    assert (node);
    assert (fileName);

    FILE* fp = fopen (fileName, "w");
    assert (fp);

    SubtreePrintPreorderToFile (node, fp);

    fclose (fp);
}

#include <stdlib.h>   //
#include <sys\stat.h>
#include <string.h>

static NodeBinTree*
NodeBinTreeCtorPreorder (char* const buf, int* len, NodeBinTree* parent)
{
    assert (buf);
    assert (len);

    if (buf[(*len)++] != '(')
    {
        return nullptr;
    }

    NodeBinTree* node = NodeBinTreeCtor ("", nullptr, nullptr);
                        // если ошибка, то free

    if (buf[(*len)++] != '"')
    {
        return nullptr;
    }
    node->data = buf + *len;

    while (buf[(*len)++] != '"');
    buf[*len - 1] = '\0';

    if (buf[(*len)] == '(')
    {
        node->left = NodeBinTreeCtorPreorder (buf, len, node);
    }
    else if (strncmp (buf + *len, "nil", 3) == 0)
    {
        *len += 3;
        node->left = nullptr;
    }

    if (buf[(*len)] == '(')
    {
        node->right = NodeBinTreeCtorPreorder (buf, len, node);
    }
    else if (strncmp (buf + *len, "nil", 3) == 0)
    {
        *len += 3;
        node->right = nullptr;
    }

    node->parent = parent;

    if (buf[*len] == ')')
    {
        (*len)++;
        return node;
    }

    return nullptr;
}

BinTree*
NodeBinTreeReadPreorder (const char* const fileName)
{
    assert (fileName);

    FILE* fp = fopen (fileName, "rb");
    assert (fp); // err

    struct stat buff = { 0 };

    fstat (fileno (fp), &buff);
    int size = buff.st_size;

    char* buf = (char*) calloc (size + 1, sizeof (char));
    assert (buf);  // err

    fread (buf, sizeof (char), size, fp);

    int i = 0;
    BinTree* tree = BinTreeCtor(NodeBinTreeCtorPreorder (buf, &i));

    //fclose (fp);

    return tree;
}
