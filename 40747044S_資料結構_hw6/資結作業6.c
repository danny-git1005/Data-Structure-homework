#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct poker_data
{
	char color;
	int num;
	struct poker_data *pre;
	struct poker_data *next;
}Poker;

Poker *creat_node( Poker *pre_card, Poker *next_card); 
Poker *delet_node( Poker *pre_card, Poker *next_card);
void *creat_card(Poker *player , int count,int *num);
void look_from_head(Poker *card,char *color1);
void look_from_tail(Poker *card,char *color2);
Poker *look_from_S_to_B(Poker *card,char *color3);
Poker *search_num(Poker *card,char *color4, int b_num);
void print_card(Poker *card);

int main ()
{
	int input[3] = {0},i=0,a,b;
	int j,k;
	int real_number[2][52] = {0};
	int max = 0;
	
	char card_color[3];
	Poker num_card[2];
	
	num_card[0].pre = NULL;
	num_card[0].next = NULL;
	num_card[0].color = '0';
	num_card[0].num = 0;
	
	
	num_card[1].pre = NULL;
	num_card[1].next = NULL;
	num_card[1].color = '0';
	num_card[1].num = 0;
	
	Poker *del_card;
	Poker *del_temp;
	Poker *temp1;
	
	while( i != 3)
	{
		printf("想要輸入哪位玩家的牌色，請輸入 玩家一(請輸入1) 或 玩家二(請輸入2) ，若想退出請輸入 3 \n");
		scanf("%d",&i);
		
		while(i == 1 || i == 2)
		{
			printf("(1) 發牌:請輸入發幾張牌\n");
			printf("(2) 選擇一個花色，依拿到順序列出\n");
			printf("(3) 選擇一個花色，依拿到相反順序列出\n");
			printf("(4) 選擇一個花色，依大小由小而大一一列出\n");
			printf("(5) 輸入一張牌，從該花色中刪除比該牌大的牌中最小的\n");
			printf("(6) 退出\n");
			printf(" 輸入: ");
			scanf("%d",&input[0]);
			if( input[0] == 6)
			{
				break;
			}
			switch (input[0])
			{
				case 1 : 
					printf("請輸入要發幾張牌:");
					scanf("%d",&a);
					creat_card(&num_card[i-1],a,real_number[i-1]);
					
					//print_card(num_card[i]);
					
					break;
				case 2 :
					printf("你要看什麼花色(黑桃:S,愛心:H,方塊:D,梅花:C)");
					scanf("%s",card_color);
					look_from_head(&num_card[i-1],card_color);
				
					break;
				case 3 :
					printf("你要看什麼花色(黑桃:S,愛心:H,方塊:D,梅花:C):");
					scanf("%s",card_color);
					look_from_tail(&num_card[i-1],card_color);
					
					break;
				case 4 :
					printf("你要看什麼花色(黑桃:S,愛心:H,方塊:D,梅花:C):");
					scanf("%s",card_color);
					print_card(look_from_S_to_B(&num_card[i-1],card_color));
					
					break;
				case 5 :
					printf("請輸入你的牌色\n");
					printf("花色(黑桃:S,愛心:H,方塊:D,梅花:C):");
					scanf("%s",card_color);
					printf("數字:");
					scanf("%d",&b);
					del_temp = search_num(&num_card[i-1],card_color, b );
					del_card = &num_card[i];
					
					temp1 = &num_card[i-1];
					while(temp1->next != NULL)
					{
						if(temp1->color == card_color[0] && temp1->num == del_temp->num)
						{
							delet_node(temp1->pre,temp1->next);
							max = 1;
							break;
						}
						
						temp1 = temp1->next;
					}
					if(max == 0)
					{
						printf("輸入的牌大於所有手牌!\n");
					}
					break;
				default:
					break;
			}
			
			if(i != 1 || i != 2)
			{
				continue;
			}
		}
	}
	printf("玩家一的手牌:\n");
	print_card(&num_card[0]);
	printf("-------------------------\n");
	printf("玩家二的手牌:\n");
	print_card(&num_card[1]);
	return 0;
}

void print_card(Poker *card)
{
	Poker *temp = card;
	while (temp->next != NULL)
	{
		printf("color = %c,\t",temp->color);
		if(temp->num == 14)
		{
			printf("number = %d\n",temp->num%13);
		}
		else
		{
			printf("number = %d\n",temp->num);
		}
		
		temp = temp->next;
	}
	if(temp->num != 0)
	{
		printf("color = %c,\t",temp->color);
		if(temp->num == 14)
		{
			printf("number = %d\n",temp->num%13);
		}
		else
		{
			printf("number = %d\n",temp->num);
		}
	
	}
	else
	{
		return;
	}
}

void *creat_card(Poker *player , int count, int *num)
{
	
	int i,j,a;
	Poker *temp ;
	temp = player;
	
	while(temp->next != NULL)
	{
		temp = temp->next; 
	}
	
	srand(time(NULL));
	for(i=0;i<count;i++)
	{
		a = (rand()%52)+1;
		while(num[a-1] != 0)
		{
			a = (rand()%52)+1;
		}
		num[a-1] = 1;
		if( 1 <= a && a <= 13 )
		{
			temp->color = 'S';
			temp->num = a%13;
			if(temp->num == 0)
			{
				temp->num = 13;
			}
			if( temp->num == 1)
			{
				temp->num = 14;
			}
			temp->next =  creat_node(temp,NULL);
		}
		else if(14 <= a && a <= 26)
		{
			temp->color = 'H';
			temp->num = a%13;
			if(temp->num == 0)
			{
				temp->num = 13;
			}
			if( temp->num == 1)
			{
				temp->num = 14;
			}
			temp->next =  creat_node(temp,NULL);
		}
		else if(27 <= a && a <= 39)
		{
			temp->color = 'D';
			temp->num = a%13;
			if(temp->num == 0)
			{
				temp->num = 13;
			}
			if( temp->num == 1)
			{
				temp->num = 14;
			}
			temp->next =  creat_node(temp,NULL);
		}
		else 
		{
			temp->color = 'C';
			temp->num = a%13;
			if(temp->num == 0)
			{
				temp->num = 13;
			}
			if( temp->num == 1)
			{
				temp->num = 14;
			}
			temp->next =  creat_node(temp,NULL);
		}
		temp = temp->next;
	}
	while( temp->pre != NULL)
	{
		 temp =  temp->pre; 
	}
	print_card(temp);
	return ;
}


Poker *creat_node( Poker *pre_card,Poker *next_card)
{
	Poker *temp1 = (Poker*)malloc(sizeof(Poker));
	temp1->color = '0';
	temp1->num = 0;
	
	temp1->pre = pre_card;
	temp1->next = next_card;
	return temp1;
}

Poker *delet_node( Poker *pre_card, Poker *next_card)
{
	if(pre_card == NULL)
	{
		next_card->pre == NULL;
	}
	else if (next_card == NULL)
	{
		pre_card->next = NULL;
	}
	else
	{
		pre_card->next = next_card;
		next_card->pre = pre_card;	
	}
	return pre_card;
}
void look_from_head(Poker *card,char *color1)
{
	char a = color1[0];
	Poker *temp = card;				
	while(temp->next != NULL)
	{
		if( temp->color == a)
		{
			if(temp->num == 14)
			{
				
			printf("color = %c, number = %d\n",temp->color,temp->num%13);
			}
			else 
			{
				printf("color = %c, number = %d\n",temp->color,temp->num);
			}
		}
		temp = temp->next;
	}
}
void look_from_tail(Poker *card,char *color2)
{
	char a = color2[0];
	Poker *temp = card;
	
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	
	while(temp->pre != NULL)
	{
		if( temp->color == a )
		{
			if(temp->num == 14)
			{
				
			printf("color = %c, number = %d\n",temp->color,temp->num%13);
			}
			else
			{
				printf("color = %c, number = %d\n",temp->color,temp->num);
			}
		}
		temp = temp->pre;
	}
}

Poker *look_from_S_to_B(Poker *card,char *color3)
{
	char a = color3[0];
	Poker *temp = card;
	Poker *order_temp1;
	Poker *order_temp2;
	Poker *order_temp3;
	
	Poker *order = creat_node(NULL,NULL);				
	order_temp1 = order;
		
	while(1)
	{
		if(temp->color == a)
		{
			if(order->num == 0 )
			{
				order->color = temp->color;
				order->num = temp->num;
			}
			if( temp->num > order_temp1->num && order_temp1->num != 0)
			{
				while( temp->num > order_temp1->num && order_temp1->next != NULL)
				{
					order_temp1 = order_temp1->next;
				}
				
				if(order_temp1->next == NULL && order_temp1->num < temp->num)
				{
					order_temp2 = creat_node(order_temp1,NULL);
					order_temp2->color = temp->color;
					order_temp2->num = temp->num;
					order_temp1->next = order_temp2;
					
				}
				else
				{
					order_temp2 = creat_node(order_temp1->pre,order_temp1);
					order_temp2->color = temp->color;
					order_temp2->num = temp->num;
					order_temp3 = order_temp1->pre;
					order_temp3->next = order_temp2;
					order_temp1->pre = order_temp2;
				}
				
			}
			else if( temp->num < order_temp1->num && order_temp1->num != 0)
			{
				while( temp->num < order_temp1->num && order_temp1->pre != NULL)
				{
					order_temp1 = order_temp1->pre;
				}
				if(order_temp1->pre == NULL && order_temp1->num > temp->num)
				{
					order_temp2 = creat_node(NULL,order_temp1);
					order_temp2->color = temp->color;
					order_temp2->num = temp->num;
					order_temp1->pre = order_temp2;
				}
				else
				{
					order_temp2 = creat_node(order_temp1,order_temp1->next);
					order_temp2->color = temp->color;
					order_temp2->num = temp->num;
					order_temp1->next = order_temp2;
					order_temp1->next = order_temp3;
					order_temp3->pre = order_temp2;
				}
			}
			while( order_temp1->pre != NULL)
			{
				order_temp1 = order_temp1->pre;
			}
		}
		if(temp->next == NULL)
		{
			break;
		}
		temp = temp->next;
	}
	while( order_temp1->pre != NULL)
	{
		order_temp1 = order_temp1->pre;
	}
	return order_temp1;
}

Poker *search_num(Poker *card,char *color4, int b_num)
{
	Poker *temp;
	Poker *temp1;
	char a = color4[0];
	temp = look_from_S_to_B(card,&a);
	
	while(temp->next != NULL)
	{
		if(temp->num > b_num)
		{
			temp1 = temp;
			break;
		}
		temp = temp->next;
	}
	printf("the card : color = %c , number = %d\n",temp1->color,temp1->num);
	return temp1;
}




