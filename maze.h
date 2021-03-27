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
    //void BFS();
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
        while(!input.eof()){
            string line; 
            getline(input, line);
            tmpmap.push_back(line);
        }
        int line = 1, currentcell = 1;

        for(int n = 0; n<tmpmap.size()-1; n=n+2) {
            vector<cell> cellVector;
            int i = 0, j = 0, k = 1,cost=-1,currentcell =0;
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
                cell current(left, right, above, below, cost, name, false);
                cellVector.push_back(current);
                
                // cout << "cell = " << currentcell++ << endl;
                // cout << "above: " << above << "\t";
                // cout << "below: " << below << endl;
                // cout << "right: " << right << "\t";
                // cout << "left: "  << left << endl;
                // cout << "cost: "  << cost << endl;
                // cout<<"name: "<<name<<endl;
                // cout << endl << endl;
            }
            // cout << tmpmap[n] << endl;
            // cout << tmpmap[n+1] << endl;
            // cout << tmpmap[n+2] << endl;
            line++;
            map.push_back(cellVector);
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
        for(int i = 0; i<map.size(); ++i){
            cout << "+---";
        }
        cout << "+" << endl;
    }
    void DFS(){
       for(int i = 0; i < map.size();++i){

               for(int j = 0; j < map[i].size() && flag != true;++j){ // FOR NOW FOR NOW FOR NOW FOR NOW FOR NOW I WILL CHANGE IT I WILL CHANGE IT
                   if(start == map[i][j].getname()){// I WILL CHANGE IT I WILL CHANGE IT I WILL CHANGE IT I WILL CHANGE IT
                           dfStack.push(map[i][j]); // I WILL CHANGE IT I WILL IT CHANGE IT I WILL CHANGE IT I WILL CHANGE IT
                           
                   }             
               }
               cout << dfStack.top().getname() << endl; // I WILL CHANGE IT I WILL CHANGE IT I WILL CHANGE IT I WILL CHANGE IT
                if(flag == true)break; // I WILL CHANGE IT I WILL CHANGE IT I WILL CHANGE IT I WILL CHANGE IT
       } 

       while(!dfStack.empty()){
               cell currentCell = dfStack.top();
               dfStack.pop();
                if(dfStack.top().getname() != end){
                        
                        
                }


       }
    }
    private:
    char start;
    char end;
    vector<vector<cell>> map;
    stack<cell> dfStack;
    queue<cell> bfStack;
};