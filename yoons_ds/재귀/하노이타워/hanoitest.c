#include <stdio.h>

void moveHanoi(int num, char from, char by, char to)
{

	if(num == 1)
		printf("원반 1을 %c에서 %c로 이동 \n",from,to);
	else{
		moveHanoi(num-1,from,to,by);
		printf("원반 %d를 %c에서 %c로 이동\n",num,from,to);
		moveHanoi(num-1,by,from,to);
	}
}

int main()
{
	moveHanoi(4,'A','B','C');
	return 0;
}