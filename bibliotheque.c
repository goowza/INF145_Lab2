//  Auteur:		Yannick Roy
//
//  Modifié par : Paul Meis (MEIP12039708) 
//				 (paul.meis.1@ens.etsmtl.ca)
//				  Hervé Neugang (NEUR14027708) 
//				 (rodrigu-herve.neugang-tchientche.1@ens.etsmtl.ca)

//  Date : novembre 2017
//
//  Description : 
//  Ce programme permet de gerer la banque de donnees d'une bibliotheque.
//  Le programme offre plusieurs fonctionnalites de gestion :
// 
//  1) Afficher Bibliothèque:     Affiche tous les livres de la bibliothèque. 
//  2) Lire Fichier Bibliothèque: Initialise la bibliothèque à partir d'un 
//								  fichier texte.
//  3) Modifier Livre:            Permet de modifier les informations (champs) 
//								  d'un livre. 
//  4) Retirer Livre:			  Permet de retirer un livre de la bibliothèque.
//  5) Emprunter Livre:			  Permet d'emprunter temporairement un livre. 
//  6) Retourner Livres:		  Permet de faire la gestion des livres 
//								  empruntés et les retourner. 
//  7) Générer Rapport:			  Génère un rapport sur le nombre de livres et 
//								  emprunts. 
//  8) Sauvegarder Bibliothèque:  Sauvegarde la bibliothèque dans un fichier 
//								  texte. 
//  9) Trier Livres :			  Permet de trier les livres dans la 
//								  bibliothèque. 
//  10) Quitter:				  Permet de quitter l'application.
// 
//  L'utilisateur navigue dans un menu pour choisir quelle action il desire 
//  effectuer.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "bibliotheque.h"

#include <time.h>

int main()
{
	// Déclaration des variables.
	int choix_menu;

	t_bibliotheque bibli;

	// Initialisation de la fonction rand()
	srand(time(NULL));

	// Initialisation de la bibliotheque
	initialiser_bibliotheque(&bibli);

	do
	{
		afficher_menu();

		// Gestion du menu.
		choix_menu = demander_choix_menu();

		switch (choix_menu)
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

		super_pause();
		system("cls");

	} while (choix_menu != 0);

	return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
//							Fonction lire_fichier
// Cette fonction permet de remplir le tableau correspondant a la bibliotheque
// a partir d'un fichier texte ou d'une simulation (en focntion de la valeur de
// la constante SIMULATION)
//
// Parametres : pBibli = pointeur vers le tableau de t_bibliotheque a remplir
// Retour :		aucun
//-----------------------------------------------------------------------------
void lire_fichier(t_bibliotheque * pBibli)
{
	FILE *fentree;

	// Variables permettant d'enregistrer un livre
	int nb_livres;
	t_genre genre;
	char titre[TAILLE_TITRE];
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
	int nb_pages;
	int isbn;
	int emprunt;

	// Variable permettant de sauter les lignes vides et les sauts de ligne
	// lors de l'utilisation de fgets et fscanf
	char char1;

	// Remplissage de la bibliotheque sans fichier texte
#if(SIMULATION == 1)
	simuler_lire_fichier(pBibli);

	// Remplissage de la bibliotheque a partir d'un fichier texte
#else
	fentree = fopen(BIBLIO_FICHIER, "rt");
	if (fentree == NULL)
	{
		printf("Erreur a l'ouverture du fichier\n");
		super_pause();
		exit(EXIT_FAILURE);
	}
	else
	{
		fscanf(fentree, "%d", &nb_livres);
		fscanf(fentree, "%c", &char1);

		while (feof(fentree) == 0)
		{
			// Enregistrement des valeurs du fichier texte dans les variables
			fscanf(fentree, "%d", &genre);
			fscanf(fentree, "%c", &char1);
			fgets(titre, TAILLE_TITRE, fentree);
			fgets(prenom, TAILLE_PRENOM, fentree);
			fgets(nom, TAILLE_NOM, fentree);
			fscanf(fentree, "%d", &nb_pages);
			fscanf(fentree, "%d", &isbn);
			fscanf(fentree, "%d", &emprunt);

			// Enlever les sauts de lignes en trop a la fin des chaines
			retirer_sautligne(titre);
			retirer_sautligne(prenom);
			retirer_sautligne(nom);

			// Mise a jour d'un livre de la bibliotheque
			pBibli->livres[genre - 1][pBibli->nb_livres[genre - 1]].genre = genre;
			strcpy(pBibli->livres[genre - 1][pBibli->nb_livres[genre - 1]].titre, titre);
			strcpy(pBibli->livres[genre - 1][pBibli->nb_livres[genre - 1]].auteur_prenom, prenom);
			strcpy(pBibli->livres[genre - 1][pBibli->nb_livres[genre - 1]].auteur_nom, nom);
			pBibli->livres[genre - 1][pBibli->nb_livres[genre - 1]].nb_pages = nb_pages;
			pBibli->livres[genre - 1][pBibli->nb_livres[genre - 1]].isbn = isbn;
			pBibli->livres[genre - 1][pBibli->nb_livres[genre - 1]].bEmprunte = emprunt;
			pBibli->nb_livres[genre - 1]++;

		}
		printf("Livres charges\n");
		fclose(fentree);
	}
#endif
}

//-----------------------------------------------------------------------------
//							Fonction simuler_lire_fichier
// Cette fonction permet de remplir le tableau correspondant a la bibliotheque
// sans avoir a passer par un fichier texte. Cette fonction est utilisee pour
// le debug
//
// Parametres : pBibli = pointeur vers le tableau de t_bibliotheque a remplir
// Retour :		aucun
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//							Fonction super_pause
// Cette fonction permet de faire une pause apres que l'utilisateur ai fait un
// choix dans le menu.
//
// Parametres : aucun
// Retour :		aucun
//-----------------------------------------------------------------------------
void super_pause()
{
	printf("Appuyez sur une touche pour continuer! \n");
	_getch();
}

//-----------------------------------------------------------------------------
//							Fonction retirer_sautligne
// Cette fonction permet d'enlever un saut de ligne d'une chaine de caracteres
//
// Parametres : chaine = pointeur vers la chaine dans laquelle on enleve le saut 
// Retour :		aucun
//-----------------------------------------------------------------------------
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
	int i, j;

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

//-----------------------------------------------------------------------------
//							Fonction demander_choix_menu
// Cette fonction permet de saisir le choix entre par l'utilisateur et de
// verifier sa validite.
//
// Parametres : aucun
// Retour :		choix = valeur entree par l'utilisateur
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//							Fonction afficher_info_livre
// Cette fonction affiche dans la console toutes les informations d'un livre
//
// Parametres : pLivre = pointeur vers le t_livre que l'on veut afficher
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_info_livre(t_livre * pLivre)
{
	printf("-------------------------------------------------------------------");
	printf("\nTitre : ");
	printf(pLivre->titre);
	printf("\nAuteur : ");
	printf(pLivre->auteur_prenom);
	printf(" ");
	printf(pLivre->auteur_nom);
	printf("\nGenre : %d", pLivre->genre);
	printf("\nPages : %d", pLivre->nb_pages);
	printf("\nISBN : %d", pLivre->isbn);
	printf("\nEmprunte : %d\n", pLivre->bEmprunte);
	printf("-------------------------------------------------------------------");
	printf("\n");
}

//-----------------------------------------------------------------------------
//							Fonction modifier_livre
// Cette fonction permet de modifier tous les champs d'un livre de la 
// bibliotheque choisi par l'utilisateur sauf son numero isbn.
// Les informations sont entrees par l'utilisateur.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle se trouve 
//						 le livre
// Retour :		aucun
//-----------------------------------------------------------------------------
void modifier_livre(t_bibliotheque * pBibli)
{
	// Caractere permettant d'enlever le enter a la saisie du titre
	char buffer;
	int isbn;
	t_livre livre_modifie;
	initialiser_livre(&livre_modifie);
	int i, j;
	t_genre genre_livre;

	// Recherche du livre a modifier
	printf("Entrez le isbn du livre a modifier : ");
	scanf("%d", &isbn);

	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
		{
			if (pBibli->livres[i][j].isbn == isbn)
			{
				livre_modifie = pBibli->livres[i][j];

				// Enlever le precedent livre du tableau
				initialiser_livre(&pBibli->livres[i][j]);

				// Actualiser compteur de genres
				pBibli->nb_livres[i]--;
			}
		}
	}

	if (livre_modifie.isbn != -1) // si le isbn a ete trouve
	{
		// Enregistrer le nouveau livre avec les nouvelles infos
		printf("Entrez le nouveau genre du livre : \n");
		scanf("%d", &genre_livre);
		livre_modifie.genre = genre_livre;
		printf("Entrez le nouveau titre du livre : \n");
		gets_s(&buffer, 1);
		gets_s(livre_modifie.titre, TAILLE_TITRE);
		printf("Entrez le nouveau prenom de l'auteur : \n");
		gets_s(livre_modifie.auteur_prenom, TAILLE_PRENOM);
		printf("Entrez le nouveau nom de l'auteur : \n");
		gets_s(livre_modifie.auteur_nom, TAILLE_NOM);
		printf("Entrez le nouveau nombre de page : \n");
		scanf("%d", &livre_modifie.nb_pages);
		livre_modifie.isbn = isbn;

		// Ranger le livre au bon endroit dans la bibliotheque
		pBibli->livres[genre_livre - 1][pBibli->nb_livres[genre_livre - 1]] =
			livre_modifie;

		// Actualiser compteur genre
		pBibli->nb_livres[genre_livre - 1]++;

		printf("Vous avez modifie le livre de numero isbn %d\n", isbn);
	}
}

//-----------------------------------------------------------------------------
//							Fonction retirer_livre
// Cette fonction permet de retirer un livre de la bibliotheque definitivement
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle se trouve 
//						 le livre a enlever
// Retour :		aucun
//-----------------------------------------------------------------------------
void retirer_livre(t_bibliotheque * pBibli)
{
	int isbn;
	int i, j;

	printf("Entrez le numero isbn du livre a retirer : \n");
	scanf("%d", &isbn);

	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
		{
			if (pBibli->livres[i][j].isbn == isbn)
			{
				initialiser_livre(&pBibli->livres[i][j]);
			}
		}
	}
	printf("Vous avez retire le livre de numero isbn %d\n", isbn);
}

//-----------------------------------------------------------------------------
//							Fonction sauvegarder_fichier
// Cette fonction permet de sauvegarder la bibliotheque actuelle dans un
// nouveau fichier texte nomme "sauvegarde_bibliotheque.txt".
//
// Parametres : pBibli = pointeur vers la bibliotheque a sauvegarder
// Retour :		aucun
//-----------------------------------------------------------------------------
void sauvegarder_fichier(t_bibliotheque * pBibli)
{

	FILE * sauvegarde = fopen(BIBLIO_SAUVEGARDE, "wt");
	int i, j;
	int nb_total_livres = compter_livres(pBibli);

	if (sauvegarde == NULL)
	{
		printf("Erreur a l'ouverture du fichier de sauvegarde");
		super_pause();
		exit(EXIT_FAILURE);
	}

	fprintf(sauvegarde, "%d\n\n", nb_total_livres);

	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
		{
			if (pBibli->livres[i][j].isbn != -1)
			{
				fprintf(sauvegarde, "%d\n", pBibli->livres[i][j].genre);
				fprintf(sauvegarde, "%s\n", pBibli->livres[i][j].titre);
				fprintf(sauvegarde, "%s\n", pBibli->livres[i][j].auteur_prenom);
				fprintf(sauvegarde, "%s\n", pBibli->livres[i][j].auteur_nom);
				fprintf(sauvegarde, "%d\n", pBibli->livres[i][j].nb_pages);
				fprintf(sauvegarde, "%d\n", pBibli->livres[i][j].isbn);
				fprintf(sauvegarde, "%d\n\n", pBibli->livres[i][j].bEmprunte);
			}
		}
	}
	printf("Bibliotheque sauvegardee\n");
	fclose(sauvegarde);
}

//-----------------------------------------------------------------------------
//							Fonction trier_livres
// Cette fonction permet de trier les livres d'un meme genre par nombre de 
// pages. 
//
// Parametres : pBibli = pointeur vers la bibliotheque a trier
// Retour :		aucun
//-----------------------------------------------------------------------------
void trier_livres(t_bibliotheque * pBibli)
{
	int i;
	int choix_user;

	printf("********************************************\n");
	printf("Choisir le mode de tri : \n");
	printf("1 - Tri par nombre de pages croissant\n");
	printf("2 - Tri par numero isbn croissant\n");
	printf("3 - Tri par ordre alphabetique (nom auteur)\n");
	printf("4 - Tri par longueur du titre croissante\n");
	printf("********************************************\n");

	do
	{
		scanf("%d", &choix_user);
	} while (choix_user < NB_CHOIX_TRI_MIN || choix_user > NB_CHOIX_TRI_MAX);


	if (choix_user == 1)
	{
		// Tri de chaque ligne du tableau de livres en fonction du nombre de pages
		for (i = 0; i < NB_GENRES; i++)
		{
			qsort((void *)pBibli->livres[i], pBibli->nb_livres[i],
				sizeof(t_livre), cmp_nbPages);
		}
		printf("Les livres ont ete tries par nombre de page croissant !\n");
	}
	else if (choix_user == 2)
	{
		// Tri de chaque ligne du tableau de livres en fonction du numero isbn
		for (i = 0; i < NB_GENRES; i++)
		{
			qsort((void *)pBibli->livres[i], pBibli->nb_livres[i],
				sizeof(t_livre), cmp_isbn);
		}
		printf("Les livres ont ete tries par numero isbn croissant !\n");
	}
	else if (choix_user == 3)
	{
		// Tri de chaque ligne du tableau de livres en fonction nom de l'auteur
		for (i = 0; i < NB_GENRES; i++)
		{
			qsort((void *)pBibli->livres[i], pBibli->nb_livres[i],
				sizeof(t_livre), cmp_nomAuteur);
		}
	}
	else if (choix_user == 4)
	{
		// Tri de chaque ligne du tableau de livres en fonction de la 
		// longueur du titre
		for (i = 0; i < NB_GENRES; i++)
		{
			qsort((void *)pBibli->livres[i], pBibli->nb_livres[i],
				sizeof(t_livre), cmp_longueurTitre);
		}
	}
}

//-----------------------------------------------------------------------------
//							Fonction compter_livres
// Cette fonction permet de compter le nombre de livres de la bibliotheque
// passee en argument.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle compter
// Retour :		nb_livres = nombre de livres dans la bibliotheque
//-----------------------------------------------------------------------------
int compter_livres(t_bibliotheque * pBibli)
{
	int i, j;
	int nb_livres = 0;

	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
		{
			if (pBibli->livres[i][j].isbn != -1)
			{
				nb_livres++;
			}
		}
	}
	return nb_livres;
}

//-----------------------------------------------------------------------------
//							Fonction afficher_bibliotheque
// Cette fonction permet d'afficher tout les livres de la bibliotheque passee
// en argument.
//
// Parametres : pBibli = pointeur vers la bibliotheque a afficher
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_bibliotheque(t_bibliotheque * pBibli)
{
	int i, j;
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

//-----------------------------------------------------------------------------
//							Fonction generer_rapport
// Cette fonction permet de generer et afficher le rapport. Le rapport contient
// le nombre de livres de la bibliotheque passee en argument et le nombre de 
// livres empruntes.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle on veut 
//						 faire le rapport
// Retour :		aucun
//-----------------------------------------------------------------------------
void generer_rapport(t_bibliotheque *pBibli)
{
	int i, j;
	int nb_livres_empruntes = 0;
	int nb_livres = 0;

	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
		{
			if (pBibli->livres[i][j].bEmprunte != DISPONIBLE)
			{
				nb_livres_empruntes++;
			}
			if (pBibli->livres[i][j].isbn != -1)
			{
				nb_livres++;
			}
		}
	}

	// actualisation des valeurs du rapport avec les nouvelles valeurs
	pBibli->rapport.nb_livres_empruntes = nb_livres_empruntes;
	pBibli->rapport.nb_livres = nb_livres;

	afficher_rapport(&pBibli->rapport);
}

//-----------------------------------------------------------------------------
//							Fonction afficher_rapport
// Cette fonction permet d'afficher le rapport passe en argument.
//
// Parametres : rapport = pointeur vers le rapport a afficher
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_rapport(t_rapport *rapport)
{
	printf("#####################################\n");
	printf("Nombre de livres : %d\n", rapport->nb_livres);
	printf("Nombre de livres empruntes : %d\n", rapport->nb_livres_empruntes);
	printf("#####################################\n");
}

//-----------------------------------------------------------------------------
//							Fonction emprunter_livre
// Cette fonction permet d'emprunter un livre de la bibliotheque passee en 
// argument. La fonction demande le numero isbn du livre que l'utilisateur veut 
// emprunter puis modifie l'indicateur d'emprunt de ce livre (il passe a 1).
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle on veut 
//						 emprunter le livre
// Retour :		aucun
//-----------------------------------------------------------------------------
void emprunter_livre(t_bibliotheque * pBibli)
{
	int isbn;
	int i, j;

	// Recherche du livre que l'on veut emprunter
	printf("Entrez le numero isbn du livre a emprunter : \n");
	scanf("%d", &isbn);

	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
		{
			if (pBibli->livres[i][j].isbn == isbn)
			{
				// On indique que ce livre est emprunte
				pBibli->livres[i][j].bEmprunte = EMPRUNT;
			}
		}
	}
	printf("Vous avez emprunte le livre de numero isbn %d\n", isbn);
}

//-----------------------------------------------------------------------------
//							Fonction gerer_lundi_matin_retours
// Cette fonction permet d'empiler les livres empruntes dans une pile de retours.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle les livres 
//						 ont ete empruntes
//				pPileRetours = pointeur vers la pile dans laquelle vont etre 
//							   stockes les livres retournes			
// Retour :		aucun
//-----------------------------------------------------------------------------
void gerer_lundi_matin_retours(t_bibliotheque*pBibli, t_pile *pPileRetours)
{
	int i, j;

	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
		{
			if (pBibli->livres[i][j].bEmprunte == EMPRUNT && !est_pleine(pPileRetours))
			{
				empile(pPileRetours, pBibli->livres[i][j]);
			}
		}
	}
}

//-----------------------------------------------------------------------------
//							Fonction retourner_livres
// Cette fonction permet de vider la pile de retours et de modifier les 
// indicateur d'emprunt des livres (on les met a 0) pour indiquer qu'ils ne 
// sont plus empruntes.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle les livres 
//						 ont ete empruntes
//				pPileRetours = pointeur vers la pile a vider	
// Retour :		aucun
//-----------------------------------------------------------------------------
void retourner_livres(t_bibliotheque * pBibli, t_pile * pPileRetours)
{
	t_livre livre_rendu;
	t_genre genre;
	initialiser_livre(&livre_rendu);
	int i;

	while (!est_vide(pPileRetours))
	{
		livre_rendu = desempile(pPileRetours);
		genre = livre_rendu.genre;

		for (i = 0; i < NB_LIVRES_MAX_RANGEE; i++)
		{
			if (livre_rendu.isbn == pBibli->livres[genre - 1][i].isbn)
			{
				pBibli->livres[genre - 1][i].bEmprunte = DISPONIBLE;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//							Fonction gerer_retours
// Cette fonction permet de gerer les retours en stockant les livres retournes
// dans une pile puis en vidant cette pile et en indiquant que les livres sont
// disponibles.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle les livres 
//						 ont ete empruntes		
// Retour :		aucun
//-----------------------------------------------------------------------------
void gerer_retours(t_bibliotheque * pBibli)
{
	t_pile pile_retours;
	init_pile(&pile_retours);

	gerer_lundi_matin_retours(pBibli, &pile_retours);
	retourner_livres(pBibli, &pile_retours);
}

//-----------------------------------------------------------------------------
//							Fonction afficher_menu
// Cette fonction permet d'afficher le menu de la bibliotheque dans la console.
//
// Parametres : aucun	
// Retour :		aucun
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//							Fonction cmp_nbPages
// Cette fonction permet de comparer le nombre de pages de 2 livres
// La fonction renvoie -1 si l'element 1 a moins de pages que l'element 2 
// La fonction renvoie 0 si l'element 1 a autant de pages que l'element 2
// La fonction renvoie 1 si l'element 1 a plus de pages que l'element 2 
//
// Parametres : aucun	
// Retour :		resultat de la comparaison
// Code inspire de la fonction de comparaison ecrite par Hugues Saulnier
//-----------------------------------------------------------------------------
int cmp_nbPages(const void*el_1, const void *el_2)
{
	if (((t_livre *)el_1)->nb_pages < ((t_livre *)el_2)->nb_pages) return -1;
	if (((t_livre *)el_1)->nb_pages == ((t_livre *)el_2)->nb_pages) return 0;
	return 1;
}

//-----------------------------------------------------------------------------
//							Fonction cmp_isbn
// Cette fonction permet de comparer le numero isbn de 2 livres
// La fonction renvoie -1 si isbn_1 < isbn_2 
// La fonction renvoie 0 si isbn_1 = isbn_2 
// La fonction renvoie 1 si isbn_1 > isbn_2
//
// Parametres : aucun	
// Retour :		resultat de la comparaison
// Code inspire de la fonction de comparaison ecrite par Hugues Saulnier
//-----------------------------------------------------------------------------
int cmp_isbn(const void*el_1, const void *el_2)
{
	if (((t_livre *)el_1)->isbn < ((t_livre *)el_2)->isbn) return -1;
	if (((t_livre *)el_1)->isbn == ((t_livre *)el_2)->isbn) return 0;
	return 1;
}

//-----------------------------------------------------------------------------
//							Fonction cmp_nomAuteur
// Cette fonction permet de comparer le nom des auteurs de 2 livres
// La fonction renvoie -1 si nom_1 < nom_2 
// La fonction renvoie 0 si nom_1 = nom_2 
// La fonction renvoie 1 si nom_1 > nom_2
// La comparaison est evaluee par rapport a l'ordre alphabetique ("A" < "B")
//
// Parametres : aucun	
// Retour :		resultat de la comparaison
// Code inspire de la fonction de comparaison ecrite par Hugues Saulnier
//-----------------------------------------------------------------------------
int cmp_nomAuteur(const void*el_1, const void *el_2)
{
	return strcmp(((t_livre *)el_1)->auteur_nom, ((t_livre *)el_2)->auteur_nom);
}

//-----------------------------------------------------------------------------
//							Fonction cmp_isbn
// Cette fonction permet de comparer la longueur du titre de 2 livres
// La fonction renvoie -1 si titre_1 < titre_2
// La fonction renvoie 0 si titre_1 = titre_2
// La fonction renvoie 1 si titre_1 > titre_2
//
// Parametres : aucun	
// Retour :		resultat de la comparaison
// Code inspire de la fonction de comparaison ecrite par Hugues Saulnier
//-----------------------------------------------------------------------------
int cmp_longueurTitre(const void*el_1, const void *el_2)
{
	if (strlen(((t_livre *)el_1)->titre) < strlen(((t_livre *)el_2)->titre)) return -1;
	if (strlen(((t_livre *)el_1)->titre) == strlen(((t_livre *)el_2)->titre)) return 0;
	return 1;
}
