#include<stdio.h>
#include<stdlib.h>

#define NUM 8   //queen數目

void lay(int *, int, int *);
int check(int *, int, int);


int main(){

    int queens[NUM];    //用來記錄每個放置的queen是在第幾列
    int *q = queens;
    int sol = 0;        //解的個數

    lay(q, NUM, &sol);

    printf("there is %d solutions to %d-queens problem.\n", sol, NUM);
}

//從第一行開始，用forloop嘗試每一列，如果檢查沒有衝突就用遞迴繼續往右邊下
void lay(int *q, int count, int *sol){
    if (count != 0){        
        for (int i = 0; i < NUM; i++){    
            if (check(q, NUM - count, i)){     
                *(q+NUM-count) = i;         //紀錄位置
                lay(q, count-1, sol); 
            }
        }
    }else {         //全部下完沒有衝突
        (*sol)++;}      
}

//跟已經下好的棋子比對
int check(int *q, int end, int tar){
    for (int i = 0; i < end; i++){
        int col = *(q+i);
        if (col == tar || col+i == tar+end || col-i == tar-end) return 0;   //三個條件分別為同一橫排、右上左下、左上右下
    }
    return 1;
}