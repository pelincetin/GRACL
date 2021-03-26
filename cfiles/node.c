#include <stdlib.h>
#include <string.h>

struct Node
{
    char data[];
    bool visited;
    struct EdgeList neighbors;
    /* Mutex? */
};

String data()
{
    // Returns data stored in the Node object.
}

NodeList neighbors()
{
    // Returns a list of neighbor Nodes. 
}

bool visited()
{
    // Returns a boolean representing if the Node has already been visited.
}

int updateData(String data)
{
    // Updates the data field on the Node to be the new data passed in and returns 0 on success. On failure, returns -1.
}

int updateVisited(bool tf)
{
    // Updates the visited field on the Node to be the new bool passed in and returns 0 on success. On failure, returns -1.
}

bool equals(Node n)
{
    // Compares the two Node objects. Returns True if they are the same and returns False if they’re not the same.
    // Under the hood, this is implemented by comparing the implicit id associated with the Node object. 
}




// struct node* front(struct node *head,int value)
// {
// 	struct node *p;
// 	p=malloc(sizeof(struct node));
// 	p->data=value;
// 	p->next=head;
// 	return (p);
// }

// end(struct node *head,int value)
// {
//     struct node *p,*q;
//     p=malloc(sizeof(struct node));
//     p->data=value;
//     p->next=NULL;
//     q=head;
//     while(q->next!=NULL)
//     {
//         q = q->next;
//     }
//     q->next = p;
// }