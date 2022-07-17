#ifndef AUTEUR_H
#define AUTEUR_H

#include <string>
#include <vector>
#include <fstream>

#include "util.h"
#include "BDR_SQLite3.h"
#include "RefCounted.h"


using namespace std;


//-----------------------declaration AuteurData --------------------------
class AuteurData : public RefCounted
{
public:
    AuteurData(string nom,string prenom);
    AuteurData(unsigned int id,string nom,string prenom);
    AuteurData(const AuteurData &ad);

    static void affiche_auteurData(vector<AuteurData> &v);
    const string to_string(const string &separateur=" ");

    unsigned int id = -1;
    string nom;
    string prenom;
};


//-----------------------declaration Auteur ----------------------------------
class Auteur{
    public:

        static bool ajouter(const string &nom,const string &prenom);
        static bool modifierNom(unsigned int id,const string &nom);
        static bool modifierPrenom(unsigned int id,const string &prenom);
        static bool supprimer(unsigned int id);
        static bool consulter(vector<AuteurData> &auteurs,const string &concat="");

        static bool modifierNoms(const vector<unsigned int> &ids,const string &nom);
        static bool modifierPrenoms(const vector<unsigned int> &ids,const string &prenom);
        static bool supprimer(const vector<unsigned int> &ids);
        static bool consulter(vector<AuteurData> &auteurs,const vector<unsigned int> &ids);

        /* valeur[0] change ids[0] et ainsi de suite.
         *  en temps normal on retourne le nombre de champs modifies
         *  on ne fait rien si les deux(02) vecteurs n'ont pas la meme taille et on retourne -1
         */
        static bool modifierNoms_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &noms);
        static bool modifierPrenoms_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &prenoms);

        static bool exportToFile(vector<AuteurData> &data,const string &nom_fichier,const string &separateur=" ");
        static bool exportToFile(const string &nom_fichier,const string &separateur=" ");
        static unsigned int importToVector(vector<AuteurData> &data,string nom_fichier,const string &separateur=" ");//importe dans un tableau dynamique, retourne le nombre d'elements ajoutes
        static unsigned int importToDB(string nom_fichier,const string &separateur=" "); // met dans la base de donnees
    private:
        static vector<string> vChamps;
        static vector<string> vChamps_full;
        static string nomTable;
};

#endif // AUTEUR_H
