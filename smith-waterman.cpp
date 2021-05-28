/* 	HOMEWORK 3

	Author :FURKAN HAYTA
	NO:150170022
	DATE:19.05.2021
	Compile :	g++ -std=c++11 -Wall -Werror  smith-waterman.cpp -o smith-waterman
	Run :	./smith-waterman input.txt output.txt match mismatch gap
	
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>

using namespace std;
string convertToString(vector<char>a, int size) // convert char vector to string
{
    int i;
    string s = "";
    for (i = size-1; i >= 0; i--) {
        s = s + a[i];
    }
    return s;
}

void remove(vector<string> &v)			// remove all elements of vector
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = remove(it + 1, end, *it);
    }
    v.erase(end, v.end());
}
 

int max_(int d , int l , int u ,int z){		//return highest value from parameters;
	int max =d;
	if( l > max) max=l;
	if( u > max) max=u;
	if( z > max) max=z;
	return max;
}

void LGC(string one,string two,string outfile_name, string match,string mismatch,string gap){
	
	int longest = 0;
	stack<array<int, 2>> s;		// keeps i,j for elements with the highest score
	
    stringstream geek(match);
    int match_ ;
    geek >> match_;	// match string to int 
	stringstream geek1(mismatch);
    int mismatch_ ;
    geek1 >> mismatch_; // mismatch string to int 
	stringstream geek2(gap);
    int gap_ ;
    geek2 >> gap_;	// gap string to int 
    
	int matrix[one.length()+1][two.length()+1];
	int one_length=one.length();
	int two_length=two.length();
	for(int i =0 ;i<one_length+1 ;i ++){ 	// initializing elements as 0.
		for(int j=0 ;j<two_length+1 ;j++){	
			matrix[i][j]=0;
		}
	}
	
	for(int i =1 ;i<one_length+1 ;i ++){		// matrix filling
		for(int j=1 ;j<two_length+1 ;j++){
			
			int diagonal = matrix[i-1][j-1];
			if (one[i-1]==two[j-1]){
				diagonal = diagonal+match_;
			}
			else diagonal +=mismatch_;
			int left = matrix[i][j-1] + gap_;
			int upper =	matrix[i-1][j] +gap_;
			matrix[i][j] = max_(diagonal,left ,upper ,0);
			if ( matrix[i][j] > longest){
				while(!s.empty()){
					s.pop();
				}
				s.push({i, j});
				longest =matrix[i][j];
			}
			else if (matrix[i][j] == longest){
				s.push({i, j});
			}
			
		}
	}
	
	ofstream outfile;
  	outfile.open(outfile_name, std::ios_base::app); // append instead of overwrite
  	outfile <<one<<" - "<<two<<endl;
	outfile <<"Score: "<<longest<<" Sequence(s):";
	cout <<one<<" - "<<two<<endl;
	cout <<"Score: "<<longest<<" Sequence(s):";
	
	vector <char> a;
	vector<string> seq;
	int size =s.size();
	for(int i=0 ; i<size ; i++){    
		array<int,2> x_y =s.top();
		int x=x_y[0];
		int y=x_y[1];
		while(matrix[x][y]!=0){
			a.push_back(one[x-1]);
			x--;
			y--;
		}
		seq.push_back(convertToString(a,a.size()));
		a.clear();
		s.pop();
	}
	remove(seq);
	sort(seq.begin(), seq.end());
	int seq_size =seq.size();
	if(longest!=0){
		for(int i=0 ;i < seq_size ;i++){
			cout << " " <<  "\"" <<seq[i] <<  "\"" ;
			outfile << " " <<  "\"" <<seq[i] <<  "\"" ;
		}
	}
	outfile<<endl;
	cout<<endl;
	outfile.close();
}
int main(int argc, char *argv[]){
	vector<string> strings;
	string one_string;
	fstream myfile;
	myfile.open(argv[1], ios::in);		// open input file
	while(!myfile.eof()){
		myfile>>one_string;				//read strings
		strings.push_back(one_string); //insert into vector
	}
	ofstream outfile;
	outfile.open(argv[2]); // open new txt file
	
	sort(strings.begin(), strings.end());	// sort strings alphabetically
	int strings_size = strings.size();
	for(int i=0 ; i<strings_size ; i++){	
		for(int j=i+1 ; j<strings_size ;j++){
			LGC(strings[i],strings[j],argv[2],argv[3],argv[4],argv[5]);	
		}
	}
}
