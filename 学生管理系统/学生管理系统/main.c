#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Source 150
#define FILESIZEMAX 1024

//链表的每一个元素叫做节点。
typedef struct node
{
	int age;
	char name[15];
	int number;
	int source;
	struct node* next;//指针域
}Node;//Node

Node* ListHead;
Node* ListEnd;

void AddStudent(int age,char *name,int number,int source)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->age = age;
	temp->number = number;
	temp->source = source;
	//C语言：字符串操作函数
	strcpy(temp->name, name);

	//把我们的新创建的节点放到我们的链表内

	//第一种情况：当我们这个Head和end都是NULL的时候
	if (ListHead == NULL && ListEnd == NULL)
	{
		ListHead = temp;
		ListEnd = temp;
	}
	//第二种情况：
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
		printf("姓名:%s\n", temp->name);
		printf("年龄:%d\n",temp->age);
		printf("学号:%d\n",temp->number);
		printf("成绩:%d\n",temp->source);
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
			printf("姓名:%s\n", temp->name);
			printf("年龄:%d\n", temp->age);
			printf("学号:%d\n", temp->number);
			printf("成绩:%d\n", temp->source);
			printf("-----------------------------------\n");
			return;
		}

		temp = temp->next;
	}
	printf("没有这个学生:%d\n", number);
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

			printf("输入学生名称:");
			scanf_s("%s", str, 15);
			printf("输入学生年龄:");
			scanf_s("%d", &age);
			printf("输入学生学号:");
			scanf_s("%d", &number);
			printf("输入学生成绩:");
			scanf_s("%d", &source);

			temp->age = age;
			temp->source = source;
			temp->number = number;
			strcpy(temp->name, str);
			printf("学生信息已经修改完毕\n");

			return;
		}

		temp = temp->next;
	}
	printf("没有这个学生:%d\n", number);
}

void ShowFailStudent()
{
	Node* temp = ListHead;
	while (temp != NULL)
	{
		if (temp->source < Source * 0.6)
		{
			printf("姓名:%s\n", temp->name);
			printf("年龄:%d\n", temp->age);
			printf("学号:%d\n", temp->number);
			printf("成绩:%d\n", temp->source);
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
		printf("文件打开错误");
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

		printf("0.退出系统\n");
		printf("1.添加一名学生\n");
		printf("2.保存数据进文件\n");
		printf("3.显示指定学生信息\n");
		printf("4.显示所有学生信息\n");
		printf("5.修改指定学生信息\n");
		printf("6.删除指定学生信息\n");
		printf("7.统计(显示不及格学生)\n");
		printf("8.读取文件\n");

		int n = -1;//存储我们的用户选择的功能的,初始化-1呢？8，9

		scanf_s("%d", &n);

		//switch    if ... else if ... else
		switch (n)
		{
		case 0:
			printf("感谢使用本系统!\n");
			return 1;
			break;
		case 1:
		{
			int age = -1;
			int number = -1;
			char str[15] = { '\0' };
			int source = -1;

			printf("输入学生名称:");
			scanf_s("%s", str, 15);
			printf("输入学生年龄:");
			scanf_s("%d", &age);
			printf("输入学生学号:");
			scanf_s("%d", &number);
			printf("输入学生成绩:");
			scanf_s("%d", &source);

			AddStudent(age, str, number, source);
		}
			break;
		case 2:
		{
			char FileName[FILESIZEMAX] = { '\0' };
			printf("请输入保存的文件名称:");
			scanf_s("%s", FileName, FILESIZEMAX - 1);//-1 是为\0留一个位置
			SaveStudent(FileName);
		}
			break;
		case 3:
		{
			int number = -1;
			printf("输入要查找的学生学号:");
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
			printf("输入要查找的学生学号:");
			scanf_s("%d", &number);
			ReviseStudentInfo(number);
		}
			break;
		case 6:
		{
			int number = -1;
			printf("输入要查找的学生学号:");
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
			printf("请输入读取的文件名称:");
			scanf_s("%s", FileName, FILESIZEMAX - 1);//-1 是为\0留一个位置
			ReadFile(FileName);
		}
			break;
		default:
			printf("您输入的功能数字有误，请重新输入\n");
			system("pause>0");
			break;
		}
		system("pause>0");

	}

	system("pause>0");//system : 调用我们的命令提示符里面的命令的
	return 0;
}