#include <iostream>
#include<vector>
#include <fstream>
#include <cstring>
#include <cctype>
#include "maze.h"
using namespace std;
//display the options 
void display(){
cout << "1. Load map\n";
cout << "2. Display map\n";
cout << "3. Set Start\n";
cout << "4. Set goal\n";
cout << "5. Find path with DFS\n";
cout << "6. Find path with BFS\n";
cout << "7. Display path with DA\n";
cout << "8. Exit\n";       
}
void loadfile(ifstream& in){
    string fil;
    cout << "Please Enter a text file to read from: ";
    cin >> fil;
    in.open(fil);
    if(in.fail()){
        cout << "Invalid File!\n";
        return;
    }
    cout << "Loaded File Successfully!\n ";
}
// void displaymap(vector<string>& map){
//     for(auto i : map){
//         cout << i << endl;
//     }
// }
// void displaydetails(vector<string>& map){
    
// }

int main() {
int option;
ifstream fin;
maze myMaze;
char start, end;
    do{
        cout << "select an option: \n";
        display();
        cin >> option;
        
    switch(option){
        case 1:
                loadfile(fin);
                myMaze.loadmap(fin);
                break;
        case 2:
                myMaze.printmap();
                break;
        case 3:  
                cout << "select your start: ";
                cin >> start;
                if(myMaze.setStart(start))
                {
                        cout << "the beginnning has been set!\n";
                }
                else{
                        cout << "invalid input!\n";
                }
                break;
        case 4:
                cout << "select your goal: ";
                cin >> end;
                if(myMaze.setEnd(end))
                {
                        cout << "the goal has been set!\n";
                }
                else{
                        cout << "invalid input!\n";
                }
                break;
        case 5:
                cout << "searching a path using Depth First Search (DFS)...\n";
                if(myMaze.DFS())
                {
                        cout << "the path has been found!\n";
                }
                else{
                        cout << "no path exsists from beginning to goal!\n";
                }
                break;
        case 6:
                cout << "searching a path using Breadth First Search (BFS)...\n";
                if(myMaze.BFS())
                {
                        cout << "the path has been found!\n";
                }
                else
                {
                        cout << "no path exsists from beginning to goal!\n";
                }
                break;
        case 7:
                cout << "searching a path using dijkstra algorithm (DA)...\n";
                if(myMaze.DA())
                {
                        cout << "the path has been found!\n";
                }
                else
                {
                        cout << "no path exsists from beginning to goal!\n";
                }
    }
    }while(option!=8);
    cout << "\n---Thank you and Goodbye---\n";
   
    fin.close();   
}