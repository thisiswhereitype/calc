#include "Atoi.h"
// #include <iostream>

#ifndef token_H
#define token_H
//Structs
struct token {
  char type;
  int data;
  token* opLeft;
  token* opRight;
};

//Prototypes - Discontinued
token makeIntToken(char* value);
token makeIntToken(int value);
token makeOPToken(char operation);
token makeVoidToken();
int CountNodes(token*);
int GetPrecedenceLevel(char Check);
int GetOPCode(char op);
char OPFromCode(int code);

token makeIntToken(char* value)
{
  token t;
  t.data = myAtoi(value);
  t.type = 'i';
  t.opLeft = 0;
  t.opRight = 0;
  return t;
}

token makeIntToken(int value)
{
  token t;
  t.data = (value);
  t.type = 'i';
  t.opLeft = 0;
  t.opRight = 0;
  return t;

}

token makeOPToken(char operation)
{
  token t;
  t.data = GetOPCode(operation);
  t.type = 'o';
  t.opLeft = 0;
  t.opRight = 0;
  return t;
}

token makeVoidToken()
{
  token t;
  t.data = 'v';
  t.type = 'v';
  t.opLeft = 0;
  t.opRight = 0;
  return t;
}

int myMax(int a, int b)
{
  if(a >= b)
    return a;
  else return b;
}
int GetOPCode(char op)
{
  switch (op) {
    case '+': return 1;
    case '-': return 2;
    case '/': return 3;
    case '*': return 4;
    default : return 0;
  }
}

char OPFromCode(int code)
{
  switch (code) {
    case 1: return '+';
    case 2: return '-';
    case 3: return '/';
    case 4: return '*';
    default : return 'v';
  }
}

int GetPrecedenceLevel(char Check)
{
  switch(Check)
  {
    default:
      return 0;
    case '0':
		case '1':
		case '2':
		case '3':
    case '4':
    case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		//case '.':
      return 1;
    case '+':
    case '-':
      return 3;
    case '*':
    case '/':
      return 2;
    case '(':
    case ')':
      return 4;
  }
}

int CountNodes(token* node)
{
  // std::cout << "1" << std::endl;
  int i=1;
  if(node->opLeft != 0)
  {
    // std::cout << "1 if" << std::endl;
    i += CountNodes(node->opLeft);
  }
  if(node->opRight != 0)
  {
    // std::cout << "2 if" << std::endl;
    i += CountNodes(node->opRight);
  }
  return i;
}

int GetFirstMaxValue(char* a, int length)
{
  int MaxValue =0;
  // std::cout << "FirstChar: "<< *(a) << std::endl;
  for(int i =0; i<length; i++)
  {
    MaxValue = myMax(MaxValue, GetPrecedenceLevel(*(a+i)));
    // std::cout << "i: "<< i << std::endl;
  }
  for(int j =0; j<length; j++)
  {
    // std::cout << "j: "<< j << std::endl;
    // std::cout << "Current char: " << *(a+j)<< std::endl;
    if(MaxValue == GetPrecedenceLevel(*(a+j)))
    {
      return j;
    }
  }
  return 0;
}

token* TreeDropper(char* Insertion, int Length)
{
  token* t =(token*) calloc(1, sizeof(struct token));
  int i = GetFirstMaxValue(Insertion, Length);
  int Prec = GetPrecedenceLevel(*(Insertion + i));
  // std::cout << "Prec: " << Prec << ", i: " << i << std::endl;
  // std::cout << "First OP: " << *(Insertion +i) << std::endl;
  switch (Prec)
  {
    default:
      // std::cout << "DEFAULT CASE, Illegal char:" << *(Insertion +i) <<std::endl;
      *t = makeVoidToken();
      return t;
    case 1://Numbers
        *t = makeIntToken(Insertion+i);
        Insertion += GetFirstMaxValue(Insertion+i, Length-i-1);
        // std::cout << "Making int token" << std::endl;
        Prec =-2;
        break;
    case 2://+&-
        *t = makeOPToken(*(Insertion +i));
        Prec = -1;
        // std::cout << "Making order 2 op" << std::endl;
        break;
    case 3://*&/
        *t = makeOPToken(*(Insertion +i));
        // std::cout << "Making order 3 op" << std::endl;
        Prec = -1;
        break;
  }
  // std::cout << std::endl;
  switch (Prec)
  {
    case -2:
      break;
    case -1 :
      t->opLeft = TreeDropper(Insertion, i);
      t->opRight = TreeDropper((Insertion +i +1), Length-i-1);
      break;
  }
  return t;
}

// void tokenReader(token* t)
// {
//   if(t->opLeft != 0) tokenReader(t->opLeft);
//   // else  std::cout << "LeftPointerNull" << std::endl;
//   if(t->opRight != 0) tokenReader(t->opRight);
//   // else std::cout << "RightPointerNull" << std::endl;
//   switch (t->type)
//   {
//     case 'o':
//       std::cout << OPFromCode(t->data) << std::endl;
//       break;
//     case 'i':
//       std::cout << t->data << std::endl;
//       break;
//     default :
//       std::cout << "Default Case" << std::endl;
//       break;
//   }
// }

bool IsIntToken(token* t)
{
  if (t->type == 'i') return true;
  else return false;
}

bool IsOPToken(token* t)
{
  if (t->type == 'o') return true;
  else return false;
}

bool IsVoidToken(token* t)
{
  if (t->type == 'v') return true;
  else return false;
}


#endif
