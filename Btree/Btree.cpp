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
    if (head != NULL) {
        Node* tmp = IndexFile->readNode(head);
        tmp->Traverse();
        delete tmp;
    }
    cout << endl;
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
        Node* node = new Node(order, true, IndexFile);
        node->keys[0] = k;  
        node->keys_count = 1; 
        head = sizeof(pointer);
        IndexFile->writePtr(0, head);
        IndexFile->writeNode(head, ios::beg, node);
        delete node;
    }
    else 
    {
        Node* node = IndexFile->readNode(this->head);
        if (node->keys_count == 2 * order - 1)
        {
            Node* newNode = new Node(order, false);
            newNode->childrens[0] = head;
            newNode->IndexFile = IndexFile;
            IndexFile->writeNode(0, ios::end, newNode);
            newNode->Split(0, node);
            int i = 0;
            if (newNode->keys[0] < k)
                i++;
            Node* NewNodeChild = IndexFile->readNode(newNode->childrens[i]);
            NewNodeChild->Insert(k);
            delete NewNodeChild;
            head = newNode->thisobj;
            IndexFile->writePtr(0, head);
            delete newNode;
        }
        else {
            node->Insert(k);
        }
        delete node;
    }
}

void Btree::Delete(int k)
{
    Node* node = IndexFile->readNode(this->head);
    if (!head)
    {
        cout << "The tree is empty\n";
        return;
    }
    node->Delete(k);
    if (node->keys_count == 0)
    {
        Node* tmp = node;
        if (node->leaf)
            node = NULL;   //סעונועü פאיכ
        else
        {
            head = node->childrens[0];
            IndexFile->writePtr(0, head);
        } 
        delete tmp;
        return;
    }
    delete node;
    return;
}