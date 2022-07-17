#ifndef ROOT_H_INCLUDED
#define ROOT_H_INCLUDED

#include <iostream>

#include "BDR_SQLite3.h"
#include "UniqueSet.h"

using namespace std;

//This macro can be optimized by removing the *in_vector_of_ids_ptr* arg and and all it's related chunks of code sice the UniqueSet here is mandatory
//For use in Data classes of database tables containing complex fields(which are also data classes)
#define dut_puc2442_proj_backend_fill_child_field(child_data_type,this_data_type,child_id_field,child_field,out_vector_of_xxx_data,in_vector_of_ids_ptr,get_xxx_data_ptrs_func_name,ret_val_if_fail)  \
    if (1){     \
        vector<unsigned int> _ids_;     \
        if (in_vector_of_ids_ptr == NULL){     \
            UniqueSet<unsigned int> __ids;      \
            for (unsigned int i = 0 ; i < out_vector_of_xxx_data.size() ; i++){     \
                __ids.push_back(out_vector_of_xxx_data[i].child_id_field);     \
            }       \
            _ids_ = __ids.getInternalVector();     \
            \
        }       \
        else{   \
            _ids_ = *(vector<unsigned int>*)(in_vector_of_ids_ptr);    \
        }   \
        hash_map<unsigned int,child_data_type*> h1;    \
        if (get_xxx_data_ptrs_func_name(h1,_ids_) == false)    return ret_val_if_fail;    \
        for (unsigned int i = 0 ; i < out_vector_of_xxx_data.size() ; i++){    \
            this_data_type &elem = out_vector_of_xxx_data[i];    \
            elem.child_field = (child_data_type*) h1[elem.child_id_field]->ref();  \
        }    \
    }    \

class Root{
    private:
        static BDR_SQLite3 *db;
        //D'autres fonctionnalités ou données qui sont globale au package backend doivent être ajouter ici ...
    public:
        static BDR_SQLite3& recupererBD(){
            return *db;
        };

        static void chargerBD(BDR_SQLite3 &nouvelBD){
            if (!nouvelBD.estOuvert()){
                cerr << "*Avertissement* backend::Root::chargerBD : la nouvelle BD n'est pas ouvert !!!" << endl;
            }
            else{
                nouvelBD.executerCommandeSQL("PRAGMA foreign_keys=on;");
                cout << "*Info* backend::Root::chargerBD : la nouvelle BD a bien eté charger dans l'objet Root" << endl;
            }
            db = &nouvelBD;
        };


};


#endif // ROOT_H_INCLUDED
