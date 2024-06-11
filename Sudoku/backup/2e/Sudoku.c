/**
 * 
 * @brief Programme de Sudoku
 * @author ALBERT Cyprien
 * @version 1.0
 * @date 22 Novembre 2023
 * 
 * Ce programme permet de jouer au jeu du Sudoku, en insérant
 * des chiffres dans les cases afin de remplir la grille
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/**
 * 
 * @def POINT
 * @brief constante pour afficher les points de la grille
 * et utilisé dans la vérification de la présence d'un point
 * lors de la saisie
 * 
*/
#define POINT '.'

/**
 * 
 * @def TIRET
 * @brief constante pour afficher les tirets de la grille
 * 
*/
#define TIRET '-'

/**
 * 
 * @def BARRE
 * @brief constante pour afficher les barres de la grille
 * 
*/
#define BARRE '|'

/**
 * 
 * @def PLUS
 * @brief constante pour afficher les '+' de la grille
 * 
*/
#define PLUS '+'

/**
 * 
 * @def ZERO
 * @brief constante utiliser dans plusieurs procédures / fonctions
 * 
*/
#define ZERO 0

/**
 * 
 * @def UN
 * @brief constante utiliser dans plusieurs procédures / fonctions
 * 
*/
#define UN 1

/**
 * 
 * @def N
 * @brief constante définissant les dimensions des blocs et
 * de la grille
 * 
*/
#define N 3

/**
 * 
 * @def NB_LIGNES
 * @brief constante utiliser pour définir le nombre de
 * ligne de la grille
 * 
*/
#define NB_LIGNES 9

/**
 * 
 * @def NB_COLONNES
 * @brief constante utiliser pour définir le nombre de
 * colonnes de la grille
 * 
*/
#define NB_COLONNES 9

/**
 * 
 * @typedef Tgrille
 * @brief type tableau de taille NB_LIGNES * NB_COLONNES
 * 
 * Le type tGrille sert à stocker la grille de jeu
 * 
*/
typedef int Tgrille[NB_LIGNES][NB_COLONNES];

bool nomFichierValide(char[]);
void chargerGrille(Tgrille,bool*);
void afficheLigneSeparateur();
void afficherGrille(Tgrille);
bool pointPresent(char[]);
void saisir(int*);
bool possible(Tgrille, int, int, int);
bool grillePleine(Tgrille);
int nbElementsLigne(Tgrille,int);
int nbElementsColonne(Tgrille, int);

/**
 * 
 * @fn int main()
 * @brief Programme principal.
 * @return Code de sortie du programme : soit failure soit succes
 * 
 * Le programme principal génère un grille de jeu et tant que
 * la grille n'est pas pleine, il demande à l'utilisateur la
 * saisie des coordonnées pour saisir une valeur dans la grille
 * 
*/
int main() {
    Tgrille grilleJeu;
    int numLig, numCol, valeur;
    bool fichierValide;
    
    chargerGrille(grilleJeu, &fichierValide);
    if(fichierValide == true){
        while(!grillePleine(grilleJeu)){
            printf("\n");
            afficherGrille(grilleJeu);
            printf("Indices de la case ? \n");
            printf("Ligne : ");
            saisir(&numLig);
            numLig = numLig - 1; /** car décalage d'1*/
            printf("Colonne : ");
            saisir(&numCol);
            numCol = numCol - 1; /** car décalage d'1*/
            if(grilleJeu[numLig][numCol] != 0){
                printf("IMPOSSIBLE, la case n'est pas libre.\n");
            }
            else{
                printf("Valeur à insérer ? ");
                saisir(&valeur);
                if(possible(grilleJeu,numLig,numCol,valeur)){
                    grilleJeu[numLig][numCol] = valeur;
                }
            }
        }
        afficherGrille(grilleJeu);
        printf("Grille pleine, fin de partie\n");
        return EXIT_SUCCESS;
    } else{
        return EXIT_FAILURE;
    }
}

/**
 * 
 * @fn bool nomFichierValide(char nomFichier[])
 * @brief Fonction qui vérifie la validité du nom du fichier
 * @param nomFichier : paramètre d'entrée qui représente le nom du
 * fichier vérifié
 * @return true si le nom du fichier est correct, false sinon
 * 
*/
bool nomFichierValide(char nomFichier[]){
    bool estValide;
    if((strcmp(nomFichier,"Grille1.sud") == ZERO) ||
    (strcmp(nomFichier,"Grille2.sud") == ZERO) ||
    (strcmp(nomFichier,"Grille3.sud") == ZERO) ||
    (strcmp(nomFichier,"Grille4.sud") == ZERO) ||
    (strcmp(nomFichier,"Grille5.sud") == ZERO) ||
    (strcmp(nomFichier,"Grille6.sud") == ZERO) ||
    (strcmp(nomFichier,"Grille7.sud") == ZERO) ||
    (strcmp(nomFichier,"Grille8.sud") == ZERO) ||
    (strcmp(nomFichier,"Grille9.sud") == ZERO) ||
    (strcmp(nomFichier,"Grille10.sud") == ZERO)) {
        estValide = true;
    } else {
        estValide = false;
    }
    return estValide;
}   

/**
 * 
 * @fn void chargerGrille(Tgrille g).
 * @brief Procédure qui insère une grille de Sudoku initiale
 * dans la grille de jeu
 * @param g : paramètre d'entrée et de sortie qui représente
 * la grille à charger
 * @param fichierValide : paramètre de sortie qui indique si
 * le fichier est valide
 * Place le contenu d'un fichier Grille<nombre_entre_1_et_10_compris>.sud
 * dans la grille de jeu 
*/
void chargerGrille(Tgrille g,bool *fichierValide){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    if(nomFichierValide(nomFichier) == true){
        f = fopen(nomFichier, "rb");
    
        if (f==NULL){
            printf("\n ERREUR sur le fichier %s\n", nomFichier);
            *fichierValide = false;
        } else {
            fread(g, sizeof(int), NB_LIGNES*NB_COLONNES, f);
            *fichierValide = true;
            fclose(f);
        }
    } else{
        printf("Le fichier %s n'est pas valide\n",nomFichier);
        *fichierValide = false;
    }
}

/**
 * 
 * @fn void afficheLigneSeparateur()
 * @brief Procédure qui permet d'afficher les lignes de
 * séparations horizontales de la grille affichée
 *
*/
void afficheLigneSeparateur(){
    printf("   %c",PLUS);
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            printf("%c%c%c",TIRET,TIRET,TIRET);
        }
        printf("%c",PLUS);
    }
    
    printf("\n");
}

/**
 * 
 * @fn void afficherGrille(Tgrille g)
 * @brief Procédure qui permet d'afficher la grille
 * @param g : paramètre d'entrée qui représente la grille à afficher
 *
*/
void afficherGrille(Tgrille g){
    printf("     1  2  3   4  5  6   7  8  9\n");
    afficheLigneSeparateur();
    for(int i = 0; i < NB_LIGNES; i++){
        printf("%d  %c",i+1,BARRE);
        for(int j = 0; j < NB_COLONNES ; j++){
            if(g[i][j] == ZERO){
                printf(" %c ",POINT);
            }
            else{
                printf(" %d ",g[i][j]);
            }
            
            if((j+1)%N == ZERO){
                printf("%c (%d)",BARRE,nbElementsLigne(g,i));
            }
        }
        printf("\n");
        if((i+1)%N == ZERO){
            afficheLigneSeparateur();
        }
    }
    printf("    ");
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            printf("(%d)",nbElementsColonne(g,(i*N)+j));
        }
        printf(" ");
    }
    printf("\n");
}

/**
 * 
 * @fn bool pointPresent(char chaine[])
 * @brief Fonction qui vérifie la présence d'un point dans la
 * chaine de caractères de la procédure saisir
 * @param chaine : paramètre d'entrée qui représente la chaine
 * de caractères vérifiée
 * @return true s'il y a un point dans la chaine de caractères,
 * false sinon
 * 
 * La fonction permet de déterminer (dans le cas où la chaine
 * est un nombre) s'il s'agit d'un float ou non.
 * 
*/
bool pointPresent(char chaine[]){
    int i = 0;
    bool pointPresent = false;

    while((pointPresent == false) && (i < 20)){
        if(chaine[i] == POINT){
            pointPresent = true;
        }
        i++;
    }
    return pointPresent;
}

/**
 * 
 * @fn void saisir(int *adresseInt)
 * @brief Procédure qui permet d'insérer soit un numéro de ligne,
 * soit une colonne, soit le chiffre à placer dans la grille
 * @param adresseInt : paramètre de sortie qui représente le
 * numéro de colonne ou de ligne ou le numéro à placer
 *
*/
void saisir(int *adresseInt){
    char chaine[20];
    int saisie;

    scanf("%s",chaine);
    if((sscanf(chaine,"%d",&saisie) != ZERO) && (pointPresent(chaine) != true)) {
        if((saisie <= N*N) && (saisie > ZERO)){
            *adresseInt = saisie;
        }
        else{
            printf("La valeur saisie n'est pas compris entre 1 et 9.\n");
            saisir(adresseInt);
        }
    } else {
        printf("La valeur saisie n'est pas un entier.\n");
        saisir(adresseInt);
    }
    
}

/**
 * 
 * @fn bool possible(Tgrille g, int numLig, int numCol, int numIns)
 * @brief Fonction qui indique s'il est possible de placer le
 * numéro à insérer dans la grille au coordonnées en paramètre
 * @param g : paramètre d'entrée qui représente la grille de jeu
 * à modifier
 * @param numLig : paramètre d'entrée qui représente la ligne
 * de la grille du nombre à placer
 * @param numCol : paramètre d'entrée qui représente la colonne
 * de la grille du nombre à placer
 * @param numIns : paramètre d'entrée qui représente la valeur
 * à insérer dans la grille
 * @return true s'il est possible d'y placer le numéro à insérer,
 * false sinon
 * 
 * La fonction vérifie la présence du numéro à insérer sur la
 * ligne, colonne et bloc dans lequel il se trouve
 * 
*/
bool possible(Tgrille g, int numLig, int numCol, int numIns){
    bool estPossible = true;
    int baseLig = (numLig/N) * N;
    int baseCol = (numCol/N) * N;
    for (int i = 0 ; i < N*N ; i++){
        if(g[numLig][i] == numIns){
            estPossible = false;
            printf("%d est déjà présent sur la ligne.\n",numIns);
        }
        if(g[i][numCol] == numIns){
            estPossible = false;
            printf("%d est déjà présent sur la colonne.\n",numIns);
        }
    }
    for (int ligBloc = baseLig; ligBloc < baseLig + 3 ; ligBloc++){
        for(int colBloc = baseCol; colBloc < baseCol + 3 ; colBloc++){
            if(g[ligBloc][colBloc] == numIns){
                if((colBloc != numCol) && (ligBloc != numLig)){
                    estPossible = false;
                    printf("%d est déjà présent dans le bloc.\n",numIns);
                }
            }
        }
    }
    return estPossible;
}

/**
 * 
 * @fn bool grillePleine(Tgrille g)
 * @brief Fonction qui indique si la grille passée en paramètre
 * est pleine ou non (remplis de valeurs compris entre 1 et 9)
 * @param g : paramètre d'entrée qui représente la grille de jeu
 * à vérifier
 * @return true si la grille est pleine, false sinon
 * 
*/
bool grillePleine(Tgrille g){
    bool resultat = true;
    int lig = 0;
    int col = 0;

    while((resultat == true) && (lig < N*N)){
        while((resultat == true) && (col < N*N)){
            if(g[lig][col] == ZERO){
                resultat = false;
            }
            col++;
        }
        lig++;
        col = ZERO;
    }
    return resultat;
}

int nbElementsLigne(Tgrille g, int lig){
    int nbElementsLig = 0;
    for (int i = 0; i < N*N; i++){
        if(g[lig][i] != ZERO){
            nbElementsLig++;
        }
    }
    return nbElementsLig;
}

int nbElementsColonne(Tgrille g, int col){
    int nbElementsCol = 0;
    for (int i = 0; i < N*N; i++){
        if(g[i][col] != ZERO){
            nbElementsCol++;
        }
    }
    return nbElementsCol;
}