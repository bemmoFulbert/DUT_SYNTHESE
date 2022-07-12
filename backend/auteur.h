#ifndef AUTEUR_H
#define AUTEUR_H

#include <string>
#include <vector>

#include "BDR_SQLite3.h"

using namespace std;

class AuteurData
{
public:
    AuteurData(string nom,string prenom);
    static void affiche_auteurData(vector<AuteurData> v);

    string nom;
    string prenom;
};

class Auteur{
    public:
        static bool ajouter(const string &nom,const string &prenom);
        static bool modifierNom(unsigned int id,const string &nom);
        static bool modifierPrenom(unsigned int id,const string &prenom);
        static bool supprimer(unsigned int id);
        static bool consulter(vector<AuteurData> &auteurs);

        static unsigned int import(string nom_fichier);
    private:
        static BDR_SQLite3 bd;
        static vector<string> vChamps;
};

#endif // AUTEUR_H
