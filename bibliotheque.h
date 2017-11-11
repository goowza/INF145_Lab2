#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include "t_pile.h"

#define NB_LIVRES_MAX_RANGEE        100
#define NB_GENRES                   6
#define BIBLIO_FICHIER		    "biblio.txt"
#define BIBLIO_SAUVEGARDE	    "sauvegarde_bibliotheque.txt"

#define TAILLE_TITRE	80
#define TAILLE_NOM	30	
#define TAILLE_PRENOM	30

#define MAX_ISBN	9999

#define SIMULATION      0

#define EMPRUNT         1
#define DISPONIBLE      0

#define NB_CHOIX_TRI_MIN	1
#define NB_CHOIX_TRI_MAX	4

typedef struct
{
	int nb_livres;
	int nb_livres_empruntes;
} t_rapport;

typedef struct
{
	// tableau de t_livre
	t_livre livres[NB_GENRES][NB_LIVRES_MAX_RANGEE];
	int nb_livres[NB_GENRES];
	//t_pile retours;
	t_rapport rapport;
} t_bibliotheque;

// Cette fonction permet de saisir le choix entre par l'utilisateur et de
// verifier sa validite.
int demander_choix_menu();

// Cette fonction initialise la bibliotheque en mettant tout les compteurs du 
// tableau nb_livres a 0, en remplissant toutes les cases du tableau 2D
// contenant les livres avec des livres initialises par la fonction 
// initialiser_livre et en initialisant le rapport avec la fonction 
// initialiser_rapport.
void initialiser_bibliotheque(t_bibliotheque * pBibli);

// Cette fonction initialise un livre en mettant son genre a "AUCUN", 
// son isbn a -1, son nombre de pages a 0, le nom et prenom de l'auteur
// a "N/A", le titre du livre a "N/A" et son sa disponibilite a "DISPONIBLE".
void initialiser_livre(t_livre * pLivre);

// Cette fonction initialise le rapport en mettant le nombre de livres total et
// le nombre de livres empruntes a 0.
void initialiser_rapport(t_rapport * pRapport);

// Cette fonction permet de sauvegarder la bibliotheque actuelle dans un
// nouveau fichier texte nomme "sauvegarde_bibliotheque.txt".
void sauvegarder_fichier(t_bibliotheque * pBibli);

// Cette fonction permet de remplir le tableau correspondant a la bibliotheque
// a partir d'un fichier texte ou d'une simulation (en fonction de la valeur de
// la constante SIMULATION).
void lire_fichier(t_bibliotheque * pBibli);

// Cette fonction permet de remplir le tableau correspondant a la bibliotheque
// sans avoir a passer par un fichier texte. Cette fonction est utilisee pour
// le debug.
void simuler_lire_fichier(t_bibliotheque * pBibli);

// Cette fonction permet de trier les livres d'un meme genre par nombre de 
// pages. 
void trier_livres(t_bibliotheque * pBibli);

// Cette fonction permet d'afficher tout les livres de la bibliotheque passee
// en argument.
void afficher_bibliotheque(t_bibliotheque * pBibli);

// Cette fonction permet d'afficher le rapport passe en argument.
void afficher_rapport(t_rapport *rapport);

// Cette fonction permet de generer et afficher le rapport. Le rapport contient
// le nombre de livres de la bibliotheque passee en argument et le nombre de 
// livres empruntes.
void generer_rapport(t_bibliotheque *pBibli);

// Cette fonction permet d'emprunter un livre de la bibliotheque passee en 
// argument. La fonction demande le numero isbn du livre que l'utilisateur veut 
// emprunter puis modifie l'indicateur d'emprunt de ce livre (il passe a 1).
void emprunter_livre(t_bibliotheque * pBibli);

// Cette fonction permet de gerer les retours en stockant les livres retournes
// dans une pile puis en vidant cette pile et en indiquant que les livres sont
// disponibles.
void gerer_retours(t_bibliotheque * pBibli);

// Cette fonction affiche dans la console toutes les informations d'un livre.
void afficher_info_livre(t_livre * pLivre);

// Cette fonction permet de modifier tous les champs d'un livre de la 
// bibliotheque choisi par l'utilisateur sauf son numero isbn.
// Les informations sont entrees par l'utilisateur.
void modifier_livre(t_bibliotheque * pBibli);

// Cette fonction permet de retirer un livre de la bibliotheque definitivement.
void retirer_livre(t_bibliotheque * pBibli);

// Cette fonction permet de compter le nombre de livres de la bibliotheque
// passee en argument.
int compter_livres(t_bibliotheque * pBibli);

// Cette fonction permet d'empiler les livres empruntes dans une pile de retours.
void gerer_lundi_matin_retours(t_bibliotheque * pBibli, t_pile * pPileRetours);

// Cette fonction permet de vider la pile de retours et de modifier les 
// indicateur d'emprunt des livres (on les met a 0) pour indiquer qu'ils ne 
// sont plus empruntes.
void retourner_livres(t_bibliotheque * pBibli, t_pile * pPileRetours);

// Cette fonction permet d'enlever un saut de ligne d'une chaine de caracteres.
void retirer_sautligne(char * chaine);

// Cette fonction permet de faire une pause apres que l'utilisateur ai fait un
// choix dans le menu.
void super_pause();

// Cette fonction permet d'afficher le menu de la bibliotheque dans la console.
void afficher_menu();

// Cette fonction permet de comparer le nombre de pages de 2 livres
// La focntion renvoie -1 si l'element 1 a moins de pages que l'element 2 
// La focntion renvoie 0 si l'element 1 a autant de pages que l'element 2
// La focntion renvoie 1 si l'element 1 a plus de pages que l'element 2 
int cmp_nbPages(const void*el_1, const void *el_2);

// Cette fonction permet de comparer le numero isbn de 2 livres
// La focntion renvoie -1 si isbn 1 < isbn 2 
// La focntion renvoie 0 si isbn 1 = isbn 2 
// La focntion renvoie 1 si isbn 1 > isbn 2 
int cmp_isbn(const void*el_1, const void *el_2);

// Cette fonction permet de comparer le nom des auteurs de 2 livres
// La fonction renvoie -1 si nom_1 < nom_2 
// La fonction renvoie 0 si nom_1 = nom_2 
// La fonction renvoie 1 si nom_1 > nom_2
// La comparaison est evaluee par rapport a l'ordre alphabetique ("A" < "B")
int cmp_nomAuteur(const void*el_1, const void *el_2);

// Cette fonction permet de comparer la longueur du titre de 2 livres
// La fonction renvoie -1 si titre_1 < titre_2
// La fonction renvoie 0 si titre_1 = titre_2
// La fonction renvoie 1 si titre_1 > titre_2
int cmp_longueurTitre(const void*el_1, const void *el_2);
#endif


