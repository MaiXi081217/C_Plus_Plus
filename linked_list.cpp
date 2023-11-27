#include <iostream>
using namespace std;

// ��������ڵ�ṹ��  
struct ListNode {
    int val;    // ��������
    ListNode* next; // ������һλ��ָ��
    int num;
    ListNode(int x) : val(x), num(0), next(NULL){} // ������һ�����캯�������ڳ�ʼ��val��next��
};
// ����������  
class LinkedList {
public:
    LinkedList() {
        head = NULL;    //ͷ�ڵ�Ϊ��
    }

    // ������ĩβ����һ���ڵ�  
    void Append(int val) 
    {  // ����ֵval
        ListNode* new_node = new ListNode(val);     // newһ��ListNode���󣬴���valֵ��������ָ�봫��new_node
        if (head == NULL) {     //���ͷ�ڵ�Ϊ��
            head = new_node;    //���½ڵ��ָ�봫��head��
        }
        else {      //���ͷ�ڵ㲻Ϊ��
            ListNode* curr = head;      //��ͷ�ڵ��ָ�봫��curr��
            while (curr->next != NULL) {        //��curr����һλ�ڵ㲻Ϊ��ʱ
                curr = curr->next;              //ָ����һ���ڵ�
            }   
            new_node->num = curr->num+1;        //��num�������
            curr->next = new_node;              //��new_node�е����ݣ��µ�ListNode�����ָ�룩����curr��
            new_node->next = NULL;              //��new_node����һλָ��գ�ȷ��Ϊ���һ���ڵ�
        }
    }
    // ɾ���������һ���ڵ�
    void Delete()
    {
        if (head == NULL){   //���ͷ�ڵ�Ϊ��
            cout << "error,link have no node\n";
            return;         //����
        }
        else{        //���ͷ�ڵ㲻Ϊ��     
            if (head->next == NULL){     //���nextΪ�գ�����ֻ��һ���ڵ㣩
                
                delete head;//ɾ��ͷ�ڵ�
                head = NULL;           //�ͷ�ͷ�ڵ��ڴ�
                //�ͷ��ڴ�
                cout << "Delete complete,link is empty\n";
                return;
            }
            ListNode* curr = head;
            ListNode* tmp = NULL;       
            while (curr->next != NULL){
                tmp = curr;     //�������һ���ڵ�
                curr = curr->next;  //���뵹���ڶ����ڵ�
                if (curr->next == NULL){
                    delete curr;     //�ͷ����һ���ڵ�
                    tmp->next = NULL;       //�������ڶ����ڵ��nextָ���
                    return;
                }
            }
        }
   }
    // ��ӡ�����е����нڵ�ֵ  
    void print() {
        ListNode* curr = head;
        while (curr != NULL) {
            printf("[%d]", curr->val);
            curr = curr->next;
        }
        cout << endl;
    }
    // �ı�������ָ���ڵ��ֵ
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
    // ���ҽڵ�
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
    ListNode* head; // ����ͷ�ڵ�ָ��  
};
int main() {
    LinkedList my_list;
    my_list.Append(1); // ������ĩβ����ڵ� 1  
   // my_list.Append(2); // ������ĩβ����ڵ� 2  
   // my_list.Append(3); // ������ĩβ����ڵ� 3  
    my_list.print(); // ��������е����нڵ�ֵ��1 2 3   
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