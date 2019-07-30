#include <stdlib.h>
#include <string.h>
#include <getch.h>
#include <student.h>
#include <user.h>

// 存储用户账户信息的链表
List* user_list = NULL;

// 存储学生信息的链表
List* stu_list = NULL;

static const void* stu_arr[STU_MAX];

static void user_add(void)
{
	Student* stu = malloc(STU_SIZE);
	pf("请输入姓名、性别(w/m)、学号:");
	sf("%s %c %d",stu->name,&stu->sex,&stu->id);
	add_tail_list(stu_list,stu);
	stu_arr[0] = NULL;
}

static void user_del(void)
{
	int id = 0;
	pf("请输入要删除学员的学号：");
	sf("%d",&id);
	int cmp(const void* ptr1,const void* ptr2)
	{
		const int* id = ptr1;
		const Student* stu = ptr2;
		if(*id > stu->id)
			return 1;
		else if(*id < stu->id)
			return -1;
		else 
			return 0;
	}
	if(del_value_list(stu_list,&id,cmp))
	{
		pf("学号：%d 的学员已经删除!\n",id);
		stu_arr[0] = NULL;
	}
	else
	{
		pf("删除失败，未找到学号为：%d的学员!\n",id);
	}
}

static void user_chg(void)
{
	int id = 0;
	pf("请输入要修改学员的学号：");
	sf("%d",&id);
	int cmp(const void* ptr1,const void* ptr2)
	{
		const int* id = ptr1;
		const Student* stu = ptr2;
		if(*id > stu->id)
			return 1;
		else if(*id < stu->id)
			return -1;
		else 
			return 0;
	}
	Student* stu = find_list(stu_list,&id,cmp);
	if(NULL == stu)
	{
		pf("未找到学号为:%d的学员!\n",id);
		return;
	}
	
	pf("请重新输入学员为:%d的姓名和性别:",id);
	sf("%s %c",stu->name,&stu->sex);
	pf("修改信息成功!\n");
}

static void user_find(void)
{
	int id = 0;
	pf("请输入要查找学员的学号：");
	sf("%d",&id);
	int cmp(const void* ptr1,const void* ptr2)
	{
		const int* id = ptr1;
		const Student* stu = ptr2;
		if(*id > stu->id)
			return 1;
		else if(*id < stu->id)
			return -1;
		else 
			return 0;
	}
	int index = binary_find(stu_arr,stu_list->size,&id,cmp);
	if(index < 0)
	{
		pf("没有找到学号为：%d的学员!\n",id);
	}
	else
	{
		show_stu(stu_arr[index]);
	}
}

static void user_sort(void)
{
	if(stu_arr[0]) return;
	size_t index = 0;
	void get_stu(const void* ptr)
	{
		stu_arr[index++] = ptr;
	}
	show_list(stu_list,get_stu);
	
	int cmp(const void* ptr1,const void* ptr2)
	{
		const Student* s1 = ptr1, * s2 = ptr2;
		if(s1->id > s2->id)
			return 1;
		else if(s1->id < s2->id)
			return -1;
		else
			return 0;
	}
	
	quick_sort(stu_arr,index,cmp);
	
	for(int i=0; i<index; i++)
	{
		show_stu(stu_arr[i]);
	}
}

static void user_menu(void)
{
	for(;;)
	{
		system("clear");
		pf("******学生信息管理******\n");
		pf("1、增\n");
		pf("2、删\n");
		pf("3、改\n");
		pf("4、查\n");
		pf("5、排\n");
		pf("6、撤\n");
		
		switch(get_cmd('1','6'))
		{
			case '1': user_add(); break;
			case '2': user_del(); break;
			case '3': user_chg(); break;
			case '4': user_find(); break;
			case '5': user_sort(); break;
			case '6': return;
		}
	}
}

// 登录
State user_login(const char* acc,const char* pwd)
{
	int cmp(const void* ptr1,const void* ptr2)
	{
		const User* user = ptr2;
		return strcmp(ptr1,user->acc);
	}

	User* user = find_list(user_list,acc,cmp);
	
	if(NULL == user)
		return NameError;
	if(strcmp(pwd,user->pwd))
	{
		printf("---------passerror---------\n");
		return PassError;
	}
	user_menu();
	return LoginOk;
}
