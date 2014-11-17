#include<iostream>
#include<string>
#include<cstring>
using namespace std;
//================전역 변수==================================================
char oper;
class Floating{
public:
	double data;

	void print(){
		cout << data << endl;
	}

	//연산자 오버로딩
	Floating operator+(const Floating &refClass){
		Floating temp;
		temp.data = data + refClass.data;
		return temp;
	}
	Floating operator-(const Floating &refClass){
		Floating temp;
		temp.data = data - refClass.data;
		return temp;
	}
	Floating operator/(const Floating &refClass){
		Floating temp;
		temp.data = data / refClass.data;
		return temp;
	}
	Floating operator*(const Floating &refClass){
		Floating temp;
		temp.data = data + refClass.data;
		return temp;
	}
};
class Complex
{
public:
	double real;		// 실수부
	double imag;		// 허수부
public:
	/*
	Complex();
	Complex(double a, double b){
		real = a;
		imag = b;
	}
	*/
	void printComp(){
		cout << real << " + " << imag << "i" << endl;
	};
	Complex operator+(Complex &refComplex){
		Complex temp;
		temp.real = this->real + refComplex.real;
		temp.imag = this->imag + refComplex.imag;
		return temp;
	};

	Complex operator-(Complex &refComplex){
		Complex temp;
		temp.real = real - refComplex.real;
		temp.imag = real - refComplex.imag;
		return temp;
	};
};
Floating fa, fb, fc;
Complex  com1, com2, com3;
bool complexFlag;
//===========================================================================
void analyzeInput(string &input);
//===========================================================================
int main()
{
	string inputExpr;
	complexFlag = false;

	cout << "※ 각 피연산자 및 연산자는 띄어쓰기로 구분합니다.\n"
		 << "※ 띄어쓰기를 올바르게 입력해 주시길바랍니다.\n"
		 << "※ 복소수 식을 입력할때 두식 모두 괄호를 입력하거나 둘다 입력하지 않아야 합니다."
		 << "※ 식을 올바르게 입력하지 않을경우 프로그램이 제대로 동작하지 않습니다.\n" << endl;
	cout << "계산할 식을 입력하시오 -> ";

	getline(cin, inputExpr);		//입력을 한줄로 다 받아서 스트링으로 처리함
	analyzeInput(inputExpr);		//입력받은 식을 분석함

	cout << "출력 결과 : ";

	switch (oper)
	{
	case '+':
		if (complexFlag == true){
			com1 = com2 + com3;
			com1.printComp();
		} else{
			fc = fa + fb;
			fc.print();
		}
		break;
	case '-':
		if (complexFlag == true){
			com1 = com2 - com3;
			com1.printComp();
		} else{
			fc = fa - fb;
			fc.print();
		}
		break;
	case '/':
		fc = fa / fb;
		fc.print();
		break;
	case '*':
		fc = fa * fb;
		fc.print();
		break;
	}

	return 0;

}

void analyzeInput(string &input){

	const string OPERATORS = "+-*/";
	int i, j, operIdx = -1;
	int midIdx = input.length() / 2;
	bool braketFlag = false;

	if (input.find("i") != string::npos){				//i가 문자열에 존재한다는 것은 이식은 복소수식임
		//복소수식에서는 연산자가 총 3개 나올수 있다, 그 중 2번재 연산자의 인덱스를 찾는다.
		//2번째 연산자의 인덱스를 중심으로 앞 뒤로 구분한다.
		for (i = 0; i < 2; i++){
			for (int j = operIdx + 1; j < input.length(); j++){
				if (OPERATORS.find(input[j]) != string::npos){
					operIdx = j;
					break;
				}
			}
		}

		oper = input[operIdx];

		string subExpr1 = input.substr(0, operIdx - 1);				//첫번째 인덱스 ~ 연산자의 앞까지의 부분 식 즉 첫번째 복소수식
		string subExpr2 = input.substr(operIdx + 2, input.length());	//두번째 복소수식

		int imgIdx1 = subExpr1.find("i");					//첫번째 복소수 식의 i의 인덱스
		int imgIdx2 = subExpr2.find("i");					//두번째 복소수 식의 i의 인덱스

		for (i = 0; i < subExpr1.length(); i++){
			if (OPERATORS.find(subExpr1[i]) != string::npos){
				break;
			}
		}
		for (j = 0; j < subExpr1.length(); j++){
			if (OPERATORS.find(subExpr2[j]) != string::npos){
				break;
			}
		}
		int subOper1 = i;									//첫번째 복소수 식의 연산자의 인덱스
		int subOper2 = j;									//두번째 복소수 식의 연산자의 인덱스

		int subStart1, subStart2;

		if (input[0] == '(') { braketFlag = true; }			//괄호에 식이 있는지 체크

		if (braketFlag == true){
			subStart1 = subStart2 = 1;
		} else {
			subStart1 = subStart2 = 0;
		}
		//서브스트링들을 연산자를 중심으로 분리한다.
		string temp,temp2,temp3,temp4;
		char *number1, *number2, *img1, *img2;

		temp = subExpr1.substr(subStart1, subOper1 - 1);									//		| temp는 복소수의 실수 |
		number1 = (char*)temp.c_str();									
		temp2 = subExpr1.substr((subOper1 + 1), imgIdx1 - (subOper1+1));					//		| temp2는 허수	|
		img1 = (char*)temp2.c_str();
		temp3 = subExpr2.substr(subStart2, subOper2 - 1);								//		| temp3는 뒷 복소수의 실수 |
		number2 = (char*)temp3.c_str();
		temp4 = subExpr2.substr((subOper2 + 1), imgIdx2 - (subOper2+1));					//		| temp4은 허수	|
		img2 = (char*)temp4.c_str();

		float real1, real2, imag1, imag2;
		real1 = atof(number1);
		real2 = atof(number2);
		imag1 = atof(img1);
		imag2 = atof(img2);

		//마지막으로 서브스트링들의 oper를 통하여서 허수부의 음수 양수 구분함
		if (subExpr1[subOper1] == '-'){ imag1 = 0 - imag1; }
		if (subExpr2[subOper2] == '-'){ imag2 = 0 - imag2; }

		complexFlag = true;			//이 bool형을 통하여 복소수 연산인지 실수의 연산인지 구분한다.

		
		com2.real = real1;
		com2.imag = imag1;
		
		com3.real = real2;
		com3.imag = imag2;
		
	} else {
		//실수 끼리의 계산 일 수도 있고 정수 끼리의 계산일 수도 있다.
		for (i = 0; i < input.length(); i++){
			if (OPERATORS.find(input[i]) != string::npos){
				break;
			}
		}
		int operIdx = i;
		oper = input[operIdx];								//operIdx가 가진 값의 인덱스 값으로 연산자를 추출한다.

		string sub1 = input.substr(0, operIdx - 1);
		string sub2 = input.substr(operIdx + 2, input.length()-operIdx);

		char *temp1 = (char*)sub1.c_str();
		char *temp2 = (char*)sub2.c_str();

		//sub1,2는 연산자를 중심으로 실수,정수를 추출하기 위한 입력의 subString이다
		fa.data = atof(temp1);
		fb.data = atof(temp2);
	}
}
