#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

/*
 * Complete the 'gridChallenge' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING_ARRAY grid as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
void merge(char* s,int l,int m,int r){
    int i,j,k;
    int n1=m-l+1;
    int n2=r-m;
    char L[n1],R[n2];
    for(int i=0;i<n1;i++){
        L[i]=s[l+i];
        
    }
    for(int j=0;j<n2;j++){
        R[j]=s[m+j+1];
    }
    
    i=0;j=0;k=l;
    while(i<n1 && j<n2){
        if(L[i]<=R[j]){
            s[k]=L[i];
            i++;
        }
        else{
            s[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        s[k]=L[i];
        k++;
        i++;
    }
    while(j<n2){
        s[k]=R[j];
        j++;
        k++;
    }
}
void sort(char* s,int l,int r){
    if(l<r){
        int m=l+(r-l)/2;
        
        sort(s,l,m);
        sort(s,m+1,r);
        merge(s,l,m,r);
    }
}
char* gridChallenge(int grid_count, char** grid) {
    if(grid_count==1){
        return "YES";
    }
    for(int i=0;i<grid_count;i++){
        sort(grid[i],0,grid_count-1);
    }
    int res=1;
    for(int j=0;j<grid_count;j++){
        int i;
        for(i=0;i<grid_count-1;i++){
            if(grid[i][j]>grid[i+1][j]){
                res=0;
                break;
            }
        }
        if(i!=grid_count-1){
            break;
        }
    }
    if(res==0)return "NO";
    else return "YES";
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char** grid = malloc(n * sizeof(char*));

        for (int i = 0; i < n; i++) {
            char* grid_item = readline();

            *(grid + i) = grid_item;
        }

        char* result = gridChallenge(n, grid);

        fprintf(fptr, "%s\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
