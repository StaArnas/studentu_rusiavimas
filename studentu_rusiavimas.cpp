#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;
};

double skaiciuotiVidurki(const vector<int>& nd);
double skaiciuotiMediana(vector<int> nd);
double skaiciuotiGalutini(double vidurkisArMediana, int egzaminas);
void ivestiDuomenis(vector<Studentas>& studentai);
void spausdintiRezultatus(const vector<Studentas>& studentai);

int main() {
    vector<Studentas> studentai;
    char pasirinkimas;

    do {
        cout << "\n--- Meniu ---\n"
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
                ivestiDuomenis(studentai);
                spausdintiRezultatus(studentai); 
                studentai.clear();
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

double skaiciuotiVidurki(const vector<int>& nd) {
    if (nd.empty()) return 0.0;
    // std::accumulate susumuoja visus vektoriaus elementus
    return accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
}

double skaiciuotiMediana(vector<int> nd) {
    if (nd.empty()) return 0.0;
    sort(nd.begin(), nd.end());
    size_t dydis = nd.size();
    if (dydis % 2 == 0) {
        return (nd[dydis / 2 - 1] + nd[dydis / 2]) / 2.0;
    } else {
        return nd[dydis / 2];
    }
}

double skaiciuotiGalutini(double vidurkisArMediana, int egzaminas) {
    return 0.4 * vidurkisArMediana + 0.6 * egzaminas;
}

void ivestiDuomenis(vector<Studentas>& studentai) {
    char testi = 't';
    while (testi == 't' || testi == 'T') {

        Studentas temp;
        cout << "Iveskite studento varda: ";
        cin >> temp.vardas;
        cout << "Iveskite studento pavarde: ";
        cin >> temp.pavarde;

        cout << "Iveskite namu darbu pazymius (baigti ivedus ne skaiciu): ";
        int pazymys;
        while (cin >> pazymys) {
            if (pazymys >= 1 && pazymys <= 10) {
                temp.nd.push_back(pazymys);
            } else {
                cout << "Pazymys turi buti intervale [1, 10]. Bandykite dar karta.\n";
            }
        }
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Iveskite egzamino rezultata: ";
        while (!(cin >> temp.egzaminas) || temp.egzaminas < 1 || temp.egzaminas > 10) {
            cout << "Neteisinga ivestis. Egzamino rezultatas turi buti skaicius intervale [1, 10]: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        temp.galutinisVid = skaiciuotiGalutini(skaiciuotiVidurki(temp.nd), temp.egzaminas);
        temp.galutinisMed = skaiciuotiGalutini(skaiciuotiMediana(temp.nd), temp.egzaminas);

        studentai.push_back(temp);

        cout << "Ar norite ivesti dar viena studenta? (t/n): ";
        cin >> testi;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    } 
}

void spausdintiRezultatus(const vector<Studentas>& studentai) {
    if (studentai.empty()) {
        cout << "Studentu sarasas tuscias." << endl;
        return;
    }

    cout << "\n--- Studentu Rezultatai ---\n";
    cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << endl;
    cout << "------------------------------" << endl;

    for (const auto& s : studentai) {
        cout << left << setw(15) << s.pavarde << setw(15) << s.vardas << endl;
    }
}