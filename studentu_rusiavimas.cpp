#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

// Struktūra, skirta studento duomenims saugoti.
struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;
};

// Funkcijų prototipai
double skaiciuotiVidurki(const vector<int>& nd);
double skaiciuotiMediana(vector<int> nd);
double skaiciuotiGalutini(double vidurkisArMediana, int egzaminas);
void ivestiDuomenis(vector<Studentas>& studentai);
void generuotiDuomenis(vector<Studentas>& studentai);
void nuskaitytiIsFailo(vector<Studentas>& studentai, const string& failoVardas);
void spausdintiRezultatus(const vector<Studentas>& studentai);

// Pagrindinė programos funkcija, valdanti meniu ir vartotojo pasirinkimus.
int main() {
    vector<Studentas> studentai;
    char pasirinkimas;

    // Pagrindinis meniu ciklas, kuris veikia tol, kol vartotojas nepasirenka '4'
    do {
        cout << "\n--- Meniu ---\n"
             << "1. Ivesti duomenis ranka\n"
             << "2. Generuoti duomenis atsitiktinai\n"
             << "3. Nuskaityti duomenis is failo 'kursiokai.txt'\n"
             << "4. Baigti darba\n"
             << "Jusu pasirinkimas: ";
        cin >> pasirinkimas;

        // Patikrinimas, ar įvestis nebuvo klaidinga (pvz., ne skaičius)
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pasirinkimas = '0';
        }

        switch (pasirinkimas) {
            case '1':
                ivestiDuomenis(studentai);
                break;
            case '2':
                generuotiDuomenis(studentai);
                break;
            case '3':
                nuskaitytiIsFailo(studentai, "kursiokai.txt");
                break;
            case '4':
                cout << "Programa baigia darba.\n";
                break;
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
                continue; 
        }

        if (pasirinkimas == '1' || pasirinkimas == '2' || pasirinkimas == '3') {
            if (!studentai.empty()) {
                spausdintiRezultatus(studentai);
            }
            studentai.clear();
        }

    } while (pasirinkimas != '4');

    return 0;
}

// Apskaičiuoja namų darbų pažymių vidurkį.
double skaiciuotiVidurki(const vector<int>& nd) {
    if (nd.empty()) return 0.0;
    return accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
}

// Apskaičiuoja namų darbų pažymių medianą.
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

// Apskaičiuoja galutinį balą pagal formulę: 0.4 * vidurkis/mediana + 0.6 * egzaminas.
double skaiciuotiGalutini(double vidurkisArMediana, int egzaminas) {
    return 0.4 * vidurkisArMediana + 0.6 * egzaminas;
}

// Nuskaito studentų duomenis iš failo.
void nuskaitytiIsFailo(vector<Studentas>& studentai, const string& failoVardas) {
    ifstream failas(failoVardas);
    if (!failas) {
        cerr << "Klaida: Nepavyko atidaryti failo '" << failoVardas << "'\n";
        return;
    }

    string eilute;
    getline(failas, eilute);

    while (getline(failas, eilute)) {
        stringstream ss(eilute);
        Studentas temp;
        int pazymys;
        
        ss >> temp.pavarde >> temp.vardas;

        vector<int> pazymiai;
        while(ss >> pazymys) {
            pazymiai.push_back(pazymys);
        }

        if (!pazymiai.empty()) {
            temp.egzaminas = pazymiai.back();
            pazymiai.pop_back();
            temp.nd = pazymiai;
        } else {
            temp.egzaminas = 0;
        }

        temp.galutinisVid = skaiciuotiGalutini(skaiciuotiVidurki(temp.nd), temp.egzaminas);
        temp.galutinisMed = skaiciuotiGalutini(skaiciuotiMediana(temp.nd), temp.egzaminas);

        studentai.push_back(temp);
    }
    failas.close();
    cout << "Duomenys is failo '" << failoVardas << "' nuskaityti sekmingai.\n";
}

// Leidžia vartotojui rankiniu būdu įvesti studentų duomenis.
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

// Sugeneruoja nurodytą kiekį studentų su atsitiktiniais duomenimis.
void generuotiDuomenis(vector<Studentas>& studentai) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> pazymiuDist(1, 10);
    uniform_int_distribution<> ndSkaiciausDist(1, 15);

    int studentuSk;
    cout << "Kiek studentu sugeneruoti? ";
    cin >> studentuSk;

    for (int i = 1; i <= studentuSk; ++i) {
        Studentas temp;
        temp.vardas = "Vardas" + to_string(i);
        temp.pavarde = "Pavarde" + to_string(i);

        int ndSkaicius = ndSkaiciausDist(gen);
        for (int j = 0; j < ndSkaicius; ++j) {
            temp.nd.push_back(pazymiuDist(gen));
        }

        temp.egzaminas = pazymiuDist(gen);

        temp.galutinisVid = skaiciuotiGalutini(skaiciuotiVidurki(temp.nd), temp.egzaminas);
        temp.galutinisMed = skaiciuotiGalutini(skaiciuotiMediana(temp.nd), temp.egzaminas);
        
        studentai.push_back(temp);
    }
    cout << studentuSk << " studentu duomenys sugeneruoti.\n";
}

// Išspausdina studentų galutinius rezultatus surikiuotus pagal vardą.
void spausdintiRezultatus(const vector<Studentas>& studentai) {
    if (studentai.empty()) {
        cout << "Studentu sarasas tuscias.\n";
        return;
    }

    vector<Studentas> surikiuotiStudentai = studentai;

    sort(surikiuotiStudentai.begin(), surikiuotiStudentai.end(), 
        [](const Studentas& a, const Studentas& b) {
            if (a.vardas != b.vardas) {
                return a.vardas < b.vardas;
            }
            return a.pavarde < b.pavarde;
        });


    size_t maxVardasPlotis = 6;
    size_t maxPavardePlotis = 7;
    for (const auto& s : surikiuotiStudentai) {
        if (s.vardas.length() > maxVardasPlotis) {
            maxVardasPlotis = s.vardas.length();
        }
        if (s.pavarde.length() > maxPavardePlotis) {
            maxPavardePlotis = s.pavarde.length();
        }
    }

    cout << "\n" << left 
         << setw(maxPavardePlotis + 2) << "Pavarde"
         << setw(maxVardasPlotis + 2) << "Vardas"
         << setw(20) << "Galutinis (Vid.)"
         << setw(20) << "Galutinis (Med.)\n";

    cout << string(maxPavardePlotis + maxVardasPlotis + 4 + 40, '-') << "\n";

    for (const auto& s : surikiuotiStudentai) {
        cout << left
             << setw(maxPavardePlotis + 2) << s.pavarde
             << setw(maxVardasPlotis + 2) << s.vardas
             << fixed << setprecision(2)
             << setw(20) << s.galutinisVid 
             << setw(20) << s.galutinisMed << "\n";
    }
}