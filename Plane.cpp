#include <iostream>
using namespace std;

void PrintSeats(int [][6], int);
void Reservation(int [][6], int [][6], int [][6], int , int , int);
int IfReserved(int[][6], int[][6], int[][6], int, int, int);
void ChangeSeats(int[][6], int[][6], int[][6], int, int, int, int, int, int);

int main() {
	int menu;

	//1-3 구역의 좌석을 나타낼 2D array 생성
	int fSection[4][6] = { {0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0} };
	int sSection[4][6] = { {0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0} };
	int tSection[4][6] = { {0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0} };

	int adult, child;
	int totalP = 0; //한 번에 예약할 인원
	int money = 0; //총 금액

	do {
		cout << "**비행기 예약 시스템**\n";
		cout << "1. 좌석 예약\n";
		cout << "2. 좌석 변경\n";
		cout << "3. 프로그램 종료\n";
	
		cout << "번호를 입력하세요: ";
		cin >> menu;
		cout << endl;

		//case 1과 2는 내부에서 변수 선언이 가능하도록 각각 {}로 묶어 블록 처리한다.
		switch (menu) {
		case 1: {
			PrintSeats(fSection, 1);
			PrintSeats(sSection, 2);
			PrintSeats(tSection, 3);
			cout << endl;

			cout << "성인 (50000원): ";
			cin >> adult;
			cout << endl;
			cout << "유아 (40000원): ";
			cin >> child;
			cout << endl;

			totalP = adult + child;
			money += adult * 50000 + child * 40000;

			//예약하려는 사람 수 만큼 반복
			int i = 0;
			while (i < totalP) {
				int section, row, col;

				while (true) {
					//구역 입력
					cout << "어떤 구역을 예약하시겠습니까?\n";
					cin >> section;

					if (section < 1 || section > 3) {
						cout << "예약 가능한 구역이 아닙니다.\n\n";
						continue;
					}

					//좌석 입력
					cout << "몇 열, 몇 번째 좌석을 예약하시겠습니까?\n";
					cin >> col >> row;

					if (row < 1 || row > 4 || col < 1 || col > 6) {
						cout << "예약 가능한 좌석이 아닙니다.\n\n";
						continue;
					}

					//인덱스 변환
					row--;
					col--;

					//예약 여부 체크
					if (IfReserved(fSection, sSection, tSection, section, row, col) == 1) {
						cout << "이미 예약되었습니다. 다른 좌석을 선택하세요.\n\n";
						continue;
					}

					Reservation(fSection, sSection, tSection, section, row, col);
					break;
				}

				cout << endl;
				cout << "예약되었습니다.\n\n";

				i++;
			}

			//예약 후 좌석
			PrintSeats(fSection, 1);
			PrintSeats(sSection, 2);
			PrintSeats(tSection, 3);

			cout << endl;
			break;
		}
		case 2: {
			int numChg; //바꿀 좌석의 개수 = 몇 번 반복해야 하는지

			PrintSeats(fSection, 1);
			PrintSeats(sSection, 2);
			PrintSeats(tSection, 3);
			cout << endl;

			cout << "바꿀 좌석의 개수를 입력하세요: ";
			cin >> numChg;

			while (numChg > 0) {
				int currSection, currRow, currCol; //current
				int chgSection, chgRow, chgCol; //changed

				while (true) {
					cout << "현재 좌석과 바꿀 좌석을 입력하세요.\n";
					cout << "현재 좌석(H구역, N열, M번째): ";
					cin >> currSection >> currCol >> currRow;

					//현재 좌석 Validity -------------------------------------------------------------------
					
					//좌석 번호를 잘못 입력한 경우
					if (currSection < 1 || currSection > 3 || currRow < 1 || currRow > 4 || currCol < 1 || currCol > 6) {
						cout << "좌석 번호를 다시 입력해주세요.\n\n";
						continue;
					}

					//인덱스 변환
					currRow--; 
					currCol--;
					
					//예약이 안되어 있는 경우
					if (IfReserved(fSection, sSection, tSection, currSection, currRow, currCol) != 1) {
						cout << "현재 좌석이 틀렸습니다. 다시 입력해주세요.\n\n";
						continue;
					}
					//---------------------------------------------------------------------------------------
					
					cout << "변경 좌석(H구역, N열, M번째): ";
					cin >> chgSection >> chgCol >> chgRow;

					//변경 좌석 Validity --------------------------------------------------------------------
					
					//좌석 번호를 잘못 입력한 경우
					if (chgSection < 1 || chgSection > 3 || chgRow < 1 || chgRow > 4 || chgCol < 1 || chgCol > 6) {
						cout << "좌석 번호를 다시 입력해주세요.\n\n";
						continue;
					}

					//인덱스 변환
					chgRow--;
					chgCol--;

					//현재 좌석과 변경 좌석이 같은 경우
					if (currSection == chgSection && currRow == chgRow && currCol == chgCol) {
						cout << "똑같은 좌석입니다. 다른 좌석을 선택하세요.\n\n";
						continue;
					}
					//변경 좌석이 이미 예약석인 경우
					if (IfReserved(fSection, sSection, tSection, chgSection, chgRow, chgCol) == 1) {
						cout << "이미 예약되었습니다. 다른 좌석을 선택하세요.\n\n";
						continue;
					}
					//---------------------------------------------------------------------------------------

					ChangeSeats(fSection, sSection, tSection, currSection, currRow, currCol, chgSection, chgRow, chgCol);
					break;
				}

				cout << endl;
				cout << "변경되었습니다.\n\n";
				numChg--;
			}

			//변경 후 좌석
			PrintSeats(fSection, 1);
			PrintSeats(sSection, 2);
			PrintSeats(tSection, 3);

			cout << endl;
			break;
		}
		case 3:
			cout << "총 " << money << "원 입니다.\n";
			break;
		}

	} while (menu != 3);
}

void PrintSeats(int seats [][6], int section) {
	cout << "1 2 3   4 5 6  (" << section << "구역)\n";
	cout << "---------------\n";

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++){
			cout << seats[i][j] << " ";
			if (j == 2) {
				cout << "  ";
			}
		}
		cout << endl;
	}
	cout << "---------------\n";
}

//case 1 좌석 예약
void Reservation(int fSection [][6], int sSection [][6], int tSection [][6], int section, int row, int col) {
	if (section == 1) {
		fSection[row][col] = 1;
	}
	else if (section == 2) {
		sSection[row][col] = 1;
	}
	else {
		tSection[row][col] = 1;
	}
}

int IfReserved(int fSection[][6], int sSection[][6], int tSection[][6], int section, int row, int col) {
	int reserved;

	if (section == 1) {
		reserved = fSection[row][col];
	}
	else if (section == 2) {
		reserved = sSection[row][col];
	}
	else {
		reserved = tSection[row][col];
	}

	return reserved;
}

//case 2 좌석 변경
void ChangeSeats(int fSection[][6], int sSection[][6], int tSection[][6], int section1, int row1, int col1, int section2, int row2, int col2) {
	if (section1 == 1) {
		fSection[row1][col1] = 0;
	}
	else if (section1 == 2) {
		sSection[row1][col1] = 0;
	}
	else {
		tSection[row1][col1] = 0;
	}

	if (section2 == 1) {
		fSection[row2][col2] = 1;
	}
	else if (section2 == 2) {
		sSection[row2][col2] = 1;
	}
	else {
		tSection[row2][col2] = 1;
	}
}
