#include "Node.h"

Btree::Btree(int order)
{
	this->order = order;
	head = NULL;
	FileIndex->open("C:/Users/video/source/repos/notFREAK/Btree/Btree");
}

Btree::~Btree()
{
}

void Btree::Traverse()
{
	if (head != NULL)
		FileIndex->ReadNode(head)->Traverse();
}

//Node* Btree::Search(int k)
//{
//	if (head == nullptr)
//		return nullptr;
//	else
//		return head->Search(k);
//}

void Btree::Insert(int k)
{
    if (head == nullptr)
    {
        head = new Node(order, true);
        head->keys[0] = k;  
        head->keys_count = 1; 
    }
    else 
    {
        if (head->keys_count == 2 * order - 1)
        {
            Node* newNode = new Node(order, false);
            newNode->childrens[0] = head;
            newNode->Split(0, head);

            int i = 0;
            if (newNode->keys[0] < k)
                i++;
            newNode->childrens[i]->Insert(k);
            head = newNode;
        }
        else
            head->Insert(k);
    }
}