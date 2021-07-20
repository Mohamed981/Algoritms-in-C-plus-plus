#include <iostream>
#include "Node.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<fstream>
using namespace std;
Node*root=NULL;
void LeftRotate(Node*node)
{
    Node*parent1=node->parent;
    Node*grand=node->parent->parent;
    parent1->right=node->left;
    if (node->left!=NULL)
    node->left->parent=parent1;
    node->left=parent1;
    if (grand!=NULL)
    {
        if (grand->right==parent1)
            grand->right=node;
        else
            grand->left=node;
    }
    node->parent=grand;
    parent1->parent=node;

}

void RightRotate(Node*node)
{
    Node*parent1=node->parent;
    Node*grand=node->parent->parent;
    parent1->left=node->right;
    if (node->right!=NULL)
    node->right->parent=parent1;
    node->right=parent1;
    if (grand!=NULL)
    {
        if (grand->right==parent1)
            grand->right=node;
        else
            grand->left=node;
    }
    node->parent=grand;
    parent1->parent=node;
}
void RBTree(Node*node)
{


    if(node->parent->color!='b')
    {
        Node*grand=node->parent->parent;
        Node*uncle;
        Node*parent;

        if(grand->left==node->parent)
        {
            uncle=grand->right;
            parent=grand->left;
        }
        else if (grand->right==node->parent)
        {
            uncle=grand->left;
            parent=grand->right;
        }
        if(uncle==NULL||uncle->color=='b')
        {
            if(grand->left==parent)
            {
                if(parent->left==node)
                {
                    //LL
                    swap(parent->color,grand->color);
                    RightRotate(parent);
                }
                else if(parent->right==node)
                {
                    //LR
                    LeftRotate(node);
                    grand=node->parent;
                    parent=node;
                    swap(parent->color,grand->color);
                    RightRotate(parent);
                }

            }
            else if(grand->right==parent)
            {
                if(parent->left==node)
                {
                    //RL
                    RightRotate(node);
                    grand=node->parent;
                    parent=node;
                    swap(parent->color,grand->color);
                    LeftRotate(parent);
                }
                else if(parent->right==node)
                {
                    //RR
                    swap(parent->color,grand->color);
                    LeftRotate(parent);
                }

            }

        }
        else if(uncle->color=='r')
        {
            grand->color='r';
            grand->left->color=grand->right->color='b';
            if(grand->parent!=NULL&&grand->parent->parent==NULL)
                grand->parent->color='b';
            else if(grand->parent==NULL)
                grand->color='b';
            else
                RBTree(grand);


        }

    }
    if (root->parent!=NULL)
        root=root->parent;
}

void insert1(Node *&node,char* i,Node *&parent)
{
    if(node==NULL&&parent!=NULL)
    {
        node=new Node(i);
        if(strcmp(i,node->data)<0)
        {
            parent->left=node;
            //left
        }
        else if(strcmp(i,node->data)>0)
        {
            parent->right=node;
            //right
        }
        node->parent=parent;
        RBTree(node);


    }
    else if(node==NULL)
    {
        node=new Node(i);
        node->parent=NULL;
        root=node;
        node->color='b';

    }
    else
    {

        if(strcmp(i,node->data)<0)
        {

            insert1(node->left,i,node);


        }
        else if(strcmp(i,node->data)>0)
        {
            insert1(node->right,i,node);
        }
        else
            cout <<("ERROR: Word already in the dictionary!\n");

    }






}
void PrintInOrder(Node*node)
{
    if(node!=NULL)
    {
        PrintInOrder(node->left);
        printf("%s -color:%c \n",node->data,node->color);
        PrintInOrder(node->right);

    }


}

int height(Node*node)
{
    return (node==NULL)?-1:1+max(height(node->left),height(node->right));
}
int sizee(Node *root)
{
    if (root!=NULL)
    {
        return 1+sizee(root->right)+sizee(root->left);
    }
    return 0;
}

void PrintPreOrder(Node *node)
{
    if(node!=NULL)
    {
        printf("%s -color:%c \n",node->data,node->color);
        PrintPreOrder(node->left);
        PrintPreOrder(node->right);

    }
}

int searchfn(Node *node,char* data)
{
    if (node==NULL)
    {
     cout <<"No\n";
     return 0;
    }
    else if(strcmp(data,node->data)>0)
         searchfn(node->right,data);
    else if (strcmp(data,node->data)<0)
         searchfn(node->left,data);
    else
    {
       cout <<"Yes\n";
        return 1;
    }

}
void loadfile (char* filename)
{

    char* b;
    int i=0;
    string line;
    ifstream file;
    file.open(filename);
    if (file.is_open())
  {
    while ( getline (file,line) )
    {
        b=(char*)malloc(sizeof(char)*line.length());
        strcpy(b,line.c_str());
      i++;
        insert1(root,b,root);
        free(b);
    }
    file.close();
  }

  else cout << "Unable to open file";

   /* FILE *f=fopen(filename,"r");
    if (f!=NULL)
    {
    while (!feof(f))
    {
        i++;
        fscanf(f,"[^\n]",b);
        insert1(root,b,root);

    }
    }
    else
        cout << "File Not Found\n";
    fclose(f);*/
}


int main()
{
  int Option;

    do
    {
        char* filename=(char*)malloc(25);
        char* data=(char*)malloc(25);
        cout <<"Please Select An Option :\n";
        cout <<"--------------------------\n";
        cout <<" 1) Load From File \n";
        cout <<" 2) Insert  \n";
        cout <<" 3) Search  \n";
        cout <<" 4) Quit \n" ;
        cout <<"Choose an Option: ";
        cin >>Option;
        cout <<"\n";
       switch(Option)
        {
        case 1 :
            system("@cls||clear");

            cout << "Enter The File Name :";
            cin >> filename;
            loadfile(filename);
            cout << "Height :" << height(root) ;
            cout << "\nSize   :" << sizee(root) ;
            cout << "\n";
            break;
        case 2 :
             system("@cls||clear");

            cout << "Enter The word you want to insert :";
            cin >> data;
            insert1(root,data,root);
            cout << "Height :" << height(root) ;
            cout << "\nSize   :" << sizee(root) ;
            break;
        case 3:
           system("@cls||clear");
            cout << "Enter The word you want to Search on it :";
            cin >> data;
            searchfn(root,data);
            break;
            break;
        case 4:
            exit(0);
            break;
        default:
            system("@cls||clear");
            break;

        }
        cout << "\n";
        }
    while(Option!=4);
    return 0;
}
