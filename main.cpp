#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

ifstream fin ("matrice.txt");

int matrice[32][32];

bool nv(int m[32][32], int lat, int x, int y)
{
    if (lat>min(x,y))
        return false;
    if (m[x-lat][y-lat] && m[x-lat][y] && m[x][y-lat])
        return true;
    else
        return false;
}

bool sv(int m[32][32],int marime, int lat, int x, int y)
{
    if (lat>min(marime-y,x))
        return false;
    if (m[x-lat][y+lat] && m[x-lat][y] && m[x][y+lat])
        return true;
    else
        return false;
}

bool ne(int m[32][32],int marime, int lat, int x, int y)
{
    if (lat>min(marime-x,y))
        return false;
    if (m[x][y-lat] && m[x+lat][y-lat] && m[x+lat][y])
        return true;
    else
        return false;
}

bool se(int m[32][32],int marime, int lat, int x, int y)
{
    if (lat>min(marime-x,marime-y))
        return false;
    if (m[x+lat][y] && m[x][y+lat] && m[x+lat][y+lat])
        return true;
    else
        return false;
}

bool patrat(int m[32][32],int marime,int lat, int x, int y)
{
    if (lat<=0 || m[x][y]==0)
        return false;
    else if (nv(m,lat,x,y))
        return true;
    else if (sv(m,marime,lat,x,y))
        return true;
    else if (ne(m,marime,lat,x,y))
        return true;
    else if (se(m,marime,lat,x,y))
        return true;
    else
        return patrat (m,marime,lat-1,x,y);
}

int main()
{
    int i,j,n;
    fin>>n;
    for (i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if (i<n && j<n)
                fin>>matrice[i][j];
            else
                matrice[i][j]=0;
        }
    }
    cout << "Citit" << endl;
    for (i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if (i<n && j<n)
                cout<<matrice[i][j]<<" ";
        }
        cout<<endl;
    }
    int mx,my;
    cin>>mx>>my;
    if (patrat(matrice,n,n,mx,my))
        cout<<"Patrat";
    else
        cout<<"NU";
    return 0;
}
