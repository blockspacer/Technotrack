#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "rec_desc.hpp"

RecDescent::RecDescent ():
    str (0),
    ptr (0)
    {
        FILE* source  = fopen ("source", "r");

        fseek (source, 0, SEEK_END);
        long fileSize = ftell (source);
        rewind (source);

        str = new char [fileSize + 1];
        size_t  charQt = fread (str,
                sizeof(char), (size_t) fileSize, source);
        assert (charQt ==  (size_t) fileSize);
        str [fileSize] = '\0';
        PRINT ("fileSize = %d\n", (int) fileSize);

        for (int cnt = 0; cnt < fileSize - 1; cnt++)
        {
            PRINT ("%c", str [cnt]);
        }
        PRINT ("\n");

        fclose (source);
    }

RecDescent::~RecDescent ()
{
    delete [] str;
}

Node* RecDescent::GetN (Node* parent)
{
    PRINT ("I am GetN \n");

    int val = 0;
    while ('0' <= str [ptr] && str [ptr] <= '9') //sscanf %d
    {
        val = val * 10 + str [ptr] - '0';
        ptr++;
    }

    Node* newNode = new Node (parent, val, T_constant);

    PRINT ("I've found %d\n", val);
    return newNode;
}

Node* RecDescent::GetF (Node* parent)
{
    PRINT ("I am GetF\n");
    while (isalpha (str [ptr]))
    {
        const unsigned int SIZE_OF_FUNC = 8;
        char func_name [SIZE_OF_FUNC]   = {};
        int cnt = 0;

        while (isalpha (str [ptr]))
        {
            func_name [cnt] = str [ptr];
            ptr ++;
            cnt ++;
        }

        PRINT ("%s\n", func_name);

        if (!strcmp (func_name, "Ln"))
        {
            PRINT ("I've found Ln\n");
            Node* newNode  = new Node (parent, O_Ln, T_operation);
            Node* LnArg    = GetP (parent);
            newNode->left_ = LnArg;
            LnArg->parent_ = newNode;

            return newNode;
        }
        else if (!strcmp (func_name, "x"))
        {
            PRINT ("I've found X\n");
            Node* newNode = new Node (parent, 0, T_value);
            return newNode;
        }
        else
        {
            printf ("Unknown command!\n");
            exit (0);
        }
    }
    return GetP (parent);
}

Node* RecDescent::GetP (Node* parent)
{
    if (str [ptr] == '(')
    {
        PRINT ("I've found %c\n", str [ptr]);
        ptr++;
        Node* val = GetE (parent);
        PRINT ("I've found %c\n", str [ptr]);
        assert (str [ptr] == ')');
        ptr++;
        return val;
    }
    else { return GetN (parent); }
}

Node* RecDescent::GetT (Node* parent)
{
    PRINT ("I am GetT \n");
    bool cycle_flag = false;
    double data = 0;

    Node* val = GetF (parent);
    Node* newNode = NULL;

    while (str [ptr] == '*' || str [ptr] == '/')
    {
        cycle_flag = true;

        int operation = str [ptr];
        PRINT ("I've found mul or div\n");
        ptr++;
        Node* val2 = GetF (parent);

        (operation == '*')? data = O_mul: data = O_div;

        newNode = new Node (parent, data, T_operation);

        newNode->left_  = val;
        newNode->right_ = val2;
        val->parent_    = newNode;
        val2->parent_   = newNode;
    }
    if (cycle_flag == true) { return newNode; }
    else  { return val; }
}

Node* RecDescent::GetE (Node* parent)
{
    PRINT ("I am GetE \n");
    bool cycle_flag = false;
    double data = 0;

    Node* val = GetT (parent);
    Node* newNode = NULL;

    while (str [ptr] == '+' || str [ptr] == '-')
    {
        cycle_flag = true;

        int operation = str [ptr];
        PRINT ("I've found plus or minus\n");
        ptr++;
        Node* val2 = GetT (parent);

        (operation == '+')? data = O_add: data = O_sub; //redo

        newNode = new Node (parent, data, T_operation);

        newNode->left_  = val;
        newNode->right_ = val2;
        val->parent_    = newNode;
        val2->parent_   = newNode;
    }

    if (cycle_flag == true) { return newNode; }
    else { return val; }
}

Node* RecDescent::GetG (Node* parent)
{
    PRINT ("I am GetG \n");

    Node* head = GetE (parent);

    PRINT ("!!!%s!!!\n", str);
    PRINT ("ptr = %d\n", ptr);
    PRINT ("(ptr - 1) = %c\n", (ptr - 1));
    PRINT ("(ptr) = %c\n", ptr);
    PRINT ("(ptr + 1) = %c\n", (ptr + 1));

    assert (str [ptr + 1] == '\0');
    return head;
}
