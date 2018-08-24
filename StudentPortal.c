#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
//----------------------------------------

#define MAX_STR_LENGTH 30

//----------------------------------------

void menu();
void std();
void dlt(char *ID);
void add(int n);
void edit(char *n);
void view(char *n);
void adm();
void ag();
void veiwl();
void prof();
void addSlist(char *t,char *s);
float castnumber(char *x);
void calc(char *y);

//----------------------------------------

typedef struct prof{
	char name[MAX_STR_LENGTH];//first and last name
	char email[MAX_STR_LENGTH];
	char NID[10];
}Prof;

//----------------------------------------

typedef struct course{
	char cname[MAX_STR_LENGTH];//course name
	char credit[2];//vahed
	char porf[MAX_STR_LENGTH];
	char score[2];//nomre
	char day[1];
	char time[5];
	//struct course *next;
}Course;

//----------------------------------------

typedef struct term{
	char num;//terme chand?!
	char ave[6];//average
	//Course *head;
	//struct term *next;
}Term;

//----------------------------------------

Term *head=NULL;

//----------------------------------------
typedef struct student{
	char fname[MAX_STR_LENGTH];//first name
	char lname[MAX_STR_LENGTH];//last name
	char NID[10];//national ID
	char SID[7];//student ID
	char email[MAX_STR_LENGTH];
	char pass[10];//10=max strlen(password)
	//Term *head;
}Student;

//----------------------------------------

void std()
{
    int cmd;//command
    char password[10];
    FILE *fp;
    int i=0,j=0;
    char c;
    char ID[MAX_STR_LENGTH];
    char temp[6][MAX_STR_LENGTH];
    printf("enter student ID:\n");
    scanf("%s",ID);
    printf("enter password:\n");
    scanf("%s",password);
    strcat(ID,".txt");
    fp=fopen(ID,"r+");
    fseek(fp,0,SEEK_SET);
    while(i<5)
    {
        fscanf(fp,"%c",&c);
        if(c!='*')
        {
            temp[i][j]=c;
            j++;
        }
        else
        if(c=='*')
        {
            temp[i][j]=c;///
            temp[i][j+1]='\0';
            i++;
            j=0;
        }
    }
    fclose(fp);
    ID[7]='\0';
    strcat(password,"*");
    if(strcmp(temp[3],password)==1)
    {
        printf("wrong password! :|\n");
        exit(1);
    }
    else
    if(strcmp(temp[3],password)==0)
    {
        printf("welcome! :)");
        printf("\nenter command:\n");
        printf("edit info-->1\n");///
        //printf("take courses-->2\n");
        //printf("delete course-->3\n");
        printf("change password-->4\n");///
        printf("view info-->5\n");///
        printf("calculate average-->6\n");
        scanf("%d",&cmd);
        switch(cmd)
        {
        case 1:
            edit(ID);
            break;
        //case 2:
            //tc();
            //break;
        //case 3:
            //dltc();//delete course
            //break;
        case 4:
            edit(ID);
            break;
        case 5:
            view(ID);
            break;
        case 6:
            calc(ID);
            break;
        }
    }
}

//----------------------------------------

void calc(char *ID)
{
    FILE *fp;
    char temp[1000];
    char num[2];
    char termnumber[MAX_STR_LENGTH];
    char *termptr;//term pointer
    char *courseptr1;
    char *courseptr2;
    char *courseptr3;//course pointer
    char point1[6];
    char point2[6];
    char point3[6];
    char c;
    int i=0,j;
    float ave=0;
    strcat(ID,".txt");
    fp=fopen(ID,"r");
    printf("\nenter term number:");
    scanf("%s",&num);
    while(!feof(fp))
    {
        fscanf(fp,"%c",&c);
        temp[i]=c;
        i++;
    }
    temp[i]=NULL;
    fclose(fp);
    strcpy(termnumber,"+term number=");
    strcat(termnumber,num);
    termptr=strstr(temp,termnumber);
    ///termptr=null?!
    courseptr1=strstr(termptr,"point:");
    courseptr1=courseptr1+6;
    /*for(j=0;j<5;j++)
    {
        point1[j]=*(courseptr1+j);
    }
    point1[5]=NULL;*/
    strncpy(point1,courseptr1,5);
    courseptr2=strstr(courseptr1,"point:");
    courseptr2=courseptr2+6;
    /*for(j=0;j<5;j++)
    {
        point2[j]=*(courseptr2+j);
    }
    point2[5]=NULL;*/
    strncpy(point2,courseptr2,5);
    courseptr3=strstr(courseptr2,"point:");
    courseptr3=courseptr3+6;
    /*for(j=0;j<5;j++)
    {
        point3[j]=*(courseptr3+j);
    }
    point3[5]=NULL;*/
    strncpy(point3,courseptr3,5);
    //printf("\n%s\n%s\n%s",point1,point2,point3);
    ///find grades=check! :)
    ave=(castnumber(point1)+castnumber(point2)+castnumber(point3))/3;
    printf("\n%f",ave);
}

//----------------------------------------

float castnumber(char *x)
{
    float cast=0;
    int i;
    int dot=strlen(x);
    for(i=0;i<strlen(x);i++)
    {
        if(x[i]=='.')
        {
            dot=i;
            break;
        }
    }
    for(i=0;i<dot;i++)
    {
        cast=cast*10+(int)x[i]-'0';
    }
    for(i=strlen(x);i>dot;i--)
    {
        cast=cast+((int)x[i]-'0')*pow(10,-1*i+dot);
    }
    return cast;
}

//----------------------------------------

void dlt(char *ID)
{
    int ret;
    strcat(ID,".txt");
    ret=remove(ID);
    if(ret==0)
    {
        printf("\nstudent deleted! :)");
    }
    else
        printf("\nError: unable to delete student!");
}

//----------------------------------------

void add(int n)//n=0 for student and n=1 for professor
{
    FILE *fp;
    FILE *fp1;
    Student m;
    Prof p;
    int i;
    if(n==0)
    {
        //fp=fopen("stdlist.txt","a+");
        printf("\nenter student ID:\n");
        scanf("%s",m.SID);
        //fprintf(fp,"\n*");
        //fprintf(fp,"\n%s",m.SID);
        strcat(m.SID,".txt");
        fp1=fopen(m.SID,"w+");
        for(i=0;i<MAX_STR_LENGTH;i++)
        {
            if(m.SID[i]=='.')
            {
                m.SID[i]='\0';
                break;
            }
        }
        fprintf(fp1,"%s",m.SID);
        fprintf(fp1,"*");
        printf("enter first name:\n");
        scanf("%s",m.fname);
        //fprintf(fp,"\n%s",m.fname);
        fprintf(fp1,"%s",m.fname);
        fprintf(fp1,"*");
        printf("enter last name:\n");
        scanf("%s",m.lname);
        //fprintf(fp,"\n%s",m.lname);
        fprintf(fp1,"%s",m.lname);
        fprintf(fp1,"*");
        printf("enter national ID:\n");
        scanf("%s",m.NID);
        //fprintf(fp,"\n%s",m.NID);
        fprintf(fp1,"%s",m.NID);
        fprintf(fp1,"*");
        printf("enter email address:\n");
        scanf("%s",m.email);
        if(strstr(m.email,"@aut.ac.ir")!=NULL)
        {
            //fprintf(fp,"\n%s",m.email);
            fprintf(fp1,"%s",m.email);
            fprintf(fp1,"*");
        }
        else
        {
            printf("\nwrong email format! :|");
            exit(1);
        }
    }
    else
    if(n==1)
    {
       fp=fopen("proflist.txt","a+");
       printf("\nenter name:\n");
       scanf("%s",p.name);
       fprintf(fp,"%s",p.name);
       printf("enter email address:\n");
       scanf("%s",p.email);
       fprintf(fp,"\t%s",p.email);
       printf("enter national ID:\n");
       scanf("%s",p.NID);
       fprintf(fp,"\t%s",p.NID);
       fprintf(fp,"*\n");
    }

}

//----------------------------------------

void edit(char *ID)//to change info and password
{
    FILE *fp;
    int i=0,j=0;
    char c;
    int cmd;
    char temp[5][MAX_STR_LENGTH];
    char edt[MAX_STR_LENGTH];//edit
    strcat(ID,".txt");
    fp=fopen(ID,"r+");
    //fseek(fp,0,SEEK_SET);
    while(i<5)
    {
        fscanf(fp,"%c",&c);
        if(c!='*')
        {
            temp[i][j]=c;
            j++;
        }
        else
        if(c=='*')
        {
            temp[i][j]=c;
            temp[i][j+1]='\0';
            i++;
            j=0;

        }
    }
    printf("\nenter command:\n");
    printf("edit first name-->1\n");
    printf("edit last name-->2\n");
    printf("edit national ID//password-->3\n");
    printf("edit email-->4\n");
    scanf("%d",&cmd);
    printf("\nenter edited info:\n");
    scanf("%s",edt);
    strcpy(temp[cmd],edt);
    strcat(temp[cmd],"*");
    fseek(fp,0,SEEK_SET);
    for(i=0;i<6;i++)
    {
        fprintf(fp,"%s",temp[i]);
    }
    fclose(fp);
}

//----------------------------------------

void view(char *ID)
{
    FILE *fp;
    char c;
    strcat(ID,".txt");
    fp=fopen(ID,"r+");
    while(!feof(fp))
    {
        fscanf(fp,"%c",&c);
        printf("%c",c);
    }
    fclose(fp);
}

//----------------------------------------

void append(char *ID)
{
    FILE *fp;
    //Term n;//new term
    char n;
    char teacher[MAX_STR_LENGTH];
    strcat(ID,".txt");
    fp=fopen(ID,"a");
    printf("\nenter term number:\n");
    scanf("\n%c",&n);
    fprintf(fp,"\n+term number=%c",n);///+
    switch(n)
    {
    case '1':
        fprintf(fp,"\n$teacher:shiri");
        fprintf(fp,"$time=01:00");
        fprintf(fp,"$credit:3$");
        fprintf(fp,"point:00.00$");//five spaces
        fprintf(fp,"principles of programming$");
        //fprintf(fp,"\n");
        strcpy(teacher,"shiri");
        addSlist(teacher,ID);
        fprintf(fp,"\n$teacher:salimi");
        fprintf(fp,"$time=10:00");
        fprintf(fp,"$credit:3$");
        fprintf(fp,"point:00.00$");//five spaces
        fprintf(fp,"math$");
        //fprintf(fp,"\n");
        strcpy(teacher,"salimi");
        addSlist(teacher,ID);
        fprintf(fp,"\n$teacher:saba");
        fprintf(fp,"$time=15:00");
        fprintf(fp,"$credit:3$");
        fprintf(fp,"point:00.00$");//five spaces
        fprintf(fp,"physics$");
        //fprintf(fp,"\n");
        strcpy(teacher,"saba");
        addSlist(teacher,ID);
        break;
    case '2':

        fprintf(fp,"\n$teacher:shiri");
        fprintf(fp,"$time=01:00");
        fprintf(fp,"$credit:3$");
        fprintf(fp,"point:00.00$");//five spaces
        fprintf(fp,"AP$");
        //fprintf(fp,"\n");
        strcpy(teacher,"shiri");
        addSlist(teacher,ID);
        fprintf(fp,"\n$teacher:salimi");
        fprintf(fp,"$time=10:00");
        fprintf(fp,"$credit:3$");
        fprintf(fp,"point:00.00$");//five spaces
        fprintf(fp,"Cmath$");
        //fprintf(fp,"\n");
        strcpy(teacher,"salimi");
        addSlist(teacher,ID);
        fprintf(fp,"\n$teacher:saba");
        fprintf(fp,"$time=15:00");
        fprintf(fp,"$credit:3$");
        fprintf(fp,"point:00.00$");//five spaces
        fprintf(fp,"physics2$");
        //fprintf(fp,"\n");
        strcpy(teacher,"saba");
        addSlist(teacher,ID);
        break;
    case '3':
        fprintf(fp,"\n$teacher:dehghan");
        fprintf(fp,"$time=01:00");
        fprintf(fp,"$credit:2$");
        fprintf(fp,"point:00.00$");//five spaces
        fprintf(fp,"english$");
        //fprintf(fp,"\n");
        strcpy(teacher,"dehghan");
        addSlist(teacher,ID);
        fprintf(fp,"\n$teacher:salimi");
        fprintf(fp,"$time=10:00");
        fprintf(fp,"$credit:3$");
        fprintf(fp,"point:00.00$");//five spaces
        fprintf(fp,"math2$");
        //fprintf(fp,"\n");
        strcpy(teacher,"salimi");
        addSlist(teacher,ID);
        fprintf(fp,"\n$teacher:shiri");
        fprintf(fp,"$time=15:00");
        fprintf(fp,"$credit:3$");
        fprintf(fp,"point:00.00$");//five spaces
        fprintf(fp,"DS$");
        //fprintf(fp,"\n");
        strcpy(teacher,"shiri");
        addSlist(teacher,ID);
        break;
    }
}

//----------------------------------------

void addSlist(char *t,char *ID)
{
    int i;
    FILE *fp;
    strcat(t,".txt");
    for(i=0;i<strlen(ID);i++)
    {
        if(ID[i]=='.')
        {
            ID[i]==NULL;
            break;
        }
    }
    fp=fopen(t,"a");
    fprintf(fp,"%s\n",ID);
    fclose(fp);
}

//----------------------------------------

void prof()
{
    int cmd;
    char ema[MAX_STR_LENGTH];
    FILE *fp;
    char temp[100][100];
    char c;
    char *npass;
    char npass1[MAX_STR_LENGTH];
    char nid[MAX_STR_LENGTH];
    int i=0,j=0,t=0,l=0;//counter
    printf("\nenter your email address:");
    scanf("%s",ema);
    fp=fopen("proflist.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%c",&c);
        if(c=='*')
        {
            i++;
            j=0;
        }
        else
        if(c!='*')
        {
            temp[i][j]=c;
            j++;
            t++;
        }
    }
    fclose(fp);
    for(i=0;i<t;i++)
    {
        if(strstr(temp[i],ema)==NULL)
            {
                printf("not teacher! :|");
                exit(1);
            }
        else
            {
                printf("\nenter your national ID:");
                scanf("%s",nid);
                if(strstr(temp[i],nid)==NULL)
                {
                    printf("\nwrong password! :|");
                    exit(1);
                }
                else
                {
                    printf("\nwelcome! :)");
                    printf("\nenter command:");///
                    printf("\nchange password-->1");///
                    printf("\nassign grade-->2");///
                    printf("\nview student list-->3");///
                    //printf("\ndelete student!-->4");
                    scanf("%d",&cmd);
                    switch(cmd)
                    {
                    case 1:
                       npass=strstr(temp[i],nid);
                       printf("\nenter new password:");
                       scanf("%s",npass1);
                       strcpy(npass,npass1);
                       printf("%s",npass);
                       strcpy(npass,"*");
                       printf("%s",temp[i]);
                       fp=fopen("proflist.txt","w");
                       for(l=0;l<t;l++)
                       {
                           fprintf(fp,"%s",temp[l]);
                       }
                       fclose(fp);
                       break;
                    case 2:
                        ag();
                        break;
                    case 3:
                        viewl();
                        break;
                    }
                }
            }
            break;
    }
}

//----------------------------------------

void viewl()
{
    char name[MAX_STR_LENGTH];
    FILE *fp;
    char c;
    printf("\nenter your last name:");
    scanf("%s",name);
    strcat(name,".txt");
    fp=fopen(name,"r");
    while(!feof(fp))
    {
        fscanf(fp,"%c",&c);
        printf("%c",c);
    }
}

//----------------------------------------

void ag()//assign grade
{
    char ID[MAX_STR_LENGTH];
    FILE *fp;
    char temp[1000];
    char temp1[1000];
    char cre[MAX_STR_LENGTH];
    int i=0;
    char c;
    char grade[MAX_STR_LENGTH];
    int strl;//strlen
    char *j;
    int len;
    int len1;
    printf("\nenter student ID:");
    scanf("%s",ID);
    strcat(ID,".txt");
    fp=fopen(ID,"r");
    if(fp==NULL)
    {
        printf("\nno student with this ID :|");
        exit(1);
    }
    else
    {
        while(!feof(fp))
        {
           fscanf(fp,"%c",&c);
           temp[i]=c;
           temp1[i]=c;
           i++;
        }
        fclose(fp);
        printf("\nenter course name:");
        scanf("%s",cre);
        j=strstr(temp,cre);
        //strl=strlen(cre);
        printf("\nenter grade:");
        scanf("%s",grade);
        strcat(grade,"$");
        strcat(grade,j);
        //printf("%s",grade);
        j=j-7;
        len=strlen(temp);
        len1=strlen(grade);
        len1=len-len1;
        *j=NULL;
       // printf("%s",temp);
    //    temp1[-1]=NULL;
    //    temp1[len1]=NULL;
         strcat(temp,":");
         strcat(temp,grade);
    //   printf("%s",temp1);
        fp=fopen(ID,"w+");
        fprintf(fp,"%s",temp);
        fclose(fp);
    }
}

//----------------------------------------

void dltp()
{
    FILE *fp;
    char temp[100];
    char c;
    int i=0,j=0;
    char *dpr;//delete professor
    char profname[MAX_STR_LENGTH];
    printf("\nenter professor's name:\n");
    scanf("%s",profname);
    fp=fopen("proflist.txt","r+");
    while(!feof(fp))
    {
        fscanf(fp,"%c",&c);
        temp[i]=c;
        i++;
    }
    fclose(fp);
    dpr=strstr(temp,profname);
    while(dpr[j]!='*')
    {
        dpr[j]=NULL;
        j++;
    }
    dpr=dpr+j+1;
    strcat(temp,dpr);
    fp=fopen("proflist.txt","w");
    fprintf(fp,"%s",temp);
    strcat(profname,".txt");
    remove(profname);
    fclose(fp);
}

//----------------------------------------

void adm()
{
    int cmd;
    char ID[7];
    char password[11];
    printf("\nenter password:");
    scanf("%s",password);
    if(strcmp(password,"adminadmin")==1)
    {
        printf("\nwrong password! :|");
        exit(1);
    }
    else
    if(strcmp(password,"adminadmin")==0)
    {
        printf("\nwelcome! :)");
        printf("\nenter command:\n");///
        printf("add student-->1\n");///
        printf("add professor-->2\n");///
        printf("view student info-->3\n");///
        printf("edit student info-->4\n");///
        //printf("delete student course-->5\n");
        printf("delete student-->6\n");///
        printf("add new term and courses-->7\n");///
        printf("delete professor-->8\n");
        scanf("%d",&cmd);
        switch(cmd)
        {
        case 1:
            add(0);
            break;
        case 2:
            add(1);
            break;
        case 3:
            printf("\nenter sudent ID:\n");
            scanf("%s",ID);
            view(ID);
            break;
        case 4:
            printf("\nenter sudent ID:\n");
            scanf("%s",ID);
            edit(ID);
            break;
        //case 5:
        case 6:
            printf("\nenter sudent ID:\n");
            scanf("%s",ID);
            dlt(ID);//delete professor
            break;
        case 7:
            printf("\nenter sudent ID:\n");
            scanf("%s",ID);
            append(ID);
            break;
        case 8:
            dltp();//delete professor
            break;
    }
    }
}

//----------------------------------------

void menu()
{
    //int command;
    char temp[MAX_STR_LENGTH];
    char temp1[MAX_STR_LENGTH];
    int i=0,j=0;
    char  c;
    /*printf("\nwho are you?\n");
    printf("1-->admin\n");
    printf("2-->professor\n");
    printf("3-->student\n");
    printf("enter command:\n");
    scanf("%d",&command);
    switch(command)
    {
    case 1:
        adm();//admin function
        break;
    case 2:
        prof();//professor function
        break;
    case 3:
        std();//student function
        break;
    default:
        printf("wrong command!\n");
        break;
    }*/
    ///command line
    printf("\nenter command:\n");
    scanf("%s",temp);
    scanf("%s",temp1);
    if(strcmp(temp,"login")==0)
    {
        if(strcmp(temp1,"admin")==0)
        {
            adm();
        }
        else
        if(strcmp(temp1,"student")==0)
        {
            std();
        }
        else
        if(strcmp(temp1,"professor")==0)
        {
            prof();
        }
        else
        {
            printf("\nwrong command!");
            menu();
        }
    }
    else
    {
        printf("\nwrong command!");
        menu();
    }
}

//----------------------------------------

int main()
{
   menu();
}
