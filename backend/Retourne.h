#ifndef RETOURNE_H_INCLUDED
#define RETOURNE_H_INCLUDED

#include "Emprunte.h"

#include <string>
#include <vector>
#include <hash_map>

#include "root.h"
#include "adherent.h"
#include "livre.h"
#include "util.h"

using namespace __gnu_cxx;      //For using c++ <hashmap>

class RetourneData : public RefCounted{     //Even though it not a child in the database tree
    public:
        unsigned int id;
        string date;
    public:
        EmprunteData *emprunte;
    public:
        RetourneData(unsigned int id,const string &date){
            this->id = id;
            this->date = date;
            this->emprunte = NULL;
        };
        RetourneData(const RetourneData &rd){
            *this = rd;
        }
        ~RetourneData(){
            if (emprunte)   emprunte->unref();
        };
    public:
        string to_string(const string &separateur) const{
            return string("Livre : " + emprunte->livre->to_string(separateur) + " Remis par : " + emprunte->adherent->to_string(separateur) + " le " + date);
        };

        void affiche() const{
            cout << to_string(",");
        };

        static void afficheVecteur(const vector<RetourneData> &retours){
            for (unsigned int i = 0 ; i < retours.size() ; i++){
                retours[i].affiche();
                cout << endl;
            }
        };

    public:
        void operator=(const RetourneData &ed){
            this->id = ed.id;
            this->date = ed.date;
            this->emprunte = ed.emprunte;
            if (this->emprunte)      this->emprunte->ref();
        };
};

class Retourne{
    public:
        static bool consulter(vector<RetourneData> &retours,const string &dateG="0000-00-00",const string &dateD="DATETIME()"){     	//Les emprunts entre la dateGauche et la dateDroite
            vector<string> vals;

            Root::recupererBD().consulter("Retourne",{"id","date"},vals," WHERE (date >= " + dateG + " AND  date <= " + dateD + ")");

            for (unsigned int i = 0 ; i < vals.size() ; i+=2){
                retours.push_back(RetourneData(Util::str_to_integer(vals[i]),vals[i+1]));
            }

            if (retours.size()){
                dut_puc2442_proj_backend_fill_child_field(EmprunteData,RetourneData,id,emprunte,retours,NULL,Retourne::getEmprunterDataPtrs,false);
            }

            return true;
        };

    private:
        //ids vector is gotten from a unique set
        static bool getEmprunterDataPtrs(hash_map<unsigned int,EmprunteData*> &vals,const vector<unsigned int> &ids){
            vector<EmprunteData> emprunts;

            bool res = Emprunte::consulter(emprunts,ids);

            if (!res)   return false;

            for (unsigned int i = 0 ; i < emprunts.size() ; i++){
                const unsigned int &id = ids[i];
                EmprunteData *emp = new EmprunteData(emprunts[i]);
                emp->unsafe_setRefCount(0);     //Inorder to not consider it's reference in the hashmap
                vals[id] = emp;
            }
            return true;
        };
};



#endif // RETOURNE_H_INCLUDED
