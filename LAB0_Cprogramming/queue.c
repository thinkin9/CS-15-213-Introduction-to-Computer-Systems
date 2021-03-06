#include<stdlib.h>
#include "queue.h"

queue_t* q_new() {
    queue_t* node = malloc(sizeof(queue_t));
    if (node == NULL) return NULL;  // 동적할당할 수 없으면 return NULL;
    node->head = NULL;
    node->tail = NULL;
    node->size = 0;
    return node;
}

void q_free(queue_t* q) {
    if (q == NULL) return;
    // q_insert_head, q_insert_tail에서 각 list_ele_t를 동적할당하면서 추가할테니,
    // 모든 queue를 free하고자 할 때는, 동적할당했던 list_ele_t를 돌면서 free해주고
    // 마지막에 queue_t를 해제해야함
    list_ele_t* pnt = q->head, * cur;
    while (pnt != NULL) {
        cur = pnt;
        pnt = pnt->next;
        free(cur);
    }
    free(q);
}

bool q_insert_head(queue_t* q, int v) {
    if (q == NULL) return false;
    list_ele_t* node = malloc(sizeof(list_ele_t));
    if (node == NULL) return false; // 동적할당할 수 없으면, node == NULL -> return false;
    node->next = q->head;  //node->next를 기존의 1st element의 head로
    node->value = v;  
    q->head = node;  // queue가 가리키는 head에 node를
    if (q->size == 0) q->tail = node; // size가 0이라면, 추가하는 element가 head이자, tail임
    q->size++;
    return true;
}

bool q_insert_tail(queue_t* q, int v) {
    if (q == NULL) return false;
    list_ele_t* node = malloc(sizeof(list_ele_t));
    if (node == NULL) return false;
    node->next = NULL;
    node->value = v;
    if (q->size == 0) {
        q->head = node;
        q->tail = node;
    }
    else {
        q->tail->next = node;
        q->tail = node;
    }
    q->size++;
    return true;
}

bool q_remove_head(queue_t* q, int* vp) {
    if (q == NULL || q->head == NULL) return false;
    list_ele_t* temp = q->head;
    if (vp != NULL) *vp = temp->value;
    q->head = q->head->next;
    free(temp);
    q->size--;
    return true;
}

int q_size(queue_t* q) {
    if (q == NULL) return 0;
    return q->size;
}

void q_reverse(queue_t* q) {
    /* Return if list is NULL, empty or size=1 */
    if (q == NULL || q->size == 0 || q->size == 1) return;
    list_ele_t* start = q->head, *end = q->tail;
    list_ele_t* first = q->head, *second, *third;
    second = first->next;
    third = second->next;
    second->next = first;
    first->next = NULL;
    while (third != NULL) {
        first = second;
        second = third;
        third = second->next;
        second->next = first;
    }
    q->head = end;
    q->tail = start;
}

/*
1. typedef struct
    typedef: typedef is a reserved keyword in the C and C++ programming languages. 
            It is used to create an alias name for another data type.
               As such, it is often used to simplify the syntax of declaring complex data structures consisting of struct and union types
               , but is just as common in providing specific descriptive type names for integer data types of varying lengths.
    typedef struct <tag_name>{
    } <type_name>
    https://finsternis.tistory.com/27
    https://ingorae.tistory.com/481

    Difference between 'struct' and 'typedef struct' in C++?
    https://stackoverflow.com/questions/612328/difference-between-struct-and-typedef-struct-in-c
    
    Structure의 문법에 대한 이해가 필요
        struct <tag_name> { ... }
        typedef struct (<tag_name>) { ... } <type_name>
        사용할 때 차이가 존재한다
    
    
    namespace의 차이
    struct Foo{
        int var;
    };
    //Foo a; (X, because Foo is only defined in the tag namespace)
    //Struct Foo a; (O)

    //typedef struct Foo{
    //    int x;
    //}Foo;
    //Foo x; (O, because Foo is only defined in the typedef namespace

2. poinet variable을 여러 개 동시에 define할 때,
    int* var1_pnt, var2_pnt (X)
    int* var1_pnt, * var2_pnt (O)

3. queue_reverse에서
    while (third != NULL) {
        second->next = first;
        first = second;
        second = third;
        third = second->next;
    }
    이런 식으로하면 second에서 first를 연결시키고자하는 second->next = first가 무시된다
    왜냐하면 second를 third로 다시 assign하기 때문이지
    그래서 그러한 연결을 first, second, third를 설정하고 난 뒤에 해주면 된다.
*/