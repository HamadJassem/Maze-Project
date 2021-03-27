#include <iostream>
using namespace std;
class cell{
    public:
    cell(bool l=false, bool r=false, bool u=false, bool d=false, int c=0, char n=' ', bool v=false): left(l), right(r), above(u), below(d), cost(c), name(n), visited(v){};
    bool getleft(){return left;}
    bool getright(){return right;}
    bool getabove(){return above;}
    bool getbelow(){return below;}
    void setleft(bool l){left = l;};
    void setright(bool r){right = r;};
    void setabove(bool a){above = a;};
    void setbelow(bool b){below = b;};
    int getcost(){return cost;}
    char getname(){return name;}
    void setname(char n){name = n;};
    bool getvisited(){return visited;}
    void setvisited(bool v){visited = v;}
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
    private:
    bool left;
    bool right;
    bool above;
    bool below;
    int cost;
    char name;
    bool visited;
};