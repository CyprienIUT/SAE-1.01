#include <stdio.h>
#include <stdlib.h>
const int STOP = -1;
const int ZERO = 0;
int main()
{
    int sommeNb = 0;
    int nbEntiers = 0;
    float moyenne;
    int entierCourant;

    printf("Entrer votre première valeur (-1 pour arrêter) : ");
    scanf("%d",entierCourant);

    while(entierCourant != STOP) {
        sommeNb = sommeNb + entierCourant;
        nbEntiers++;
        printf("Entrer une valeur (-1 pour arrêter) : ");
        scanf("%d",entierCourant);
    }

    if(nbEntiers == ZERO){
        printf("pas de moyenne\n");
    }
    else {
        moyenne = sommeNb / nbEntiers * 1.0;
        printf("\nMoyenne = %.2f\n\n", moyenne);
    }


    
    return EXIT_SUCCESS;
}