#ifndef EMPRUNTE_H_INCLUDED
#define EMPRUNTE_H_INCLUDED

#include <string>
#include <vector>
#include <hash_map>

#include "BDR_SQLite3.h"



class LivreData;
class AdherentData;

static BDR_SQLite3 bd;


#define EMPRUNTE_NUM_FIELDS 3

class EmprunteData{
    public:
        string date;
        unsigned int id_livre;
        unsigned int id_adherent;
    public:
        EmprunteData(const string &date,const LivreData &livre,const AdherentData &adherent){
            this->date = date;
            this->id_livre = livre.id;
            this->id_adherent = adherent.id;
            this->livre = livre;
            this->adherent = adherent;
        };
};

class Emprunte{
    /*private:
        static hash_map<string,LivreData*> livres;
        static hash_map<string,AdherentData*> adherents;
    */
    public:
        static bool consulterEmprunts(vector<EmprunteData> &emprunts,const string &dateG,const string &dateD){      	//Les emprunts entre la dateGauche et la dateDroite
            vector<string> tabs = {"Emprunte","Livre","Adherent"};
            vector<string> fields = {{"*"},{""},"Adherent"};
            vector<string> vals;

            bd.consulter("Emprunte",tabs,vals,"WHERE (date >= " + dateG + " AND  date <= " + dateD + ")");

            return true;
        };
};


#endif // EMPRUNTE_H_INCLUDED
