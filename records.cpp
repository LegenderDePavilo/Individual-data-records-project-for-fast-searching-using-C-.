#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 10
#define NAME 10
using namespace std;
struct bst
{
    char data[SIZE];
    struct bst *left,*right;
}*root=NULL;
class student
{
char roll[SIZE];
char name[SIZE];
public:
    student()
    {
        strcpy(roll,"NA");
        strcpy(name,"NA");
    }
  void getdata(char data[])
  {
      strcpy(roll,data);
      cout<<"\nEnter the name : ";cin>>name;
  }
  void writedata()
  {
      cout<<name<<"\n"<<roll<<"\n";
  }
  int insertrecord(struct bst*,char []);
  int deleterecord(struct bst*,char []);
  int modifyrecord(struct bst*,char []);
  void displayrecord(struct bst*,char []);
  int searchrecord(struct bst*,char []);
};
struct bst*insertnode(bst*,char []);
struct bst *deletenode(struct bst*,char []);
struct bst *findmax(struct bst*);
void display(struct bst*);
void write(struct bst * root);
void deleteall(struct bst*);
int main()
{
    struct bst *head;
    int k,ch;
    char data[SIZE];
    ifstream fin;
    fin.open("bstre.txt",ios::binary|ios::in);
    if(fin)
    fin>>setw(5)>>ch;
    else
        ch=0;
    k=ch;
    if(ch>0)
    while(fin&& ch>0)
    {
        fin>>setw(SIZE-1)>>data;
        root=insertnode(root,data);
        --ch;
    }
    fin.close();
    student R;
    do
    {
    cout<<"\n1. Insert a record\n"<<"2. Delete a record\n"<<"3. Edit a record\n"<<"4. Display a record\n"<<"5. Display list of records\n"<<"6. Delete all records\n"<<"7. Exit once for all\n";
    cout<<"\nEnter your choice : ";
    cin>>ch;
    switch(ch)
    {
        case 1:
            cout<<"\nEnter the roll number of the student to be inserted : ";
            cin>>data;
            head=root;
            ch=R.insertrecord(head,data);
            while(ch==-2)
            {
                cout<<"\nEnter the new different roll number : ";
                cin>>data;
                ch=R.insertrecord(head,data);
            }
            if(ch==1)
            {
            root=insertnode(root,data);
            ++k;
            cout<<"\nRecord of the student entered successfully.\n";
            }
            else
                cout<<"\nRecord not stored successfully.\n";
            break;
        case 2:
            cout<<"\nEnter the roll number of the student to be deleted : ";
            cin>>data;
            head=root;
            ch=R.deleterecord(head,data);
            if(ch)
            {
            root=deletenode(root,data);
            --k;
            cout<<"\nRecord of the student deleted successfully.\n";
            }
            else
                cout<<"\nRecord not deleted successfully.\n";
            break;
        case 3:
            cout<<"\nEnter the roll number of the student whose record is to be modified : ";
            cin>>data;
            head=root;
            ch=R.modifyrecord(head,data);
            if(ch)
            {
            cout<<"\nRecord of the student modified successfully.\n";
            }
            else
                cout<<"\nRecord not modified successfully.\n";
            break;
        case 4:
            head=root;
            cout<<"\nEnter the roll number whose record is to be displayed : ";
            cin>>data;
            R.displayrecord(head,data);
            break;
        case 5:
            if(root!=NULL)
            {
            head=root;
            cout<<"\nThe number of existing records is : "<<k<<"\n";
            display(head);
            }
            else
                cout<<"\nThere are no existing records.\n";
            break;
        case 6:
                deleteall(root);
                root=NULL;
                char roll[18];
                strcpy(roll,"bstre.txt");
                remove(roll);
                fflush(stdin);
                cout<<"\nAll records deleted successfully.\n";
                k=0;
                break;
        case 7:
            cout<<"\n\tEXITED From Records\n";
            exit(1);
        default:
            cout<<"\nWrong choice\n";
    }
    cout<<"\nDo you want to continue (1/0) : ";
    cin>>ch;
    }
    while(ch==1);
    ofstream fout;
    fout.open("bstre.txt",ios::binary|ios::trunc|ios::out);
    fout<<setw(5)<<k;
    fout.close();
    write(root);
    return 0;
}
void write(struct bst * root)
{
    if(root)
    {
        write(root->left);
        ofstream fout;
        fout.open("bstre.txt",ios::binary|ios::app|ios::out);
        fout<<setw(SIZE-1)<<root->data;
        fout.close();
        write(root->right);
    }
    return;
}
void read(struct bst * root)
{
    ofstream fout;
    fout.open("bstre.txt",ios::binary|ios::app|ios::out);
    if(root)
    {
        write(root->left);
        fout<<root->data<<"\n";
        write(root->right);
    }
}
void deleteall(struct bst * root)
{
    if(root)
    {
    deleteall(root->left);
    char roll[18];
    strcpy(roll,root->data);
    strcat(roll,".txt");
    remove(roll);
    deleteall(root->right);
    }
    return;
}
struct bst*insertnode(struct bst*root,char data[SIZE])
{
    if(root==NULL)
    {
        root=(struct bst *)malloc(sizeof(struct bst));
        if(root==NULL)
        {
            cout<<"\nMemory error";
            exit(1);
        }
    strcpy(root->data,data);
    root->left=NULL;
    root->right=NULL;
    }
    else
    {
        int p=strcmp(data,root->data);
            if(p==-1)
                root->left=insertnode(root->left,data);
            else if(p==1)
                root->right=insertnode(root->right,data);
    }
    return root;
}
void display(struct bst *root)
{
    if(root)
    {
        display(root->left);
        cout<<"\n"<<root->data;
        display(root->right);
    }
    return;
}
struct bst *deletenode(struct bst*root,char data[SIZE])
{
    struct bst *temp;
    if(root==NULL)
        cout<<"\nThere are no existing records\n";
    else if(strcmp(data,root->data))
    {
            int p=strcmp(data,root->data);
            if(p==-1)
                root->left=deletenode(root->left,data);
            else if(p==1)
                root->right=deletenode(root->right,data);
    }
    else
    {
        if(root->right&&root->left)
        {
            temp=findmax(root->left);
            strcmp(root->data,temp->data);
            root->left=deletenode(root->left,root->data);
        }
        else
        {
            temp=root;
            if(root->left==NULL)
                root=root->right;
            else if(root->right==NULL)
                root=root->left;
            free(temp);
        }
    }
    return root;
}
struct bst *findmax(struct bst*root)
{
    if(root==NULL)
       return NULL;
    else if(root->right==NULL)
        return root;
    else
    return (findmax(root->right));

}
int student::insertrecord(struct bst *head,char data[])
{
    int i=searchrecord(head,data);
    if(i)
    {
        cout<<"\n'Sorry' this roll number already exists, please try for another.\n";
        return -2;
    }
    student();
    getdata(data);
    if(!strcmp(roll,"NA"))
        return 0;
    char filename[18];
    strcpy(filename,data);
    strcat(filename,".txt");
    ofstream fout;
    if(!fout)
    {
        cout<<"\nFile error.\n";
        return 0;
    }
    fout.open(filename,ios::binary|ios::trunc|ios::out);
    fout.write((char*)this,sizeof(*this));
    fout.close();
    return 1;
}
int student::deleterecord(struct bst *head,char data[SIZE])
{
            int i=searchrecord(head,data);
            if(i)
            {
            char roll[18];
            strcpy(roll,data);
            strcat(roll,".txt");
            remove(roll);
            return 1;
            }
            else
            {
                cout<<"\nFile does not exist for deletion.\n";
                return 0;
            }
}

int student::modifyrecord(struct bst * head,char data[SIZE])
{
    int i=searchrecord(head,data);
            if(i)
            {
                cout<<"Are you sure to make changes to the existing record as follows ? (1/0) : ";
                cin>>i;
                displayrecord(head,data);
                if(i)
                {
                    student();
                    getdata(data);
                    if(!strcmp(roll,"NA"))
                    return 0;
                    char filename[18];
                    strcpy(filename,data);
                    strcat(filename,".txt");
                    ofstream fout;
                    if(!fout)
                        {
                            cout<<"\nFile error.\n";
                            return 0;
                        }
                    fout.open(filename,ios::binary|ios::trunc|ios::out);
                    fout.write((char*)this,sizeof(*this));
                    writedata();
                    fout.close();
                    return 1;
                }
            }
            else
                cout<<"\nFile does not exist for modification.\n";
return 0;
}
void student::displayrecord(struct bst * head,char data[SIZE])
{
    int i=searchrecord(head,data);
    if(i)
    {
        char filename[18];
        strcpy(filename,data);
        strcat(filename,".txt");
        ifstream fin;
            if(!fin)
            {
                cout<<"\nFile error.\n";
                return;
            }
            fin.open(filename,ios::binary|ios::app|ios::in);
            fin.read((char*)this,sizeof(*this));
            writedata();
            fin.close();
    }
    else
        cout<<"\nRecord does not exist for display.\n";
    return;
}
int student::searchrecord(struct bst * head,char data[SIZE])
{
    int temp;
    if(head==NULL)
        return 0;
        else
        {
            if(!strcmp(data,head->data))
                return 1;
            else
            {
                temp=searchrecord(head->left,data);
                if(temp!=0)
                    return temp;
                else
                    return (searchrecord(head->right,data));
            }
        }
}
