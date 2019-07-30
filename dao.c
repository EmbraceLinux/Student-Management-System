#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <student.h>
#include <dao.h>

// 加密解密文件
static bool de_code(const char* path,char* cmd)
{
	FILE* frp = fopen(path,"r");
	if(NULL == frp) return false;
	char buf[16] = {};
	fread(buf,4,1,frp);
	
	FILE* fwp = fopen(TEMP_PATH,"w");
	if(0 == strcmp("decode",cmd))
	{
		printf("-----decode----------\n");
		if(0 != strncmp("code",buf,4))
		{
			printf("----no read code----------\n");
			return 0;
		}
	}
	else
	{
		printf("-------code------\n");
		if(0==strncmp("code",buf,4))
		{
			printf("-----read code----------\n");
			return 0;
		}
		rewind(frp);
		fwrite("code",4,1,fwp);
	}
	
	size_t len = strlen(PASSWORD) , i = 0;
	uint8_t data = 0;
	printf("index %d\n",ftell(frp));
	while(fread(&data,1,1,frp))
	{
		data ^= PASSWORD[i++%len];
		fwrite(&data,1,1,fwp);
	}
	
	fclose(frp); frp = NULL;
	fclose(fwp); fwp = NULL;
	
	remove(path);
	rename(TEMP_PATH,path);
	return true;
}

// 加载数据到链表
size_t load(List* list,const char* path,size_t size)
{
	// 解密文件
	de_code(path,"decode");
	// 读取文件
	FILE* frp = fopen(path,"r");
	if(NULL == frp)
	{
		printf("文件打开失败\n");
		return 0;
	}
	size_t count = 0;
	while(true)
	{
		void* ptr = malloc(size);
		if(0 >= fread(ptr,size,1,frp))
		{
			fclose(frp);
			return count;
		}
		add_tail_list(list,ptr);
		count++;	
	}
}

// 从链读取数据保存到文件中
size_t save(List* list,const char* path,size_t size)
{
	// 写入文件
	FILE* fwp = fopen(path,"w");
	size_t count = 0;
	void print(const void* ptr)
	{
		fwrite(ptr,size,1,fwp);
		count++;
	}
	show_list(list,print);
	fclose(fwp); fwp = NULL;
	// 加密文件
	de_code(path,"code");
	return count;
}
