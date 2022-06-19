#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
void homePage();
struct Transaction
{
	char username[100];
	time_t timestamp;
	int type;//0-ȡ�1-���
	int amount;

	struct Transaction* next;
};
typedef struct Transaction Transaction;

//���׼�¼��Ϣ���� 
Transaction* tHead = NULL;
Transaction* tTail = NULL;


struct Account
{
	char password[7];
	char username[19];
	int money;
	struct Account* next;
};
typedef struct Account Account;

int language;
Account a;

typedef struct Account Account;

Account* head = NULL;//ָ��ͷ��� 
Account* tail = NULL;//ָ��β��� 
Account* curAccount = NULL;//��¼��ǰ�˻� 


//���سɹ�����1�����򷵻�0 
void loadData()
{
	FILE* fp = fopen("D:/demo2/atm.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			//�������
			Account* newNode = (Account*)malloc(sizeof(Account));
			if (newNode == NULL) {
				exit(-1);
			}//�ж�malloc����ռ��Ƿ�ɹ�����������

			//����ʼ��
			newNode->next = NULL;
			fscanf_s(fp, "%s %s %d\n", newNode->username,19, newNode->password,7,&newNode->money);

			//��ӽ�㵽����
			if (head == NULL)
			{
				head = newNode;
				tail = newNode;
			}
			else
			{
				tail->next = newNode;
				tail = newNode;
			}
		}
		fclose(fp);
	}
}

void drawMoney()
{
	system("cls");
	printf("-	ȡ��>1		����>2	-\n");
		
	int n;
	scanf_s("%d",&n);
	switch (n)
	{
	case 1:
			printf("������ȡ���");
			int money;
			while (1)
			{
				scanf_s("%d", &money);
				if ((money % 100) != 0)
					printf("������ȡ��������룺\n");
				else
					break;

			}
			

			//��֤���
			if (curAccount->money >= money)
			{
				printf("ȡ��ɹ���\n");
				curAccount->money -= money;

				//�������׼�¼...	

				//�������
				Transaction* newNode = (Transaction*)malloc(sizeof(Transaction));
				if (newNode == NULL) {
					exit(-1);
				}//�ж�malloc����ռ��Ƿ�ɹ�����������
				//����ʼ��
				newNode->next = NULL;
				strcpy(newNode->username, curAccount->username);
				newNode->timestamp = time(NULL);
				newNode->type = 0;
				newNode->amount = money;

				//��ӽ�㵽����
				if (tHead == NULL)
				{
					tHead = newNode;
					tTail = newNode;
				}
				else
				{
					tTail->next = newNode;
					tTail = newNode;
				}
			}
			else
			{
				printf("���㣡\n");
			}
			system("pause");
	case 2: homePage(); break;
	default:
		break;
	}
	
}

void transfer() {
	system("cls");
	FILE* fp = fopen("D:/demo2/atm.txt", "r+");
	if (fp == NULL)	//�޸������жϽ�����־���Warning C6387
		exit(-1);
	int money;
	char id[7] = {"\0"};
	Account* curp=head;
	

	
	printf("\n\n\t\t������ת���˵��û�����");
	scanf_s("%s", &id,7);
	while (curp!=NULL)
	{
	
	
		if (strcmp(id,curp->username) == 0) 
		{
			printf("\n\n\t\t������Ҫת�˵Ľ�");
			scanf_s("%d", &money);
			printf("\n\n\t\t��ȷ����Ŀ��%d", money);
			curp->money += money;
			curAccount->money -= money;
			printf("\n\n\nת�˳ɹ�");
			fprintf(fp, "%s\t%s\t%d\n", curAccount->username, curAccount->password,curAccount->money);
			fclose(fp);
		}
		curp =curp-> next;
		
	}
	system("pause");
	homePage();
}


void saveMoney()
{
	system("cls");
	printf("-	���>1		����>2	-\n");

	int n;
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:
			printf("���������");
			int money;
			while (1)
			{
				scanf_s("%d", &money);
				if ((money % 100) != 0)
					printf("�����ٴ��������룺\n");
				else
					break;

			}
			printf("���ɹ���\n");
			curAccount->money += money;

			//�������׼�¼...	
			system("pause");
	case 2: homePage(); break;
	default:
		break;
	}
	
}

void esc()
{
	void saveData();
	saveData();
	exit(0);
}

void enquiryService()
{
	system("cls");
	printf("-	��ѯ����>1		����>2	-\n");
	
	int n;
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:printf("%s\t%s\t%d\t\n", curAccount->username, curAccount->password, curAccount->money);
		   system("pause");
	case 2:homePage(); break;
	default:
		break;
	}
	

}

void printLinkedList()
{
	Account* curP = head;
	while (curP != NULL)
	{
		printf("%s\t%s\t%d\t\n", curP->username, curP->password,  curP->money);
		curP = curP->next;
	}
}



void signUp()
{
	void showMenu();
	Account* newNode = (Account*)malloc(sizeof(Account));
	if (newNode == NULL) {
		exit(-1);
	}//�ж�malloc����ռ��Ƿ�ɹ�����������
	newNode->next = NULL;
	printf("�������˺ţ�\n");
	scanf_s("%s", newNode->username,19);

	printf("���������룺\n");
	scanf_s("%s", newNode->password,7);
	newNode->money = 0;
	tail->next = newNode;
	tail = newNode;
	printf("ע��ɹ���\n");
	showMenu();

}


//�ҵ�����1�����򷵻�0 
int findAccount(Account a)
{
	Account* curp = head;
	while (curp != NULL)
	{
		if ((strcmp(curp->username, a.username) == 0) && (strcmp(curp->password, a.password) == 0))
		{
			curAccount = curp;
			return 1;
		}
		curp = curp->next;
	}
	return 0;
}
void updatePassword()
{

	system("cls");
	printf("-	��������>1		����>2	-\n");
	
	int n;
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:
			printf("����������룺");
			char oldPassword[7] = { "\0" };
			scanf_s("%s", oldPassword, 7);
			if (strcmp(oldPassword, curAccount->password) == 0)
			{
				printf("�����������룺");
				while (1)
				{
					scanf_s("%s", curAccount->password, 7);
					if (strcmp(oldPassword, curAccount->password) == 0)
					{
						printf("�¾����벻��һ��!\n");
						printf("��������!\n");
					}
					else
						break;
				}
				printf("�޸ĳɹ���\n");

			}
			else
			{
				printf("������󣡲����޸ģ�\n");
			}
			system("pause");
	case 2:	homePage(); break;
	default:
		break;
	}
	

}


void signIn()
{

	int i;
	for (i = 0; i < 3; i++)
	{
		Account a;
		printf("�������˺ţ�");
		scanf_s("%s", a.username,19);

		printf("���������룺");
		scanf_s("%s", a.password,7);

		if (findAccount(a))
		{
			printf("��¼�ɹ���\n");
			homePage();
		}
		else
		{
			printf("��¼ʧ�ܣ�\n");
		}
	}
	Account* node=head;
	curAccount = node;

}


void showMenu()
{
	system("cls");
	if (language == 1)
	{
		printf("\t\t||------------------------------||\n");
		printf("\t\t||	    ��¼>1		||\n");
		printf("\t\t||	    ����>2		||\n");
		printf("\t\t||	    �˳�>3		||\n");
		printf("\t\t||------------------------------||\n");
	}
	else if (language == 2)
	{
		printf("-	Sign in> 1	-\n");
		printf("-	Sign up> 2	-\n");
		printf("-	Sign out> 3	-\n");
	}
	int n;
	scanf_s("%d", &n);
	if (n == 1)
	{
		signIn();
	}
	else if (n == 2)
	{
		signUp();
	}
	else if (n == 3)
	{
		return;
	}
}

//���سɹ�����1�����򷵻�0 

void saveData()
{
	FILE* fp = fopen("D:/demo2/atm.txt", "w");
	if (fp != NULL)
	{
		Account* curP = head;
		while (curP != NULL)
		{
			fprintf(fp, "%s\t%s\t%d\n",curP->username, curP->password,  curP->money);
			curP = curP->next;
		}
		fclose(fp);
	}
}

void homePage()
{
	system("cls");
	printf("\t\t||--------------------------------------||\n");
	printf("\t\t||	ȡ��>1			���>2	||\n");
	printf("\t\t||	��ѯ����>3		ת��>4	||\n");
	printf("\t\t||	��������>4		�˳�>6	||\n");
	printf("\t\t||--------------------------------------||\n");
	
	
	int n;
	scanf_s("%d",&n);
	switch (n)
	{
	case 1: drawMoney(); break;
	case 2: saveMoney(); break;
	case 4:transfer(curAccount); break;
	case 3: enquiryService(); break;
	case 5: updatePassword(); break;
	case 6: esc(); break;
	default:
		break;
	}
}


int main()
{
	loadData();
	printf("\t\t||-----------ATM����------------||\n");
	printf("\t\t||	   ���ķ���>1		||\n");
	printf("\t\t||	English Service>2	||\n");
	printf("\t\t||------------------------------||\n");
	scanf_s("%d", &language);
	showMenu();
	saveData();
	return 0;
}
