#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        Node(char*);
        Node*left,*right,*parent;
        char color;
        char data[60];
        virtual ~Node();

    protected:

    private:
};

#endif // NODE_H
