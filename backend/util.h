#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

using namespace std;

class Util
{
public:
    static vector<string> splitString(string chaine, string separateur);// separer une chaine de caractere par rapport a un separateur
    static string vectorToString(const vector<string> &v,const string &separateur=" ");// vecteur pour une chaine de caratere les element sont separer par le separateur
    static bool isComment(const string &ligne);// verifie si une ligne est un commentaire
};

#endif // UTIL_H
