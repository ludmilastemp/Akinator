#include "STL_graphviz.h"

#include <assert.h>

#define pr(...) fprintf (fp, __VA_ARGS__)

static void PrintSubtree (FILE* fp, const NodeBinTree* node, int* num);

int  STL_GraphvizBinTree (const NodeBinTree* node)
{
    FILE* fp = fopen ("BinTree/STL_graphviz_png.txt", "w");
    assert (fp);

    pr ("digraph STL\n{\n");

    pr ("rankdir = TB\n");
    pr ("graph [ splines = ortho, splines = true ]\n");
    pr ("node  [ shape = record, style = filled, fillcolor = \"#E0FFFF\", color = \"#A0FFFF\" ]\n");
    pr ("edge  [ arrowhead = none ]\n\n");

    int num = 0;

    PrintSubtree (fp, node, &num);

    pr ("\n}\n");

    fclose (fp);

}

static void PrintSubtree (FILE* fp, const NodeBinTree* node, int* num)
{
    fprintf (fp, "f%d", *num);

    if (node == nullptr)
    {
        pr (" [label = \" nil \", fillcolor = \"#E0FFDF\", color = \"#E0FFDF\" ]\n");
        (*num)++;
    }

    else
    {
        int curNum = *num;

        pr (" [label = \" %d \" ]\n", node->data);

        (*num)++;
        fprintf (fp, "f%d->f%d\n", curNum, *num);
        PrintSubtree (fp, node->left, num);

        fprintf (fp, "f%d->f%d\n", curNum, *num);
        PrintSubtree (fp, node->right, num);
        (*num)++;
    }
}

#undef pr
