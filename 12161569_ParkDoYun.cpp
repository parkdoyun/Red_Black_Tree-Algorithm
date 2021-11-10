#include <iostream>
#include <string>

using namespace std;

#define BLACK 0
#define RED 1
#define FOUND 2 // 플래그 변수 값에 사용
#define NOT_FOUND 3 // 플래그 변수 값에 사용

struct node
{
	int ID = -1; // ID, -1 : leaf node
	string name; // 이름
	int capacity; // 용량
	int price; // 가격
	int color = BLACK; // 0 : black, 1 : red
	node *parent = NULL; // parent node
	node *left = NULL; // left child
	node *right = NULL; // right child
};

node *binary_search(int id, node *tmp, int &depth, int &flag); // 이진 탐색 함수
void insert(int id, string name, int capacity, int price); // 등록 함수
void restructure(node *z, node *v, node *w); // restructure 함수
void traversal(node *tmp, int x, int y, int P); // 순회 함수 -> 트리의 모든 node 순회하면서 범위에 맞는 node의 가격 할인
int find_depth(node *tmp); // tmp의 depth 구하는 함수

node *root = NULL; // root 가리키는 포인터

// 알고리즘 설계과제1
// 12161569 컴퓨터공학과 박도윤
// red-black tree

int main()
{
	int inst_n; // 질의의 수
	char inst; // 명령어
	int input_i; // 입력받는 검색 ID
	string input_n; // 입력받는 이름
	int input_c; // 입력받는 용량
	int input_p; // 입력받는 가격

	root = new node; // root

	cin >> inst_n; // 질의의 수 입력

	for (int i = 0; i < inst_n; i++)
	{
		cin >> inst; // 명령어 입력 ('I', 'F', 'R', 'D')
		if (inst == 'I') // 등록
		{
			cin >> input_i >> input_n >> input_c >> input_p;

			insert(input_i, input_n, input_c, input_p); // 등록
		}
		else if (inst == 'F') // 검색
		{
			cin >> input_i;

			int depth = 0;
			int flag; // 찾았는지 플래그 변수
			node *tmp = root;
			node *n = binary_search(input_i, tmp, depth, flag); // 탐색

			// 출력
			if (flag == NOT_FOUND) cout << "NULL\n"; // 못 찾았을 경우
			else cout << depth << ' ' << n->name << ' ' << n->capacity << ' ' << n->price << '\n'; // 찾았을 경우 출력
		}
		else if (inst == 'R') // 업데이트
		{
			cin >> input_i >> input_n >> input_c >> input_p;

			int depth = 0;
			int flag; // 찾았는지 플래그 변수
			node *tmp = root;
			node *n = binary_search(input_i, tmp, depth, flag); // 탐색

			if (flag == NOT_FOUND) cout << "NULL\n"; // 못 찾았을 경우
			else // 찾았을 경우 -> 정보 갱신
			{
				n->name = input_n;
				n->capacity = input_c;
				n->price = input_p;
				cout << depth << '\n';
			}
		}
		else // (inst == 'D') // 할인
		{
			int x, y; // 범위
			int P; // 할인율
			cin >> x >> y >> P;

			traversal(root, x, y, P); // 순회하며 범위에 맞는 node의 가격 할인
		}
	}
	return 0;
}

node *binary_search(int id, node *tmp, int &depth, int &flag) // 이진 탐색 함수
{ // id : 찾고자 하는 ID, tmp : 현재 node 포인터, depth : 현재 node의 depth, flag : 찾았는지 못 찾았는지 확인 플래그
	if (tmp->ID == -1) // 존재하지 않으면 (leaf node 도착했다면)
	{
		flag = NOT_FOUND; // 플래그 설정
		return tmp; // 해당 leaf node return
	}
	if (tmp->ID == id) // 탐색 완료 시
	{
		flag = FOUND; // 플래그 설정
		return tmp; // 찾은 node return
	}
	else if (id < tmp->ID) return binary_search(id, tmp->left, ++depth, flag); // left child
	else return binary_search(id, tmp->right, ++depth, flag); // right child
}

void insert(int id, string name, int capacity, int price) // 등록 함수
{
	int depth = 0;
	int flag; // 찾았는지 확인 플래그
	node *tmp = root;
	node *n = binary_search(id, tmp, depth, flag); // 탐색

	if (flag == NOT_FOUND) // 못 찾았으면 등록
	{
		if (n == root) // root 삽입 시
		{
			n->ID = id;
			n->name = name;
			n->capacity = capacity;
			n->price = price;
			node *left = new node;
			node *right = new node;
			left->parent = n;
			right->parent = n;
			n->left = left;
			n->right = right;
		}
		else // root가 아닐 때
		{
			n->ID = id;
			n->name = name;
			n->capacity = capacity;
			n->price = price;
			n->color = RED;
			node *left = new node;
			node *right = new node;
			left->parent = n;
			right->parent = n;
			n->left = left;
			n->right = right;

			// double red 검사
			node *z = n;

			// z가 root거나 root 바로 밑이라면 종료
			if (z->parent == NULL || z->parent->parent == NULL)
			{
				cout << depth << '\n';
				return;
			}

			node *v = n->parent; // z의 parent node
			node *grand = n->parent->parent; // z의 grandparent node
			node *w = (grand->left == v ? grand->right : grand->left); // v의 sibling

			while (z->color == RED && v->color == RED) // double red
			{
				if (w->color == BLACK) // restructuring
				{
					restructure(z, v, w);
					// depth 갱신
					depth = find_depth(n);
					cout << depth << '\n';
					return;
				}
				else // recoloring
				{
					if (grand != root) grand->color = RED;
					w->color = BLACK;
					v->color = BLACK;
					z->color = RED;

					// 위로 올라가기
					z = grand;

					// z가 root거나 root 바로 밑이라면 종료
					if (z->parent == NULL || z->parent->parent == NULL) break;

					v = z->parent; // z의 parent node
					grand = v->parent; // z의 grandparent node
					w = (grand->left == v ? grand->right : grand->left); // v의 sibling
				}
			}
			
			
		}
	}

	// node의 depth 출력
	cout << depth << '\n';
}

void restructure(node *z, node *v, node *w) // restructure
{
	node *grand = v->parent; // z의 grandparent node
	node *grandgrand = grand->parent; // grand의 parent node
	int gg_chk = -1; // grand가 left child면 0, right child면 1, grandgrand가 없으면 -1 (grand가 root이면)

	if (grandgrand != NULL) // grand가 root가 아니라면
	{
		if (grand == grandgrand->left) gg_chk = 0; // grand가 left child
		else gg_chk = 1; // grand가 right child
	}

	node *t0, *t1, *t2, *t3; // 서브 트리 4개, 이 트리들의 부모 포인터도 전부 갱신 필요

	// 4가지 case 구분
	if (grand->right == v && v->left == z)
	{
		// 서브 트리 설정 (t0, t1, t2, t3)
		t0 = w; t1 = z->left;
		t2 = z->right; t3 = v->right;

		if (gg_chk != -1) // grandgrand node의 자식 포인터 갱신
		{
			if (gg_chk == 0) grandgrand->left = z; // grand가 left child
			else grandgrand->right = z; // grand가 right child
		}
		else root = z; // grand가 root이면 root 포인터 갱신

		// restructuring
		z->parent = grand->parent; z->left = grand; z->right = v; z->color = BLACK;
		grand->parent = z; grand->left = t0; grand->right = t1; grand->color = RED;
		v->parent = z; v->left = t2; v->right = t3; v->color = RED;

		// 서브 트리들의 부모 포인터 갱신
		t0->parent = grand; t1->parent = grand; t2->parent = v; t3->parent = v;
	}
	else if (grand->left == v && v->right == z)
	{
		// 서브 트리 설정
		t0 = v->left; t1 = z->left;
		t2 = z->right; t3 = w;

		if (gg_chk != -1) // grandgrand node의 자식 포인터 갱신
		{
			if (gg_chk == 0) grandgrand->left = z; // grand가 left child
			else grandgrand->right = z; // grand가 right child
		}
		else root = z; // grand가 root이면 root 포인터 갱신 

		// restructuring
		z->parent = grand->parent; z->left = v; z->right = grand; z->color = BLACK;
		v->parent = z; v->left = t0; v->right = t1; v->color = RED;
		grand->parent = z; grand->left = t2; grand->right = t3; grand->color = RED;

		// 서브 트리들의 부모 포인터 갱신
		t0->parent = v; t1->parent = v; t2->parent = grand; t3->parent = grand;
	}
	else if (grand->left == v && v->left == z)
	{
		// 서브 트리 설정
		t0 = z->left; t1 = z->right;
		t2 = v->right; t3 = w;

		if (gg_chk != -1) // grandgrand node의 자식 포인터 갱신
		{
			if (gg_chk == 0) grandgrand->left = v; // grand가 left child
			else grandgrand->right = v; // grand가 right child
		}
		else root = v; // grand가 root이면 root 포인터 갱신

		// restructuring
		v->parent = grand->parent; v->left = z; v->right = grand; v->color = BLACK;
		z->parent = v; z->left = t0; z->right = t1; z->color = RED;
		grand->parent = v; grand->left = t2; grand->right = t3; grand->color = RED;

		// 서브 트리들의 부모 포인터 갱신
		t0->parent = z; t1->parent = z; t2->parent = grand; t3->parent = grand;
	}
	else // grand->right == v && v->right == z
	{
		// 서브 트리 설정
		t0 = w; t1 = v->left;
		t2 = z->left; t3 = z->right;

		if (gg_chk != -1) // grandgrand node의 자식 포인터 갱신
		{
			if (gg_chk == 0) grandgrand->left = v; // grand가 left child
			else grandgrand->right = v; // grand가 right child
		}
		else root = v; // grand가 root이면 root 포인터 갱신

		// restructuring
		v->parent = grand->parent; v->left = grand; v->right = z; v->color = BLACK;
		grand->parent = v; grand->left = t0; grand->right = t1; grand->color = RED;
		z->parent = v; z->left = t2; z->right = t3; z->color = RED;

		// 서브 트리들의 부모 포인터 갱신
		t0->parent = grand; t1->parent = grand; t2->parent = z; t3->parent = z;
	}
}

void traversal(node *tmp, int x, int y, int P) // 순회 함수 -> 트리의 모든 node 순회하면서 범위에 맞는 node의 가격 할인
{
	if (tmp->ID == -1) // leaf node
	{
		return;
	}
	if (tmp->ID >= x && tmp->ID <= y) tmp->price = (tmp->price * (100 - P) / 100); // 범위에 맞는 node의 가격 할인
	traversal(tmp->left, x, y, P);
	traversal(tmp->right, x, y, P);
}

int find_depth(node *tmp) // 해당 node의 depth 반환
{ // 항상 이미 존재하는 node의 depth를 찾기 때문에 예외 조건 설정 X
	node *cmp = root;
	int d = 0; // depth

	while (cmp != tmp) // 일치할 때까지 밑으로 탐색
	{
		if (tmp->ID < cmp->ID)
		{
			cmp = cmp->left;
		}
		else cmp = cmp->right;
		d++;
	}
	return d; // depth return
}