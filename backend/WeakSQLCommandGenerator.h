#ifndef WEAKSQLCOMMANDGENERATOR_H_INCLUDED
#define WEAKSQLCOMMANDGENERATOR_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

/*
    Initially written by tjordan on the 10th July 2022
*/


using namespace std;

/*
    This class provides a set of methods that generates weak sql commands from userdata
    The *weak* here means the expected sql strings provided by the user are not checked by an sql parser
*/
class WeakSQLCommandGenerator{
    /*
        - Could add *delimiter or statement_terminator* argument
        - Could add enableLogging/disableLogging
    */

    public:

        static string Insert(const string &tableName,const vector<string> &fieldNames,const vector<string> &values){
            double l = (double)values.size()/(double)fieldNames.size();
            if (l != (long long)l){
                cerr << "*Warning* function WeakSQLCommandGenerator::Insert : the number of values divided by the number of fieldNames must not be a fraction or an incomplete tuple shall be encountered" << endl;
            }
            if (!fieldNames.size()){
                cerr << "*Fatal* function WeakSQLCommandGenerator::Insert : the fieldNames array must not be empty" << endl;
            }

            string sql_com = "";

            unsigned int num_columns = fieldNames.size();
            unsigned int num_rows = values.size()/fieldNames.size();

            string headers = "";
            for (unsigned int i = 0 ; i < num_columns ; i++){
                headers += fieldNames[i] + ",";
            }

            for (unsigned int k = 0 ; k < num_rows ; k++){

                sql_com += "INSERT INTO " + tableName + "(";

                sql_com += headers;
                sql_com[sql_com.size() - 1] = ')';
                sql_com += " VALUES(";

                string vals = "";
                for (unsigned int i = k*num_columns , stop = i + num_columns ; i < stop ; i++){
                    vals += values[i] + ",";
                }
                sql_com += vals;
                sql_com[sql_com.size() - 1] = ')';
                sql_com += ";";
            }

            return sql_com;
        };

        //*cond* here is an sql statement appended after the WHERE keyword , it must not include the semicolon and the main surrounding brackets
        static string Update(const string &tableName,const vector<string> &fieldNames,const vector<string> &newValues,const string &cond=""){
            if (fieldNames.size() != newValues.size()){
                cerr << "*Warning* function WeakSQLCommandGenerator::Update : the number of fieldNames must be equal to the number of newValues" << endl;
            }
            if (!fieldNames.size()){
                cerr << "*Fatal* function WeakSQLCommandGenerator::Update : the fieldNames array must not be empty" << endl;
            }
            if (!newValues.size()){
                cerr << "*Fatal* function WeakSQLCommandGenerator::Update : the newValuess array must not be empty" << endl;
            }


            string sql_com = "";

            unsigned int num_columns = fieldNames.size();

            sql_com += "UPDATE " + tableName + " SET ";

            string h = "";
            for (unsigned int i = 0 ; i < num_columns ; i++){
                h += fieldNames[i] + "=" + newValues[i] + ",";
            }
            h.pop_back();     //To remove the last comma character

            sql_com += h;

            if (cond[0])    sql_com += " WHERE (" + cond + ")";

            return sql_com + ";";
        };

        //*cond* here is an sql statement appended after the WHERE keyword, it must not include the semicolon and the main surrounding brackets
        static string Delete(const string &tableName,const string &cond=""){
            string sql_com = "";

            sql_com += "DELETE FROM " + tableName;

            if (cond[0])    sql_com += " WHERE (" + cond + ")";

            return sql_com + ";";
        };

        //*concat* here is an sql statement appended after the generated SELECT statement, it may not include the semicolon
        static string SelectFromOneTable(const string &tableName,const vector<string> &fieldNames,const string &concat=""){
            if (!fieldNames.size()){
                cerr << "*Fatal* function WeakSQLCommandGenerator::SelectFromOneTable : the fieldNames array must not be empty" << endl;
            }

            string sql_com = "";

            unsigned int num_columns = fieldNames.size();

            sql_com += "SELECT ";

            string h = "";
            for (unsigned int i = 0 ; i < num_columns ; i++){
                h += fieldNames[i]+",";
            }
            h.pop_back();      //Remove last comma character

            sql_com += h + " FROM " + tableName;

            if (concat[0])    sql_com += " " + concat;

            return sql_com + ";";
        };

        ////*concat* here is an sql statement appended after the generated SELECT statement, it may not include the semicolon
        static string SelectAllFromOneTable(const string &tableName,const string &concat=""){
            return SelectFromOneTable(tableName,{"*"},concat);
        };

        //*concat* here is an sql statement appended after the generated SELECT statement, it may not include the semicolon
        static string SelectFromManyTables(const vector<string> &tableNames,const vector<vector<string>> &fieldNamesArrays,const string &concat=""){
            if (fieldNamesArrays.size() != tableNames.size()){
                cerr << "*Warning* function WeakSQLCommandGenerator::SelectFromManyTables : the number of tableNames must be equal to the number of fieldNamesArrays" << endl;
            }
            if (!tableNames.size()){
                cerr << "*Fatal* function WeakSQLCommandGenerator::SelectFromManyTables : the tableNames array must not be empty" << endl;
            }
            if (!fieldNamesArrays.size()){
                cerr << "*Fatal* function WeakSQLCommandGenerator::SelectFromManyTables : the fieldNamesArrays array must not be empty" << endl;
            }


            string sql_com = "";

            sql_com += "SELECT ";

            //Field Names in format {TableName}.{FieldName}
            string h = "";
            for (unsigned int i = 0 ; i < tableNames.size() ; i++){
                for (unsigned int j = 0 ; j < fieldNamesArrays[i].size() ; j++){
                    h += tableNames[i] + "." + fieldNamesArrays[i][j] + ",";
                }
            }
            h.pop_back();      //Remove last comma character

            sql_com += h + " FROM ";

            //Table Names
            string g = "";
            for (unsigned int i = 0 ; i < tableNames.size() ; i++){
                g += tableNames[i] + ",";
            }
            g.pop_back();      //Remove last comma character

            sql_com += g;

            if (concat[0])    sql_com += " " + concat;

            return sql_com + ";";
        };

        //*concat* here is an sql statement appended after the generated SELECT statement, it may not include the semicolon
        static string SelectAllFromManyTables(const vector<string> &tableNames,const string &concat=""){
            if (!tableNames.size()){
                cerr << "*Fatal* function WeakSQLCommandGenerator::SelectAllFromManyTables : the tableNames array must not be empty" << endl;
            }


            string sql_com = "";

            sql_com += "SELECT * FROM ";

            //Table Names
            string g = "";
            for (unsigned int i = 0 ; i < tableNames.size() ; i++){
                g += tableNames[i] + ",";
            }
            g.pop_back();      //Remove last comma character

            sql_com += g;

            if (concat[0])    sql_com += " " + concat;

            return sql_com + ";";
        };

};


#endif // WEAKSQLCOMMANDGENERATOR_H_INCLUDED
