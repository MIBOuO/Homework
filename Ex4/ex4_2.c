
#include<stdio.h>
#include<stdlib.h>

int check(int *, int, int);
void draw(int *, int, int, int);
void printResult(int *, int);

int main(){

    //input
    int n, k;
    printf("input n k: ");
    scanf("%d %d", &n, &k);
    if (k > n){
        printf("k should be no more than n");
        return 0;
    }

    int *result = malloc(k*sizeof(int));    //放結果

    //排組
    draw(result, n, k, 0);

    free(result);
}

void draw(int *result, int n, int k, int count){    //count: 已經取了幾個
    if (count == k) printResult(result, k);    //取完指定數量就印結果，並結束遞迴
    else
        for (int i = 0; i < n; i++)
            if (check(result, count, i+1)){    //如果result裡面已經有重複的元素就跳過，
                *(result+count) = i+1;         //否則就放到result裡
                draw(result, n, k, count+1);
            }  
}

//檢查target和result裡已經取好的元素有沒有重複。 沒重複回傳1
int check(int *a, int count, int target){
    for (int i = 0; i < count; i++)
        if (*(a+i) == target)
            return 0;
    return 1;
}

//印結果
void printResult(int *result, int size){
    for (int i = 0; i < size; i++){
        printf("%d", *(result+i));
        if (i == size-1)
            printf("\n");
        else
            printf(" ");
    }
}
