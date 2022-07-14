#ifndef ADHERENT_H
#define ADHERENT_H

#include <string>
#include <vector>
#include <fstream>


#include "BDR_SQLite3.h"
#include "RefCounted.h"

#include "util.h"

using namespace std;

//-----------------------declaration AdherentData --------------------------
class AdherentData : public RefCounted{
    public:
        AdherentData(string nom,
            string addresse,
            unsigned int nbreLivresEmprunter);
        AdherentData(unsigned int id,string nom,
            string addresse,
            unsigned int nbreLivresEmprunter);

        AdherentData(const AdherentData &ad);

        const string to_string(const string &separateur);
        static void affiche_adherentData(vector<AdherentData> &v);

        unsigned int id = -1;
        string nom;
        string addresse;
        unsigned int nbreLivresEmprunter;
};


//-----------------------declaration AdherentData --------------------------
class Adherent{
        public:
            static bool ajouter(const string nom,const string addresse);
            static bool modifierNom(unsigned int id,const string &nom);
            static bool modifierAddresse(unsigned int id,const string addresse);
            static bool supprimer(unsigned int id);
            static bool consulter(vector<AdherentData> &adherents,const string &concat="");

            static bool modifierNoms(const vector<unsigned int> &ids, const string &nom);
            static bool modifierAddresses(const vector<unsigned int> &ids,const string &addresse);
            static bool supprimer(const vector<unsigned int> &ids);
            static bool consulter(vector<AdherentData> &adherents,const vector<unsigned int> &ids,const string &condition="",const string &concat="");

            /* valeur[0] change ids[0] et ainsi de suite.
             *  en temps normal on retourne le nombre de champs modifies
             *  on ne fait rien si les deux(02) vecteurs n'ont pas la meme taille et on retourne -1
             */
            static unsigned int modifierNoms_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &noms);
            static unsigned int modifieraddresses_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &addresses);

//            static bool emprunterLivre(unsigned int id_livre);
//            static bool rendreLivre(unsigned int id_livre);

            static bool consulterEmprunteurTrieParNom(vector<AdherentData> &adherents,bool isAsc=true);
            static bool consulterEmprunteurTrieParDate(vector<AdherentData> &adherents,bool isAsc=true);

            static bool exportToFile(vector<AdherentData> &data,const string &nom_fichier,const string &separateur=" ");
            static bool exportToFile(const string &nom_fichier,const string &separateur=" ");
            static unsigned int importToVector(vector<AdherentData> &data,string nom_fichier,const string &separateur=" ");//importe dans un tableau dynamique, retourne le nombre d'elements ajoutes
            static unsigned int importToDB(string nom_fichier,const string &separateur=" "); // met dans la base de donnees
    private:
        static vector<string> vChamps ;
        static string nomTable;
    };
#endif // ADHERENT_H
