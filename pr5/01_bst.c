#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    long int value;
    struct Node *right;
    struct Node *left;
    struct Node *parent;
} Node;

typedef struct Tree
{
    long int key;
    struct Node *root;
} Tree;

void init(Tree *t)
{
    Node *rootNode = (Node *)malloc(sizeof(Node));
    Tree *tempTree = (Tree *)malloc(sizeof(Tree));
    rootNode->parent = NULL;
    rootNode->right = NULL;
    rootNode->left = NULL;
    tempTree->root = rootNode;

    *t = *tempTree;
}

long int remove_min(Node *n)
{
    long int value;

    Node *rootNode;
    rootNode = (Node *)malloc(sizeof(Node));
    rootNode = n;

    Node *leftNode = (Node *)malloc(sizeof(Node));
    leftNode = rootNode;

    while (rootNode->left)
    {
        rootNode = rootNode->left;
    }
    if (rootNode->right)
    {
        rootNode = rootNode->right;
        remove_min(rootNode);
    }
    else
    {
        value = rootNode->value;
        if (rootNode->value > rootNode->parent->value)
        {
            rootNode->parent->right = NULL;
        }
        else
        {
            rootNode->parent->left = NULL;
        }
        rootNode->parent = NULL;
        free(rootNode);
        return value;
    }
}

void clean(Tree *t)
{
    Node *rootNode = (Node *)malloc(sizeof(Node));
    rootNode = t->root;
    while (rootNode->left || rootNode->right)
    {
        remove_min(rootNode);
    }
    rootNode->left = NULL;
    rootNode->right = NULL;
    rootNode->parent = NULL;
    t->root = NULL;
    t->key = 0;
    free(rootNode);
}

Node *find(Tree *t, long int value)
{
    if (t)
    {
        if (t->key > 0)
        {
            Node *rootNode;
            rootNode = (Node *)malloc(sizeof(Node));
            rootNode = t->root;

            while (rootNode)
            {
                if (rootNode->value == value)
                {
                    return rootNode;
                }
                else if (value > rootNode->value && rootNode->right)
                {
                    rootNode = rootNode->right;
                }
                else if (value < rootNode->value && rootNode->left)
                {
                    rootNode = rootNode->left;
                }
                else
                {
                    return NULL;
                }
            }
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
    return NULL;
}

long int insert(Tree *t, long int value)
{
    Node *addNode;
    addNode = (Node *)malloc(sizeof(Node));
    addNode->parent = addNode;
    addNode->left = NULL;
    addNode->right = NULL;
    addNode->value = value;

    Tree *tempTree = (Tree *)malloc(sizeof(Tree));
    tempTree = t;

    Tree *tempTree1 = (Tree *)malloc(sizeof(Tree));
    tempTree1 = t;

    Node *rootNode = (Node *)malloc(sizeof(Node));
    rootNode = tempTree->root;

    long int keyNode = tempTree->key;
    if (tempTree && rootNode && addNode)
    {
        if (find(tempTree1, value))
        {
            return 1;
        }
        else
        {
            if (keyNode != 0)
            {
                rootNode = tempTree->root;
                while (rootNode)
                {
                    if (value > rootNode->value)
                    {
                        if (rootNode->right)
                        {
                            rootNode = rootNode->right;
                            continue;
                        }
                        else
                        {
                            addNode->parent = rootNode;
                            rootNode->right = addNode;
                            tempTree->key = keyNode + 1;
                            return 0;
                        }
                    }
                    else
                    {
                        if (rootNode->left)
                        {
                            rootNode = rootNode->left;
                            continue;
                        }
                        else
                        {
                            addNode->parent = rootNode;
                            rootNode->left = addNode;
                            tempTree->key = keyNode + 1;
                            return 0;
                        }
                    }
                }
                return 2;
            }
            else
            {
                tempTree->root = addNode;
                tempTree->key = 1;
                return 0;
            }
        }
    }
    else
    {
        return 2;
    }
}

long int remove_node(Tree *t, long int value)
{
    Node *foundNode = (Node *)malloc(sizeof(Node));
    foundNode = find(t, value);

    if (foundNode)
    {
        if (foundNode->left && foundNode->right)
        {
            Node *leftNode = (Node *)malloc(sizeof(Node));
            Node *rightRoot = (Node *)malloc(sizeof(Node));
            Node *leftrootNode = (Node *)malloc(sizeof(Node));
            Node *leftRightRootNode = (Node *)malloc(sizeof(Node));
            Node *leftmostRightRootNode = (Node *)malloc(sizeof(Node));
            rightRoot = foundNode->right;
            leftrootNode = foundNode->left;
            if (rightRoot->left)
            {
                leftNode = rightRoot->left;
                while (leftNode->left)
                {
                    leftNode = leftNode->left;
                }
                if (leftNode->right)
                {
                    leftRightRootNode = leftNode->right;
                    if (rightRoot->right)
                    {
                        leftmostRightRootNode = rightRoot->right;
                        while (leftmostRightRootNode->left)
                        {
                            leftmostRightRootNode = leftmostRightRootNode->left;
                        }
                    }
                    else
                    {
                        leftmostRightRootNode = leftNode->parent;
                    }
                    leftRightRootNode->parent = leftmostRightRootNode;
                    leftmostRightRootNode->left = leftRightRootNode;
                    leftNode->right = NULL;
                }
                leftNode->parent->left = NULL;
                leftNode->parent = NULL;
                leftNode->right = rightRoot;
                rightRoot->parent = NULL;
                rightRoot->parent = leftNode;
                leftNode->left = leftrootNode;
                leftrootNode->parent = NULL;
                leftrootNode->parent = leftNode;
                leftNode->parent = foundNode->parent;
                if (leftNode->parent == foundNode)
                {
                    leftNode->parent = leftNode;
                    t->root = leftNode;
                }
                else
                {
                    if (leftNode->parent->value < leftNode->value)
                    {
                        leftNode->parent->right = leftNode;
                    }
                    else
                    {
                        leftNode->parent->left = leftNode;
                    }
                }
                foundNode->left = NULL;
                foundNode->right = NULL;
                foundNode->parent = NULL;
                foundNode = NULL;
                return 0;
            }
            else
            {
                rightRoot->left = leftrootNode;
                leftrootNode->parent = NULL;
                leftrootNode->parent = rightRoot;
                rightRoot->parent = foundNode->parent;
                if (rightRoot->parent == foundNode)
                {
                    rightRoot->parent = rightRoot;
                    t->root = rightRoot;
                }
                else
                {
                    if (rightRoot->parent->value < rightRoot->value)
                    {
                        rightRoot->parent->right = rightRoot;
                    }
                    else
                    {
                        rightRoot->parent->left = rightRoot;
                    }
                }
                foundNode->left = NULL;
                foundNode->right = NULL;
                foundNode->parent = NULL;
                foundNode = NULL;
                return 0;
            }
            return 0;
        }
        else if (foundNode->left)
        {
            Node *firstLeftNode = (Node *)malloc(sizeof(Node));
            firstLeftNode = foundNode->left;
            if (t->root == foundNode)
            {
                firstLeftNode->parent = firstLeftNode;
                t->root = firstLeftNode;
            }
            else
            {
                firstLeftNode->parent = foundNode->parent;
                if (foundNode->value > foundNode->parent->value)
                {
                    firstLeftNode->parent->right = firstLeftNode;
                }
                else
                {
                    firstLeftNode->parent->left = firstLeftNode;
                }
            }
            return 0;
        }
        else if (foundNode->right)
        {
            Node *firstRightNode = (Node *)malloc(sizeof(Node));
            firstRightNode = foundNode->right;
            if (foundNode == t->root)
            {
                firstRightNode->parent = firstRightNode;
                t->root = firstRightNode;
            }
            else
            {
                firstRightNode->parent = foundNode->parent;
                if (foundNode->value > foundNode->parent->value)
                {
                    firstRightNode->parent->right = firstRightNode;
                }
                else
                {
                    firstRightNode->parent->left = firstRightNode;
                }
            }
            return 0;
        }
        else
        {
            if (foundNode->value > foundNode->parent->value)
            {
                foundNode->parent->right = NULL;
            }
            else
            {
                foundNode->parent->left = NULL;
            }
            foundNode->parent = NULL;
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

long int rotate_right(Node *n)
{
    Node *rootNode = (Node *)malloc(sizeof(Node));
    rootNode = n;

    Node *leftrootNode = (Node *)malloc(sizeof(Node));
    leftrootNode = rootNode->left;

    if (rootNode && leftrootNode)
    {
        rootNode->left = leftrootNode->right;
        if (leftrootNode->right)
        {
            leftrootNode->right->parent = rootNode;
        }
        leftrootNode->parent = rootNode->parent;
        if (leftrootNode->parent == rootNode)
        {
            leftrootNode->parent = leftrootNode;
        }
        else
        {
            if (leftrootNode->parent->value < leftrootNode->value)
            {
                leftrootNode->parent->right = leftrootNode;
            }
            else
            {
                leftrootNode->parent->left = leftrootNode;
            }
        }
        leftrootNode->right = rootNode;
        rootNode->parent = leftrootNode;
        return 0;
    }
    else
    {
        return 1;
    }
}

long int rotate_left(Node *n)
{
    Node *rootNode = (Node *)malloc(sizeof(Node));
    rootNode = n;

    Node *rightrootNode = (Node *)malloc(sizeof(Node));
    rightrootNode = rootNode->right;

    Node *rightNodeLeftTree = (Node *)malloc(sizeof(Node));

    if (rootNode && rightrootNode)
    {
        rightNodeLeftTree = rightrootNode->left;
        rootNode->right = rightNodeLeftTree;
        if (rightNodeLeftTree)
        {
            rightNodeLeftTree->parent = rootNode;
        }
        rightrootNode->parent = rootNode->parent;
        if (rightrootNode->parent == rootNode)
        {
            rightrootNode->parent = rightrootNode;
        }
        rootNode->parent = rightrootNode;
        rightrootNode->left = rootNode;
        return 0;
    }
    else
    {
        return 1;
    }
}

void print(Node *n)
{
    Node *rootNode = (Node *)malloc(sizeof(Node));
    rootNode = n;

    Node *emptyNode = (Node *)malloc(sizeof(Node));

    if (rootNode && emptyNode)
    {
        long int oldlvl = 1, lvl = 1, cnt = 0, i = 0, j = 0;
        Node **Nodes = (Node **)malloc(lvl * sizeof(Node *));
        Nodes[0] = rootNode;
        printf("%ld\n", Nodes[0]->value);
        bool flag = true;
        long int size = oldlvl;
        while (flag)
        {
            flag = false;
            oldlvl = lvl;
            lvl *= 2;
            size += lvl;
            Nodes = (Node **)realloc(Nodes, size * sizeof(Node *));
            for (i = oldlvl - 1, j = lvl - 1; i < (lvl - 1); i++, j++)
            {
                if (Nodes[i]->left && Nodes[i] != emptyNode)
                {
                    flag = true;
                    Nodes[j] = Nodes[i]->left;
                }
                else
                {
                    Nodes[j] = emptyNode;
                }
                j += 1;
                if (Nodes[i]->right && Nodes[i] != emptyNode)
                {
                    flag = true;
                    Nodes[j] = Nodes[i]->right;
                }
                else
                {
                    Nodes[j] = emptyNode;
                }
            }
            if (flag)
            {
                for (i = oldlvl - 1; i < (lvl - 1); i++)
                {
                    if (Nodes[i]->left && Nodes[i] != emptyNode)
                    {
                        printf("%ld ", Nodes[i]->left->value);
                    }
                    else
                    {
                        printf("_ ");
                    }
                    ++j;
                    if (Nodes[i]->right && Nodes[i] != emptyNode)
                    {
                        printf("%ld ", Nodes[i]->right->value);
                    }
                    else
                    {
                        printf("_ ");
                    }
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    else
    {
        printf("-\n");
        printf("\n");
    }
}

// Вывести все значения дерева t, аналогично функции print
void print_tree(Tree *t)
{
    Node *rootNode = (Node *)malloc(sizeof(Node));
    rootNode = t->root;
    if (t->key > 0 && rootNode)
        print(rootNode);
    else
    {
        printf("-\n");
        printf("\n");
    }
}

int main()
{
    Tree *t = (Tree *)malloc(sizeof(Tree));
    Node *rootNode = (Node *)malloc(sizeof(Node));
    long int value;
    init(t);
    for (long int i = 0; i < 4; i++)
    {
        scanf("%ld", &value);
        insert(t, value);
    }
    print_tree(t);
    for (long int i = 0; i < 3; i++)
    {
        scanf("%ld", &value);
        insert(t, value);
    }
    print_tree(t);
    long int m1;
    scanf("%ld", &m1);
    rootNode = find(t, m1);
    if (rootNode)
    {
        if (rootNode->parent && rootNode->parent != rootNode)
            printf("%ld ", rootNode->parent->value);
        else
            printf("_ ");
        if (rootNode->left)
            printf("%ld ", rootNode->left->value);
        else
            printf("_ ");
        if (rootNode->right)
            printf("%ld", rootNode->right->value);
        else
            printf("_");
    }
    else
    {
        printf("-");
    }
    printf("\n");
    printf("\n");
    scanf("%ld", &m1);
    rootNode = find(t, m1);
    if (rootNode)
    {
        if (rootNode->parent && rootNode->parent != rootNode)
            printf("%ld ", rootNode->parent->value);
        else
            printf("_ ");
        if (rootNode->left)
            printf("%ld ", rootNode->left->value);
        else
            printf("_ ");
        if (rootNode->right)
            printf("%ld", rootNode->right->value);
        else
            printf("_");
    }
    else
    {
        printf("-");
    }
    printf("\n");
    printf("\n");
    scanf("%ld", &m1);
    if (remove_node(t, m1) == 0)
    {
        t->key = t->key - 1;
    }
    if (t->key > 0)
    {
        rootNode = t->root;
        t->root = rootNode->parent;
    }
    print_tree(t);
    rootNode = t->root;
    while (rotate_left(rootNode) == 0)
    {
        t->root = rootNode->parent;
        rootNode = t->root;
    }
    print_tree(t);
    rootNode = t->root;
    while (rotate_right(rootNode) == 0)
    {
        t->root = rootNode->parent;
        rootNode = t->root;
    }
    print_tree(t);
    printf("%ld\n", t->key);
    printf("\n");
    clean(t);
    print_tree(t);
    return 0;
}
