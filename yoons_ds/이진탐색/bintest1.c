#include <stdio.h>

int binSearch(int arr[], int length, int target)
{
	int first = 0;	//배열의 첫번째 인덱스
	int last = length-1;	//배열의 마지막 인덱스
	int mid;
	
	while(first<=last)
	{
		mid = (first+last)/2;	//첫번째와 마지막인덱스를 더하여 2를 나누어서 중간 인덱스 맹글어줌
		if(arr[mid] == target){
			return mid;			//만약 중간인덱스와 타겟의 값이 같다면 인덱스 리턴 해서 함수빠져나옴
		}else{
			if(target < arr[mid]){	//타겟값이 중간인덱스 값보다 작을경우 왼쪽으로 탐색 하여야 함!
				last = mid-1;		//따라서 마지막인덱스 값을 중간인덱스에서 -1한 값으로 대입하여서 탐색범위를 줄인다
			}else{
				first=mid+1;		//그 반대일 경우는 첫번째 인덱스 값에 중간 인덱스보다 큰 값을 넣어서 탐색범위를 중간값 보다 큰
			}						//범위로 재설정함.  여기서 -1과 +1을 해주지 않는 다면 while이 무한루프에 빠질수 있음.
		}							//바로 first와 last의 값이 같을때 역전 되어야 while문이 빠져나오는데 역전되지 않음.
	}
	return -1;					//while문을 빠져나왔다면 찾는 값이 존재하지 않는다는 것이므로 -1 리턴
}
int main()
{
	int numArr[6] = {1,3,5,7,9,10};

	printf("이진탐색 스타또\n");
	puts("====================================");

	printf("배열의 %d번째에 값존재\n",binSearch(numArr,6,10)+1);

	return 0;
}