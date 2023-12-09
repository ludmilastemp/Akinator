#include "STL_graphviz.h"

#include <assert.h>

#define pr(...) fprintf (fp, __VA_ARGS__)

static void PrintSubtree (FILE* fp, const NodeBinTree* node, int* num);

void STL_GraphvizBinTree (const NodeBinTree* node)
{
    FILE* fp = fopen ("temp/STL_graphviz_png.dot", "w");
    assert (fp);

    pr ("digraph STL\n{\n"
        "rankdir = TB\n"
        "graph [ splines = ortho, splines = true ]\n"
        "node  [ shape = record, style = filled, fillcolor = \"#E0FFFF\", color = \"#A0FFFF\" ]\n"
        "edge  [ arrowhead = none ]\n\n");

    int num = 0;

    PrintSubtree (fp, node, &num);

    pr ("\n}\n");

    fclose (fp);
}

static void PrintSubtree (FILE* fp, const NodeBinTree* node, int* num)
{
    fprintf (fp, "\nf%d", *num);

    int curNum = *num;

    pr (" [ label = \"" BIN_TREE_DATA_PRINT_SPECIFIER, node->data);

    if (node->left == nullptr && node->left == nullptr)
        pr ("\", fillcolor = \"#CCFFCC\", color = \"#CCFFCC\" ]\n");
    else
        pr ("?\" ]\n");

    if (node->left != nullptr)
    {
        (*num)++;
        fprintf (fp, "f%d->f%d [ label = \" да \"]\n", curNum, *num);
        PrintSubtree (fp, node->left, num);
    }

    if (node->right != nullptr)
    {
        fprintf (fp, "f%d->f%d [ label = \" нет \"]\n", curNum, *num);
        PrintSubtree (fp, node->right, num);
    }

    (*num)++;
}

#undef pr
