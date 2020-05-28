#include "Node.h"

Node::Node(Tile* tile, Node* next) {
    this->tile = tile;
    this->next = next;
}

Node::Node(Node& other) {
    
}

Node::~Node() {
    //delete this;
    //delete tile;
    //delete next;
}

Node* Node::getNext() {
    return next;
}

void Node::setNext(Node* next) {
    this->next = next;
}

Tile* Node::getValue() {
    return tile;
}