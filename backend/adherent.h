#ifndef ADHERENT_H
#define ADHERENT_H

#include <string>
#include <vector>
#include <fstream>


#include "BDR_SQLite3.h"
#include "RefCounted.h"
#include <QStringList>

#include "util.h"

using namespace std;

//-----------------------declaration AdherentData --------------------------
class AdherentData : public RefCounted{
    public:

        AdherentData(unsigned int id,string nom,
            string addresse,
            unsigned int nbreLivresEmprunter,
            string prenom,string email, string dateDeNaissance, string sexe);

        AdherentData(const AdherentData &ad);

        const string to_string(const string &separateur=" ");
        static void affiche_adherentData(vector<AdherentData> &v);
        static void toQStringLists(const vector<AdherentData> &vAdhData,QStringList &ids, QStringList &addresses, QStringList &nbreLivresEmprunters, QStringList &prenoms, QStringList &emails, QStringList &dateDeNaissances,QStringList &sexes);

        unsigned int id = -1;
        string nom;
        string addresse;
        string prenom;
        string email;
        string dateDeNaissance;
        string sexe;
        unsigned int nbreLivresEmprunter;
};


//-----------------------declaration AdherentData --------------------------
class Adherent{
        public:
            static bool ajouter(const string &nom, const string &addresse, const string &prenom, const string &email, const string &dateDeNaissance, const string &sexe);
            static bool modifierNom(unsigned int id,const string &nom);
            static bool modifierAddresse(unsigned int id,const string addresse);

            static bool modifierPrenom(unsigned int id,const string prenom);
            static bool modifierEmail(unsigned int id,const string email);
            static bool modifierDateDeNaissance(unsigned int id,const string dateDeNaissance);
            static bool modifierSexe(unsigned int id,const string sexe);

            static bool supprimer(unsigned int id);
            static bool consulter(vector<AdherentData> &adherents,const string &concat="");

            static bool modifierNoms(const vector<unsigned int> &ids, const string &nom);
            static bool modifierAddresses(const vector<unsigned int> &ids,const string &addresse);

            static bool modifierPrenoms(const vector<unsigned int> &ids,const string &prenom);
            static bool modifieEmails(const vector<unsigned int> &ids,const string &email);
            static bool modifierDateDeNaissances(const vector<unsigned int> &ids,const string &dateDeNaissance);
            static bool modifierSexes(const vector<unsigned int> &ids,const string &sexe);

            static bool supprimer(const vector<unsigned int> &ids);
            static bool consulter(vector<AdherentData> &adherents,const vector<unsigned int> &ids,const string &condition="",const string &concat="");

            /* valeur[0] change ids[0] et ainsi de suite.
             *  on retourne true si au moins 1 enregistrement a ete sauvegarde
             *  on ne fait rien si les deux(02) vecteurs n'ont pas la meme taille et on retourne false
             */
            static bool modifierNoms_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &noms);
            static bool modifierAddresses_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &addresses);

            static bool modifierPrenoms_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &prenoms);
            static bool modifierEmails_WithDiffValues(const vector<unsigned int> &ids, const vector<string> &emails);
            static bool modifierDateDeNaissances_WithDiffValues(const vector<unsigned int> &ids, const vector<string> &dateDeNaissances);
            static bool modifierSexes_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &sexes);

            static bool emprunterLivre(unsigned int id_livre,unsigned int id_adherent);
            static bool rendreLivre(unsigned int id_livre,unsigned int id_adherent);

            static bool consulterEmprunteurTrieParNom(vector<AdherentData> &adherents,bool isAsc=true);
            static bool consulterEmprunteurTrieParDate(vector<AdherentData> &adherents,bool isAsc=true);

            static bool exportToFile(vector<AdherentData> &data,const string &nom_fichier,const string &separateur=" ");
            static bool exportToFile(const string &nom_fichier,const string &separateur=" ");
            static unsigned int importToVector(vector<AdherentData> &data,string nom_fichier,const string &separateur=" ");//importe dans un tableau dynamique, retourne le nombre d'elements ajoutes
            static unsigned int importToDB(string nom_fichier,const string &separateur=" "); // met dans la base de donnees
            static vector<string> getVChamps_full(){
                return vChamps_full;
            }
private:
        static vector<string> vChamps ;
        static vector<string> vChamps_full;
        static string nomTable;
    };
#endif // ADHERENT_H
