#include "NodeStruct.hpp"

#ifndef Stack_H
#define Stack_H
class Stack
{
  private:
      token* tokenStack [50];
      int top;

  public:
      Stack(int);
      // ~Stack();

      void push(token*);
      token* pop();
      token* peek();
      int getHeight();
      // void display();
};

Stack::Stack(int stackSize)
{
    top=-1;
    // tokenStack = (tokenStack)Calloc( [1+stackSize], sizeof(token *);
}

// Stack::~Stack()
// {
//   token
// }

// Stack::~Stack()
// {
//     if(p!=0)
//         delete [] p;
// }
int Stack::getHeight()
{
    return top;
}

void Stack::push(token *t)
{
  top++;
  tokenStack[top]=t;
}

token* Stack::pop()
{
    if(top==-1)
      return 0;
    return tokenStack[top--];
}

token* Stack::peek()
{
  if(top==-1)
    return 0;
  return tokenStack[top];
}

#endif
