#include "Node.h"
#include "Btree.h"

Node::Node(int order, bool leaf)    //������� ���� � �������� � ��������� �������� �� ���� 
{
	try {
		keys = new int[order];
		childrens = new Node * [order + 1];
	}
	catch (...) {
		 cout << "Error memory allocation" << endl;
	}
	this->order = order;
	this->leaf = leaf;
	keys_count = 0;
}

void Node::Traverse() {      //����� ������
	int i;
	for (i = 0; i < keys_count; i++)
	{
		if (leaf == false)
			childrens[i]->Traverse();
		cout << " " << keys[i];
	}
	if (leaf == false)
		childrens[i]->Traverse();
}

Node* Node::Search(int key) {  //����� �����
	int i = 0;
	for (; i < keys_count && keys[i] < key; i++);
	if (keys[i] == key) {
		return this;
	}
	else {
		if (!leaf)
			return childrens[i]->Search(key);
		else
			return nullptr;
	}
}

void Node::Split(int i, Node* root)   //���������� ��������� ���� root ���� �� ������������
{
	Node* newChildren = new Node(root->order, root->leaf);
	newChildren->keys_count = order - 1;
	for (int j = 0; j < order - 1; j++)
		newChildren->keys[j] = root->keys[j + order];
	if (root->leaf == false)
	{
		for (int j = 0; j < order; j++)
			newChildren->childrens[j] = root->childrens[j + order];
	}
	root->keys_count = order - 1;
	for (int j = keys_count; j >= i + 1; j--)
		childrens[j + 1] = childrens[j];
	childrens[i + 1] = newChildren;
	for (int j = keys_count - 1; j >= i; j--)
		keys[j + 1] = keys[j];
	keys[i] = root->keys[order - 1];
	keys_count = keys_count + 1;
}

void Node::Insert(int k)  //���������� ����
{
	int i = keys_count - 1;

	if (leaf == true)
	{
		for (;i >= 0 && keys[i] > k; i--)
			keys[i + 1] = keys[i];
		keys[i + 1] = k;
		keys_count = keys_count+ 1;
	}
	else
	{
		for (; i >= 0 && keys[i] > k; i--);
		if (childrens[i + 1]->keys_count == 2 * order - 1)
		{
			Split(i + 1, childrens[i + 1]);
			if (keys[i + 1] < k)
				i++;
		}
		childrens[i + 1]->Insert(k);
	}
}

int Node::FindKey(int k)  //������ �����, ������� ������ ��� ����� �����
{
    int idx = 0;
    while (idx < keys_count && keys[idx] < k)
        ++idx;
    return idx;
}

void Node::Delete(int k) //�������� ����
{
    int idx = FindKey(k);
    if (idx < keys_count && keys[idx] == k)
    {
        if (leaf)  
        {
            for (int i = idx + 1; i < keys_count; ++i)
                keys[i - 1] = keys[i];
            keys_count--;
            }
        else
        {
            if (childrens[idx]->keys_count >= order)
            {
                int pred = getPred(idx);
                keys[idx] = pred;
                childrens[idx]->Delete(pred);
            }
            else if (childrens[idx + 1]->keys_count >= order)
            {
                int succ = getSucc(idx);
                keys[idx] = succ;
                childrens[idx + 1]->Delete(succ);
            }
            else
            {
                Merge(idx);
                childrens[idx]->Delete(k);
            }
        }
    }
    else
    {
        if (leaf)
        {
            cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }
        bool flag = ((idx == keys_count) ? true : false);
        if (childrens[idx]->keys_count < order)
            Fill(idx);
        if (idx == keys_count && idx > keys_count)
            childrens[idx - 1]->Delete(k);
        else
            childrens[idx]->Delete(k);
    }
    return;
}

int Node::getPred(int idx) //���������� ����� ������� �����
{
    Node* cur = childrens[idx];
    while (!cur->leaf)
        cur = cur->childrens[cur->keys_count];
    return cur->keys[cur->keys_count - 1];
}

int Node::getSucc(int idx) //���������� ����� ���������
{
    Node* cur = childrens[idx + 1];
    while (!cur->leaf)
        cur = cur->childrens[0];
    return cur->keys[0];
}

void Node::Fill(int idx)//��������� ��������� �����
{
    if (idx != 0 && childrens[idx - 1]->keys_count >= order)
        BorrowFromPrev(idx);
    else if (idx != keys_count && childrens[idx + 1]->keys_count >= order)
        BorrowFromNext(idx);
    else
    {
        if (idx != keys_count)
            Merge(idx);
        else
            Merge(idx - 1);
    }
    return;
}

void Node::BorrowFromPrev(int idx) //���������� ���� �� ���� �����
{

    Node* child = childrens[idx];
    Node* sibling = childrens[idx - 1];
    for (int i = child->keys_count - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];
    if (!child->leaf)
    {
        for (int i = child->keys_count; i >= 0; --i)
            child->childrens[i + 1] = child->childrens[i];
    }
    child->keys[0] = keys[idx - 1];
    if (!child->leaf)
        child->childrens[0] = sibling->childrens[sibling->keys_count];
    keys[idx - 1] = sibling->keys[sibling->keys_count - 1];
    child->keys_count += 1;
    sibling->keys_count -= 1;
    return;
}

void Node::BorrowFromNext(int idx) //���������� �� ���� ������
{

    Node* child = childrens[idx];
    Node* sibling = childrens[idx + 1];
    child->keys[(child->keys_count)] = keys[idx];
    if (!(child->leaf))
        child->childrens[(child->keys_count) + 1] = sibling->childrens[0];
    keys[idx] = sibling->keys[0];
    for (int i = 1; i < sibling->keys_count; ++i)
        sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->keys_count; ++i)
            sibling->childrens[i - 1] = sibling->childrens[i];
    }
    child->keys_count += 1;
    sibling->keys_count -= 1;
    return;
}

void Node::Merge(int idx) //C������
{
    Node* child = childrens[idx];
    Node* sibling = childrens[idx + 1];
    child->keys[order - 1] = keys[idx];
    for (int i = 0; i < sibling->keys_count; ++i)
        child->keys[i + order] = sibling->keys[i];
    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->keys_count; ++i)
            child->childrens[i + order] = sibling->childrens[i];
    }
    for (int i = idx + 1; i <keys_count; ++i)
        keys[i - 1] = keys[i];
    for (int i = idx + 2; i <=keys_count; ++i)
        childrens[i - 1] = childrens[i];
    child->keys_count += sibling->keys_count + 1;
    keys_count--;
    delete(sibling);
    return;
}

