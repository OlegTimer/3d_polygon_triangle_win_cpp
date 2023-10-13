#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void init(){

ifstream ino("./_options.txt", ios::in | ios::binary);
if(!ino) {
ofstream outo("./_options.txt"); 
if(!outo) {
exit(1);
}
int get_width();
int get_height();
outo << get_width()<<"\n";
outo << get_height()<<"\n";
outo.close();
}
string line;
int counter=0;
    while (getline(ino, line)) {
void set_width(int a);
void set_height(int a);		  
        if (counter==0){set_width(atoi( line.c_str()) );}
        if (counter==1){set_height(atoi( line.c_str()) );}
        counter++;
    }
ino.close();	 

string s("F1 for info. Up to start");	 
void set_str(string s);	  
set_str(s);

void try_to_read_field();
try_to_read_field();
}
