#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <ctime>




using namespace std;

class Product{
public:
    string      name;       //Nazwa produktu
    string      type;         //Pora dnia o której się je(śniadanie, launch, obiad, kolacja)
    int         cal;        //Ilość kalorii produktu

    Product(string Kname, int Kcal, string Kpr)
    {
        Product::name = Kname;
        Product::cal = Kcal;
        Product::type = Kpr;
    }
};
class Cwiczenie {

    public:
    string nazwa;
    string typ; //na jaki miesien


    int powtorzenia; // powtorzenia lub czas w sekundach
    bool czas;


   void show(int intens){
        if(czas) {
                if (powtorzenia<240){
                cout << nazwa <<'\n' << " ("<< "serie: "<<intens<<", " << "seria: " <<powtorzenia <<" sekund)"<< '\n' << '\n';
                }
                else cout << nazwa << " ("<<(powtorzenia*intens)/60 <<" minut)"<< '\n'<< '\n';
        }

        else cout << nazwa <<" ("<< "serie: "<<intens<<", " << "seria: " <<powtorzenia <<" powtorzen)"<< '\n'<< '\n';


    }
};

//DEFINICJE FUNCKJI

void exc (vector <Cwiczenie> wektor, int ile_dni, int intens );
void diet (int ile_dni, float kalorie, vector<Product> produkty);
void all (vector <Cwiczenie> wektor, int ile_dni, int intens, float kalorie, vector<Product> produkty);
vector<Product> diet_single (float kalorie, vector <Product> dish);

vector<Cwiczenie> oblicz_cw(string typ)
{   string linia;
    vector<Cwiczenie> v;
    fstream plik;
    int nr=5;
    int nr_obiektu=-1; //na poczatku petli jest inkrementowany


    plik.open("cwiczenia.txt",ios::in) ;
    if (plik.good()==false)
        {cout << "Nie znaleziono pliku z danymi, sprawdz scieszczke i uruchom program ponownie"; exit(0); }

//petla pobierajaca tekst
     while (getline(plik, linia))
    {

        if (nr>4) {
                nr=1;
                v.push_back(Cwiczenie());
                nr_obiektu++;
        }
        switch (nr){

            case 1:  v[nr_obiektu].nazwa = linia; break;
            case 2:v[nr_obiektu].typ = linia; break;
            case 3:v[nr_obiektu].powtorzenia = atoi(linia.c_str()); break;
            case 4: {if (linia=="nie") {v[nr_obiektu].czas=false;}
                    else v[nr_obiektu].czas=true;
                     break;
                }
        }
       nr ++;

    }
    plik.close();


    vector<Cwiczenie> wybrane;


        //wpisywanie do vectora tylko tych, ktore spelniaja warunki
    int nrWybrany=0;
        for (int i=0; i<v.size(); i++)
        {
            if (v[i].typ == typ)
            {
                wybrane.push_back(Cwiczenie());
                wybrane[nrWybrany]=v[i];
                nrWybrany++;
            }
        }

 random_shuffle(wybrane.begin(), wybrane.end()); //polosowanie kolejnosci

return wybrane;
}

vector<Product> oblicz_dieta(){
    ifstream dietData;
    vector<Product> produkt;
    dietData.open("dania.txt");
    if (dietData.fail())
    {
        cout << "Err"; exit(0);
    }
    else
    {
        string tmp, nameS, calS;
        int mode = 1;
        while (getline(dietData, tmp))
        {
            //cout << tmp << endl;
            switch (mode)
            {
            case 1:
                nameS = tmp;
                mode++;
                break;
            case 2:
                calS = tmp;
                mode++;
                break;
            case 3:
                switch (tmp[0])
                {
                case 'b':
                    produkt.push_back(Product(nameS, atoi(calS.c_str()), "Breakfast"));
                    break;
                case 'l':
                    produkt.push_back(Product(nameS, atoi(calS.c_str()), "Lunch"));
                    break;
                case 'd':
                    produkt.push_back(Product(nameS, atoi(calS.c_str()), "Dinner"));
                    break;
                case 's':
                    produkt.push_back(Product(nameS, atoi(calS.c_str()), "Supper"));
                    break;
                }
                mode = 1;
                break;
            }
        }
    }


return produkt;

}





int main()
{
srand(time(NULL));

    setlocale(LC_ALL, "");

    int ile_dni;

    string typ;

    float wiek;
    float waga;
    float wzrost;
    float bmi;
    float ppm;  //podstawowa przemiana materii
    int zmianawagi;

    cout << "\nWitaj w programie, ktory pomoze ci dbac o zdrowie w domu!\n";

    cout << "Dostepne opcje to cwiczenia i dieta\n";
    cout << "Menu nawiguje sie poprzez klawisze strzalki w gore i w dol, i enter" << '\n';

    cout << "\nAby kontynuowac nacisnij klawisz\n";

    getch();
    system("cls");
//wiek

    do {

        cout << "\nPodaj wiek:\n";
        cin >> wiek;

        if(!wiek) //sprawdzanie czy wiek jest poprawnie podany
        {
        cout <<"Podaj dane w liczbach\n";
        cin.clear();
        cin.sync();
        }

    }
    while( 120 < wiek || wiek < 1 );

//waga

    do {

        cout << "Podaj wage w kg:\n";
        cin >> waga;

            if(!waga)

            {
            cout <<"Podaj dane w liczbach\n";
            cin.clear();
            cin.sync();
            }

    }
    while( 600 < waga || waga < 1 );

//wzrost

    do {

        cout << "Podaj wzrost w cm:\n";
        cin >> wzrost;

            if(!wzrost)

            {
            cout <<"Podaj dane w liczbach\n";
            cin.clear();
            cin.sync();
            }

    }
    while( 250 < wzrost || wzrost < 1 );

//plec

    int wybranaopcja = 0;
    char opcja;

    do {
        system( "cls" );

        if( wybranaopcja == 0 ) cout << "--> Mezczyzna\n";
            else cout << "Mezczyzna\n";

        if( wybranaopcja == 1 ) cout << "--> Kobieta\n";
            else cout << "Kobieta\n";

        opcja = getch();

        switch( opcja )
        {
        case 72: // strzalka w dol(ASCII)
            wybranaopcja--;
            break;
        case 80: //strzalka w gore  (ASCII)
            wybranaopcja++;
            break;
        }

        if( wybranaopcja < 0 ) wybranaopcja++ ;
        if( wybranaopcja > 1 ) wybranaopcja-- ;

    }
    while( opcja != 13 );

//ppm

        if( wybranaopcja == 0 && opcja == 13 )
        {
            cout << "\nWybrano mezczyzna\n";

            ppm = 66.47 + (13.75 * waga) + (5 * wzrost) - (6.75 * wiek);

            cout << "Twoje podstawowe zapotrzebowanie kaloryczne wynosi:\n" << "\n" << ppm << "kcal\n";
            cout << "\nJest to ilosc energii potrzebna na samo podtrzymanie funkcji zyciowych bez wykonywania jakichkolwiek czynnosci.\n";
            cout << "Ilosc kalorii ktore spozywasz nie powinna byc nizsza.\n";
        }

        else if( wybranaopcja == 1 && opcja == 13 )
        {
            cout << "\nWybrano kobieta\n";

            ppm = 665.09 + (9.56 * waga) + (1.85 * wzrost) - (4.67 * wiek);

            cout << "Twoje podstawowe zapotrzebowanie kaloryczne wynosi:\n" << "\n" << ppm << "kcal\n";
            cout << "\nJest to ilosc energii potrzebna na samo podtrzymanie funkcji zyciowych bez wykonywania jakichkolwiek czynnosci\n";
            cout << "Ilosc kalorii ktore spozywasz nie powinna byc nizsza.\n";
        }

//bmi

    bmi = (waga/((wzrost*0.01)*(wzrost*0.01)));

    cout << "\nTwoje BMI wynosi:\n" << bmi << "\n";


        if(25 > bmi && bmi >= 18.5)
        {
            cout << "\nTwoje BMI jest poprawne.\n";
            cout << "Utrzymaj obecna wage.\n";
        }

        else if(16 <= bmi && bmi < 18.5)
        {
            cout << "\nTwoje BMI jest za niskie.\n";
            cout << "Sproboj utrzymac prawidlowa diete.\n";
        }

        else if(bmi < 16)
        {
            cout << "\nTwoje BMI wskazuje na wyglodzenie.\n";
            cout << "Skontaktuj sie z lekarzem.\n";
        }

        else if(25 <= bmi && bmi < 30)
        {
            cout << "\nTwoje BMI wskazuje na nadwage.\n";
            cout << "Sproboj utrzymac prawidlowa diete.\n";
        }

        else if(40 > bmi && bmi >= 30)
        {
            cout << "\nTwoje BMI wskazuje na otylosc.\n";
            cout << "Sproboj utrzymac prawidlowa diete.\n";
        }

        else if(bmi >= 40)
        {
            cout << "\nTwojemu BMI towarzyszy powazne ryzyko chorob.\n";
            cout << "Skontaktuj sie z lekarzem.\n";
        }

        cout << "\nTeraz mozesz wybrac plan dla siebie\n";
        cout << "\nWybierz swoj cel\n";
        cout << "\nAby kontynuowac nacisnij klawisz\n";
        getch();

        do {
            system( "cls" );

            if( wybranaopcja == 0 ) cout << "--> Chce utrzymac prawidlowa wage\n";
            else cout << "Chce utrzymac prawidlowa wage\n";

            if( wybranaopcja == 1 ) cout << "--> Chce schudnac\n";
            else cout << "Chce schudnac\n";

            if( wybranaopcja == 2 ) cout << "--> Maksymalna utrata wagi\n";
            else cout << "Maksymalna utrata wagi\n";


            opcja = getch();

            switch( opcja )
            {
                case 72:
                wybranaopcja--;
                break;
                case 80:
                wybranaopcja++;
                break;
            }

            if( wybranaopcja < 0 ) wybranaopcja++ ;
            if( wybranaopcja > 2 ) wybranaopcja-- ;

        } while( wybranaopcja != 3 && opcja != 13 );


        if( wybranaopcja == 0 && opcja == 13 )
        {
            cout << "\nWybrano utrzymanie prawidlowej wagi\n";
            zmianawagi = 1;
        }

        else if( wybranaopcja == 1 && opcja == 13 )
        {
            cout << "\nWybrano umiarkowana utrate wagi\n";
            zmianawagi = 2;
        }

        else if( wybranaopcja == 2 && opcja == 13 )
        {
            cout << "\nWybrano maksymalna utrate wagi\n";
            zmianawagi = 3;
        }

        cout << "\nWybierz rodzaj aktywnosci!\n";
        cout << "\nAby kontynuowac nacisnij klawisz\n";

        getch();

        do {
            system( "cls" );

            if( wybranaopcja == 0 ) cout << "--> Dieta\n";
            else cout << "Dieta\n";

            if( wybranaopcja == 1 ) cout << "--> Cwiczenia\n";
            else cout << "Cwiczenia\n";

           


            opcja = getch();

            switch( opcja )
            {
            case 72:
                wybranaopcja--;
                break;
            case 80:
                wybranaopcja++;
                break;
            }

            if( wybranaopcja < 0 ) wybranaopcja++ ;

            if( wybranaopcja > 1 ) wybranaopcja-- ;

        } while( wybranaopcja != 3 && opcja != 13 );

        do {

            cout << "\nNa ile dni wygenerowac plan?\n";
            cin >> ile_dni;

            if(!ile_dni) //sprawdzanie czy wiek jest poprawnie podany
            {
            cout <<"Podaj tylko liczbe\n";
            cin.clear();
            cin.sync();
            }

        }
        while( 120 < ile_dni || ile_dni < 1 );

        if( wybranaopcja == 0 && opcja == 13 )
        {
            cout << "\nWybrano dieta\n";
            if (zmianawagi == 1)
                {
                    cout << "Twoje zapotrzebowanie kaloryczne wynosi: " << 1.4*ppm << " kcal\n";
                    cout << "Oto jadlospis :\n";
                    //jedzenie
                   vector<Product> dania;
                   dania = oblicz_dieta();
                   diet (ile_dni, 1.4*ppm, dania);
                }

            else if (zmianawagi == 2)
                {
                    cout << "Twoje zapotrzebowanie kaloryczne wynosi: " << 1.2*ppm << " kcal\n";
                    cout << "Oto jadlospis :\n";
                    //jedzenie
                    vector<Product> dania;
                   dania = oblicz_dieta();
                   diet (ile_dni, 1.2*ppm, dania);
                }

             else if (zmianawagi == 3)
                {
                    cout << "Twoje zapotrzebowanie kaloryczne wynosi: " << ppm << " kcal\n";
                    cout << "Oto jadlospis:\n";
                    //jedzenie
                    vector<Product> dania;
                   dania = oblicz_dieta();
                   diet (ile_dni, ppm, dania);
                }
        }

        if( wybranaopcja == 1 && opcja == 13 )
        {
            cout << "\nWybrano cwiczenia\n";
            int intensywnosc=2*zmianawagi;
            if (zmianawagi == 1)
                {   int typ_cwiczen=0;
                       //Wybor typu cwiczen
                        do {
                            system( "cls" );
                            cout <<"Wybierz typ cwiczen"<< '\n';
                            if( typ_cwiczen == 0 ) cout << "--> Funkcyjne (wzmocnienie miesni bez ich rozbudowy)\n";
                            else cout << "Funkcyjne (wzmocnienie miesni bez ich rozbudowy)\n";

                            if( typ_cwiczen == 1 ) cout << "--> Cardio (zwiekszenie wydolnosci serca i spalanie tluszczu)\n";
                            else cout << "Cardio (zwiększenie wydolnosci serca i spalanie tluszczu)\n";

                            if( typ_cwiczen == 2 ) cout << "--> Silowe (rozbudowa tkanki miesniowej)\n";
                            else cout << "Silowe (rozbudowa tkanki miesniowej)\n";


                            opcja = getch();

                            switch( opcja )
                            {
                                case 72:
                                typ_cwiczen--;
                                break;
                                case 80:
                                typ_cwiczen++;
                                break;
                            }

                            if( typ_cwiczen < 0 ) typ_cwiczen++ ;
                            if( typ_cwiczen > 2 ) typ_cwiczen-- ;

                        } while(typ_cwiczen != 3 && opcja != 13 );

                        switch (typ_cwiczen){
                            case 0: typ="funk"; break;
                            case 1: typ = "cardio"; break;
                            case 2: typ= "sil"; break;
                        }
                    cout << "Musisz spalic: " << 0.6*ppm << " kcal dziennie\n";
                    cout << "Oto plan cwiczen:\n";
                    //cwiczenia
                    vector<Cwiczenie> wybrane_cw;
                    wybrane_cw= oblicz_cw(typ);
                    exc(wybrane_cw, ile_dni, intensywnosc);
                }

             else if (zmianawagi == 2)
                {
                    int typ_cwiczen=1;
                       //Wybor typu cwiczen
                        do {
                            system( "cls" );
                            cout <<"Wybierz typ cwiczen" << '\n';

                            if( typ_cwiczen == 1 ) cout << "--> Cardio (zwiekszenie wydolnosci serca i spalanie tluszczu)\n";
                            else cout << "Cardio (zwiększenie wydolnosci serca i spalanie tluszczu)\n";

                            if( typ_cwiczen == 2 ) cout << "--> Silowe (rozbudowa tkanki miesniowej)\n";
                            else cout << "Silowe (rozbudowa tkanki miesniowej)\n";


                            opcja = getch();

                            switch( opcja )
                            {
                                case 72:
                                typ_cwiczen--;
                                break;
                                case 80:
                                typ_cwiczen++;
                                break;
                            }

                            if( typ_cwiczen < 1 ) typ_cwiczen++ ;
                            if( typ_cwiczen > 2 ) typ_cwiczen-- ;

                        } while(typ_cwiczen != 3 && opcja != 13 );

                        switch (typ_cwiczen){
                            case 1: typ = "cardio"; break;
                            case 2: typ= "sil"; break;
                        }




                    cout << "Musisz spalic: " << 0.8*ppm << " kcal dziennie\n";
                    cout << "Oto plan cwiczen:\n";
                    //cwiczenia
                    vector<Cwiczenie> wybrane_cw;
                    wybrane_cw= oblicz_cw(typ);
                    exc(wybrane_cw, ile_dni, intensywnosc);
                }

             else if (zmianawagi == 3)
                { typ ="cardio";
                    cout << "Musisz spalic: " << ppm << " kcal\n";
                    cout << "Oto plan cwiczen:\n";
                    //cwiczenia
                    vector<Cwiczenie> wybrane_cw;
                    wybrane_cw= oblicz_cw(typ);
                    exc(wybrane_cw, ile_dni, intensywnosc);
                }

        }

       

    return 0;
}







//CIALA FUNCKJI

void exc (vector <Cwiczenie> wektor, int ile_dni, int intens){
srand(time(NULL));
for (int i=1; i<ile_dni; i++){
                cout << "Dzien " << i << ":"<< '\n' << '\n';
                
                random_shuffle(wektor.begin(), wektor.end());

                cout << "Zestaw cwiczen:" <<  '\n';
                float czas=0;

                for (int i =0; czas<2000 && i<wektor.size() ;i++) //czas w sekundach, mniej wiecej pol godziny
                    {
                        wektor[i].show(intens);
                        if (wektor[i].czas) czas+=(wektor[i].powtorzenia*4);
                        else czas += (wektor[i].powtorzenia*8);
                    }
            cout << '\n' << "===============================" << '\n';
        }
}
void diet (int ile_dni, float kalorie, vector<Product> produkty){
        vector <Product> jedzenie;
        srand(time(NULL));
    for (int i=1; i<ile_dni; i++){
                cout << "Dzien " << i << ":"<< '\n' << '\n';
                jedzenie = diet_single( kalorie, produkty );
        random_shuffle(produkty.begin(), produkty.end());
                cout << "Jedzenie: " <<  '\n';
                cout << "Sniadanie: " << jedzenie[0].name << '\n';
                cout << "Lunch (drugie sniadanie): " << jedzenie[1].name <<'\n';
                cout << "Obiad: " << jedzenie[2].name <<'\n';
                cout << "Kolacja: " << jedzenie[3].name <<'\n';

            cout << '\n' << "===============================" << '\n';
        }


}


vector<Product> diet_single (float kalorie, vector <Product> dish){

    vector<Product> produkt;
    float part = kalorie / 20;
    string typ;
    bool znalezione = false;

     int ktory;
    for (int i=0; i<4; i++){
        ktory = 0;

            switch(i){
            case 0: typ="Breakfast"; break;
            case 1: typ="Lunch"; break;
            case 2: typ="Dinner"; break;
            case 3: typ="Supper"; break;
            }

        while (!znalezione && ktory<dish.size()) {

            if ((dish[ktory].type == typ) && ((dish[ktory].cal) < ((part*5) + 100)) && ((dish[ktory].cal ) > (part* 5 - 100))){
                  produkt.push_back(Product(dish[ktory].name , dish[ktory].cal , dish[ktory].type));
                znalezione = true;
            }
            ktory++;

        }
       znalezione = false;
   
        if (ktory>dish.size()){

        cout << "nie udało się znaleść pasującego dania, dodaj więcej dań do pliku i spróbuj ponownie";
        exit(0);
        }
    }

 return produkt;
}


