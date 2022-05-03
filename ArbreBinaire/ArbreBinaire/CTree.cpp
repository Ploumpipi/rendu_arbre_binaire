#include "CTree.h"

Node* CTree::getArbre()
{
	return this->arbre;
}

void CTree::placer(Node* node)
{
	Node* courant = arbre;
	Node* precedent = nullptr;
	//Si l'arbre est vide
	if (arbre == NULL) {
		arbre = node;
		return;
	}

	//On trouve une place vide
	while (courant) {
		precedent = courant;
		if (node->valeur < courant->valeur)
			courant = courant->fils_gauche;
		else {
			courant = courant->fils_droite;
		}
	}

	//on replace un noeud
	if (node->valeur < precedent->valeur) {
		precedent->fils_gauche = node;
		precedent->valeurGauche = node->valeur;
	}
	else {
		precedent->fils_droite = node;
		precedent->valeurDroite = node->valeur;
	}
		
}

void CTree::addNode(int valeur)
{
	//Création d'un nouveau noeud
	Node* nouveau = new Node;
	nouveau->valeur = valeur;
	nouveau->fils_droite = NULL;
	nouveau->fils_gauche = NULL;

	//On place à la bonne place
	placer(nouveau);
}

Node* CTree::rechercher(int valeur)
{
	Node* courant = arbre;
	while (courant) {
		if (valeur == courant->valeur)
			return courant;
		else if (valeur < courant->valeur)
			courant = courant->fils_gauche;
		else
			courant = courant->fils_droite;
	}
	return nullptr;
}

void CTree::supprimer(Node* node)
{
	Node* droite = node->fils_droite;
	Node* gauche = node->fils_droite;
	Node* courant = arbre;

	//Supression de la racine?
	if (node == arbre) {
		arbre = droite;
		if (gauche)
			placer(gauche);
		delete node;
		return;
	}

	while (courant) {
		if (courant->fils_droite == node || courant->fils_gauche == node)
			break;
		if (node->valeur >= courant->valeur)
			courant = courant->fils_droite;
		else
			courant = courant->fils_gauche;
	}

	//Maintenant que le noeud courant pointe le noeud précédent
	if (courant->fils_droite == node)
		courant->fils_droite = droite;
	else
		courant->fils_gauche = droite;

	//Puis on replace l'autre fils du noeud supprimé
	if (gauche)
		placer(gauche);

	//On libère l'objet noeud de ses obligations
	delete node;
}

void CTree::afficher(Node* racine)
{
	if (racine->fils_gauche)
		afficher(racine->fils_gauche);
	if (racine->fils_droite)
		afficher(racine->fils_droite);
	cout << racine->valeur << endl;
	cout << racine->valeur << " a pour fils gauche : " << racine->valeurGauche << endl;

}
