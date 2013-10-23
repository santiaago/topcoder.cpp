// Decode.cpp: Santiago Arias
// Description: decode input

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class BinaryCode{
private:
  bool isPValid(int p){
    return ((p == 0) || (p == 1));
  }
  string intToString(int a){
    stringstream ss;
    ss << a;
    return ss.str();
  }
  
  string decodeQ(string Q, int *P){

    string decoded;

    if(Q.length() == 1){
      if(!isPValid((int)Q[0]-48)){
	return "NONE";
      }else{
	int i = (int)Q[0]-48 - P[0];
	if(isPValid(i) && i == ((int)Q[0]-48)){
	  return intToString(i);
	}else{
	  return "NONE";
	}
      }
    }
    P[1] = (int)Q[0]-48 - P[0];
    if(!isPValid(P[1])){
      decoded = "NONE";
    }else{
      
      decoded = intToString(P[0]);
      decoded += intToString(P[1]);

      if(Q.length() > 2){
	for(int i = 1; i < Q.length()-1 ; i++){ 
	  P[i+1] = (int) Q[i]-48 - P[i] - P[i - 1];

	  if (!isPValid(P[i+1])){
	    decoded = "NONE";
	    break;
	  }
	  decoded += intToString(P[i+1]);
	}
	if((((int)Q[Q.length()-1]-48)- P[Q.length()-1] - P[Q.length()-2]) != 0){
	  decoded = "NONE";
	}
      }
    }
    return decoded;
  }
public:
  vector<string> decode(string Q){
  
    // case 1
    // assume P[0] = 0
    int P[50] = {0};
    string left = decodeQ(Q, P);
    // case 2 assume P[0] = 1
    P[0] = 1;
    string right = decodeQ(Q, P);

    vector<string> vDecode;
    vDecode.push_back(left);
    vDecode.push_back(right);
    return vDecode;
  }
};

int main(void){
  
  BinaryCode *bcode = new BinaryCode();
  vector<string> decode;

  cout << endl << "case 0" <<endl;
  decode = bcode->decode("123210122");
  cout << decode[0] << " " << decode[1] << endl;
  cout << boolalpha << (decode[0] == "011100011") << " " << boolalpha << (decode[1] == "NONE") << endl;


  cout << endl << "case 1" <<endl;
  decode = bcode->decode("11");
  cout << decode[0] << " " << decode[1] << endl;
  cout << boolalpha << (decode[0] == "01") << " " << boolalpha << (decode[1] == "10") << endl;

  cout << endl << "case 2" <<endl;
  decode = bcode->decode("22111");
  cout << decode[0] << " " << decode[1] << endl;
  cout << boolalpha << (decode[0] == "NONE") << " " << boolalpha << (decode[1] == "11001") << endl;  

  cout << endl << "case 3" <<endl;
  decode = bcode->decode("123210120");
  cout << decode[0] << " "  << decode[1] << endl;
  cout << boolalpha << (decode[0] == "NONE") << " " << boolalpha << (decode[1] == "NONE") << endl;

  cout << endl << "case 4" <<endl;
  decode = bcode->decode("3");
  cout << decode[0] << " " << decode[1] << endl;
  cout << boolalpha << (decode[0] == "NONE") << " " << boolalpha << (decode[1] == "NONE") << endl;

  cout << endl << "case 5" <<endl;
  decode = bcode->decode("12221112222221112221111111112221111");
  cout << decode[0] << " " << decode[1] << endl;
  cout << boolalpha << (decode[0] == "01101001101101001101001001001101001") << " " << boolalpha << (decode[1] == "10110010110110010110010010010110010") << endl;


  cout << endl << "case 6" <<endl;
  decode = bcode->decode("1");
  cout << decode[0] << " " << decode[1] << endl;
  cout << boolalpha << (decode[0] == "1") << " " << boolalpha << (decode[1] == "NONE") << endl;

  cout << endl << "case 7" <<endl;
  decode = bcode->decode("0");
  cout << decode[0] << " " << decode[1] << endl;
  cout << boolalpha << (decode[0] == "0") << " " << boolalpha << (decode[1] == "NONE") << endl;
            
  delete bcode;
}
