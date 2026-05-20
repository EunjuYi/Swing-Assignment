#include <iostream>
#include <string>
using namespace std;

//Node 구조체 선언
template <typename T> //T라는 가상의 타입 지정
struct Node {
	T data;
	Node<T>* next; //다음 Node의 메모리 주소를 저장하는 포인터 변수 next
};

template <typename T> //T라는 가상의 타입 지정
class GameList {
private:
	Node<T>* head;
	Node<T>* tail;
public:
	GameList() { //처음 생성할 때는 head와 tail을 NULL로 설정하여 비어있도록 초기화
		head = NULL;
		tail = NULL;
	};
	~GameList() { //프로그램이 끝날 때 동적 할당했던 모든 Node들을 차례대로 delete
		Node<T>* current = head; //head부터 시작
		while (current != NULL) {
			Node<T>* nextNode = current->next;
			delete current;
			current = nextNode;
		}
	};
	void add(T game) {
		// 새 노드 생성 및 데이터 세팅
		Node<T>* newNode = new Node<T>;
		newNode->data = game;
		newNode->next = NULL;

		if (head == NULL) { // 리스트가 비어있다면 head와 tail이 동일
			head = newNode;
			tail = newNode;
		}
		else { // 이미 Node가 있다면 맨 뒤에 붙이기
			tail->next = newNode;
			tail = newNode;
		}
	};
	void show() {
		Node<T>* current = head; //head부터 시작
		cout << "\n--- Game List ---" << endl;
		while (current != NULL) {
			cout << "- " << current->data << endl;
			current = current->next; // 다음 Node로 이동
		}
	};
};

int main() {
	GameList<string>* games = new GameList<string>;

	games->add("Minecraft");
	games->add("Stardew Valley");

	string userInput;
	cout << "Add a game: ";
	getline(cin, userInput); //공백 포함 입력 받기
	games->add(userInput);

	games->show();

	delete games;

}