#include <iostream>
#include <vector>
using namespace std;

class ShoppingB {
	string productName;
	int price;
	int num;
public:
	ShoppingB() { productName = ""; price = 0; num = 0; }; //기본 생성자
	ShoppingB(string name, int p, int n) { //사용자 지정 변수 생성자
		productName = name;
		price = p;
		num = n;
	}
	string getPName(); //상품 이름 반환
	int getPrice(); //상품 가격 반환
	int getNum(); //상품 개수 반환
	int getTotalP(); //상품에 대해 총 지불해야 하는 가격 반환
};
string ShoppingB::getPName() {
	return productName;
}
int ShoppingB::getPrice() {
	return price;
}
int ShoppingB::getNum() {
	return num;
}
int ShoppingB::getTotalP() {
	return price * num;
}

int main() {
	int menu;

	vector <ShoppingB> sb; //ShoppingB 클래스의 객체를 vector의 요소로 가질 수 있도록 vector sb 생성
	ShoppingB* paid = new ShoppingB[100]; //100개의 객체까지 담을 수 있도록 동적 할당
	int paidCount = 0; //몇 개의 상품이 결제되었는지 세는 변수

	do {
		cout << "======== 쇼핑몰 장바구니 시스템 ========\n";
		cout << "1. 장바구니 담기\n";
		cout << "2. 장바구니 목록 보기\n";
		cout << "3. 결제하기\n";
		cout << "4. 전체 결제 내역 확인\n";
		cout << "5. 프로그램 종료\n";
		cout << ">> 메뉴 선택: ";

		cin >> menu;
		cout << endl;

		if (menu < 1 || menu > 5) { //1~5를 제외한 다른 번호가 menu에 입력될 경우 안내 문구 출력
			cout << "잘못된 번호입니다. 1~5 사이만 입력해주세요.\n\n";
			continue;
		}

		switch (menu) {
		case 1: { //1. 장바구니 담기
			cout << "[장바구니 담기]" << endl;
			string productN;
			int price;
			int num;

			cout << "상품 이름 : ";
			cin >> productN;
			cout << "가격 : ";
			cin >> price;
			cout << "수량 : ";
			cin >> num;

			sb.push_back(ShoppingB(productN, price, num));
			cout << "상품 추가 완료했습니다." << endl << endl;

			break;
		}
		case 2: //2. 장바구니 목록 보기
			cout << "-------- [장바구니 목록] --------" << endl;
			if (!sb.empty()) {
				for (int i = 0; i < sb.size(); i++) {
					cout << "- " << sb.at(i).getPName() << "[" << sb.at(i).getNum() << "개] : " << sb.at(i).getTotalP() << "원 (단가: " << sb.at(i).getPrice() << "원)" << endl;
				}
			}
			else {
				cout << "(장바구니에 담긴 상품이 없습니다.)" << endl;
			}
			cout << "---------------------------------" << endl << endl;
			
			break;
		case 3: { //3. 결제하기
			if (!sb.empty()) {
				int total = 0; //각 상품의 total price를 더한 최종 지불해야 하는 가격

				cout << "-------- [결제 상세 내역] --------" << endl;
				for (int i = 0; i < sb.size(); i++) {
					cout << "- " << sb.at(i).getPName() << "[" << sb.at(i).getNum() << "개] : " << sb.at(i).getTotalP() << "원 (단가: " << sb.at(i).getPrice() << "원)" << endl;
					total += sb.at(i).getTotalP();
				}
				cout << "----------------------------------" << endl;

				cout << "최종 결제 금액 : " << total << "원" << endl;

				char pay; //결제 여부
				do {
					cout << "결제하시겠습니까? (Y/N) : ";
					cin >> pay;

					if (pay != 'Y' && pay != 'y' && pay != 'N' && pay != 'n') { //y 나 n 둘 다 아닌 입력을 받았을 경우, 올바른 입력을 받을 때까지 입력을 재요청
						cout << "잘못된 입력입니다. Y나 N를 입력하세요." << endl;
					}
				} while (pay != 'Y' && pay != 'y' && pay != 'N' && pay != 'n');

				if (pay == 'Y' || pay == 'y') { //Y인 경우
					for (int i = 0;i < sb.size(); i++) {
						if (paidCount < 100) {
							paid[paidCount] = sb.at(i);
							paidCount++;
						}
					}
					sb.clear(); //vector sb 내 요소를 모두 삭제
					cout << "결제가 완료되었습니다. 장바구니를 비웁니다." << endl << endl;
				}
				else { //N인 경우
					cout << "결제가 취소되었습니다." << endl << endl;
				}
			}
			else {
				cout << "(장바구니에 담긴 상품이 없습니다.)" << endl << endl;
			}
			
			break;
		}
		case 4: //4. 전체 결제 내역 확인
			cout << "[주문 상세 내역]" << endl;
			if (paidCount == 0) cout << "(결제 내역이 없습니다.)" << endl;
			else {
				for (int i = 0; i < paidCount; i++) {
					cout << "- " << paid[i].getPName() << "[" << paid[i].getNum() << "개] : " << paid[i].getTotalP() << "원 (단가 : " << paid[i].getPrice() << "원)" << endl;
				}
			}
			cout<< endl;

			break;
		}

	} while (menu != 5); //5. 프로그램 종료

	delete[] paid; //동적 메모리 할당 해제

	cout << "프로그램을 종료합니다." << endl;
}