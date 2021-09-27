# Введение

Цель работы - изучение базовых команд терминала ОС Linux, получение навыков реализации обхода бинарного дерева в языке программирования C.

## Задание

Задание выполняется с использованием бинарного дерева поиска, реализованного в практической работе 5
Необходимо реализовать обход дерева в ширину, прямой обход дерева без использования рекурсии, а также обратный обход с использованием рекурсии

## Ход работы

__Дерево__ - граф без петель и циклов. Используются для организации данных в виде иерархической структуры.

### Обход дерева в ширину

__Обход в ширину (breadth - first search)__ - один из базовых алгоритмов, лежащий в основе многих других алгоритмов для графов.
Алгоритм поиска в ширину начинает работу с некоторой начальной вершиной и затем проводит обработку каждой вершины с ней.

Реализация функции для обхода дерева в ширину:
```c
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

    Node *nodeOfNULL = (Node *)malloc(sizeof(Node));

    if (rootNode && nodeOfNULL)
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
                if (Nodes[i]->left && Nodes[i] != nodeOfNULL)
                {
                    flag = true;
                    Nodes[j] = Nodes[i]->left;
                }
                else
                {
                    Nodes[j] = nodeOfNULL;
                }
                j += 1;
                if (Nodes[i]->right && Nodes[i] != nodeOfNULL)
                {
                    flag = true;
                    Nodes[j] = Nodes[i]->right;
                }
                else
                {
                    Nodes[j] = nodeOfNULL;
                }
            }
            if (flag)
            {
                for (i = oldlvl - 1; i < (lvl - 1); i++)
                {
                    if (Nodes[i]->left && Nodes[i] != nodeOfNULL)
                    {
                        printf("%ld ", Nodes[i]->left->value);
                    }
                    else
                    {
                        printf("_ ");
                    }
                    ++j;
                    if (Nodes[i]->right && Nodes[i] != nodeOfNULL)
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

void bfs(Node *n)
{
    Node *rootNode;
    rootNode = (Node *)malloc(sizeof(Node));
    rootNode = n;

    Node *nodeOfNULL;
    nodeOfNULL = (Node *)malloc(sizeof(Node));

    if (rootNode && nodeOfNULL)
    {
        long int oldlvl = 1, lvl = 1, cnt = 0, i = 0, j = 0;
        Node **nodes = (Node **)malloc(lvl * sizeof(Node *));
        nodes[0] = rootNode;
        printf("%ld ", nodes[0]->value);
        bool flag = true;
        long int size = oldlvl;
        while (flag)
        {
            flag = false;
            oldlvl = lvl;
            lvl *= 2;
            size += lvl;
            nodes = (Node **)realloc(nodes, size * sizeof(Node *));
            for (i = oldlvl - 1, j = lvl - 1; i < (lvl - 1); i++, j++)
            {
                if (nodes[i]->left && nodes[i] != nodeOfNULL)
                {
                    flag = true;
                    nodes[j] = nodes[i]->left;
                }
                else
                {
                    nodes[j] = nodeOfNULL;
                }
                j += 1;
                if (nodes[i]->right && nodes[i] != nodeOfNULL)
                {
                    flag = true;
                    nodes[j] = nodes[i]->right;
                }
                else
                {
                    nodes[j] = nodeOfNULL;
                }
            }
            if (flag)
            {
                for (i = oldlvl - 1, j = lvl - 1; i < (lvl - 1); i++, j++)
                {
                    if (nodes[i]->left && nodes[i] != nodeOfNULL)
                    {
                        printf("%ld ", nodes[i]->left->value);
                    }
                    ++j;
                    if (nodes[i]->right && nodes[i] != nodeOfNULL)
                    {
                        printf("%ld ", nodes[i]->right->value);
                    }
                }
            }
        }
        printf("\n");
    }
    else
    {
        printf("\n");
    }
}

int main()
{
    Tree *t = (Tree *)malloc(sizeof(Tree));
    init(t);
    long int value;
    for (long int i = 0; i < 7; i++)
    {
        scanf("%ld", &value);
        insert(t, value);
    }
    bfs(t->root);
    return 0;
}

```

Таблица с результатами работы функции для обхода дерева в ширину.

***
|input | output |
|-----------------:|:-------------------:|
| 5 3 7 2 4 6 8 | 5 3 7 2 4 6 8 |
***

### Прямой обход дерева

__Прямой обход дерева__ представляет собой следующией алгоритм: посетить корневой узел, затем идем к левому поддереву и обходим его в прямой последовательности, после чего посещаем правое поддерево и обходим его в прямой последовательности

Реализация прямого обхода дерева:
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

typedef struct tree
{
    node *root;
} tree;

typedef struct node_stack
{
    node *data;
    struct node_stack *next;
} node_stack;

typedef struct stack
{
    node_stack *head;
} stack;

void init_stack(stack *s)
{
    s->head = NULL;
}

int push(stack *s, node *n)
{
    node_stack *snode = malloc(sizeof(node_stack));
    snode->data = n;
    snode->next = s->head;
    s->head = snode;
    return 0;
}

node *pop(stack *s)
{
    node_stack *snode = s->head;
    node *n = s->head->data;
    s->head = s->head->next;
    free(snode);
    return n;
}

void clear_stack(stack *s)
{
    node_stack *tmp = s->head;

    while (tmp != NULL)
    {
        node_stack *p = tmp->next;
        free(tmp);
        tmp = p;
    }
    s->head = NULL;
}

void init(tree *t)
{
    t->root = NULL;
}

node *clear_impl(node *n)
{
    if (n != NULL)
    {
        clear_impl(n->left);
        clear_impl(n->right);
        n = NULL;
        return n;
    }

    return NULL;
}

void clear(tree *t)
{
    clear_impl(t->root);
}

int insert(tree *t, int value)
{
    node *tmp = malloc(sizeof(node));
    tmp->value = value;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;

    node *curr = t->root;
    node *prev = NULL;

    if (t->root == NULL)
    {
        t->root = tmp;
    }
    else
    {
        while (curr != NULL)
        {
            prev = curr;
            if (value < curr->value)
            {
                curr = curr->left;
            }
            else if (value > curr->value)
            {
                curr = curr->right;
            }
            else if (value == curr->value)
            {
                return 1;
            }
        }
        tmp->parent = prev;

        if (value < prev->value)
        {
            prev->left = tmp;
        }
        else if (value > prev->value)
        {
            prev->right = tmp;
        }
    }
    return 0;
}

void iterPreorder(node *n)
{
    if (n == NULL)
    {
        return;
    }
    stack *s = malloc(sizeof(stack));
    init_stack(s);
    push(s, n);

    while (s->head != NULL)
    {
        n = pop(s);
        printf("%d", n->value);

        if (n->right != NULL)
        {
            push(s, n->right);
        }

        if (n->left != NULL)
        {
            push(s, n->left);
        }
        if (s->head != NULL)
        {
            printf(" ");
        }
    }
    printf("%c", '\n');
    clear_stack(s);
}

int main()
{
    tree *t = malloc(sizeof(tree));
    init(t);
    int n = 7;
    int a;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a);
        insert(t, a);
    }
    iterPreorder(t->root);
    clear(t);

    return 0;
}

```
Таблица с результатами работы функции для прямого обхода дерева.

***
|input | output |
|-----------------:|:-------------------:|
| 5 3 7 2 4 6 8 | 5 3 2 4 7 6 8 |
***

### Обратный обход дерева

__Обратный обход дерева__: сначала следует обойти левое поддерево обратным ходом, затем обойти правое поддерево обратным ходом, после чего обойти корневой узел.

Реализация функции обратного обхода дерева:
```c
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

    Node *nodeOfNULL = (Node *)malloc(sizeof(Node));

    if (rootNode && nodeOfNULL)
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
                if (Nodes[i]->left && Nodes[i] != nodeOfNULL)
                {
                    flag = true;
                    Nodes[j] = Nodes[i]->left;
                }
                else
                {
                    Nodes[j] = nodeOfNULL;
                }
                j += 1;
                if (Nodes[i]->right && Nodes[i] != nodeOfNULL)
                {
                    flag = true;
                    Nodes[j] = Nodes[i]->right;
                }
                else
                {
                    Nodes[j] = nodeOfNULL;
                }
            }
            if (flag)
            {
                for (i = oldlvl - 1; i < (lvl - 1); i++)
                {
                    if (Nodes[i]->left && Nodes[i] != nodeOfNULL)
                    {
                        printf("%ld ", Nodes[i]->left->value);
                    }
                    else
                    {
                        printf("_ ");
                    }
                    ++j;
                    if (Nodes[i]->right && Nodes[i] != nodeOfNULL)
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

void postOrder(Node *n)
{
    Node *tempNode;
    tempNode = (Node *)malloc(sizeof(Node));
    tempNode = n;

    if (tempNode)
    {
        postOrder(tempNode->left);
        postOrder(tempNode->right);
        if (tempNode)
        {
            printf("%ld ", tempNode->value);
        }
    }
    else
    {
        return;
    }
}

int main()
{
    Tree *t = (Tree *)malloc(sizeof(Tree));
    init(t);
    long int value;
    for (long int i = 0; i < 7; i++)
    {
        scanf("%ld", &value);
        insert(t, value);
    }
    postOrder(t->root);
    return 0;
}

```
Таблица с результатами работы функции для обратного обхода дерева.

***
|input | output |
|-----------------:|:-------------------:|
| 5 3 7 2 4 6 8 | 2 4 3 6 8 7 5 |
***

Написанные программы успешно проходят pipeline.

[![](https://gitlab.com/Korobejnikova/practices/-/raw/master/pr6/pr6.png)](https://gitlab.com/Korobejnikova/practices/-/blob/master/pr6/pr6.png)

## Заключение

Были получены навыки работы с обходом бинарных деревьев в C.
Был составлен отчёт с помощью языка разметки Markdown.
