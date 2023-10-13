#include <vector> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;

#define PI 3.14159

double pitch=0; //in radians
double roll=0;
double yaw =0;
double angle_step = 0.0175;
double move_step = 0.125;
vector< vector<int> >  drawpol;
vector< vector<double> >  drawpol_temp;
vector< vector<double> >  field;
vector< vector<double> >  field2;
int get_width(); int get_height();
int d=get_width()*2;
int kx=get_width()/2; 
int ky=get_height()/2;
double pitchshow = 0;
double rollshow = 0;
double yawshow =0;


void clear_drawpol(){
drawpol.clear();	 
	 }		 

int get_drawpol_size(){
return 	 drawpol.size();
	 }
	 
int get_drawpol(int a, int b){
return 	 drawpol[a][b];
	 }	 	  


void clear_field(){
field.clear();	 
	 }

	 
void try_to_read_field(){
clear_drawpol();	 
ifstream file2("./_input.txt");
if(!file2) {
ofstream out3("./_input.txt"); 
if(!out3) {
exit(1);
}
out3<<-1<<"\t"<<1<<"\t"<<-10<<"\t"<<1<<"\t"<<1<<"\t"<<-10<<"\t";
out3<<1<<"\t"<<-1<<"\t"<<-10<<"\t"<<0<<"\t"<<0<<"\t"<<255;
out3.close();
}
file2.close();
//
ifstream file("./_input.txt");
if (file.is_open()) {	     					
    std::string line;
    while (std::getline(file, line)) {
        line.c_str();
        vector<string> arr;
        vector<double> arrd;
  string delim("\t");
  size_t prev = 0;
  size_t next;
  size_t delta3 = delim.length();
  while( ( next = line.find( delim, prev ) ) != string::npos ){
    arr.push_back( line.substr( prev, next-prev ) );
    prev = next + delta3;
  }
arr.push_back( line.substr(prev ) );

for (int i=0; i<arr.size(); i++){
double t  =  atof(arr[i].c_str()) ; 
arrd.push_back(t);
}
field.push_back(arrd);
    }
    file.close();
}	 
	 }	 //  try_to_read_field end


double checkangle (double d){
void calc();  calc();
return 0;	   
}

void up(){	 //pitch
pitchshow-=angle_step;
pitch = angle_step;
pitch = checkangle(pitch);	
	 }
	 
void down(){
pitchshow+=angle_step;	 
pitch = -angle_step;
pitch = checkangle(pitch);	 	 
	 }
	 
void left(){ //yaw	
yawshow+=angle_step;
yaw = angle_step;
yaw = checkangle(yaw);
	 }
	 
void right(){
yawshow-=angle_step;	 
yaw = -angle_step;
yaw = checkangle(yaw); 	 
	 }	 	 	 

void roll_left(){
rollshow+=angle_step;	 
roll = angle_step;
roll = checkangle(roll); 
	 }

void roll_right(){
rollshow-=angle_step;	 
roll = -angle_step;
roll = checkangle(roll); 	 
	 }


void calc(){
clear_drawpol();
drawpol_temp.clear();
double coord[3][3];

for (int r=0; r<field.size(); r++){ //poly field start
coord[0][0]=field[r][0]; coord[0][1]=field[r][1]; coord[0][2]=field[r][2];
coord[1][0]=field[r][3]; coord[1][1]=field[r][4]; coord[1][2]=field[r][5];
coord[2][0]=field[r][6]; coord[2][1]=field[r][7]; coord[2][2]=field[r][8];

double yawr; double tx;
yawr = pitch; 
for (int i=0; i<3; i++){
tx = coord[i][1];
coord[i][1]= tx*cos(yawr)-coord[i][2]*sin(yawr);
coord[i][2]= tx*sin(yawr)+coord[i][2]*cos(yawr); }

yawr= yaw; 
for (int i=0; i<3; i++){
tx = coord[i][0];
coord[i][0]= tx*cos(yawr)-coord[i][1]*sin(yawr);
coord[i][1]= tx*sin(yawr)+coord[i][1]*cos(yawr); }

yawr = roll; 
for (int i=0; i<3; i++){
tx = coord[i][0];
coord[i][0]= tx*cos(yawr)-coord[i][2]*sin(yawr);
coord[i][2]= tx*sin(yawr)+coord[i][2]*cos(yawr); }

field[r][0]=coord[0][0]; field[r][1]=coord[0][1]; field[r][2]=coord[0][2];
field[r][3]=coord[1][0]; field[r][4]=coord[1][1]; field[r][5]=coord[1][2];
field[r][6]=coord[2][0]; field[r][7]=coord[2][1]; field[r][8]=coord[2][2];

if (coord[0][2]<0 || coord[1][2]<0 || coord[2][2]<0) {
double backface_culling=1;
double x1= coord[0][0] - coord[1][0];
double x2= coord[0][0] - coord[2][0];
double y1= coord[0][1] - coord[1][1];
double y2= coord[0][1] - coord[2][1];
double z = x1*y2-y1*x2;
backface_culling = -z;
if (backface_culling>0){
vector <double> ivector; 
double min =   coord[0][2];
if (coord[1][2]<min){min=coord[1][2];}
if (coord[2][2]<min){min=coord[2][2];}
ivector.push_back(min);					  
double plusz =  coord[0][2]; if (plusz<0){plusz=-plusz;} if (plusz<1){plusz=1;} 				  
tx = coord[0][0]*d/plusz+kx;  ivector.push_back(tx); 
tx=-coord[0][1]*d/plusz+ky;  ivector.push_back(tx);
plusz =  coord[1][2]; if  (plusz<0){plusz=-plusz;} if (plusz<1){plusz=1;}
tx = coord[1][0]*d/plusz+kx;  ivector.push_back(tx);
tx=-coord[1][1]*d/plusz+ky;  ivector.push_back(tx);
plusz =  coord[2][2]; if  (plusz<0){plusz=-plusz;} if (plusz<1){plusz=1;}
tx = coord[2][0]*d/plusz+kx; ivector.push_back(tx);
tx=-coord[2][1]*d/plusz+ky; ivector.push_back(tx);
ivector.push_back((int)field[r][9]);  
ivector.push_back((int)field[r][10]); 
ivector.push_back((int)field[r][11]); 
drawpol_temp.push_back(ivector);
}// backface_culling end
}//if any of z coord below 0
}//poly field end

sort (drawpol_temp.begin(), drawpol_temp.end()); 
 for (int i = 0; i < drawpol_temp.size(); i++) {
vector <int> ivector;  	 
 for (int i2 = 1; i2 < drawpol_temp[0].size(); i2++) {
double d =  drawpol_temp[i][i2];
int p = (int) d;	 
ivector.push_back(p);	  	 
	  } 
drawpol.push_back(ivector);	  	 
	  }

void showline(); showline();	
void redraw(); redraw();
} //calc end	 


void copyfield(){
field2.clear();	 
for (int i2=0; i2<field.size(); i2++){
vector<double> arrd;	
for (int i=0; i<field[0].size(); i++){
arrd.push_back(field[i2][i]);	
}
field2.push_back(arrd);
}	 
	 }


void copyfield2(){
field.clear();	 
for (int i2=0; i2<field2.size(); i2++){
vector<double> arrd;	
for (int i=0; i<field2[0].size(); i++){
arrd.push_back(field2[i2][i]);	
}
field.push_back(arrd);
}	 
	 }
	 	 

void checkmove(){
int condition = 1;
for (int i=0; i<field2.size(); i++){//check field side for collisions start
double x,y,z, r;
x = field2[i][0]; if (x<0){x=-x;}
y = field2[i][1]; if (y<0){y=-y;}
z = field2[i][2]; if (z<0){z=-z;}
r=x+y+z;
if (r<6){ //if collision may happen
double d1=sqrt(field2[i][0]*field2[i][0]+field2[i][1]*field2[i][1]+field2[i][2]*field2[i][2]);
double d2=sqrt(field2[i][3]*field2[i][3]+field2[i][4]*field2[i][4]+field2[i][5]*field2[i][5]);
double d3=sqrt(field2[i][6]*field2[i][6]+field2[i][7]*field2[i][7]+field2[i][8]*field2[i][8]);
if (d1<1 || d2<1 || d3<1){
condition=0;
}
else{
if (d1+d2+d3<9){condition=0;}	 
	 }   		    		  
}//if collision may happen end
} //check field side for collisions end	

if (condition==1){
copyfield2();  				  
calc();
}
else{
	 void claim_collision(); claim_collision();
	 }	 
}//checkmove end

void forward (){
copyfield(); 
for (int i2=0; i2<field2.size(); i2++){
field2[i2][2]+=move_step;
field2[i2][5]+=move_step;
field2[i2][8]+=move_step;
} 	 
checkmove(); 
	 }

void back (){  
copyfield(); 
for (int i2=0; i2<field2.size(); i2++){
field2[i2][2]-=move_step;
field2[i2][5]-=move_step;
field2[i2][8]-=move_step;
} 	 
checkmove(); 	  
	 }

void stepleft (){	 
copyfield(); 
for (int i2=0; i2<field2.size(); i2++){
field2[i2][0]+=move_step;
field2[i2][3]+=move_step;
field2[i2][6]+=move_step;
} 	 
checkmove();	 
	 }
	 
void stepright (){
copyfield(); 
for (int i2=0; i2<field2.size(); i2++){
field2[i2][0]-=move_step;
field2[i2][3]-=move_step;
field2[i2][6]-=move_step;
} 	 
checkmove();	 
	 }
	 
void stepup(){		 
copyfield(); 
for (int i2=0; i2<field2.size(); i2++){
field2[i2][1]-=move_step;
field2[i2][4]-=move_step;
field2[i2][7]-=move_step;
} 	 
checkmove();	 
	 }
	 
void stepdown(){ 
copyfield(); 
for (int i2=0; i2<field2.size(); i2++){
field2[i2][1]+=move_step;
field2[i2][4]+=move_step;
field2[i2][7]+=move_step;
} 	 
checkmove();	 
	 }	 	  


double checkzeroangle (double d){
if (d<0){d=2*PI+d;}
if (d>2*PI){d=d-2*PI;}
return d;	   
}


void showline(){
string s("");
pitchshow=checkzeroangle(pitchshow);
std::ostringstream strs;
strs <<(int) (pitchshow*57.3);
s += strs.str()+" ";
strs.str("");
rollshow=checkzeroangle(rollshow);
strs <<(int) (rollshow*57.3);
s += strs.str()+" ";
strs.str("");
yawshow=checkzeroangle(yawshow);
strs <<(int) (yawshow*57.3);
s += strs.str()+"    ";
void set_str(string s);	  
set_str(s);	 	 
if (field.size()<1){
string s("Seems _input.txt is empty. Fill it, please");	 
void set_str(string s);	  
set_str(s);   					
} 
	 }
	 

void claim_collision(){
string s("Collision!");	 
void set_str(string s);	  
set_str(s); 
void redraw(); redraw();	 
	 }	 
