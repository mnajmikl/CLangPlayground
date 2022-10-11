#include <stdio.h>
#include <string.h>

struct element
{
    int elementnumber;
    char elementsymbol[4];
    char elementname[16];
};

int getelementcount()
{
    int count_lines = 0;
    FILE *fp;
    fp = fopen("elements.csv","r");
    char chr = getc(fp);
    while (chr != EOF)
    {
        if (chr == '\n')
        {
            count_lines = count_lines + 1;
        }
        chr = getc(fp);
    }
    fclose(fp);
    return count_lines;
}

void displaynumberofelements()
{
    printf("\nThere are currently %d elements in the latest Element Periodic Table\n", getelementcount());
}
void displayelements()
{
    FILE *fp;
    fp = fopen("elements.csv","r");
    struct element displayelement;
    while (!feof(fp))
    {
        fscanf(fp, "%d,%[^,\n],%[^,\n]\n",
               &displayelement.elementnumber, displayelement.elementsymbol, displayelement.elementname);
        printf("Element number: %3d\tElement Symbol: %3s\tElement Name: %s\n",
               displayelement.elementnumber, displayelement.elementsymbol, displayelement.elementname);
    }
    fclose(fp);
}

void searchelementsbynumber()
{
    FILE *fp;
    int element_number = 0, found = 0;
    struct element searchelement;
    printf("Enter Element Number to search: ");
    scanf("%d", &element_number);
    fflush(stdin);
    fp = fopen("elements.csv","r");
    while (!feof(fp))
    {
        fscanf(fp, "%d,%[^,\n],%[^,\n]\n", &searchelement.elementnumber,
               searchelement.elementsymbol, searchelement.elementname);
        if (searchelement.elementnumber == element_number)
        {
            printf("\nElement Number %d has been found\n", searchelement.elementnumber);
            printf("Element number: %3d\tElement Symbol: %3s\tElement Name: %s\n",
                   searchelement.elementnumber, searchelement.elementsymbol,
                   searchelement.elementname);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nElement Number %d Is Not Found\n", element_number);
    }
    fclose(fp);
}

void searchelementsbysymbol()
{
    FILE *fp;
    char element_symbol[4];
    int found = 0;
    struct element searchelement;
    printf("Enter Element Symbol to search: ");
    scanf("%3s", element_symbol);
    fflush(stdin);
    fp = fopen("elements.csv","r");
    while (!feof(fp))
    {
        fscanf(fp, "%d,%[^,\n],%[^,\n]\n", &searchelement.elementnumber,
               searchelement.elementsymbol, searchelement.elementname);
        if (strcmp(element_symbol, searchelement.elementsymbol) == 0)
        {
            printf("\nElement Symbol %s has been found\n", element_symbol);
            printf("Element number: %3d\tElement Symbol: %3s\tElement Name: %s\n",
                   searchelement.elementnumber, searchelement.elementsymbol, searchelement.elementname);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nElement Symbol %3s Is Not Found\n", element_symbol);
    }
    fclose(fp);
}

void menu()
{
    char choice = '1';
    while (choice != '5')
    {
        printf("\n ____________________________________________________");
        printf("\n|                                                    |");
        printf("\n|               Periodic Element Table               |");
        printf("\n|____________________________________________________|");
        printf("\n\ntSelect One Of The Choices\n");
        printf("\n\t(1) Display All Element");
        printf("\n\t(2) Display Current Total Number of Elements");
        printf("\n\t(3) Search An Element By Number");
        printf("\n\t(4) Search An Element By Symbol (Case Sensitive)");
        printf("\n\t(5) Exit");
        printf("\n\nEnter Your choice here : ");
        scanf(" %c", &choice);
        fflush(stdin);
        switch (choice)
        {
        case '1':
            displayelements();
            break;
        case '2':
            displaynumberofelements();
            break;
        case '3':
            searchelementsbynumber();
            break;
        case '4':
            searchelementsbysymbol();
            break;
        case '5':
            break;
        default:
            printf("Invalid Choice. Please Try Again\n");
            break;
        }
    }
}

int main()
{
    menu();
    return 0;
}