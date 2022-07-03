#include <stdio.h>
#include<stdlib.h>
#include <ctype.h>
struct stack
{
char stk[100];
int top;
};
void push(struct stack *s, char ele)
{
s->stk[++s->top]=ele;
}
char pop(struct stack *s)
{
return s->stk[s->top--];
}

int precedence(char symb)
{
if(symb=='+' || symb=='-')
return 1;
else if(symb=='*' || symb=='/' || symb=='%')
return 2;
else if(symb=='$' || symb=='^')
return 3;
else if(symb=='(')
return 0;
else
return 5;
}
void infixToPostfix(char in[], char post[])
{
char ch, symbol;
int i, j=0;
struct stack s;
s.top=-1;
push(&s, '#');
for(i=0; in[i]!='\0'; i++)
{
symbol=in[i];
if(symbol=='(') //if opening bracket push it into stack
push(&s, symbol);
else if(isalnum(symbol)) //if alphabet / number then place it in postfix
post[j++]=symbol;
else if(symbol==')') //if closing bracket, pop all stack elts until matching '('
{
while((ch=pop(&s))!='(')
post[j++]=ch;
}
else //if operator check for precedence
 {
while(s.stk[s.top]!='#' && precedence(symbol)<=precedence(s.stk[s.top]) ) 
post[j++]=pop(&s);
push(&s, symbol);
}
}//end of scanning of infix expression
//pop all the remaining operators until stack's top is left with only '#'
while(s.stk[s.top]!='#')
post[j++]=pop(&s);
}

int evaluate_postfix(char post[])
{
int i, op1, op2, res;
char symbol;
struct stack s;
s.top=-1;
for(i=0; post[i]!='\0'; i++) //12*3+
{
symbol=post[i];
if(isdigit(symbol))
{
push(&s, symbol-'0');
}
else
{
op2=pop(&s);
op1=pop(&s);
if(symbol=='+') res=op1+op2;
else if(symbol=='-') res=op1-op2;
else if(symbol=='*') res=op1*op2; else
if(symbol=='/') res=op1/op2;
else if(symbol=='^' || symbol=='$') res=op1^op2; else
{
printf("Invalid operator\n");
exit(0);
}
push(&s, res);
}
}//for --> completed postfix scanning
return (pop(&s));
}

int main()
{
char infix[100], postfix[100];
int res;
printf("Enter a valid infix expression:\n");
gets(infix);
infixToPostfix(infix, postfix);
printf("The equivalent postfix expression is:\n%s", postfix);
res = evaluate_postfix(postfix);
printf("The evaluated val of %s is %d\n", postfix, res);
return 0;
}