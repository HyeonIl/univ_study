#include<stdio.h>
#define TRUE 0

int isPrime(int number);
int main()
{
	int testCase;
	int testNumber;
	int prime;

	FILE *rp = fopen("primefactor.inp","r");
	FILE *wp = fopen("primefactor.out","w");

	fscanf(rp,"%d",&testCase);

	while(testCase--){
		fscanf(rp,"%d",&testNumber);
		prime = isPrime(testNumber);

		if(prime == TRUE){
			fprintf(wp,"Prime Number\n");
		}else{
			fprintf(wp,"%d\n",prime);
		}
	}


	fclose(rp);
	fclose(wp);
}
int isPrime(int number)
{
	int i;
	int total = 0;
	//number변수 값을 받아와서 setNumber변수에 초기화 시켜준다.
	int setNumber = number;

	for(i=2; i<setNumber+1; i++){
		//i가 number와 같아지면 그 숫자는 Prime Number 이므로 break
		if(number == i)	break;
		//setNumber변수를 i로 나누었을때 나머지가 0이라는 것은 나누어지는 소인수가 존재한다는 의미
		//소인수분해는 작은 소인수 순서로 나누어서 계속 쪼개는 것이다.
		if(setNumber%i == 0){
		//total 변수에 i가 가지고 있는 현재 소인수를 더해준다.
		//setNumber 변수에 소인수로 나누어서 다음 소인수를 구하기위해 반복문 setNumber변수를 갱신
		//i도 1로 초기화하여 i++이 되면서 루핑을 돌때 다시 2부터 시작하여 소인수를 구하는 연산을 할 수 있도록 함.
				total += i;
				setNumber = setNumber/i;
				i=1;
			}
		}
	//만약 total에 소인수가 존재하지 않아 초기화 값인 0이라면 이숫자는 Prime Number이므로 TRUE값을 리턴한다.
	//아니라면 소인수들의 합을 리턴함.
	if(total == 0){
		return TRUE;
	}else{
		return total;
	}
}