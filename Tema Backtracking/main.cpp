//Simion Stefan Gr 163
//Numele fisierelor .out este seed-ul folosit cand DIMENSION este 7
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#ifndef DIMENSION
#define DIMENSION 7 //Trebuie sa fie numar impar, se poate modifica si se pot pune numere mari, complexitatea cred ca e DIMENSION^2 +-
#endif

using namespace std;

///Ziduri notate cu 1, locul pe unde se merge notat cu 2 (le afisez ca fiind 0 pentru o vizibilitate mai buna)
int maze[DIMENSION][DIMENSION];
int dir[4]={1,2,3,4};

void init(){//Functie care pune un zid pe toate valorile care au un numar par fie la linie, fie la coloana, credeam ca am nevoie de ea dar aparent e doar redundanta
    for(int i=0;i<DIMENSION;i+=2)
        for(int j=0;j<DIMENSION;j++)
            maze[i][j]=maze[j][i]=1;


}

void randomizearray(int arr[], int s){//Functie de randomizare a unui array pe care o sa o folosesc la alegerea unei directii random
    for(int i=0;i<s;i++){
        swap(arr[i],arr[rand()%s]);
    }

}

void afis0(){//Afisare in care inlocuiesc 2-ul cu 0 pentru vizibilitate
    for(int i=0;i<DIMENSION;i++){
        for(int j=0;j<DIMENSION;j++)
            if(maze[i][j]==2)
                cout<<"0 ";
            else
                cout<<"1 ";

        cout<<endl;
    }
}
void afis(){
    for(int i=0;i<DIMENSION;i++){
        for(int j=0;j<DIMENSION;j++)
            cout<<maze[i][j]<<" ";
        cout<<endl;
    }

}


void gen(int x,int y, int dir);

void bck(int x, int y);


int main()
{
    srand(time(NULL));
    int x,y;
    x=((rand()%((DIMENSION-3)/2))*2)+1;//Numar impar intre 1 si 19;
    y=((rand()%((DIMENSION-3)/2))*2)+1;
    init();//Nu ne nevoie de init, dar o apelez ca zidurile sa fie notate cu 1;
    bck(x,y);
    maze[x][0]=2;//Setez intrarea si iesirea din maze. Mereu se intra prin stanga si se iese prin dreapta
    maze[y][DIMENSION-1]=2;
    //afis();
    afis0();

    return 0;
}


void gen(int x,int y, int direction){
    switch (direction){
        case 1: //SUS
            maze[x-1][y]=2;
            bck(x-2,y);
            break;
        case 2: //JOS
            maze[x+1][y]=2;
            bck(x+2,y);
            break;
        case 3: //STANGA
            maze[x][y-1]=2;
            bck(x,y-2);
            break;
        case 4: //DREAPTA
            maze[x][y+1]=2;
            bck(x,y+2);
            break;
    }


}

void bck(int x, int y){
    maze[x][y]=2;
    randomizearray(dir,4);
    int dir2[4];
    for(int i=0;i<4;i++)
        dir2[i]=dir[i];
    //Fix la un bug care facea ca maze-ul sa nu se genereze in totalitate:
    //Tin minte aranjementul curent al vectorului de directii ca sa nu uite programul sa se duca intr-o directie

    for(int i=0;i<4;i++){
        switch (dir2[i]){//Ma duc pe o directie random, daca nu ies din matrice si nici nu am mai fost pe acolo, sparg zidul
            case 1: //SUS
                if(x!=1&&maze[x-2][y]==0)//Schema ca cpp-ul nu mai verifica a doua conditie daca prima e falsa si nu-mi moare programul
                    gen(x,y,1);
                break;
            case 2: //JOS
                if(x!=DIMENSION-2&&maze[x+2][y]==0)
                    gen(x,y,2);
                break;
            case 3: //STANGA
                if(y!=1&&maze[x][y-2]==0)
                    gen(x,y,3);
                break;
            case 4: //DREAPTA
                if(y!=DIMENSION-2&&maze[x][y+2]==0)
                    gen(x,y,4);
                break;




        }
    }





}

