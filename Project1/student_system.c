#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct STUDENT {
	int id;
	char name[50];
	int scores[3];
	float averageScore;
};

void saveSTU(struct STUDENT stu) {
	FILE* scoreFile = fopen("score.txt", "a");
	if (scoreFile != NULL) {
		fprintf(scoreFile, "%d ", stu.id);
		fprintf(scoreFile, "%s ", stu.name);
		for (int i = 0; i < 3; i++)
			fprintf(scoreFile,"%d ", stu.scores[i]);
		fprintf(scoreFile,"%.6f \n", stu.averageScore);


		fclose(scoreFile);
		printf("学生输入成功!\n");
	}
	else {
		printf("文件打开失败\n");
	}
}

struct STUDENT* readSTU(int* size) {
	FILE* scoreFile = fopen("score.txt", "r");
	if (scoreFile == NULL) {
		printf("文件打开失败.\n");
		return NULL;
	}

	// Count the number of lines in the file
	*size = 0;
	char temp;
	while ((temp = fgetc(scoreFile)) != EOF) {
		if (temp == '\n') {
			(*size)++;
		}
	}
	
	struct STUDENT* students = malloc(*size * sizeof(struct STUDENT));

	if (students == NULL) {
		printf("Memory allocation failed.\n");
		fclose(scoreFile);
		return NULL;
	}

	rewind(scoreFile);
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
		saveSTU(currSTU);
	}
}

void showSTU() {
	int size;
	struct STUDENT* students = readSTU(&size);

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
	int size;
	struct STUDENT* students = readSTU(&size);

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

	//Selection  sort
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

void insertSTU2(int pos) {
	int size;
	struct STUDENT* students = readSTU(&size);

	if (pos >= size) {
		insertSTU(1);
		free(students); //释放内存空间

		return;				//结束这个函数
	}

	//加了一个学生，所以size++
	size++;
	//从新给students内存
	students = realloc(students, (size) * sizeof(struct STUDENT));

	//从pos到最后一个的学生都往后移一格
	for (int i = size - 1; i > pos; i--)
		students[i] = students[i - 1];
	

	//加一个学生
	students[pos].averageScore = 0;			//赋予初始值

	printf("请输入学生学号：");
	scanf("%d", &students[pos].id);
	printf("请输入学生姓名：");
	scanf("%s", students[pos].name);
	for (int i = 0; i < 3; i++) {
		printf("请输入学生第%d门课成绩：", i + 1);
		scanf("%d", &students[pos].scores[i]);
		students[pos].averageScore += students[pos].scores[i];
	}
	students[pos].averageScore /= 3.0;

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
		printf("请输入插入学生的位置(0是第一个位置）:");
		scanf("%d", &pos);
		insertSTU2(pos);							//插入学生信息
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
