// lottery.cpp: Santiago Arias
// Description: Lottery game

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Lottery{
public:
  vector<string> sortByOdds(vector<string> rules);
private:
  double score(int choices, int blank, bool sorted, bool unique);
  int factorial(int n);
  int semi_factorial(int n, int m);
};

vector<string> Lottery::sortByOdds(vector<string> rules){
    int colon;
    
    string rule_name;
    int choices;
    int blank;
    double current_score;
    string rest;
    bool sorted;
    bool unique;
    for(int i = 0; i < rules.size(); ++i){

      cout << rules[i] << endl;
      // name
      colon = rules[i].find(':');
      rule_name = rules[i].substr(0, colon);
      // choices
      rest = rules[i].substr(colon + 2, string::npos);
      choices = atoi(rest.substr(0, rest.find(' ')).c_str());;
      // blank
      rest = rest.substr( rest.find(' ') + 1, string::npos);
      blank = atoi(rest.substr(0, rest.find(' ')).c_str());

      rest = rest.substr( rest.find(' ') + 1, string::npos);
      // sorted and unique
      sorted = (rest[0] == 'T')? true: false;
      unique = (rest[2] == 'T')? true: false;
      current_score = score(choices, blank, sorted, unique);
      cout << "Current score: " << current_score << endl;
    }
    return rules;

}

double Lottery::score(int choices, int blank, bool sorted, bool unique){
  if(!sorted && !unique){
    return double(1)/pow(choices, blank);
  } else if(!sorted && unique){
    return double(1)/semi_factorial(choices, choices - blank + 1);//0;// N * N-1 * N-2 ... * N-M+1
  } else if(sorted && unique){
    return double(1)/(double(semi_factorial(choices, choices - blank + 1 ) ) / factorial(blank)); //0;// N * N-1 * N-2 ... * N-M+1/ M!
  } else if( sorted && !unique){
    return score(choices + blank - 1, blank, true, true);
  }
}

int Lottery::factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


int Lottery::semi_factorial(int n, int m)
{
  
  if(n == m){
    return n;
  }
  return (n == 1 || n == 0) ? 1 : semi_factorial(n - 1, m) * n;
}


int main(){
  cout << "Lottery:" << endl;
  vector<string> rules;
  rules.push_back("PICK ANY TWO: 10 2 F F");
  rules.push_back("PICK TWO IN ORDER: 10 2 T F");
  rules.push_back("PICK TWO DIFFERENT: 10 2 F T");
  rules.push_back("PICK TWO LIMITED: 10 2 T T");
  Lottery *loto = new Lottery();
  loto->sortByOdds(rules);
}
