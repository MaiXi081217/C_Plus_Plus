#include <iostream>
using namespace std;

// 定义链表节点结构体  
struct ListNode {
    int val;    // 定义内容
    ListNode* next; // 定义下一位的指针
    int num;
    ListNode(int x) : val(x), num(0), next(NULL){} // 定义了一个构造函数，用于初始化val和next。
};
// 定义链表类  
class LinkedList {
public:
    LinkedList() {
        head = NULL;    //头节点为空
    }

    // 在链表末尾插入一个节点  
    void Append(int val) 
    {  // 传入值val
        ListNode* new_node = new ListNode(val);     // new一个ListNode对象，传入val值，并将其指针传入new_node
        if (head == NULL) {     //如果头节点为空
            head = new_node;    //将新节点的指针传入head中
        }
        else {      //如果头节点不为空
            ListNode* curr = head;      //将头节点的指针传入curr中
            while (curr->next != NULL) {        //当curr的下一位节点不为空时
                curr = curr->next;              //指向下一个节点
            }   
            new_node->num = curr->num+1;        //将num序号自增
            curr->next = new_node;              //将new_node中的内容（新的ListNode对象的指针）传入curr中
            new_node->next = NULL;              //将new_node的下一位指向空，确保为最后一个节点
        }
    }
    // 删除链表最后一个节点
    void Delete()
    {
        if (head == NULL){   //如果头节点为空
            cout << "error,link have no node\n";
            return;         //返回
        }
        else{        //如果头节点不为空     
            if (head->next == NULL){     //如果next为空（链表只有一个节点）
                
                delete head;//删除头节点
                head = NULL;           //释放头节点内存
                //释放内存
                cout << "Delete complete,link is empty\n";
                return;
            }
            ListNode* curr = head;
            ListNode* tmp = NULL;       
            while (curr->next != NULL){
                tmp = curr;     //存入最后一个节点
                curr = curr->next;  //存入倒数第二个节点
                if (curr->next == NULL){
                    delete curr;     //释放最后一个节点
                    tmp->next = NULL;       //将倒数第二个节点的next指向空
                    return;
                }
            }
        }
   }
    // 打印链表中的所有节点值  
    void print() {
        ListNode* curr = head;
        while (curr != NULL) {
            printf("[%d]", curr->val);
            curr = curr->next;
        }
        cout << endl;
    }
    // 改变链表中指定节点的值
    void change(int Num, int Val) {
        ListNode* curr = head;
        while (curr->num != Num ) {
            curr = curr->next;
            if (curr == NULL) {
                cout << "There is no such serial number" << endl;
                return;
            }
        }
        curr->val = Val;
        printf("the num %d has been modified to %d\n", Num,Val);
    }
    // 查找节点
    void find(int x) {
        ListNode* curr = head;
        while (curr->num != x){
            curr = curr->next;
            if (curr == NULL) {
            cout << "There is no such serial number" << endl;
            return;
            }
        } 
        printf("num %d is [%d]\n",x,curr->val);
    }
private:
    ListNode* head; // 链表头节点指针  
};
int main() {
    LinkedList my_list;
    my_list.Append(1); // 在链表末尾插入节点 1  
   // my_list.Append(2); // 在链表末尾插入节点 2  
   // my_list.Append(3); // 在链表末尾插入节点 3  
    my_list.print(); // 输出链表中的所有节点值：1 2 3   
    my_list.find(2);
    my_list.change(2, 5);
    my_list.print();//1 2 5
   /* my_list.Delete();
    my_list.print();//1,2
    my_list.Delete();
    my_list.print();//1
    my_list.Delete();//empty
    my_list.print();
    my_list.Delete();*/
    

    /*LinkedList my_list2;
    my_list2.Delete();
    my_list2.Append(1);
    my_list2.Delete();
    my_list2.print();

    my_list2.Append(1); 
    my_list2.print();*/
    return 0;
}