# God_of_Organization

## C_first_project

✨이 세상의 모든 정리는 싹다 이걸루!!

편의점의 재고나 도서관의 도서자료등을 정리할 수 있는 프로그램을 작성해보고자 했습니다.

### 목표

![DB저장확인](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FIzifu%2FbtqNRIKzcIp%2Fk6ZT1Jw3apodVIRutwXww1%2Fimg.png)
- 학습한 linked list 를 사용한다.
- json 파일을 사용한다.
- git을 사용한 협업을 한다. 


### 사용한 json File 구조
파일명 "productList.json" 직접 만듬

```json
   "stock": [
        {
            "바코드": 8010192928102,
            "상품명": "농심 새우깡 90g",
            "분류": "식품류",
            "가격": 2000,
            "제조사": "농심",
            "재고량": 5,
            "유통기한": "2023-08-10"
        },
```

## Code Review

### haeder 

``` c
#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, free
#include <string.h> // strcpy
#include "cJSON.h" // JSON 파싱 라이브러리

#define EXPIR 50 // 유통기한 문자열 길이
#define S_SIZE 50 // 상품명, 분류, 제조사 문자열 길이
#define FILE_NAME "productList.json" // JSON 파일 이름
```

### 상품 구조체

```c
typedef struct Item 
{
    long long 바코드; // 바코드는 13자리 숫자
    char 상품명[S_SIZE]; // 상품명은 50자 이하의 문자열
    char 분류[S_SIZE]; // 분류는 50자 이하의 문자열
    int 가격;          // 가격은 0원 이상의 정수
    char 제조사[S_SIZE]; // 제조사는 50자 이하의 문자열
    int 재고량;            // 재고량은 0개 이상의 정수
    char 유통기한[EXPIR]; // 유통기한은 50자 이하의 문자열
    struct Item* next; // 다음 상품을 가리키는 포인터
} Item; // Item 구조체

Item* head = NULL; // 인벤토리의 첫 번째 상품을 가리키는 포인터
```

### 상품을 생성하는 함수
```c
Item* create_item(long long 바코드, char* 상품명, char* 분류, int 가격, char* 제조사, int 재고량, char* 유통기한)
{
    Item* new_item = (Item*)malloc(sizeof(Item)); // 상품을 생성
    new_item->바코드 = 바코드; // 상품의 바코드를 설정
    strcpy(new_item->상품명, 상품명); // 상품의 상품명을 설정
    strcpy(new_item->분류, 분류); // 상품의 분류를 설정
    new_item->가격 = 가격; // 상품의 가격을 설정
    strcpy(new_item->제조사, 제조사); // 상품의 제조사를 설정
    new_item->재고량 = 재고량; // 상품의 재고량을 설정
    strcpy(new_item->유통기한, 유통기한); // 상품의 유통기한을 설정
    new_item->next = NULL; // 상품의 다음 상품을 가리키는 포인터를 NULL로 설정
    return new_item; // 생성한 상품을 반환
}
```

### 인벤토리에 있는 상품을 삭제하는 함수
```c
void delete_item(long long 바코드)  // 상품의 바코드를 입력받음
{
    Item* temp = head; // 인벤토리의 첫 번째 상품을 가리키는 포인터를 생성
    Item* prev = NULL; // 이전 상품을 가리키는 포인터를 생성

    if (temp != NULL && temp->바코드 == 바코드) // 첫 번째 상품의 바코드가 입력한 바코드와 같으면
    {
        head = temp->next; // 인벤토리의 첫 번째 상품을 다음 상품으로 설정
        free(temp); // 첫 번째 상품을 삭제
        return;
    }

    while (temp != NULL && temp->바코드 != 바코드) // 인벤토리의 마지막 상품을 찾을 때까지 반복
    {
        prev = temp; // 이전 상품을 현재 상품으로 설정
        temp = temp->next; // 다음 상품으로 이동
    }
    if (temp == NULL) // 상품을 찾지 못하면
    {
        printf("상품을 찾을 수 없습니다.\n");
        return;
    }

    prev->next = temp->next; // 이전 상품의 다음 상품을 현재 상품의 다음 상품으로 설정
    free(temp); // 현재 상품을 삭제
}
```
### JSON 파일을 읽어서 인벤토리에 추가
```c
void load_inventory_from_file(const char *file_name)
{
    // 1. JSON 파일을 읽기 위해 열기
    FILE *file = fopen(file_name, "rb"); // 파일을 읽기 전용으로 열기
    if (file == NULL)   // 파일을 열지 못하면
    {
        printf("Unable to open %s for reading.\n", file_name);
        return;
    }

    // 2. 파일 전체를 버퍼에 읽어오기

    //fseek(file, 0, SEEK_END)를 사용하여 파일 포인터를 파일의 끝으로 이동시키고, 
    //long length = ftell(file)를 사용하여 현재 파일 포인터의 위치를 얻어 파일의 크기를 구합니다. 
    //마지막으로, fseek(file, 0, SEEK_SET)를 사용하여 파일 포인터를 다시 파일의 시작 위치로 되돌립니다.
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);


    char *buffer = (char *)malloc(length + 1); // 버퍼를 동적 할당
    if (buffer == NULL) // 버퍼를 할당하지 못하면 
    {
        printf("Unable to allocate memory for JSON buffer.\n");
        fclose(file);
        return;
    }
    
    fread(buffer, 1, length, file); // 파일을 버퍼에 읽어옴
    buffer[length] = '\0'; // 버퍼의 끝에 NULL 문자 추가
    fclose(file); // 파일 닫기

    // 3. cJSON 라이브러리를 사용하여 JSON 버퍼 구문 분석
    cJSON *json_data = cJSON_Parse(buffer); // 버퍼를 JSON 데이터로 파싱
    if (json_data == NULL) // JSON 데이터를 파싱하지 못하면
    {
        printf("Unable to parse JSON data.\n");
        free(buffer);
        return;
    }

    cJSON *json_inventory = cJSON_GetObjectItem(json_data, "stock"); // JSON 데이터에서 "stock" 항목을 가져옴

    // 4. JSON 배열을 순회하며 각 항목을 인벤토리 연결 리스트에 로드
    int inventory_size = cJSON_GetArraySize(json_inventory); // JSON 배열의 크기를 가져옴
    for (int i = 0; i < inventory_size; i++) // 배열의 크기만큼 반복
    {
        cJSON *json_item = cJSON_GetArrayItem(json_inventory, i); // 배열의 i번째 항목을 가져옴

        // 4.1 JSON 항목에서 값을 가져오기
        long long 바코드 = cJSON_GetObjectItem(json_item, "바코드")->valuedouble; // 바코드는 정수이지만 JSON에서는 실수로 저장되므로 valuedouble을 사용
        char *상품명 = cJSON_GetObjectItem(json_item, "상품명")->valuestring; //  상품명은 문자열이므로 valuestring을 사용
        char *분류 = cJSON_GetObjectItem(json_item, "분류")->valuestring;   //  분류도 문자열이므로 valuestring을 사용
        int 가격 = cJSON_GetObjectItem(json_item, "가격")->valueint; // 가격은 정수이므로 valueint를 사용
        char *제조사 = cJSON_GetObjectItem(json_item, "제조사")->valuestring; //  제조사도 문자열이므로 valuestring을 사용
        int 재고량 = cJSON_GetObjectItem(json_item, "재고량")->valueint; // 재고량도 정수이므로 valueint를 사용
        cJSON *json_유통기한 = cJSON_GetObjectItem(json_item, "유통기한"); // 유통기한은 문자열이지만 값이 없을 수도 있으므로 cJSON 포인터를 사용
        char *유통기한 = json_유통기한->type == cJSON_NULL ? "null" : json_유통기한->valuestring; // 유통기한이 NULL이면 "null"을 저장하고 아니면 valuestring을 저장

        // 4.2 항목을 인벤토리 연결 리스트에 추가
        add_item(바코드, 상품명, 분류, 가격, 제조사, 재고량, 유통기한);  // 인벤토리에 상품 추가
    }

    // 5. cJSON 객체와 버퍼 정리
    cJSON_Delete(json_data); // cJSON 객체 삭제
    free(buffer); // 버퍼 삭제
}
```

### 인벤토리를 JSON 파일로 저장
```c
void save_inventory_to_file(const char *file_name)   
{
    cJSON *json_data = cJSON_CreateObject(); // JSON 데이터를 저장할 cJSON 객체 생성
    cJSON *json_inventory = cJSON_CreateArray(); // JSON 배열을 저장할 cJSON 객체 생성

    Item *current = head; // 연결 리스트의 첫 번째 항목을 가리키는 포인터
    while (current != NULL) // 연결 리스트의 끝까지 반복
    {
        cJSON *json_item = cJSON_CreateObject(); // JSON 항목을 저장할 cJSON 객체 생성

        cJSON_AddNumberToObject(json_item, "바코드", current->바코드); // 바코드는 정수이므로 AddNumberToObject를 사용
        cJSON_AddStringToObject(json_item, "상품명", current->상품명); // 상품명은 문자열이므로 AddStringToObject를 사용
        cJSON_AddStringToObject(json_item, "분류", current->분류); // 분류도 문자열이므로 AddStringToObject를 사용
        cJSON_AddNumberToObject(json_item, "가격", current->가격); // 가격은 정수이므로 AddNumberToObject를 사용
        cJSON_AddStringToObject(json_item, "제조사", current->제조사); // 제조사도 문자열이므로 AddStringToObject를 사용
        cJSON_AddNumberToObject(json_item, "재고량", current->재고량); // 재고량도 정수이므로 AddNumberToObject를 사용
        cJSON_AddStringToObject(json_item, "유통기한", current->유통기한); // 유통기한도 문자열이므로 AddStringToObject를 사용

        cJSON_AddItemToArray(json_inventory, json_item); // JSON 배열에 JSON 항목 추가
        current = current->next; // 다음 항목으로 이동
    }

    cJSON_AddItemToObject(json_data, "stock", json_inventory); // JSON 데이터에 JSON 배열 추가

    char *json_string = cJSON_Print(json_data); // JSON 데이터를 문자열로 변환

    FILE *file = fopen(file_name, "wb"); // 파일 열기
    if (file == NULL) // 파일을 열지 못하면
    {
        printf("Unable to open %s for writing.\n", file_name);
        cJSON_Delete(json_data); // cJSON 객체 삭제
        return;
    }

    fwrite(json_string, strlen(json_string), 1, file); // 파일에 JSON 문자열 쓰기
    fclose(file); // 파일 닫기

    cJSON_Delete(json_data); // cJSON 객체 삭제
    free(json_string);  
}
```
### 인벤토리 연결 리스트의 모든 항목을 삭제
```c
void free_all_items()
{
    Item *current = head; // 연결 리스트의 첫 번째 항목을 가리키는 포인터
    Item *next_item; // 다음 항목을 가리키는 포인터

    while (current != NULL) // 연결 리스트의 끝까지 반복
    {
        next_item = current->next; 
        free(current);
        current = next_item;
    }
}
```

### 메인부 ------------
```c
int main()
{   
    // 프로그램 시작 시 JSON 파일에서 인벤토리 불러오기
    const char *file_name = FILE_NAME; // JSON 파일 이름
    load_inventory_from_file(file_name); // JSON 파일에서 인벤토리 불러오기

    int 선택;
    long long 바코드;
    int 재고량;
    char 상품명[50], 분류[50], 제조사[50], 유통기한[11];
    int 가격;
    while (1)
    {
        printf("\n{인벤토리 관리 시스템}\n\n");
        printf("1. 상품 추가\n");
        printf("2. 상품 목록 표시\n");
        printf("3. 상품 검색\n");
        printf("4. 상품 삭제\n");
        printf("5. DB에 저장\n\n");
        printf("6. 종료\n\n");
        printf("원하는 명령을 선택하세요: ");
        scanf("%d", &선택);
        printf("\n");

        switch (선택)
        {
        case 1: // 상품 추가
            puts("\t\t[1. 상품 추가]\n\n");
            printf("상품 바코드 입력: ");
            scanf("%lld", &바코드);
            printf("상품명 입력: ");
            scanf(" %[^\n]%*c", 상품명);
            printf("분류 입력: ");
            scanf(" %[^\n]%*c", 분류);
            printf("가격 입력: ");
            scanf("%d", &가격);
            printf("제조사 입력: ");
            scanf(" %[^\n]%*c", 제조사);
            printf("재고량 입력: ");
            scanf("%d", &재고량);
            printf("유통기한 입력 (YYYY-MM-DD): ");
            scanf(" %10s", 유통기한);
            add_item(바코드, 상품명, 분류, 가격, 제조사, 재고량, 유통기한);
            break;
        case 2: // 상품 목록 표시
            puts("\t\t[2. 상품 목록 표시]\n\n");
            display_items();
            break;
        case 3: // 상품 검색
            puts("\t\t[3. 상품 검색]\n\n");
            printf("상품 바코드 입력: ");
            scanf("%lld", &바코드);
            Item* item = search_item(바코드);
            if (item)
            {
                printf("바코드: %lld, 상품명: %s, 분류: %s, 가격: %d, 제조사: %s, 재고량: %d, 유통기한: %s\n",
                       item->바코드, item->상품명, item->분류, item->가격, item->제조사, item->재고량, item->유통기한);
            }
            else
            {
                printf("상품을 찾을 수 없습니다.\n");
            }
            break;
        case 4: // 상품 삭제
            puts("\t\t[4. 상품 삭제]\n\n");
            printf("상품 바코드 입력: ");
            scanf("%lld", &바코드);
            delete_item(바코드);
            break;
        
        case 5: // DB 저장
            printf("인벤토리 저장 중...\n\n");
            save_inventory_to_file(file_name);
            printf("인벤토리 저장 완료.\n");
            break;

        case 6: // 종료
            printf("종료 중...\n\n");
            free_all_items(); // 메모리 해제
            exit(0);
            break;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    return 0;
}
```
![목록추가](https://user-images.githubusercontent.com/76278512/230550353-68463aab-135e-4bec-9af8-a8aa1049dac6.png)

![목록출력](https://user-images.githubusercontent.com/76278512/230550395-dade252e-a3c7-422b-b461-cdecd33452c8.png)

![상품검색](https://user-images.githubusercontent.com/76278512/230550421-a1a8fa1f-9c67-44c7-ad12-49dd24924079.png)

![상품삭제](https://user-images.githubusercontent.com/76278512/230550453-013c3e14-13f4-467f-81eb-9cd3f0b549c0.png)

![DB저장](https://user-images.githubusercontent.com/76278512/230550485-d0288430-dc97-423b-be12-62f0a6326bbc.png)

![DB저장확인](https://user-images.githubusercontent.com/76278512/230550495-a74f47e4-4326-4e84-a479-4b629c36843b.png)
