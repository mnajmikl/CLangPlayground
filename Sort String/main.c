#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LIMIT 20

int main()
{
    int n,i,j;
    printf("Enter number of strings: \n");
    scanf("%d",&n);
    fflush(stdin);
    char str_arr[n][MAX_LIMIT];
    char arr_i[MAX_LIMIT];
    char s[MAX_LIMIT];

    printf("Enter strings:\n");

    for(i=0; i<n; i++)
    {
        fgets(arr_i, MAX_LIMIT, stdin);
        strcpy(str_arr[i], arr_i);
        fflush(stdin);
    }

    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(strcmp(str_arr[i], str_arr[j])>0)
            {
                strcpy(s, str_arr[i]);
                strcpy(str_arr[i], str_arr[j]);
                strcpy(str_arr[j], s);
            }
        }
    }

    printf("Your strings:  \n");
    for(i=0; i<n; i++)
    {
        printf("%s\n", str_arr[i]);
    }

    return 0;
}
