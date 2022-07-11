#ifndef ADHERENT_H
#define ADHERENT_H

#include <string>
#include <vector>



#include "BDR_SQLite3.h"

using namespace std;

class AdherentData{
    public:
        AdherentData(string nom,
            string addresse,
            unsigned int nbreLivresEmprunter);

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
    private:
        static BDR_SQLite3 bd;
    };
#endif // ADHERENT_H
