#include "STL_bintree_struct.h"

#define calloc(x,y) STL_calloc (x, y)
#define malloc(x,y) STL_calloc (x, y)
#define free(x)     STL_free (x)

void* STL_calloc (int count, int size);
void* STL_free   (void* ptr);

static int
NodeBinTreePrintPreorder (NodeBinTree* node,
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

    node->data  = nullptr;
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
    if (binTree->buf != nullptr) free (binTree->buf);

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
    if (node == nullptr) return ERROR_NOT_NODE_POINTER;

    if (fileName == nullptr)
    {
        printf ("\nОШИБКА!!! Пожалуйста, укажите в аргументах командной строки имя файла, куда нужно записать дерево\n");
        return 0;
    }

    FILE* fp = fopen (fileName, "w");
    if (fp == nullptr)
    {
        printf ("\nНе удалось открыть файл\n");
        return 0;
    }

    NodeBinTreePrintPreorder (node, fp);

    fclose (fp);

    return 0;
}


static int
NodeBinTreePrintPreorder (NodeBinTree* node, FILE* fp)
{
    if (fp == nullptr) return ERROR_NOT_FILE_POINTER;

    if (node == nullptr)
    {
        fprintf (fp, NULL_POINTER);
        return 0;
    }

    fprintf (fp, "(");

    fprintf (fp, "\"" BIN_TREE_DATA_PRINT_SPECIFIER "\"", node->data);
    NodeBinTreePrintPreorder (node->left,  fp);
    NodeBinTreePrintPreorder (node->right, fp);

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

    if (file->name == nullptr)
    {
        printf ("\nОШИБКА!!! Пожалуйста, укажите в аргументах командной строки имя файла, где записано дерево\n");
        return 0;
    }

    STL_Fread (file);

    int pointer = 0;

    NodeBinTree* root = NodeBinTreeCtorPreorder (file->text, &pointer);

    /// ошибка при чтении дерева
    if (pointer == -1)
    {
        printf ("\n\n\nTREE IS INCORRECT!!!\n\n\n");
        NodeBinTreeDtor (root);
        return nullptr;
    }

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
    if (node == nullptr) return nullptr;

    node->left   = ReadBranchNodeBinTree (buf, len, node);
    node->right  = ReadBranchNodeBinTree (buf, len, node);
    node->parent = parent;

    if (buf[*len] == ')')
    {
        (*len)++;
        return node;
    }

    *len = -1;
    return node;
}

static NodeBinTree*
ReadDataNodeBinTree (char* const buf, int* len)
{
    if (buf == nullptr || len == nullptr)
    {
        return nullptr;
    }

    NodeBinTree* node = NodeBinTreeCtor ("", nullptr, nullptr);
    if (node == nullptr)
    {
        printf ("ERROR!!! NO MEMORY\n");
        *len = -1;
        return nullptr;
    }

    if (buf[(*len)++] != '"')
    {
        printf ("ERROR!!! %d symbol\n", *len);
        free (node);
        *len = -1;
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
        return nullptr;
    }

    if (buf[(*len)] == '(')
    {
        return NodeBinTreeCtorPreorder (buf, len, node);
    }

    else if (strncmp (buf + *len, NULL_POINTER, sizeof (NULL_POINTER) - 1) == 0)
    {
        *len += sizeof (NULL_POINTER) - 1;
        return nullptr;
    }

    return nullptr;
}

#undef calloc
#undef malloc
#undef free

void* STL_calloc (int count, int size)
{
    static int countCalloc = 0;
    countCalloc++;

    FILE* fp = nullptr;
    static int isFileOpen = 0;

    if (!isFileOpen){
        fp = fopen ("temp/FILE_CALLOC.txt", "w");
        assert (fp);

        isFileOpen = 1;
    }

    else
    {
        fp = fopen ("temp/FILE_CALLOC.txt", "a");
        assert (fp);
    }

    void* memory = (void*) calloc (count, size);
    fprintf (fp, "%d. %p - allocated %d bytes\n",
        countCalloc, memory, count * size);

    fclose (fp);

    return memory;
}

void* STL_free (void* ptr)
{
    static int count = 0;
    count++;

    FILE* fp = fopen ("temp/FILE_CALLOC.txt", "a");
    assert (fp);

    fprintf (fp, "%d. %p - free\n", count, ptr);

    free (ptr);

    fclose (fp);

    return ptr;
}
