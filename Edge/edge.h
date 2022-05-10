#include <iostream> 

#include "../Node/node.h";
#include "../Vertex/vertex.h";

class Edge {
    public: 
        int id;
        int weight;
        Vertex *head;
        Node *tail;

        Edge(int id, int weight, Vertex *head, Node *tail);
        ~Edge();

        Edge::Edge(int id, int weight, Vertex *head, Node *tail) {
            id = id;
            weight = weight;
            head = head;
            tail = tail;
        }

        Edge::~Edge(){
            delete head;
            delete tail;
        }
    
    
    private:


};
