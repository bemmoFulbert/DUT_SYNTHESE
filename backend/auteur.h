#ifndef AUTEUR_H
#define AUTEUR_H

#include <string>
#include <vector>
#include <fstream>

#include "BDR_SQLite3.h"
#include "util.h"

using namespace std;

class AuteurData
{
public:
    AuteurData(string nom,string prenom);
    static void affiche_auteurData(vector<AuteurData> v);
    const string to_string(const string &separateur=" ");

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

        static bool exportToFile(vector<AuteurData> &data,const string &nom_fichier,const string &separateur=" ");
        static bool exportToFile(const string &nom_fichier,const string &separateur=" ");
        static unsigned int importToVector(vector<AuteurData> &data,string nom_fichier,const string &separateur=" ");//importe dans un tableau dynamique, retourne le nombre d'elements ajoutes
        static unsigned int importToDB(string nom_fichier,const string &separateur=" "); // met dans la base de donnees
    private:
        static BDR_SQLite3 bd;
        static vector<string> vChamps;
};

#endif // AUTEUR_H
