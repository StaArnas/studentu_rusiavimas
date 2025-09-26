#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <limits>


using namespace std;

struct Studentas {

    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;

};

int main(){

    vector<Studentas> studentai;
    char pasirinkimas;

    do {

        cout << "\n --- Meniu ---\n"
             << "1. Ivesti duomenis ranka\n"
             << "2. Baigti darba\n"
             << "Jusu pasirinkimas: ";
        cin >> pasirinkimas;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pasirinkimas = '0';
        }

        switch (pasirinkimas) {
            case '1':
                cout << "Sekmingai pasirinktas skaicius 1.";
                break;
            case '2':
                cout << "Programa baigia darba.\n";
                break;
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
                break;
        }

    } while (pasirinkimas != '2');

    return 0;

}