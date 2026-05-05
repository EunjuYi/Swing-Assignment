#include <iostream>
using namespace std;

class CoffeeMachine {
private:
	//멤버 변수
	int water;
	int beans;
	bool isOn;

public:
	//생성자
	CoffeeMachine(); //기본 생성자 선언
	CoffeeMachine(int w, int b); //사용자 지정 생성자 선언

	//멤버 함수
	void powerOn();
	void checking();
	void refill();
	void makeEspresso();


	//소멸자
	~CoffeeMachine();
};

//생성자 (기본 / 사용자 지정) 정의 -----------------------
CoffeeMachine::CoffeeMachine() {
	water = 100;
	beans = 50;
	isOn = false;
}

CoffeeMachine::CoffeeMachine(int w, int b) {
	water = w;
	beans = b;
	isOn = false;
}

//멤버 함수 정의 -----------------------------------------
void CoffeeMachine::powerOn() {
	isOn = true;
	cout << "---커피 머신 ON---" << endl;
	cout << endl;
}

void CoffeeMachine::checking() {
	cout << "[현재 재료 상태]" << endl;
	cout << "[물: " << water << "ml]" << endl;
	cout << "[원두: " << beans << "g]" << endl;
	cout << endl;
}

void CoffeeMachine::refill() {
	int refillWater;
	int refillBeans;

	cout << "리필할 물 양 (ml): ";
	cin >> refillWater;
	water += refillWater;

	cout << "리필할 원두 양 (g): ";
	cin >> refillBeans;
	beans += refillBeans;
	cout << endl;
}

void CoffeeMachine::makeEspresso() {
	if (!isOn) {
		cout << "머신의 전원을 먼저 켜주세요." << endl;
		cout << endl;
		return;
	}

	if (water >= 30 && beans >= 15) {
		water -= 30;
		beans -= 15;
		cout << "에스프레소 완성." << endl;
	}
	else {
		cout << "물 30ml 이상, 원두 15g 이상이 필요합니다. 확인해주세요." << endl;
	}
	cout << endl;
}

//소멸자 정의 --------------------------------------------
CoffeeMachine::~CoffeeMachine() { //소멸자 정의
	cout << "---커피 머신 OFF---" << endl;
}


int main() {
	CoffeeMachine maker(500, 10);

	maker.makeEspresso();
	maker.powerOn();
	maker.makeEspresso();
	maker.checking();
	maker.refill();
	maker.makeEspresso();
}