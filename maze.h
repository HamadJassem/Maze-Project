#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cctype>
#include "cell.h"
#include <stack>
#include <queue>
using namespace std;
class maze{
    public:
    //void clearStack();
    //void clearQueue();
    bool setStart(char s){
        if(s==end) return false;
        for(int i = 0; i<map.size(); ++i){
            for(int j = 0; j<map[i].size(); ++j){
                if(s==map[i][j].getname()){
                    start=s;
                    return true;
                }
            }
        }
        return false;
    }
    bool setEnd(char e){
        if(e==start) return false;
        for(int i = 0; i<map.size(); ++i){
            for(int j = 0; j<map[i].size(); ++j){
                if(e==map[i][j].getname()){
                    end = e;
                    return true;
                }
            }
        }
        return false;
    }
    void loadmap(std::ifstream& input){     
        vector<string> tmpmap;
        int y = 0;
        while(!input.eof()){
            string line; 
            getline(input, line);
            tmpmap.push_back(line);
        }
        int line = 1, currentcell = 1;

        for(int n = 0; n<tmpmap.size()-1; n=n+2) {
            vector<cell> cellVector;
            int i = 0, j = 0, k = 1,cost=-1,currentcell =0,x=0;
            char name=' ';
            bool above, below, right, left; 
            // cout << "line " << line << endl;
            
            while (i < tmpmap[n].size() - 1) {
                above = below = right = left = true;
                name =' ';
                if (tmpmap[n][i] == '+') i++; // new path
                if (tmpmap[n][i] == '-') above = false;
                else if (tmpmap[n][i] == ' ') above = true;
                // else error
                i = i + 3; // path left
                if (tmpmap[n+1][j] == '|') left = false; 
                else if (tmpmap[n+1][j] == ' ') left = true; 
                // else error
                j = j + 2; // cost
                if (tmpmap[n+1][j]!=' ')
                    if (isdigit(tmpmap[n+1][j])) cost= (tmpmap[n+1][j] - '0');
                    else { cost = 0; name = tmpmap[n+1][j]; }
                else cost = 0;
                j = j + 2; //path right
                if (tmpmap[n+1][j] == '|') right = false;
                else if (tmpmap[n+1][j] == ' ') right = true;
                // else error
                //path below
                if (tmpmap[n+2][k] == ' ') below = true;
                else if (tmpmap[n+2][k] == '-') below = false;
                // else error
                k = k + 4; // wall below
                cell current(left, right, above, below, cost, name, false,x,y, nullptr);
                cellVector.push_back(current);
                
                // cout << "cell = " << currentcell++ << endl;
                // cout << "above: " << above << "\t";
                // cout << "below: " << below << endl;
                // cout << "right: " << right << "\t";
                // cout << "left: "  << left << endl;
                // cout << "cost: "  << cost << endl;
                // cout<<"name: "<<name<<endl;
                // cout << endl << endl;
                x++;
            }
            // cout << tmpmap[n] << endl;
            // cout << tmpmap[n+1] << endl;
            // cout << tmpmap[n+2] << endl;
            line++;
            map.push_back(cellVector);
            y++;
        }
    }

    void print(){
        for(int i = 0; i<map.size(); ++i){
            for(int j = 0; j<map[i].size(); ++j){
                cout << "Cell: " << i << ", " << j << endl;
                cout << " ";
                map[i][j].printdetails();
            }
            cout << endl;
        }
    }
    void printmap(){
        for(int i = 0; i<map.size(); ++i){
            for(int j = 0; j<map[i].size(); ++j){
                if(!map[i][j].getabove()) cout << "+---";    
                else cout << "+   ";
            }
            cout << "+";
            cout << endl;
            for(int k = 0; k<map[i].size(); ++k){
                if(!map[i][k].getleft()) cout << "|";
                else cout << " ";
                if(start== map[i][k].getname()) cout << "("<<start<<")";
                else if(end == map[i][k].getname()) cout << "{"<<end<<"}";
                else cout << " "<<map[i][k].getname()<<" ";
            }
            cout << "|";
            cout << endl;
        }
        for(int i = 0; i<map[0].size(); ++i){
            cout << "+---";
        }
        cout << "+" << endl;
    }
    bool DFS(){
            
        row = map.size();
        col = map[0].size();
       for(int i = 0; i < map.size();++i)
       {
                bool flag = false;
                for(int j = 0; j < map[i].size() && flag != true;++j){ 
                   if(start == map[i][j].getname())
                   {
                        dfStack.push(&map[i][j]);
                        flag = true;
                   }           //search for start -for now-
                }         
                if(flag == true)break; 
       }
       while(!dfStack.empty()){

                cell* currentcell = dfStack.top();
                
                dfStack.pop();
                int currentsize = dfStack.size();
                
                if(currentcell->getname() == end){   
                        Success(currentcell);   
                        while(currentcell->getname() != start){// it will print o from the end to the beginning
                                if(currentcell->getname() == ' '){
                                        currentcell->setname('o');
                                }
                                currentcell = currentcell->getparent();                  
                        }
                        return true;         
                }
                if(!currentcell->getvisited()){
                        currentcell->setvisited(true);
                        if(currentcell->gety()-1 >= 0){//above
                                if(currentcell->getabove() == true && map[currentcell->gety()-1][currentcell->getx()].getvisited() == false)
                                 {              
                                        dfStack.push(&map[currentcell->gety()-1][currentcell->getx()]); 
                                        dfStack.top()->setparent(currentcell);
                                 }
                        }        
                        if(currentcell->gety()+1 < row){//below
                                if(currentcell->getbelow() == true && map[currentcell->gety()+1][currentcell->getx()].getvisited() == false)
                                        { 
                        
                                                dfStack.push(&map[currentcell->gety()+1][currentcell->getx()]);
                                                dfStack.top()->setparent(currentcell);
                                                
                                                
                                        }
                        }
                        if(currentcell->getx()+1 < col){//right
                                if(currentcell->getright() == true && map[currentcell->gety()][currentcell->getx()+1].getvisited() == false)
                                {               
                                        dfStack.push(&map[currentcell->gety()][currentcell->getx()+1]); 
                                        dfStack.top()->setparent(currentcell);
                                }
                        }
                        if(currentcell->getx()-1 >= 0){//left
                                if(currentcell->getleft() == true && map[currentcell->gety()][currentcell->getx()-1].getvisited() == false)
                                {         
                                        dfStack.push(&map[currentcell->gety()][currentcell->getx()-1]);
                                        dfStack.top()->setparent(currentcell);
                                }
                        }
                }

                if(currentsize == dfStack.size()){ // if it is a deadend, it will go to the previous step.
                       if(currentcell->getname() == ' ')
                       {
                               currentcell->setname('.');
                       }     
                }
       }
       return false;
     }
    bool BFS(){
        row = map.size();
        col = map[0].size();
       for(int i = 0; i < map.size();++i){
                bool flag = false;
               for(int j = 0; j < map[i].size() && flag != true;++j){ 
                   if(start == map[i][j].getname()){
                        bfStack.push(&map[i][j]);
                        flag = true;
                   }           //search for start -for now-
               }         
                if(flag == true)break; 
       }
       while(!bfStack.empty()){

                cell* currentcell = bfStack.front();
                
                bfStack.pop();
                int currentsize = bfStack.size();
                
                if(currentcell->getname() == end){   
                        Success(currentcell);   
                        while(currentcell->getname() != start){// it will print o from the end to the beginning
                                if(currentcell->getname() == ' '){
                                        currentcell->setname('o');
                                }
                                currentcell = currentcell->getparent();                  
                        }
                        return true;         
                }
                if(!currentcell->getvisited()){
                        currentcell->setvisited(true);
                        if(currentcell->gety()-1 >= 0){//above
                                if(currentcell->getabove() == true && map[currentcell->gety()-1][currentcell->getx()].getvisited() == false)
                                 {              
                                        bfStack.push(&map[currentcell->gety()-1][currentcell->getx()]); 
                                        bfStack.back()->setparent(currentcell);
                                 }
                        }        
                        if(currentcell->gety()+1 < row){//below
                                if(currentcell->getbelow() == true && map[currentcell->gety()+1][currentcell->getx()].getvisited() == false)
                                        { 
                        
                                                bfStack.push(&map[currentcell->gety()+1][currentcell->getx()]);
                                                bfStack.back()->setparent(currentcell);
                                                
                                                
                                        }
                        }
                        if(currentcell->getx()+1 < col){//right
                                if(currentcell->getright() == true && map[currentcell->gety()][currentcell->getx()+1].getvisited() == false)
                                {               
                                        bfStack.push(&map[currentcell->gety()][currentcell->getx()+1]); 
                                        bfStack.back()->setparent(currentcell);
                                }
                        }
                        if(currentcell->getx()-1 >= 0){//left
                                if(currentcell->getleft() == true && map[currentcell->gety()][currentcell->getx()-1].getvisited() == false)
                                {         
                                        bfStack.push(&map[currentcell->gety()][currentcell->getx()-1]);
                                        bfStack.back()->setparent(currentcell);
                                }
                        }
                }

                if(currentsize == bfStack.size()){ // if it is a deadend, it will go to the previous step.
                       if(currentcell->getname() == ' ')
                       {
                               currentcell->setname('.');
                       }     
                }
       }
       return false;

    }
    bool DA(){
            
        row = map.size();
        col = map[0].size();
       for(int i = 0; i < map.size();++i)
       {
                bool flag = false;
                for(int j = 0; j < map[i].size() && flag != true;++j){ 
                   if(start == map[i][j].getname())
                   {
                        pq.push(&map[i][j]);
                        flag = true;
                   }           //search for start -for now-
                }         
                if(flag == true)break; 
       }
       while(!pq.empty()){

                cell* currentcell = pq.top();      
               // currentcell->printcoord();
                pq.pop();
                int currentsize = pq.size();
                
                if(currentcell->getname() == end){   
                        Success(currentcell);   
                        while(currentcell->getname() != start){// it will print o from the end to the beginning
                                if(currentcell->getname() == ' '){
                                        currentcell->setname('o');
                                }
                                currentcell = currentcell->getparent();                  
                        }
                        return true;         
                }
                if(!currentcell->getvisited()){
                        currentcell->setvisited(true);
                        if(currentcell->gety()-1 >= 0){//above
                                if(currentcell->getabove() == true && map[currentcell->gety()-1][currentcell->getx()].getvisited() == false)
                                 {       
                                        map[currentcell->gety()-1][currentcell->getx()].setparent(currentcell);       
                                        pq.push(&map[currentcell->gety()-1][currentcell->getx()]); 
                                        
                                 }
                        }        
                        if(currentcell->gety()+1 < row){//below
                                if(currentcell->getbelow() == true && map[currentcell->gety()+1][currentcell->getx()].getvisited() == false)
                                        { 
                                                map[currentcell->gety()+1][currentcell->getx()].setparent(currentcell);
                                                pq.push(&map[currentcell->gety()+1][currentcell->getx()]);
                                                
                                                
                                                
                                        }
                        }
                        if(currentcell->getx()+1 < col){//right
                                if(currentcell->getright() == true && map[currentcell->gety()][currentcell->getx()+1].getvisited() == false)
                                {       
                                       map[currentcell->gety()][currentcell->getx()+1].setparent(currentcell);        
                                        pq.push(&map[currentcell->gety()][currentcell->getx()+1]); 
                                        
                                }
                        }
                        if(currentcell->getx()-1 >= 0){//left
                                if(currentcell->getleft() == true && map[currentcell->gety()][currentcell->getx()-1].getvisited() == false)
                                {         

                                        map[currentcell->gety()][currentcell->getx()-1].setparent(currentcell);
                                        pq.push(&map[currentcell->gety()][currentcell->getx()-1]);
                                        
                                }
                        }
                }

                if(currentsize == pq.size()){ // if it is a deadend, it will go to the previous step.
                       if(currentcell->getname() == ' ')
                       {
                               currentcell->setname('.');
                       }     
                }
       }
       return false;
    }
    private:
    int row;
    int col;
    char start;
    char end;
    vector<vector<cell>> map;
    stack<cell*> dfStack;
    queue<cell*> bfStack;
    priority_queue<cell*, vector<cell*>, compareCost> pq;
    void Success(cell* c){
        while(c!=nullptr){
            c->printcoord();
            c=c->getparent();
        }
    }
};

/*

*/