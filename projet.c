#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define N 28


//procédure envoyée par le prof permettant de vider le buffer (utilisée après chaque scanf)
void viderBuffer()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
}



//cette fonction prend en valeur le code ascii de la lettre rentrée par l'utilisateur et lui retire 64 car l'alphabet commence par A=65
//Cela permet d'obtenir la coordonnée de la colonne dans le tableau
int conversion (char lettre) 
{									
	int res = lettre-64;									
	return res;
}


//procédure initialise les tableaux en 28*28. Ensuite, on utilisera seulement la partie du tableau qui nous intéresse
void init (int plateau[N][N]) 
{								
	for (int i=0;i<N;i++) {
		for (int j=0;j<N;j++) {
			plateau[i][j] = 0;	
		}
	}	
}


//procécure affichant les tableaux, interprétant les données brutes en caractères plus "lisibles" avec des couleurs
//ecrit la premiere lettre avec du decalage pour qu'elle soit au dessus de la colonne
void affiche(int plateau[N][N], int n) 
{					
	printf("       A ");									
	for (int i=2;i<n+1;i++) {
		printf("  %c ",65+i-1);
	}
	printf("\n");
	
	
	for (int i=1;i<n+1;i++) {								
		if (i<10) {
			printf("  %d  ",i);
		}
		else {
			printf("  %d ",i);
		}
		for (int j=1;j<n+1;j++) {
			if (plateau[i][j]==0) {
				printf("\033[44;01m| ~ \033[00m");
			}
			else {
				if (plateau[i][j]==1) {
					printf("\033[47;01m| ~ \033[00m");
				}
				else {
					if (plateau[i][j]==2) {
						printf("\033[46;01m| B \033[00m");
					}
					else {
						printf("\033[41;01m| X \033[00m");
					}
				}
			}
		}
		printf("| \n");
	}
}


//determine si la partie est finie en scannant le plateau pour vérifier qu'il n'y a plus de bateaux
int verifGagne (int plateau[N][N], int n) 
{				
	int verif = 1;
	
	for (int i = 1; i<n+1; i++) {
		for (int j = 1; j<n+1; j++) {
			if (plateau[i][j] == 2) {
				verif = 0;
			}
		}
	}
	return verif;
}


//écran de transition qui annonce qui va jouer pour que l'autre ne voit pas son plateau
void transition (int joueur) {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	if (joueur == 1) {printf("                      Au tour du \033[34;01mjoueur %c\033[00m !\n", joueur+64);}
	if (joueur == 2) {printf("                      Au tour du \033[31;01mjoueur %c\033[00m !\n", joueur+64);}
	if (joueur == 3) {printf("                      Au tour de l'\033[31;01mIA\033[00m !\n");}
	printf("\n\n\n\n\n\n\n\n\n");
	printf("Appuyez sur Entrée pour continuer\n");
	while(getchar() != '\n');
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


//procedure qui demande à l'utilisateur où il souhaite placer son bateau,
//verifie qu'il peut être poser à cet endroit, et le place dans le plateau
void placerbateau (int plateau[N][N], int taille, int n) {				
																		
	int VERIF = 1;
	int verif;
	int colonne;
	int ligne;
	int direction;	
	
	while (VERIF !=0)
	{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPlacez votre bateau de taille %d !\n\n",taille);
	affiche (plateau,n);
	verif = 1;
				
	while (verif !=0) 
	{
		printf("\nSaisissez la colonne (entre A et %c) : \n",n+64);				//l'utilisateur rentre la colonne en lettre capitale
		char lettre;
		scanf("%c",&lettre);
		viderBuffer();
		colonne = conversion(lettre);
		if ( 0 < colonne && colonne < n+1 ) 
		{
			verif = 0;	
		}		
		else 
		{
			printf("ERREUR : VEUILLEZ SAISIR UNE LETTRE ENTRE 'A' ET '%c' \n",n+64);
		}
	}
	
	verif = 1;
	while ( verif !=0) 
	{
		printf("Saisissez la ligne (entre 1 et %d) : \n",n);					//l'utilisateur rentre la ligne en chiffre
		scanf("%d",&ligne);
	
		if ( 0 < ligne && ligne < n+1 ) 
		{
			verif = 0;			
		} 
		else 
		{
			printf("ERREUR : VEUILLEZ SAISIR UN NOMBRE ENTRE 1 ET %d \n",n);
		}
	}
	
	verif = 1;
	while (verif !=0) 
	{
		printf("Voulez-vous placer le bateau horizontalement (rentrer 0) ou verticalement (rentrer 1) ? \n");			//il choisit la direction du bateau
		scanf("%d",&direction);
		viderBuffer();
		if ( direction != 0 && direction != 1) 
		{ 
			printf("ERREUR : RECOMMENCER \n");
		} 
		else 
		{
			verif = 0;
		}
	}
	
	if ( direction == 0 ) 												//ce bloc de conditions "if" vérifie que le bateau peut être posé, dans le cas horizontal, puis vertical
	{
		if (taille + colonne > n+1) {verif = 1;}						//vérifie que le bateau ne dépasse pas de la grille
		for (int i = colonne - 1; i < taille + colonne + 1; i++)		
		{
			for (int j = ligne -1; j < ligne + 2; j++)
			{
				if (plateau [j][i] == 2 )								//vérifie tout autour du bateau qui va être posé s'il y en un ou non, 
				{														//pour éviter une superposition et respecter le couloir d'eau
					verif = 1;
				}
			}
		}
	}
	else
	{
		if (taille + ligne > n+1) {verif = 1;}
		for (int i = ligne - 1; i < taille + ligne + 1; i++)
		{
			for (int j = colonne -1; j < colonne + 2; j++)
			{
				if (plateau [i][j] == 2 )
				{
					verif = 1;
				}
			}
		}
	}
	
	if (verif == 1)
	{
		printf("ERREUR : Le bateau est mal placé ! Faites attention au couloir d'eau et à ne pas superposer les bateaux ! \n");
		printf("\nAppuyez sur Entrée pour continuer\n");
		while(getchar() != '\n');
	}
	else
	{
		VERIF = 0;
	}
	}

	if ( direction == 0 ) {
		for (int i=colonne; i<taille+colonne;i++) {
			plateau[ligne][i] = 2;										//place le bateau dans le tableau
		}
	}
	if ( direction == 1 ) {
		for (int i=ligne; i<taille+ligne;i++) {
			plateau[i][colonne] = 2;									//place le bateau dans le tableau
		}
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVoici votre grille :\n\n");
	affiche(plateau,n);
	
	printf("\nAppuyez sur Entrée pour continuer\n");
	while(getchar() != '\n');
}


//procédure qui s'ocuppe de placer aléatoirement les bateaux dans la grille de l'IA
void placerbateauIA (int plateau[N][N], int taille, int n) {			
	
	int VERIF = 1;
	int verif;
	int colonne;
	int ligne;
	int direction;
	
	
	while (VERIF !=0)
	{
	direction = rand() % 2;												//choisis la direction aléatoirement
	if (direction == 0) {
		int nombre = n-taille +1;
		colonne = rand() % nombre ;										//choisis la colonne aléatoirement
		colonne = colonne + 1;
		ligne = rand() % n ;											//choisis la ligne aléatoirement
		ligne = ligne +1;
	} else {
		int nombre = n-taille +1;
		ligne = rand() % nombre;										//choisis la ligne
		ligne = ligne +1;
		colonne = rand() % n;											//colonne
		colonne++;
	}
	
	verif = 0;
	
	if ( direction == 0 ) 												//même vérifivations que pour "placerbateau"
	{
		if (taille + colonne > n+1) {verif = 1;}
		for (int i = colonne - 1; i < taille + colonne + 1; i++)
		{
			for (int j = ligne -1; j < ligne + 2; j++)
			{
				if (plateau [j][i] == 2 )
				{
					verif = 1;
				}
			}
		}
	}
	else
	{
		if (taille + ligne > n+1) {verif = 1;}
		for (int i = ligne - 1; i < taille + ligne + 1; i++)
		{
			for (int j = colonne -1; j < colonne + 2; j++)
			{
				if (plateau [i][j] == 2 )
				{
					verif = 1;
				}
			}
		}
	}
	
	if (verif == 1)
	{
		//printf("ERREUR : Le bateau est mal placé ! Faites attention au couloir d'eau et à ne pas superposer les bateaux ! \n");
		//printf("\nAppuyez sur Entrée pour continuer\n");
		//while(getchar() != '\n');
	//	sleep(1);										//si les random s'enchainent sans latence, il se peut que la valeur aléatoire ne change pas, d'où le sleep
		srand(time(NULL));
		
	}
	else
	{
		VERIF = 0;
	}
	}

	if ( direction == 0 ) {									//place le bateau comme dans "placerbateau"
		for (int i=colonne; i<taille+colonne;i++) {
			plateau[ligne][i] = 2;
		}
	}
	if ( direction == 1 ) {
		for (int i=ligne; i<taille+ligne;i++) {
			plateau[i][colonne] = 2;
		}
	}
	//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVoici votre grille :\n\n");
	//affiche(plateau,n);
	
	//printf("\nAppuyez sur Entrée pour continuer\n");
	//while(getchar() != '\n');
}


//sauvegarde les données de la partie en cours dans un fichier save.txt (la taille des plateaux, les plateaux des joueurs, les grilles de tir et s'il s'agit d'une partie contre IA)
void Sauvegarde(int A,int plateauJ1[N][N],int ennemiJ1[N][N], int plateauJ2[N][N], int ennemiJ2[N][N], int ia) { 
	
	int nb;
	nb=0;
	if (A>9) { // si le plateau fait plus de 9*9 cases, on met une variable à 1 pour le chargement plus tard
	nb=1;	
	}
	
	FILE *fichier = NULL;
	fichier = fopen("save.txt","w");

	if(fichier != NULL) {
		fprintf(fichier,"%d",nb);
		
		fprintf(fichier,"%d",A);// la taille du plateau
		
		fprintf(fichier,"%d", ia); // 1 pour ia et  0 pour joueur*

		for (int i=0;i<N;i++) {
			for (int j=0;j<N;j++) {
				fprintf(fichier, "%d", plateauJ1[i][j]);
			}
		}
		
		//fprintf(fichier,"\n");
		for (int i=0;i<N;i++) {
			for (int j=0;j<N;j++) {
				fprintf(fichier, "%d", ennemiJ1[i][j]);
			}
		}
		
		//fprintf(fichier,"\n");
		for (int i=0;i<N;i++) {
			for (int j=0;j<N;j++) {
				fprintf(fichier, "%d", plateauJ2[i][j]);
			}
		}
		
		//fprintf(fichier,"\n");
		for (int i=0;i<N;i++) {
			for (int j=0;j<N;j++) {
				fprintf(fichier, "%d", ennemiJ2[i][j]);
			}
		}

//on rentre tous les plateaux les un derrières les autres


		fclose(fichier);
	
	}
	

	//exit(1);
}


//fonction qui demande à l'utilisateur les coordonnées du tir, et qui change l'état de la case touchée. retourne 1 ou 0
int tir(int plateau[N][N], int ennemi[N][N], int n)			
{
	int VERIF = 1;
	int verif;
	int colonne;
	int ligne;
	int gagne;
	
	while (VERIF !=0)
	{
	verif = 1;
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nLes canons sont armés ! Choisissez où tirer !\n\n");
	affiche(ennemi,n);								//affiche la grille de tir
	
	while (verif !=0) 
	{
		printf("\nSaisissez la colonne (entre A et %c) : \n",n+64);
		char lettre;
		scanf("%c",&lettre);										//saisi de la colonne
		viderBuffer();
		colonne = conversion(lettre);
		if ( 0 < colonne && colonne < n+1 ) 
		{
			verif = 0;	
		}		
		else 
		{
			printf("ERREUR : VEUILLEZ SAISIR UNE LETTRE ENTRE 'A' ET '%c' \n",n+64);
		}
	}
	
	
	verif = 1;
	while ( verif !=0) 
	{
		printf("Saisissez la ligne (entre 1 et %d) : \n",n);
		scanf("%d",&ligne);										//saisi de la ligne
	
		if ( 0 < ligne && ligne < n+1 ) 
		{
			verif = 0;			
		} 
		else 
		{
			printf("ERREUR : VEUILLEZ SAISIR UN NOMBRE ENTRE 1 ET %d \n",n);
		}
	}
	
	switch (plateau[ligne][colonne]) {						//traite les differents cas : si le joueur touche un bateau, tire dans l'eau, tire sur une case déjà touchée

	case 0 :
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVous avez tiré dans l'eau \n\n");
		plateau[ligne][colonne] = 1;
		ennemi[ligne][colonne] = 1;
		VERIF = 0;										//si il tire dans l'eau, la boucle s'arrete
	break;

	case 1 :											//s'il tire sur case déjà touchée, il relance un tir
	case 3 :
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVous avez déjà tiré sur cette case, recommencez ! \n\n");
	break;

	case 2 :											//s'il tire sur un bateau
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nTouché ! Vous avez touché un bateau ! ");
		plateau[ligne][colonne] = 3;
		ennemi[ligne][colonne] = 3;
		gagne = verifGagne(plateau,n);									//on vérifie qu'il reste des bateaux ennemis
		if (gagne == 1) {
			printf("\n\nElimination totale des bateaux ennemis ! Fin de la partie. \n\n");	//s'il n'y en a plus, fin de la boucle, la fonction retourne 1
			VERIF = 0;
		} else {
			printf("Vous rejouez !\n\n");												//s'il en reste, il rejoue
		}
	break;

	//default:
		
	}
	affiche(ennemi,n);
	
	printf("\nAppuyez sur Entrée pour continuer\n");
	while(getchar() != '\n');
	
	viderBuffer();
	}
	return gagne;					//on retourne 0 par défaut, ce qui fait continuer la partie, ou 1 qui signifie la fin de la partie, les bateaux adverses sont coulés
}


//meme fonction que "tir, sauf que les cases sont choisis par l'IA
int tirIA(int plateau[N][N], int ennemi[N][N], int n)				
{
	int VERIF = 1;
	int colonne;
	int ligne;
	int gagne;
	int ite = 0;
	int val=0;
	
	while (VERIF !=0)
	{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nLes canons sont armés ! L'\033[31;01mIA\033[00m va tirer !\n\n");
	affiche(ennemi,n);
	
	printf("\nAppuyez sur Entrée pour continuer\n");
	while(getchar() != '\n');
	
	if (ite == 0) {
	
		ligne = rand () % n+1;										//au premier tir, l'IA est full random
		colonne = rand () % n+1;
		
	} else {														//si elle touche un bateau, l'IA tire sur une case adjacente
		switch (ite) {
			
			case 1:
				if (ligne == 1) {									//pour éviter que l'IA tire au delà de la bordure
					ligne = ligne +1;
					ite = 2;						//à la prochaine boucle, l'IA ne tirera pas sur la case qu'elle a touchée à la boucle d'avant
				} else {
					ligne = ligne -1;
				}
			break;
			
			case 2:
				if (ligne == n) {									//pour éviter que l'IA tire au delà de la bordure
					ligne = ligne - 1;
					ite = 1;
				} else {
					ligne = ligne + 1;
				}				
			break;
			
			case 3:
				if (colonne == 1) {									//pour éviter que l'IA tire au delà de la bordure
					colonne = colonne +1;
					ite = 4;
				} else {
					colonne = colonne - 1;
				}
			break;
			
			case 4:
				if (colonne == n) {									//pour éviter que l'IA tire au delà de la bordure
					colonne = colonne -1;
					ite = 3;
				} else {
					colonne = colonne +1;
				}
				
			break;
		}
		
		
	}
	
	switch (plateau[ligne][colonne]) {							//les mêmes cas que pour "tir"

	case 0 :
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nL'\033[31;01mIA\033[00m a tiré dans l'eau \n\n");
		plateau[ligne][colonne] = 1;
		ennemi[ligne][colonne] = 1;
		VERIF = 0;
	break;

	case 1 :
	case 3 :
		ite =0;
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nL'\033[31;01mIA\033[00m a déjà tiré sur cette case, elle va recommencer ! \n\n");
	break;

	case 2 :
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nTouché ! L'\033[31;01mIA\033[00m a touché un bateau ! ");
		plateau[ligne][colonne] = 3;
		ennemi[ligne][colonne] = 3;
		gagne = verifGagne(plateau,n);	
		if (gagne == 1) {
			printf("\n\nElimination totale des bateaux du \033[34;01mjoueur\033[00m ! Fin de la partie. \n\n");
			VERIF = 0;
		} else {					
			printf("L'\033[31;01mIA\033[00m rejoue !\n\n");
			
			val++;
			
			if (val == 1) {			//l'IA rejoue en choisissant au hasard une case adjacente à celle touchée
				ite = rand() % 4 +1;
			}						//si c'est la deuxième fois (ou plus) qu'elle touche, la direction de tir ne change pas
		}
	break;

	//default:
		
	}
	affiche(ennemi,n);
	
	printf("\nAppuyez sur Entrée pour continuer\n");
	while(getchar() != '\n');
	
	}
	return gagne;				//retourne 1 ou 0 comme pour "tir"
}


//gère la partie en fonction des paramètres
void JcJ (int tab[40], int n, int nbrbateau, int plateauA[N][N], int plateauB[N][N], int ennemiA[N][N], int ennemiB[N][N], int charge) {	
	int verif = 0;
	
	//int save;
	
	if (charge == 0) {								//appelle la procédure placerbateau seulement s'il s'agit d'une nouvelle partie
		transition(1);								//au tour du joueur A
		for (int i =0; i<nbrbateau; i++) {			//placerbateau ne place qu'un bateau, on l'appelle donc autant de fois qu'il y a de bateaux à placer
			placerbateau(plateauA, tab[i], n);
		}
	
		transition(2);								//au tour du joueur B de placer ses bateaux
		for (int i = 0; i<nbrbateau; i++) {
			placerbateau(plateauB, tab[i], n);
		}
	}
	
	while (verif !=1) {					//une boucle = les 2 joueurs tirent = un tour
		transition(1);								//joueur A
		
		printf("Voici votre grille : \n\n");		//affiche la grille du joueur pour voir l'avancée de la partie
		affiche(plateauA,n);
		
		printf("\nAppuyez sur Entrée pour continuer\n");
		while(getchar() != '\n');
		
		verif = tir(plateauB, ennemiB,n);				//le joueur A tire
		
		if (verif == 1) {printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          Le \033[34;01mJoueur A\033[00m a gagné la partie !\n\n\n\n\n\n\n\n");}
		
		if (verif !=1) {							// si le tir renvoie 1, c'est la fin de la parti, le joueur A a gagné. sinon, c'est au tour du joueur B
			transition(2);
			
			printf("Voici votre grille : \n\n");
			affiche(plateauB,n);
			
			printf("\nAppuyez sur Entrée pour continuer\n");
			while(getchar() != '\n');
			
			verif = tir(plateauA, ennemiA,n);			//le joueur B tire
			
			if (verif == 1) {printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          Le \033[31;01mJoueur B\033[00m a gagné la partie !\n\n\n\n\n\n\n\n");}
		}		//si le tir renvoie 1, B a gagné, fin de la partie, sinon, la boucle continue
		
		
		if (verif != 1) {			//tant que la partie n'est pas finie, on sauvegarde automatiquement à chaque fin de tour
			Sauvegarde(n,plateauA,ennemiA,plateauB,ennemiB,0);
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nSauvegarde automatique effectuée !\n");
			
			printf("\nAppuyez sur Entrée pour continuer\n");
			while(getchar() != '\n');
		}
	}
	
}


//gère la partie contre l'IA
void JcIA (int tab[40], int n, int nbrbateau, int plateauA[N][N], int plateauB[N][N], int ennemiA[N][N], int ennemiB[N][N], int charge) { 
	int verif = 0;
	
	//int save;
	
	if (charge == 0) {				//placerbateau seulement si nouvelle partie
		transition(1);
		for (int i =0; i<nbrbateau; i++) {
			placerbateau(plateauA, tab[i], n);
		}
	
		transition(3);
	
		printf("Veuillez attendre pendant que l'ordinateur place ses bateaux. Cela peut être plus ou moins long.\n");
	
		for (int i = 0; i<nbrbateau; i++) {
			srand(time(NULL));
			placerbateauIA(plateauB, tab[i], n);
		//	sleep(1);		//à chaque fois que l'IA place un bateau, on laisse un peu de temps au random pour qu'il ne donne pas le même tirage
		}
	}
		
	//affiche (plateauB,n);							//affiche le plateau de l'IA. utile pour le debug
	
	//printf("\nAppuyez sur Entrée pour continuer\n");
	//while(getchar() != '\n');
	
	while (verif !=1) {			//une boucle = un tour
		transition(1);			//tour du joueur
		
		printf("Voici votre grille : \n\n");
		affiche(plateauA,n);
		
		printf("\nAppuyez sur Entrée pour continuer\n");
		while(getchar() != '\n');
		
		verif = tir(plateauB, ennemiB,n);			//tir du joueur
		
		if (verif == 1) {printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          Le \033[34;01mJoueur A\033[00m a gagné la partie !\n\n\n\n\n\n\n\n");}
		
		if (verif !=1) {		//si le joueur n'a pas gagné, au tour de l'ia
			transition(3);
			
			//printf("Voici votre grille : \n\n");
			//affiche(plateauB,n);								//affiche la grille de l'IA, utile pour le debug
			
			//printf("\nAppuyez sur Entrée pour continuer\n");
			//while(getchar() != '\n');
			
			verif = tirIA(plateauA, ennemiA,n);				//tir de l'ia
			
			if (verif == 1) {printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          L'\033[31;01mIA\033[00m a gagné la partie !\n\n\n\n\n\n\n\n");}
		}//si l'ia gagne, fin de la partie
		//sinon, sauvegarde automatique et tour suivant	
		if (verif != 1) {
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nSauvegarde automatique effectuée !\n");
		
			Sauvegarde(n,plateauA,ennemiA,plateauB,ennemiB,1);
			
			printf("\nAppuyez sur Entrée pour continuer\n");
			while(getchar() != '\n');
		}
	}
}


//charge la partie à partir de save.txt
void Charger(int A,int plateauJ1[N][N],int ennemiJ1[N][N], int plateauJ2[N][N], int ennemiJ2[N][N], int ia){		
	int tab[2];
	int nb;
	int test;
	nb=0;
	test=0;
	
	FILE *fichier = NULL;
	fichier = fopen("save.txt","r"); //ouvre le fichier en lecture 
	nb=fgetc(fichier)-48; //lecture du premier caractère, problème le caractère ce faisait lire en ascii (pour le 1 nous obtenons 49) donc nous enlevons 48 pour obtenir les bonnes valeurs
	//fgetc(fichier);

	if (nb==1){ //si la taille du plateau est supérieur a 9 le programme va lire deux caractère puis faire en sorte de lire la première en dizaine et d'additionner les deux 
		test=fgetc(fichier)-48;
		test=test*10;
	}
	
	A=fgetc(fichier)-48;
	A=A+test;

	ia=fgetc(fichier)-48;  // 1 pour ia et  0 pour joueur*

	//printf("%d",ia);

	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			plateauJ1[i][j]=fgetc(fichier)-48;
		}
	}

	fprintf(fichier,"\n");
	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			ennemiJ1[i][j]=fgetc(fichier)-48;
		}
	}
	
	fprintf(fichier,"\n");
	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			plateauJ2[i][j]=fgetc(fichier)-48;
		}
	}
	
	fprintf(fichier,"\n");
	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			ennemiJ2[i][j]=fgetc(fichier)-48;

//lecture des enregistrements pour les différents plateaux de jeux
		}
	}
	
	if (ia==0){
		JcJ(tab,A,10, plateauJ1, plateauJ2, ennemiJ1, ennemiJ2,1);
	} else {
		JcIA(tab,A,10, plateauJ1, plateauJ2, ennemiJ1, ennemiJ2,1);
	}
}


//le main initialise tous les tableaux
int main() {			
	
	int choix;
	int choix2;
	int n;
	int nbrbateau;
	int tab[40];
	int ia;
	int taille;
	
	
	int plateauA[N][N];
	int ennemiA[N][N];
	int plateauB[N][N];
	int ennemiB[N][N];
	init(plateauA);
	init(ennemiA);
	init(plateauB);
	init(ennemiB);
	
	//le menu :
	
	printf("o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°\n");
	printf("o°o°o°o°o°o°o°o°o°o°o°o°o° \033[31;01mBATAILLE NAVALE\033[00m °o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°\n");
	printf("o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°o°\n");
	
	printf("\n\n\nMenu : faites votre choix en rentrant le chiffre correspondant !\n");
	printf("\n	1. \033[34;01mJoueur\033[00m contre \033[31;01mJoueur\033[00m (paramètres standards)\n");
	printf("	2. \033[34;01mJoueur\033[00m contre \033[31;01mIA\033[00m (paramètres standards)\n");
	printf("	3. Partie Personalisée\n");
	printf("	   Rentrez n'importe quelle autre touche pour quitter le programme\n");
	
	scanf("%d",&choix);				//l'utilisateur rentre son choix
	viderBuffer();
	
	switch (choix) {
		
	case 1:				//partie standard JcJ : plateaux : 10*10, 10 bateaux et taille des bateaux suivantes :
		tab[0] = 6;
		tab[1] = 4;
		tab[2] = 4;
		tab[3] = 3;
		tab[4] = 3;
		tab[5] = 3;
		tab[6] = 2;
		tab[7] = 2;
		tab[8] = 2;
		tab[9] = 2;
		JcJ(tab,10,10, plateauA, plateauB, ennemiA, ennemiB,0);
	break;
	
	case 2:				// partie standard JcIA
		tab[0] = 6;
		tab[1] = 4;
		tab[2] = 4;
		tab[3] = 3;
		tab[4] = 3;
		tab[5] = 3;
		tab[6] = 2;
		tab[7] = 2;
		tab[8] = 2;
		tab[9] = 2;
		JcIA(tab,10,10, plateauA, plateauB, ennemiA, ennemiB,0);
	break;
	
	case 3:			//sous-menu :
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("Partie personnalisée :\n");
		printf("\n	1. Lancer la personnalisation des paramètres\n");
		printf("	2. Charger partie\n");
		printf("	   Rentrez n'importe quelle autre touche pour quitter le programme\n");
		
		scanf("%d",&choix2);		//sélection du choix 2
		viderBuffer();
		
		switch(choix2) {
			
		case 1:		//création de la partie perso
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPartie en cours de personnalisation !\n");
			ia = 2;
			while (ia !=0 && ia != 1) {
				printf("\nMode \033[34;01mJoueur\033[00m contre \033[31;01mJoueur\033[00m (rentrez 0) ou \033[34;01mJoueur\033[00m contre \033[31;01mIA\033[00m (rentrez 1) ?\n");
				scanf("%d",&ia);			//choix de JcJ ou JcIA
				viderBuffer();
			}
			n = 0;
			while (n > 26 || n < 1) {
				printf("Choisir la taille du plateau de jeu (min : 1 max : 26) :\n");
				scanf("%d",&n);			//choix de la taille du plateau (entre 1 et 26)
				viderBuffer();
			}
			nbrbateau = 0;
			while (nbrbateau > 40 || nbrbateau <1) {
				printf("Choisir le nombre de bateau :\n");
				scanf("%d",&nbrbateau);			//choix du nombre de bateaux
				viderBuffer();
			}
			for (int i=0; i<nbrbateau; i++) {
				printf("Rentrez la taille du bateau %d :\n",i+1);
				scanf("%d",&taille);		//choix de la taille de chaque bateaux
				viderBuffer();
				tab[i]=taille;
			}
			if (ia == 0) {		//lance la partie perso JcJ
				JcJ(tab,n,nbrbateau, plateauA, plateauB, ennemiA, ennemiB,0);
			}
			if (ia == 1) {		//lance la partie perso JcIA
				JcIA(tab,n,nbrbateau, plateauA, plateauB, ennemiA, ennemiB,0);
			}
		break;
		
		case 2:		//charge une partie à partir de save.txt
			Charger(n,plateauA,ennemiA,plateauB,ennemiB,ia);
			
			exit(1);
		break;
		
		default : exit(1);
		}
		
	break;
		
	default : exit(1); //quitte le programme si l'utilisateur ne choisis aucune des propositions
	}
	
	return 0;
}


/*
0 = vide

1 = vide touché

2 = bateau

3 = bateau touché
*/
