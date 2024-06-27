#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Source 150
#define FILESIZEMAX 1024

//�����ÿһ��Ԫ�ؽ����ڵ㡣
typedef struct node
{
	int age;
	char name[15];
	int number;
	int source;
	struct node* next;//ָ����
}Node;//Node

Node* ListHead;
Node* ListEnd;

void AddStudent(int age,char *name,int number,int source)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->age = age;
	temp->number = number;
	temp->source = source;
	//C���ԣ��ַ�����������
	strcpy(temp->name, name);

	//�����ǵ��´����Ľڵ�ŵ����ǵ�������

	//��һ����������������Head��end����NULL��ʱ��
	if (ListHead == NULL && ListEnd == NULL)
	{
		ListHead = temp;
		ListEnd = temp;
	}
	//�ڶ��������
	else
	{
		ListEnd->next = temp;
		ListEnd = temp;
	}

	temp->next = NULL;
}

void ShowStudent()
{
	Node* temp = ListHead;
	while (temp != NULL)
	{
		printf("����:%s\n", temp->name);
		printf("����:%d\n",temp->age);
		printf("ѧ��:%d\n",temp->number);
		printf("�ɼ�:%d\n",temp->source);
		printf("-----------------------------------\n");

		temp = temp->next;
	}
}

void UseInforShowStudent(int number)
{
	Node* temp = ListHead;
	while (temp != NULL)
	{
		if (temp->number == number)
		{
			printf("����:%s\n", temp->name);
			printf("����:%d\n", temp->age);
			printf("ѧ��:%d\n", temp->number);
			printf("�ɼ�:%d\n", temp->source);
			printf("-----------------------------------\n");
			return;
		}

		temp = temp->next;
	}
	printf("û�����ѧ��:%d\n", number);
}

void ReviseStudentInfo(int number)
{
	Node* temp = ListHead;
	while (temp != NULL)
	{
		if (temp->number == number)
		{
			int age = -1;
			int number = -1;
			char str[15] = { '\0' };
			int source = -1;

			printf("����ѧ������:");
			scanf_s("%s", str, 15);
			printf("����ѧ������:");
			scanf_s("%d", &age);
			printf("����ѧ��ѧ��:");
			scanf_s("%d", &number);
			printf("����ѧ���ɼ�:");
			scanf_s("%d", &source);

			temp->age = age;
			temp->source = source;
			temp->number = number;
			strcpy(temp->name, str);
			printf("ѧ����Ϣ�Ѿ��޸����\n");

			return;
		}

		temp = temp->next;
	}
	printf("û�����ѧ��:%d\n", number);
}

void ShowFailStudent()
{
	Node* temp = ListHead;
	while (temp != NULL)
	{
		if (temp->source < Source * 0.6)
		{
			printf("����:%s\n", temp->name);
			printf("����:%d\n", temp->age);
			printf("ѧ��:%d\n", temp->number);
			printf("�ɼ�:%d\n", temp->source);
			printf("-----------------------------------\n");
		}

		temp = temp->next;
	}
}

void DeleteStudent(int number)
{
	Node* temp = ListHead;
	Node* PrePoint = NULL;
	while (temp != NULL)
	{
		if (temp->number == number)
		{
			if (temp == ListHead)
			{
				ListHead = temp->next;
				temp->next = NULL;
				free(temp);
			}
			else if (temp == ListEnd)
			{
				ListEnd = PrePoint;
				PrePoint->next = NULL;
				free(temp);
			}
			else
			{
				PrePoint->next = temp->next;
				temp->next = NULL;
				free(temp);
			}

			return;
		}

		PrePoint = temp;
		temp = temp->next;
	}
}

void SaveStudent(char *SaveFileName)
{
	FILE* file = NULL;
	fopen_s(&file, SaveFileName, "w");

	Node* temp = ListHead;

	int count = 0;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	fwrite(&count, sizeof(int), 1, file);

	temp = ListHead;

	while (temp != NULL)
	{
		fwrite(temp, sizeof(Node), 1, file);
		temp = temp->next;
	}

	fclose(file);
}

void ReadFile(char* FileName)
{
	FILE* file = NULL;
	errno_t e = fopen_s(&file, FileName, "r");
	if (e == 2)
	{
		printf("�ļ��򿪴���");
		return;
	}

	int count = 0;

	fread(&count, sizeof(int), 1, file);

	if (count == 0)
	{
		fclose(file);
		return;
	}

	Node* temp = (Node*)malloc(sizeof(Node));

	for (int i = 0; i < count; i++)
	{
		fread(temp, sizeof(Node), 1, file);
		AddStudent(temp->age, temp->name, temp->number, temp->source);
	}

	fclose(file);
}

int main()
{

	while (1)
	{
		//pause cls
		system("cls");

		printf("0.�˳�ϵͳ\n");
		printf("1.���һ��ѧ��\n");
		printf("2.�������ݽ��ļ�\n");
		printf("3.��ʾָ��ѧ����Ϣ\n");
		printf("4.��ʾ����ѧ����Ϣ\n");
		printf("5.�޸�ָ��ѧ����Ϣ\n");
		printf("6.ɾ��ָ��ѧ����Ϣ\n");
		printf("7.ͳ��(��ʾ������ѧ��)\n");
		printf("8.��ȡ�ļ�\n");

		int n = -1;//�洢���ǵ��û�ѡ��Ĺ��ܵ�,��ʼ��-1�أ�8��9

		scanf_s("%d", &n);

		//switch    if ... else if ... else
		switch (n)
		{
		case 0:
			printf("��лʹ�ñ�ϵͳ!\n");
			return 1;
			break;
		case 1:
		{
			int age = -1;
			int number = -1;
			char str[15] = { '\0' };
			int source = -1;

			printf("����ѧ������:");
			scanf_s("%s", str, 15);
			printf("����ѧ������:");
			scanf_s("%d", &age);
			printf("����ѧ��ѧ��:");
			scanf_s("%d", &number);
			printf("����ѧ���ɼ�:");
			scanf_s("%d", &source);

			AddStudent(age, str, number, source);
		}
			break;
		case 2:
		{
			char FileName[FILESIZEMAX] = { '\0' };
			printf("�����뱣����ļ�����:");
			scanf_s("%s", FileName, FILESIZEMAX - 1);//-1 ��Ϊ\0��һ��λ��
			SaveStudent(FileName);
		}
			break;
		case 3:
		{
			int number = -1;
			printf("����Ҫ���ҵ�ѧ��ѧ��:");
			scanf_s("%d", &number);
			UseInforShowStudent(number);
		}
			break;
		case 4:
			ShowStudent();
			break;
		case 5:
		{
			int number = -1;
			printf("����Ҫ���ҵ�ѧ��ѧ��:");
			scanf_s("%d", &number);
			ReviseStudentInfo(number);
		}
			break;
		case 6:
		{
			int number = -1;
			printf("����Ҫ���ҵ�ѧ��ѧ��:");
			scanf_s("%d", &number);
			DeleteStudent(number);
		}
			break;
		case 7:
			ShowFailStudent();
			break;
		case 8:
		{
			char FileName[FILESIZEMAX] = { '\0' };
			printf("�������ȡ���ļ�����:");
			scanf_s("%s", FileName, FILESIZEMAX - 1);//-1 ��Ϊ\0��һ��λ��
			ReadFile(FileName);
		}
			break;
		default:
			printf("������Ĺ���������������������\n");
			system("pause>0");
			break;
		}
		system("pause>0");

	}

	system("pause>0");//system : �������ǵ�������ʾ������������
	return 0;
}