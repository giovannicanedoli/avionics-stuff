#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

//tutte le variabili relative a quota, tempo e spazio sono gestite in O(1)

string stateTick(int delta,float pressure);

int main() {
    ifstream file("data.csv");

    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }

    ofstream writeFile("output.csv");
    
    if(!writeFile){
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }

    writeFile << "state,time,pression" << endl;

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
            list[i].second = list[i - 1].second; 
        }

        

        cout << list[i].first << " " << list[i].second << endl;


        //paracadute
        float pression = stof(list[i].second);
        float initial = 81192;
        //calcolo la quota (considero g = 10 e la densità dell'aria 1)
        int quota = (pression - initial)/10;
        if(quota == 400){
            cout << "secondo paracadute" << endl;
        }

        string state = stateTick(stoi(list[i].first), stof(list[i].second));

        writeFile << state << "," << pression << "," << list[i].first << endl;  


    }

    cout << "e\n\n";

    
    file.close();
    writeFile.close();

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
        //non è specificato il nome dell'evento in questo caso
        return "";
    }
    if(delta == 268159){
        return "Paracadute azionato";
    }
}
