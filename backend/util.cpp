#include "util.h"

vector<string> Util::splitString(string chaine, string separateur){
    size_t pos_start = 0, pos_end;
    string element;
    vector<string> res;

    while ((pos_end = chaine.find(separateur, pos_start)) != string::npos) {
        element = chaine.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + separateur.length();
        res.push_back(element);
    }

    res.push_back(chaine.substr (pos_start));
    return res;
}

string Util::vectorToString(const vector<string> &v,const string &separateur){
    string res;
    for(unsigned int i=0;i<v.size();i++){
        res.append(v[i]);
        res.append(separateur);
    }
    return res;
}

bool Util::isComment(const string &ligne){
    if(ligne[0] == '/' && ligne[1] == '/'){return true;}
    else if(ligne[0] == '#'){return true;}
    else if(ligne.empty()){return true;}
    else return false;
}


long long Util::str_to_integer(const string &str){
    return strtoll(str.c_str(),NULL,10);
}

double Util::str_to_decimal(const string &str){
    return strtod(str.c_str(),NULL);
}

string Util::stringify(const string &str){
    return "\"" + str + "\"";
}

string Util::integer_to_str(long long i){
    return std::to_string(i);
}

string Util::decimal_to_str(double d){
    return std::to_string(d);
}

string Util::bool_to_str(bool b){
    return b ? "true" : "false";
}
