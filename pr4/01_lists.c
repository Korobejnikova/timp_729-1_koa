#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
int value; 
struct node* next; 
struct node* prev; 
} node; 

typedef struct list {
struct node* head; 
struct node* tail; 
} list; 

void init(list* l)
{
list* tmp = (list*)malloc(sizeof(list));
tmp->head = tmp->tail = NULL;
*l = *tmp;
}

void clean(list* l)
{
node* tempNode = l->head;
node* removeNode = (node*)malloc(sizeof(node)); 
while (tempNode) 
{
removeNode = tempNode;
tempNode = tempNode->next;
free(removeNode);
}
l->head = NULL;
l->tail = NULL;
}

bool is_empty(list* l)
{
if (l->head == NULL)
return 1;
else return 0;
}

node* find(list* l, int value)
{
node* tempNode = l->head;
while (tempNode)
{
if (tempNode->value == value)
{
return tempNode;
}
tempNode = tempNode->next;
}
return NULL;
}

int push_back(list* l, int value)
{
node* tempNode = (node*)malloc(sizeof(node)); 
if (tempNode == NULL)
{
return 0;
}
tempNode->value = value;
tempNode->next = NULL;
tempNode->prev = l->tail;
if (l->tail) 
{
l->tail->next = tempNode; 
}
l->tail = tempNode; 

if (l->head == NULL) 
{
l->head = tempNode; 
}
return 0;
}

int push_front(list* l, int value)
{
node* tempNode = (node*)malloc(sizeof(node)); 
tempNode->value = value; 
if (l->head == NULL) 
{
l->head = tempNode;
l->tail = tempNode;
}
else
{
tempNode->next = l->head;
tempNode->next->prev = tempNode;
l->head = tempNode;
}
if (tempNode)
{
return 0;
}
}

int insert_after(list* l, node* n, int value) {
node* tempNode = (node*)malloc(sizeof(node)); 
if (n->next == NULL) 
{
tempNode->prev = n;
n->next = tempNode;
l->tail = tempNode;
tempNode->value = value;
return 0;
}
tempNode->value = value;
tempNode->prev = n;
tempNode->next = n->next;
n->next->prev = tempNode;
n->next = tempNode;
return 0;
}

int insert_before(list* l, node* n, int value)
{
node* tempNode = (node*)malloc(sizeof(node)); 
if (n->prev == NULL) 
{
tempNode->next = n;
n->prev = tempNode;
l->head = tempNode;
tempNode->value = value;
return 0;
}
tempNode->value = value;
tempNode->prev = n->prev;
n->prev->next = tempNode;
tempNode->next = n;
n->prev = tempNode;
return 0;
}

int remove_node(list* l, int value)
{
node* tempNode = l->head;
while (tempNode != NULL) { 
if (tempNode->value == value) { 
if (tempNode->prev) { 
tempNode->prev->next = tempNode->next; 
}
if (tempNode->next) { 
tempNode->next->prev = tempNode->prev; 
}
if (!tempNode->prev) { 
l->head = tempNode->next;
}
if (!tempNode->next) { 
l->tail = tempNode->prev;
}
free(tempNode);
return 0;
}
else {
tempNode = tempNode->next;
}
}
return 1;
}

node* findlast(list* l, int value) {
node* tempNode = l->tail;
if (!l->head) {
return NULL;
}
while (tempNode) {
if (tempNode->value == value)
return tempNode;
tempNode = tempNode->prev;
}
return NULL;
}

int remove_last(list* l, int value) {
if (l->head == NULL) {
return 1;
}
node* tempNode = findlast(l, value);
if (tempNode != NULL) {
node* prevNode = tempNode->prev;
node* nextNode = tempNode->next;
if (prevNode != NULL) {
prevNode->next = nextNode;
}
if (nextNode != NULL) {
nextNode->prev = prevNode;
}
if (tempNode == l->head) {
l->head = tempNode->next;
}
if (tempNode == l->tail) {
l->tail = tempNode->prev;
}
free(tempNode);
}
return 0;
}

void print(list* l)
{
node* tempNode = l->head;
if (tempNode == NULL) {
return;
}
while (tempNode != NULL) {
printf("%d ", tempNode->value);
tempNode = tempNode->next;
}
printf("\n");
}

void print_invers(list* l)
{
node* tempNode = l->tail;
if (tempNode == NULL) {
return;
}
while (tempNode != NULL) {
printf("%d ", tempNode->value);
tempNode = tempNode->prev;
}
printf("\n");
}

int main() {
list* l; 
init(l); 
int n, values, i;
scanf("%d", &n); 
for (int i = 0; i < n; i++) 
{
scanf("%d", &values);
push_back(l, values);
}
print(l);
for (int i = 0; i < 3; i++)
{
scanf("%d", &values);
if (find(l, values) == NULL)
{
printf("%d ", 0);
}
else
{
printf("%d ", 1);
}

}
printf("\n");
scanf("%d", &values);
push_back(l, values);
print_invers(l);
scanf("%d", &values);
push_front(l, values);
print(l);
int j, x;
scanf("%d", &j);
scanf("%d", &x);
node* temp = l->head;
for (i = 1; i < j; i++)
{
temp = temp->next;
}
insert_after(l, temp, x);
print_invers(l);
int u, y;
scanf("%d", &u);
scanf("%d", &y);
temp = l->head;
for (i = 1; i < u; i++)
{
temp = temp->next;
}
insert_before(l, temp, y);
print(l);
scanf("%d", &values);
remove_node(l, values);
print_invers(l);
scanf("%d", &values);
remove_last(l, values);
print(l);
clean(l);
return 0;
}
