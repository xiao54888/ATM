#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Account
{
	char username[100];
	char password[100];

	struct Account * next;
};
typedef struct Account Account;

Account* head=NULL;//ָ��ͷ���
Account* tail=NULL;//ָ��β���

Account* curAccount=NULL;//��¼��ǰ�˻�

//�ҵ�����1�����򷵻�0
int findAccount(Account a)
{
	Account * curp=head;
	while(curp!=NULL)
	{
		if((strcmp(curp->username,a.username)==0)&&(strcmp(curp->password,a.password)==0))
		{
			curAccount=curp;
			return 1;
		}
		curp=curp->next;
	}
	return 0;
}

void updatePassword()
{
	char formerPassword[100];
	printf("����������룺");
	scanf("%s",formerPassword);
	if(strcmp(formerPassword,curAccount->password)==0)
	{
		printf("�����������룺");
		scanf("%s",curAccount->password);
		printf("�޸ĳɹ���\n");
	}
	else
	{
		printf("������󣡲����޸ģ�\n");
	}
}

void signIn()
{
	int i;
	for(i=0;i<3;i++)
	{
		Account a;
		printf("�������˺ţ�");
		scanf("%s",a.username);

		printf("���������룺");
		scanf("%s",a.password);

		if(findAccount(a)==1)
		{
			printf("��¼�ɹ���\n");
			updatePassword();
			break;
		}
		else
		{
			printf("��¼ʧ�ܣ�\n");
		}
	}
}

//���سɷ���1������ʧ�ܷ���0
int loadData()
{
	FILE*fp=fopen("D:/atm.txt","r");
	if(fp==NULL)
	{
		return 0;
	}
	else
	{
		while(!feof(fp))
		{
			//�������
			Account * newNode=(Account *)malloc(sizeof(Account));

			//����ʼ��
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
	int i=loadData();
	if(i==0)
	{
		printf("����ʧ�ܣ�\n");
	}
	else
	{
		printf("���سɹ���\n");
	}
	signIn();

	return 0;
}