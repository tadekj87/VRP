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
 vector <double> AA; // kopia z drugiego while
 vector <double> N; // zbiór miast
 vector <int> pomoc;

 int tablicaSW[100], tablicaNEW[100];
 void wyswietlPermutacje();

void Greedy(int Rozmiar, int K, int baza)
{
    int rozmiar = Rozmiar;

    A = N;    
    
    int k = 1, ine1=0,ine2=0; // nr ciężarówki
    double j = 0, l=99999;
    bool limit = true;
    int x[100]; // xk

    Permutacja.clear();
    int rozmiar2 = rozmiar;
A.erase(A.begin() + baza);
       pomoc.push_back(baza);
    while (A.size())
    {   // jesteśmy w pierwszym wierszu
        cout << endl << "poczatek duzego while" << endl;
        
        Permutacja.push_back(tablica[baza][baza]);

        j = 0,l=99999;
        
        for (vector<double>::iterator it = A.begin(); it != A.end(); it++)
        {
            if (*it > j)
            {
                j = *it;
                ine1 = it - A.begin();
            }
        }

        cout << endl <<"J "<<j << " Max(pozycja) "<< ine1<<endl;

        Permutacja.push_back(j); 

        x[k] = 1; // liczba zleceń obsłużonych przez pojazd k


        A.erase(A.begin()+ine1);


        AA.clear();

       for (int i = 0; i < rozmiar; i++)
            AA.push_back(tablica[ine1][i]);
  wyswietlPermutacje(); 

       pomoc.push_back(ine1);

       cout << endl << "Pomoc baza " << pomoc[0] << " Pomoc ine1 " << pomoc[1] << endl;

       for (vector<int>::iterator it = pomoc.begin(); it != pomoc.end(); it++) {
           AA.erase(AA.begin() + *it);
           cout << endl << "*it " << *it << endl;
       }

        while (limit==true)
        {
            cout << endl << "maly while" << endl;
            wyswietlPermutacje();
            for (vector<double>::iterator it = AA.begin(); it != AA.end(); it++)
            {
                if (*it < l && *it>0 && *it!=j)
                {
                    l = *it;               
                    ine2 = it - AA.begin();    // pozycja najmniejszego elementu w kolejnym wierszu    
                }
            }

            if (x[k] + 1 < rozmiar/K)
            {
                pomoc.push_back(ine2);
                cout << endl << "1" << endl;
                Permutacja.push_back(l); 
                cout << endl << "2" << endl;
                AA.erase(AA.begin() + ine2);
                cout << endl << "3" << endl;
                A.erase(A.begin()+ine2);
                cout << endl << "4" << endl;
                x[k]++;
                l = 9999;
            }
            else
                limit = false;
        }         
        limit = true;
        k++; 
    }
}

double obliczPermutacje(int rozmiar,int tablicaOblicz[])
{
    double suma=0;

        for (int i = 0; i < rozmiar-1; i++)
        {
            suma+=tablica[tablicaOblicz[i]][tablicaOblicz[i+1]];
            
        }cout << endl << "dodawanie: " << suma << endl;
        return suma;
}

double symulowaneWyrzazanie(int rozmiar) 
{
    
    int T = 100;
    int T0 = T;
    double L=sqrt(rozmiar);
    double deltaCmax, oldCmax,newCmax, r;
    double wynik=0;


    // inicjalizacja permutacji

    for (int i = 0; i < rozmiar; i++)
    {
        tablicaSW[i] = i;
    }

    int i, j;

    while (T0 > 0)
    {
        for (int k = 1; k < 2; k++)
        {
            i = 1 + rand()%(rozmiar-1);
            j = 1 + rand() % (rozmiar - 1);

            // swap
            int pomoc = 0;


            for (int t = 0; t < rozmiar; t++)
                if (t != i)
                    tablicaNEW[t] = tablicaSW[t];
                else if (t == i)
                    tablicaNEW[t] = tablicaSW[j];
                else if (t == j)
                    tablicaNEW[t] = tablicaSW[i];
            

            oldCmax = obliczPermutacje(rozmiar,tablicaSW);
            newCmax = obliczPermutacje(rozmiar,tablicaNEW);

            deltaCmax = oldCmax - newCmax;

            if (deltaCmax <= 0)
            {
                r = (double)rand()/RAND_MAX;
                if (r >= exp(deltaCmax/T0))
                {
                    for (int z = 0; z < rozmiar; z++)
                    {
                        tablicaNEW[z] = tablicaSW[z];
                    }
                    wynik = oldCmax;
                }
            }

            for (int z = 0; z < rozmiar; z++)
            {
                tablicaSW[z] = tablicaNEW[z];
            }
            wynik = oldCmax;

            if (deltaCmax > 0)
            {
                for (int z = 0; z < rozmiar; z++)
                {
                    tablicaNEW[z] = tablicaSW[z];
                }
                wynik = oldCmax;
            }
        }
        T0--;
    }
    return wynik;

}



 void wyswietlPermutacje() 
 {

     cout << endl << "Wyswietlenie permutacji: ";

     for (std::vector<double>::iterator it = Permutacja.begin(); it != Permutacja.end(); ++it)
         cout << ' ' << *it;
     cout << endl << "Wyswietlenie permutacji: A ";

     for (std::vector<double>::iterator it = A.begin(); it != A.end(); ++it)
         cout << ' ' << *it;
     cout << endl << "Wyswietlenie permutacji: AA ";

     for (std::vector<double>::iterator it = AA.begin(); it != AA.end(); ++it)
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

    //for (int i = 0; i < rozmiar; i++)
      //  N.push_back(tablica[0][i]);

    //Greedy(rozmiar,1,0);

    //wyswietlPermutacje();

    double wynikWyrzazania = 0;
    wynikWyrzazania = symulowaneWyrzazanie(rozmiar);

    cout << endl << "Wynik wyrzazania to: " << wynikWyrzazania << " "<< jednostka<< endl;

    system("PAUSE");

    return 0;
}
