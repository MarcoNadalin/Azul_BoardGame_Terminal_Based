#ifndef COSC_ASS_TWO_TILE
#define COSC_ASS_TWO_TILE

class Tile{
    public:
        //default constructor
        Tile();
        //in constructor, set colour according to integer parameter
        Tile(int c);        
        ~Tile();
        int getColour();
        void setColour(int col);
        
    private: 
        // //enumeration of colours
        enum Colour {
            EMPTY,
            B, 
            Y, 
            R, 
            U,
            L, 
            F            
        }; 

        Colour colour;
};

#endif