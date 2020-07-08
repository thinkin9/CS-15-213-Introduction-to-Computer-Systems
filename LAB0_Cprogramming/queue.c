#include<stdlib.h>
#include "queue.h"

queue_t* q_new() {
    queue_t* node = malloc(sizeof(queue_t));
    if (node == NULL) return NULL;  // �����Ҵ��� �� ������ return NULL;
    node->head = NULL;
    node->tail = NULL;
    node->size = 0;
    return node;
}

void q_free(queue_t* q) {
    if (q == NULL) return;
    // q_insert_head, q_insert_tail���� �� list_ele_t�� �����Ҵ��ϸ鼭 �߰����״�,
    // ��� queue�� free�ϰ��� �� ����, �����Ҵ��ߴ� list_ele_t�� ���鼭 free���ְ�
    // �������� queue_t�� �����ؾ���
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
    if (node == NULL) return false; // �����Ҵ��� �� ������, node == NULL -> return false;
    node->next = q->head;  //node->next�� ������ 1st element�� head��
    node->value = v;  
    q->head = node;  // queue�� ����Ű�� head�� node��
    if (q->size == 0) q->tail = node; // size�� 0�̶��, �߰��ϴ� element�� head����, tail��
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
    
    Structure�� ������ ���� ���ذ� �ʿ�
        struct <tag_name> { ... }
        typedef struct (<tag_name>) { ... } <type_name>
        ����� �� ���̰� �����Ѵ�
    
    
    namespace�� ����
    struct Foo{
        int var;
    };
    //Foo a; (X, because Foo is only defined in the tag namespace)
    //Struct Foo a; (O)

    //typedef struct Foo{
    //    int x;
    //}Foo;
    //Foo x; (O, because Foo is only defined in the typedef namespace

2. poinet variable�� ���� �� ���ÿ� define�� ��,
    int* var1_pnt, var2_pnt (X)
    int* var1_pnt, * var2_pnt (O)

3. queue_reverse����
    while (third != NULL) {
        second->next = first;
        first = second;
        second = third;
        third = second->next;
    }
    �̷� �������ϸ� second���� first�� �����Ű�����ϴ� second->next = first�� ���õȴ�
    �ֳ��ϸ� second�� third�� �ٽ� assign�ϱ� ��������
    �׷��� �׷��� ������ first, second, third�� �����ϰ� �� �ڿ� ���ָ� �ȴ�.
*/