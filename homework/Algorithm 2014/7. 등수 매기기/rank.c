#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 300
#define NAME_MAX 30

//===============����ü ����=========================
typedef struct student{
	char name[NAME_MAX];
	int score;
	int rank;
}Student;
//==============��������==============================
FILE *input, *output;
Student students[MAX];
int number;
//===================================================
int scoreCompare(const void *val1, const void *val2);
int nameCompare(const void *val1, const void *val2);
void makeRank();
//===================================================
int main()
{
	int i;

	input = fopen("rank.inp", "r");
	output = fopen("rank.out", "w");

	fscanf(input, "%d", &number);

	for (i = 0; i < number; i++){
		fscanf(input, "%s %d", &students[i].name, &students[i].score);
	}

	//������ �������� �迭 ����
	qsort(students, number, sizeof(Student), scoreCompare);

	//���ĵ� ���� �������� ������ �ű��.
	makeRank();

	//�̸��� �������� �ٽ� ����
	qsort(students, number, sizeof(Student), nameCompare);

	for (i = 0; i < number; i++){
		fprintf(output, "%s %d %d\n", students[i].name, students[i].score, students[i].rank);
	}

	fclose(input);
	fclose(output);
	return 0;
}
void makeRank(){
	int i;

	for (i = 0; i < number; i++){
		if (students[i].score == students[i - 1].score){
			students[i].rank = students[i-1].rank;
		} else
			students[i].rank = i + 1;
	}
}
int scoreCompare(const void *val1, const void *val2){
	int score1, score2;

	score1 = ((Student*)val1)->score;
	score2 = ((Student*)val2)->score;

	//������������ �����Ѵ�. ���� ���� ���� �� Ŭ�� ������ �����ϸ� �������� �����̵ȴ�.
	if (score1 > score2)
		return -1;
	else if (score1 < score2)
		return 1;
	else
		return 0;
}
int nameCompare(const void *val1, const void *val2){
	return strcmp(((Student*)val1)->name, ((Student*)val2)->name);
}
