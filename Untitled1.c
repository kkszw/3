#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
typedef struct FCB{   //�ļ���Ŀ¼���ƿ�
   char name[8];//�ļ���Ŀ¼��
   int size;//�ļ���Ŀ¼��С��Ŀ¼��С������Ϊ0
   int type;//���ͣ�1Ϊ�ļ���2ΪĿ¼
   int flag;//��¼�ڼ����ļ�
   char datetime[30];	//����ʱ�䣬��ʽΪyyyymmdd hhmmss
   struct FCB *next;//��һ���ֵܽڵ�
   struct FCB *pro;//���ڵ�
   struct FCB *child;//��һ�����ӽڵ�
}myFCB;
myFCB *fcb;
char path[30];//·��
myFCB *calcultime(myFCB *f)//����ʱ��
{
    char s[10],temp[20]={""};
    time_t time_ptr;
    struct tm *tmp_ptr=NULL;
    time(&time_ptr);
    tmp_ptr=localtime(&time_ptr);
    itoa(1900+tmp_ptr->tm_year,s,10);
    strcat(temp,s);
    strcat(temp,"-");
    itoa(1+tmp_ptr->tm_mon,s,10);
    strcat(temp,s);
    strcat(temp,"-");
    itoa(tmp_ptr->tm_mday,s,10);
    strcat(temp,s);
    strcpy(s,__TIME__);
    strcat(temp," ");
    strcat(temp,s);
    strcpy(f->datetime,temp);
    return f;
}
void add(myFCB *head,myFCB *sour)
{
    myFCB *temp=head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=sour;
}
void createFile(myFCB *fcb)//������Ŀ¼
{
    myFCB *f=(myFCB *)malloc(sizeof(myFCB));
    myFCB *q1=(myFCB *)malloc(sizeof(myFCB));
    myFCB *q2=(myFCB *)malloc(sizeof(myFCB));

    scanf("%s",f->name);
    f->pro=fcb;
    f->type=2;
    f->flag=0;
    f->size=2;
    fcb->size+=f->size;
    f=calcultime(f);
    f->child=NULL;
    f->next=NULL;
    fcb->flag++;
    add(fcb->child,f);

    strcpy(q1->name,".");
    strcpy(q2->name,"..");
    q1=calcultime(q1);
    q2=calcultime(q2);
    q1->type=2;
    q2->type=2;
    q1->size=1;
    q2->size=1;
    q1->next=NULL;
    q2->next=NULL;

    f->child=q1;
    add(f->child,q2);
}
myFCB *searchfcb(myFCB *f,char filename[])//����Ŀ¼
{
    myFCB *temp=f->child;
    while(temp!=NULL)
    {
        if(strcmp(temp->name,filename)==0)
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}
void left(char *dst,char *src, int n)//���ַ�������߽�ȡn���ַ�
{
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if(n>len)
        n=len;
    while(n--)
        *(q++)=*(p++);
    *(q++)='\0';
}
myFCB *cd(myFCB *f)
{
    char filename[10];
    scanf("%s",filename);
    if(strcmp(filename,"..")==0)
    {
        if(f->pro==NULL)
        {
            printf("�ѵ���Ŀ¼�����ɺ���\n");
            return f;
        }
        else
        {
            left(path,path,strlen(path)-strlen(f->name)-1);
            return f->pro;
        }
    }
    else
    {

        if(searchfcb(f,filename)!=NULL)
        {
            f=searchfcb(f,filename);
            strcat(path,"\\");
            strcat(path,f->name);
            return f;
        }
        else
        {
            printf("δ�ҵ���Ŀ¼\n");
            return f;
        }
    }
}
void deletef(myFCB *f)
{
    char filename[10];
    myFCB *temp=f->child,*te=NULL;
    scanf("%s",&filename);
    if((f=searchfcb(f,filename))!=NULL)
    {
        while(temp!=NULL&&temp!=f)
        {
            te=temp;
            temp=temp->next;
        }
        if(f->next!=NULL)
        {
            te->next=f->next;
        }
        else
        {
            te->next=NULL;
        }
        f->pro->size-=f->size;
    }
    else
    {
        printf("δ�ҵ���Ŀ¼\n");
    }
}
void create(myFCB *fcb)//�����ļ�
{
    myFCB *f=(myFCB *)malloc(sizeof(myFCB));
    scanf("%s",f->name);
    f->pro=fcb;
    f->type=1;
    f->flag=0;
    f->size=0;
    fcb->size+=f->size;
    f=calcultime(f);
    f->child=NULL;
    f->next=NULL;
    fcb->flag++;
    add(fcb->child,f);
}
void defile(myFCB *f)
{
    char filename[10];
    myFCB *temp=f->child,*te=NULL;
    scanf("%s",&filename);
    if((f=searchfcb(f,filename))!=NULL)
    {
        while(temp!=NULL&&temp!=f)
        {
            te=temp;
            temp=temp->next;
        }
        if(f->next!=NULL)
        {
            te->next=f->next;
        }
        else
        {
            te->next=NULL;
        }
    }
    else
    {
        printf("δ�ҵ����ļ�\n");
    }
}
void showall(myFCB *f)
{
    myFCB *temp=f->child;
    printf("����%sĿ¼�µ��ļ�\n",path);
    while(temp!=NULL)
    {
        printf("%s    ",f->datetime);
        if(temp->type==2)
            printf("<DIR>\t");
        else
            printf("\t\t");
        printf("%5d\t",temp->size);
        printf("%s\n",temp->name);
        temp=temp->next;
    }
}
void Menu()
{
    char order[5];
    strcpy(order,"c");
    myFCB *f=fcb;
    while(strcmp(order,"exit"))
    {
        printf("%s>",path);
        scanf("%s",order);
        if(strcmp(order,"md")==0||strcmp(order,"MD")==0)//ʶ�𴴽�Ŀ¼ָ��
        {
            createFile(f);
        }
        else if(strcmp(order,"cd")==0||strcmp(order,"CD")==0)
        {
            f=cd(f);
        }
        else if(strcmp(order,"rd")==0||strcmp(order,"RD")==0)
        {
            deletef(f);
        }
        else if(strcmp(order,"mk")==0||strcmp(order,"MK")==0)
        {
            create(f);
        }
        else if(strcmp(order,"del")==0||strcmp(order,"DEL")==0)
        {
            defile(f);
        }
        else if(strcmp(order,"dir")==0||strcmp(order,"DIR")==0)
        {
            showall(f);
        }
        else if(strcmp(order,"exit")==0)
        {
            printf("���˳�����\n");
        }
        else
        {
            printf("δָ֪��\n");
        }
    }
}
void main()
{
    fcb=(myFCB *)malloc(sizeof(myFCB));
    strcpy(path,"D:\\test");
    strcpy(fcb->name,"D:\\test");
    fcb->child=NULL;
    fcb->pro=NULL;
    fcb->next=NULL;
    fcb->type=2;
    myFCB *q1=(myFCB *)malloc(sizeof(myFCB));
    myFCB *q2=(myFCB *)malloc(sizeof(myFCB));
    q1=calcultime(q1);
    q2=calcultime(q2);
    q1->type=2;
    q2->type=2;
    q1->size=1;
    q2->size=1;
    q1->next=NULL;
    q2->next=NULL;
    strcpy(q1->name,".");
    strcpy(q2->name,"..");
    fcb->child=q1;
    add(fcb->child,q2);
    Menu();
}
/*
dir
cd ..
md qwe
dir
md asd
dir
cd zxc
cd qwe
dir
rd asd
md asd
dir
rd asd
dir
cd ..
dir
rd qwe
dir
rd asd
dir
mk qwe
dir
mk asd
dir
del qwe
dir
del asd
dir


*/
