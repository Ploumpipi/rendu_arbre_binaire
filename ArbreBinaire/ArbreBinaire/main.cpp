#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>

using namespace std;


typedef struct noeud {
	int n_donnee;
	struct noeud* fgauche;
	struct noeud* fdroite;
}noeud;

typedef struct arbre_binaire {
	int nbNoeud = 0;
	int hauteur = 0;
	noeud* racine;
}arbre_binaire;



void initialisation(arbre_binaire* pArbre);

void parcoursPrefixe(noeud* racine);
void parcoursPostfixe(noeud* racine);
void traiter(noeud* n);
noeud* rechercher(int  valeur);

int inserArbreVide(arbre_binaire* pArbre, int n_val);
int ajoutNoeud(arbre_binaire* pArbre, int n_val);


noeud* supprNoeud(arbre_binaire* pArbre, noeud* courant, int n_val);
void supprNoeudArbre(arbre_binaire* pArbre, int val);
noeud* plusGrand(noeud* elem);

void liberer(noeud** p_racine);
void nombreNoeud(arbre_binaire* pArbre);
void affichageHauteur(arbre_binaire* pArbre);



int main() {

	arbre_binaire* pArbre = nullptr;
	pArbre = (arbre_binaire*)malloc(sizeof(arbre_binaire));
	initialisation(pArbre);
	pArbre->hauteur = -1;
	pArbre->nbNoeud = 0;

	inserArbreVide(pArbre, 10);
	ajoutNoeud(pArbre, 20);
	ajoutNoeud(pArbre, 8);
	ajoutNoeud(pArbre, 5);
	ajoutNoeud(pArbre, 6);
	ajoutNoeud(pArbre, 4);
	ajoutNoeud(pArbre, 3);

	parcoursPrefixe(pArbre->racine);

	cout << "\n" << endl;

	parcoursPostfixe(pArbre->racine);

	cout << "\n" << endl;

	affichageHauteur(pArbre);
	nombreNoeud(pArbre);


	//noeud *elem=supprNoeud(pArbre->racine, 1);
	//supprNoeudArbre(pArbre, 6);

	//parcoursPrefixe(pArbre->racine);

	if(pArbre!=nullptr)
		liberer(&pArbre->racine);

	free(pArbre);

	return 0;
}


void parcoursPrefixe(noeud* racine) {
	if (racine != NULL) {
		traiter(racine);
		parcoursPrefixe(racine->fgauche);
		parcoursPrefixe(racine->fdroite);
	}
}

void parcoursPostfixe(noeud* racine)
{
	if (racine != NULL) {
		parcoursPrefixe(racine->fgauche);
		parcoursPrefixe(racine->fdroite);
		traiter(racine);
	}
}


void traiter(noeud* n) {
	printf("%d, ", n->n_donnee);
}

noeud* rechercher(int valeur)
{
	noeud* courant = NULL;
	//courant = (noeud*)malloc(sizeof(noeud));

	while (courant) {
		if (valeur == courant->n_donnee)
			return courant;
		else if (valeur < courant->n_donnee)
			courant = courant->fgauche;
		else
			courant = courant->fdroite;
	}
	return nullptr;
}

void initialisation(arbre_binaire* pArbre)
{
	pArbre->racine = NULL;
}


int inserArbreVide(arbre_binaire* pArbre, int n_val) {

	noeud* elem = NULL;
	elem = (noeud*)malloc(sizeof(noeud));

	if (elem == NULL) {
		return 0;
	}
	else {
		elem->n_donnee = n_val;

		elem->fgauche = NULL;
		elem->fdroite = NULL;
		pArbre->racine = elem;

		return 1;
	}
}

int ajoutNoeud(arbre_binaire* pArbre, int n_val)
{
	noeud* elem = NULL;
	elem = (noeud*)malloc(sizeof(noeud));

	noeud* courant = pArbre->racine;
	noeud* precedent = NULL;

	elem->fdroite = NULL;
	elem->fgauche = NULL;
	elem->n_donnee = n_val;

	pArbre->hauteur = pArbre->hauteur++;
	pArbre->nbNoeud = pArbre->nbNoeud++;

	// On avance jusqu'à trouver une place
	while (courant)
	{
		precedent = courant;
		if (elem->n_donnee < courant->n_donnee)
			courant = courant->fgauche;
		else
			courant = courant->fdroite;
	}

	// on a trouvé une place libre, et
   // precedent pointe vers le parent de notre
   // noeud à replacer.
	if (elem->n_donnee < precedent->n_donnee)
		precedent->fgauche = elem;
	else
		precedent->fdroite = elem;

	return 1;
}

void nombreNoeud(arbre_binaire* pArbre)
{
	cout << "nombre de noeuds : " << pArbre->nbNoeud << endl;
}

void liberer(noeud** p_racine) {

	noeud* racine = *p_racine;

	if (racine != nullptr) {
		liberer(&racine->fgauche);
		liberer(&racine->fdroite);
		free(racine);
	}
	*p_racine = nullptr;
}

void affichageHauteur(arbre_binaire* pArbre)
{
	cout << "hauteur : " << pArbre->hauteur << endl;
}

noeud* supprNoeud(arbre_binaire* pArbre, noeud* courant, int n_val)
{
	if (courant == nullptr) { //Si arbre vide
		return courant;
	}
	else if (n_val < courant->n_donnee) {//Si val à suppr < donnée du noeud courant sous arbre gauche
		courant->fgauche = supprNoeud(pArbre, courant->fgauche, n_val);
	}
	else if (n_val > courant->n_donnee) {//Si val à suppr > donnée du noeud courant => sous arbre droit
		courant->fdroite = supprNoeud(pArbre, courant->fdroite, n_val);
	}
	else
	{	//on a la valeur
		if (courant->fgauche == nullptr) { //si fils gauche est nullptr 								
			return courant->fdroite; //on retourne fils droit
		}
		else if (courant->fdroite == nullptr) { //si fils droit est nullptr		
			return courant->fgauche; //on retourne fils gauche
		}
		else { // dans le cas fils gauche et fils droit diff de nullptr
			noeud* succ = plusGrand(courant->fgauche);//on cherche le plus grand de fils gauche
			if (courant != nullptr) {
				courant->n_donnee = succ->n_donnee; //on remplace la valeur à supprimer par le successeur
				supprNoeud(pArbre, courant->fgauche, succ->n_donnee);//on supprime par récursivité la valeur doublon du successeur.
			}
		}
	}
	return courant;
}

noeud* plusGrand(noeud* elem)
{
	noeud* courant = elem;
	if (elem->fdroite == nullptr) {
		return courant;
	}
	return plusGrand(courant->fdroite);
}

void supprNoeudArbre(arbre_binaire* pArbre, int val) {
	assert(pArbre);
	if (pArbre->racine)
		supprNoeud(pArbre, pArbre->racine, val);
}


