#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_LEN 30

int cmp_name(const void *, const void *);
int cmp_score(const void *, const void *);

typedef struct studentscore
{
	char name[MAX_LEN];
	int score;
}ss;


int main ()
{
    ss input;
	ss *data = NULL;
    int n = 0;
	

	FILE *infile = fopen ("unsorted_studentscore", "r");
    FILE *outfile = fopen("sorted_studentscore", "w");
	if (infile == NULL || outfile == NULL){
		printf("\nError opening file\n");
		exit (1);
	}

//讀資料
	while(fread(&input, sizeof(ss), 1, infile)){
        data = realloc(data, sizeof(ss)*(n+1));
        *(data+n) = input;
        n++;
    }

//照名字排、照分數排
    qsort(data, n, sizeof(ss), cmp_name);
    qsort(data, n, sizeof(ss), cmp_score);

    for (int i = 0; i < n; i++) fprintf(outfile, "%s %d\n", (data+i)->name, (data+i)->score);

// close file
	fclose (infile);
    fclose(outfile);
    free(data);
	return 0;
}

int cmp_name(const void *a, const void *b){
    return _stricmp(((ss *)a)->name, ((ss *)b)->name);
}

int cmp_score(const void *a, const void *b){
    return (((ss *)a)->score>((ss *)b)->score)? 1: ((((ss *)a)->score<((ss *)b)->score)? -1: 0);
}
