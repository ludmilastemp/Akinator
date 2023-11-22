#ifndef STL_akinator_
#define STL_akinator_

#include "Bintree/STL_bintree_struct.h"
#include "../SPU/spu/STACK_FILE_TYPE_int.h"
#include "../SPU/lib/STL_stack/generic.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

NodeBinTree*
PredictObject (BinTree* tree);

NodeBinTree*
FindObject (BinTree* tree, const char* answer);

int
CompareObject (BinTree* tree, const char* object1, const char* object2);

#endif /* STL_akinator_ */
