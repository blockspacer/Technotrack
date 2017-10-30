#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include "akinator.hpp"

enum { SIZE_OF_SENTENCE = 32 };

Akinator::Akinator (FILE* input):
    input_ (input),
    tree_  (NULL),
    Buffer (NULL)
{
    fromFileToArray ();
}

Akinator::~Akinator ()
{
    tree_->recDestructor ();
    delete [] Buffer;
}

void Akinator::fromFileToArray ()
{
    assert (input_); 

    fseek (input_, 0, SEEK_END);
    long fileSize = ftell (input_);
    rewind (input_);

    Buffer = new char [fileSize];

    size_t  charQt = fread (Buffer, sizeof(char), 
            (size_t) fileSize, input_);
    assert (charQt ==  (size_t) fileSize);

    tree_ =  buildTreeRec (Buffer, NULL);
}

void Akinator::addTeacher (Node* curNode)
{
    char* teacher  = new char [SIZE_OF_SENTENCE];
    char* question = new char [SIZE_OF_SENTENCE];

    printf ("Enter your teacher.\n");
    scanf (" %[^\n]", teacher);
    printf ("What is the difference between %s and %s?\n",
            teacher, curNode->data_);
    scanf (" %[^\n]", question);

    Node* newNode    = new Node (curNode->parent, question);
    Node* newTeacher = new Node (newNode, teacher);

    if (tree_->isLeftNode (curNode)) 
        newNode->parent->left = newNode;
    else newNode->parent->right = newNode;

    newNode->left   = newTeacher;
    newNode->right  = curNode;
    curNode->parent = newNode;
}

void Akinator::menu ()
{
    printf ("\nHello, it's Akinator!\n\n");
    printf ("(1) Play the game.\n");
    printf ("(2) Print tree.\n");
    printf ("(3) Instruction.\n");
    printf ("(4) Finish the program.\n");
    printf ("(5) Description.\n");

    char character = 0;

    while (character != '4')
    {
        printf ("\nChoose the mode: ");
        scanf (" %c", &character);
        switch (character)
        {
            case '1':

                printf ("Let's play a game. You can answer "
                        "only 'y'/'n' (yes or no).\n");
                game (tree_);
                fseek (input_, 0, SEEK_SET);
                tree_->printTree (input_);
                break;

            case '2': 
            
                treeDump (tree_); 
                break;

            case '3':

                printf ("\n~~~~~INSTRUCTION~~~~~\n\n"
                        "In 'Play the game' mode:\n"
                        "Press 'y' if your answer is 'yes'.\n"
                        "Press 'n' if your answer is 'no'.\n\n"
                        "'Print tree' mode shows you the tree.\n\n"
                        "In 'Description' mode:\n"
                        "Enter the teacher and press 'Enter'.\n\n"
                        "~~~Made by Detinin Roman~~~\n"); 
                break;

            case '4': 
                
                printf ("Goodbye!\n\n"); 
                return; 
                break;

            case '5':

                description (); 
                break;

            default:

                printf ("You've entered a wrong character!\n");
                return;
        }
    }
}


void Akinator::game (Node* curNode)
{
    printf ("%s\n", curNode->data_);

    assert (!(curNode->right && !curNode->left));
    assert (!(!curNode->right && curNode->left));

    char answer = 0;
     
    if (!curNode->right)
    {
        printf ("Have I guessed?\n");
        scanf (" %c", &answer);

        if (answer == 'y') {
            printf ("\nThat's all. Hope you enjoyed the game!\n");
            return;
        } 
        else if (answer == 'n') {
            printf ("Do you want to continue?\n");
            scanf (" %c", &answer);

            if (answer == 'n') {
                printf ("\nThe game is finished \n");
                return;
            } 
            else if (answer == 'y') {
                addTeacher (curNode);
                return;
            } 
            else {
                printf ("\nYou've entered a wrong character.\n");
                exit (1);
            }
        }
    }

    scanf (" %c", &answer);

    switch (answer)
    {
        case 'y':

            assert (curNode->left);
            game   (curNode->left);
            break;

        case 'n':

            assert (curNode->right);
            game   (curNode->right);
            break;

        default:

            printf ("\nYou've entered a wrong character.\n");
            exit (1);
    }
}


void Akinator::treeDump (Node* tree)
{
    assert (tree); 

    FILE* ptrFile = fopen ("dumpFile.gv", "w");
    assert (ptrFile);

    fprintf (ptrFile, "digraph graf {\n");
    nodeDump (tree, ptrFile);
    fprintf (ptrFile, "}");
    fclose (ptrFile);

    system ("dot dumpFile.gv -Tpng -o dumpFile.png");
    system ("xdot dumpFile.gv");
}

void Akinator::nodeDump (Node* tree, FILE* ptrFile)
{
    assert (tree);
    assert (ptrFile);

    fprintf (ptrFile, "treeNode_%p [label=\""
                      "[%p]\\l"
                      "parent [%p]\\l"
                      "left   [%p]\\l"
                      "right  [%p]\\l"
                      "string [%p] = %s\\l"
                      "\"]\n",
    tree, tree, tree->parent, tree->left, tree->right,
    tree->data_, tree->data_);

    if (tree->left) {
        fprintf  (ptrFile, "treeNode_%p->treeNode_%p\n", tree, 
                tree->left);
        nodeDump (tree->left, ptrFile);
    }

    if (tree->right) {
        fprintf  (ptrFile, "treeNode_%p->treeNode_%p\n", tree,
                tree->right);
        nodeDump (tree->right, ptrFile);
    }
}

void Akinator::description ()
{
    printf ("Enter your teacher: ");

    char* requiredTeacher = new char [SIZE_OF_SENTENCE];
    scanf (" %[^\n]", requiredTeacher);

    Node* requiredNode = findTeacher (tree_, requiredTeacher);
    delete [] requiredTeacher;

    if (!requiredNode) {
        printf ("I don't know such teacher!\n");
        return;
    }

    if (requiredNode->parent) {
        printDescription (requiredNode->parent);
    }
}

Node* Akinator::findTeacher (Node* curNode, char* requiredTeacher)
{
    if (!curNode) return NULL;

    if (!(strcmp (curNode->data_, requiredTeacher))) {
        return curNode;
    }
    else {
        Node* inLeft = findTeacher (curNode->left, requiredTeacher);
        if (inLeft) return inLeft;

        Node* inRight = findTeacher(curNode->right, requiredTeacher);
        if (inRight) return inRight;

        return NULL;
    }
}

void Akinator::printDescription (Node* node)
{
    assert (node);
    assert (node->data_);

    if (node->parent) {
        if (tree_->isLeftNode (node))
            printf ("%s\n", node->parent->data_);
        else printf ("! (%s)\n", node->parent->data_);

        printDescription (node->parent);
    } 
    else return;
}
