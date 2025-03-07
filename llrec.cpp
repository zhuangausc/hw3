#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot){
  // Recursive function
  // Handle case where in first recursive call, head is nullptr
  Node* temp = head;
  if(head==nullptr){
    smaller=nullptr;
    larger=nullptr;
    return;
  }
  Node* nextNode = head->next;
  if(head->val<=pivot) {
    smaller = temp;
    llpivot(nextNode, smaller->next, larger, pivot);
  } else {
    larger = temp;
    llpivot(nextNode, smaller, larger->next, pivot);
  }
  //Make sure head is nullptr
  head = nullptr;
}