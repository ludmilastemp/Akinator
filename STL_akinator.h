#ifndef STL_akinator_
#define STL_akinator_

#include "Bintree/STL_bintree_struct.h"
#include "BinTree/STACK_FILE_TYPE_WayToNode.h"
#include "../Stack/generic.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

enum AkinatorFunctions
{
    PredictObjectMode        = '1',
    FindObjectMode           = '2',
    CompareObjectsMode       = '3',
    GraphvizBinTreeMode      = '4',
    BinTreePrintPreorderMode = '5',
    ExitMode                 = '6',
};

const int  MAX_LEN_STR = 100;
const char FORMAT_SPECIFICATION_STR[] = " %99[^\n]";
const int  MAX_LEN_ANS = 10;
const char FORMAT_SPECIFICATION_ANS[] = " %9[^\n]";

const char POSITIVE_ANSWER[] = "да";
const char NEGATIVE_ANSWER[] = "нет";

NodeBinTree*
PredictObject (BinTree* tree);

NodeBinTree*
FindObject (BinTree* tree, const char* answer);

int
CompareObjects (BinTree* tree, const char* object1, const char* object2);

#endif /* STL_akinator_ */
