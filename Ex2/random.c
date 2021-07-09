#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>

#define MAX_LEN 30

struct studentscore
{
	char name[MAX_LEN];
	int score;
};

int main ()
{	
    srand(time(NULL));

	FILE *fp = fopen ("unsorted_studentscore", "w");
    FILE *namelist = fopen("namelist", "r");
	if (fp == NULL){
		fprintf(stderr, "unsorted_studentscore could not open\n");
		return 1;
	}
    if (namelist == NULL){
		fprintf(stderr, "namelist could not open\n");
		return 1;
	}

    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, namelist)){
        line[strcspn(line, "\n")] = '\0';
        struct studentscore input = {.score = rand()*(100)/RAND_MAX};
        strncpy(input.name, line, MAX_LEN-1);
        fwrite (&input, sizeof(struct studentscore), 1, fp);
    }

	// close file
	fclose (fp);
    fclose(namelist);

	return 0;
}
