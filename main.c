#include "linkedList.h"

int main(void)
{
    int i = 0;
    int Count = 0;
    Node *List = NULL;    // 연결 리스트의 헤드 노드
    Node *Current = NULL; // 현재 노드를 가리키는 포인터
    Node *NewNode = NULL; // 새로운 노드를 가리키는 포인터

    /*  노드 5개 추가 */
    for (i = 0; i < 5; i++) // 0부터 4까지 반복
    {
        NewNode = SLL_CreateNode(i);    // 새로운 노드 생성
        SLL_AppendNode(&List, NewNode); // 연결 리스트의 끝에 노드 추가
    }

    NewNode = SLL_CreateNode(-1);      // 새로운 노드 생성
    SLL_InsertNewHead(&List, NewNode); // 연결 리스트의 맨 앞에 노드 추가

    NewNode = SLL_CreateNode(-2);      // 새로운 노드 생성
    SLL_InsertNewHead(&List, NewNode); // 연결 리스트의 맨 앞에 노드 추가

    /*  리스트 출력 */
    Count = SLL_GetNodeCount(List); // 연결 리스트의 노드 개수 계산
    for (i = 0; i < Count; i++)    // 0부터 Count-1까지 반복
    {
        Current = SLL_GetNodeAt(List, i);            // i번째 노드를 가리키는 포인터 반환
        printf("List[%d] : %d\n", i, Current->Data); // 노드의 데이터 출력
    }

    /*  리스트의 세번째 노드 뒤에 새 노드 삽입 */
    printf("\nInserting 3000 After [2]...\n\n");

    Current = SLL_GetNodeAt(List, 2); // 2번째 노드를 가리키는 포인터 반환
    NewNode = SLL_CreateNode(3000);   // 새로운 노드 생성

    SLL_InsertAfter(Current, NewNode); // 2번째 노드 뒤에 새로운 노드 삽입

    /*  리스트 출력 */
    Count = SLL_GetNodeCount(List); // 연결 리스트의 노드 개수 계산
    for (i = 0; i < Count; i++)
    {
        Current = SLL_GetNodeAt(List, i);            // i번째 노드를 가리키는 포인터 반환
        printf("List[%d] : %d\n", i, Current->Data); // 노드의 데이터 출력
    }

    /*  모든 노드를 메모리에서 제거     */
    printf("\nDestroying List...\n");

    for (i = 0; i < Count; i++)
    {
        Current = SLL_GetNodeAt(List, 0); // 첫 번째 노드를 가리키는 포인터 반환

        if (Current != NULL)
        {
            SLL_RemoveNode(&List, Current); // 노드 제거
            SLL_DestroyNode(Current);       // 노드 메모리 해제
        }
    }

    return 0;
}