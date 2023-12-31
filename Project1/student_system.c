﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct STUDENT {
	int id;
	char name[50];
	int scores[3];
	float averageScore;
};

void saveSTU(struct STUDENT stu) { //学生信息作为参数
	FILE* scoreFile = fopen("score.txt", "a"); //打开文件
	if (scoreFile != NULL) {					//确保文件能打开
		//储存信息
		fprintf(scoreFile, "%d ", stu.id);
		fprintf(scoreFile, "%s ", stu.name);
		for (int i = 0; i < 3; i++)
			fprintf(scoreFile,"%d ", stu.scores[i]);
		fprintf(scoreFile,"%.6f \n", stu.averageScore);

		fclose(scoreFile);//关闭文件
		printf("学生输入成功!\n");
	}
	else {
		printf("文件打开失败\n");
	}
}

struct STUDENT* readSTU(int* size) {  //学生数量作为参数（注意这里的参数是一个指针，也就是说这个函数可以改变size在外部的数据）    这个函数返回的是STUDENT指针，也就是说可以通过下标找到第n个学生的信息
	FILE* scoreFile = fopen("score.txt", "r"); //打开文件
	if (scoreFile == NULL) { //如果打开失败
		printf("文件打开失败.\n");
		return NULL; //返回空值
	}

	*size = 0;
	char temp;
	while ((temp = fgetc(scoreFile)) != EOF) {//读取文件里的字符
		if (temp == '\n') {						/*如果当前值为\n,那么也就是说我们读取到了一行的结尾*/
			(*size)++;//每一行代表着一个学生，所以size + 1
		}
	}
	
	struct STUDENT* students = malloc(*size * sizeof(struct STUDENT)); //赋予内存

	if (students == NULL) { //如果赋予失败
		printf("读取内存失败\n");
		fclose(scoreFile);
		return NULL;
	}

	rewind(scoreFile); //从头开始读取scorefile
	for (int i = 0; i < *size; i++){
		//读取学生信息
		fscanf(scoreFile, "%d", &students[i].id);
		fscanf(scoreFile, "%s", students[i].name);
		for (int j = 0; j < 3; j++) {
			fscanf(scoreFile, "%d", &students[i].scores[j]);
		}
		fscanf(scoreFile, "%f", &students[i].averageScore);
	}

	fclose(scoreFile);
	
	return students;
}

void insertSTU(int n) {	
	while (n--) {							//循环n遍
		struct STUDENT currSTU;				//储存学生信息
		currSTU.averageScore = 0;			//赋予初始值

		printf("请输入学生学号：");
		scanf("%d", &currSTU.id);
		printf("请输入学生姓名：");
		scanf("%s", currSTU.name);
		for (int i = 0; i < 3; i++) {
			printf("请输入学生第%d门课成绩：",i + 1);
			scanf("%d", &currSTU.scores[i]);
			currSTU.averageScore += currSTU.scores[i];
		}

		currSTU.averageScore /= 3.0;
		saveSTU(currSTU);				//储存学生信息
	}
}

void showSTU() {
	int size; //定义一个空的变量，这个变量会根据学生的数量而改变
	struct STUDENT* students = readSTU(&size); //通过readSTU函数读取学生信息

	for (int i = 0; i < size; i++) {
		//显示学生信息
		printf("学号:%d  ", students[i].id);
		printf("姓名:%s  ", students[i].name);
		for (int j = 0; j < 3; j++)
			printf("第%d门课成绩:%d  ", i + 1, students[i].scores[j]);
		printf("平均分: %.6f\n", students[i].averageScore);
	}

	free(students); //释放内存空间
}

void findSTU(char* name) {
	int size;	//定义一个空的变量，这个变量会根据学生的数量而改变
	struct STUDENT* students = readSTU(&size); //通过readSTU函数读取学生信息

	int found = 0;

	for (int i = 0; i < size; i++) {
		if (strcmp(students[i].name, name) == 0) {
			//显示学生信息
			printf("学号:%d  ", students[i].id);
			printf("姓名:%s  ", students[i].name);
			for (int j = 0; j < 3; j++)
				printf("第%d门课成绩:%d  ", i + 1, students[i].scores[j]);
			printf("平均分: %.6f\n", students[i].averageScore);

			//找到学生了
			found = 1;
		}
	}

	if (!found)//如果学生没找到
		printf("此学生不存在");

	free(students); //释放内存空间
}

void sortSTU() {
	int size;
	struct STUDENT* students = readSTU(&size);

	//选择排序
	for (int i = 0; i < size; i++)
	{
		int maxAverageScoreIndex = i;
		for (int j = i + 1; j < size; j++)
			if (students[j].averageScore > students[maxAverageScoreIndex].averageScore)
				maxAverageScoreIndex = j;

		if (maxAverageScoreIndex != i) {
			struct STUDENT temp = students[i];
			students[i] = students[maxAverageScoreIndex];
			students[maxAverageScoreIndex] = temp;
		}
	}

	//删除文件里原有的信息
	FILE* file = fopen("score.txt", "w");
	fclose(file);
	//更新文件
	for (int i = 0; i < size; i++)
		saveSTU(students[i]);
	free(students); //释放内存空间
}

void insertSTU2() {
	sortSTU();
	int size, i;
	struct STUDENT* students = readSTU(&size);

	struct STUDENT newSTU;						//储存新的学生信息
	newSTU.averageScore = 0;					//赋予初始值

	printf("请输入学生学号：");
	scanf("%d", &newSTU.id);
	printf("请输入学生姓名：");
	scanf("%s", newSTU.name);
	for (i = 0; i < 3; i++) {
		printf("请输入学生第%d门课成绩：", i + 1);
		scanf("%d", &newSTU.scores[i]);
		newSTU.averageScore += newSTU.scores[i];
	}

	newSTU.averageScore /= 3.0;

	//要加一个学生，所以size++
	size++;
	//从新给students内存
	students = realloc(students, (size) * sizeof(struct STUDENT));

	//对比, size - 1 因为我们在上面那行size++。但是目前来说最后一个元素是空的
	for (i = 0; i < size - 1; i++) {
		if (students[i].averageScore < newSTU.averageScore) {
			//如果student[i]的平均值小于新的学生，那么从i开始往后移一格
			int j;
			for (j = size - 1; j > i; j--)//从最后一个开始移
				students[j] = students[j - 1];
			
			//插入新学生
			students[i] = newSTU;
		}
	}


	//删除文件里原有的信息
	FILE* file = fopen("score.txt", "w");
	fclose(file);
	//更新文件
	for (int i = 0; i < size; i++)
		saveSTU(students[i]);
	free(students); //释放内存空间
}

void menu()
{
	int command;							//command = 命令
	int n, pos;								//n 是学生人数, pos是学生位置
	char name[50];							//name 是学生姓名

	printf("\n\n");
	printf("\t\t\t===================成绩记录薄==================\n");
	printf("\t\t\t*                                                   *\n");
	printf("\t\t\t*          1>. 录入学生信息                         *\n");
	printf("\t\t\t*          2>. 显示学生信息                         *\n");
	printf("\t\t\t*          3>. 查找学生信息                         *\n");
	printf("\t\t\t*          4>. 排序学生信息                         *\n");
	printf("\t\t\t*          5>. 插入学生信息                         *\n");
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
		printf("请输入您要录入的学生人数:");
		scanf("%d", &n);
		insertSTU(n);							//输入学生信息
		getchar();
		printf("\n请按回车主菜单\n");
		getchar();
		system("cls");
		break;
	case 2:
		showSTU();						      //显示学生信息       
		getchar();
		printf("\n请按回车主菜单\n");
		getchar();
		system("cls");
		break;
	case 3:
		printf("请输入您要查找的学生姓名:");
		scanf("%s", name);
		findSTU(name);                         //查找学生信息     
		getchar();
		printf("\n请按回车主菜单\n");
		getchar();
		system("cls");
		break;
	case 4:
		sortSTU();							  //排序学生信息
		getchar();
		printf("\n请按回车主菜单\n");
		getchar();
		system("cls");
		break;
	case 5:
		insertSTU2();							//插入学生信息
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
	while(1)
		menu();
}
