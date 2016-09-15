
#include "NodeStruct.hpp"
#include "Stack.hpp"

token* StackEvaluator(Stack* s);
void StackDropper(token* t, Stack* s);

void StackDropper(token* t, Stack* s)
{
  // std::cout << "Left" << std::endl;
  if(t->opLeft != 0) StackDropper(t->opLeft, s);
  // std::cout << "Right" << std::endl;
  if(t->opRight != 0) StackDropper(t->opRight, s);
  // std::cout << "Pushing: " << t->type << " " << t->data << std::endl;
  // std::cout << "Height: " << s->getHeight() << std::endl;
  s->push(t);
  // std::cout << "Height: " << s->getHeight() << std::endl;
}

int CharEvaluator(char* charpointer, int length)
{
  char a[length];
  for(int i=0; i <length; i++)
      a[i] = *(charpointer+i);
  char *b = charpointer;
  token* t = TreeDropper(b, sizeof(a));
  Stack* s = new Stack(sizeof(a));
  // std::cout << "Tree Dropped" << std::endl;
  StackDropper(t, s);
  // std::cout << "Stack Filled" << std::endl;
  // std::cout << "Top of stack pointer is: " << (s->peek() !=0) << std::endl;
  // tokenReader(t);
  t = StackEvaluator(s);
  // std::cout << "Stack Evaluated" << std::endl;
  free(s->pop());
  free(s);
  // tokenReader(t);
  return t->data;
}

token* StackEvaluator(Stack* s)
{
  token *operand2, *operand1, *operation;
  token *result;
  if(IsIntToken(s->peek()))
  {
    // std::cout << "Returning int token " << s->peek()->data << std::endl;
    return s->pop();
  }
  else//if(IsOPToken(s->peek()))
  {
    result = (token*) calloc(1, sizeof(struct token));
    // std::cout << "Popping Stack: "<< s->peek()->data  << std::endl;
    operation = s->pop();
    operand2 = StackEvaluator(s);
    if(IsVoidToken(operand2))
      return operand2;
    operand1 = StackEvaluator(s);
    if(IsVoidToken(operand1))
      return operand1;
    switch (OPFromCode(operation->data))
    {
      case '+': *result =(makeIntToken(operand1->data + operand2->data));
      break;
      case '-': *result =(makeIntToken(operand1->data - operand2->data));
      break;
      case '/': *result =(makeIntToken(operand1->data / operand2->data));
      break;
      case '*': *result =(makeIntToken(operand1->data * operand2->data));
      break;
    }
    // std::cout << "Making new int token, operation:"<< std::endl
    // << operand1->data << OPFromCode(operation->data) << operand2->data<<" = " << result->data << std::endl;
    free(operand2);
    free(operand1);
    free(operation);
    // std::cout << "Int token returned." << std::endl;
    return result;
  }
}
