#include "Node.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

Node::Node(char* data)
{
    left=NULL;
    right=NULL;
    parent=NULL;
    strcpy(this->data,data);
    color='r';
}

Node::~Node()
{
    //dtor
}
