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
    private:
        static BDR_SQLite3 bd;
};

#endif // AUTEUR_H
