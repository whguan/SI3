/***************************************************************** 
*COMP 550 SI3- Sorting Flags

Input :  Segments
Output: Sorted endpoints of Segments

Purpose: Sorting the starting flag and terminal according to rules:
	1. Compare by x coordinates, breaking ties by y; 
	2. If same point, compare by type: ternimal < start;
	3. If same type, compare by starting slope;
	4. If same slope, compare by color : 
		blue start < red start;
	        red terminal < blue terminal
Date: Sep 10th, 14 by  Wenhua Guan

******************************************************************/
#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <limits>
#include <string>
using namespace std;

//Define 1st class: Point
class Point {

	public:	int x, y;
	
	Point(int x0, int y0){
		x = x0;
		y = y0;
	}
	
	//Comparison by x, breaking ties by y
	bool LessThan(Point *q){
		return (x < q->x)||((x == q->x) && (y < q->y));
	}
	//Define two points equal
	bool Equal(Point *q){
		return((x == q->x) && (y == q->y));
	}

};


class Segment{
 
	//Members
	public:	Point  *start, *end;
	
	//constructor
	Segment(Point  *start0, Point *end0){
		start = start0;
		end = end0;
	}
	~Segment(){
		delete start;
		delete end;
	}

	static double MiniusSlope(Point *start, Point *end){
		if(start->x != end->x){
			return -(start->y-end->y)/(start->x-end->x);
		
		}else{
			return numeric_limits<int>::max();
		
		}
	}

};

class flag {
	public: Point *P;
		Segment *Seg;
		int NoSeg;
		int typetag;
		string color;
			
	flag(Point *P0, Segment *Seg0,int NoSeg0, int typetag0, string color0){
		P = P0;
		Seg = Seg0;
		NoSeg = NoSeg0;
		typetag = typetag0;
		color = color0;
	}
	~flag(){
		delete P;
	}
};

	// Compare flags, return true if flag f1 < f2, vise versa
bool compare(flag *f0,flag *f1){
	if (!(f0->P->Equal(f1->P))){
		return f0->P->LessThan(f1->P);// Point: Compare by x, breaking ties by y
	}else if (f0->typetag != f1->typetag){
		return f0->typetag < f1->typetag;            // Tyep : terminal < start
	}else if(Segment::MiniusSlope(f0->Seg->start, f0->Seg->end) !=
		 Segment::MiniusSlope(f1->Seg->start, f1->Seg->end) ){
		return Segment :: MiniusSlope(f0->Seg->start, f0->Seg->end)<
		Segment::MiniusSlope(f1->Seg->start, f1->Seg->end); // -Slope
	}else if(f0->typetag == 1){ //start blue<  start red  
		return f0->color <  f1->color; 
	}else if(f0->typetag == 0){ // red term < blue term
		return f0->color > f1->color;
	}else{
		 cout <<"Overlapping lines of same color error!" <<endl;
		 return false;
	}
}

int main(int argc, char *argv[]){
	int m, n, k;
	
	//Read coordinates of segments into variables
	if(argc !=2){
		printf("ERROR: No input file!");
		exit(EXIT_FAILURE);
	}
	
	FILE *fp;
	fp = fopen(argv[1],"r");
	if(fp ==NULL){
		printf("ERROR: Can't open input file!");
		exit(EXIT_FAILURE);
	}
	
	fscanf(fp,"%d %d %d\n",&m, &n, &k );
      	
	vector<Segment *> RedSeg;
	vector<Segment *> BlueSeg;
	vector<flag *> FlagList;

	for (int i = 0; i < m; i++){
		int x1,y1,x2,y2;
		fscanf(fp,"%d %d %d %d\n", &x1,&y1, &x2, &y2);
		Point *P = new Point(x1, y1), *Q = new Point(x2, y2);
		Segment *s = new Segment(P,Q); 
		flag *start = new flag(P,s,i,1,"R"), *end = new flag(Q,s,i,0,"R");//start: typetag =1; end: typetag=0
        //        flag start(P,s,i,1,"R"), end(Q,s,i,0,"R");
		RedSeg.push_back(s); 		//  red: color = 0; blue : color = 1; 
		FlagList.push_back(start);   
		FlagList.push_back(end);
	}
	for(int j=0; j<n; j++){
		int x1,y1,x2,y2;
		fscanf(fp,"%d %d %d %d\n", &x1,&y1, &x2, &y2);
		Point *P = new Point(x1,y1), *Q = new Point(x2,y2);
		Segment *s = new Segment(P,Q);
	//	flag start(P,s,j,1,"B"), end(Q,s,j,0, "B");
		flag *start = new flag(P,s,j,1,"B"), *end = new flag(Q,s,j,0,"B");
		
		BlueSeg.push_back(s);
		FlagList.push_back(start);
		FlagList.push_back(end);
	
	}

	fclose(fp);
        
	// Sort FlagList
	sort(FlagList.begin(), FlagList.end(),compare);
	
	// Print
	for (vector<int>:: size_type i =0; i < FlagList.size(); i++){
		cout << FlagList[i]->NoSeg+1<<FlagList[i]->color 
		<<(FlagList[i]->typetag ==0 ? "T":"S")<<endl;
	
	}

	//Delete
	for(vector<int>::size_type i=0; i < RedSeg.size(); i++) 
		delete RedSeg[i];

	for(vector<int>::size_type j=0; j < BlueSeg.size(); j++)
		delete BlueSeg[j];
	for(vector<int>::size_type i =0; i < FlagList.size(); i++)
		delete FlagList[i];
	while(!RedSeg.empty()){
		RedSeg.pop_back();
	}
	while(!BlueSeg.empty()){
		BlueSeg.pop_back();
	}
	while(!FlagList.empty()){
		FlagList.pop_back();
	}
	
	return 0;

}
