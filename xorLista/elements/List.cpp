#include <iostream>
#include "List.h"

using namespace std;

List::List(){
    head=nullptr;
    curr=nullptr;
    end=nullptr;
}
//operacja xor na dwoch adresach
struct List::node* List::XOR(struct node* a, struct node* b)
{
    return (struct node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}
//dodaie i ustawia alement jako pierwszy
void List::addNodeBeg(int addData)
{
    nodePtr n=new node;
    n->data=addData;
    if(!head)
    {
        n->xptr=NULL;
        curr=n;
        end=n;
    }
    else
    {
        head->xptr=XOR(n,head->xptr);
        n->xptr=head;
    }
    head=n;
}
//dodaje element i ustawia go jako ACTUAL
void List::addNodeAct(int addData)
{
    if(curr==head) {
        List::addNodeBeg(addData);
        return;
    }
    nodePtr n=new node;
    n->data=addData;
    if(!head)
    {
        n->xptr=NULL;
        head=n;
        end=n;
        curr=n;
    }
    else
    {
        nodePtr prev=NULL;
        nodePtr temp=head;
        nodePtr next;
        
        do {
            next = XOR(prev,temp->xptr);
            if(next == curr)
            {
                n->xptr=XOR(temp,next);
                next->xptr=XOR (n, XOR(temp, next->xptr));
                temp->xptr = XOR(prev,n);
            }
            prev=temp;
            temp=next;
            
        }while(next!=curr);
        curr=next;
    }
}
//dodaje element i ustawia jako ostatni
void List::addNodeEnd(int addData)
{
    nodePtr n=new node;
    n->data=addData;
    if(!head)
    {
        n->xptr=NULL;
        curr=n;
        head=n;
    }
    else{
        end->xptr=XOR(n,end->xptr);
        n->xptr=end;
        
    }
    end=n;
}
//usuwa pierwszy element
void List::deleteNodeBeg()
{
    if(head==NULL) return;
    if(head==end)
    {
        delete head;
        head=NULL;
        return;
    }
    nodePtr temp=head->xptr;
        
        temp->xptr=XOR(temp->xptr,head);
        if(curr==head) curr=temp;
        delete head;
        head=temp;
}
//usuwa ostatni element
void List::deleteNodeEnd()
{
    if(head==NULL) return;
    if(head==end)
    {
        delete end;
        head=NULL;
        return;
    }
        nodePtr temp=end->xptr;
        
        temp->xptr=XOR(temp->xptr,end);
        if(curr==end) curr=temp;
        delete end;
        end=temp;
}
//usuwa element ktory znajduje sie na miejscu ACTUAL
void List::deleteNodeAct()
{
    if(head==end)
    {
        delete head;
        head=NULL;
        return;
    }
    if(head==NULL) return;
    if(curr==head)
    {
        List::deleteNodeBeg();
        curr=end;
    }
    else if(curr==end)
    {
        List::deleteNodeEnd();
    }
    else
    {
        nodePtr prev=NULL;
        nodePtr tempHead=head;
        nodePtr next=end;
        nodePtr temp=curr;
        nodePtr tempPrev=NULL;
            
        do
        {
            tempPrev=XOR(prev,tempHead->xptr);
            prev=tempHead;
            tempHead=tempPrev;
        }while(tempPrev != curr);
        nodePtr temp2=NULL;
        nodePtr tempNext=next;
        while(XOR(temp2,next->xptr) != curr)
        {
            next=XOR(temp2,tempNext->xptr);
            temp2=tempNext;
            tempNext=next;
        }
        temp=curr;
        curr=prev;
        prev->xptr=XOR(XOR(prev->xptr,temp), next);
        next->xptr=XOR(XOR(next->xptr,temp),prev);
        delete temp;
    }
}
//usuwa wszystkie elementy, ktore przechowuja konkretna wartosc
void List::deleteNode(int delData)
{
    nodePtr next=NULL;
    nodePtr prev=NULL;
    nodePtr temp=head;
    if(head==end)
    {
        curr=nullptr;
        end=nullptr;
        head=nullptr;
        return;
    }
    while(temp != NULL)
    {
        if(temp==head) next=temp->xptr;
        else next=XOR(prev,temp->xptr);
        
        if(temp->data==delData)
        {
            nodePtr x=temp;
            if(temp==head)
            {
                List::deleteNodeBeg();
                temp=NULL;
            }
            else if(temp==end)
            {
                List::deleteNodeEnd();
                prev=XOR(prev,x->xptr);
                temp=prev;
                next=NULL;
            }
            else if(temp==curr)
            {
                List::deleteNodeAct();
                temp=next;
                prev=XOR(prev->xptr,x);
            }
            else
            {
                prev->xptr=XOR(next,XOR(prev->xptr,temp));
                next=XOR(temp->xptr,prev);
                next->xptr=XOR(XOR(temp,next->xptr),prev);
                if(prev == head)
                {
                    head->xptr=prev->xptr;
                    
                }
                delete temp;
                temp=prev;
            }
        }
        prev=temp;
        temp=next;
    }
}
//wypisuje liste od przodu (od head do end)
void List::printListF()
{
    nodePtr next=NULL;
    nodePtr prev=NULL;
    nodePtr temp=head;
    while(temp != NULL)
    {
        next=XOR(prev,temp->xptr);
        printf("%d ",temp->data);
        if(temp==end)
        {
            cout<<endl;
            return;
        }
        prev=temp;
        temp=next;
    }
    
    if(temp==NULL) cout<<"NULL"<<endl;
}
//wypisuje liste od tylu (od end do head)
void List::printListB()
{
    nodePtr next=NULL;
    nodePtr prev=NULL;
    nodePtr temp=end;
    while(temp != NULL)
    {
        next=XOR(prev,temp->xptr);
        printf("%d ",temp->data);
        if(temp==head)
        {
            cout<<endl;
            return;
        }
        prev=temp;
        temp=next;
    }
    cout<<endl;
    if(temp==NULL) cout<<"NULL"<<endl;
}
//zwraca wartosc ACTUAL, jezeli lista jest pusta to zwraca NULL
void List::getAct()
{
    if(head == NULL )
    {
        cout<<"NULL"<<endl;
        return;
    }
    if(curr != NULL) cout<<curr->data<<endl;
    else cout<<"NULL"<<endl;
}
//zwraca wartosc poprzedzajaca ACTUAL i ustawia go ACTUAL
void List::getNext()
{
    if(head == NULL )
    {
        cout<<"NULL"<<endl;
        return;
    }
        nodePtr next=end;
        nodePtr temp=NULL;
        nodePtr tempNext=next;

    if(curr==end) curr=head;
    else
    {
        while(XOR(next->xptr,temp) != curr)
        {
            next=XOR(temp,tempNext->xptr);
            temp=tempNext;
            tempNext=next;
        }
        curr=next;
    }
    if(curr != NULL) cout<<curr->data<<endl;
    else cout <<"NULL"<<endl;
}
// zwraca wartosc uprzedzajaca ACTUAL i ustawia go ACTUAL
void List::getPrev()
{
    if(head == NULL )
    {
        cout<<"NULL"<<endl;
        return;
    }
    
    nodePtr prev=NULL;
    nodePtr tempHead=head;
    nodePtr tempPrev=NULL;
    if(curr == head) curr=end;
    else
    {
        do
        {
            tempPrev=XOR(prev,tempHead->xptr);
            prev=tempHead;
            tempHead=tempPrev;
        }while(tempPrev != curr);
        curr=prev;
    }
    if(curr!=NULL) cout<<curr->data<<endl;
    else cout<<"NULL"<<endl;
}   

