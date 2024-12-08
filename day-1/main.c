#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main(void) {
    int LINE_LEN = 13;
    int SPACING = 3;
    int NUM_SIZE = 5;

    FILE* file_ptr = fopen("input", "r");

    if (NULL == file_ptr) {
        fprintf(stderr, "file can't be opend\n");
        exit(1);
    }

    int number_rows = 1000;

    int *left_numbers = malloc(sizeof(int) * number_rows);
    int *right_numbers = malloc(sizeof(int) * number_rows);


    char left_num[NUM_SIZE + 1];
    char right_num[NUM_SIZE + 1];
    int current;

    int col_index = 0;
    int row_index = 0;
    while ((current = fgetc(file_ptr)) != EOF) {
        if (current != '\n') {
            if (row_index < NUM_SIZE) {
                left_num[row_index] = (char) current;
            } else if (row_index >= (NUM_SIZE + SPACING) && row_index < LINE_LEN) {
                right_num[row_index - ( NUM_SIZE + SPACING )] = (char) current;
            }
            row_index++;
        } else {
            int number_offset = col_index * sizeof(int);

            left_num[5] = '\0';
            right_num[5] = '\0';

            sscanf(left_num, "%d", &left_numbers[number_offset]);
            sscanf(right_num, "%d", &right_numbers[number_offset]);

            printf("%s -> %d - ", left_num, left_numbers[number_offset]);
            printf("%s -> %d\n", right_num, right_numbers[number_offset]);

            row_index = 0;
            col_index++;
        }
    }

    qsort(left_numbers, number_rows, sizeof(int), compare);
    qsort(right_numbers, number_rows, sizeof(int), compare);

    /*
    for(int i = 0; i < number_rows; i++) {
        printf("%d - %d\n", left_numbers[i * sizeof(int)], right_numbers[i * sizeof(int)]);
    }*/

    //printf("Number of rows is: %d\n", number_rows);

    fclose(file_ptr);
    return 0;
}
