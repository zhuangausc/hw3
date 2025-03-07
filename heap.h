#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <iostream>
//Use vector
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int ary;
  PComparator comp;
  void swap(int idx1, int idx2) {
    T temp = data[idx1];
    data[idx1] = data[idx2];
    data[idx2] = temp;
  }
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : ary(m), comp(c) {}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() {}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
  return data.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
  return data.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
  // Add item at back of heap
  data.push_back(item);

  // While the heap invariant is not satisfied, continue swapping
  int currentIdx = size()-1;
  while(true){
    // If parent exists
    bool parentExists = true;
    // Parent index
    int parent = (currentIdx-1)/ary;
    // If parent does not exist, or current node is root
    if(parent<0 || currentIdx==0){
      // Parent does not exist
      parentExists = false;
    }
    // If this is the root OR heap invariant is satisfied
    if(!parentExists || comp(data[parent], data[currentIdx])) {
      break;
    }
    // Otherwise, swap this node with parent
    swap(currentIdx, parent);
    // Update currentIdx
    currentIdx = parent;
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Called top on empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Called pop on empty heap");
  }

  // Swap first (best) node and last node
  swap(0, size()-1);

  // Delete last node (the best node)
  data.pop_back();

  // While the heap invariant is not satisfied, continue swapping
  int currentIdx = 0;
  while(true){
    // Find the best node out of the children
    bool childExists = true;
    // Best index
    int best = (ary*currentIdx)+1;
    // If first child exists
    if(best<size()){
      for(int i=2; i<=ary; i++){
      int nextChild = (ary*currentIdx)+i;
      // If this child exists
        if(nextChild<size()){
          // If data[nextChild] is better than data[best]
          if(comp(data[nextChild], data[best])){
            // Change best to nextChild
            best = nextChild;
          }
        } else {
          //If this child does not exists
          break;
        }
      }
    } else {
      // First child does not exists
      childExists = false;
    }
    // If there are no more children OR heap invariant is satisfied
    if(!childExists || comp(data[currentIdx], data[best])) {
      break;
    }
    // Otherwise, swap this node with best child
    swap(currentIdx, best);
    // Update currentIdx
    currentIdx = best;
  }
  /*
  while(!PComparator(data[currentIdx], data[????])){
    // Find the best node out of the children
    int best = (2*currentIdx)+1;
    for(int i=2; i<=ary; i++){
      int nextChild = (2*currentIdx)+i;
      // If data[nextChild] is better than data[best]
      if(PComparator(data[nextChild], data[best])){
        // Change best to nextChild
        best = nextChild;
      }
    }
    swap(data[currentIdx], data[best]);
    // Update currentIdx
    currentIdx = best;
  }*/
}



#endif
