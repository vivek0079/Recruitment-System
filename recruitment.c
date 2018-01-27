#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>//directory to printthe number of applicants used in the viewapplicants()
#include<unistd.h>//directory to access getpass()

struct candidate//structure declaration
{
    char name[20],dob[10],address[50],b10[10],b12[10],about[100],email_id[20],pass[20];
    int age,mrk10,mrk12;
    long int phone_num;
}*app[50];//array of structure pointer variable

struct vacancy//structure for vacancy
{
    char vacname[20],lstdate[10],addon[30];
    int num;
}vac;//normal structure variable

//user defined fn. declaration
void welcome();
void login();
void createvacancy();
void viewvacancy();
void apply();
void viewapplicant();
int exist(char name[20]);
void hr();
void hr_inner();
void applicant();
void totalappli();
void applist();

//main function
int main()
{
    welcome();
    login();
    return 0;
}
void welcome()//Welcome function(template)
{
    printf("************************************************************\n");
    printf("**************WELCOME TO THE RECRUITMENT SYSTEM*************\n");
    printf("************************************************************\n");
    printf("*********************************************Done by VIVEK S\n");
}
void login()//login function
{
    int ch;
    system("clear");
    welcome();
    printf("\nLOGIN AS:\n1.HR MANAGER\n2.APPLICANT\n3.EXIT\n");
    scanf("%d",&ch);
    //ch=getch();
    switch(ch)
    {
        case 1:
            hr();
            break;
        case 2:
            applicant();
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Error!!!");
    }
}
void hr()//function definition of the HR
{

    char usrname[20];
    system("clear");
    welcome();
    START:
        printf("Enter the login details:\nUSER NAME:\n");
        scanf("%s",usrname);
        char *password = getpass("PASSWORD:\n");//password mask using getpass()
        if ((strcmp(usrname,"admin")==0)&&(strcmp(password,"admin")==0))
        {
            hr_inner();
        }
        else
        {
                printf("Incorrect Password\n");
                goto START;
        }
}

void hr_inner()//inner functionalities of HR function
{
    int c;
    system("clear");
    welcome();
    printf("Enter your choice\n1.Create Vacancy\n2.View Applicant details\n3.View Applicants list\n4.GOTO HOME\n");
    scanf("%d",&c);
    switch(c)
    {
        case 1:
            createvacancy();
            break;
        case 2:
            viewapplicant();
            break;
        case 3:
            applist();
            break;
        case 4:
            login();;
            break;
        default:
            printf("Error!!!");
    }
}
void applicant()//function of the applicant
{
    int cc;
    system("clear");
    welcome();
    printf("\n1.VIEW VACANCY\n2.APPLY FOR VACANCY\n3.GOTO HOME\n");
    scanf("%d",&cc);
    switch (cc)
    {
        case 1:
            viewvacancy();
            break;
        case 2:
            apply();
            break;
        case 3:
            login();
            break;
        default:
            printf("Error!!!\n");
    }
}
void createvacancy()//functionn to create a vancancy
{
    char ha,ab;
    system("clear");
    welcome();
    FILE *vacfile;
    vacfile=fopen("Vacancy list.txt","w");
    printf("Enter the following details\n");
    printf("VACANCY NAME:\n");
    scanf("%s",vac.vacname);
    printf("LAST DATE TO APPLY:\n");
    scanf("%s",vac.lstdate);
    printf("NO. OF VACANCIES AVAILABLE:\n");
    scanf("%d",&vac.num);
    printf("ADDITIONAL INFORMATION:\n");
    scanf("%s",vac.addon);
    //fgets(vac.addon,20,stdin);
    fprintf(vacfile,"\t\t\tVACANCY LIST FOR THE CANDIDATES\n\n\nVACANCY NAME:%s\n\n\nLAST DATE TO APPLY:%s\n\n\nNO.OF VACANCIES AVAILABLE:%d\n\n\nADDITIONAL INFORMATION:%s\n\n\n",vac.vacname,vac.lstdate,vac.num,vac.addon);
    fclose(vacfile);
    scanf("%c",&ab);
    printf("Press ENTER to continue");
    ha=getchar();
    if(ha=='\n')
    {
    system("clear");
    welcome();
    hr_inner();
    }

}

void viewapplicant()//function to view the applicant details
{
    FILE *appli;
    char name[20],ch,ha,ab;
    int file_count = 0;
    DIR * dirp;
    struct dirent * entry;

    dirp = opendir("."); //. denotes the current directory
    while ((entry = readdir(dirp)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
             file_count++;//to print the total number of applicants registered
        }
    }
    printf("TOTAL NUMBER OF APPLICANTS:\n%d\n",file_count-4);
    closedir(dirp);
    TOP:
    printf("Enter the applicant you wish to view:\n");
    scanf("%s",name);
    strcat(name,".txt");
    if (exist(name)==1)
    {
        goto TOP;
        printf("Invalid Applicant name\nTry Again\n");
    }
    appli=fopen(name,"r");
    while (fscanf(appli,"%c",&ch) != EOF)
        {
            printf("%c",ch);
        }
    scanf("%c",&ab);
    printf("Do you wish to reject [Y or N]\n");//to reject and to delete the applicant from the list
    char c=getchar();//this line not working
    if (c=='y')
    {
        remove(name);
        printf("Successfully rejected\n");
    }
    fclose(appli);
    scanf("%c",&ab);
    printf("Press ENTER to continue");
    ha=getchar();
    if(ha=='\n')
    {
    system("clear");
    welcome();
    hr_inner();
    }

}

int exist(char name[20])//function to find whether the applicant has already registered
{
    FILE *fexist;
    char temp_name[20],ab;
    strcpy(temp_name,name);
    strcat(temp_name,".txt");
    fexist=fopen(temp_name,"r");
    if (fexist==NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void applist()//function to print the names of the applicants
{
    FILE *list;
    char c,ab;
    list=fopen("Applicant List.txt","r");
    while(fscanf(list,"%c",&c)!=EOF)
    {
        printf("%c",c);
    }
    fclose(list);
    scanf("%c",&ab);
    printf("\nPress ENTER to continue\n");//This part is directly executed
    char haha=getchar();
    if(haha=='\n')
    {
    system("clear");
    welcome();
    hr_inner();
    }
}

void apply()
{
    FILE *appli,*applist;
    char app_name[20],name[20];
    int n=1,i;
    for (i=1;i<=n;i++)
    {
        ABOVE:
        system("clear");
        welcome();
        app[i]=(struct candidate*)malloc(n*sizeof(struct candidate));
        printf("Enter the following details:\n");
        printf("NAME:\n");
        scanf("%s",app[i]->name);
        strcpy(app_name,app[i]->name);
        strcpy(name,app[i]->name);
        if(exist(app_name)==1)
        {
            goto ABOVE;
            printf("ERROR!!!\nAlready registered\n");
        }
        printf("DOB[ddmmyy]:\n");
        scanf("%s",app[i]->dob);
        printf("AGE:\n");
        scanf("%d",&app[i]->age);
        printf("ADDRESS:\n");
        scanf("%s",app[i]->address);
        printf("E-MAIL:\n");
        scanf("%s",app[i]->email_id);
        printf("BOARD OF EDUCATION IN 10TH STANDARD\n");
        scanf("%s",app[i]->b10);
        printf("10th MARK:\n");
        scanf("%d",&app[i]->mrk10);
        printf("BOARD OF EDUCATION OF 12TH STANDARD\n");
        scanf("%s",app[i]->b12);
        printf("12th MARK:\n");
        scanf("%d",&app[i]->mrk12);
        printf("PHONE NUMBER:\n");
        scanf("%ld",&app[i]->phone_num);
        printf("ABOUT:\n");
        scanf("%s",app[i]->about);
        //strcpy(app_name,app[i]->name);
        strcat(app_name,".txt");
        appli=fopen(app_name,"w");
        applist=fopen("Applicant List.txt","w");
        fprintf(applist,"\t\t\tAPPLICANTS LIST\n%s\n",name);
        fprintf(appli,"1.NAME:\n%s\n\n2.DOB:\n%s\n\n3.AGE:\n%d\n\n4.ADDRESS:\n%s\n\n5.E-MAIL:\n%s\n\n6.BOARD OF EDUCATION IN 10TH STANDARD:\n%s\n\n7.10th MARK:\n%d\n\n8.BOARD OF EDUCATION IN 12TH STANDARD:\n%s\n\n9.12th MARK:\n%d\n\n10.PHONE NUMBER:\n%ld\n\n11.ABOUT:\n%s\n\n",app[i]->name,app[i]->dob,app[i]->age,app[i]->address,app[i]->email_id,app[i]->b10,app[i]->mrk10,app[i]->b12,app[i]->mrk12,app[i]->phone_num,app[i]->about);

    }
    fclose(applist);
    fclose(appli);
    system("clear");
    welcome();
    login();
}

void viewvacancy()//module to view the vacancy available in the applicant()
{
    char ab;
    printf("\t\t\tVACANCY LIST\n1.VACANCY NAME:%s\n2.LAST DATE TO APPLY:%s\n3.NO. OF POST AVAILABLE:%d\n4.ADDITIONAL INFO:%s\n",vac.vacname,vac.lstdate,vac.num,vac.addon);
    scanf("%c",&ab);
    printf("\nPress ENTER to continue\n");
    char haha=getchar();
    if(haha=='\n')
    {
    system("clear");
    welcome();
    applicant();
    }
}
