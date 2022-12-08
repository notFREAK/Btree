#include "Node.h"

Node::Node(int order, bool leaf)    //Создаем узел с размером и указанием листовой ли узел 
{
	try {
		keys = new keytype[2*order];
		childrens = new pointer[2*order + 1];
	}
	catch (...) {
		 cout << "Error memory allocation" << endl;
	}
	for (int i = 0; i < 2*order; i++)
	{
		keys[i] = 0; 
		childrens[i] = 0;
	}
	childrens[2*order] = 0;
	this->order = order;
	this->leaf = leaf;
	thisobj = 0;
	keys_count = 0;
}

Node::Node(int order, bool leaf, File* file) : Node(order, leaf)  //Создаем узел с размером и указанием листовой ли узел 
{
	IndexFile = file;
}

void Node::Print()
{
	cout << childrens[0];
	for (int i = 0; i < 2*order; i++)
	{
		cout << ' ' << keys[i] << ' ';
		cout << childrens[i + 1];
	}
	cout << endl;
}


Node::~Node() {
	if (keys != NULL) {
		delete keys;
	}
	if (childrens != NULL) {
		delete childrens;
	}
}

void Node::Traverse() {      //Обход дерева
	int i;
	for (i = 0; i < keys_count; i++)
	{
		if (leaf == false) {
			Node* tempa = IndexFile->readNode(childrens[i]);
			tempa->Traverse();
			delete tempa;
		}
		cout << " " << keys[i];
	}
	if (leaf == false) {
		Node* tempa = IndexFile->readNode(childrens[i]);
		tempa->Traverse();
		delete tempa;
	}
}

Node* Node::Search(int key) {  //Поиск ключа
	int i = 0;
	for (; i < keys_count && keys[i] < key; i++);
	if (keys[i] == key) {
		return this;
	}
	else {
		if (!leaf) {
			Node* tempa = IndexFile->readNode(childrens[i]);
			return tempa->Search(key);
		}
			
		else
			return nullptr;
	}
}

void Node::Split(int i, Node* root)   //Разделение дочернего узла root если он переполнился
{
	Node* newChildren = new Node(root->order, root->leaf);
	newChildren->keys_count = order - 1;
	newChildren->IndexFile = IndexFile;
	for (int j = 0; j < order - 1; j++)
		newChildren->keys[j] = root->keys[j + order];
	if (root->leaf == false)
	{
		for (int j = 0; j < order; j++)
			newChildren->childrens[j] = root->childrens[j + order];
	}
	newChildren->keys_count;
	IndexFile->writeNode(0, ios::end, newChildren);
	root->keys_count = order - 1;
	for (int j = keys_count; j >= i + 1; j--)
		childrens[j + 1] = childrens[j];
	this->childrens[i + 1] = newChildren->thisobj;
	for (int j = keys_count - 1; j >= i; j--)
		keys[j + 1] = keys[j];
	keys[i] = root->keys[order - 1];
	keys_count = keys_count + 1;
	IndexFile->writeNode(root->thisobj, ios::beg, root);
	IndexFile->writeNode(this->thisobj, ios::beg, this);
}

void Node::Insert(int k)  //Добавление узла
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
		this->Print();
		for (; i >= 0 && keys[i] > k; i--);
		i++;
		Node* temp = IndexFile->readNode(childrens[i]);
		temp->Print();
		if (temp->keys_count == 2 * order - 1)
		{
			Split(i, temp);
			if (keys[i] < k)
				i++;
		}
		IndexFile->writeNode(temp->thisobj, ios::beg, temp);
		delete temp;
		temp = IndexFile->readNode(childrens[i]);
		temp->Print();
		temp->Insert(k);
		delete temp;
	}
	IndexFile->writeNode(this->thisobj, ios::beg, this);
}

//int Node::FindKey(int k)  //Индекс ключа, который больше или равен ключу
//{
//    int idx = 0;
//    while (idx < keys_count && keys[idx] < k)
//        ++idx;
//    return idx;
//}
//
//void Node::Delete(int k) //Удаление узла
//{
//    int idx = FindKey(k);
//    if (idx < keys_count && keys[idx] == k)
//    {
//        if (leaf)  
//        {
//            for (int i = idx + 1; i < keys_count; ++i)
//                keys[i - 1] = keys[i];
//            keys_count--;
//            }
//        else
//        {
//            if (childrens[idx]->keys_count >= order)
//            {
//                int pred = getPred(idx);
//                keys[idx] = pred;
//                childrens[idx]->Delete(pred);
//            }
//            else if (childrens[idx + 1]->keys_count >= order)
//            {
//                int succ = getSucc(idx);
//                keys[idx] = succ;
//                childrens[idx + 1]->Delete(succ);
//            }
//            else
//            {
//                Merge(idx);
//                childrens[idx]->Delete(k);
//            }
//        }
//    }
//    else
//    {
//        if (leaf)
//        {
//            cout << "The key " << k << " is does not exist in the tree\n";
//            return;
//        }
//        bool flag = ((idx == keys_count) ? true : false);
//        if (childrens[idx]->keys_count < order)
//            Fill(idx);
//        if (idx == keys_count && idx > keys_count)
//            childrens[idx - 1]->Delete(k);
//        else
//            childrens[idx]->Delete(k);
//    }
//    return;
//}
//
//int Node::getPred(int idx) //Возвращает самый большой ключи
//{
//    Node* cur = childrens[idx];
//    while (!cur->leaf)
//        cur = cur->childrens[cur->keys_count];
//    return cur->keys[cur->keys_count - 1];
//}
//
//int Node::getSucc(int idx) //Возвращает самый маленький
//{
//    Node* cur = childrens[idx + 1];
//    while (!cur->leaf)
//        cur = cur->childrens[0];
//    return cur->keys[0];
//}
//
//void Node::Fill(int idx)//заполнить удаленное место
//{
//    if (idx != 0 && childrens[idx - 1]->keys_count >= order)
//        BorrowFromPrev(idx);
//    else if (idx != keys_count && childrens[idx + 1]->keys_count >= order)
//        BorrowFromNext(idx);
//    else
//    {
//        if (idx != keys_count)
//            Merge(idx);
//        else
//            Merge(idx - 1);
//    }
//    return;
//}
//
//void Node::BorrowFromPrev(int idx) //Возместить ключ из узла слева
//{
//
//    Node* child = childrens[idx];
//    Node* sibling = childrens[idx - 1];
//    for (int i = child->keys_count - 1; i >= 0; --i)
//        child->keys[i + 1] = child->keys[i];
//    if (!child->leaf)
//    {
//        for (int i = child->keys_count; i >= 0; --i)
//            child->childrens[i + 1] = child->childrens[i];
//    }
//    child->keys[0] = keys[idx - 1];
//    if (!child->leaf)
//        child->childrens[0] = sibling->childrens[sibling->keys_count];
//    keys[idx - 1] = sibling->keys[sibling->keys_count - 1];
//    child->keys_count += 1;
//    sibling->keys_count -= 1;
//    return;
//}
//
//void Node::BorrowFromNext(int idx) //возместить из узла справа
//{
//
//    Node* child = childrens[idx];
//    Node* sibling = childrens[idx + 1];
//    child->keys[(child->keys_count)] = keys[idx];
//    if (!(child->leaf))
//        child->childrens[(child->keys_count) + 1] = sibling->childrens[0];
//    keys[idx] = sibling->keys[0];
//    for (int i = 1; i < sibling->keys_count; ++i)
//        sibling->keys[i - 1] = sibling->keys[i];
//    if (!sibling->leaf)
//    {
//        for (int i = 1; i <= sibling->keys_count; ++i)
//            sibling->childrens[i - 1] = sibling->childrens[i];
//    }
//    child->keys_count += 1;
//    sibling->keys_count -= 1;
//    return;
//}
//
//void Node::Merge(int idx) //Cлияние
//{
//    Node* child = childrens[idx];
//    Node* sibling = childrens[idx + 1];
//    child->keys[order - 1] = keys[idx];
//    for (int i = 0; i < sibling->keys_count; ++i)
//        child->keys[i + order] = sibling->keys[i];
//    if (!child->leaf)
//    {
//        for (int i = 0; i <= sibling->keys_count; ++i)
//            child->childrens[i + order] = sibling->childrens[i];
//    }
//    for (int i = idx + 1; i <keys_count; ++i)
//        keys[i - 1] = keys[i];
//    for (int i = idx + 2; i <=keys_count; ++i)
//        childrens[i - 1] = childrens[i];
//    child->keys_count += sibling->keys_count + 1;
//    keys_count--;
//    delete(sibling);
//    return;
//}
//
