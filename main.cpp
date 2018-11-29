#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

using namespace std;

float limita_stanga,limita_sus,width_tabla,height_tabla,latura_patrat,window_lenght,window_height,over; ///deocamdata toate float pentru window scaling

int marime_tabla,contor_piese,culoare1=rand()%15,culoare2=rand()%15;    ///culori flashy cand dai pe langa

bool gata;

void(PiesaPusaGresit)()     ///inca lucrez la asta, mesaj colorat diferit la fiecare mutare incorecta
{
    while(culoare1==culoare2)
        culoare2=rand()%15;
    setfillstyle(1,culoare1);
    setcolor(culoare1);
    bar(0,window_height-16,window_lenght,window_height);
    culoare1=culoare2;
    setfillstyle(1,culoare2);
    setcolor(culoare2);
    outtextxy(0,window_height-16,"Nu se pot pune piese in afara tablei de joc");
    setfillstyle(0,15);
    setcolor(15);
}

void PunePiesa()        ///peste asta ar trebui implementat programul din fundal, cu o matrice
{
    int linia,coloana,x,y;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        if (!(x>=limita_stanga && x<=limita_stanga+width_tabla && y>=limita_sus&&y<=limita_sus+height_tabla))
            PiesaPusaGresit();
        else
        {
            linia=(y-limita_sus)/latura_patrat+1;
            coloana=(x-limita_stanga)/latura_patrat+1;
            circle(limita_stanga+latura_patrat*(coloana-1)+latura_patrat/2,limita_sus+latura_patrat*(linia-1)+latura_patrat/2,latura_patrat/3);
        }
    }
}

void tabla(int marime)      ///orice marime are tabla, va incapea intr-o fereastra 1280x960
{
    int i,j;
    width_tabla=floor((80*marime)/over);
    height_tabla=floor((80*marime)/over);
    latura_patrat=width_tabla/marime_tabla;
    limita_sus=(getmaxy()-width_tabla)/2;
    limita_stanga=(getmaxx()-height_tabla)/2;
    for(i=1; i<=marime_tabla; i++)
    {
        for(j=1; j<=marime_tabla; j++)
            rectangle(limita_stanga+latura_patrat*(i-1),limita_sus+latura_patrat*(j-1),limita_stanga+latura_patrat*i,limita_sus+latura_patrat*j);
    }
}

bool tabla_plina (int matrice[32][32],int marime)       ///probabil pentru mai incolo, vezi daca se mai pot face mutari sau dai rezultatul si iesi
{
    int i,j;
    for (i=0; i<marime; i++)
    {
        for(j=0; j<marime; j++)
        {
            if (matrice[i][j]==0)
                return false;
        }
    }
    return true;
}

int main()
{
    cout<<"Jocul evitarii patratelor presupune o tabla de N x N patrate."<<endl<<endl;
    cout<<"Fiecare jucator pune cate un pion pe tabla."<<endl<<endl;
    cout<<"Jocul se termina cand un jucator completeaza cu ultimul pion pus un patrat. Acest jucator pierde."<<endl<<endl;
    cout<<"Potentialele patrate sunt formate din pionii ambilor jucatori, inclusiv pe diagonale."<<endl<<endl;
    cout<<"Marimea tablei de joc ";
    cin>>marime_tabla;
    while (marime_tabla<3 || marime_tabla>32)
    {
        cout<<endl;
        cout<<"Tabla prea mica/mare, joc imposibil. Reintroduceti o marime valida (intre 3 si 32) ";        ///pare rezonabil, peste 32 cercurile nu mai sunt cercuri
        cin>>marime_tabla;
    }
    if(marime_tabla<=8)
        over=1;
    if(marime_tabla>8)
        over=float(marime_tabla)/8;                                     ///am luat ca referinta cat avea fereastra standard pentru o tabla de 8x8 si totul scaleaza la nivelul ei
    window_lenght=((160*marime_tabla)/over);
    window_height=((120*marime_tabla)/over);
    initwindow(window_lenght,window_height,"Evitarea Patratelor");
    int istoric[marime_tabla][marime_tabla];
    tabla(marime_tabla);
    gata=false;

    do
    {
        PunePiesa();
    }
    while (!gata);
    getch();
    closegraph();
    return 0;
}
