#ifndef LIVRE_H
#define LIVRE_H

#include <string>
#include <fstream>

#include "BDR_SQLite3.h"
#include "util.h"

using namespace std;

class LivreData{
    public:
        LivreData(string titre,
            string dateDePublication,
            unsigned int nbreExemplairesTotal,
            unsigned int nbreExemplairesEmprunter,
            unsigned int id_auteur);
        static void affiche_livreData(vector<LivreData> v);
        string to_string(const string &separateur=" ");

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

            static bool exportToFile(vector<LivreData> data,const string &nom_fichier,const string &separateur=" ");
            static bool exportToFile(const string &nom_fichier,const string &separateur=" ");
            static unsigned int importToVector(vector<LivreData> &data,string nom_fichier,const string &separateur=" ");//importe dans un tableau dynamique, retourne le nombre d'elements ajoutes
            static unsigned int importToDB(string nom_fichier,const string &separateur=" "); // met dans la base de donnees
        private:
            static BDR_SQLite3 bd;
            static vector<string> vChamps;
    };

#endif // LIVRE_H
