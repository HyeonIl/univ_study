#include <stdio.h>

int binSearch(int arr[],int first, int last, int target)
{
	int mid;  //2로 나눌 변수 지정

	if(first>last)
		return -1;			//first와 last의 값이 역전되었을때 -1 리턴..

	mid = (first+last)/2;	//first와 last 값을 더해 2로 나누어서 가운데 값을 인덱스로 설정;

		if(target == arr[mid])		//mid인덱스의 값과 타겟의 값이 같다면 
			return mid;				//그 값의 인덱스 값을 리턴
		else if(target < arr[mid])	//target의 값과 mid인덱스의 값을 비교한다
			return binSearch(arr,first,mid-1,target);	//그래서 target값이 작다면 왼쪽을 탐색
		else
			return binSearch(arr,mid+1,last,target);	//그렇지 않다면 오른쪽으로 탐색

}
int main()
{
	int numArr[6] = {1,3,5,7,9,10};

	printf("이진탐색 스타또\n");
	puts("====================================");

	printf("배열의 %d번째에 값존재\n",binSearch(numArr,0,(sizeof(numArr)/sizeof(int))-1,7)+1);

	return 0;
}