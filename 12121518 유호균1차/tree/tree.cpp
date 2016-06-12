#include <iostream>
using namespace std;

struct Node {           //Node의 구성
	int elem;           //노드의 번호
	int child_count = 0;    //자식의 갯수
	Node* child;        //자식 노드의 위치
	Node* parent;       //부모 노드의 위치
	Node* sibling;      //형제 노드의 위치
};

class tree {        //tree 구성
private:            //tmp , temp가 붙은 값들은 모두 임시변수 입니다
	Node* root;     //루트노드
	Node* tmp_node; //search를 위한 위치저장용
	int totalNum;   //전체 노드의 수
	int tempX;      //X좌표 출력을 위한 임시변수
	int tempY;      //Y좌표 출력을 위한 임시변수
public:
	tree(); // 생성자
	//~tree(); //소멸자
	void init_tmp_node();                   // 임시변수 tmp_node 초기화
	void set_tmp_node(Node*);               // 임시변수 tmp_node set
	void search_traversal(Node*, int);      // elem값을 받아서 해당함수의 위치를 찾음 서치함수
	void init_tempX();                      // X좌표위치를 찾기위한 임시변수 tempX 초기화
	void add_tempX();                       // tempX 더하는 함수
	void print_tempX();                     // tempX를 출력하는 함수
	void init_tempY();                      // tempY 초기화
	void add_tempY();                       // tempY 더함
	void print_tempY();                     // tempY 출력
	void initRoot(int);                     // Root 초기화
	void insertNode(int, int, int);         // element, 부모, 형제위치를 받아 노드를 추가하는 함수
	void addTotal();                        // 트리의 노드의 총 개수 추가
	void preTravle();                       // 전위순회
	void postTravle();                      // 후위순회
	void print_recursionPreTravle(Node*);   // 전위순회하여 출력
	void print_recursionPostTravle(Node*);  // 후위순회하여 출력
	void search_coordinate(int);            // x, y좌표 출력
	void print_X_coordinate(Node*, int);    // x좌표 출력
	void print_Y_coordinate(Node*, int);    // y좌표 출력
	Node* get_tmp_node();                   // 임시tmp노드 반환
	Node* searchNode(int);                  // elem값을 받아서 노드의 위치를 search하여 반환하는 함수
	Node* getRoot();                        // root위치 반환
	int get_tempY();                        // tempY 반환
	void set_tempY(int);                    // tempY set

};

tree::tree(){                               // 생성자, 변수들 초기화함
	root = NULL;
	init_tempX();
	init_tempY();
	tmp_node = new Node;// 임시노드 생성
	totalNum = 0;
	tempX = 0;
}

void tree::init_tmp_node(){// 임시노드 초기화
	tmp_node = new Node;
	tmp_node->elem = NULL;           //노드의 번호
	tmp_node->child_count = 0;    //자식의 갯수
	tmp_node->child = NULL;;        //자식 노드의 위치
	tmp_node->parent = NULL;;       //부모 노드의 위치
	tmp_node->sibling = NULL;;      //형제 노드의 위치
};
Node* tree::get_tmp_node(){// 임시노드 반환
	return tmp_node;
};
void tree::set_tmp_node(Node* node) // 임시노드 set
{
	tmp_node = node;
};


void tree::init_tempX(){ // 아래부터 set, get, print 함수
	tempX = 0;
}

void tree::add_tempX(){
	tempX++;
}

void tree::print_tempX(){
	cout << tempX;
}

void tree::init_tempY(){
	tempY = 0;
}

void tree::add_tempY(){
	tempY++;
}

void tree::print_tempY(){
	cout << tempY;
}

int tree::get_tempY(){
	return tempY;
}
void tree::set_tempY(int i){
	tempY = i;
}


void tree::addTotal(){
	tree::totalNum += 1;
}

void tree::initRoot(int input_elem) //root 초기화
{
	root = new Node;
	root->elem = input_elem;
	root->child = NULL;
	root->parent = NULL;
	root->sibling = NULL;
	addTotal();
}

void tree::insertNode(int input_elem, int input_parentNum, int input_order)
{
	//부모위치 찾은거에 노드 삽입
	struct Node *tempPtr = new Node;
	tempPtr->elem = input_elem;
	tempPtr->child = NULL;
	tempPtr->parent = searchNode(input_parentNum); //부모노드 찾기


	if (tempPtr->parent->child == NULL)// 부모의 자식이 없다면
	{
		tempPtr->parent->child = tempPtr; // 부모의 자식이 나라고 지정
		tempPtr->sibling = NULL;
	}
	else // 부모의 처음 자식이 존재한다면
	{
		if (input_order == 1){//부모의 자식이 있을때 처음에 넣음
			Node* temp2 = tempPtr->parent->child;
			tempPtr->parent->child = tempPtr;
			tempPtr->sibling = temp2;
		}
		else
		{
			Node* previousNode = tempPtr->parent->child; // 현재 맨처음노드가됌
			for (int i = 1; i < input_order - 1; i++) //내 앞 노드의 위치 찾기
			{
				previousNode = previousNode->sibling; // 직전노드를 찾아서 가리킴
			}
			Node* temp = previousNode->sibling; //임시변수
			previousNode->sibling = tempPtr; //바꾸기
			tempPtr->sibling = temp; //매달기
		}
	}
	tempPtr->parent->child_count++; //부모에 해당하는 자식갯수 늘려줌
	addTotal();
}


//Preorder
void tree::preTravle(){
	Node* root = getRoot(); //루트 찾기
	//cout << root -> elem; //루트 elem 출력
	print_recursionPreTravle(root);
	cout << endl;
}

void tree::postTravle(){ // 후위순회
	Node* root = getRoot(); //루트 찾기
	print_recursionPostTravle(root);    //출력
	cout << endl;
}

void tree::print_recursionPreTravle(Node* tmp){ //재귀함수 전위순회
	cout << tmp->elem << ' ';   //visit
	if (tmp->child != NULL)
		print_recursionPreTravle(tmp->child);
	if (tmp->sibling != NULL)
		print_recursionPreTravle(tmp->sibling);
}

void tree::print_recursionPostTravle(Node* tmp){ //재귀함수 후위순회
	if (tmp->child != NULL)
		print_recursionPostTravle(tmp->child);
	cout << tmp->elem << ' '; // visit
	if (tmp->sibling != NULL)
		print_recursionPostTravle(tmp->sibling);
}

void tree::search_traversal(Node* tmp, int search_elem){ // 재귀로 부모노드 위치 찾음
	if (tmp->child != NULL)
		search_traversal(tmp->child, search_elem);
	if (tmp->sibling != NULL)
		search_traversal(tmp->sibling, search_elem);
	if (tmp->elem == search_elem)
		set_tmp_node(tmp);
}


void tree::print_X_coordinate(Node* tmp, int want_to_know) // tmp 시작노드, want_to_know 찾고자 하는 elem, 후위순회
{
	if (tmp->child != NULL)                                // 일반트리를 이진트리로 변환해 나오는 X좌표는 일반트리를 후위순회한 순서임을 알 수 있다
		print_X_coordinate(tmp->child, want_to_know);
	add_tempX();
	if (tmp->elem == want_to_know)
		print_tempX();  //visit
	if (tmp->sibling != NULL)
		print_X_coordinate(tmp->sibling, want_to_know);
}

void tree::print_Y_coordinate(Node* tmp, int want_to_know) // tmp 시작노드, want_to_know 찾고자 하는 elem
{
	if (tmp->elem == want_to_know)                         // 규칙성을 찾아보았다. 일반트리를 이진트리로 변환해 Y 좌표값을 찾아보면
		print_tempY();                                     // preorder로 부모에서 child로 갈때는 1이 늘어나고 자식으로 갈때도 1이 늘어난다
	if (tmp->child != NULL){                               // 그러나 자식에서 두번째 자식으로는 바로 접근이 불가능하다(노드 설계 때문에)
		add_tempY();                                       // 아이디어는 preorder 순회하며 child로 갈때 1이 늘어나고 자식갈때 1 y좌표를 늘리고
		print_Y_coordinate(tmp->child, want_to_know);      // 자식이 없을때까지 다 찾고 올라왔을때 y좌표값을 자식 수만큼 차감한다
	}
	if (tmp->sibling != NULL){
		add_tempY();
		print_Y_coordinate(tmp->sibling, want_to_know);
	}
	else{
		if (tmp->parent != NULL)
			set_tempY(get_tempY() - tmp->parent->child_count); // 여기가 포인트, 부모에서 자식으로 내려간다음 자식끝까지 찾고자하는 elem을 찾지 못하면
		// 다시 부모로 올라갈때 자식의 갯수만큼 y좌표를 빼주어 y좌표를 맞춘다
	}

}



void tree::search_coordinate(int inputElem) //좌표값 찾는 함수
{
	init_tempX();
	init_tempY();
	print_X_coordinate(getRoot(), inputElem); // X좌표 찾아서 print
	cout << ' ';
	print_Y_coordinate(getRoot(), inputElem); // y좌표 찾아서 print
	cout << endl;
}

Node* tree::getRoot(){ //root 반환
	return root;
}

Node* tree::searchNode(int inputElem){ //elem을 인자로 받아 해당 인자에 해당하는 노드를 찾음
	Node* root = getRoot();
	init_tmp_node(); //임시 노드 초기화
	search_traversal(root, inputElem); //해당 노드 반환하는 함수
	return get_tmp_node();
}

int main() { //인터페이스
	tree tree1; // 트리 클래스 생성
	while (1){ //무한루프 Q에서 종료
		char s = NULL;
		int i1 = NULL, i2 = NULL, i3 = NULL;
		cin >> s;
		if (s == 'I') //I는 값 3개를 더받음
			cin >> i1 >> i2 >> i3;
		else if (s == 'C') // c는 값 1개를 더받음
			cin >> i1;
		else if (s == 'Q')
			break; // 입력이  Q이면 종료
		switch (s)
		{
		case 'I':
			if (i2 == -1 && i3 == -1) // 부모노드와 형제순서의 입력이 -1이면
			{
				tree1.initRoot(i1); // 트리 초기화
			}
			else                                    // 루트를 정의할 경우가 아니라면
				tree1.insertNode(i1, i2, i3);   //새로운노드 입력
			break;
		case 'P':
			tree1.preTravle(); // 전위순회
			break;
		case 'T':
			tree1.postTravle(); // 후위순회
			break;
		case 'C':
			tree1.search_coordinate(i1); // 좌표값 출력
			break;
		default:
			cout << "잘 못 된 값 입 력 " << endl;
		}
	}
	cout << "프 로 그 램 종 료" << endl;

}