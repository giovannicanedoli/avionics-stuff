#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

//stateTick(delta: int, pressure: float) -> str

string stateTick(int delta,float pressure);

int main() {
    ifstream file("data.csv");

    if (!file.is_open()) {
        cerr << "Error: Could not open the file" << endl;
        return 1;
    }

    string line;
    vector<pair<string, string>> list;
    
    while (getline(file, line)) {
        stringstream s(line);
        string a, b;

        getline(s, a, ',');
        getline(s, b, ',');
        list.push_back(make_pair(a, b));
    }

    cout << "plot '-' w l\n";

    for (int i = 1; i < list.size(); ++i) {
        //devono essere float
        int current = stof(list[i].second);  
        int previous = stof(list[i - 1].second); 

        if (!(current - previous <= 5000 && current - previous >= -5000)) {
            cout << "Changing from " << list[i].second << " to " << list[i - 1].second << endl;
            list[i].second = list[i - 1].second; 
        }
        cout << list[i].first << " " << list[i].second << endl;

        float val = stof(list[i].second);
        float initial = 81192;

        val = (val - initial)/10;
        //cout << val << endl;
        int p = 0;
        if((int)val == 400){
            cout << "ok" << endl;
            p=1;
            
        }
    }

    cout << "e\n\n";

    // string result;
    // for(int i = 0;i < list.size(); i++){
    //     float val = stof(list[i].second);
    //     result = stateTick(stoi(list[i].first),val);
    //     cout << result << endl;
    // }
    
    file.close();

    return 0;
}

string stateTick(int delta, float pressure){
    if(delta >= 46478 && delta < 252413){
        return "Su rampa";
    }else if(delta >= 252413 && 262424 > delta){
        return "Lancio";
    }else if(delta >= 262424 && 273865 > delta){
        return "Apogeo";
    }else if(delta >= 378262 && 800000 > delta){
        return "A terra";
    }else{
        return "";
    }
    if(delta == 282445){
        return "Paracadute azionato";
    }
}
