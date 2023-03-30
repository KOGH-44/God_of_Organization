#pragma once // 중복 포함 방지
#include <stdio.h> // 표준 입출력 함수가 선언된 헤더 파일
#include <stdlib.h> // malloc, free 함수가 선언된 헤더 파일

typedef int ElementType; // ElementType를 int형으로 정의

typedef struct tagNode // 노드를 구성하는 구조체
{
    ElementType Data;         // 노드의 데이터를 저장하는 변수
    struct tagNode *NextNode; // 다음 노드를 가리키는 포인터
} Node; // Node를 구조체 tagNode로 정의

/* 함수 원형 선언 */
Node *SLL_CreateNode(ElementType NewData);          // 새로운 노드를 생성하는 함수
void SLL_DestroyNode(Node *Node);                   // 노드를 제거하는 함수
void SLL_AppendNode(Node **Head, Node *NewNode);    // 노드를 리스트의 끝에 추가하는 함수
void SLL_InsertAfter(Node *Current, Node *NewNode); // 현재 노드 뒤에 새로운 노드를 추가하는 함수
void SLL_InsertNewHead(Node **Head, Node *NewHead); // 리스트의 헤드에 새로운 노드를 추가하는 함수
void SLL_RemoveNode(Node **Head, Node *Remove);     // 노드를 리스트에서 제거하는 함수
Node *SLL_GetNodeAt(Node *Head, int Location);      // 리스트에서 특정 위치에 있는 노드를 반환하는 함수
int SLL_GetNodeCount(Node *Head);                   // 리스트에 있는 노드의 개수를 반환하는 함수