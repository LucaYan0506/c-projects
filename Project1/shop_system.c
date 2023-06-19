#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

struct Goods//商品结构体 
{
	int id;//商品序号 
	char name[10];//商品名称  
	double price;//商品价格
	int date;//商品日期   (这个日期设的不太好）
	char vender[1000];//商品厂家
	char brand[1000];//商品牌子
};
enum Tag { quit, add, del, change, find, showall }; //枚举
struct  Goods goods[100];

int count;                   //全局变量，计数用
void menu();      //菜单
void Add();       //1.添加商品信息
void Del();       //2.删除商品信息
void Change();    //3.修改商品信息
void Find();      //4.查看单个商品信息
void Showall();   //5.显示所有商品信息

int main()
{
	while (1)
	{
		int num;
		menu();
		printf("请输入要执行的操作！\n");
		scanf("%d", &num);
		switch (num)
		{
		case add:   //1.添加商品信息
			Add();
			break;
		case del:   //2.删除商品信息
			Del();
			break;
		case change://3.修改商品信息
			Change();
			break;
		case find:  //4.查看单个商品信息
			Find();
			break;
		case showall:  //5.显示所有商品信息
			Showall();
			break;
		case quit:
			return 0;
		default:
			system("cls");	//清理cmd（运行命令提示窗口）
			printf("输入有误，请重新输入！\n");
			getchar();   //假设输入的不是一个数字，scanf只会读取数字的部分，也就是说\n是"留在terminal上的"。通过getchar清除\n
			break;
		}
	}
	return 0;
}
//超市商品管理系统菜单
void menu()
{

	printf("===================商品信息管理系统==================\n");
	printf("*                                                  *\n");
	printf("*          1. 添加商品信息                         *\n");
	printf("*          2. 删除商品信息                         *\n");
	printf("*          3. 修改商品信息                         *\n");
	printf("*          4. 查看单个商品信息                     *\n");
	printf("*          5. 显示所有商品信息                     *\n");
	printf("*          0. 退出管理系统                         *\n");
	printf("*                                                  *\n");
	printf("=====================================================\n");
}

void Add()
{
	int n, i, m;
	printf("请输入要添加的商品序号!\n");
	scanf("%d", &n);
	for (i = 0; i < count; i++)
	{
		if (n == goods[i].id)
		{
			system("cls");	//清理cmd（运行命令提示窗口）
			printf("该商品序号已存在!\n");
			return;//无返回值
		}
	}
	goods[count].id = n;
	printf("请输入要添加的商品名称!\n");
	scanf("%s", goods[count].name);
	printf("请输入要添加的商品价格!\n");
	scanf("%lf", &goods[count].price);
	printf("请输入要添加的商品日期!\n");
	scanf("%d", &goods[count].date);
	printf("请输入要添加的商品厂家!\n");
	scanf("%s", goods[count].vender);
	printf("请输入要添加的商品牌子!\n");
	scanf("%s", goods[count].brand);
	count++;
	printf("该商品信息添加成功!\n");
	printf("是否要继续添加？ 是......1，否......2\n");
	scanf("%d", &m);
	if (m == 1)
	{
		Add();
	}
	else {
		system("cls");	//清理cmd（运行命令提示窗口）
	}
	//这个不需要
	//else if (m == 2)
	//{
	//	return;
	//}
}

void Del()
{
	int found = 0;  //确保我们能找到商品的序号，初始值是0也就是还没找到。0=没找到，1=找到了， 2=找到了，但是用户不想删掉了
	int n, p;
	int i, j;
	printf("请输入要删除商品的序号!\n");
	scanf("%d", &n);
	
	//先确保商品存在
	for (i = 0; i < count; i++)
	{
		if (n == goods[i].id)
		{
			printf("请认真考虑是否要删除？ 是......1，否......2\n");
			scanf("%d", &p);
			if (p == 1)//确定要删除
			{
				found = 1;//找到商品了
				for (j = i; j < count - 1; j++)
				{
					goods[j] = goods[j + 1];
				}
			}
			else {//不确定要删除
				found = 2;
			}
			//商品找到了，循环可以结束了
			break;
		}
	}

	if (found == 1) {//如果找到商品了
		count--;
		system("cls");	//清理cmd（运行命令提示窗口）
		printf("删除成功！\n");
	}
	else if (found == 2) {
		system("cls");	//清理cmd（运行命令提示窗口）
		printf("删除失败，用户不想删除！\n");
	}
	else if (found == 0) {
		system("cls");	//清理cmd（运行命令提示窗口）
		printf("找不到序号为%d的商品！\n",n);
	}


	
	//这个不需要
	//else if (p == 2)
	//{
	//	return;
	//}

}

void Change()
{
	int found = 0;   //确保我们能找到商品的序号，初始值是0也就是还没找到
	int n, i;
	printf("请输入要修改商品的序号!\n");
	scanf("%d", &n);
	for (i = 0; i < count; i++)
	{
		if (n == goods[i].id)
		{
			found = 1;
			printf("请输入要修改的商品名称!\n");
			scanf("%s", goods[i].name);
			printf("请输入要修改的商品价格!\n");
			scanf("%lf", &goods[i].price);
			printf("请输入要修改的商品日期!\n");
			scanf("%d", &goods[i].date);
			printf("请输入要修改的商品厂家!\n");
			scanf("%s", &goods[i].vender);
			printf("请输入要修改的商品牌子!\n");
			scanf("%s", &goods[i].brand);
		}
	}

	if (found) {//如果找到商品了
		system("cls");	//清理cmd（运行命令提示窗口）
		printf("修改成功！\n");
	}
	else{
		system("cls");	//清理cmd（运行命令提示窗口）
		printf("找不到序号为%d的商品！\n", n);
	}
}

void Find()
{
	int n, i, num;
	char sp[10] = { 0 };
	int flag = 0;
	printf("**********请选择查询方式！***********\n");
	printf("**********1.通过商品序号***********\n");
	printf("**********2.通过商品名称***********\n");
	printf("*******************************\n");
	scanf("%d", &num);
	if (num == 1)
	{
		printf("请输入要查看商品的序号!\n");
		scanf("%d", &n);
		for (i = 0; i < count; i++)
		{
			if (n == goods[i].id) // 如果需要查看的商品序号和添加进去的商品序号相同 
			{
				flag = 1;
				flag = 1;
				printf("该商品信息为：\n");
				printf("商品序号:%d   ", goods[i].id);
				printf("商品名称:%s   ", goods[i].name);
				printf("商品价格:%.2f   ", goods[i].price);
				printf("商品日期:%d   ", goods[i].date);
				printf("商品厂家:%s   ", goods[i].vender);
				printf("商品牌子:%s   \n", goods[i].brand);
				
				break;//循环可以结束了，因为id具有唯一性，所以如果找到了，那么不再会有另外一个商品有同样的id
			}
		}
	}
	else if (num == 2)
	{
		printf("请输入要查看商品的名称!\n");
		scanf("%s", sp);
		for (i = 0; i < count; i++)
		{
			if (0 == strcmp(sp, goods[i].name))// 如果需要查看的商品名称和添加进去的商品名称相同 
			{
				flag = 1;
				printf("该商品信息为：\n");
				printf("商品序号:%d   ", goods[i].id);
				printf("商品名称:%s   ", goods[i].name);
				printf("商品价格:%.2f   ", goods[i].price);
				printf("商品日期:%d   ", goods[i].date);
				printf("商品厂家:%s   ", goods[i].vender);
				printf("商品牌子:%s   \n", goods[i].brand);

				//这里循环不结束，因为name不具有唯一性，所以有可能有更多一样名称的商品
			}
		}
	}

	if (flag == 0)
	{
		system("cls");	//清理cmd（运行命令提示窗口）
		printf("查无此商品,返回主菜单！\n");
	}
	else {//如果找到商品了
		getchar();//确保没有任何残留的input值
		printf("\n请按回车键会主菜单\n");
		getchar();//等待用户按回车键
		system("cls");	//清理cmd（运行命令提示窗口）
	}
}

void Showall()
{
	system("cls");	//清理cmd（运行命令提示窗口）

	printf("共有%d个商品信息\n", count);
	for (int i = 0; i < count; i++)
	{
		printf("商品序号:%d   ", goods[i].id);
		printf("商品名称:%s   ", goods[i].name);
		printf("商品价格:%.2f   ", goods[i].price);
		printf("商品日期:%d   ", goods[i].date);
		printf("商品厂家:%s   ", goods[i].vender);
		printf("商品牌子:%s   \n", goods[i].brand);

	}

	getchar();//确保没有任何残留的input值
	printf("\n请按回车键会主菜单\n");
	getchar();//等待用户按回车键
	system("cls");	//清理cmd（运行命令提示窗口）
}
