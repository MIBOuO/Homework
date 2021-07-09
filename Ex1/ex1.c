#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 100

void swap(void *, void *, void *);
void selection_sort();
void insertion_sort();
void bubble_sort();

char *infile = "unsorted_name";
char *outfile = "sorted_name";
char **data = NULL;
char line[MAX_LEN];
int n = 0;

int main(){
//讀資料
    FILE *fp = fopen(infile, "r");
    if (fp == NULL){
        printf("can't open file");
        return 1;
    }        

    while(fgets(line, MAX_LEN, fp)){
        data = (char**)realloc(data, sizeof(char**)*(n+1));
        line[strcspn(line, "\n")] = '\0';
        data[n] = (char *)malloc((MAX_LEN)*sizeof(char));
        strcpy(data[n++], line);
    }
    fclose(fp);

//sort
    selection_sort();
    insertion_sort();
    bubble_sort();


//寫資料
    FILE *output = fopen(outfile, "w");    
    for (int i = 0; i < n; i++) fprintf(output, "%s\n", data[i]);
    fclose(output);

    for (int i = 0; i < n; i++) free(data[i]);
    free(data);
    return 0;
}

void swap(void *a, void *b, void *tmp){
    if (a != NULL && b != NULL && tmp != NULL){
        memcpy(tmp, a, MAX_LEN);
        memcpy(a, b, MAX_LEN);
        memcpy(b, tmp, MAX_LEN); 
    }
}

void selection_sort(){
    for (int i = 0; i < n-1; i++){
        int max = i;
        for (int j = i+1; j < n; j++)
            if (strcmp(data[j], data[max]) < 0)
                max = j;
        if(max != i) swap(data[i], data[max], line);
    }
}

void insertion_sort(){
    for (int i = 1; i < n; i++)
        for (int j = i-1; j >= 0; j--)
            if (strcmp(data[j], data[j+1]) > 0)
                swap(data[j+1], data[j], line);
}

void bubble_sort(){
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++)
            if (strcmp(data[j], data[j+1]) > 0)
                swap(data[j], data[j+1], line);
}
