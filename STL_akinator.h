#ifndef STL_akinator_
#define STL_akinator_

#include "Bintree/STL_bintree_struct.h"
#include "../SPU/spu/STACK_FILE_TYPE_int.h"
#include "../SPU/lib/STL_stack/generic.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

const int MAX_LEN_STR = 100;
const int MAX_LEN_ANS = 10;

const int FIND  = 696969;    // почему не enum
const int LEFT  = 1;
const int RIGHT = 2;

const int  POSITIVE_ANSWER_LEN = 2;
const char POSITIVE_ANSWER[] = "да";
const int  NEGATIVE_ANSWER_LEN = 3;
const char NEGATIVE_ANSWER[] = "нет";

NodeBinTree*
PredictObject (BinTree* tree);

NodeBinTree*
FindObject (BinTree* tree, const char* answer);

int
CompareObjects (BinTree* tree, const char* object1, const char* object2);

#endif /* STL_akinator_ */
