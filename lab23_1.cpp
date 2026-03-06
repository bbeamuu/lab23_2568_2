#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include <cctype>
#include <sstream>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

string trim(string s){
    while(!s.empty() && isspace(s.front())) s.erase(0,1);
    while(!s.empty() && isspace(s.back())) s.pop_back();
    return s;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream file(filename);
    string line;

    while(getline(file,line)){
        string name;
        int s1,s2,s3;

        size_t pos = line.find(':');
        name = line.substr(0,pos);

        string scorePart = line.substr(pos+1);
        stringstream ss(scorePart);

        ss >> s1 >> s2 >> s3;

        int total = s1 + s2 + s3;

        names.push_back(name);
        scores.push_back(total);
        grades.push_back(score2grade(total));
    }
}

void getCommand(string& command, string& key){
    cout << "Please input your command:\n";
    string input;

    getline(cin,input);

    stringstream ss(input);
    ss >> command;
    getline(ss,key);

    if(key.size()>0 && key[0]==' ') key.erase(0,1);
}


void searchName(const vector<string>& names,
                const vector<int>& scores,
                const vector<char>& grades,
                const string& key)
{
    for(size_t i = 0; i < names.size(); i++){

        if(toUpperStr(names[i]) == key){

            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            return;
        }
    }

    cout << "---------------------------------\n";
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string>& names,
                 const vector<int>& scores,
                 const vector<char>& grades,
                 const string& key)
{
    bool found = false;

    cout << "---------------------------------\n";

    for(size_t i = 0; i < grades.size(); i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }

    if(!found){
        cout << "Cannot found.\n";
    }

    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}