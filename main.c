#include <stdlib.h>
#include <sims.h>
#include <user.h>
#include <student.h>
#include <string.h>
#include <dao.h>

int main()
{
/*s
	List* list = creat_list();
	for(int i=0; i<5; i++)
	{
		Student* stu = malloc(STU_SIZE);
		strcpy(stu->name,"haha");
		stu->sex = 'a'+rand()%26;
		stu->id = 10010+rand()%1000;
		add_tail_list(list,stu);
	}
	save(list,STU_PATH,STU_SIZE);
	
	
	user_list = creat_list();
	for(int i=0; i<5; i++)
	{
		User* user = malloc(USER_SIZE);
		sprintf(user->acc,"%d",10010+i);
		sprintf(user->pwd,"1234");
		user->lock = 0;
		pf("%s",user->acc);
		add_tail_list(user_list,user);
	}
	save(user_list,USER_PATH,USER_SIZE);*/

	// 初始化链表、加载数据
	init_sims();
	
	// 进入学生信息管理系统
	start_sims();
	
	// 保存数据、销毁链表
	exit_sims();

	return 0;
}
