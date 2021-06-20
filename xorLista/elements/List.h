#ifndef List_h
#define List_h
class List{
private:
    
    typedef struct node{
        int data;
        node* xptr;
    }*nodePtr;
    
    nodePtr head;
    nodePtr curr;
    nodePtr end;

public:
    List();
    nodePtr XOR(struct node* a, struct node* b);
    void getAct();
    void getNext();
    void getPrev();
    void addNodeBeg(int addData);
    void addNodeAct(int addData);
    void addNodeEnd(int addData);
    void deleteNodeBeg();
    void deleteNodeEnd();
    void deleteNode(int delData);
    void deleteNodeAct();
    void printListB();
    void printListF();
};



#endif
