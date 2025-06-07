#ifndef STACK_H
#define STACK_H
#include "linked.h"

typedef address Stack;

void SetTop (Stack *S, Stack NewTop );
void CreateEmpty (Stack *S);
boolean IsEmpty (Stack S);
void Push (Stack *S, infotype X);
void Pop (Stack *S, infotype *X);
#endif

