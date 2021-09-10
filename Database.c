#include <stdio.h>

typedef struct _ {
    int batch;
    int regNo;
    char firstName[20];
    char lastName[20];
    float cGPA;
}student_t;
student_t id_to_be_queried; //This is used to query the databse and match to print or delete records.
int student_No=0;
void printAllRecords(student_t students[100]);
void Find_Info(student_t students[100],int);
void enterData(student_t students[100]);
void deleteRecords(int ,student_t students[100]);

int main() {
    int choice;
    student_t students1[100];
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
        else if(choice==1){
            enterData(students1);
            printf("\n");

        }
        else if(choice==2){
            Find_Info(students1,choice);
            printf("\n");

         }
        else if(choice==3){
            printAllRecords(students1);
            printf("\n");
        }
        else if(choice==4){
            Find_Info(students1,4);
            printf("\n");
        }
    }
    return 0;
}

void enterData(student_t students[100]){
    printf("Enter the batch (14/15/16/17): ");
    scanf("%d", &students[student_No].batch);
    printf("Enter the registration number: ");
    scanf("%d",&students[student_No].regNo);
    printf("Enter the first name         : ");
    scanf("%s",students[student_No].firstName);
    printf("Enter the last name          : ");
    scanf("%s",students[student_No].lastName);
    printf("Enter the cumulative GPA     : ");
    scanf("%f",&students[student_No].cGPA);
    student_No=student_No+1;
}



void Find_Info(student_t students[100], int choice){
    char IndexNumber[4],enumber[9],batch[3];;
    int position;
    printf("Enter the Registration Number: ");
    scanf("%s",enumber);
    for (int i =2,j=0;i<4,j<3;i++,j++)
    {
        batch[j] = enumber[i];
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
        for(int position=0;position<student_No;position++){
            if (id_to_be_queried.regNo == students[position].regNo&&id_to_be_queried.batch == students[position].batch){
                break;
            }
        }
        for (int i=0;i<student_No;i++){
            if(eNumber==students[i].regNo){
                if (batchNumber==students[i].batch){
                id_to_be_queried=students[i];
                result=1;//If it is in the database, return 1.
                   }
        }
        else {
            result=0;
            }
        }
        if(result==1){
            deleteRecords(position,students);
            printf("Delete Successful!\n"); //If deleting is complete, display this message.
        }
        else{
            printf("No student with the given Registration Number!\n"); //Print an error message if the requested information is not found.
        }
    }
    else if (choice==2){
        //This for loop checks whether the queryimg id is in our database
         for (int i=0;i<student_No;i++){
            if(eNumber==students[i].regNo){
                if (batchNumber==students[i].batch){
                id_to_be_queried=students[i];
                result=1;//If it is in the database, return 1.
                   }
        }
        else {
            result=0;
            }
        }
        if(result==1){//Find the corresponding information of given E number and printing it.
            printf("The student %s %s (E/%d/%d) has a cumulative GPA of %.2f\n",id_to_be_queried.firstName,id_to_be_queried.lastName,id_to_be_queried.batch,id_to_be_queried.regNo,id_to_be_queried.cGPA);
        }
        else{
            printf("No student with the given Registration Number!\n"); //Displaying error message if the information is not found
        }
    }
}

//Function to delete the required information
void deleteRecords(int position,student_t students[100]){
    for(int i=position;i<student_No;i++){
        students[i]=students[i+1];
    }
    student_No=student_No-1;
}


//Function to print all  records
void printAllRecords(student_t students[100]){
    for (int i=0;i<student_No;i++){
        printf("The student %s %s (E/%d/%d) has a cumulative GPA of %.2f\n",students[i].firstName,students[i].lastName,students[i].batch,students[i].regNo,students[i].cGPA);
    }
}