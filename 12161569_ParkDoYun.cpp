#include <iostream>
#include <string>

using namespace std;

#define BLACK 0
#define RED 1
#define FOUND 2 // �÷��� ���� ���� ���
#define NOT_FOUND 3 // �÷��� ���� ���� ���

struct node
{
	int ID = -1; // ID, -1 : leaf node
	string name; // �̸�
	int capacity; // �뷮
	int price; // ����
	int color = BLACK; // 0 : black, 1 : red
	node *parent = NULL; // parent node
	node *left = NULL; // left child
	node *right = NULL; // right child
};

node *binary_search(int id, node *tmp, int &depth, int &flag); // ���� Ž�� �Լ�
void insert(int id, string name, int capacity, int price); // ��� �Լ�
void restructure(node *z, node *v, node *w); // restructure �Լ�
void traversal(node *tmp, int x, int y, int P); // ��ȸ �Լ� -> Ʈ���� ��� node ��ȸ�ϸ鼭 ������ �´� node�� ���� ����
int find_depth(node *tmp); // tmp�� depth ���ϴ� �Լ�

node *root = NULL; // root ����Ű�� ������

// �˰��� �������1
// 12161569 ��ǻ�Ͱ��а� �ڵ���
// red-black tree

int main()
{
	int inst_n; // ������ ��
	char inst; // ��ɾ�
	int input_i; // �Է¹޴� �˻� ID
	string input_n; // �Է¹޴� �̸�
	int input_c; // �Է¹޴� �뷮
	int input_p; // �Է¹޴� ����

	root = new node; // root

	cin >> inst_n; // ������ �� �Է�

	for (int i = 0; i < inst_n; i++)
	{
		cin >> inst; // ��ɾ� �Է� ('I', 'F', 'R', 'D')
		if (inst == 'I') // ���
		{
			cin >> input_i >> input_n >> input_c >> input_p;

			insert(input_i, input_n, input_c, input_p); // ���
		}
		else if (inst == 'F') // �˻�
		{
			cin >> input_i;

			int depth = 0;
			int flag; // ã�Ҵ��� �÷��� ����
			node *tmp = root;
			node *n = binary_search(input_i, tmp, depth, flag); // Ž��

			// ���
			if (flag == NOT_FOUND) cout << "NULL\n"; // �� ã���� ���
			else cout << depth << ' ' << n->name << ' ' << n->capacity << ' ' << n->price << '\n'; // ã���� ��� ���
		}
		else if (inst == 'R') // ������Ʈ
		{
			cin >> input_i >> input_n >> input_c >> input_p;

			int depth = 0;
			int flag; // ã�Ҵ��� �÷��� ����
			node *tmp = root;
			node *n = binary_search(input_i, tmp, depth, flag); // Ž��

			if (flag == NOT_FOUND) cout << "NULL\n"; // �� ã���� ���
			else // ã���� ��� -> ���� ����
			{
				n->name = input_n;
				n->capacity = input_c;
				n->price = input_p;
				cout << depth << '\n';
			}
		}
		else // (inst == 'D') // ����
		{
			int x, y; // ����
			int P; // ������
			cin >> x >> y >> P;

			traversal(root, x, y, P); // ��ȸ�ϸ� ������ �´� node�� ���� ����
		}
	}
	return 0;
}

node *binary_search(int id, node *tmp, int &depth, int &flag) // ���� Ž�� �Լ�
{ // id : ã���� �ϴ� ID, tmp : ���� node ������, depth : ���� node�� depth, flag : ã�Ҵ��� �� ã�Ҵ��� Ȯ�� �÷���
	if (tmp->ID == -1) // �������� ������ (leaf node �����ߴٸ�)
	{
		flag = NOT_FOUND; // �÷��� ����
		return tmp; // �ش� leaf node return
	}
	if (tmp->ID == id) // Ž�� �Ϸ� ��
	{
		flag = FOUND; // �÷��� ����
		return tmp; // ã�� node return
	}
	else if (id < tmp->ID) return binary_search(id, tmp->left, ++depth, flag); // left child
	else return binary_search(id, tmp->right, ++depth, flag); // right child
}

void insert(int id, string name, int capacity, int price) // ��� �Լ�
{
	int depth = 0;
	int flag; // ã�Ҵ��� Ȯ�� �÷���
	node *tmp = root;
	node *n = binary_search(id, tmp, depth, flag); // Ž��

	if (flag == NOT_FOUND) // �� ã������ ���
	{
		if (n == root) // root ���� ��
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
		else // root�� �ƴ� ��
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

			// double red �˻�
			node *z = n;

			// z�� root�ų� root �ٷ� ���̶�� ����
			if (z->parent == NULL || z->parent->parent == NULL)
			{
				cout << depth << '\n';
				return;
			}

			node *v = n->parent; // z�� parent node
			node *grand = n->parent->parent; // z�� grandparent node
			node *w = (grand->left == v ? grand->right : grand->left); // v�� sibling

			while (z->color == RED && v->color == RED) // double red
			{
				if (w->color == BLACK) // restructuring
				{
					restructure(z, v, w);
					// depth ����
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

					// ���� �ö󰡱�
					z = grand;

					// z�� root�ų� root �ٷ� ���̶�� ����
					if (z->parent == NULL || z->parent->parent == NULL) break;

					v = z->parent; // z�� parent node
					grand = v->parent; // z�� grandparent node
					w = (grand->left == v ? grand->right : grand->left); // v�� sibling
				}
			}
			
			
		}
	}

	// node�� depth ���
	cout << depth << '\n';
}

void restructure(node *z, node *v, node *w) // restructure
{
	node *grand = v->parent; // z�� grandparent node
	node *grandgrand = grand->parent; // grand�� parent node
	int gg_chk = -1; // grand�� left child�� 0, right child�� 1, grandgrand�� ������ -1 (grand�� root�̸�)

	if (grandgrand != NULL) // grand�� root�� �ƴ϶��
	{
		if (grand == grandgrand->left) gg_chk = 0; // grand�� left child
		else gg_chk = 1; // grand�� right child
	}

	node *t0, *t1, *t2, *t3; // ���� Ʈ�� 4��, �� Ʈ������ �θ� �����͵� ���� ���� �ʿ�

	// 4���� case ����
	if (grand->right == v && v->left == z)
	{
		// ���� Ʈ�� ���� (t0, t1, t2, t3)
		t0 = w; t1 = z->left;
		t2 = z->right; t3 = v->right;

		if (gg_chk != -1) // grandgrand node�� �ڽ� ������ ����
		{
			if (gg_chk == 0) grandgrand->left = z; // grand�� left child
			else grandgrand->right = z; // grand�� right child
		}
		else root = z; // grand�� root�̸� root ������ ����

		// restructuring
		z->parent = grand->parent; z->left = grand; z->right = v; z->color = BLACK;
		grand->parent = z; grand->left = t0; grand->right = t1; grand->color = RED;
		v->parent = z; v->left = t2; v->right = t3; v->color = RED;

		// ���� Ʈ������ �θ� ������ ����
		t0->parent = grand; t1->parent = grand; t2->parent = v; t3->parent = v;
	}
	else if (grand->left == v && v->right == z)
	{
		// ���� Ʈ�� ����
		t0 = v->left; t1 = z->left;
		t2 = z->right; t3 = w;

		if (gg_chk != -1) // grandgrand node�� �ڽ� ������ ����
		{
			if (gg_chk == 0) grandgrand->left = z; // grand�� left child
			else grandgrand->right = z; // grand�� right child
		}
		else root = z; // grand�� root�̸� root ������ ���� 

		// restructuring
		z->parent = grand->parent; z->left = v; z->right = grand; z->color = BLACK;
		v->parent = z; v->left = t0; v->right = t1; v->color = RED;
		grand->parent = z; grand->left = t2; grand->right = t3; grand->color = RED;

		// ���� Ʈ������ �θ� ������ ����
		t0->parent = v; t1->parent = v; t2->parent = grand; t3->parent = grand;
	}
	else if (grand->left == v && v->left == z)
	{
		// ���� Ʈ�� ����
		t0 = z->left; t1 = z->right;
		t2 = v->right; t3 = w;

		if (gg_chk != -1) // grandgrand node�� �ڽ� ������ ����
		{
			if (gg_chk == 0) grandgrand->left = v; // grand�� left child
			else grandgrand->right = v; // grand�� right child
		}
		else root = v; // grand�� root�̸� root ������ ����

		// restructuring
		v->parent = grand->parent; v->left = z; v->right = grand; v->color = BLACK;
		z->parent = v; z->left = t0; z->right = t1; z->color = RED;
		grand->parent = v; grand->left = t2; grand->right = t3; grand->color = RED;

		// ���� Ʈ������ �θ� ������ ����
		t0->parent = z; t1->parent = z; t2->parent = grand; t3->parent = grand;
	}
	else // grand->right == v && v->right == z
	{
		// ���� Ʈ�� ����
		t0 = w; t1 = v->left;
		t2 = z->left; t3 = z->right;

		if (gg_chk != -1) // grandgrand node�� �ڽ� ������ ����
		{
			if (gg_chk == 0) grandgrand->left = v; // grand�� left child
			else grandgrand->right = v; // grand�� right child
		}
		else root = v; // grand�� root�̸� root ������ ����

		// restructuring
		v->parent = grand->parent; v->left = grand; v->right = z; v->color = BLACK;
		grand->parent = v; grand->left = t0; grand->right = t1; grand->color = RED;
		z->parent = v; z->left = t2; z->right = t3; z->color = RED;

		// ���� Ʈ������ �θ� ������ ����
		t0->parent = grand; t1->parent = grand; t2->parent = z; t3->parent = z;
	}
}

void traversal(node *tmp, int x, int y, int P) // ��ȸ �Լ� -> Ʈ���� ��� node ��ȸ�ϸ鼭 ������ �´� node�� ���� ����
{
	if (tmp->ID == -1) // leaf node
	{
		return;
	}
	if (tmp->ID >= x && tmp->ID <= y) tmp->price = (tmp->price * (100 - P) / 100); // ������ �´� node�� ���� ����
	traversal(tmp->left, x, y, P);
	traversal(tmp->right, x, y, P);
}

int find_depth(node *tmp) // �ش� node�� depth ��ȯ
{ // �׻� �̹� �����ϴ� node�� depth�� ã�� ������ ���� ���� ���� X
	node *cmp = root;
	int d = 0; // depth

	while (cmp != tmp) // ��ġ�� ������ ������ Ž��
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