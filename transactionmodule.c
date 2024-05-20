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
    int balance;
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
void account();
void pincode();
void encrypt();
int insertcard();
void balance(int p);
void withdraw( int n, int p);
void deposit(int n, int p);
void fund_t(int a, int n, int p);
void ch_pin();

char pin[7];
int code;

int locate(char n[31]){
int i;
for (i=0;i<=L.last;i++)
    if (strcmp(L.ab[i].pincode,n)==0)
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
        if (L.ab[i].accnum == n)
            return (i);
    return(-1);
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

void pincode(){
int index =0;
char ch;
while((ch=getch())!=13 && index<5){
    if (index<0)
        index=0;
    if(ch==8)
    {
        putchar('\b');
        putchar(' ');
        putchar('\b');
        index--;
     continue;
    }
    if(isdigit(ch)){
     pin[index++]=ch;
     putchar('*');
    }
}
if (index==5)
    pin[index++]=ch;
pin[index]='\0';
}


void encrypt(){
int i=0;
while(pin[i]!='\0'){
    pin[i]=pin[i] + code;
    i++;
}
}

int display(char n[31]){

int p;
p = locate(n);
   system("cls");
	printf("List Information\n");
    printf("Account Number:%s \n",L.ab[p].accnum);
    printf("Account Name: %s \n", L.ab[p].name);
    printf("Birthday: %s \n", L.ab[p].bd);
    printf("Contact number: %s \n",L.ab[p].con);
    printf("Balance: %d \n" , L.ab[p].balance);
    printf("Enrypted Pin Code %s : \n",L.ab[p].pincode);

    system("pause");

return(p);
}


void balance(int p){
printf( "Current Balance!: %d \n", L.ab[p].balance);
system("pause");
}

void withdraw(int n, int p){
    start:
if (L.ab[p].balance<5000){
  printf("cannot withdrawn! the current balance is %d", L.ab[p].balance);
    printf("Balance must be minimum of 5000php ");
    goto start;
}
else{
    if(n <= L.ab[p].balance){
	L.ab[p].balance = L.ab[p].balance - n;
	printf(" withdrawn/transfer: %d ", n);
    printf("current added balance: %d", L.ab[p].balance);
    save();
	}
	else if ( L.ab[p].balance < n){
	printf( "\n Cannot process... %d", L.ab[p].balance);

	}
}
system("pause");
}

void deposit(int n, int p){
    system("cls");
    L.ab[p].balance = L.ab[p].balance + n;
	printf( "\nYou have deposit: %d", n);
	printf("\nYour current balance: %d" ,L.ab[p].balance);
    save();
    system("pause");
}

void fund_t(int a, int n, int p){
if (L.ab[p].balance<5000 || p==-1){
    printf(" ERROR...\n");
}
else if ( L.ab[p].balance < a){
	  printf("\n you only have %d", L.ab[p].balance);
	}

else{
    L.ab[p].balance = L.ab[p].balance - a;
    save();
    L.ab[n].balance = L.ab[n].balance + a;
    printf("\n\n\n You transfer: %d to %s ", L.ab[n].balance, L.ab[n].name);
    printf(" \n Your current balance was: %d" , L.ab[p].balance);
    save();
    }
system("pause");
}

void ch_pin(){
int i, p;
PIN:
    system("cls");
    printf(" \n CHANGE PIN\n");
    printf("Press your current PIN: ");
   pincode();
    encrypt();
    p=locate(pin);
    if(p==-1){
        printf("Wrong pincode...\nPlease enter valid Pin\n");
        system("pause");
        goto PIN;
        }
    else{
	    printf("\n\n enter your NEW pin: ");
        pincode();
        encrypt();
        printf("\n Encrypted Pin Code = %s\n", pin);
        strcpy(L.ab[i].pincode, pin);
        save();
}
system ("pause");
}


int main(){
       AC acc;

   makenull();
    retrieve();
    int choice, amount, depo, p, f = 0;
    p = insertcard();
   system("cls");
   printf( "Menu \n ");
   printf("1. Withdraw\n");
   printf("2. Deposit\n");
   printf("3. Fund Transfer\n");
   printf("4. Change PIN\n" );
   printf("5. Exit\n");
   printf("select: ");
   scanf("%d", &choice);
int same;


                switch(choice){
                    case 0:
                    {
                        balance(p);
                        break;
                    }
                    case 1:
                    {
                        withdraw:
                        printf( "\n\n Enter the amount to withdraw? ");
	                    scanf("%d", &amount);
                        if (amount <  100){
		                printf("\n Please enter 99php and above\n ");
                        system("pause");
		                goto withdraw;
	                        }
                        else
                            withdraw(amount,p);
                        break;
                    }
                    case 2:
                    {
                        dep :
		                printf("\n\n Enter the amount  to deposit:  ");
	                    scanf("%d", &depo);
                        if (depo <  100){
		                printf("\nPlease enter 99php and above\n ");
                        system("pause");
		                goto dep;
	                        }
                        else
                            deposit(depo,p);
                        break;
                    }
                    case 3:
                    {
                        retry:
                        system("cls");
                        printf("\n Enter the account number of the person you want to transfer: "); scanf("%s", acc.accnum);
                        same = locate((acc.accnum));
                        if (same>-1){
                           printf("Duplicate Account Number.\n");
                          system("pause"); goto retry;
                            }
                        printf("\n\n Enter the amount to transfer:  "); scanf("%d", &amount);
                        if (amount <  100){
		                    printf("\nPlease enter 99php and above\n ");
                            system("pause");
		                    goto retry;
	                        }
                        else
		                    fund_t(amount, f, p);
                        break;
                    }
                    case 4:
                    {
                       ch_pin();
                        break;
                    }
                    case 5:
                    {
                      printf("Press any key to exit");
                        system("pause");
                        exit(0);
                    }
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
        fprintf(fp,"%s \n %s %s %s %d %s \n",L.ab[i].accnum,L.ab[i].name,L.ab[i].bd,L.ab[i].con,L.ab[i].balance,L.ab[i].pincode);
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
       fscanf(fp,"%s \n %s %s %s  %d %s \n",r.accnum,r.name,r.bd,r.con,&r.balance,r.pincode);
      add(r);
   }
 fclose(fp);
 }
}

int insertcard(){

int p;
code = rand() % 99;
FILE *fp;

do{
      printf("FINDING ATM CARD...\n");
        fp=fopen("E:\\isn2ab.dbf","r");
    } while(fp==NULL);
    fclose(fp);
    retry:

        printf("Please enter PIN : ");
        pincode();
        encrypt();
        p=locate(pin);
        if(p==-1){
           printf( "Please enter valid Pin\n");

	    system ("pause");
		goto retry;
            }
    else{
        display(pin);
    }
return(p);
}


