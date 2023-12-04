#include "STL_bintree_struct.h"

static int
SubtreePrintPreorder (NodeBinTree* node,
                      FILE* fp);

static NodeBinTree*
NodeBinTreeCtorPreorder (char* const buf,
                         int* len,
                         NodeBinTree* parent = nullptr);

static NodeBinTree*
ReadDataNodeBinTree (char* const buf,
                     int* len);

static NodeBinTree*
ReadBranchNodeBinTree (char* const buf,
                       int* len,
                       NodeBinTree* node);

NodeBinTree*
NodeBinTreeCtor (BIN_TREE_DATA_T data,
                 NodeBinTree* left,
                 NodeBinTree* right,
                 NodeBinTree* parent,
                 BinTree*     binTree)
{
    NodeBinTree* node = (NodeBinTree*) calloc (1, sizeof (NodeBinTree));
    if (node == nullptr)
    {
        printf ("ERROR_NO_MEMORY\n");
        return nullptr;
    }

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

    node->data  = nullptr; // 0
    node->left  = nullptr;
    node->right = nullptr;

    free (node);

    return nullptr;
}

BinTree*
BinTreeCtor (NodeBinTree* root, int size, char* buf)
{
    BinTree* binTree = (BinTree*) calloc (1, sizeof (BinTree));
    if (binTree == nullptr)
    {
        printf ("ERROR_NOT_MEMORY\n");
        return nullptr;
    }

    binTree->root = root;
    binTree->size = size;
    binTree->buf  = buf;

    return binTree;
}

BinTree*
BinTreeDtor (BinTree* binTree)
{
    if (binTree == nullptr) return nullptr;

    NodeBinTreeDtor (binTree->root);
    if (binTree->buf      != nullptr) free (binTree->buf);

    binTree->root = nullptr;
    binTree->buf  = nullptr;
    binTree->size = 0;

    return nullptr;
}

int
SubtreeDump (NodeBinTree* node)
{
    if (node == nullptr)
    {
        printf ("%s ", NULL_POINTER);
        return 0;
    }

    printf ("(");

    SubtreeDump (node->left);
    printf (BIN_TREE_DATA_PRINT_SPECIFIER " ", node->data);
    SubtreeDump (node->right);

    printf (") ");

    return 0;
}

int
BinTreePrintPreorder (NodeBinTree* node, const char* const fileName)
{
    if (fileName == nullptr) return ERROR_NOT_FILE;
    if (node     == nullptr) return ERROR_NOT_NODE_POINTER;

    FILE* fp = fopen (fileName, "w");
    assert (fp);

    SubtreePrintPreorder (node, fp);

    fclose (fp);
}


static int
SubtreePrintPreorder (NodeBinTree* node, FILE* fp)
{
    if (fp == nullptr) return ERROR_NOT_FILE_POINTER;

    if (node == nullptr)
    {
        fprintf (fp, NULL_POINTER);
        return 0;
    }

    fprintf (fp, "(");

    fprintf (fp, "\"" BIN_TREE_DATA_PRINT_SPECIFIER "\"", node->data);
    SubtreePrintPreorder (node->left,  fp);
    SubtreePrintPreorder (node->right, fp);

    fprintf (fp, ")");

    return 0;
}

BinTree*
BinTreeReadPreorder (struct File* file)
{
    if (file == nullptr)
    {
        printf ("ERROR_NOT_FILE\n");
        return nullptr;
    }

    STL_Fread (file);

    int pointer = 0;

    NodeBinTree* root = NodeBinTreeCtorPreorder (file->text, &pointer);
    BinTree* tree = BinTreeCtor(root, 1, file->text);

    return tree;
}

static NodeBinTree*
NodeBinTreeCtorPreorder (char* const buf, int* len, NodeBinTree* parent)
{
    if (buf == nullptr || len == nullptr)
    {
        printf ("ERROR_NOT_FILE_POINTER\n");
        return nullptr;
    }

    if (buf[(*len)++] != '(')
    {
        return nullptr;
    }

    NodeBinTree* node = ReadDataNodeBinTree (buf, len);

    node->left   = ReadBranchNodeBinTree (buf, len, node);
    node->right  = ReadBranchNodeBinTree (buf, len, node);
    node->parent = parent;

    if (buf[*len] == ')')
    {
        (*len)++;
        return node;
    }

    return nullptr;
}

static NodeBinTree*
ReadDataNodeBinTree (char* const buf, int* len)
{
    if (buf == nullptr || len == nullptr)
    {
        printf ("ERROR_NOT_FILE_POINTER\n");
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

    return node;
}

static NodeBinTree*
ReadBranchNodeBinTree (char* const buf, int* len,
                       NodeBinTree* node)
{
    if (buf == nullptr || len == nullptr)
    {
        printf ("ERROR_NOT_FILE_POINTER\n");
        return nullptr;
    }

    if (buf[(*len)] == '(')
    {
        return NodeBinTreeCtorPreorder (buf, len, node);
    }

    else if (strncmp (buf + *len, NULL_POINTER, NULL_POINTER_LEN) == 0)
    {
        *len += NULL_POINTER_LEN;
        return nullptr;
    }

    return nullptr;
}
