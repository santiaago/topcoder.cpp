// lottery.cpp: Santiago Arias
// Description: Lottery game

#include <iostream>
#include <vector>
#include <algorithm>

#include <math.h>

using namespace std;

class Lottery{
public:
  vector<string> sortByOdds(vector<string> rules);
private:
  double score(int choices, int blank, bool sorted, bool unique);
  double factorial(int n);
  double semi_factorial(int n, int m);
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
    vector< pair<double, string> > lottery_pairs;

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
      lottery_pairs.push_back(make_pair(current_score, rule_name));
    }
    sort(lottery_pairs.begin(), lottery_pairs.end());
    cout << "sorted" << endl;
    for(int i = 0; i < lottery_pairs.size(); ++i){
      cout << lottery_pairs[i].second << " " << lottery_pairs[i].first << endl;
    }
    return rules;

}

double Lottery::score(int choices, int blank, bool sorted, bool unique){
  if(!sorted && !unique){
    return pow(choices, blank);
  } else if(!sorted && unique){
    return semi_factorial(choices, choices - blank + 1);//0;// N * N-1 * N-2 ... * N-M+1
  } else if(sorted && unique){
    return double(semi_factorial(choices, choices - blank + 1 ) ) / factorial(blank); //0;// N * N-1 * N-2 ... * N-M+1/ M!
  } else if( sorted && !unique){
    return score(choices + blank - 1, blank, true, true);
  }
}

double Lottery::factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


double Lottery::semi_factorial(int n, int m)
{
  cout << n << " * ";
  if(n == m){
    return n;
  }
  return (n == 1 || n == 0) ? 1 : semi_factorial(n - 1, m) * n;
}


double semi_factorial(int n, int m)
{
  if(n == m){
    cout << n << " * ";
    return n;
  }
  if(n == 1 || n == 0){
    return 1;
  } else {
    cout << n << " * ";
    return semi_factorial(n - 1, m) * n;
 }
  return (n == 1 || n == 0) ? 1 : semi_factorial(n - 1, m) * n;
}

void test_1(){
  cout << "test_1:" << endl;

  vector<string> rules;
  rules.push_back("PICK ANY TWO: 10 2 F F");
  rules.push_back("PICK TWO IN ORDER: 10 2 T F");
  rules.push_back("PICK TWO DIFFERENT: 10 2 F T");
  rules.push_back("PICK TWO LIMITED: 10 2 T T");
  Lottery *loto = new Lottery();
  loto->sortByOdds(rules);
}


void test_2(){
  cout << "test_2:" << endl;

  vector<string> rules;
  rules.push_back("INDIGO: 93 8 T F");
  rules.push_back( "ORANGE: 29 8 F T");
  rules.push_back( "VIOLET: 76 6 F F");
  rules.push_back( "BLUE: 100 8 T T");
  rules.push_back( "RED: 99 8 T T");
  rules.push_back( "GREEN: 78 6 F T");
  rules.push_back( "YELLOW: 75 6 F F");

  Lottery *loto = new Lottery();
  loto->sortByOdds(rules);
}

int main(){
  // double a = semi_factorial(29,29 -8 + 1);
  // cout << endl;
  // cout << a << endl;
  cout << "Lottery:" << endl;
  test_1();
  test_2();
}
