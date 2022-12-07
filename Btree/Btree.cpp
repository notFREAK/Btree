#include "Btree.h"

Btree::Btree(int order, string path)
{
	this->order = order;
	head = NULL;
	IndexFile = new File(order, path);
}

Btree::~Btree()
{
	delete IndexFile;
}

void Btree::Traverse()
{
    if (head != NULL) 
	IndexFile->readNode(head)->Traverse();
}

Node* Btree::Search(int k)
{
	if (head == NULL)
		return nullptr;
	else
        return IndexFile->readNode(head)->Search(k);
}

void Btree::Insert(int k)
{
    if (head == NULL)
    {
        Node* node = new Node(order, true);
        node->keys[0] = k;  
        node->keys_count = 1; 
        IndexFile->writeNode(0, ios::beg, node);
        head = 0;
    }
    else 
    {
        Node* node = IndexFile->readNode(this->head);
        if (node->keys_count == 2 * order - 1)
        {
            Node* newNode = new Node(order, false);
            newNode->childrens[0] = head;
            newNode->Split(0, node);

            int i = 0;
            if (newNode->keys[0] < k)
                i++;
            IndexFile->readNode(newNode->childrens[i])->Insert(k);
            head = newNode->thisobj;
        }
        else
            IndexFile->readNode(head)->Insert(k);
    }
}
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