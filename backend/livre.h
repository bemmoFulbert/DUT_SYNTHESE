#ifndef LIVRE_H
#define LIVRE_H

#include <string>

#include "BDR_SQLite3.h"

using namespace std;

class LivreData{
    public:
        LivreData(string titre,
            string dateDePublication,
            unsigned int nbreExemplairesTotal,
            unsigned int nbreExemplairesEmprunter,
            unsigned int id_auteur);
        static void affiche_livreData(vector<LivreData> v);

        string titre;
        string dateDePublication;
        unsigned int nbreExemplairesTotal;
        unsigned int nbreExemplairesEmprunter;
        unsigned int id_auteur;

};

class Livre{
        public:
            static bool ajouter(const string titre,const string dateDePublication,unsigned int id_auteur);
            static bool modifierTitre(unsigned int id,const string titre);
            static bool modifierDateDePublication(unsigned int id,const string dateDePublication);
            static bool supprimer(unsigned int id);
            static bool consulter(vector<LivreData> &livres,const string &condition="");

//            static bool ajouterNbreDeCopies(unsigned int id,unsigned int nbreAAjouter);
            static bool consulterLivresEmprunterTrieParNom(vector<LivreData> &livres,bool isAsc=true);
            static bool consulterLivresEmprunterTrieParDate(vector<LivreData> &livres,bool isAsc); //par la date de l'emprunte
        private:
            static BDR_SQLite3 bd;
    };

#endif // LIVRE_H
