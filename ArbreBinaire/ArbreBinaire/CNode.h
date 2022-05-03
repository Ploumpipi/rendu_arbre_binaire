#pragma once
using namespace std;
#include <iostream>

class CNode {
public:
	int valeur;
	CNode* fils_droite;
	CNode* fils_gauche;
	CNode* arbre = nullptr;
};