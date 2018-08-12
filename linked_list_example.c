#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
    #include <stdio.h> =>標準輸入輸出函數 
    #include <stdlib.h> =>數值與字串轉換.記憶體配置.亂數與其他有用函數 
    #include <iostream.h> =>標準輸入輸出函數 
    #include <math.h>=>數算運算函數 
    #include <string.h>=>C-形態字串處理函數 
    #include <algorithm.h>=>標準資料庫容器處理資料庫的函數 
    #include <functional.h>=>標準資料庫演算的類別與函數 
    #include <time.h>=>處理時間日期函數 
    #include <memory.h>=>標準資料庫記憶體配置的類別與函數
*/

// 定義list_node結構，注意備註內容
typedef struct _list_node
{
    int val;
    struct _list_node * next;
} list_node;
/*  備註：
    上面的寫法並不能簡化成
    typedef struct{
        int val;
        list_node * next;
    } list_node;
    原因在於，上述寫法可拆為
    type expression list_node
    其中expression的部份為
    struct{
        int val;
        list_node * next;
    }
    此struct中的成員next的type為list_node *，
    但此時list_node為undefined(因為list_node要到大括號外才會出現))，
    因此此寫法會產生error。
    同理，若struct中沒有出現undefined的名稱，如下：
    typedef struct {
        int val1;
        int val2;
    } test_struct;
    資料型態int已經定義，所以以上寫法不會產生error。
*/

// 走訪全部node，並print出來
void print_all_node(list_node **head)
{
    list_node *current = *head;
    while(current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

// append list node at end
// 為了能改變作為引數的head的值，所以使用pointer of pointer
void append_node(list_node **address_of_head, int input)
{
    // create new list node
    list_node *new_node_ptr = (list_node *)malloc(sizeof(list_node));
    new_node_ptr->val = input;
    new_node_ptr->next = NULL;
    // condition 1：linked list is empty
    if(*address_of_head == NULL) {
        *address_of_head = new_node_ptr;
        return;
    }
    // condition 2：linked list is not empty
    list_node *current = *address_of_head;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = new_node_ptr;
}

// append list node at first, also called "push" 
// 同上，使用pointer of pointer
void push_node(list_node **address_of_head, int input)
{
    // create new node
    list_node *new_node_ptr = (list_node *)malloc(sizeof(list_node));
    new_node_ptr->val = input;
    new_node_ptr->next = *address_of_head;
    // make head point to new node
    *address_of_head = new_node_ptr;
}

// remove the first item and get its value
int pop_node(list_node **address_of_head)
{
    // condition 1：linked list is empty
    if(*address_of_head == NULL) {
        printf("linked list is empty, cannot pop any thing");
        return -1;
    }
    // condition 2：linked list is not empty
    int return_value = (*address_of_head)->val;
    // 存取原本第一個list_node的address
    list_node *tmp = *address_of_head;
    // 將原本head的位置free掉
    free(tmp);
    // 更新head，讓head指向新的head
    *address_of_head = (*address_of_head)->next;
    
    return return_value;
}

// remove last node and pop its value
int pop_last_node(list_node **address_of_head)
{
    // condition 1：linked list is empty
    if(*address_of_head == NULL) {
        printf("linked list is empty, cannot pop any thing");
        return -1;
    }
    // condition 2：linked list has only one list_node
    if((*address_of_head)->next == NULL) {
        printf("linked list has only one node");
        int return_value = (*address_of_head)->val;
        *address_of_head = NULL;
        return return_value;
    }
    // condition 3：linked list is not empty, has more than one list_node
    // 將指標移到linked list的尾端，讓previous指向最後的list_node的前一個
    list_node *previous = *address_of_head;
    while(previous->next->next != NULL) {
        previous = previous->next;
    }
    // 儲存要回傳的值
    int return_value = previous->next->val;
    // 將最後的的list_node給free掉
    free(previous->next);
    previous->next = NULL;
    return return_value;
}

// Removing a specific list_node
int remove_by_index(list_node **head, int n)
{
    return -1;
}

void main()
{
    list_node *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);
    push_node(&head, 6);
    print_all_node(&head);
    printf("\n");
    pop_node(&head);
    pop_node(&head);
    pop_node(&head);
    print_all_node(&head);
    printf("\n");
    pop_last_node(&head);
    print_all_node(&head);
    printf("\n");
    pop_last_node(&head);
    print_all_node(&head);
    printf("\n");
    pop_last_node(&head);
    print_all_node(&head);
    printf("\n");

    return;
}