#include <stdlib.h>
#include <student.h>
#include <sims.h>
#include <user.h>
#include <tools.h>
#include <getch.h>
#include <dao.h>


void login_sims(void)
{
	State state = 0;
	char acc[20] = {} , pwd[9]={};
	pf("请输入账号：");
	sf("%s",acc);
	pf("请输入密码：");
	sf("%s",pwd);
	
	if('1' == acc[0])
	{
		state = user_login(acc,pwd);
	}
		
	switch(state)
	{
		case NameError: pf("用户名或密码错误\n");
			break;
		case PassError: pf("密码错误请重新输入\n");
			break;
		case IsLock: pf("此账号被锁定，请申诉\n");
			break;
		default:break;
	}
}

void menu_sims(void)
{

	for(;;)
	{
		system("clear");
		pf("***欢迎使用指针信息管理系统***\n");
		pf("1、用户管理");
		pf("2、学生信息管理");
		pf("3、退出");
		pf("请输入指令：");
		switch(getch())
		{
			case '1':
			case '2': login_sims(); break;
			case '3': return;
		}
	}
}

// 初始化链表、加载数据
void init_sims(void)
{
	// 创建存储学生信息的链表
	stu_list = creat_list();
	// 载学生信息到链表中
	load(stu_list,STU_PATH,STU_SIZE);
	// 显示加载后的学生信息
	show_list(stu_list,show_stu);
	
	// 创建存储用户账号信息的链表
	user_list = creat_list();
	// 加载用户信息到链表中
	load(user_list,USER_PATH,USER_SIZE);
	// 显示加载后的用户账号信息
	void show_user(const void* ptr)
	{
		const User* user = ptr;
		pf("%s %s %hhd\n",user->acc,user->pwd,user->lock);
	}
	show_list(user_list,show_user);
}

// 进入学生信息管理系统
void start_sims(void)
{
	for(;;)
	{
		system("clear");
		pf("***欢迎使用指针信息管理系统***\n");
		pf("1、用户管理\n");
		pf("2、学生信息管理\n");
		pf("3、退出\n");
		switch(get_cmd('1','3'))
		{
			case '1':
			case '2': login_sims(); break;
			case '3': return;
		}
	}
}

// 保存数据、销毁链表
void exit_sims(void)
{
	save(stu_list,STU_PATH,STU_SIZE);
	save(user_list,USER_PATH,USER_SIZE);
}
