#include <tools.h>
#include <getch.h>

//清理输入缓冲区
void clear_stdin(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
}

//获取指令
char get_cmd(char start,char end)
{
	clear_stdin();

	printf("请输入指令:");
	while(true)
	{
		char val = getch();
		if(val >= start && val <= end)
		{
			printf("%c\n",val);
			return val;
		}
	}
}

void _quick_sort(const void* arr[],size_t left,size_t right,compar cmp)
{
	if(left >= right) return;

	// 计算标杆的下标
	int pi = (left+right)/2;
	// 备份标杆的值
	const void* pv = arr[pi];
	// 备份左右下标
	int l = left , r = right;

	// 左右下标相遇时结束
	while(l < r)
	{
		// 在标杆的左边寻找比它大的数据
		while(l<pi && 1!=cmp(arr[l],pv)) l++;
		if(l<pi) // 如果没有超出范围，说明找到比标杆大的值
		{
			// 与标杆交换位置，并记录新的标杆下标
			arr[pi] = arr[l];
			pi = l;
		}
		// 在标杆的右边寻找比它小的数据
		while(pi<r && 1!=cmp(pv,arr[r])) r--;
		if(pi<r) // 如果没有走出范围，说明找到比标杆小的值
		{
			arr[pi] = arr[r];
			pi = r;
		}
	}
	// 还原标杆的值
	arr[pi] = pv;
	//show_arr(arr,10);
	if(pi-left > 1) _quick_sort(arr,left,pi-1,cmp);
	if(right-pi > 1) _quick_sort(arr,pi+1,right,cmp);
}

void quick_sort(const void* arr[],size_t len,compar cmp)
{
	_quick_sort(arr,0,len-1,cmp);
}

int binary_find(const void* arr[],size_t len,const void* key,compar cmp)
{
	int l = 0 , r = len -1 ;

	while(l <= r)
	{
		int pi = (l+r) / 2;
		if(1 == cmp(key,arr[pi]))
			l = pi + 1;
		else if(-1 == cmp(key,arr[pi]))
			r = pi - 1;
		else 
			return pi;
	}
	
	return -1;
}
