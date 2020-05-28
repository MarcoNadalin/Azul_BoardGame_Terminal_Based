#ifndef NODE_H
#define NODE_H

#include "Tile.h"

class Node {
public:

   Node(Tile* tile, Node* next);
   Node(Tile* tile);
   Node(Node& other);
   ~Node();

   Node* getNext();
   void setNext(Node* next);
   Tile* getValue();


private:
    Node*  next;
    Tile*   tile;
};

#endif // NODE_H