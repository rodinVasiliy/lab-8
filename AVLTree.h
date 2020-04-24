#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
template <typename T>
class Set {
	struct Node {
		T _key;
		Node *_left;
		Node *_right;
		unsigned _height;
		Node(const T& k) :_key(k), _left(nullptr), _right(nullptr),_height(1) {  }
	};
	Node* _root;//������ ������
	
	uint8_t GetHeight(Node* p) const {
		return p != nullptr ? p->_height : 0;
	}

	int GetBalance(Node* p) const {
		int a = GetHeight(p->_right);
		int b = GetHeight(p->_left);
		return a - b;
		//return GetHeight  (p->_right) - GetHeight(p->_left);
	}

	void UpdateHeight(Node* p) {
		auto leftHeight = GetHeight(p->_left);
		auto rightHeight = GetHeight(p->_right);
		p->_height = std::max(leftHeight, rightHeight) + 1;
	}
	Node* RotateRight(Node* p) {
		auto q = p->_left;
		p->_left = q->_right;
		q->_right = p;
		UpdateHeight(p);
		UpdateHeight(q);
		return q;
	}

	Node* RotateLeft(Node* q) {//����� �������
		auto p = q->_right;
		q->_right = p->_left;
		p->_left = q;
		UpdateHeight(q);
		UpdateHeight(p);
		return p;
	}
	Node* Balance(Node* p) {
		UpdateHeight(p);
		auto c = GetBalance(p);
		if (c == -2) {//height of right bigger thaan height of left
			if (GetBalance(p->_left) > 0)
				p->_left = RotateLeft(p->_left);
			return RotateRight(p);
		}
		if (c == 2) {
			if (GetBalance(p->_right) < 0)
				p->_right = RotateRight(p->_right);
			return RotateLeft(p);
		}
		return p;
	}
	/*Node* Insert(Node* p, const T& key) {
		if (p == nullptr)return new Node(key);
		if (key < p->_key)p->_left = Insert(p->_left, key);
		else if (p->_key < key)p->_right = Insert(p->_right, key);
		return Balance(p);
	}*/
	Node* Insert(Node*p, const T& key) {
		if (p == nullptr) {
			p = new Node(key);
			return p;
		}
		if (key < p->_key) {
			p->_left = Insert(p->_left, key);
		}
		else if (p->_key < key) {
			p->_right = Insert(p->_right, key);
		}
		return Balance(p);
	}
	Node* Find(Node* p, const T& key) const{
		if (p == nullptr)return nullptr;
		if (key < p->_key)return Find(p->_left, key);
		else if (p->_key < key)return Find(p->_right, key);
		else return p;
	}
	void Print(Node* node, int offset) // offset - ���-�� ���������
	{
		cout << string(offset, ' ');
		if (node == nullptr)
		{
			cout << " nullptr " << endl;
			return;
		}
		cout<< node->_key<< endl;
		Print(node->_left, offset + 2);
		Print(node->_right, offset + 2);
	}
	Node* FindMin(Node*	p) const {//����� ������������ ����� � ������
		return p->_left ? FindMin(p->_left) : p;
	}
	Node* RemoveMin(Node* p) {//�������� ������������ ����� �� ������
		if (p->_left == nullptr)return p->_right;
		p->_left = RemoveMin(p->_left);
		return Balance(p);
	}
	Node* Remove(Node* p,const T& key) {//�������� ����� key �� ������
		if (p == nullptr)return nullptr;//key not found
		if (key < p->_key) p->_left = Remove(p->_left, key);
		else if(p->_key < key) p->_right = Remove(p->_right, key);
		else {
			auto q = p->_left;
			auto r = p->_right;
			delete p;//������� ���� key
			if (r == nullptr)return q;
			auto min = FindMin(r);
			min->_right = RemoveMin(r);
			min->_left = q;//p->_left
			return Balance(min);
		}
		return Balance(p);	
	}
public:
	
	Set() :_root(nullptr){}
	
	Set(const Set&) = delete;
	
	Set(Set&&) = delete;

	Set& operator=(const Set& rhs) = delete;

	Set& operator=(Set&& rhs) = delete;
	
	//~AVLTree(){}//����� ����������� ��������� �������
	
	bool Find(const T& key) const {
		return Find(_root, key)!=nullptr;
	}
	
	void Insert(const T& key) {
		_root = Insert(_root, key);//��� ������� ������ ����� ����������
	}
	
	void Remove(const T& key) {
		_root=Remove(_root, key);//after remove root may be change
	}

	void Print() const{
		Print(_root, 0);
	}
	int getHeight() const{
		return GetHeight(_root);
	}
};