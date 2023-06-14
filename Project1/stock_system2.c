#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_LENGTH 100

struct Stock {
	int id;												//商品编号是独一无二的
	char name[50];
	float price;
	int quantity;
}stock[MAX_LENGTH];
		
int count = 0;											//商品的数量

int checkUniqueID(int id) {								//确定商品编号是唯一的
	int i;
	
	for (i = 0; i < count; i++)
		if (stock[i].id == id)
			return 0;

	return 1;
}

void insertStock(int n) {
	while (n--) {										//循环n遍
		int id;
		printf("请输入商品编号：");
		scanf("%d", &id);	
		if (checkUniqueID(id))							//确定商品编号是唯一的
			stock[count].id = id;
		else {
			printf("商品输入失败，商品编号必须是独一无二的");
			return;
		}

		printf("请输入商品名称：");
		scanf("%s", &stock[count].name);
		printf("请输入商品价格：");
		scanf("%f", &stock[count].price);
		printf("请输入商品数量：");
		scanf("%d", &stock[count].quantity);

		printf("商品输入成功!\n");
		
		count++;
	}
}

void viewStock() {
	int i;

	for (i = 0; i < count; i++) {						//显示stock里的所有商品
		printf("商品编号:%d  ", stock[i].id);
		printf("商品名称:%s  ", stock[i].name);
		printf("商品价格:%.2f  ", stock[i].price);
		printf("商品数量:%d  \n", stock[i].quantity);
	}
}

void findStock(int id) {
	int i, found;
	found = 0;
	for (i = 0; i < count; i++) {
		if (stock[i].id == id) {
			printf("商品编号:%d  ", stock[i].id);
			printf("商品名称:%s  ", stock[i].name);
			printf("商品价格:%.2f  ", stock[i].price);
			printf("商品数量:%d  \n", stock[i].quantity);

			found = 1;									//商品找到了
			break;
		}
	}

	if (!found)											//如果商品没找到
		printf("找不到此商品");
}

void deleteStock(int id) {
	int i, found, pos;
	found = 0;

	//确保这个商品编号存在
	for (i = 0; i < count; i++) {
		if (stock[i].id == id) {
			found = 1;
			pos = i;
			break;
		}
	}

	if (!found) {
		printf("找不到此商品");
		return;
	}

	//从pos开始每一个商品往前移一格
	for (; pos < count - 1; pos++)
		stock[pos] = stock[pos + 1];

	count--;
}

void menu()
{
	int command;							//command = 命令
	int n, id;								//n 是商品人数, id是商品编号

	printf("\n\n");
	printf("\t\t\t===================商品信息管理系统==================\n");
	printf("\t\t\t*                                                   *\n");
	printf("\t\t\t*          1>. 录入商品信息                         *\n");
	printf("\t\t\t*          2>. 显示商品信息                         *\n");
	printf("\t\t\t*          3>. 查找商品信息                         *\n");
	printf("\t\t\t*          4>. 删除商品信息                         *\n");
	printf("\t\t\t*          0>. 退出管理系统                         *\n");
	printf("\t\t\t*                                    欢迎使用本系统!*\n");
	printf("\t\t\t=====================================================\n");
	printf("\t\t\t输入选项，按回车进入选项:                             \n");
	printf("请输入相应的数字，进行相应的操作:\n");
	scanf_s("%d", &command);
	system("cls");

	switch (command)
	{
	case 1:
		printf("请输入您要录入的商品数量:");
		scanf("%d", &n);
		insertStock(n);							//输入商品信息
		getchar();
		printf("\n请按回车主菜单\n");
		getchar();
		system("cls");
		break;
	case 2:
		viewStock();						      //显示商品信息
		getchar();
		printf("\n请按回车主菜单\n");
		getchar();
		system("cls");
		break;
	case 3:
		printf("请输入您要查找的商品编号:");
		scanf("%d", &id);
		findStock(id);							//查找商品信息
		getchar();
		printf("\n请按回车主菜单\n");
		getchar();
		system("cls");
		break;
	case 4:
		printf("请输入您要删除的商品编号:");
		scanf("%d", &id);
		deleteStock(id);							  //删除商品信息
		getchar();
		printf("\n请按回车主菜单\n");
		getchar();
		system("cls");
		break;

	case 0:                                     //退出系统
		printf("即将退出系统.....");
		exit(0);
	default:
		printf("您输入的指令不正确，请重新输入");
		getchar();
	}
}

int main() {
	while (1)
		menu();
}
