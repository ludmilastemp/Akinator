#include "STL_akinator.h"

static NodeBinTree*
CreateObject (NodeBinTree* root);

static int
FindObjectRecursively (NodeBinTree* node,
                       Stack_WayToNode* way,
                       const char* object);

static NodeBinTree*
DescribeObject (NodeBinTree* node,
                const char* object,
                Stack_WayToNode* way,
                int initialStep = 0,
                long long initialSize = 0);

static NodeBinTree*
DescribeObjectDifference (BinTree* tree,
                          const char* object1,
                          Stack_WayToNode* way1,
                          const char* object2,
                          Stack_WayToNode* way2);

static NodeBinTree*
FoundAnswer (NodeBinTree* node);

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
    char answer[MAX_LEN_ANS] = { 0 };

    printf ("Пожалуйста, отвечайте только '%s' или '%s'\n", POSITIVE_ANSWER, NEGATIVE_ANSWER);

    while (true)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            FoundAnswer (node);

            return node;
        }

        printf ("Это %s?\n", node->data);

        scanf (FORMAT_SPECIFICATION_ANS, answer);

        if (strcmp (answer, POSITIVE_ANSWER) == 0)
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
        else if (strcmp (answer, NEGATIVE_ANSWER) == 0)
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
            printf ("Да ну блин, я же просил отвечать только '%s' или '%s'\n", POSITIVE_ANSWER, NEGATIVE_ANSWER);
        }
    }

    return nullptr;
}

NodeBinTree*
FindObject (BinTree* tree, const char* object)
{
    if (tree == nullptr)
    {
        printf ("no tree found\n");
        return nullptr;
    }

    if (object == nullptr)
    {
        printf ("no object point found\n");
        return nullptr;
    }

    Stack_WayToNode way = {};
    StackCtor (&way);

    FindObjectRecursively (tree->root, &way, object);

    if (way.size == 0)
    {
        printf ("Я покопался в ствоих чертогах разума, но к сожалению, ничего не нашел :(\n");
    }
    else
    {
        printf ("\nХихи, сейчас я тебе все про него расскажу\n");
        DescribeObject (tree->root, object, &way);
    }

    StackDtor (&way);

    return tree->root;
}

int
CompareObjects (BinTree* tree, const char* object1, const char* object2)
{
    Stack_WayToNode wayObject1 = {};
    StackCtor (&wayObject1);

    Stack_WayToNode wayObject2 = {};
    StackCtor (&wayObject2);

    FindObjectRecursively (tree->root, &wayObject1, object1);
    FindObjectRecursively (tree->root, &wayObject2, object2);

    if (wayObject1.size == 0 || wayObject2.size == 0)
    {
        printf ("Я покопался в ствоих чертогах разума, но к сожалению, я не знаю, кто такой ");

        if (wayObject1.size == 0) printf ("%s\n", object1);
        if (wayObject2.size == 0) printf ("%s\n", object2);
    }
    else
    {
        DescribeObjectDifference (tree, object1, &wayObject1, object2, &wayObject2);
    }

    StackDtor (&wayObject1);
    StackDtor (&wayObject2);

    return 0;
}

static NodeBinTree*
FoundAnswer (NodeBinTree* node)
{
    if (node == nullptr)
    {
        printf ("no node found\n");
        return 0;
    }

    char answer[MAX_LEN_ANS] = { 0 };
    printf ("Ответ: %s\n", node->data);

    while (true)
    {
        printf ("\nКак ты считаешь, я заслужил синюю руку?\n");

        scanf (FORMAT_SPECIFICATION_ANS, answer);

        if (strcmp (answer, POSITIVE_ANSWER) == 0)
        {
            printf ("Я всегда в себя верил!\n");
            return node;
        }
        else if (strcmp (answer, NEGATIVE_ANSWER) == 0)
        {
            CreateObject (node);
            return 0;
        }
        else
        {
            printf ("Да ну блин, я же просил отвечать только '%s' или '%s'\n", POSITIVE_ANSWER, NEGATIVE_ANSWER);
        }
    }

    return node;
}

static NodeBinTree*
CreateObject (NodeBinTree* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    char* answer = (char*) calloc (MAX_LEN_STR, sizeof (char));
    if (answer == nullptr)
    {
        printf ("ERROR_NOT_MEMORY\n");
        return nullptr;
    }

    char* question = (char*) calloc (MAX_LEN_STR, sizeof (char));
    if (question == nullptr)
    {
        printf ("ERROR_NOT_MEMORY\n");
        return nullptr;
    }

    printf ("А кто это был?\n");
    scanf (FORMAT_SPECIFICATION_STR, answer);

    printf ("Какое свойство его отличает от %s?\
             \nВведите свойство: %s ", node->data, answer);
    scanf (FORMAT_SPECIFICATION_STR, question);

    node->left  = NodeBinTreeCtor (answer,     nullptr, nullptr);
    node->right = NodeBinTreeCtor (node->data, nullptr, nullptr);
    node->data  = question;

    printf ("Благодарю, теперь я стал умнее!\n");

    return node;
}

static int
FindObjectRecursively (NodeBinTree* node, Stack_WayToNode* way, const char* object)
{
    if (way == nullptr)
    {
        printf ("no stack way found\n");
        return 0;
    }

    if (node == nullptr) return 0;

    if (strcmp (node->data, object) == 0)
    {
        return 1;
    }

    StackPush (way, LEFT);

    if (FindObjectRecursively (node->left, way, object))
    {
        return 1;
    }

    StackPop (way, nullptr);

    StackPush (way, RIGHT);

    if (FindObjectRecursively (node->right, way, object))
    {
        return 1;
    }

    StackPop (way, nullptr);

    return 0;
}

static NodeBinTree*
DescribeObject (NodeBinTree* node, const char* object, Stack_WayToNode* way, int initialStep, long long initialSize)
{
    if (node == nullptr)  return nullptr;
    if (way == nullptr)   return nullptr;
    if (object != 0)      printf ("%s \n", object);
    if (initialSize == 0) initialSize = way->size;

    for (int i = initialStep; i < initialSize; i++)
    {
        if (way->data[i] == LEFT)  printf ("  ");
        else printf ("  не ");

        printf ("%s\n", node->data);

        if (way->data[i] == LEFT)  node = node->left;
        else node = node->right;
    }

    return node;
}

static NodeBinTree*
DescribeObjectDifference (BinTree* tree, const char* object1, Stack_WayToNode* way1, const char* object2, Stack_WayToNode* way2)
{
    if (tree == nullptr    ||
        way1 == nullptr    ||
        way2 == nullptr    ||
        object1 == nullptr ||
        object2 == nullptr)   return nullptr;

    printf ("\nПрисаживайтесь поудобнее\n");

    NodeBinTree* node = tree->root;
    int i = 0;

    if (way1->data[0] == way2->data[0])
    {
        printf ("%s похож на %s, тем что они оба \n", object1, object2);

        while (i < way1->size && i < way2->size &&
               way1->data[i] == way2->data[i]) i++;

        node = DescribeObject (node, 0, way1, 0, i);
    }

    if (way1->data[0] == way2->data[0]) printf ("HO ");
    DescribeObject (node, object1, way1, i);

    if (way1->data[0] == way2->data[0]) printf ("A  ");
    DescribeObject (node, object2, way2, i);

    return nullptr;
}
