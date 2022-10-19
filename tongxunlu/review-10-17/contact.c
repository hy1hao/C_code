#define _CRT_SECURE_NO_WARNINGS 1
#include "contact.h"
//动态内存空间一定要注意回收
//修改动态内存要先确定成功再改变指针
//文件关闭后要清理野指针
//文件是否打开成功也要注意检查
static void SpaceCheck(Contact* ps)
{
	if (ps->size == ps->space)
	{
		PeoInfo* ptr = realloc(ps->data, (ps->space + 2) * sizeof(PeoInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->space += 2;
		}
		else
		{
			perror("加载通讯录:增容");
			return;
		}
	}
}
void InitContact(Contact* ps)
{
	ps->size = 0;
	ps->data = (PeoInfo*)calloc(InitSpace, sizeof(PeoInfo));
	if (ps->data == NULL)
	{
		perror("创建动态内存空间");
		return;
	}
	ps->space = InitSpace;
	FILE* pfread = fopen("contact.lib", "rb");
	if(pfread!=NULL)
	{
		PeoInfo tmp = { 0 };
		while (fread(&tmp, sizeof(PeoInfo), 1, pfread))
		{
			SpaceCheck(ps);
			ps->data[ps->size] = tmp;
			ps->size++;
		}
	}
	else
	{
		perror("加载通讯录");
		return;
	}
	fclose(pfread);
	pfread = NULL;
}

void ShowContact(Contact* ps)
{
	if (0 == ps->size)
	{
		printf("通讯录无人员\n");
		return;
	}
	else
	{
		printf("通讯录已保存%d个人的信息\n", ps->size);
	}
	printf("%-10s%-10s%-10s%-15s%-40s\n", 
		"姓名", "性别", "年龄", "电话", "住址");
	int i = 0;
	for(i=0;i<ps->size;i++)
	{
		printf("%-10s%-10s%-10d%-15s%-40s\n",
			ps->data[i].name,
			ps->data[i].sex,
			ps->data[i].age,
			ps->data[i].tele,
			ps->data[i].address);
	}
}

void AddContact(Contact* ps)
{
	SpaceCheck(ps);
	printf("请输入名字:>");
	scanf("%s", ps->data[ps->size].name);
	printf("请输入性别:>");
	scanf("%s", ps->data[ps->size].sex);
	printf("请输入年龄:>");
	scanf("%d", &(ps->data[ps->size].age));
	printf("请输入电话:>");
	scanf("%s", ps->data[ps->size].tele);
	printf("请输入住址:>");
	scanf("%s", ps->data[ps->size].address);
	ps->size++;
	printf("添加成功\n");
	ShowContact(ps);
}

static int searchContact(Contact* ps, char name[20])
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (0 == strcmp(name, ps->data[i].name))
		{
			return i;
		}
	}
	return -1;
}

void DelContact(Contact* ps)
{
	char name[20];
	int i = 0;
	int j = 0;
	if (0 == ps->size)
	{
		printf("通讯录无人员\n");
		return;
	}
	printf("请选择要删除的人:>");
	scanf("%s", name);
	i = searchContact(ps, name);
	if (-1 == i)
	{
		printf("查无此人\n");
	}
	else
	{
		for (j = i; j < ps->size; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size -= 1;
		printf("删除成功\n");
	}
}

void SearchContact(Contact* ps)
{
	char name[20];
	int i = 0;
	if (0 == ps->size)
	{
		printf("通讯录无人员\n");
		return;
	}
	printf("请输入要查找的人员名字:>");
	scanf("%s", name);
	i = searchContact(ps, name);
	if (-1 == i)
	{
		printf("查无此人\n");
	}
	else
	{
		printf("%-10s%-10s%-10s%-15s%-40s\n",
			"姓名", "性别", "年龄", "电话", "住址");
		printf("%-10s%-10s%-10d%-15s%-40s\n",
				ps->data[i].name,
				ps->data[i].sex,
				ps->data[i].age,
				ps->data[i].tele,
				ps->data[i].address);
	}
}

void ModifyContact(Contact* ps)
{
	char name[20];
	int i = 0;
	if (0 == ps->size)
	{
		printf("通讯录无人员\n");
		return;
	}
	printf("请输入要修改的人名字:>");
	scanf("%s", name);
	i = searchContact(ps, name);
	if (-1 == i)
	{
		printf("查无此人\n");
	}
	else
	{
		int input = 0;
		printf("****  1.修改名字  ******\n");
		printf("****  2.修改性别  ******\n");
		printf("****  3.修改年龄  ******\n");
		printf("****  4.修改电话  ******\n");
		printf("****  5.修改地址  ******\n");
		printf("****  0.  取消    ******\n");
		switch(input)
		{
			printf("请输入名字:>");
			scanf("%s", ps->data[i].name);
			printf("请输入性别:>");
			scanf("%s", ps->data[i].sex);
			printf("请输入年龄:>");
			scanf("%d", &(ps->data[i].age));
			printf("请输入电话:>");
			scanf("%s", ps->data[i].tele);
			printf("请输入住址:>");
			scanf("%s", ps->data[i].address);
			printf("修改成功\n");
		}
	}
}

static int sortbyname(const void* e1, const void* e2)
{
	return strcmp(((PeoInfo*)e1)->name, ((PeoInfo*)e2)->name);
}

static int sortbyage(const void* e1, const void* e2)
{
	return ((PeoInfo*)e1)->age - ((PeoInfo*)e2)->age;
}

void SortContact(Contact* ps)
{
	int sort_by_whar = 0;
	while(1)
	{
		printf("1.根据名字排序\n");
		printf("2.根据年龄排序\n");
		scanf("%d", &sort_by_whar);
		if (1 == sort_by_whar)
		{
			qsort(ps->data, ps->size, sizeof(ps->data[0]), sortbyname);
			break;
		}
		else if (2 == sort_by_whar)
		{
			qsort(ps->data, ps->size, sizeof(ps->data[0]), sortbyage);
			break;
		}
		else
		{
			printf("请输入1或2!\n");
		}
	}
}

void SaveContact(Contact* ps)
{
	FILE* pfwrite = fopen("contact.lib", "wb");
	if (pfwrite == NULL)
	{
		perror("通讯录保存");
		return;
	}
	int i = 0;
	for(i=0;i<ps->size;i++)
	{
		fwrite(&(ps->data[i]), sizeof(PeoInfo), 1, pfwrite);
	}
	fclose(pfwrite);
	//文件关闭后注意指针，不要留下野指针
	pfwrite = NULL;
}

void DestroyContact(Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
}
 