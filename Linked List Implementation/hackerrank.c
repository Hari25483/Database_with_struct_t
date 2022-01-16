//Importing required libraries
#include <stdlib.h>
#include <stdio.h>

//Defining a struct type with next pointer so that we can create linked lists
typedef struct _ {
    int batch;
    int regNo;
    char firstName[20];
    char lastName[20];
    float cGPA;
    struct _* next;
}student_t;

//Head for the linked list so that it can be used to initialize linked list
student_t * head=NULL;

//Function prototypes
void reversePrint();
void printAllRecords();
void Find_Info(int);
student_t * enterData(); //This function returns a head node of a linked list
void deleteRecords(int,int);


int main() {
    int choice;
    student_t * HEAD=NULL;
    printf("--------------------------------------------\n");
    printf("A VOLATILE STUDENT RECORD MAINTENANCE SYSTEM\n");
    printf("--------------------------------------------\n");
    printf("0. Quit\n");
    printf("1. Insert a Student Record\n");
    printf("2. Print a Student Record\n");
    printf("3. Print all Student Records\n");
    printf("4. Delete a Student Record\n");
    while(1){
        printf("------------------\n");
        printf("ENTER OPTION [0-4]\n");
        printf("------------------\n");
        scanf("%d",&choice);
        if (choice==0){
            break;
        }
        else if(choice==4){
            Find_Info(4);
            printf("\n");
        }        
        else if(choice==2){
            Find_Info(choice);
            printf("\n");
        }
        else if(choice==1){
            HEAD=enterData();
            printf("\n");
        }
        else if(choice==3){
            printAllRecords();
            printf("\n");
        }
    }
    return 0;
}

//Function to enter student data
student_t * enterData(){
    student_t * temporary_node=NULL;
    student_t * p=NULL;
    temporary_node=(student_t*)(malloc(sizeof(student_t)));
    printf("Enter the batch (14/15/16/17): ");
    scanf("%d",&(temporary_node->batch));
    printf("Enter the registration number: ");
    scanf("%d",&(temporary_node->regNo));
    printf("Enter the first name         : ");
    scanf("%s",temporary_node->firstName);
    printf("Enter the last name          : ");
    scanf("%s",temporary_node->lastName);
    printf("Enter the cumulative GPA     : ");
    scanf("%f",&temporary_node->cGPA);
    temporary_node->next=NULL;
    
    if (head==NULL){
        head=temporary_node;
    }
    else{
        p=head;
        while (p->next!=NULL){
            p=p->next;
        }
        p->next=temporary_node;
    }
    return head;
}


void Find_Info(int choice){
    char IndexNumber[4],enumber[9],batch[3]={0};
    int position;
    printf("Enter the Registration Number: ");
    scanf("%s",enumber);
    //To get batch, and E-number from the input string.
    int i=0,j=0;
    for (int i =2;i<4;i++)
    {
        batch[i-2]= enumber[i];
    }
    for (int i=5,j=0;i<9,j<4;i++,j++)
    {
        IndexNumber[j] = enumber[i];
    }

//Convert the input string to integer so that we can search it in our database
    int int1 = 0,int2=0,eNumber,batchNumber,result;    
    for (int i = 0; IndexNumber[i] != '\0'; ++i){
         int1=int1*10 + IndexNumber[i]-'0';
    }
    eNumber= int1;  
    
    for (int i = 0; batch[i] != '\0'; ++i)
        int2=int2*10+batch[i]-'0';
        
    batchNumber=int2;
    
    if (choice==4){
        //This for loop checks whether the queryimg id is in our database.
        student_t * temporary_node=head;
        while(temporary_node!=NULL){
            if((temporary_node->regNo==eNumber)&&(temporary_node->batch==batchNumber)){
                    result=1;
                    break;
                }
            else{
                result=0;
            }
            temporary_node = temporary_node->next;
        }
        if(result==1){
            deleteRecords(eNumber,batchNumber);
            printf("Delete Successful!\n"); //If deleting is complete, display this message.
        }
        else{
            printf("No student with the given Registration Number!\n"); //Print an error message if the requested information is not found.
        }
    }
    else if (choice==2){
        //This for loop checks whether the queryimg id is in our database
        student_t * temporary_node=head;
        while(temporary_node!=NULL){
            if((temporary_node->regNo==eNumber)&&(temporary_node->batch==batchNumber)){
                    result=1;
                    break;
                }
            else{
                result=0;
            }
            temporary_node = temporary_node->next;
        }
      
        if(result==1){//Find the corresponding information of given E number and printing it.
            printf("The student %s %s (E/%d/%d) has a cumulative GPA of %.2f\n",temporary_node->firstName,temporary_node->lastName,temporary_node->batch,temporary_node->regNo,temporary_node->cGPA);
        }
        else{
            printf("No student with the given Registration Number!\n"); //Displaying error message if the information is not found
        }
    }
}

//Function to delete the required information
void deleteRecords(int regno,int batch){
    student_t *temporary1=head;
    student_t *temporary2=head;
    while(temporary1!=NULL){
        //Traverse the linked list, and check whether our required data is in the linked list, and deletes the particular node if it is found.
        if ((temporary1->regNo==regno)&&(temporary1->batch==batch)){
            //Free the required node, and link the previous node, and the next node
            if (temporary1==temporary2){
                head=head->next;
                free(temporary1);
            }
            else{
                temporary2->next=temporary1->next;
                free(temporary1);
            }
            return;
        }
        //Connect the previous node, and the next node of the deleted node
        temporary2=temporary1;
        temporary1=temporary1->next;
    }
}


//Function to print all  records
void printAllRecords(){
    student_t * p=head;
    while (p!=NULL){
        printf("The student %s %s (E/%d/%d) has a cumulative GPA of %.2f\n",p->firstName,p->lastName,p->batch,p->regNo,p->cGPA);
        p=p->next;
    }
}



/*
    DISCUSSION
    
1. int data takes 4 bytes of memory, char data type takes 1 byte of memory, and float data type occupies 4 bytes of memory. Since int types batch, and regNo takes 8 bytes, the size occupied by them in the memory is 8 bytes. Same type of calculation goes for firstName[20], and lastName[20]. Both of  them occupy a total of  40 bytes. Since float cGPA takes 4 bytes as mentioned above, It can be confirmed that the total memory allocated for the linked list is 52 bytes.

2.  Memory allocation happens dynamically by using the malloc function. When a new student entry is created, the data of that student is saved in a node. When the data is entered continuously, new nodes will be created, and connections between those nodes will be kept, and the data will be stored in each node. Since this is a volatile program, memory is freed when the program is terminated.

3. Deleting of nodes happens when a required data that needs to be deleted is found in the linked list. When the registration number of the student whose details are to be deleted is given, that will be matched with the required node if  the data is in the node, and the memory of that node is freed, and the link between the previous node of the node to be deleted, and the next node of the node to be deleted will be created so that there will be continuity in the linked list after freeing a particular node. .  

4. Since this program is using a linked list for storing data, unlimited  data can be stored. 

5. Pros over arrays
 Dynamic memory allocation,
 Can add unlimited amount of data
 Easy to insert and delete off nodes than arrays 

 cons over arrays 
 We cannot do binary search with linked lists efficiently like arrays. 
 We can’t access data in the middle or any other places directly like we do in arrays. We have to start from the head node, and traverse one by one.
 Extra memory space is needed as a pointer is required with each element of the list 

6. Since we know the exact amount of data that needs to be added, and there is no insertion or deletion, it’s better to implement the system by using arrays. We can randomly access elements in an array, and we won’t be wasting extra memory for keeping the next pointers like we do in the linked list method. 

*/