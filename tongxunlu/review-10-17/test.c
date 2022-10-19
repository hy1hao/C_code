#define _CRT_SECURE_NO_WARNINGS 1
#include "contact.h"

void menu()
{
	printf(" --------------------------------- \n");
	printf("|****   1.add        2.del    ****|\n");
	printf("|****   3.search     4.modify ****|\n");
	printf("|****   5.sort       6.show   ****|\n");
	printf("|****   7.save       0.exit   ****|\n");
	printf(" --------------------------------- \n");
	return 0;
}

int main()
{
	int input = 0;
	Contact con = { 0 };
	InitContact(&con);
	do
	{
		menu();
		scanf("%d", &input);
		switch(input)
		{
		case ADD:
			AddContact(&con);
			break;
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SORT:
			SortContact(&con);
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case SAVE:
			SaveContact(&con);
			break;
		case EXIT:
			printf("退出程序\n");
			SaveContact(&con);
			DestroyContact(&con);
			break;
		default:
			printf("非法输入,请输入0-7的数字！\n");
			break;
		}
	} while (input);
	return 0;
}