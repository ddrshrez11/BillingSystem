#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
void bills();
void add();
void edit();
void ddelete();
void dispall();
void menu();
void retmenu();
int inputint();
struct data{
	int code;
	char name[50];
	int rate;
} s;

void main()
{
    menu();
}


void menu()
{
    char options;
    system("cls");
    printf("\n\n\t\tCOMPANY'S NAME\n\n\n");
    printf("MAIN MENU:\n1.Calculate Bills\n2.Add Items\n3.Edit Items\n4.Delete Items\n5.Display All\n6.Exit\n\n");
    printf("Choose An Option:");
    //scanf(" %c",&options);
    options=getche();
    switch(options)
    {
        case '1':
            bills();
            break;
        case '2':
            add();
            break;
        case '3':
            edit();
            break;
        case '4':
            ddelete();
            break;
        case '5':
            system("cls");
            dispall();
            retmenu();
            break;
        case '6':
            printf("\n\n\t\t Thank You!!");
            exit(1);
            break;
        default:
            printf("\n\nINVALID OPTION!");
            getch();
            menu();
        }
}

void bills()
{
    struct data s;
    FILE *fp, *fp1;
    int code[100],qty[100],rate[100],amount[100],i,ni,j,total=0,input,v,cnt;
    char cname[100];
    system("cls");
    fp= fopen("items.txt","r");
    fp1= fopen("bill.txt","w");
    if (fp==NULL)
	{
		printf("cannot open file");
		exit(1);
	}
	if (fp1==NULL)
	{
		printf("cannot open file");
		exit(1);
	}
    printf("______Calculate Bills______\n");
    printf("Enter Customer's Name:");
    scanf("%s",cname);
    printf("\nEnter Number of Items:");
    ni=inputint();
    //scanf(" %d",&ni);
    system("cls");
    dispall();
    printf("\n\n\n");
    for(i=0;i<ni;i++)
    {
	printf("\n\nEnter Code:");
	//scanf(" %d",code[i]);
	cnt=inputint();
	code[i]=cnt;
	printf("\nEnter Quantity:");
	cnt=inputint();
	qty[i]=cnt;
    }
    system("cls");
    printf("\t\t\tCUSTOMER'S BILL");
    printf("\n\n\tNAME: %s", cname);
    printf("\n\n\nS.N\tPARTICULARS\tQUANTITY\tRATE\t  AMOUNT ");
    fprintf(fp1,"\n\t\t\tCUSTOMER'S BILL\n\n\t Name: %s\n\nS.N\tPARTICULARS\tQUANTITY\t RATE \t AMOUNT \n\n",cname);
    for(i=0;i<ni;i++)
    {
        cnt=0;
        while(!feof(fp))
        {
            fscanf(fp," %d\t%s\t%d\n",&s.code, s.name, &s.rate);
            if(s.code==code[i])
            {
                amount[i]=s.rate*qty[i];
                printf("\n %2d\t %-10.10s\t%7d \t%4d\t%7d\n",i+1,s.name,qty[i],s.rate,amount[i]);
                fprintf(fp1,"\n %2d\t  %-11s\t\t%8d\t\t%6d\t%8d\n",i+1,s.name,qty[i],s.rate,amount[i]);
                total=total+amount[i];
                cnt=1;
            }
        }
        if (cnt!=1)
            {
                printf("\nItem not found\n");
            }
        rewind(fp);
    }
    printf("\n\n\t\t\t\t\t Total=%d",total);
    fprintf(fp1,"\n\n\t\t\t\t\t Total=%d",total);
    fclose(fp);
    fclose(fp1);
    getch();
    retmenu();

}

void edit()
{
    FILE *fp1, *fp2;
    int cod;
    system("cls");
    fp1= fopen("items.txt","r");
    fp2= fopen("temp.txt","w");
    if (fp1==NULL)
	{
		printf("Cannot Open File");
		exit(1);
	}
	if (fp2==NULL)
	{
		printf("Cannot Open File");
		exit(1);
	}
	printf("Records Before Alteration\n");
	dispall();
	rewind(fp1);

	printf("Enter Code to Edit:");
	scanf("%d",&cod);
	while(!feof(fp1))
        {

            fscanf(fp1,"%d\t%s\t%d\n",&s.code, s.name, &s.rate);
            if(s.code==cod)
            {
                printf("Enter New Name:");
                scanf("%s",s.name);
                printf("Enter New Rate:");
                scanf("%d",&s.rate);
                fprintf(fp2,"%d\t%s\t%d\n", s.code, s.name, s.rate);
            }
            else
            {
                fprintf(fp2,"%d\t%s\t%d\n", s.code, s.name, s.rate);
            }
        }
    fclose(fp1);
    fclose(fp2);

    remove("items.txt");
    rename("temp.txt","items.txt");
    system("cls");
    printf("Records After Alteration\n");
    dispall();
    rewind(fp1);
    getch();
    retmenu();
}

void dispall()
{
    int i=0;
    struct data s;
	FILE *fp;
	fp= fopen("items.txt","r");
    if (fp==NULL)
	{
		printf("Cannot open file");
		exit(1);
	}
    printf("\nCode\tPARTICULARS\tRATE");
	while(!feof(fp))//getc(fp)!=EOF)//!feof(fp))
    {

        fscanf(fp,"%d\t%s\t%d\n",&s.code, s.name, &s.rate);
        printf("\n %2d\t %-11.10s\t%4d\n", s.code, s.name, s.rate);
        //i++;
    }
    fclose(fp);

	getch();
}

void ddelete()
{
    FILE *fp1, *fp2;
    int delno;
    system("cls");
    fp1= fopen("items.txt","r");
    fp2= fopen("temp.txt","w");
    if (fp1==NULL)
	{
		printf("Cannot open file");
		exit(1);
	}
	if (fp2==NULL)
	{
		printf("Cannot open file");
		exit(1);
	}
	printf("Records Before Alteration\n");
	dispall();
	rewind(fp1);
	printf("Enter Code to Delete:");
	scanf("%d",&delno);
	while(!feof(fp1))
        {
            fscanf(fp1,"%d\t%s\t%d\n",&s.code, s.name, &s.rate);
            if(s.code==delno)
            {
                continue;
            }
            else
            {
                fprintf(fp2,"%d\t%s\t%d\n", s.code, s.name, s.rate);
            }
        }
    fclose(fp1);
    fclose(fp2);

    remove("items.txt");
    rename("temp.txt","items.txt");
    system("cls");
    printf("Records After Alteration\n");
    dispall();
    rewind(fp1);
    getch();
    retmenu();
}

void add()
{
    char opt='y';
	FILE *fp;
    system("cls");
	fp= fopen("items.txt","a");
    if (fp==NULL)
	{
		printf("cannot open file");
		exit(1);
	}

	while(opt=='y'|| opt=='Y')
    {
        printf("Enter Code:");
        scanf(" %d",&s.code);
        printf("Enter Name:");
        scanf(" %s",s.name);
        printf("Enter Rate:");
        scanf(" %d",&s.rate);
        fprintf(fp,"%d\t%s\t%d\n", s.code, s.name, s.rate);
        printf("\n\n Record Added Successfully.");
        printf("\nAdd More Items[Y/N]?");
        opt=getche();
    }
	//fwrite(&s,sizeof(s),1,fp);
	fclose(fp);
	getch();

	retmenu();

}

void retmenu()
{
    char mm;
    printf("\n\n\nReturn to Main Menu?[Y/N]");
	scanf(" %c",&mm);
	//mm=getche();
	if (mm=='y'||mm=='Y')
    {
        system("cls");
        menu();
    }
    else if (mm=='N'|| mm=='n')
        exit(1);
    else retmenu();
}

int inputint()
{
    char a;
    int b,c;
    a=getche();
    b=(int)a-48;
    c=0;
    while(a>=48&&a<=58)
    {
        a=getche();
        if(a=="")
        {
            break;
        }
        else
        {
            c=c*10+b;
        }
        b=(int)a-48;
    }
    return c;
}
