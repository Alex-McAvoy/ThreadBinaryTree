typedef enum{link,thread} Tag;//link=0表示指向左右孩子指针，thead=1表示指向前驱或后继的线索
template<class T>
struct Node{
    T data;//数据域
    Node<T> *lchild,rchild;//指针域
    Tag ltag,rtag;//标志域
};
template<class T>
class ThreadTree{
public:
    ThreadTree();//构造函数，建立中序线索链表
    ~ThreadTree();//析构函数，释放各结点空间
    Node<T> * findNext(Node<T> *bt);//查找结点bt的后继
    void inOrder();//中序遍历
private:
    Node<T> *root;//指向线索链表的头指针
    Node<T> * creat(Node<T> *bt);//构造函数调用，创建带线索标志的二叉链表
    void inThread(Node<T> *bt,Node<T> *pre);//构造函数调用，中序线索化
};
template<class T>
ThreadTree<T>::ThreadTree(){//构造函数
    root=creat(root);//建立带线索标志的二叉链表
    Node<T> *pre=NULL;//当前访问结点的前驱结点
    inThread(root,pre);//遍历二叉链表，建立线索
}
template<class T>
Node<T>* ThreadTree<T>::creat(Node<T> *bt){//建立带线索标志的二叉链表
    char ch;
    cin>>ch;
    if(ch=='#')//生成空树
        bt=NULL;
    else{
        bt=new Node<T>;
        bt->data=ch;
        bt->ltag=link;//左标志
        bt->rtag=link;//右标志
        bt->lchild=creat(bt->lchild);//递归建立左子树
        bt->rchild=creat(bt->rchild);//递归建立右子树
    }
}

template<class T>
void ThreadTree<T>::inThread(Node<T> *bt,Node<T> *pre){//中序线索化
    if(root!=NULL){
        inThread(bt->lchild,pre);//递归左子树线索化
        if(bt->lchild!=NULL){//没有左孩子
            bt->ltag=thread;//前驱线索
            bt->lchild=pre;//左孩子指针执行前驱
        }
        if(pre->rchild!=NULL){//没有右孩子
            pre->rtag=thread;//后继线索
            pre->rchild=bt;//右孩子指向后继
        }
        pre=bt;//保持pre指向bt的前驱
        inThread(bt->rchild,pre);//递归右子树线索化
    }
}
template<class T>
Node<T> * ThreadTree<T>::findNext(Node<T> *bt){//查找结点bt的后继
    Node<T> *q;//后继
    if(bt->rtag==thread)//已有线索，直接得到后继结点
        q=bt->rchild;
    else{
        q=bt->rchild;//工作指针q指向bt的右孩子
        while(q->ltag==link)//查找最左下结点
            q=q->lchild;
    }
    return q;
}
template<class T>
void ThreadTree<T>::inOrder(){//遍历
    if(root==NULL)
        return;
    else{
        Node<T> *p;
        p=root;
        while(p->ltag==link)//寻找中序遍历序列的第一个结点
            p=p->lchild;
        cout<<p->data;
        while(p->rchild!=NULL){//当结点p存在后继，依次访问其后继
            p=findNext(p);
            cout<<p->data;
        }
    }
}
