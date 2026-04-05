#include <iostream>
using namespace std;

void PrintAcc(string[100], int[100], int);
void Deposit(int&, int);
void Withdraw(int&, int);
void Transfer(int[100], int, int, int);



int main()
{
	int menu;

	string name[100];
	int acc[100];
	int count = 0;

	do {
		cout << "============ 은행 계좌 관리 시스템 ============\n";
		cout << "1. 현재 등록된 계좌 리스트 보기\n";
		cout << "2. 신규 계좌 등록\n";
		cout << "3. 입금 및 출금\n";
		cout << "4. 계좌 간 이체\n";
		cout << "5. 프로그램 종료\n";
		cout << "===============================================\n";


		cout << "메뉴 선택: ";
		cin >> menu;
		cout << endl;

		if (menu < 1 || menu > 5) {
			cout << "올바른 번호를 입력해주세요.\n\n";
			continue;
		}

		switch (menu) {
		case 1: //등록된 계좌 리스트
			PrintAcc(name, acc, count);
			break;
		case 2: { //신규 계좌 등록
			cout << "[신규 계좌 등록]\n";
			string accName;
			int balance;

			cout << "등록할 이름 : ";
			cin >> accName;
			name[count] = accName;

			cout << "초기 잔액 : ";
			cin >> balance;
			acc[count] = balance;

			count++;

			cout << "신규 계좌 등록 완료했습니다.\n\n";
			break;
		}
		case 3: { //입금 및 출금
			string findN;
			int index = -1;

			while (true) {
				cout << "조회할 이름을 입력하세요 : ";
				cin >> findN;
			
				for (int i = 0; i < count; i++) {
					if (name[i].compare(findN) == 0) {
						index = i;
						break;
					}
				}
				if (index == -1) {
					cout << "존재하지 않는 사용자입니다. \n\n";
					continue;
				}
				
				break;
			}

			cout << "현재 " << name[index] << "님의 잔액 : " << acc[index] << endl;
			
			int dw; //deposit, withdraw

			while (true) {
				cout << "(1) 입금 | (2) 출금 : ";
				cin >> dw;
				if (dw != 1 && dw != 2) {
					cout << "올바른 번호를 입력하세요 (1 또는 2).\n";
					continue;
				}

				break;
			}

			int money; //거래 금액

			while (true) {
				cout << "거래 금액 입력 : ";
				cin >> money;

				if (dw == 1) {
					Deposit(acc[index], money);
					cout << money << "원 입금 완료했습니다. \n\n";
					break;
				}
				else {
					if (acc[index] < money) {
						cout << "잔액이 부족합니다. \n";
						continue;
					}
					Withdraw(acc[index], money);
					cout << money << "원 출금 완료했습니다. \n\n";
					break;
				}
			}
			break;
		}
		case 4: { //계좌 간 이체
			cout << "[계좌 간 이체]\n";

			string sender;
			string reciever;
			int transfer;
			int indexS = -1;
			int indexR = -1;

			while (true) {
				cout << "보내는 분 이름 : ";
				cin >> sender;
				cout << "받는 분 이름 : ";
				cin >> reciever;
				cout << "이체할 금액 : ";
				cin >> transfer;

				indexS = -1;
				indexR = -1;

				for (int i = 0; i < count; i++) {
					if (name[i] == sender) {
						indexS = i;
					}
					if (name[i] == reciever) {
						indexR = i;
					}
				}

				if (indexS == -1 || indexR == -1) {
					cout << "존재하지 않는 사용자입니다. \n\n";
					continue;
				}
				if (acc[indexS] < transfer) {
					cout << "잔액이 부족합니다. \n";
					continue;
				}

				break;
			}

			Transfer(acc, indexS, indexR, transfer);
			cout << "이체가 완료되었습니다.\n\n";
			break;
		}
		}
	} while (menu != 5);
}

void PrintAcc(string name[100], int acc[100], int count) {
	cout << "---------- [현재 등록된 계좌 리스트] ----------\n";

	if (count == 0) {
		cout << "(등록된 계좌가 없습니다.)\n";
	}
	else {
		for (int i = 0; i < count; i++) {
			cout << i + 1 << ". 이름 : " << name[i] << "	| 잔액 : " << acc[i] << "원\n";
		}
	}

	cout << "-----------------------------------------------\n\n";
}

void Deposit(int& balance, int money) { //Call By Reference + Call By Value
	balance += money;
}

void Withdraw(int& balance, int money) { //Call By Reference + Call By Value
	balance -= money;
}

void Transfer(int* acc, int indexS, int indexR, int transfer) { //Call By Address + Call By Value
	acc[indexS] -= transfer;
	acc[indexR] += transfer;
}
