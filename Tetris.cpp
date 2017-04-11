/**

 DO ZROBIENIA :
    - OBRACANIE  .....................................................READY
    - WYKRYWANIE PRZESZKODY PO BOKACH.................................READY
    - PUNKTY..........................................................READY
    - WYGRYWANIE/PRZEGRYWANIE
    - KASOWANIE BLOKOW PO ULOZENIU CALEJ LINII........................READY
    - SPADNIECIE BLOKU PO PRZYTRZYMANIU BUTTONA W DOL.................NOT READY

**/


#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cstdio>
#include <time.h>
#define wysokosc 21
#define szerokosc 19
using namespace std;
extern short int KolorKlocka();

    class plansza
        {
            friend int main();
            friend void StworzKlocek();
            private:
                bool pola[wysokosc][szerokosc];
                short int pola_kolor[wysokosc][szerokosc];
                char znak=219;
                int wynik=0;
                int skasowanych=0;
                int poziom=1;
                int next_level=0;
                int kolor_glowny=6;
                bool przegrana=false;
            public:
                void WyswietlPlansze()
                    {
                        system("cls");

                        HANDLE konsola;
                        konsola = GetStdHandle(STD_OUTPUT_HANDLE);

                        cout<<endl<<endl;
                        for(int i=0;i<wysokosc;i++)
                        {
                            SetConsoleTextAttribute(konsola,kolor_glowny);
                            cout<<"\t\t\t|";
                            for(int j=0;j<szerokosc;j++)
                            {
                                SetConsoleTextAttribute(konsola,pola_kolor[i][j]);
                                if(pola[i][j])
                                    cout<<znak;
                                else
                                    cout<<" ";

                            }
                            SetConsoleTextAttribute(konsola,kolor_glowny);
                            cout<<"|";
                            switch(i)
                                {
                                    case 1:
                                        cout<<"\tCmdTetris - Piotr Jagusiak"<<endl;
                                        break;

                                    case 3:
                                        cout<<"\t___________"<<endl;
                                        break;

                                    case 4:
                                        cout<<"\tPoziom :"<<poziom<<endl;
                                        break;

                                    case 5:
                                        cout<<"\tWynik :"<<wynik<<endl;
                                        break;
                                    case 6:
                                        cout<<"\t___________"<<endl;
                                        break;
                                    case 7:
                                        cout<<"\t'ESC' by zakonczyc"<<endl;
                                        break;
                                    case 8:
                                        cout<<"\t'a' i 'd' poruszanie klockiem"<<endl;
                                        break;
                                    case 9:
                                        cout<<"\t'w' obracanie klockiem"<<endl;
                                        break;
                                    case 10:
                                        cout<<"\t's' by opuscic klocek"<<endl;
                                        break;

                                    case 12:
                                        if(przegrana)
                                        {
                                            cout<<"\tPrzegrales!"<<endl;
                                            break;
                                        }
                                    case 13:
                                        if(przegrana)
                                        {
                                            cout<<"\t'ENTER' by zrestartowac"<<endl;
                                            break;
                                        }
                                    default:
                                        cout<<endl;
                                        break;
                                }

                        }

                            cout<<"\t\t\t ";
                        for(int i=0;i<szerokosc;i++)
                            cout<<"-";
                    };

                void DodajPunktPlanszy(int x,int y)
                {
                    pola[y][x]=true;
                }

                void DodajKolorKlocka(int x,int y)
                {
                    pola_kolor[y][x]=KolorKlocka();
                }

                void PrzeniesKolorKlocka(int x,int y, int x2, int y2)
                {
                    pola_kolor[y2][x2]=pola_kolor[y][x];
                }

                void WyczyscKolor(int x,int y)
                {
                    pola_kolor[y][x]=7;
                }
                void UsunPunktPlanszy(int x,int y)
                {
                    pola[y][x]=false;
                }

                bool CzyPunktZapelniony(int x,int y)
                {
                    if(pola[y][x]==true)
                        return true;
                    else
                        return false;
                }

                void idle_check_and_remove()
                {
                    _beep(100,100);
                    bool wiersz_do_usuniecia[wysokosc];
                    short int liczba_wierszy=wysokosc;

                    for(int i=0;i<wysokosc;i++)
                    {
                        wiersz_do_usuniecia[i]=true;
                    }

                    for(int i=0;i<wysokosc;i++)
                    {
                        for(int j=0;j<szerokosc;j++)
                        {
                            if(!CzyPunktZapelniony(j,i))
                            {
                                wiersz_do_usuniecia[i]=false;
                                liczba_wierszy--;
                                break;
                            }
                        }
                    }

                    skasowanych+=liczba_wierszy;
                    wynik+=liczba_wierszy*1000;
                    next_level+=liczba_wierszy;

                    if(next_level>=10)
                        {
                            poziom++;
                            next_level=0;
                            _beep(300,200);
                            _beep(500,500);

                            if(kolor_glowny==6)
                                kolor_glowny=10;
                            else if(kolor_glowny>6 and kolor_glowny<16)
                                kolor_glowny++;
                            else
                                kolor_glowny=6;

                            fflush(stdin);
                        }

                    bool usuwano_cos=false;
                    bool dzwiek=false;
                    for(int i=0;i<szerokosc;i++)
                    {
                        for(int j=0;j<wysokosc;j++)
                        {
                            if(wiersz_do_usuniecia[j])
                            {
                                usuwano_cos=true;
                                dzwiek=true;
                                UsunPunktPlanszy(i,j);
                            }
                        }

                        if(dzwiek)
                        {
                            _beep(200,40);
                            WyswietlPlansze();
                            dzwiek=false;
                        }
                    }

                    if(usuwano_cos)
                    {
                        bool pusta;
                        short int ile_pustych=0;
                            for(int i=wysokosc-1;i>0;i--)
                                {
                                    pusta=true;
                                    for(int j=0;j<szerokosc;j++)
                                        {
                                            if(CzyPunktZapelniony(j,i))
                                            {
                                                pusta=false;
                                            }
                                        }
                                    if(pusta)
                                        ile_pustych++;
                                    else
                                        for(int j=0;j<szerokosc;j++)
                                            {
                                                if(CzyPunktZapelniony(j,i))
                                                {
                                                    UsunPunktPlanszy(j,i);
                                                    DodajPunktPlanszy(j,i+ile_pustych);
                                                    PrzeniesKolorKlocka(j,i,j,i+ile_pustych);
                                                }
                                            }
                                }
                            WyswietlPlansze();
                        }
                }

                plansza()
                {
                    for(int i=0;i<wysokosc;i++)
                        {
                            for(int j=0;j<szerokosc;j++)
                            {
                                pola[i][j]=false;
                                pola_kolor[i][j]=7;
                            }
                        }
                };
        };
plansza plansza;

    class klocek
        {
            friend int main();
            friend void StworzKlocekStart(string id);
            friend void StworzKlocek();
            private:
                short int PozycjaSegmentu_x[4];
                short int PozycjaSegmentu_y[4];
                short int obrot=0;
                short int kolor;
                string id;
            public:
                void DefinicjaKlocka(int x1,int x2,int x3, int x4,
                                    int y1,int y2, int y3, int y4,
                                    string identyfikator)
                                        {
                                                PozycjaSegmentu_x[0]=x1;
                                                PozycjaSegmentu_x[1]=x2;
                                                PozycjaSegmentu_x[2]=x3;
                                                PozycjaSegmentu_x[3]=x4;

                                                PozycjaSegmentu_y[0]=y1;
                                                PozycjaSegmentu_y[1]=y2;
                                                PozycjaSegmentu_y[2]=y3;
                                                PozycjaSegmentu_y[3]=y4;

                                                id=identyfikator;
                                        };
                void UstawPozycje(int x,int y)
                        {
                            for(int i=0;i<4;i++)
                            {
                                PozycjaSegmentu_x[i]+=x;
                                PozycjaSegmentu_y[i]+=y;
                            }
                        }
                void NalozNaPlansze()
                        {
                            for(int i=0;i<4;i++)
                            {
                                plansza.DodajPunktPlanszy(PozycjaSegmentu_x[i],PozycjaSegmentu_y[i]);
                                plansza.DodajKolorKlocka(PozycjaSegmentu_x[i],PozycjaSegmentu_y[i]);
                            }
                        }
                string PobierzID()
                        {
                            return id;
                        }
                bool czy_przeszkoda(string w_ktora)
                {
                        for(int i=0;i<4;i++)
                            {
                                plansza.UsunPunktPlanszy(PozycjaSegmentu_x[i],PozycjaSegmentu_y[i]);
                            }

                            if(w_ktora=="lewo")
                                {
                                    for(int i=0;i<4;i++)
                                        if(PozycjaSegmentu_x[i]<=0 or plansza.CzyPunktZapelniony(PozycjaSegmentu_x[i]-1,PozycjaSegmentu_y[i]))
                                            return true;
                                }
                            if(w_ktora=="prawo")
                                {
                                    for(int i=0;i<4;i++)
                                        if(PozycjaSegmentu_x[i]>=szerokosc-1 or plansza.CzyPunktZapelniony(PozycjaSegmentu_x[i]+1,PozycjaSegmentu_y[i]))
                                            return true;
                                }
                            if(w_ktora=="dol")
                                {
                                    for(int i=0;i<4;i++)
                                        if(PozycjaSegmentu_y[i]>=wysokosc-1 or plansza.CzyPunktZapelniony(PozycjaSegmentu_x[i],PozycjaSegmentu_y[i]+1))
                                            return true;
                                }
                            if(w_ktora=="gora")
                                {
                                    for(int i=0;i<4;i++)
                                        if(PozycjaSegmentu_y[i]<=0 or plansza.CzyPunktZapelniony(PozycjaSegmentu_x[i],PozycjaSegmentu_y[i]-1))
                                            return true;
                                }

                }
                void Przesun(string w_ktora)
                        {
                            for(int i=0;i<4;i++)
                                {
                                    plansza.UsunPunktPlanszy(PozycjaSegmentu_x[i],PozycjaSegmentu_y[i]);
                                }

                            if(w_ktora=="lewo")
                                {
                                    if(!czy_przeszkoda("lewo"))
                                        for(int i=0;i<4;i++)
                                            PozycjaSegmentu_x[i]-=1;
                                }
                            if(w_ktora=="prawo")
                                {
                                    if(!czy_przeszkoda("prawo"))
                                        for(int i=0;i<4;i++)
                                            PozycjaSegmentu_x[i]+=1;
                                }
                            if(w_ktora=="dol")
                                {
                                    if(!czy_przeszkoda("dol"))
                                        for(int i=0;i<4;i++)
                                            PozycjaSegmentu_y[i]+=1;
                                }
                            if(w_ktora=="gora")
                                {
                                    if(!czy_przeszkoda("gora"))
                                        for(int i=0;i<4;i++)
                                            PozycjaSegmentu_y[i]-=1;
                                }
                            NalozNaPlansze();
                        }

                bool czy_podloze()
                {
                    bool sprawdzanie_podloza[4];
                    for(int i=0;i<4;i++)
                    {
                        sprawdzanie_podloza[i]=true;
                    }

                    for(int i=0;i<4;i++)
                    {
                        if(PozycjaSegmentu_y[i]<wysokosc-1 and plansza.CzyPunktZapelniony(PozycjaSegmentu_x[i],PozycjaSegmentu_y[i]+1))
                        {
                            for(int j=0;j<4;j++)
                            {
                                if(i!=j)
                                {
                                    if(PozycjaSegmentu_y[i]==PozycjaSegmentu_y[j]-1 and PozycjaSegmentu_x[i]==PozycjaSegmentu_x[j])
                                    {
                                        sprawdzanie_podloza[i]=false;
                                        break;
                                    }
                                }

                            }
                        }
                        else if(PozycjaSegmentu_y[i]>=wysokosc-1)
                        {
                            sprawdzanie_podloza[i]=true;
                        }
                        else
                        {
                          sprawdzanie_podloza[i]=false;
                        }

                    }

                    for(int i=0;i<4;i++)
                    {
                        if(sprawdzanie_podloza[i]==true)
                        {
                            return true;
                        }
                    }
                    return false;
                }

            void obroc()
            {
                for(int i=0;i<4;i++)
                    {
                        plansza.UsunPunktPlanszy(PozycjaSegmentu_x[i],PozycjaSegmentu_y[i]);
                    }

                short int Najmniejsza_wartoscX=99;
                short int Najwieksza_wartoscX=0;

                short int Najmniejsza_wartoscY=99;
                short int Najwieksza_wartoscY=0;

                short int Wielkosc_Obiektu;
                short int SrodekX;
                short int SrodekY;
                for(int i=0;i<4;i++)
                    {
                        if(PozycjaSegmentu_x[i]>Najwieksza_wartoscX)
                            Najwieksza_wartoscX=PozycjaSegmentu_x[i];
                        if(PozycjaSegmentu_x[i]<Najmniejsza_wartoscX)
                            Najmniejsza_wartoscX=PozycjaSegmentu_x[i];

                        if(PozycjaSegmentu_y[i]>Najwieksza_wartoscY)
                            Najwieksza_wartoscY=PozycjaSegmentu_y[i];
                        if(PozycjaSegmentu_y[i]<Najmniejsza_wartoscY)
                            Najmniejsza_wartoscY=PozycjaSegmentu_y[i];
                    }

                if((Najwieksza_wartoscX-Najmniejsza_wartoscX)>=(Najwieksza_wartoscY-Najmniejsza_wartoscY))
                    {
                        Wielkosc_Obiektu=Najwieksza_wartoscX-Najmniejsza_wartoscX+1;
                    }
                else
                    {
                        Wielkosc_Obiektu=Najwieksza_wartoscY-Najmniejsza_wartoscY+1;
                    }

                SrodekX=(Najmniejsza_wartoscX+Najwieksza_wartoscX)/2;
                SrodekY=(Najmniejsza_wartoscY+Najwieksza_wartoscY)/2;

                bool TempObiekt[Wielkosc_Obiektu][Wielkosc_Obiektu];
                bool TempObiektNew[Wielkosc_Obiektu][Wielkosc_Obiektu];

                    for(int i=0;i<Wielkosc_Obiektu;i++)
                        {
                            for(int j=0;j<Wielkosc_Obiektu;j++)
                                {
                                    TempObiekt[i][j]=false;
                                }
                        }

                    for(int i=0;i<4;i++)
                        TempObiekt[PozycjaSegmentu_y[i]-Najmniejsza_wartoscY][PozycjaSegmentu_x[i]-Najmniejsza_wartoscX]=true;

                    for(int i=0;i<Wielkosc_Obiektu;i++)
                        {
                                for(int j=0;j<Wielkosc_Obiektu;j++)
                                {
                                        TempObiektNew[i][j]=TempObiekt[j][(Wielkosc_Obiektu-1)-i];
                                }
                        }
                    short int k=0;


                    if(obrot<=3) obrot++;
                    else         obrot=1;

                    short int PozycjaSegmentu_x_temp[4];
                    short int PozycjaSegmentu_y_temp[4];

                    for(int i=0;i<Wielkosc_Obiektu;i++)
                        {
                             for(int j=0;j<Wielkosc_Obiektu;j++)
                                {
                                    if(TempObiektNew[i][j]==true)
                                    {
                                        if(id!="kwadrat")
                                        {
                                            short int poprawkax=0;
                                            short int poprawkay=0;

                                            if(id=="LX")
                                            {
                                                if(obrot==1)
                                                {
                                                  poprawkay=0;
                                                  poprawkax=1;
                                                }
                                                if(obrot==2)
                                                {
                                                    poprawkax=1;
                                                    poprawkay=0;
                                                }
                                                if(obrot==3)
                                                {
                                                    poprawkax=0;
                                                    poprawkay=-1;
                                                }
                                                if(obrot==4)
                                                {
                                                    poprawkax=0;
                                                    poprawkay=1;
                                                }
                                            }

                                            if(id=="L")
                                            {
                                                if(obrot==1)
                                                {
                                                  poprawkay=-1;
                                                  poprawkax=0;
                                                }
                                                if(obrot==2)
                                                {
                                                    poprawkax=0;
                                                    poprawkay=1;
                                                }
                                                if(obrot==3)
                                                {
                                                    poprawkax=1;
                                                    poprawkay=0;
                                                }
                                                if(obrot==4)
                                                {
                                                    poprawkax=1;
                                                    poprawkay=0;
                                                }
                                            }

                                            if(id=="prosty" )
                                            {
                                                if(obrot==1)
                                                {
                                                    poprawkax=1;
                                                    poprawkay=0;
                                                }
                                                if(obrot==2)
                                                {
                                                    poprawkax=2;
                                                    poprawkay=0;
                                                }
                                                if(obrot==3)
                                                {
                                                    poprawkax=1;
                                                    poprawkay=0;
                                                }
                                                if(obrot==4)
                                                {
                                                    poprawkax=2;
                                                    poprawkay=0;
                                                }
                                            }

                                            if(id=="s")
                                            {
                                                if(obrot==1)
                                                {
                                                    poprawkax=0;
                                                    poprawkay=0;
                                                }
                                                if(obrot==2)
                                                {
                                                    poprawkax=1;
                                                    poprawkay=0;
                                                }
                                                if(obrot==3)
                                                {
                                                    poprawkax=0;
                                                    poprawkay=0;
                                                }
                                                if(obrot==4)
                                                {
                                                    poprawkax=1;
                                                    poprawkay=0;
                                                }
                                            }

                                            if(id=="z")
                                            {
                                                if(obrot==1)
                                                {
                                                    poprawkax=0;
                                                    poprawkay=0;
                                                }
                                                if(obrot==2)
                                                {
                                                    poprawkax=1;
                                                    poprawkay=0;
                                                }
                                                if(obrot==3)
                                                {
                                                    poprawkax=0;
                                                    poprawkay=0;
                                                }
                                                if(obrot==4)
                                                {
                                                    poprawkax=1;
                                                    poprawkay=0;
                                                }
                                            }
                                            PozycjaSegmentu_x_temp[k]=SrodekX-(Wielkosc_Obiektu/2)+j+poprawkax;
                                            PozycjaSegmentu_y_temp[k]=SrodekY-(Wielkosc_Obiektu/2)+i+poprawkay;
                                     //       cout<<SrodekX-(Wielkosc_Obiektu/2)+j+poprawkax<<" "<<SrodekY-(Wielkosc_Obiektu/2)+i+poprawkay<<"|";
                                            k++;
                                        }
                                    }
                                }
                        }

                    bool mozna_obrocic=true;

                    for(int i=0;i<4;i++)
                            if(plansza.CzyPunktZapelniony(PozycjaSegmentu_x_temp[i],PozycjaSegmentu_y_temp[i]) or
                               PozycjaSegmentu_x_temp[i]<0 or PozycjaSegmentu_x_temp[i]>=szerokosc or
                               PozycjaSegmentu_y_temp[i]<0 or PozycjaSegmentu_y_temp[i]>wysokosc)
                                    mozna_obrocic=false;

                    if(mozna_obrocic)
                    {
                        for(int i=0;i<4;i++)
                        {
                            PozycjaSegmentu_x[i]=PozycjaSegmentu_x_temp[i];
                            PozycjaSegmentu_y[i]=PozycjaSegmentu_y_temp[i];
                        }
                    }
                    NalozNaPlansze();
                    plansza.WyswietlPlansze();
            }

            short int returnKolor()
            {
                return kolor;
            }
        };

    vector<klocek> TypyKlockow;
    klocek *WskTablicaKlockow;
    klocek *Wsk_Klocek=new klocek;

        void StworzKlocek()
        {
            short int numer=(rand()%(TypyKlockow.size()-1)+1);
                WskTablicaKlockow=&TypyKlockow[numer];
                *(Wsk_Klocek)=*(WskTablicaKlockow);
                Wsk_Klocek->kolor=rand()%7+1;

                Wsk_Klocek->UstawPozycje(szerokosc/2,0);
                Wsk_Klocek->NalozNaPlansze();

                if(Wsk_Klocek->czy_podloze())
                    plansza.przegrana=true;
        }

        short int KolorKlocka()
        {
            return Wsk_Klocek->returnKolor();
        }



int main()
{
    char znak=0;
    // KLOCEK "S"
    WskTablicaKlockow=new klocek;
    WskTablicaKlockow->DefinicjaKlocka(0,1,1,2,1,0,1,0,"s");
    TypyKlockow.push_back(*WskTablicaKlockow);
    delete WskTablicaKlockow;

    // KLOCEK "Z"
    WskTablicaKlockow=new klocek;
    WskTablicaKlockow->DefinicjaKlocka(0,1,1,2,0,0,1,1,"z");
    TypyKlockow.push_back(*WskTablicaKlockow);
    delete WskTablicaKlockow;

    // KLOCEK "KWADRAT"
    WskTablicaKlockow=new klocek;
    WskTablicaKlockow->DefinicjaKlocka(0,0,1,1,0,1,0,1,"kwadrat");
    TypyKlockow.push_back(*WskTablicaKlockow);
    delete WskTablicaKlockow;

    // KLOCEK PROSTY
    WskTablicaKlockow=new klocek;
    WskTablicaKlockow->DefinicjaKlocka(0,0,0,0,0,1,2,3,"prosty");
    TypyKlockow.push_back(*WskTablicaKlockow);
    delete WskTablicaKlockow;

    // KLOCEK "L"
    WskTablicaKlockow=new klocek;
    WskTablicaKlockow->DefinicjaKlocka(0,0,0,1,0,1,2,2,"L");
    TypyKlockow.push_back(*WskTablicaKlockow);
    delete WskTablicaKlockow;

    // KLOCEK ODWROCONE L "LX"
    WskTablicaKlockow=new klocek;
    WskTablicaKlockow->DefinicjaKlocka(0,1,1,1,2,0,1,2,"LX");
    TypyKlockow.push_back(*WskTablicaKlockow);
    delete WskTablicaKlockow;

    StworzKlocek();
    plansza.WyswietlPlansze();
    bool nowy=false;
    clock_t koniec=clock() + 1/(plansza.poziom*0.4) * CLOCKS_PER_SEC;;

   // char znak[4]={'w','a','s','d'};
  //  cout<<(int)znak[0]<<endl;   //119 w
  //  cout<<(int)znak[1]<<endl;   //97 a
  //  cout<<(int)znak[2]<<endl;   //115 s
  //  cout<<(int)znak[3]<<endl;   //100 d
    while(znak!=27)
        {
            if(kbhit())
            {
                 fflush(stdin);
                 znak=getch();
            }

            if(plansza.przegrana==true)
            {
                plansza.kolor_glowny=12;
                _beep(700,200);
                _beep(600,200);
                _beep(500,200);
                _beep(200,400);
                for(int i=wysokosc-1;i>=0;i--)
                {
                    for(int j=szerokosc-1;j>=0;j--)
                    {
                        plansza.DodajPunktPlanszy(j,i);
                        plansza.WyczyscKolor(j,i);
                        if(j%4==0)
                            plansza.WyswietlPlansze();
                    }
                }

                while(1==1)
                {
                    if(kbhit())
                    {
                         fflush(stdin);
                         znak=getch();
                    }

                    if(znak==13)
                    {
                            for(int i=wysokosc-1;i>=0;i--)
                            {
                                for(int j=szerokosc-1;j>=0;j--)
                                {
                                    plansza.UsunPunktPlanszy(j,i);
                                    plansza.WyczyscKolor(j,i);
                                }
                            }
                        plansza.wynik=0;
                        plansza.poziom=1;
                        plansza.przegrana=false;
                        plansza.next_level=0;
                        plansza.kolor_glowny=6;

                        koniec=clock() + 1/((plansza.poziom+1)*0.5) * CLOCKS_PER_SEC;
                        StworzKlocek();
                        _beep(300,200);
                        _beep(500,500);
                        plansza.WyswietlPlansze();
                        break;
                    }

                    if(znak==27)
                    {
                        return true;
                    }
                }
            }

            if(znak=='a')
                {
                    Wsk_Klocek->Przesun("lewo");
                    plansza.WyswietlPlansze();
                    znak=0;
                }

            if(znak=='d')
                {
                    Wsk_Klocek->Przesun("prawo");
                    plansza.WyswietlPlansze();
                    znak=0;
                }
            if(Wsk_Klocek->czy_podloze())
                {
                    if(znak=='s')
                        {
                            plansza.idle_check_and_remove();
                            StworzKlocek();
                            plansza.wynik+=10;
                            nowy=false;
                            znak=0;
                        }
                }
            else
                {
                    if(znak=='s')
                        {
                            Wsk_Klocek->Przesun("dol");
                            plansza.WyswietlPlansze();
                            znak=0;
                        }
                }

            if(znak=='w' and koniec>clock())
                {
                    Wsk_Klocek->obroc();
                    plansza.WyswietlPlansze();
                    znak=0;
                }

            if(koniec<=clock())
            {
                if(!Wsk_Klocek->czy_podloze())
                    {
                        Wsk_Klocek->Przesun("dol");
                        plansza.WyswietlPlansze();
                    }
                else
                    {
                        nowy=true;
                    }

                if(nowy==true)
                {
                    plansza.idle_check_and_remove();
                    StworzKlocek();
                    plansza.wynik+=10;
                    plansza.WyswietlPlansze();
                    nowy=false;
                }

                koniec=clock() + 1/((plansza.poziom+1)*0.5) * CLOCKS_PER_SEC;
            }
        }
}
