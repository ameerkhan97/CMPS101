//-----------------------------------------------------------------------------
//  List.c
//  Ameer Khan
//  ammukhan
//  CS101 PA4
//  Implementation file for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj {
   Node front;
   Node back;
   Node locator;
   int length;
   int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L) {
	if (L == NULL) {
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
    }
   	return (L->length == 0);
}

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data) {
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN) {
   if (pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void) {
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->locator = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
	if(pL !=NULL && *pL !=NULL) {
		while(!isEmpty(*pL)) {
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access Functions --------------------------------------------------------

// length()
// Returns the number of elements in this List.
int length(List L){
	if (L == NULL) {
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
    }
    return (L->length);
}

// index()
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L) {
   	if (L == NULL) {
		  printf("List Error: calling index() on NULL List reference\n");
		  exit(1);
	}
	return (L->index);
}

// front()
// Returns front element.
// Pre: length() > 0
int front(List L) {
   if (L == NULL) {
     printf("List Error: calling front() on NULL List reference\n");
     exit(1);
   }
   if (isEmpty(L)) {
     printf("List Error: calling front() on an empty List\n");
     exit(1);
   }
   return (L->front->data);
}

// back()
// Returns back element.
// Pre: length() > 0
int back(List L) {
   if (L == NULL) {
     printf("List Error: calling back() on NULL List reference\n");
     exit(1);
   }
   if (isEmpty(L)) {
     printf("List Error: calling back() on an empty List\n");
     exit(1);
   }
   return (L->back->data);
}


// get()
// Returns cursor element.
// Pre: length() > 0, index() >= 0
int get(List L) {
   if (L == NULL) {
     printf("List Error: calling get() on NULL List reference\n");
     exit(1);
   }
   if (isEmpty(L)) {
     printf("List Error: calling get() on an empty List\n");
     exit(1);
   }
   return (L->locator->data);
}


// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B) {
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if (A == NULL || B == NULL) {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;

   while (eq && N != NULL) {
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets this List to its original empty state.
void clear(List L) {
   L->front = L->back = L->locator = NULL;
   L->length = 0;
   L->index = -1;
}

// moveFront()
// If List is non-empty, places the cursor under the front element, otherwise does nothing.
void moveFront(List L) {
	if (L->length > 0) {
		L->locator = L->front;
		L->index = 0;
	}
}

// moveBack()
// If List is non-empty, places the cursor under the back element, otherwise does nothing.
void moveBack(List L) {
	if (L->length > 0) {
		L->locator =  L->back;
		L->index = (L->length - 1);
	}
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward front of this List.
// If cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
void movePrev(List L) {
	if (L->locator != NULL && L->index != 0) {
		L->locator = L->locator->prev;
		L->index--;
	} else if (L->locator != NULL && L->index == 0) {
		L->locator = NULL;
		L->index = -1;
	}
}

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward back of this List.
// If cursor is defined and at back, cursor becomes undefined, if cursor is undefined does nothing.
void moveNext(List L) {
	if (L->locator != NULL && L->index != (L->length - 1)) {
		L->locator = L->locator->next;
		L->index++;
	} else if (L->locator != NULL && L->index == (L->length - 1)) {
		L->locator = NULL;
		L->index = -1;
	}
}

// prepend()
// Insert new element into this List.  
// If List is non-empty, insertion takes place before front element.
void prepend(List L, int data) {
	Node temp = newNode(data);
	if (L->length == 0) {
		L->front = L->back = temp;
	} else {
		temp->next = L->front;
		L->front->prev = temp;
		L->front = temp;
		L->index++;
	}
	L->length++;
}

// append()
// Insert new element into this List.  
// If List is non-empty, insertion takes place after back element.
void append(List L, int data) {
	Node temp = newNode(data);
	if (L->length == 0) {
		L->front = L->back = temp;
	} else { 
		L->back->next = temp;
		temp->prev = L->back;
		L->back = temp;
	}
	L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	} else if (isEmpty(L) || L->index < 0) {
		printf("List Error: calling insertBefore() on empty list\n");
		exit(1);
	} else {
		if (L->index == 0) {
			prepend(L, data);
		} else {
			Node N = newNode(data);
			Node temp = L->locator->prev;
			N->prev = temp;
			N->next = L->locator;
			temp->next = N;
			L->locator->prev = N;
			L->length++;
			L->index++;
		}
	}
}

// insertAfter()
// Insert new element after cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
	} else if (isEmpty(L) || L->index < 0) {
		printf("List Error: calling insertAfter() on empty list\n");
		exit(1);
	} else {
		if (L->index == (L->length - 1)) {
			append(L, data);
		} else {
			Node N = newNode(data);
			Node temp = L->locator->next;
			N->next = temp;
			N->prev = L->locator;
			temp->prev = N;
			L->locator->next = N;
			L->length++;
		}
	}
}

// deleteFront()
// Deletes the front element.
// Pre: length() > 0
void deleteFront(List L) {
   if (L == NULL) {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if (isEmpty(L)) {
      printf("List Error: calling deleteFront on an empty List\n");
      exit(1);
   }

   Node N = NULL;
   N = L->front;

   if (L->length > 1) { 
      L->front = L->front->next; 
   } else { 
      L->front = L->back = NULL; 
   }
   L->length--;
   freeNode(&N);
}

// deleteBack()
// Deletes the back element.
// Pre: length() > 0
void deleteBack(List L) {
   if (L == NULL) {
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if (isEmpty(L)) {
      printf("List Error: calling deleteBack on an empty List\n");
      exit(1);
   }

   Node N = NULL;
   N = L->back;

   if (L->length > 1) { 
      L->back = L->back->prev; 
   } else { 
      L->front = L->back = NULL; 
   }
   L->length--;
   freeNode(&N);
}

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L) {
	if (L == NULL) {
		printf("List Error: calling delete() on NULL List reference\n");
      	exit(1);
    }
	if (isEmpty(L) || L->index < 0) {
		printf("List Error: calling delete on an empty List\n");
      	exit(1);
	} 
	
	Node N = NULL;
    N = L->locator;
    
    if (N == L->front) {
		deleteFront(L);
    } else if (N == L->back) {
      	deleteBack(L);
    } else {
      	L->locator->prev->next = L->locator->next;
      	L->locator->prev = L->locator->next = NULL;
      	freeNode(&N);
      	L->locator = NULL;
      	L->index = -1;
      	L->length--;
	}
}

// Other methods ---------------------------------------------------------

// printList()
// prints out desired result
void printList(FILE* out, List L) {
   Node N = NULL;

   if (L == NULL) {
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }

   for(N = L->front; N != NULL; N = N->next) {
      fprintf(out, "%d ", N->data);
   }
}

// copy()
// Returns a new List representing the same integer sequence as this List.  
// The cursor in the new list is undefined, regardless of the state of the cursor in this List. 
// This List is unchanged.
List copyList(List L) {
	if (L == NULL) {
	  printf("List Error: calling copyList() on NULL List reference\n");
      exit(1);
	}

   	List lst = newList();
    Node N = L->front;

    while (N != NULL){
        append(lst, N->data);
        N = N->next;
    }
    return lst;
}

