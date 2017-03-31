#include "server.h"
#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace  std;

Server::Server(string _procolName): procolName(_procolName), sockD(0), errorFlag(0)
{

}

string Server::getProcolName() const
{
    return procolName;
}

void Server::setError(const string &errMesg){
    errorFlag = true;
    cout << "Error: " << errMesg << endl;
}

void Server::processingMsg(const string& msg){
    vector <string> digits;
    digits.resize(10);
    int sum = 0;
    bool hasDig = 0;
    for( auto c : msg  ){
       if(isdigit(c)){
           int oneDigit = stoi(&c);
           digits[oneDigit] += c;
           sum += oneDigit;
           hasDig = true;
       }
    }
    if(hasDig){
        string sortedDigits;
        cout << "Desc sorted msg only with numbers: ";
        for(auto it = digits.rbegin(); it != digits.rend(); it++){
            cout << *it;
            sortedDigits += *it;
        }
        cout << endl;
        cout << "Max value: " << sortedDigits.at(0) << endl;
        cout << "Min value: " << sortedDigits.at(sortedDigits.length()-1) << endl;
        cout << "Sum of numbers: " << sum << endl << endl;
    }else{
        cout << "There are no numbers in message. \n";
    }

//    char processedMsg [msg.length()+1];
//    memset(processedMsg, 0, msg.size()+1);
//    remove_copy_if(msg.begin(), msg.end(), processedMsg , [](char c){
//        return !isdigit(c);
//    });

//    string processedMsgStr(processedMsg);
//    sort(processedMsgStr.begin(), processedMsgStr.end(), greater<char>());
//    if(!processedMsgStr.empty()){
//        cout << "Desc sorted msg only with numbers: " << processedMsgStr << endl;
//        cout << "Max value: " << processedMsgStr.at(0) << endl;
//        cout << "Min value: " << processedMsgStr.at(processedMsgStr.length()-1) << endl;
//        int sum = 0;
//        for( auto c :processedMsgStr  ){
//            sum += stoi(&c);
//        }
//        cout << "Sum of numbers: " << sum << endl << endl;
//    }else{
//        cout << "There are no numbers in message. \n";
//    }
}
