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

	for (i = 0; i < count; i++)							//查找有没有一个商品的编号是跟id一样的
		if (stock[i].id == id)							//如果有那么id就不是唯一的所以返回0
			return 0;
		
	return 1;											//如果找完所以商品都没有一个商品编号跟id一样，那么id就是唯一的所以返回1
}

void insertStock(int n) {
	while (n--) {										//循环n遍
		int id;
		printf("请输入商品编号：");
		scanf("%d", &id);
		if (checkUniqueID(id))							//确定商品编号是唯一的
			stock[count].id = id;						//count是商品的数量，我们知道数组是从第0个元素开始的。所以stock[count]实际上就是最后一个商品的下一个
		else {
			printf("商品输入失败，商品编号必须是独一无二的");
			return;
		}

		printf("请输入商品名称：");
		scanf("%s", stock[count].name);
		printf("请输入商品价格：");
		scanf("%f", &stock[count].price);
		printf("请输入商品数量：");
		scanf("%d", &stock[count].quantity);

		printf("商品输入成功!\n");

		count++;									//新加了一个商品所以count + 1
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
			break;										//循环可以结束了，因为商品编号具有唯一性，所以如果找到了，那么不再会有另外一个商品有同样的id
		}
	}

	if (!found)											//如果商品没找到
		printf("找不到此商品");
}

void changeStock(int id) {
	int i, change;
	change = 0;

	for (i = 0; i < count; i++) {
		if (stock[i].id == id) {					//找到商品
			printf("请输入商品编号: ");
			scanf("%d", &stock[i].id);
			printf("请输入商品名称：");
			scanf("%s", stock[i].name);
			printf("请输入商品价格：");
			scanf("%f", &stock[i].price);
			printf("请输入商品数量：");
			scanf("%d", &stock[i].quantity);
			printf("商品输入成功!\n");
			change = 1;                                      //商品修改了
			break;										//循环可以结束了，因为商品编号具有唯一性，所以如果找到了，那么不再会有另外一个商品有同样的id
		}
	}

	if (!change)                                      //如果商品没修改到 
		printf("修改不了此商品");

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

	if (!found) {//如果不存在
		printf("找不到此商品");
		return;
	}

	//从pos开始每一个商品往前移一格
	for (; pos < count - 1; pos++)
		stock[pos] = stock[pos + 1];

	//删除了一个所以count-1 
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
	printf("\t\t\t*          4>. 修改商品信息                         *\n");
	printf("\t\t\t*          5>. 删除商品信息                         *\n");
	printf("\t\t\t*          0>. 退出管理系统                         *\n");
	printf("\t\t\t*                                    欢迎使用本系统!*\n");
	printf("\t\t\t=====================================================\n");
	printf("\t\t\t输入选项，按回车进入选项:                             \n");
	printf("请输入相应的数字，进行相应的操作:\n");
	scanf("%d", &command);
	system("cls");		//清理cmd（运行命令提示窗口）

	switch (command)
	{
	case 1:
		printf("请输入您要录入的商品数量:");
		scanf("%d", &n);
		insertStock(n);							//输入商品信息
		getchar(); // 假设输入的不是一个数字，scanf只会读取数字的部分，也就是说\n是"留在terminal上的"。通过getchar清除\n
		printf("\n请按回车主菜单\n");
		getchar();//等待用户按回车键
		system("cls");		//清理cmd（运行命令提示窗口）
		break;
	case 2:
		viewStock();						      //显示商品信息
		getchar(); // 假设输入的不是一个数字，scanf只会读取数字的部分，也就是说\n是"留在terminal上的"。通过getchar清除\n
		printf("\n请按回车主菜单\n");
		getchar();//等待用户按回车键
		system("cls");		//清理cmd（运行命令提示窗口）
		break;
	case 3:
		printf("请输入您要查找的商品编号:");
		scanf("%d", &id);
		findStock(id);							//查找商品信息
		getchar(); // 假设输入的不是一个数字，scanf只会读取数字的部分，也就是说\n是"留在terminal上的"。通过getchar清除\n
		printf("\n请按回车主菜单\n");
		getchar();//等待用户按回车键
		system("cls");		//清理cmd（运行命令提示窗口）
		break;
	case 4:
		printf("请输入您要修改的商品编号:");
		scanf("%d", &id);
		changeStock(id);							//修改商品信息
		getchar(); // 假设输入的不是一个数字，scanf只会读取数字的部分，也就是说\n是"留在terminal上的"。通过getchar清除\n
		printf("\n请按回车主菜单\n");
		getchar();//等待用户按回车键
		system("cls");		//清理cmd（运行命令提示窗口）
		break;
	case 5:
		printf("请输入您要删除的商品编号:");
		scanf("%d", &id);
		deleteStock(id);							  //删除商品信息
		getchar(); // 假设输入的不是一个数字，scanf只会读取数字的部分，也就是说\n是"留在terminal上的"。通过getchar清除\n
		printf("\n请按回车主菜单\n");
		getchar();//等待用户按回车键
		system("cls");	//清理cmd（运行命令提示窗口）
		break;

	case 0:                                     //退出系统
		printf("即将退出系统.....");
		exit(0);//退出系统
	default:
		printf("您输入的指令不正确，请重新输入");
		getchar();//假设输入的不是一个数字，scanf只会读取数字的部分，也就是说\n是"留在terminal上的"。通过getchar清除\n
	}
}

int main() {
	while (1)//无限循环menu这个函数（我们会通过在menu里的exit()退出系统）
		menu();//生成一个菜单
}
