#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void readSudoku(char *, FILE *);
void printSudoku(int *);
int init(char [], int [], int);
int solve(char [], int[], int);
int check(int [], int, int);

int main(int argc, const char * argv[]) {
    
    char file_name[] = "sudoku.csv";
    FILE *fp;
    fp = fopen(file_name, "r");    
    if (!fp) {
        fprintf(stderr, "failed to open file for reading\n");
        return 1;
    }
   
    char sudoku[81];    //儲存csv讀進來的數獨題目
    int sol[81] = {0};  //解答

    readSudoku(sudoku, fp);
    fclose (fp);

    init(sudoku, sol, 0);

    if (solve(sudoku, sol, 0))
        printSudoku(sol);
    else
        printf("there is no solution to this sudoku\n");

    return 0;
}

//將csv讀進一維陣列裡
void readSudoku(char *sudoku, FILE *fp){
    char line[20];
    char *token = NULL;    
    for (int i = 0; fgets(line, 20, fp); i++){
        token = strtok(line, ",");
        for (int j = 0; token; j++){
                *(sudoku+i*9+j) = *token;
                token = strtok(NULL, ",");
        }        
    }
}

//印出來
void printSudoku(int *sol){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
            printf("%d ", *(sol+i*9+j));        
        printf("\n");
    }
}

//將sol初始化，把題目給的數字代進去，底線就寫0
int init(char sudoku[81], int sol[81], int initpoint){
    for (int i = initpoint; i < 81; i++)
        if (sudoku[i] == '_')
            sol[i] = 0;
        else
            sol[i] = (int)sudoku[i]-48;
}

//從第index個開始解，每個空格都是著代入1~9，如果有可能解就用遞迴從index+1繼續解，
//沒有可能解就回到上一步試試其他解。
int solve(char sudoku[81], int sol[81], int index){
    
    if (index == 81) return 1;  //全部填完就是解答
    if (sudoku[index] == '_'){
        for (int j = 1; j <= 9; j++)
            if (check(sol, index, j)){
                sol[index] = j;
                if (solve(sudoku, sol, index+1))
                    return 1;
            }
        sol[index] = 0;      
        return 0;   
    }else{
        sol[index] = (int)sudoku[index]-48;
        return solve(sudoku, sol, index+1)?1:0;
    }

}

//檢查合不合。三個條件分別為同一列、同一行、同一區塊
int check(int sol[81], int index, int tar){
    for (int i = 0; i < 9; i++)
        if (tar == sol[(index/9)*9 + i] || 
            tar == sol[index%9 + i*9] || 
            tar == sol[(index/27)*27 + ((index%9)/3)*3 + (i/3)*9 + i%3]) return 0;
    return 1;
}

