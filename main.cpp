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
    //leggo il file in input
    ifstream file("data.csv");

    //check di errori
    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }

    //per scrivere in output
    ofstream writeFile("output.csv");
    
    //check di errori
    if(!writeFile){
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }

    //scrivo l'header del file csv di output
    writeFile << "state,pression,time" << endl;

    string line;
    vector<pair<string, string>> list;
    
    //analizzo il file di input e scrivo i dati dentro a list
    while (getline(file, line)) {
        stringstream s(line);
        string a, b;

        getline(s, a, ',');
        getline(s, b, ',');
        list.push_back(make_pair(a, b));
    }

    //scrivo in stdout questa riga per far funzionare gnuplot
    cout << "plot '-' w l\n";
    for (int i = 1; i < list.size(); ++i) {
        //analizzo i dati di list, se non sono in un range di ± 5KPa correggo il punto
        //andando a scrivere nel valore successivo quello precendente (così evito errori di plot nel grafico)
        int current = stof(list[i].second);  
        int previous = stof(list[i - 1].second); 

        if (!(current - previous <= 5000 && current - previous >= -5000)) {
            list[i].second = list[i - 1].second; 
        }

        
        //scrivo in output per far funzionare gnuplot
        cout << list[i].first << " " << list[i].second << endl;


        //paracadute
        float pression = stof(list[i].second);
        float initial = 81192;
        //calcolo la quota (considero g = 10 e la densità dell'aria 1)
        //utilizzo la legge di stevino
        int quota = (pression - initial)/10;
        if(quota == 400){
            cout << "secondo paracadute" << endl;
        }

        string state = stateTick(stoi(list[i].first), stof(list[i].second));
        //scrivo su file
        writeFile << state << "," << pression << "," << list[i].first << endl;  
    }
    //comunico a gnuplot che ho finito di dare dati
    cout << "e\n\n";

    //chiudo
    file.close();
    writeFile.close();

    return 0;
}

string stateTick(int delta, float pressure){
    //differenzio gli stati in base all'intervallo temporale, in base alle specifiche date
    //si ha un calo di pressione negli intervalli temporali considerati. I valori sono scelti di
    //conseguenza.
    if(delta >= 46478 && delta < 252413){
        return "Su rampa";
    }else if(delta >= 252413 && 262424 > delta){
        return "Lancio";
    }else if(delta >= 262424 && 273865 > delta){
        //all'apogeo aziono il paracadute
        if(delta == 268159){
            cout << "Paracadute azionato" << endl;
        }
        return "Apogeo";
    }else if(delta >= 378262 && 800000 > delta){
        return "A terra";
    }else{
        //non è specificato il nome dell'evento in questo caso
        return "";
    }
    
}
