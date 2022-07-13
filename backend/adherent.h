#ifndef ADHERENT_H
#define ADHERENT_H

#include <string>
#include <vector>
#include <fstream>


#include "BDR_SQLite3.h"
#include "util.h"

using namespace std;

class AdherentData{
    public:
        AdherentData(string nom,
            string addresse,
            unsigned int nbreLivresEmprunter);
        AdherentData(unsigned int id,string nom,
            string addresse,
            unsigned int nbreLivresEmprunter);
        const string to_string(const string &separateur);

        unsigned int id = -1;
        string nom;
        string addresse;
        unsigned int nbreLivresEmprunter;
};

class Adherent{
        public:
            static bool ajouter(const string nom,const string addresse);
            static bool modifierNom(unsigned int id,const string nom);
            static bool modifierAddresse(unsigned int id,const string addresse);
            static bool supprimer(unsigned int id);
            static bool consulter(vector<AdherentData> &adherents,const string &condition="");

//            static bool emprunterLivre(unsigned int id_livre);
//            static bool rendreLivre(unsigned int id_livre);

            static bool consulterEmprunteurTrieParNom(vector<AdherentData> &adherents,bool isAsc=true);
            static bool consulterEmprunteurTrieParDate(vector<AdherentData> &adherents,bool isAsc=true);

            static bool exportToFile(vector<AdherentData> &data,const string &nom_fichier,const string &separateur=" ");
            static bool exportToFile(const string &nom_fichier,const string &separateur=" ");
            static unsigned int importToVector(vector<AdherentData> &data,string nom_fichier,const string &separateur=" ");//importe dans un tableau dynamique, retourne le nombre d'elements ajoutes
            static unsigned int importToDB(string nom_fichier,const string &separateur=" "); // met dans la base de donnees
    private:
        static BDR_SQLite3 bd;
        static vector<string> vChamps ;
    };
#endif // ADHERENT_H
