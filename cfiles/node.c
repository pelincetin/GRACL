#include <stdlib.h>
#include <string.h>

struct Node
{
    char data[];
    struct EdgeList neighbors;
    /* Mutex? */
};

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