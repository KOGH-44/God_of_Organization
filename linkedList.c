#include "linkedList.h"

/*  노드 생성 */
Node *SLL_CreateNode(ElementType NewData) // ElementType형 매개변수를 받는다.
{
    Node *NewNode = (Node *)malloc(sizeof(Node)); /* 새로운 노드를 동적 할당한다. */

    NewNode->Data = NewData;  /*  데이터를 저장한다. */
    NewNode->NextNode = NULL; /*  다음 노드에 대한 포인터는 NULL로 초기화 한다. */

    return NewNode; /*  노드의 주소를 반환한다. */
}

/*  노드 소멸 */
void SLL_DestroyNode(Node *Node) // Node 포인터를 매개변수로 받는다.
{
    free(Node); /* 노드를 동적 할당 해제한다. */
}

/*  노드 추가 */
void SLL_AppendNode(Node **Head, Node *NewNode) // Node 포인터의 주소를 매개변수로 받는다.
{
    /*  헤드 노드가 NULL이라면 새로운 노드가 Head */
    if ((*Head) == NULL) /* Head가 NULL이면 새로운 노드가 Head가 된다. */
    {
        *Head = NewNode; // Head를 새로운 노드로 설정한다.
    }
    else
    {
        /*  테일을 찾아 NewNode를 연결한다. */
        Node *Tail = (*Head); // Head 노드를 Tail 포인터에 저장한다.
        while (Tail->NextNode != NULL) /* Tail 노드를 찾는다. */
        {
            Tail = Tail->NextNode; // 다음 노드로 이동한다.
        }

        Tail->NextNode = NewNode; /* Tail 노드의 다음 노드로 새로운 노드를 연결한다. */
    }
}

/*  노드 삽입 */
void SLL_InsertAfter(Node *Current, Node *NewNode) // Node 포인터를 매개변수로 받는다.
{
    NewNode->NextNode = Current->NextNode; /* 새로운 노드의 다음 노드를 Current의 다음 노드로 설정한다. */
    Current->NextNode = NewNode;           /* Current 노드의 다음 노드를 새로운 노드로 설정한다. */
}

/*  노드 헤드 삽입 */
void SLL_InsertNewHead(Node **Head, Node *NewHead) // Node 포인터의 주소를 매개변수로 받는다.
{
    if (Head == NULL) /* Head가 NULL이면 새로운 노드가 Head가 된다. */
    {
        (*Head) = NewHead;
    }
    else
    {
        NewHead->NextNode = (*Head); /* 새로운 노드의 다음 노드를 Head로 설정한다. */
        (*Head) = NewHead;           /* Head를 새로운 노드로 설정한다. */
    }
}

/*  노드 제거 */
void SLL_RemoveNode(Node **Head, Node *Remove) // Node 포인터의 주소를 매개변수로 받는다.
{
    if (*Head == Remove) /* Head 노드를 제거하는 경우 */
    {
        *Head = Remove->NextNode; /* Head를 다음 노드로 설정한다. */
    }
    else
    {
        Node *Current = *Head; // Head 노드를 Current 포인터에 저장한다.
        while (Current != NULL && Current->NextNode != Remove) /* 제거할 노드를 찾는다. */
        {
            Current = Current->NextNode; // 다음 노드로 이동한다.
        }

        if (Current != NULL)
            Current->NextNode = Remove->NextNode; /* 제거할 노드를 건너뛰어 다음 노드와 연결한다. */
    }
}

/*  노드 탐색 */
Node *SLL_GetNodeAt(Node *Head, int Location) // Node 포인터와 int형 매개변수를 받는다.
{
    Node *Current = Head; // Head 노드를 Current 포인터에 저장한다.

    while (Current != NULL && (--Location) >= 0) /* Location 위치의 노드를 찾는다. */
    {
        Current = Current->NextNode; // 다음 노드로 이동한다.
    }

    return Current; // 찾은 노드를 반환한다.
}

/*  노드 수 세기 */
int SLL_GetNodeCount(Node *Head) // Node 포인터를 매개변수로 받는다.
{
    int Count = 0;        // 노드 개수를 저장할 변수 Count를 0으로 초기화한다.
    Node *Current = Head; // 연결 리스트의 첫 번째 노드를 가리키는 포인터 Current를 선언하고, Head를 할당한다.

    while (Current != NULL) /* 노드의 개수를 센다. */
    {
        Current = Current->NextNode; // Current가 다음 노드를 가리키도록 한다.
        Count++;                     // 노드 개수를 1 증가시킨다.
    }

    return Count; // 노드 개수를 반환한다.
}