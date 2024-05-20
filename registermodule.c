#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
# define max 50

typedef struct accInfo{
    char name[31];
    char accnum[6];
    char bd[31];
    char con[31];
    char pincode[7];
    int dep;
}AC;

typedef struct registration{
  AC ab[max];
  int last;
}REG;

REG L;
void makenull();
void add(AC x);
void del(char n[31]);
int display(char n[31]);
int locate(char n[31]);
int locPosition(char n[31]);
int isempty();
int isfull();
void save();
void retrieve();
int menu();
int check(char n[31]);
void encrypt();
void pincode();
void insertcard(char n[31]);

char pin[7];
int code;

int main(){
AC acc;
makenull();
retrieve();
code = rand() % 99;
int same;
system("cls");
printf("Registration Mode...\n");

    retry:
    printf("Enter account number (5 digits) : ");
    scanf("%[^\n]%*c", acc.accnum);
  if(strlen(acc.accnum) != 5)
{
   printf("invalid input...\n"); goto retry;
}
   same = locate((acc.accnum));
            if (same>-1){
                printf("Duplicate Account Number.\n");
                system("pause"); goto retry;
            }
    printf("Enter your Name : ");
    scanf("%[^\n]%*c", acc.name);
    printf("Enter your birth date: ");
    scanf ("%[^\n]%*c", acc.bd);
    printf("Enter Contact number: ");
    scanf("%[^\n]%*c", acc.con); second:
    printf("Enter your Initial Deposit (min. 5000): ");
    scanf("%d", &acc.dep);
    if (acc.dep<5000)
    {
    printf("Invalid input. Must be 5000 initial Deposit");
    system("pause");goto second;
    }
    printf("Enter 4-6 digits Pin Code: ");
    pincode();
    encrypt();
    strcpy(acc.pincode, pin);
    add(acc);
    display(acc.accnum);
    insertcard(acc.accnum);

return (0);
}


int locate(char n[31]){
int i;
for (i=0;i<=L.last;i++)
    if (strcmp(L.ab[i].accnum,n)==0)
        return(i);
return(-1);
}

int locPosition(char n[31]){
int i;
for (i=0;i<=L.last;i++){
    if (strcmp(L.ab[i].accnum,n)>0)
        return (i);
}
return (i);

}
int isempty(){
    return(L.last==-1);
}

int isfull(){
   return(L.last==max-1);
}

void makenull(){
  L.last = -1;
}

int check(char n[31]){
  int i;
    for(i=0;i<=L.last;i++)
        if (strcmp(L.ab[i].accnum,n)==0)
            return (i);
    return(-1);
}

void pincode(){
int index =0;
char ch;
while((ch=getch())!=13 && index<5){
    if (index<0)
        index=0;
    if(ch==8)
    {
        putch('\b');
        putch(' ');
        putch('\b');
        index--;
     continue;
    }
    if(isdigit(ch)){
     pin[index++]=ch;
     putch('*');
    }
}
if (index==5)
    pin[index++]=ch;
pin[index]='\0';
}

void add(AC x){
int i,p;
if (isfull()){
    printf("Account is full.\n");
    system("pause");
}
else {
    p=locPosition(x.accnum);
    for (i=L.last;i>=p;i--){
        L.ab[i+1]=L.ab[i];
    }
        L.ab[p] = x;
        L.last++;
}
}

void encrypt(){
int i=0;
while(pin[i]!='\0'){
    pin[i]=pin[i] + code;
    i++;
}
}
int display(char n[31]){
int i;
int p;
char option;
i=locate(n);
system("cls");
printf("\nList Information\n");
printf("Account Number: %s \n",L.ab[i].accnum);
printf("Account Name: %s \n", L.ab[i].name);
printf("Birthday: %s \n",L.ab[i].bd);
printf("Contact number: %s \n ",L.ab[i].con);
printf("Initial Deposit (Min.5000) : %d \n", L.ab[i].dep);
printf("Pin code: %s ",L.ab[i].pincode);
printf("\n Would you like to save this account? press y if yes press any key if no: ");

scanf("%s", &option);
if (option=='Y'|| option =='y'){
    save();
    system("pause");
}
else{
    exit (0);
}
}

void save(){
FILE *fp;
int i;
fp = fopen("isn2ab.dbf","w+");
if (fp==NULL){
    printf("File error.\n");
    system("pause");
}
else {
    for (i=0;i<=L.last;i++)
        fprintf(fp,"%s \n %s %s %s %d %s \n",L.ab[i].accnum, L.ab[i].name,L.ab[i].bd,L.ab[i].con,L.ab[i].dep,L.ab[i].pincode);
}
fclose(fp);
}

void retrieve(){
FILE *fp;
AC r;
fp = fopen("isn2ab.dbf","r+");
if (fp==NULL){
    printf("File error.\n");
    system("pause");
}
else {
    while (!feof(fp)){
       fscanf(fp,"%s \n %s %s %s %d %s \n",r.accnum,r.name,r.bd,r.con,&r.dep,r.pincode);
      add(r);
   }
 fclose(fp);
 }
}

void insertcard(char n[31]){
    int p;
p=locate(n);
FILE *fp;
do{
     system("cls");
    printf("FINDING ATM CARD...\n");
    fp = fopen("E:\\isn2ab.dbf","r+");
} while(fp==NULL);
fclose(fp);
system("pause");

}

