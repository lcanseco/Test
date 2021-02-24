#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdio>

using namespace std;

const long BILLION = 1000000000;
const long MILLION = 1000000;

map<string, int> reference;

string ones[] = {"one","two","three","four","five","six","seven","eight","nine"};
string teens[]={"Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};
string tens[]={"Ten","Twenty","Thirty","Fourty","Fifty","Sixty","Seventy","Eighty","Ninety"};

void loadMapRelations()
{
  for(int i = 1; i < 10; i++){
    //fill with ones
    std::transform(ones[i-1].begin(), ones[i-1].end(), ones[i-1].begin(), ::toupper);
    reference[ones[i-1]] = i;
    //fill with teens
    std::transform(teens[i-1].begin(), teens[i-1].end(), teens[i-1].begin(), ::toupper);
    reference[teens[i-1]] = i + 10;
    //fill with tens
    std::transform(tens[i-1].begin(), tens[i-1].end(), tens[i-1].begin(), ::toupper);
    reference[tens[i-1]] = i * 10;
  }
  //hardcore fullfilling
  reference["AND"] = -1;
  reference["ZERO"] = 0;
  reference["HUNDRED"] = 100;
  reference["THOUSAND"] = 1000;
  reference["MILLION"] = 1000000;
  reference["BILLION"] = 1000000000;
}



long suma_all_items(vector<long> *temp) {
  long tot =0;

  for(int i=0;i<temp->size(); i++) {
    tot += temp->at(i);
  }
  return tot;
}

int main(){
  
  //set up
  loadMapRelations();
  //vars
  string test;
  string buffer, buffer2;
  int count = 0; 
  vector<long> temp_vector;
  vector<long> total_vector;
  bool flag = false;
  //get text
  cout << "Enter a text: ";
  getline (cin,test);

  cout<<"Texto resultante:\n";
  test.append(" ");
  
  int length_test = test.length();
  for(int i = 0; i < length_test; i++){
    if( i+1 == length_test){
      flag=false;
    }
    if(test.at(i) == '-'){test.at(i)=' ';}
    if (test.at(i) == ' ') {
      if(flag == 0 && (temp_vector.size() > 0 || total_vector.size() >0 )) {
    	total_vector.push_back( suma_all_items(&temp_vector) );
    	long gran_total = suma_all_items(&total_vector);
    	cout<<gran_total<<" ";
	temp_vector.resize(0);
	total_vector.resize(0);
	count=0;
      }
      if(buffer2.size()>0){
	cout<<buffer2<<" ";
      }
      buffer="";
      buffer2="";
    } else {    
      buffer.push_back(toupper(test.at(i)));
      map<string, int>::iterator it = reference.find(buffer);
      if(it != reference.end() && (test.at(i+1) == ' ' || test.at(i+1) == '-')){//match
	buffer2 = "";
	flag = true;	
	if((*it).second == -1) { //AND special
	  //cout<<"find un AND \n";
	} else if((*it).second == 1000000000) { //Billion
	  total_vector.push_back( suma_all_items(&temp_vector) * BILLION );
	  temp_vector.resize(0);
	  count=0;
	} else if((*it).second == 1000000) { //Million
	  total_vector.push_back( suma_all_items(&temp_vector) * MILLION );
	  temp_vector.resize(0);
	  count=0;	
	} else if((*it).second == 1000) { //Thousand
	  total_vector.push_back( suma_all_items(&temp_vector) * 1000 );
	  temp_vector.resize(0);
	  count=0;
	} else if((*it).second == 100) { //Hundred	
	  temp_vector[count-1] *= 100;
	} else {
	  temp_vector.push_back((*it).second);
	  count++;
	}
	buffer = "";
      } else {
	buffer2.push_back(test.at(i));
	flag=false;
      }
    
    }
  }  
  cout << endl << endl;
  return 0;
}

