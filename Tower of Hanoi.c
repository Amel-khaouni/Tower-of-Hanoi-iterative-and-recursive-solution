#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "createtab.h"
#include <math.h>

clock_t t1;
clock_t t2;
double temp;
int **jeu = NULL;
int *sommets = NULL;

FILE *fp;

void deplacer(int a, int b)
{
    sommets[b] = sommets[b] + 1;
    jeu[b][sommets[b]] = jeu[a][sommets[a]];
    jeu[a][sommets[a]] = 0;
    sommets[a] = sommets[a] - 1;
}

void interchanger(int a, int b)
{
    if (jeu[b][sommets[b]] > jeu[a][sommets[a]])
    {
        deplacer(a, b);
    }
    else
    {
        deplacer(b, a);
    }
}

void afficher_tours(int **jeu, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", jeu[j][n - i - 1]);
        }
        printf("\n");
    }
}

void tour_hanoi(int n, int i, int j, int avant, int vide, int apres)
{

    if (i == j)
    {
        deplacer(avant, apres);
        /*afficher_tours(jeu, n);
        printf("\n \n");*/
    }
    else
    {
        if (i > j)
        {

            tour_hanoi(n, i - 1, j, avant, apres, vide);
            deplacer(avant, apres);
            /*afficher_tours(jeu, n);
            printf("\n \n");*/
            tour_hanoi(n, i - 1, j, vide, avant, apres);
        }
    }
}

void tour_hanoi_iterative(int n)
{
    int a = (n + 1) % 2 + 1;
    int b = n % 2 + 1;
    int iter = pow(2, n) - 1;
    for (int i = 1; i <= iter; i++)
    {
        if (i % 3 == 2)
        {
            interchanger(0, a);
        }
        if (i % 3 == 1)
        {
            interchanger(0, b);
        }
        if (i % 3 == 0)
        {
            interchanger(1, 2);
        }
        /*afficher_tours(jeu, n);
        printf("\n \n");*/
    }
}

int verification(int n){
    for(int i=0;i<n;i++){
     if(jeu[2][i]!=n-i){
        return(0);
     }
    }
    return(1);
}

int main()
{
    int verif;
    double temps;
    int nbr = 0;
    for(int test=3;test<=30;test++){
    nbr = test;
    jeu = (int **)malloc(3 * sizeof(int *));
    sommets = (int *)malloc(3 * sizeof(int));
    for (int i = 0; i < 3; i++)
    {
        jeu[i] = (int *)malloc(nbr * sizeof(int));
        if (i == 0)
        {

            for (int j = 0; j < nbr; j++)
            {
                jeu[0][j] = nbr - j;
            }
            sommets[0] = nbr - 1;
        }
        else
        {
            sommets[i] = -1;
            for (int j = 0; j < nbr; j++)
            {
                jeu[i][j] = 0;
            }
        }
    }
    /*afficher_tours(jeu, nbr);*/
    printf("\n \n");
    t1=clock();
    tour_hanoi(nbr, nbr, 1, 0, 1, 2);
    //tour_hanoi_iterative(nbr);
    t2=clock();
    temps = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("le temps d'execution pour n=%d est %Lf \n",nbr,temps);
    t1=clock();
    verif=verification(nbr);
    t2=clock();
    temps = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("l'algorithme de verification retourne %d avec un temps d'execution %Lf \n",verif,temps);
    
    
    free(jeu);
    jeu=NULL;
    free(sommets);
    sommets=NULL;

    /*printf("-----------\n\n\n\n");*/
    }
}
