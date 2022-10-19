#define _CRT_SECURE_NO_WARNINGS 1
#include "contact.h"
//��̬�ڴ�ռ�һ��Ҫע�����
//�޸Ķ�̬�ڴ�Ҫ��ȷ���ɹ��ٸı�ָ��
//�ļ��رպ�Ҫ����Ұָ��
//�ļ��Ƿ�򿪳ɹ�ҲҪע����
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
			perror("����ͨѶ¼:����");
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
		perror("������̬�ڴ�ռ�");
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
		perror("����ͨѶ¼");
		return;
	}
	fclose(pfread);
	pfread = NULL;
}

void ShowContact(Contact* ps)
{
	if (0 == ps->size)
	{
		printf("ͨѶ¼����Ա\n");
		return;
	}
	else
	{
		printf("ͨѶ¼�ѱ���%d���˵���Ϣ\n", ps->size);
	}
	printf("%-10s%-10s%-10s%-15s%-40s\n", 
		"����", "�Ա�", "����", "�绰", "סַ");
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
	printf("����������:>");
	scanf("%s", ps->data[ps->size].name);
	printf("�������Ա�:>");
	scanf("%s", ps->data[ps->size].sex);
	printf("����������:>");
	scanf("%d", &(ps->data[ps->size].age));
	printf("������绰:>");
	scanf("%s", ps->data[ps->size].tele);
	printf("������סַ:>");
	scanf("%s", ps->data[ps->size].address);
	ps->size++;
	printf("��ӳɹ�\n");
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
		printf("ͨѶ¼����Ա\n");
		return;
	}
	printf("��ѡ��Ҫɾ������:>");
	scanf("%s", name);
	i = searchContact(ps, name);
	if (-1 == i)
	{
		printf("���޴���\n");
	}
	else
	{
		for (j = i; j < ps->size; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size -= 1;
		printf("ɾ���ɹ�\n");
	}
}

void SearchContact(Contact* ps)
{
	char name[20];
	int i = 0;
	if (0 == ps->size)
	{
		printf("ͨѶ¼����Ա\n");
		return;
	}
	printf("������Ҫ���ҵ���Ա����:>");
	scanf("%s", name);
	i = searchContact(ps, name);
	if (-1 == i)
	{
		printf("���޴���\n");
	}
	else
	{
		printf("%-10s%-10s%-10s%-15s%-40s\n",
			"����", "�Ա�", "����", "�绰", "סַ");
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
		printf("ͨѶ¼����Ա\n");
		return;
	}
	printf("������Ҫ�޸ĵ�������:>");
	scanf("%s", name);
	i = searchContact(ps, name);
	if (-1 == i)
	{
		printf("���޴���\n");
	}
	else
	{
		int input = 0;
		printf("****  1.�޸�����  ******\n");
		printf("****  2.�޸��Ա�  ******\n");
		printf("****  3.�޸�����  ******\n");
		printf("****  4.�޸ĵ绰  ******\n");
		printf("****  5.�޸ĵ�ַ  ******\n");
		printf("****  0.  ȡ��    ******\n");
		switch(input)
		{
			printf("����������:>");
			scanf("%s", ps->data[i].name);
			printf("�������Ա�:>");
			scanf("%s", ps->data[i].sex);
			printf("����������:>");
			scanf("%d", &(ps->data[i].age));
			printf("������绰:>");
			scanf("%s", ps->data[i].tele);
			printf("������סַ:>");
			scanf("%s", ps->data[i].address);
			printf("�޸ĳɹ�\n");
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
		printf("1.������������\n");
		printf("2.������������\n");
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
			printf("������1��2!\n");
		}
	}
}

void SaveContact(Contact* ps)
{
	FILE* pfwrite = fopen("contact.lib", "wb");
	if (pfwrite == NULL)
	{
		perror("ͨѶ¼����");
		return;
	}
	int i = 0;
	for(i=0;i<ps->size;i++)
	{
		fwrite(&(ps->data[i]), sizeof(PeoInfo), 1, pfwrite);
	}
	fclose(pfwrite);
	//�ļ��رպ�ע��ָ�룬��Ҫ����Ұָ��
	pfwrite = NULL;
}

void DestroyContact(Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
}
 