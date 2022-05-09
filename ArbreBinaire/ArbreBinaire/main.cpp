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
int nombreNoeud(noeud* racine);
int nombreNoeudGauche(noeud* racine);
int nombreNoeudDroit(noeud* racine);
int calculHauteur(noeud* racine);

void equilibrage(noeud* racine, arbre_binaire* pArbre);
void rotationGauche(noeud* node, arbre_binaire* pArbre);
void rotationDroite(noeud* node, arbre_binaire* pArbre);


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

	int gauche = nombreNoeudGauche(pArbre->racine);
	cout << "gauche : " << gauche << endl;

	int droit = nombreNoeudDroit(pArbre->racine);
	cout << "droit : " << droit << endl;

	equilibrage(pArbre->racine, pArbre);

	parcoursPrefixe(pArbre->racine);

	int gauche2 = nombreNoeudGauche(pArbre->racine);
	cout << "gauche : " << gauche2 << endl;

	int droit2 = nombreNoeudDroit(pArbre->racine);
	cout << "droit : " << droit2 << endl;


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

int nombreNoeud(noeud* racine)
{
	if (racine == nullptr)
		return 0;
	else
		return 1 + nombreNoeud(racine->fgauche) + nombreNoeud(racine->fdroite);
}

int nombreNoeudGauche(noeud* racine)
{
	if (racine == nullptr)
		return 0;
	else
		return 1 + nombreNoeudGauche(racine->fgauche);
}

int nombreNoeudDroit(noeud* racine)
{
	if (racine == nullptr)
		return 0;
	else
		return 1 + nombreNoeudDroit(racine->fdroite);
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

int calculHauteur(noeud* racine)
{
	int hauteurDroite, hauteurGauche, hauteur;

	//si l'arbre est vide on retourne -1
	if (racine == nullptr)
	{
		hauteur = -1;
	}
	else
	{
		//calcul de la profondeur du sous arbre droit
		hauteurDroite = calculHauteur(racine->fdroite);
		//calcul de la profondeur du sous arbre gauche
		hauteurGauche = calculHauteur(racine->fgauche);

		hauteur = 1 + (hauteurGauche > hauteurDroite ? hauteurGauche : hauteurGauche);
	}
	return hauteur;
}

void equilibrage(noeud* racine, arbre_binaire* pArbre)
{
	bool isEquilibrer = false;
	while (isEquilibrer == false) {
		int nbNoeudGauche = nombreNoeudGauche(racine);
		int nbNoeudDroit = nombreNoeudDroit(racine);

		//Pour équilibrage droite - gauche
		int equilibre = nbNoeudDroit - nbNoeudGauche;
		if (equilibre >= -1 && equilibre <= 1) {
			//l'arbre est équilibré
			isEquilibrer = true;
			cout << "l'arbre est equilibre (normalement)" << endl;
			cout << "nombre de noeud a gauche : " << nbNoeudGauche << " et a droite : " << nbNoeudDroit << endl;
		}
		else {
			if (equilibre < -1)
				rotationDroite(racine, pArbre);
			if (equilibre > 1)
				rotationGauche(racine, pArbre);
		}
	}
}

void rotationGauche(noeud* node, arbre_binaire* pArbre)
{
	noeud* Y = node;
	noeud* X = node->fdroite;
	noeud* B = nullptr;

	if (X != nullptr) {
		B = X->fgauche;
		pArbre->racine = X;
		X->fgauche = Y;
	}
	Y->fdroite = B;
}

void rotationDroite(noeud* node, arbre_binaire* pArbre)
{
	noeud* Y = node;
	noeud* X = node->fgauche;
	noeud* B = nullptr;

	if (X != nullptr) {
		B = X->fdroite;
		pArbre->racine = X;
		X->fdroite = Y;
	}
	Y->fgauche = B;
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


