#include "Btree.h"

Btree::Btree(int order, string path)
{
	this->order = order;
	head = NULL;
	IndexFile->open(path);
}

Btree::~Btree()
{
	if (head != nullptr)
		delete head;
}

//void Btree::Traverse()
//{
//    if (head != nullptr) 
//		head->Traverse();
//}
//
//Node* Btree::Search(int k)
//{
//	if (head == nullptr)
//		return nullptr;
//	else
//		head->Search(k);
//}
//
//void Btree::Insert(int k)
//{
//    if (head == nullptr)
//    {
//        head = new Node(order, true);
//        head->keys[0] = k;  
//        head->keys_count = 1; 
//    }
//    else 
//    {
//        if (head->keys_count == 2 * order - 1)
//        {
//            Node* newNode = new Node(order, false);
//            newNode->childrens[0] = head;
//            newNode->Split(0, head);
//
//            int i = 0;
//            if (newNode->keys[0] < k)
//                i++;
//            newNode->childrens[i]->Insert(k);
//            head = newNode;
//        }
//        else
//            head->Insert(k);
//    }
//}
//
//void Btree::Delete(int k)
//{
//    if (!head)
//    {
//        cout << "The tree is empty\n";
//        return;
//    }
//    head->Delete(k);
//    if (head->keys_count == 0)
//    {
//        Node* tmp = head;
//        if (head->leaf)
//            head = NULL;
//        else
//            head = head->childrens[0];
//        delete tmp;
//    }
//    return;
//}