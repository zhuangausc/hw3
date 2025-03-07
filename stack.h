#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack() : std::vector<T>(){};
    ~Stack(){};
    bool empty() const{
      return std::vector<T>::empty();
    }
    size_t size() const{
      return std::vector<T>::size();
    }
    void push(const T& item){
      this->push_back(item);
    }
    void pop(){
      // throws std::underflow_error if empty
      if(this->empty()){
        throw std::underflow_error("Called pop on empty stack");
      } else {
        this->pop_back();
      }
    }
    const T& top() const{
      // throws std::underflow_error if empty
      if(this->empty()){
        throw std::underflow_error("Called top on empty stack");
      } else {
        return this->back();
      }
    }
    // Add other members only if necessary
};

#endif