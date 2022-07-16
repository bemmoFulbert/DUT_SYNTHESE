#ifndef LIVRE_H
#define LIVRE_H

#include <string>
#include <hash_map>
#include <fstream>

#include "util.h"
#include "auteur.h"

using namespace std;
using namespace __gnu_cxx;      //For using c++ <hashmap>

#define NBR_EXAMPLAIRE_DEPART 100

//-----------------------declaration LivreData ---------------------------------
class LivreData : public RefCounted {
    public:
        LivreData(unsigned int id,
            string titre,
            string dateDePublication,
            unsigned int nbreExemplairesTotal,
            unsigned int nbreExemplairesEmprunter,
            unsigned int id_auteur,
            string image);
        LivreData(const LivreData &ld);

        static void affiche_livreData(vector<LivreData> &v);
        const string to_string(const string &separateur=" ");

        ~LivreData();

        void operator=(const LivreData &ld);

        unsigned int id = -1;
        string titre;
        string dateDePublication;
        unsigned int nbreExemplairesTotal;
        unsigned int nbreExemplairesEmprunter;
        unsigned int id_auteur;
        string image;

        AuteurData *auteur = NULL;

};


//-----------------------declaration Livre ------------------------------
class Livre{
        public:
            static bool ajouter(const string titre,const string dateDePublication,unsigned int id_auteur);
            static bool ajouter(const string titre,const string dateDePublication,unsigned int id_auteur,string image);
            static bool modifierTitre(unsigned int id,const string &titre);
            static bool modifierDateDePublication(unsigned int id,const string &dateDePublication);
            static bool modifierImage(unsigned int id,const string &image);
            static bool supprimer(unsigned int id);
            static bool consulter(vector<LivreData> &livres,const string &concat="");

            static bool modifierTitres(const vector<unsigned int> &ids, const string &titre);
            static bool modifierDateDePublications(const vector<unsigned int> &ids,const string &DateDePublication);
            static bool modifierImage(const vector<unsigned int> &ids, const string &image);
            static bool supprimer(const vector<unsigned int> &ids);
            static bool consulter(vector<LivreData> &livres,const vector<unsigned int> &ids,const string &condition="",const string &concat="");

            /* valeur[0] change ids[0] et ainsi de suite.
             *  en temps normal on retourne le nombre de champs modifies
             *  on ne fait rien si les deux(02) vecteurs n'ont pas la meme taille et on retourne -1
             */
            static bool modifierTitres_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &titres);
            static bool modifierDateDePublications_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &dateDePublications);
            static bool modifierImages_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &images);

            static bool ajouterNbreDeCopies(unsigned int id,unsigned int nbreAAjouter);
            static bool enleverNbreDeCopies(unsigned int id,unsigned int nbreAEnlever);
            static bool consulterLivresEmprunterTrieParNom(vector<LivreData> &livres,bool isAsc=true);
            static bool consulterLivresEmprunterTrieParDate(vector<LivreData> &livres,bool isAsc=true); //par la date de l'emprunte

            static bool exportToFile(vector<LivreData> &data,const string &nom_fichier,const string &separateur=" ");
            static bool exportToFile(const string &nom_fichier,const string &separateur=" ");
            static unsigned int importToVector(vector<LivreData> &data,string nom_fichier,const string &separateur=" ");//importe dans un tableau dynamique, retourne le nombre d'elements ajoutes
            static unsigned int importToDB(string nom_fichier,const string &separateur=" "); // met dans la base de donnees
        private:
            static vector<string> vChamps;
            static vector<string> vChamps_full;
            static string nomTable;

            static bool getAuteurDataPtrs(hash_map<unsigned int,AuteurData*> &vals,const vector<unsigned int> &ids,const string &concat="");
    };

#endif // LIVRE_H
