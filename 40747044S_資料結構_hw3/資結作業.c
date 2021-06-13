#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define MAX 20 

int check(char* my_input );
void inTopost(char* in, char* post);
int in_stack_prior(char a);
int in_coming_prior(char a);
int push(char* my_stack,char* my_in,int num_in,int num_top);
int pop(char* my_stack,char* my_post,int num_post,int num_top);

double calculate(char* post);
int cal_push(double* my_stack , char* my_post ,int i_num , int cal_top);
int cal_pop(double* my_stack , char* token , int i_num , int cal_top);

int main ()
{
	char infix[60];
	char postfix[60]={'0'};
	char input_ch;
	int m = 0 , n = 0 ;
	
	while( 1 )
	{
		for(m = 0;m < 60;m++)
		{
			infix[m] = '\0';
			postfix[m] = '\0';
		}
		printf("Please enter an infix expression and press enter:\n");
		fgets(infix , 30 , stdin);
		
		infix[strlen(infix)-1] = '\0'; 
		if( strlen(infix) > 20 )
		{
			printf("Error - line contains more characters than allowed.\n");
		}
		
		if(check(infix) == 0)
		{
			continue;
		}
		inTopost(infix,postfix);
		postfix[strlen(postfix)] = '\0';
		printf("The postfix expression:\n");
		printf("%s\n",postfix);
		printf("=\n");
		printf("%lf\n",calculate(postfix));
	}
	return 0;
} 

void inTopost(char* in, char* post)
{
	char stack[MAX] = {0};
	int i = 0 , j = 0 , top = -1 ;			
	for(i = 0;in[i] != '\0';i++)
	{
		switch(in[i])
		{
			case '(':
				stack[++top] = in[i];
				break;
			case '+':
			case '-':
			case '*':	
			case '/':
				if(top == -1)
				{
					top = push(stack,in,i,top); 
					break;
				}
				while(in_stack_prior(stack[top]) >= in_coming_prior(in[i]))
				{
					top = pop(stack,post,j++,top);
					post[j++] = ' ';
				}
				
				top = push(stack,in,i,top);
				break;
			case ')':
				while(stack[top] != '(')
				{
					top = pop(stack,post,j++,top);
					post[j++] = ' ';
				}
				top--;
				break;
			default:
				if( '0'<= in[i-1] && post[i-1] <= '9')
				{
					j--;
					post[j++] = in[i];
					post[j++] = ' ';
					break;
				}
				post[j++] = in[i];
				post[j++] = ' ';
		}
	}

	while(top >= 0)
	{
		top = pop(stack,post,j++,top);
	}
}
int in_stack_prior(char a)
{
	if( a == '-' || a == '+'){ return 1 ; }
	else if(a == '*' || a == '/'){ return 2 ; }
	else{ return 0 ; }
}
int in_coming_prior(char a)
{
	if( a == '-' || a == '+'){ return 1 ; }
	else if(a == '*' || a == '/'){ return 2 ; }
	else {return 4;}
}
int push(char* my_stack,char* my_in,int num_in,int num_top)
{
	num_top++;
	my_stack[num_top] = my_in[num_in];
	return num_top;
}
int pop(char* my_stack,char* my_post,int num_post,int num_top)
{
	if(num_top == -1){ return -1; }
	my_post[num_post] = my_stack[num_top];
	num_top--;
	return num_top;
}
double calculate(char* post)
{
	double num_stack[MAX] = {0};
	int i = 0 , top = -1;
	
	for(i = 0 ; post[i] != '\0' ; i++ )
	{
		switch(post[i])
		{
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
				top = cal_push( num_stack , post , i , top );
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				top = cal_pop( num_stack , post , i , top );
				break;
		}	
	}
	return num_stack[0];
}

int cal_push(double* my_stack , char* my_post , int i_num , int cal_top)
{
	char ch_temp[4] = {'\0'};
	cal_top++;
	strncpy(ch_temp,&my_post[i_num],1);
	if( '0' <= my_post[i_num-1] && my_post[i_num-1] <= '9')
	{
		my_stack[cal_top-1] = my_stack[cal_top-1]*10 + atof(ch_temp);
		cal_top--;
	}	
	else
	{
		my_stack[cal_top] = atof(ch_temp);		
	}
	return cal_top;
}

int cal_pop(double* my_stack , char* token , int i_num ,int cal_top)
{
	if(token[i_num] == '+'){ my_stack[cal_top-1] = my_stack[cal_top-1] + my_stack[cal_top]; }	
	if(token[i_num] == '-'){ my_stack[cal_top-1] = my_stack[cal_top-1] - my_stack[cal_top]; }	
	if(token[i_num] == '*'){ my_stack[cal_top-1] = my_stack[cal_top-1] * my_stack[cal_top]; }	
	if(token[i_num] == '/'){ my_stack[cal_top-1] = my_stack[cal_top-1] / my_stack[cal_top]; }	
	
	cal_top--;
	return cal_top;
}
 
int check(char* my_input )
{
	int i =  0 , l_parenthe = 0 , r_parenthe = 0;
	
	for( i = 0 ; my_input[i] != '\0' ; i++ )
	{
		switch(my_input[i])
		{
			case '(':
				l_parenthe ++;
				if(((my_input[i+1] == '+' || my_input[i+1] == '-') || my_input[i+1] == '*') || my_input[i+1] == '/')
				{
					printf("Left parenthesis followed by an operator");
					return 0;
				}
			case ')':
				r_parenthe ++;
				
		}
	}
}
 
 
 
 
