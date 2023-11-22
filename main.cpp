#include "Bintree/STL_bintree_struct.h"
#include "Bintree/STL_graphviz.h"
#include "STL_akinator.h"

#include <stdio.h>

int main()
{
    /*
    char ch = 0;

    while (isspace(ch = getchar()));
    printf ("printf %d '%c'\n", ch, ch);

    while (isspace(ch = getchar()));
    printf ("printf %d '%c'\n", ch, ch);

    return 0;       */

                              // хардкод
    BinTree* tree = NodeBinTreeReadPreorder ("STL_preorder.txt");
//
//    const char* s1 = "животное";
//    const char* s2 = "ведет матан";
//
//    const char* s4 = "крокодил";
//    const char* s5 = "Лукашов";
//    const char* s6 = "Богданов";
//
//    NodeBinTree* n4 = NodeBinTreeCtor (s4, 0, 0);
//    NodeBinTree* n5 = NodeBinTreeCtor (s5, 0, 0);
//    NodeBinTree* n6 = NodeBinTreeCtor (s6, 0, 0);
//
//    NodeBinTree* n2 = NodeBinTreeCtor (s2, n5, n6);
//    NodeBinTree* n1 = NodeBinTreeCtor (s1, n4, n2);
//
//    BinTree* tree = BinTreeCtor (n1);

//                \n3. Режим \"википедия c прибамбахом\"

    char answer = 0;

    printf ("Привет, я супер-дупер акинатор\n");
    while (true)
    {
        printf ("\n\nЯ умею делать несколько вещей, что из этого ты хотел бы проверить?\
                \n1. Экстрасенсорные способности\
                \n2. Я расскажу тебе всё\
                \n3. Сине-золотое платье\
                \n4. МРТ моего мозга\
                \n5. Сквозь года, сквозь века\
                \n6. Я пошел спать\
                \n");
        printf ("\nПожалуйста введите номер команды: ");

        while (isspace(answer = getchar()));

        switch ((int)(answer - '0'))
        {
            case 1:
            {
            PredictObject (tree);

            break;
            }

            case 2:
            {
            printf ("Чьи тайны тебе поведать?\n");

            char object[100] = { 0 };
            scanf ("%s", &object);

            FindObject (tree, object);

            break;
            }

            case 3:
            {
            printf ("Кого сегодня будем сравнивать?\n");

            char object1[100] = { 0 };
            char object2[100] = { 0 };

            printf ("Введите первый объект: \n");
            scanf ("%s", &object1);

            printf ("Введите второй объект: \n");
            scanf ("%s", &object2);

            CompareObject (tree, object1, object2);

            break;
            }

            case 4:
            {
            STL_GraphvizBinTree (tree->root);

            system ("dot -Tpng .\\BinTree/STL_graphviz_png.dot -o STL.png");
            printf ("Файл STL находится в основной папке, только не надо его открывать ;)\n");

            break;
            }

            case 5:
            {
            BinTreePrintPreorder (tree->root, "STL_preorder.txt");
            printf ("Ну теперь то я точно это не забуду\n");

            break;
            }

            case 6:
            {
            NodeBinTreeDtor (tree->root);

            return 0;
            }
        default:
            {
            printf ("Я же не умею это... Выбери из того, что я умею\n");
            }
        }

        printf ("\n\nНажмите пробел, а после enter чтобы продолжить...\n");
        while ((answer = getchar()) != ' ');
    }

    return 0;
}
