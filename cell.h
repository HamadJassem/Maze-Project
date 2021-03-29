#include <iostream>
using namespace std;
class cell{
    public:
    cell(bool l=false, bool r=false, bool u=false, bool d=false, int c=0, char n=' ', bool v=false,int x=0,int y=0, cell* prnt=nullptr): left(l), right(r), above(u), below(d), cost(c), name(n), visited(v),coordinate_x(x),coordinate_y(y), parent(prnt){};
    cell(const cell& c){
        left = c.left;
        right = c.right;
        above = c.above;
        below = c.below;
        cost = c.cost;
        name = c.name;
        visited = c.visited;
        coordinate_x = c.coordinate_x;
        coordinate_y = c.coordinate_y;
    }
    bool operator==(const cell& c){
        if(*this==c){
            return true;
        }
        else{
            return false;
        }
    }
    bool operator==(const cell* c){
        if(this==c){
            return true;
        }else{
            return false;
        }
    }
    bool operator!=(const cell& c){
        return !operator==(c);
    }
    bool operator!=(const cell* c){
        return !operator==(c);
    }
      cell& operator=(const cell& c){
        if(this == &c){
                return* this;
        }    
        else{
        left = c.left;
        right = c.right;
        above = c.above;
        below = c.below;
        cost = c.cost;
        name = c.name;
        visited = c.visited;
        coordinate_x = c.coordinate_x;
        coordinate_y = c.coordinate_y;      
        }
        return*this;
    }
    bool getleft(){return left;}
    bool getright(){return right;}
    bool getabove(){return above;}
    bool getbelow(){return below;}
    void setleft(bool l){left = l;};
    void setright(bool r){right = r;};
    void setabove(bool a){above = a;};
    void setbelow(bool b){below = b;};
    int getcost()const{return cost;}
    char getname(){return name;}
    void setname(char n){name = n;};
    bool getvisited(){return visited;}
    void setvisited(bool v){visited = v;}
    int getx(){return coordinate_x;}
    void setx(int x){coordinate_x=x;}
    int gety(){return coordinate_y;}
    void sety(int y){coordinate_y=y;}
    void printdetails(){
        cout << "Left: " << left << endl;
        cout << "Right: " << right << endl;
        cout << "Above: " << above << endl;
        cout << "Below: " << below << endl;
        cout << "Name: " << name << endl;
        cout << "Visited: "<< ((visited)?"Yes":"No");
        cout << endl;
        cout << "Cost: " << cost << endl;
        cout << endl;
    }
    void printcoord(){
        cout << "("<<coordinate_x << ", " << coordinate_y<<")";
    }
    void setparent(cell* x){
            parent = x;
    }
    cell* getparent(){
            return parent;
    }

    private:
//must implement parent node
    cell* parent;
    bool left;
    bool right;
    bool above;
    bool below;
    int cost;
    char name;
    bool visited;
    int coordinate_x;
    int coordinate_y;
};

struct compareCost { // defining the comparison operator
  bool operator() (const cell* cell1, const cell* cell2) {
    return (cell1->getcost() > cell2->getcost());
  }
};
