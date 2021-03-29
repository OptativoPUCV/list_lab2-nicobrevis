#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
      List * L = (List *)malloc(sizeof(List));
      L -> head = NULL;
      L -> tail = NULL;
      L -> current = NULL;


     return L;
}

void * firstList(List * list) {
  if(list->head == NULL) return NULL; 

  list->current = list->head;

  return (void*)list->current->data;
}

void * nextList(List * list) {
  if(list->current == NULL || list->current->next == NULL) return NULL;
    
  list->current = list->current->next;

  return (void*)list->current->data;
}

void * lastList(List * list) {

  if(list->tail == NULL) return NULL; 

  list->current = list->tail;

    return (void*)list->tail->data;
}

void * prevList(List * list) {

  if(list->current == NULL || list->current->prev == NULL) return NULL;
    
  list->current = list->current->prev;

  return (void*)list->current->data;
}

void pushFront(List * list, const void * data) {
  Node* n = createNode(data);
  n->next = list->head;
  if(list->head == NULL){
  
    list->tail = n;

  }
  if(list->head){

    list->head->prev = n;

  }
  list->head = n;
  n->prev = NULL;
   
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  Node* n =createNode(data);

  if(list->current == list->tail){
    list->tail = n;
    n->prev = list->current;
    list->current->next = list->tail;
    n->next = NULL;
  }else{
    list->current->next = n;
    n->prev = list->current;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node * aux = list->current; 
  if(list->head && list->tail){
    
    if(list->current == list->head){ // aca tambien hubieras dicho current == head-antes lo tenía así pero da lo mismo o no? sipii
      
      list->head = aux->next;
      aux->next->prev = NULL;
      list->current = list->head; // asi? sisi ya esta lista esta primera parte
   
    }
    if(list->current->prev != NULL && list->current->next !=NULL){ //creo que acá es donde me tira el error

      aux->prev = aux->next; //aca haces eso 
      aux->next = aux->prev; //entonces depués de eso tengo que decir que el current->prev apunte al current->next? alreves pq eso lo tienes, el current next tiene que apuntar al prev
    
    }

    if(list->current == list->tail){
     list->tail = list->current->prev;
     list->tail->prev->next = NULL;
     list->current =NULL;
    }

  }

  return (void*) aux->data; 
    
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}