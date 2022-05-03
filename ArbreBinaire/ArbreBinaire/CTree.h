#pragma once
using namespace std;
#include <iostream>

struct Node {
	int valeur;
	int valeurDroite, valeurGauche;
	Node* fils_droite;
	Node* fils_gauche;
};

class CTree {
private:
	Node* arbre = NULL;
public:
	Node* getArbre();

	void placer(Node* node);

	void addNode(int valeur);

	Node* rechercher(int valeur);

	void supprimer(Node* node);

	void afficher(Node* racine);
};