#include<iostream>
#include<string>
#include<cstring>
#include<cctype>




//================전역 변수=======================

char oper;
int intNum1;
int intNum2;
int fltNum1;
int fltNum2;

using namespace std;
void analyzeInput(string &input);
int main()

{
	string inputExpr;

	cout << "======각 피연산자는 띄어쓰기로 구분합니다.======\n"

		<< "======띄어쓰기를 올바르게 입력해 주시길바랍니다.======\n" << endl;

	cout << "계산할 식을 입력하시오 -> ";

	getline(cin, inputExpr);
	analyzeInput(inputExpr);

	switch (oper)

	{
	case '+':
		break;
	case '-':
		break;
	case '/':
		break;
	case '*':
		break;
	}

	return 0;

}

void analyzeInput(string &input){



	const string OPERATORS = "+-*/";
	
	int midIdx = input.length() / 2;
	
	if (input.find("i") != string::npos){

		//이것은 복소수 식이다.

		int midIdx = input.length() / 2;

		string subExpr1 = input.substr(0, midIdx - 2);				//첫번째 인덱스 ~ 연산자의 앞까지의 부분 식 즉 첫번째 복소수식
		string subExpr2 = input.substr(midIdx + 2, input.length());	//두번째 복소수식

		int imgIdx1 = subExpr1.find("i");					//첫번째 복소수 식의 i의 인덱스
		int imgIdx2 = subExpr2.find("i");					//두번째 복소수 식의 i의 인덱스

	}
	else {

		//실수 끼리의 계산 일 수도 있고 정수 끼리의 계산일 수도 있다.
		int i;

		for (i = 0; i < input.length(); i++){
			if (OPERATORS.find(input[i]) != string::npos){
				break;
			}
		}

		int operIdx = i;
		oper = input[operIdx];								//operIdx가 가진 값의 인덱스 값으로 연산자를 추출한다.

		string sub1 = input.substr(0, operIdx - 1);
		string sub2 = input.substr(operIdx + 2, input.length());

		char *temp1 = (char*)sub1.c_str();
		char *temp2 = (char*)sub2.c_str();

		//sub1,2는 연산자를 중심으로 실수,정수를 추출하기 위한 입력의 subString이다
		//1보다 크면 실수를 나타냄 실수인경우는 실수변수에 저장하고 정수이면 정수 변수에 저장한다.
		if (sub1.length() > 1){
			fltNum1 = atof(temp1);
		}
		else {
			intNum1 = atoi(temp1);
		}
		if (sub2.length() > 1){
			fltNum2 = atof(temp2);
		}
		else {
			intNum2 = atoi(temp2);
		}
	}
}