#include <iostream> 

#include "../Node/node.h";


class Vertex {
    public: 
        int id;
        int degree;
        Node *node;

        Vertex(int id, int degree, Node *node);
        ~Vertex();

        Vertex::Vertex(int id, int degree, Node *node) {
            node = node;
            degree = degree;
            id = id;
        }

        Vertex::~Vertex(){
            delete node;
        }
    
    private:


};
