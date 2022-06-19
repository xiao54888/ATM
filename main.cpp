#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Transaction
{
	char username[100];
	time_t timestamp;
	int type;//0-ȡ�1-���
	int amount;

	struct Transaction *next;//�����һ�����׽��ĵ�ַ
};
typedef struct Transaction Transaction;


struct Account
{
	char username[100];
	char password[100];	
	int money;
	
	struct Account * next;
};
typedef struct Account Account;

Account * head=NULL;//ָ��ͷ����ָ��
Account * tail=NULL;//ָ��β����ָ�� 
Account * curAccount=NULL;//ָ��ǰ��¼�˻���ָ�� 

//�ҵ�����1�����򷵻�0 
int findAccount(Account a)
{
	Account *curP=head;
	while(curP!=NULL)
	{
		if((strcmp(curP->username,a.username)==0)&&(strcmp(curP->password,a.password)==0))
		{
			curAccount=curP;
			return 1;
		}
		curP=curP->next;
	} 
	return 0;
}

void updatePassword()
{
	printf("�����������:\n");
	char oldPassword[100]={'\0'};
	scanf("%s",oldPassword);
	if(strcmp(oldPassword,curAccount->password)==0)
	{
		//�����޸� 
		printf("�����������룺\n");
		scanf("%s",curAccount->password);
		printf("�޸ĳɹ���\n");
	}
	else
	{
		printf("������������󣬾ܾ��޸ģ�\n");
	} 
	
}

void saveMoney()
{
  printf("���������");
  int money;
  scanf("%d",&money);
  
  //�������ƣ�

  curAccount->money+=money;
  printf("���ɹ���\n");

  //��¼������Ϣ

}


void drawMoney()
{
	printf("������ȡ���");
	int money;
	scanf("%d",&money);
	if(money<=curAccount->money)
	{
		printf("ȡ��ɹ���\n");
		curAccount->money-=money;

	
	}
	else
	{
		printf("����!ȡ��ʧ��\n");
	}

}

void homePage()
{
	system("cls");


	saveMoney();
}

void signIn()
{
	for(int i=0;i<3;i++)
	{
		Account a; 
		printf("��ӭ��¼\n");
		printf("�������˺ţ�\n");
		scanf("%s",a.username);
		
		printf("���������룺\n");
		scanf("%s",a.password);
		
		if(findAccount(a))
		{
			homePage();
			return;
		}
		else
		{
			printf("��¼ʧ��!\n");
		}
	} 
}


int loadData()
{
	FILE* fp=fopen("D:/atm.txt","r");
	if(fp==NULL)
	{
		return 0; 
	}
	else
	{
		while(!feof(fp))
		{
			//������㣺�ڶ�������һ���ڴ�ռ䣬�����ַ��ֵ��ָ��newNode
			Account * newNode=(Account *)malloc(sizeof(Account)); 
			
			//��㸳ֵ������ʼ��
			newNode->next=NULL;
			fscanf(fp,"%s %s\n",newNode->username,newNode->password);
			
			//��ӽ�㵽����
			if(head==NULL)
			{
				head=newNode;
				tail=newNode;
			}
			else
			{
				tail->next=newNode;
				tail=newNode;
			}
		}
		return 1;
	}

}


int main()
{
	/*int status=loadData();
	if(status==1)
	{
		printf("���سɹ���\n");
	}
	else
	{
		printf("����ʧ�ܣ�\n");
	}
	signIn();*/


	time_t timestamp = time(NULL);
	printf("%ld\n",timestamp);

	char *ct=ctime(&timestamp);
	printf("%s\n",ct);

	return 0;
}