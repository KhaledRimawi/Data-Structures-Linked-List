#include <stdio.h>
#include <stdlib.h>
#include <string.h>//Khaled azmi sameeh abdalraheem //1210618//dr.Saadeddin Hroub//sec.3
#include <ctype.h>

int size =63;
// define doubly node
typedef struct Node *ptr;
struct Node {
    char data[31];
    ptr prev;
    ptr next;
};

// insert At Beginning of list
void insertAtBeginning(ptr head, char * newData) {
    ptr newNode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newNode->data,newData);//<==>  newNode->data = newData;
    newNode->next = head->next;


    if (head->next != NULL) {
        head->next->prev = newNode;
    }

    head->next = newNode;
    newNode->prev = head;
}



int readfile(ptr head)
{

    // Open the file for writing
    FILE *file = fopen("input.txt", "r");

    //Check if the unlock was successful
    if (file == NULL) {
        perror("ERROR");
        return 1; // Indicates an error has occurred
    }

    // Read the content from the file and print it on the screen
    char string[31];
    printf("Reading from file.....\n\n");

    while ((fscanf(file,"%s",string)) != EOF)
    {
        insertLast(string, head);//*****************************************************
    }


    // Close the file after you finish reading
    fclose(file);
    printf("Reading done....\n\n\n");


}


void writefile(ptr head) {
    // Open the file for writing
    FILE *file = fopen("output.txt", "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Failed to open file");
        return; // Return void
    }

    // Write the content to the file
    ptr current = head->next;
    while (current != NULL) {
        fprintf(file, "%s\n", current->data);
        current = current->next;
    }

    // Close the file after finishing writing
    fclose(file);
    printf("Writing done....\n\n\n");
}


ptr  MakeEmpty(ptr head)//Here I made the head, but made it empty
{

    head=(ptr) malloc(sizeof (struct Node));
    if(head==NULL)// It enters it if the memory is full
    {
        printf("Out of memory ! \n");
        return NULL;
    }
    head->next=NULL;
    head->prev=NULL;
    return head;
}

void printres(ptr head) {//Prints list
    ptr p = head->next;
    while (p != NULL) {
        printf("%s ", p->data);
        p = p->next;
    }
    printf("\n");
}

int mapping (char c)//Here we specify the index for each letter and number
{
    if(isdigit(c))
    {
        return c-47;//47=>'0'-x=1
    }
    else if(isupper(c))
    {
        return c-54;//54=>'A'-x=11
    }
    else if(islower(c))
    {
        return c-60;//60=>'a'-x=37
    }
    else if(c == '\0')
    {
        return 0;
    }
}


int getMaxSize(ptr head)//to get Max Size for string
{
    ptr r=head->next;
    int max = strlen(head->next->data);

    while(head != NULL)
    {
        int len = strlen(head->data);
        if(len>max)
        {
            max=len;
        }

        head=head->next;
    }
    return max;

}
void insertLast(char word[], ptr head)//insert at Last
{


    if (head == NULL) {
        fprintf(stderr, "The head is null.\n");
        exit(1);
    }
    ptr newNode = (ptr)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Out of memory!");
        return;
    }

    strcpy(newNode->data, word);
    newNode->next = NULL;

    ptr p = head;
    while (p->next != NULL) {
        p = p->next;
    }

    newNode->prev = p;
    p->next = newNode;
}

void radixSort(ptr head)//radix Sort
{


    ptr arre_oflist[size];
    for(int i=0;i<size;i++)
    {
        arre_oflist[i] = MakeEmpty( NULL);

    }

    for(int i=(getMaxSize( head)-1);i>=0   ;i--)
    {
        ptr r =head->next;
        while(r != NULL)
        {
            insertLast(r->data, arre_oflist[ mapping (r->data[i])]);
            r =r->next;

        }
        head->next=NULL;
        for(int j=0;j<size;j++)
        {
            ptr p=arre_oflist[j]->next;
            while(p!=NULL)
            {
                insertLast(p->data,head);
                p=p->next;
            }


        }
        for(int g=0;g<size;g++)
        {
            arre_oflist[g]->next=NULL;
        }


    }
}

//Delete >>>>>>
void Delete (char * d,ptr head)
{
    ptr temp=head->next;
    while (temp!=NULL && strcmp(temp->data, d) != 0)
    {
        temp=temp->next;
    }
    if(temp !=NULL)
    {


        if(temp->prev !=NULL)
        {
            temp->prev->next=temp->next;
        }
        if(temp->next !=NULL)
        {
            temp->next->prev=temp->prev;
        }
        free(temp);
    }

}

void ToDelete(ptr head)//world to deleted
{
    char deleted[31] ;
    printf("Enter the world to deleted:-\n");
    scanf("%s",deleted);
    Delete ( deleted, head);

    printres(head);
}


int main() {
    printf("****Hello****\n");

    ptr list = NULL;
    list=MakeEmpty( list);

    ptr listAfterSort=NULL;
    listAfterSort=MakeEmpty( listAfterSort);



    int x;
    char s[31] ;
    FILE *file = fopen("input.txt", "r");
    int choice;


    do {
        printf("\nMenu:\n");
        printf("1. Load the strings\n");
        printf("2. Print the strings before sorting\n");
        printf("3. Sort the strings\n");//??
        printf("4. Print the sorted	strings\n");//??
        printf("5. Add a new word to the list of sorted	strings	(and sort it)\n");
        printf("6. Delete a word from the sorted strings\n");
        printf("7. Save to output file\n");
        printf("8. Exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list=MakeEmpty( list);
                listAfterSort=MakeEmpty( listAfterSort);

                readfile( list);// Load the strings from the input file
                readfile( listAfterSort);
                break;
            case 2:
                printres(listAfterSort);// Print the strings before sorting

                break;
            case 3:
                radixSort( list);// Sort the strings using Radix Sort


                break;
            case 4:
                printres(list);



                break;
            case 5:

                printf("Enter the word you want to add:-\n");
                scanf("%s",s);

                insertLast(s, list);
                radixSort( list);


                break;
            case 6:
                ToDelete(list);

                break;
            case 7:
                writefile(list);

                break;
            case 8:// Exit the program

                printf("good bye....");

                break;

            default://if the entered choice is not from this list.
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);



    return 0;
}




























