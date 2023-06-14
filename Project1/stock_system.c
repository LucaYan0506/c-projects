#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct Stock {
	int id;												//商品编号是独一无二的
	char name[50];
	float price;
	int quantity;
	struct Stock* next;
}*headStock;

int checkUniqueID(int id) {
	struct Stock* currStock = headStock;
	while (currStock != NULL && currStock->id != -1) {
		if (currStock->id == id) 
			return 0;

		currStock = currStock->next;
	}

	return 1;
}

void insertStock(int n) {
	struct Stock* currStock = headStock;
	while (currStock != NULL && currStock->id != -1)
		currStock = currStock->next;
	while (n--) {										//循环n遍
		int id;
		printf("请输入商品编号：");
		scanf("%d", &id);
		if (checkUniqueID(id))
			currStock->id = id;
		else {
			printf("商品输入失败，商品编号必须是独一无二的");
			return;
		}

		printf("请输入商品名称：");
		scanf("%s", currStock->name);
		printf("请输入商品价格：");
		scanf("%f", &currStock->price);
		printf("请输入商品数量：");
		scanf("%d", &currStock->quantity);

		printf("商品输入成功!\n");
		currStock->next = malloc(sizeof(struct Stock));		//赋予内存空间
		currStock->next->id = -1;
		currStock = currStock->next;
	}
}

void viewStock() {
	struct Stock* currStock = headStock;			
	while (currStock != NULL && currStock->id != -1) {
		printf("商品编号:%d  ", currStock->id);
		printf("商品名称:%s  ", currStock->name);
		printf("商品价格:%.2f  ", currStock->price);
		printf("商品数量:%d  \n", currStock->quantity);
		currStock = currStock->next;
	}
}

void findStock(int id) {
	int found = 0;

	struct Stock* currStock = headStock;
	while (currStock != NULL && currStock->id != -1) {
		if (currStock->id == id) {
			printf("商品编号:%d  ", currStock->id);
			printf("商品名称:%s  ", currStock->name);
			printf("商品价格:%.2f  ", currStock->price);
			printf("商品数量:%d  \n", currStock->quantity);
			found = 1;
			break;
		}

		currStock = currStock->next;
	}

	if (!found)
		printf("找不到此商品");
}

void deleteStock(int id) {
	struct Stock* currStock = headStock;
	int found = 0;
	struct Stock* prevStock = headStock;					//prevStock储存着我们要删掉的商品的前一个，所有prevStock->next是我们要删掉的商品

	if (currStock->id == id) {								//如果我们要删掉的商品是第一个，也就是headStock
		struct Stock *temp = headStock;
		headStock = headStock->next;						//headStock往前移一格
		free(temp);											//释放内存空间

		return;
	}

	//确保这个商品编号存在
	while (currStock != NULL && currStock->id != -1 && currStock->next != NULL && currStock->next->id != -1) {
		if (currStock->next->id == id) {
			found = 1;				
			prevStock = currStock;
			break;
		}

		currStock = currStock->next;
	}

	if (!found){
		printf("找不到此商品");
		return;
	}

	struct Stock* temp = prevStock->next;
	prevStock->next = prevStock->next->next;			//"删除"prevStock->next
	free(temp);											//释放内存空间

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
	headStock = malloc(sizeof(struct Stock));		//赋予内存空间
	headStock->id = -1;								//商品编号是独一无二的并且是一个正数,所以赋予一个负数的商品编号我们就能知道headStock是空的
	while (1)
		menu();
}
