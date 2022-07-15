#ifndef EMPRUNTE_H_INCLUDED
#define EMPRUNTE_H_INCLUDED

#include <string>
#include <vector>
#include <hash_map>

#include "root.h"
#include "adherent.h"
#include "livre.h"
#include "util.h"

using namespace __gnu_cxx;      //For using c++ <hashmap>

class EmprunteData{
    public:
        string date;
        unsigned int id_livre;
        unsigned int id_adherent;
    public:
        LivreData *livre;
        AdherentData *adherent;
    public:
        EmprunteData(const string &date,unsigned int livre_id,unsigned int adherent_id){
            this->date = date;
            this->id_livre = livre_id;
            this->id_adherent = adherent_id;
            this->livre = NULL;
            this->adherent = NULL;
        };
        ~EmprunteData(){
            if (livre)  livre->unref();
            if (adherent)   adherent->unref();
        };
    public:
        string to_string(const string &separateur) const{
            return string("Livre : " + livre->to_string(separateur) + " Prété par : " + adherent->to_string(separateur) + date);
        };

        void affiche() const{
            cout << to_string(",");
        };

        static void afficheVecteur(const vector<EmprunteData> &emprunts){
            for (unsigned int i = 0 ; i < emprunts.size() ; i++){
                emprunts[i].affiche();
                cout << endl;
            }
        };

    public:
        void operator=(const EmprunteData &ed){
            this->date = ed.date;
            this->id_adherent = ed.id_adherent;
            this->id_livre = ed.id_livre;
            this->livre = ed.livre;
            this->adherent = ed.adherent;

            if (livre)      livre->ref();
            if (adherent)      adherent->ref();
        };
};

class Emprunte{
    public:
        static bool consulterEmprunts(vector<EmprunteData> &emprunts,const string &dateG="0000-00-00",const string &dateD="DATETIME()"){     	//Les emprunts entre la dateGauche et la dateDroite
            vector<string> vals;

            Root::recupererBD().consulter("Emprunte",{"date","livre_id","adherent_id"},vals,"WHERE (date >= " + dateG + " AND  date <= " + dateD + ")");

            for (unsigned int i = 0 ; i < vals.size() ; i+=3){
                emprunts.push_back(EmprunteData(vals[i],Util::str_to_integer(vals[i+1]),Util::str_to_integer(vals[i+2])));
            }

            dut_puc2442_proj_backend_fill_child_field(LivreData,EmprunteData,id_livre,livre,emprunts,NULL,getLivreDataPtrs,false);
            dut_puc2442_proj_backend_fill_child_field(AdherentData,EmprunteData,id_adherent,adherent,emprunts,NULL,getAdherentDataPtrs,false);

            return true;
        };

    private:
        //ids vector is gotten from a unique set
        static bool getLivreDataPtrs(hash_map<unsigned int,LivreData*> &vals,const vector<unsigned int> &ids){
            vector<LivreData> livres;

            bool res = Livre::consulter(livres,ids);

            for (unsigned int i = 0 ; i < livres.size() ; i++){
                const unsigned int &id = ids[i];
                LivreData *liv = new LivreData(livres[i]);
                liv->unsafe_setRefCount(0);     //Inorder to not consider it's reference in the hashmap
                vals[id] = liv;
            }
            return true;
        };

        static bool getAdherentDataPtrs(hash_map<unsigned int,AdherentData*> &vals,const vector<unsigned int> &ids){
            vector<AdherentData> adherents;

            bool res = Adherent::consulter(adherents,ids);

            if (!res)    return res;

            for (unsigned int i = 0 ; i < adherents.size() ; i++){
                const unsigned int &id = ids[i];
                AdherentData *adh = new AdherentData(adherents[i]);
                adh->unsafe_setRefCount(0);     //Inorder to not consider it's reference in the hashmap
                vals[id] = adh;
            }
            return true;
        };
};


#endif // EMPRUNTE_H_INCLUDED
