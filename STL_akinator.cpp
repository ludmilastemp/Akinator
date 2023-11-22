#include "STL_akinator.h"

static const int MAX_LEN_STR = 100;

static const int FIND  = 696969;
static const int LEFT  = 1;
static const int RIGHT = 2;

static NodeBinTree*
CreateObject (NodeBinTree* root);

static NodeBinTree*
FindObjectRecursively (NodeBinTree* node,
                       Stack_int* way,
                       const char* answer);

static NodeBinTree*
PrintObject (NodeBinTree* node,
             const char* answer,
             Stack_int* way,
             int initialStep = 0,
             int initialSize = 0);

static NodeBinTree*
PrintObjectDifference (BinTree* tree,
                       const char* object1,
                       Stack_int* way1,
                       const char* object2,
                       Stack_int* way2);

NodeBinTree*
PredictObject (BinTree* tree)
{
    if (tree == nullptr)
    {
        printf ("no tree found\n");
        return 0;
    }

    if (tree->root == nullptr)
    {
        printf ("no tree root found\n");
        return 0;
    }

    NodeBinTree* node = tree->root;
    char answer[10] = { 0 };

    printf ("Пожалуйста, отвечайте только 'дa' или 'нет'\n");

    while (true)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            printf ("Ответ: %s\n", node->data);

            while (true)
            {
                printf ("\nКак ты считаешь, я заслужил синюю руку?\n");

                scanf ("%s", &answer);

                if (strncmp (answer, "да", 2) == 0)
                {
                    printf ("Я всегда в себя верил!\n");
                    return node;
                }
                else if (strncmp (answer, "нет", 3) == 0)
                {
                    CreateObject (node);
                    return 0;
                }
                else
                {
                    printf ("Да ну блин, я в просил отвечать только 'дa' или 'нет'\n");
                }
            }

            return node;
        }

        printf ("Это %s?\n", node->data);

        scanf ("%s", &answer);

        if (strncmp (answer, "да", 2) == 0)
        {
            if (node->left != nullptr)
            {
                node = node->left;
            }
            else
            {
                printf ("Incorrect tree");
                return node;
            }
        }
        else if (strncmp (answer, "нет", 3) == 0)
        {
            if (node->right != nullptr)
            {
                node = node->right;
            }
            else
            {
                printf ("Incorrect tree");
                return node;
            }
        }
        else
        {
            printf ("Да ну блин, я в просил отвечать только 'дa' или 'нет'\n");
        }
    }

    return 0;
}

NodeBinTree*
FindObject (BinTree* tree, const char* answer)
{
    Stack_int way = {};
    StackCtor (&way);

    FindObjectRecursively (tree->root, &way, answer);

    if (way.size == 0)
    {
        printf ("Я покопался в ствоих чертогах разума, но к сожалению, ничего не нашел :(\n");
    }
    else
    {
        int lastWay = 0;
        StackPop (&way, &lastWay);

        printf ("\nХихи, сейчас я тебе все про него расскажу\n");
        PrintObject (tree->root, answer, &way);
    }

    StackDtor (&way);

    return tree->root;
}

int
CompareObject (BinTree* tree, const char* object1, const char* object2)
{
    Stack_int wayObject1 = {};
    StackCtor (&wayObject1);

    Stack_int wayObject2 = {};
    StackCtor (&wayObject2);

    FindObjectRecursively (tree->root, &wayObject1, object1);
    FindObjectRecursively (tree->root, &wayObject2, object2);

    if (wayObject1.size == 0)
    {
        printf ("Я покопался в ствоих чертогах разума, но к сожалению,  \
                 я не знаю, кто такой %s :(\n", object1);
    }
    else if (wayObject2.size == 0)
    {
        printf ("Я покопался в ствоих чертогах разума, но к сожалению,  \
                 я не знаю, кто такой %s :(\n", object2);
    }
    else
    {
        int lastWay = 0;
        StackPop (&wayObject1, &lastWay);
        StackPop (&wayObject2, &lastWay);

        PrintObjectDifference (tree, object1, &wayObject1, object2, &wayObject2);
    }

    StackDtor (&wayObject1);
    StackDtor (&wayObject2);
}

static NodeBinTree*
CreateObject (NodeBinTree* root)
{
    char answer[MAX_LEN_STR]   = { 0 };
    char question[MAX_LEN_STR] = { 0 };

    printf ("А кто это был?\n");

    int i = 0;
    while (iscntrl(question[i++] = getchar()) == 0);
    question[i - 1] = '\0';

    while ((question[0] = getchar()) != '\n');

    printf ("Какое свойство его отличает от %s?\
             \nВведите свойство: %s ", root->data, answer);

    i = 0;
    while (iscntrl(question[i++] = getchar()) == 0);
    question[i - 1] = '\0';

    char* answerCalloc = (char*) calloc (strlen (answer), sizeof (char));
    assert (answerCalloc);  // error

    char* questionCalloc = (char*) calloc (strlen (question), sizeof (char));
    assert (questionCalloc);  // error

    strncpy (answerCalloc,   answer,   strlen(answer));
    strncpy (questionCalloc, question, strlen(question));

    root->left  = NodeBinTreeCtor (answerCalloc, 0, 0);
    root->right = NodeBinTreeCtor (root->data, 0, 0);
    root->data  = questionCalloc;

    printf ("Благодарю, теперь я стал умнее!\n");

    return 0;
}

static NodeBinTree*
FindObjectRecursively (NodeBinTree* node, Stack_int* way, const char* answer)
{
    if (way == nullptr)
    {
        printf ("no stack way found\n");
        return 0;
    }

    if (node == nullptr) return 0;

    if (strcmp (node->data, answer) == 0)
    {
        StackPush (way, FIND);
        return 0;
    }

    StackPush (way, LEFT);
    FindObjectRecursively (node->left, way, answer);

    int lastWay = 0;

    StackPop (way, &lastWay);
    if (lastWay == FIND)
    {
        StackPush (way, lastWay);
        return 0;
    }

    StackPush (way, RIGHT);
    FindObjectRecursively (node->right, way, answer);

    StackPop (way, &lastWay);
    if (lastWay == FIND)
    {
        StackPush (way, lastWay);
        return 0;
    }

    return 0;
}

static NodeBinTree*
PrintObject (NodeBinTree* node, const char* answer, Stack_int* way, int initialStep, int initialSize)
{
    if (node == nullptr) return nullptr;
    if (way == nullptr)  return nullptr;
    if (answer != 0)      printf ("%s \n", answer);
    if (initialSize == 0) initialSize = way->size;

    for (int i = initialStep; i < initialSize; i++)
    {
        if (way->data[i] == LEFT)  printf ("  это ");
        if (way->data[i] == RIGHT) printf ("  это не ");

        printf ("%s\n", node->data);

        if (way->data[i] == LEFT)  node = node->left;
        if (way->data[i] == RIGHT) node = node->right;
    }                               // nen 2 if
                                    // yf erfpfntkz[ 1
    return node;
}

static NodeBinTree*
PrintObjectDifference (BinTree* tree, const char* object1, Stack_int* way1, const char* object2, Stack_int* way2)
{
    printf ("\nПрисаживайтесь поудобнее\n");

    NodeBinTree* node = tree->root;
    int i = 0;

    if (way1->data[0] == way2->data[0])
    {
        printf ("%s похож на %s, тем что они оба \n", object1, object2);

        while (i < way1->size && i < way2->size &&
               way1->data[i] == way2->data[i]) i++;

        node = PrintObject (node, 0, way1, 0, i);
    }

    if (way1->data[0] == way2->data[0]) printf ("HO ");
    PrintObject (node, object1, way1, i);

    if (way1->data[0] == way2->data[0]) printf ("A  ");
    PrintObject (node, object2, way2, i);

    return 0;
}
