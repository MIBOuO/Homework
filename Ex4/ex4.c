
#include<stdio.h>
#include<stdlib.h>

typedef struct obj obj;
struct obj{
    int value;
    obj *next;      //linked list 建置好next就不會再變動
    obj *remain;    //a b c, b被取走後，a的remain就會指到c, 但是a的next仍是指向b
};

void draw(obj *, int, int *, int);
void reset(obj *);
void printResult(int *, int);
int check(int *, int);

int main(){

//input
    int n, k;
    printf("input n k: ");
    scanf("%d %d", &n, &k);
    if (k > n){
        printf("k should be no more than n");
        return 0;
    }
    int *result = malloc(k*sizeof(int));    //用來放排組的結果

//build linked list with n elements
    obj *head, *current;   
    head = (obj *)malloc(sizeof(obj));
    head->value = 1;
    current = head;

    for (int i = 0; i < n-1; i++){
        current->next = (obj *)malloc(sizeof(obj));
        current->remain = current->next;
        current = current->next;
        current->value = i+2;
    }
    current->next = NULL;
    current->remain = NULL;
    current = head;

//permutation and combination
    draw(head, k, result, k);

//free dynamic memory
    obj *temp = head;
    while(temp != NULL){
        current = temp;
        temp = temp->next;
        free(current);
    }
}

void draw(obj *head, int count, int *result, int k){
    obj *current = head;
    obj *previous = head;

    //取完指定數目就印出來
    if (count == 0){
        printResult(result, k);
        return;
    }

    //走訪從head開始的每個元素，依序取出放入result, 再用遞迴走訪剩下的其他元素
    while(current != NULL){
        *(result+k-count) = current->value; 

        if(current == head){
            draw(head->remain, count-1, result, k);
        }
        else{
            previous->remain = current->remain; //取出current
            draw(head, count-1, result, k);
        }
        reset(head);
        if (current != head) previous = previous->remain;
        current = current->remain;        
    }
}

//把取走的元素插回來，以利進行下一種排列組合
void reset(obj *current){
    while(current != NULL){
        current->remain = current->next;
        current = current->next;
    }
}

//印結果
void printResult(int *result, int size){
    if (check(result, size)){
        for (int i = 0; i < size; i++){
            printf("%d", *(result+i));
            if (i == size-1)
                printf("\n");
            else
                printf(" ");
        }
    }
}

//確保元素不重複
int check(int *a, int size){
    for (int i = 0; i < size-1; i++)
        for (int j = i + 1; j < size; j++) 
            if (*(a+i) == *(a+j)) 
                return 0;
    return 1;
}

