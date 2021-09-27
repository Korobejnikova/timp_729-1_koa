#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list {
	struct node *head;  // начало списка
} list;

typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;


// инициализация пустого списка
void init(list *l){
  list *tempList = (list*)malloc(sizeof(list));
  tempList->head = NULL;

  *l = *tempList ;
}

// удалить все элементы из списка
void clean(list *l){
  node *temp = l->head;
  while(temp != NULL){
    node *tempNode = temp;
    temp = temp->next;
    free(tempNode);
  }
  
  l->head = NULL;
}

// проверка на пустоту списка
bool is_empty(list *l){
  if(l->head == NULL)
  {
    return true;
  }
  else{
    return false;
  }
}

// поиск элемента по значению. вернуть NULL если эжемент не найден
node *find(list *l, int value){
  node *tempNode = l -> head;
  while(tempNode){
    if(tempNode->value == value){
      return tempNode;
    }
     else tempNode = tempNode->next;
  }
  return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value){
    node *temp = l->head;
    if(l->head == NULL){
      node *tempNode = (node*)malloc(sizeof(node));
      tempNode->value = value;
      tempNode->next = NULL;
      temp = tempNode;
      l->head = temp;
    }
  else{
    while(temp->next != NULL){
      temp = temp->next;
    }
    node *tempNode = (node*)malloc(sizeof(node));
    tempNode->value = value;
    tempNode->next = NULL;
    temp->next = tempNode;
  }
  
    return 0;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value){
      node *temp = l->head;
      node *tempNode = (node*)malloc(sizeof(node));
      if(tempNode == NULL)
         return 1;
      tempNode->value = value;
      tempNode->next = temp;
      temp = tempNode;
      l->head = temp;
  
    return 0;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, int pos, int value){
  int i = 1;  
  node *tempNode = l->head;

    while(i < pos && tempNode->next){
        tempNode = tempNode->next;
        i++;
    }
    node *tmp = (node*) malloc(sizeof(node));
    tmp->value = value;
    // если это не последний элемент, то next перекидываем на следующий узел
    if(tempNode->next){
        tmp->next = tempNode->next;
    }
    else{
        tmp->next = NULL;
    }
    tempNode->next = tmp;

    return 0;
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(list *l, int value){
  node *tempNode = l->head;
  node *prevNode = (node*)malloc(sizeof(node));
  if(tempNode->value == value){
    tempNode = tempNode->next;
    l->head = tempNode;
    return 0;
  }
  
  while(tempNode->next){
    prevNode = tempNode;
    tempNode = tempNode->next;
    if(tempNode->value == value){
       prevNode->next=tempNode->next;
       tempNode = prevNode;
       return 0;
    }
  }
  
  return 0;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l){
  node *tempNode = l->head;
  while(tempNode !=NULL){
    printf("%d ", tempNode->value);
    tempNode = tempNode->next;
  }
  printf("\n");
}

int main(){
  list *lst;
  init(lst);
  int num, i, a, k1, k2, k3, m, t, j, x, z;
  scanf("%d", &num);
  for(i = 0; i < num; i++){
    scanf("%d", &a);
    push_back(lst, a);
  }
  print(lst);
  scanf("%d", &k1);
  if(find(lst, k1) != NULL){
    printf("1 ");
  }
  else{
    printf("0 ");
  }
  scanf("%d", &k2);
  if(find(lst, k2) != NULL){
    printf("1 ");
  }
  else{
    printf("0 ");
  }
  scanf("%d", &k3);
  if(find(lst, k3) != NULL){
    printf("1\n");
  }
  else{
    printf("0\n");
  }
  scanf("%d", &m);
  push_back(lst, m);
  print(lst);
  scanf("%d", &t);
  push_front(lst, t);
  print(lst);
  scanf("%d %d", &j, &x);
  insert_after(lst, j, x);
  print(lst);
  scanf("%d", &z);
  remove_node(lst, z);
  print(lst);
  clean(lst);
  return 0;
}
