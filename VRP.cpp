//Schrage.cpp : Ten plik zawiera funkcję „main”.W nim rozpoczyna się i kończy wykonywanie programu.
// Grupa: WT 13: Junak Tadeusz, Karol Kędzia

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

 double tablica[100][100]; // tablica na wczytywane dane
 double permutacja[100]; // tablica pomocnicza
 vector <double> Permutacja; // szukane rozwiązanie
 vector <double> A; // dostępne miasta
 vector <double> kopiaA;
 vector <double> N; // zbiór miast
 void wyswietlPermutacje();

void Greedy(int Rozmiar, int K)
{
    int rozmiar = Rozmiar;

    kopiaA=A = N;    
    
    int k = 1, ine1=0,ine2=0; // nr ciężarówki
    double j = 0, l=99999;
    bool limit = true;
    int x[100]; // xk

    Permutacja.clear();

    while (A.size())
    {   
        int rozmiar2 = rozmiar;
        Permutacja.push_back(tablica[0][0]);

        j = 0,l=99999;

        for (vector<double>::iterator it = A.begin(); it != A.end(); it++)
        {
            if (*it > j)
            {
                j = *it;
                ine1 = it - A.begin();
            }
        }

        cout << "J "<<j << " Ine1 "<< ine1<<endl;

        Permutacja.push_back(j); 

        x[k] = 1; // liczba zleceń obsłużonych przez pojazd k

        A.erase(A.begin()+ine1);

        wyswietlPermutacje();

        A.clear();

        rozmiar2--;

       for (int i = 0; i < rozmiar2; i++)
            A.push_back(tablica[ine1][i]);

        A.erase(A.begin());

        wyswietlPermutacje();

        while (limit==true)
        {
            for (vector<double>::iterator it = A.begin(); it != A.end(); it++)
            {
                if (*it < l)
                {
                    l = *it;               
                    ine2 = it - A.begin();        
                }
            }

            if (x[k] + 1 < rozmiar/K)
            {
                Permutacja.push_back(l); 
                A.erase(A.begin() + ine2); cout << endl << "Rozmiar A" << A.size() << endl;
                x[k]++;
            }
            else
                limit = false;
        }            
        k++; 
    }
}
/*
void symulowaneWyrzazanie() 
{
    
    int T = 100;
    int T0 = T;
    double L;
    double deltaCmax, r;

    // inicjalizacja permutacji

    vector <double> nowaP;


    Permutacja.push_back(tablica[0][0]);

    for (int i = 1; i < L; i++)
    {
        Permutacja.push_back(tablica[0][i]);
    }

    L = Permutacja.size();

    Permutacja.push_back(tablica[0][0]);

    int i, j;

    while (T0 > 0)
    {
        for (int k = 1; k < L; k++)
        {
            i = Randint(1, L);
            j = Randint(1, L);

            swap();

            oldCmax = obliczPermutacje();
            newCmax = obliczPermutacje();

            deltaCmax = oldCmax - newCmax;

            if (deltaCmax <= 0)
            {
                r = Rand01();
                if (r >= exp(deltaCmax/T0))
                {
                    Permutacja = newP;
                }
            }

            Permutacja = nowaP;

            if (newCmax < )
            {
                result = Permutacja;
                resultRoute = newCmax;
            }
        }
        T0--;
    }

}

*/

 void wyswietlPermutacje() 
 {

     cout << endl << "Wyswietlenie permutacji: ";

     for (std::vector<double>::iterator it = Permutacja.begin(); it != Permutacja.end(); ++it)
         cout << ' ' << *it;
     cout << endl << "Wyswietlenie permutacji: A ";

     for (std::vector<double>::iterator it = A.begin(); it != A.end(); ++it)
         cout << ' ' << *it;

 }

 void wstawPermutacje()
 {
     Permutacja.push_back(tablica[4][1]);
     Permutacja.push_back(tablica[1][0]);
     Permutacja.push_back(tablica[0][2]);
     Permutacja.push_back(tablica[2][4]);
     Permutacja.push_back(tablica[4][3]);
     Permutacja.push_back(tablica[3][4]);
 }

 double obliczPermutacje()
 {
     double suma=0;

     for (std::vector<double>::iterator it = Permutacja.begin(); it != Permutacja.end(); ++it)
         suma += *it;

         return suma;
 }

int main()
{
    fstream plik;
    plik.open("PL.csv", ios::in);
    string jednostka;
    int rozmiar = 0;
    int d = 0;
    double sumaP = 0;

    plik >> rozmiar;

    plik >> jednostka;

    cout << "Liczba miast (baza + miasta do odwiedzenia): " << rozmiar << " Jednostka: " << jednostka << endl << endl;

    for (int i = 0; i < rozmiar; i++)
    {
        for(int j=0;j<rozmiar;j++)
        {
            plik >> tablica[i][j];
            cout << tablica[i][j]<< " ";
        }
        cout << endl;
    }

    cout << endl << "Wczytano miasta" << endl;

    // wstawienie losowej permutacji

    //wstawPermutacje();

    //wyswietlPermutacje();

    //sumaP = obliczPermutacje();

    //cout << endl << "Suma wszystkich tras wynosi: " << sumaP << jednostka << endl;

    for (int i = 0; i < rozmiar; i++)
        N.push_back(tablica[0][i]);

    Greedy(rozmiar,10);

    wyswietlPermutacje();

    system("PAUSE");

    return 0;
}
