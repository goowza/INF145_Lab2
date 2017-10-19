#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotheque.h"
#include <time.h>

int main()
{
	// Déclaration des variables.
	// ...
	int choix_menu;

	t_bibliotheque bibli;

	// Initialisation de la fonction rand()
	srand(time(NULL));

	// Initialisation de la bibliotheque
	// ...
	afficher_menu();
	choix_menu = demander_choix_menu();
	initialiser_bibliotheque(&bibli);
	simuler_lire_fichier(&bibli);
	afficher_bibliotheque(&bibli);
	modifier_livre(&bibli.livres[5][0]);
	afficher_bibliotheque(&bibli);
	system("PAUSE");
    /*do
    {
		// Gestion du menu.
        choix_menu = demander_choix_menu();

        switch(choix_menu)
        {
            case 1: afficher_bibliotheque(&bibli); break;
            case 2: lire_fichier(&bibli); break;
            case 3: modifier_livre(&bibli); break;
			case 4: retirer_livre(&bibli); break;
            case 5: emprunter_livre(&bibli); break;
            case 6: gerer_retours(&bibli); break;
            case 7: generer_rapport(&bibli); break;
            case 8: sauvegarder_fichier(&bibli); break;        
			case 9: trier_livres(&bibli); break;
			case 0: break; // Quitter.
            default: break;
        }
    }while(choix_menu != 0);*/
    
    return EXIT_SUCCESS;
}

void lire_fichier(t_bibliotheque * pBibli)
{
	// ...

#if(SIMULATION == 1)
    simuler_lire_fichier(pBibli);
	
	// ...

#else
    
	// ...
    
#endif

	// ...
}

void simuler_lire_fichier(t_bibliotheque * pBibli)
{
	t_livre livre1;
	t_livre livre2;
	t_livre livre3;

	livre1.genre = INFORMATIQUE;
	strcpy(livre1.titre, "Les Ninjas de l'Info 2");
	strcpy(livre1.auteur_prenom, "Yannick");
	strcpy(livre1.auteur_nom, "Roy");
	livre1.nb_pages = 252;
	livre1.isbn = 369;
	livre1.bEmprunte = DISPONIBLE;
	pBibli->livres[INFORMATIQUE][pBibli->nb_livres[INFORMATIQUE]] = livre1;
	pBibli->nb_livres[INFORMATIQUE]++;

	livre2.genre = INFORMATIQUE;
	strcpy(livre2.titre, "Les fous du code");
	strcpy(livre2.auteur_prenom, "Hugues");
	strcpy(livre2.auteur_nom, "Saulnier");
	livre2.nb_pages = 355;
	livre2.isbn = 1001;
	livre2.bEmprunte = DISPONIBLE;
	pBibli->livres[INFORMATIQUE][pBibli->nb_livres[INFORMATIQUE]] = livre2;
	pBibli->nb_livres[INFORMATIQUE]++;

	livre3.genre = FICTION;
	strcpy(livre3.titre, "Un tableau de pointeurs");
	strcpy(livre3.auteur_prenom, "Pasdor");
	strcpy(livre3.auteur_nom, "Mi");
	livre3.nb_pages = 180;
	livre3.isbn = 1234;
	livre3.bEmprunte = DISPONIBLE;
	pBibli->livres[FICTION][pBibli->nb_livres[FICTION]] = livre3;
	pBibli->nb_livres[FICTION]++;
}

void super_pause()
{
	printf("Appuyez sur une touche pour continuer! \n");
	_getch();
}

void retirer_sautligne(char * chaine)
{
	int pos = strlen(chaine) - 1;
	if (chaine != NULL && chaine[pos] == '\n')
		chaine[pos] = '\0'; // Si on trouve \n à la fin, on le remplace par \0
}

//-----------------------------------------------------------------------------
//							Fonction Initialiser_bibliotheque
// Cette fonction initialise la bibliotheque en mettant tout les compteurs du 
// tableau nb_livres a 0, en remplissant toutes les cases du tableau 2D
// contenant les livres avec des livres initialises par la fonction 
// initialiser_livre et en initialisant le rapport avec la fonction 
// initialiser_rapport
//
// Parametres : pBibli = pointeur vers le t_bibliotheque que l'on veut initialiser
// Retour :		aucun
//-----------------------------------------------------------------------------
void initialiser_bibliotheque(t_bibliotheque * pBibli)
{
	int i,j;

	// Initialisation des compteurs de livres a 0
	for (i = 0; i < NB_GENRES; i++)
	{
		pBibli->nb_livres[i] = 0;
	}

	// Remplir tableau livres
	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
		{
			initialiser_livre(&pBibli->livres[i][j]);
		}
	}

	// Initialiser le rapport a 0
	initialiser_rapport(&(pBibli->rapport));
}

int demander_choix_menu()
{
	int choix;
	do
	{
		scanf("%d", &choix);
	} while (choix > 9 || choix < 0);

	return choix;
}

//-----------------------------------------------------------------------------
//							Fonction Initialiser_livre
// Cette fonction initialise un livre en mettant son genre a "AUCUN", 
// son isbn a -1, son nombre de pages a 0, le nom et prenom de l'auteur
// a "N/A", le titre du livre a "N/A" et son sa disponibilite a "DISPONIBLE"
//
// Parametres : pLivre = pointeur vers le t_livre que l'on veut initialiser
// Retour :		aucun
//-----------------------------------------------------------------------------
void initialiser_livre(t_livre * pLivre)
{
	pLivre->genre = AUCUN;
	pLivre->isbn = -1;
	pLivre->nb_pages = 0;
	strcpy(pLivre->auteur_nom, "N/A");
	strcpy(pLivre->auteur_prenom, "N/A");
	strcpy(pLivre->titre, "N/A");
	pLivre->bEmprunte = DISPONIBLE;
}

//-----------------------------------------------------------------------------
//							Fonction Initialiser_rapport
// Cette fonction initialise le rapport en mettant le nombre de livres total et
// le nombre de livres empruntes a 0
//
// Parametres : pRapport = pointeur vers le t_rapport que l'on veut initialiser
// Retour :		aucun
//-----------------------------------------------------------------------------
void initialiser_rapport(t_rapport * pRapport)
{
	pRapport->nb_livres = 0;
	pRapport->nb_livres_empruntes = 0;
}

void afficher_info_livre(t_livre * pLivre)
{
	printf("-------------------------------------------------------------------");
	printf("\nTitre : ");
	printf(pLivre->titre);
	printf("\nAuteur : ");
	printf(pLivre->auteur_prenom);
	printf(" ");
	printf(pLivre->auteur_nom);
	printf("\nGenre : %d",pLivre->genre);
	printf("\nPages : %d", pLivre->nb_pages);
	printf("\nISBN : %d", pLivre->isbn);
	printf("\nEmprunte : %d\n", pLivre->bEmprunte);
	printf("-------------------------------------------------------------------");
	printf("\n");
}

void modifier_livre(t_livre * pLivre)
{
	printf("Entrez le nouveau genre du livre : \n");
	scanf("%d",&pLivre->genre);
	printf("Entrez le nouveau titre du livre : \n");
	gets_s(pLivre->titre,TAILLE_TITRE); // Ne bloque pas :v
	printf("Entrez le nouveau prenom de l'auteur : \n");
	gets_s(pLivre->auteur_prenom,TAILLE_PRENOM);
	printf("Entrez le nouveau nom de l'auteur : \n");
	gets_s(pLivre->auteur_nom,TAILLE_NOM);
	printf("Entrez le nouveau nombre de page : \n");
	scanf("%d",&pLivre->nb_pages);
}

void sauvegarder_fichier(t_bibliotheque * pBibli)
{

}

void trier_livres(t_bibliotheque * pBibli)
{

}

void afficher_bibliotheque(t_bibliotheque * pBibli)
{
	int i,j;
	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
		{
			if (pBibli->livres[i][j].isbn != -1)
			{
				afficher_info_livre(&pBibli->livres[i][j]);
			}
		}
	}
}

void generer_rapport(t_bibliotheque *pBibli)
{

}

void emprunter_livre(t_bibliotheque * pBibli)
{

}

void gerer_retours(t_bibliotheque * pBibli)
{

}

void afficher_menu()
{
	printf("================================================================");
	printf("=============");
	printf("\n                             Bibliotheque 145 inc.\n");
	printf("================================================================");
	printf("=============\n");
	printf("1 - Afficher bibliotheque\n");
	printf("2 - Lire fichier bibliotheque\n");
	printf("3 - Modifier livre\n");
	printf("4 - Retirer livre\n");
	printf("5 - Emprunter livre\n");
	printf("6 - Retourner livres\n");
	printf("7 - Generer rapport\n");
	printf("8 - Sauvegarder bibliotheque\n");
	printf("9 - Trier livres\n");
	printf("0 - Quitter\n");
	printf("================================================================");
	printf("=============\n");
}
