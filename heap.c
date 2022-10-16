#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
  if(pq->size == 0) return NULL;
  return pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority){
  if(pq->size == pq->capac){
    pq->heapArray = (heapElem*)realloc(pq->heapArray,((pq->capac*2+1)* sizeof(heapElem)));
    pq->capac = pq->capac*2+1;
  }
  pq->heapArray[pq->size].data = data;
  pq->heapArray[pq->size].priority = priority;
  int aux = pq->size;
  while(aux != 0 && pq->heapArray[aux].priority > pq->heapArray[(aux-1)/2].priority){
    heapElem aux2 = pq->heapArray[aux];
    pq->heapArray[aux] = pq->heapArray[(aux-1)/2];
    pq->heapArray[(aux-1)/2] = aux2;
    aux = (aux-1)/2;
  }
  pq->size++;
}


void heap_pop(Heap* pq){
  if(pq->size == 0) return;
  pq->heapArray[0] = pq->heapArray[pq->size-1];
  pq->heapArray[pq->size].data = NULL;
  pq->heapArray[pq->size].priority = 0;
  pq->size--; 
  int aux = 0;
  while((2*aux+2) <= pq->capac && (pq->heapArray[2*aux+1].priority > pq->heapArray[aux].priority || pq->heapArray[2*aux+2].priority > pq->heapArray[aux].priority)){
    if(pq->heapArray[2*aux+1].priority > pq->heapArray[2*aux+2].priority){
      heapElem aux2 = pq->heapArray[aux];
      pq->heapArray[aux] = pq->heapArray[2*aux+1];
      pq->heapArray[2*aux+1] = aux2;
      aux = 2*aux+1;
    }
    else{
      heapElem aux2 = pq->heapArray[aux];
      pq->heapArray[aux] = pq->heapArray[2*aux+1];
      pq->heapArray[2*aux+1] = aux2;
      aux = 2*aux+2;
    }
  }
}

Heap* createHeap(){
  Heap *heap = (Heap*)malloc(sizeof(Heap));
  heap->heapArray = (heapElem*)calloc(3,sizeof(heapElem));
  heap->size = 0;
  heap->capac = 3;
  return heap;
}
