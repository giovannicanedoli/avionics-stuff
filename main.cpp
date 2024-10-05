#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

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

    for (int i = 1; i < list.size(); ++i) {
        int current = stoi(list[i].second);  
        int previous = stoi(list[i - 1].second); 

        if (!(current - previous <= 5000 && current - previous >= -5000)) {
            cout << "Changing from " << list[i].second << " to " << list[i - 1].second << endl;
            list[i].second = list[i - 1].second; 
        }
        
        cout << list[i].first << " " << list[i].second << endl;
    }
    
    file.close();

    return 0;
}
