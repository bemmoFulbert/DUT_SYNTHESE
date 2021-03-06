#ifndef BDR_SQLITE3_H_INCLUDED
#define BDR_SQLITE3_H_INCLUDED

#include "WeakSQLCommandGenerator.h"
#include "sqlite3.h"


/*
    Initially written by tjordan on the 10th July 2022
*/

/*
    Could enable the object to provide sqlite3_error_code on errors
    (vector<unsigned int> ids) could become (vector<string> ids) for more generic ids(they may not necessarily be integers !!!)
*/
class BDR_SQLite3{
    private:
        string filename;
        sqlite3 *db_handle;
        bool is_open;
    public:
        BDR_SQLite3(const string &nomFichierBD){
            filename = nomFichierBD;
            is_open = ((sqlite3_open(nomFichierBD.c_str(),&db_handle) == SQLITE_OK) ? true : false);
            if (!is_open){
                cerr << "*Avertissement* BDR_SQLite:: " << this << " n'a pas pu être ouvert" << endl;
            }
        };
        ~BDR_SQLite3(){
            sqlite3_close(db_handle);
            this->db_handle = NULL;

            cout << "*Avertissement* BDR_SQLite::~BDR_SQLite : ce destructeur a éte appellé" << endl;
        };

    public:
        bool estOuvert() const{
            return is_open;
        };

        sqlite3* recupererObjetSQLite3(){
            return db_handle;
        };

        string recupererNomFichierBD() const{
            return filename;
        };

        bool executerCommandeSQL(const string &commande_sql,int (*callback)(void *userdata,int nb_columns,char **row,char **header_row) = NULL,void *userdata = NULL){
            char *err_msg;
            string com = commande_sql;
            if (sqlite3_exec(this->db_handle,com.c_str(),callback,userdata,&err_msg)){
                cerr << "*Fatale* BDR_SQLite::executerCommandeSQL : " << err_msg << endl;
                cerr << com << endl;
                sqlite3_free(err_msg);
                return false;
            }

            return true;
        };

        bool executerCommandeSQL(const string &commande_sql,vector<string> &vals){
            return executerCommandeSQL(commande_sql,BDR_SQLite3::consulter_cb,(void*)&vals);
        };


    public:
        /*
            A noter que  (valeurs.size() / nomChamps.size()) doit être le nombre de tuples a ajouter
        */
        bool ajouter(const string &nomTable,const vector<string> &nomChamps,const vector<string> &valeurs){
            /*double l = (double)valeurs.size()/(double)nomChamps.size();
            if (l != (long long)l){
                cerr << "*Warning* un tuple de valeurs incomplet a éte detecter sur une appelle de la fonction TableBDR::ajouter" << endl;
            }*/

            char *err_msg;
            string com = WeakSQLCommandGenerator::Insert(nomTable,nomChamps,valeurs);
            if (sqlite3_exec(db_handle,com.c_str(),NULL,NULL,&err_msg)){
                cerr << "*Fatale* BDR_SQLite::ajouter : " << err_msg << endl;
                cerr << com << endl;
                sqlite3_free(err_msg);
                return false;
            }
            return true;
        }


        /*
            A noter que nouvelValeurs.size() == nomChamps.size()

            "UPDATE nomTable SET .... WHERE (" + cond + ")"  , si (cond != "")
            "UPDATE nomTable SET ...."  , si (cond == "")
        */
        bool modifier(const string &nomTable,const vector<string> &nomChamps,const vector<string> &nouvelValeurs,const string &cond=""){
            char *err_msg;
            string com = WeakSQLCommandGenerator::Update(nomTable,nomChamps,nouvelValeurs,cond);
            if (sqlite3_exec(db_handle,com.c_str(),NULL,NULL,&err_msg)){
                cerr << "*Fatale* BDR_SQLite::modifier : " << err_msg << endl;
                cerr << com << endl;
                sqlite3_free(err_msg);
                return false;
            }
            return true;
        };


        /*
            A noter que nouvelValeurs.size() == ids.size()*nomChamps.size()
        */
        bool modifier(const string &nomTable,const vector<unsigned int> &ids,const vector<string> &nomChamps,const vector<string> &nouvelValeurs,const string &cond="",const string &nomChampID="id"){
            string condID = "";

            char id_str[512];
            for (unsigned int i = 0 ; i < ids.size() ; i++){
                sprintf(id_str,"%u",ids[i]);
                condID += nomChampID + "=" + id_str + ((i == ids.size()-1) ? "" : " OR ");
            }

            if (!cond[0]){
                return modifier(nomTable,nomChamps,nouvelValeurs,condID);
            }
            return modifier(nomTable,nomChamps,nouvelValeurs,condID + " AND (" + cond + ")");
        };


        /*
            "DELETE FROM nomTable WHERE " + cond , si (cond != "")
            "DELETE FROM nomTable" , si (cond == "")
        */
        //Supprime les tuples en se basant sur des conditions
        bool supprimer(const string &nomTable,const string &cond=""){
            char *err_msg;
            string com = WeakSQLCommandGenerator::Delete(nomTable,cond);
            if (sqlite3_exec(db_handle,com.c_str(),NULL,NULL,&err_msg) != 0){
                cerr << "*Fatale* BDR_SQLite::supprimer : " << err_msg << endl;
                cerr << com << endl;
                sqlite3_free(err_msg);
                return false;
            }
            return true;
        };

        //Supprime les tuples avec les ids donner
        bool supprimer(const string &nomTable,const vector<unsigned int> &ids,const string &nomChampID="id"){
            string condID = "";

            char id_str[512];
            for (unsigned int i = 0 ; i < ids.size() ; i++){
                sprintf(id_str,"%u",ids[i]);
                condID += nomChampID + "=" + id_str + ((i == ids.size()-1) ? "" : " OR ");
            }
            return supprimer(nomTable,condID);
        };


        /* Le resultat sera charger dans le vecteur *valeurs* , concat est le code SQL a ajouter devant le "SELECT **** FROM nomTable " */
        //Consulte uniquement les champs specifier dans le vecteur nomChamps

        bool consulter(const string &nomTable,const vector<string> &nomChamps,vector<string> &valeurs,const string &concat=""){
            char *err_msg;
            string com = WeakSQLCommandGenerator::SelectFromOneTable(nomTable,nomChamps,concat);
            if (sqlite3_exec(db_handle,com.c_str(),consulter_cb,(void*)&valeurs,&err_msg) != 0){
                cerr << "*Fatale* BDR_SQLite::consulter : " << err_msg << endl;
                cerr << com << endl;
                sqlite3_free(err_msg);
                return false;
            }
            return true;
        };

        //Consulter les champs avec les ids(entiers)
        bool consulter(const string &nomTable,const vector<unsigned int> &ids,const vector<string> &nomChamps,vector<string> &valeurs,const string &cond="",const string &concat="",const string &nomChampID="id"){
            string condID = "";

            char id_str[512];
            for (unsigned int i = 0 ; i < ids.size() ; i++){
                sprintf(id_str,"%u",ids[i]);
                condID += nomChampID + "=" + id_str + ((i == ids.size()-1) ? "" : " OR ");
            }

            if (!cond[0]){
                return consulter(nomTable,nomChamps,valeurs, + "WHERE (" + condID + ") " + concat);
            }
            return consulter(nomTable,nomChamps,valeurs, + "WHERE (" + condID + " AND (" + cond + ")) " + concat);
        };

        //Consulter les champs avec les ids(chaine de charactéres)
        bool consulter(const string &nomTable,const vector<string> &ids,const vector<string> &nomChamps,vector<string> &valeurs,const string &cond="",const string &concat="",const string &nomChampID="id"){
            string condID = "";

            for (unsigned int i = 0 ; i < ids.size() ; i++){
                condID += nomChampID + "=" + ids[i] + ((i == ids.size()-1) ? "" : " OR ");
            }

            if (!cond[0]){
                return consulter(nomTable,nomChamps,valeurs, + "WHERE (" + condID + ") " + concat);
            }
            return consulter(nomTable,nomChamps,valeurs, + "WHERE (" + condID + " AND (" + cond + ")) " + concat);
        };



        //Consulte tout les champs d'une table
        bool consulter(const string &nomTable,vector<string> &valeurs,const string &concat=""){
            return consulter(nomTable,{"*"},valeurs,concat);
        };

        //Consulte des champs de plusieurs tables
        bool consulter(const vector<string> &nomTables,const vector<vector<string>> &tabNomChamps,vector<string> &valeurs,const string &concat=""){
            char *err_msg;
            string com = WeakSQLCommandGenerator::SelectFromManyTables(nomTables,tabNomChamps,concat);
            if (sqlite3_exec(db_handle,com.c_str(),consulter_cb,(void*)&valeurs,&err_msg) != 0){
                cerr << "*Fatale* BDR_SQLite::consulter : " << err_msg << endl;
                cerr << com << endl;
                sqlite3_free(err_msg);
                return false;
            }
            return true;
        };

    private:
        static int consulter_cb(void *userdata,int nb_columns,char **row,char **header_row){
            vector<string> *vals = (vector<string>*)userdata;

            for (int i = 0 ; i < nb_columns ; i++){
                if (row[i] == NULL)     vals->push_back(string(""));                //And what if row[i] is NULL ?
                else    vals->push_back(string(row[i]));
            }

            return 0;
        };

};

#endif // BDR_SQLITE3_H_INCLUDED
