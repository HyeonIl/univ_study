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
	//number���� ���� �޾ƿͼ� setNumber������ �ʱ�ȭ �����ش�.
	int setNumber = number;

	for(i=2; i<setNumber+1; i++){
		//i�� number�� �������� �� ���ڴ� Prime Number �̹Ƿ� break
		if(number == i)	break;
		//setNumber������ i�� ���������� �������� 0�̶�� ���� ���������� ���μ��� �����Ѵٴ� �ǹ�
		//���μ����ش� ���� ���μ� ������ ����� ��� �ɰ��� ���̴�.
		if(setNumber%i == 0){
		//total ������ i�� ������ �ִ� ���� ���μ��� �����ش�.
		//setNumber ������ ���μ��� ����� ���� ���μ��� ���ϱ����� �ݺ��� setNumber������ ����
		//i�� 1�� �ʱ�ȭ�Ͽ� i++�� �Ǹ鼭 ������ ���� �ٽ� 2���� �����Ͽ� ���μ��� ���ϴ� ������ �� �� �ֵ��� ��.
				total += i;
				setNumber = setNumber/i;
				i=1;
			}
		}
	//���� total�� ���μ��� �������� �ʾ� �ʱ�ȭ ���� 0�̶�� �̼��ڴ� Prime Number�̹Ƿ� TRUE���� �����Ѵ�.
	//�ƴ϶�� ���μ����� ���� ������.
	if(total == 0){
		return TRUE;
	}else{
		return total;
	}
}