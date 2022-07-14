#include "auteur.h"

BDR_SQLite3 Auteur::bd("dut_puc2442_proj.db");
vector<string> Auteur::vChamps = {"nom","prenom"};
string Auteur::nomTable = "auteur";

bool Auteur::ajouter(const string &nom,const string &prenom){
    vector<string> vValeurs = {"'"+nom+"'","'"+prenom+"'"};

    return bd.ajouter(nomTable,vChamps,vValeurs);
}

bool Auteur::modifierNoms(const vector<unsigned int> &ids,const string &nom){
    return bd.modifier(nomTable,ids,{vChamps[0]},{"'"+nom+"'"});
}

bool Auteur::modifierNom(unsigned int id,const string &nom){
    return bd.modifier(nomTable,{id},{vChamps[0]},{"'"+nom+"'"},"","id");
}

bool Auteur::modifierPrenom(unsigned int id,const string &prenom){
    return bd.modifier(nomTable,{id},{vChamps[1]},{"'"+prenom+"'"},"","id");
}

bool Auteur::modifierPrenoms(const vector<unsigned int> &ids,const string &prenom){
    return bd.modifier(nomTable,ids,{vChamps[1]},{"'"+prenom+"'"},"","id");
}

unsigned int Auteur::modifierNoms_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &noms){
    unsigned int idsLen = ids.size();
    unsigned int nomsLen = noms.size();
    unsigned int nbrChampsModifie = 0;

    if(idsLen == nomsLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(modifierNom(ids[i],noms[i])){
                nbrChampsModifie++;
            }
        }
        return nbrChampsModifie;
    }else return -1;
}

unsigned int Auteur::modifierPrenoms_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &prenoms){
    unsigned int idsLen = ids.size();
    unsigned int prenomsLen = prenoms.size();
    unsigned int nbrChampsModifie = 0;

    if(idsLen == prenomsLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(modifierPrenom(ids[i],prenoms[i])){
                nbrChampsModifie++;
            }
        }
        return nbrChampsModifie;
    }else return -1;
}

bool Auteur::supprimer(unsigned int id){
    return bd.supprimer(nomTable,{id},"id");
}

bool Auteur::supprimer(const vector<unsigned int> &ids){
    return bd.supprimer(nomTable,ids);
}

bool Auteur::consulter(vector<AuteurData> &auteurs,const string &concat){
    vector<string> vValeurs;

    if(!bd.consulter(nomTable,vChamps,vValeurs,concat)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps.size()){
        AuteurData data(vValeurs[i],vValeurs[i+1]);
        auteurs.push_back(data);
    }

    return true;
}

bool Auteur::consulter(vector<AuteurData> &auteurs,const vector<unsigned int> &ids){
    vector<string> vValeurs;

    if(!bd.consulter(nomTable,ids,vChamps,vValeurs)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps.size()){
        AuteurData data(vValeurs[i],vValeurs[i+1]);
        auteurs.push_back(data);
    }
    return true;
}

bool Auteur::exportToFile(vector<AuteurData> &data, const string &nom_fichier, const string &separateur){
    ofstream flux(nom_fichier.c_str());
    if(flux){
        flux << "// fichier d'exportation d'auteurs" <<endl;
        flux << "// " << Util::vectorToString(vChamps,separateur)  << endl <<endl;

        for(unsigned int i=0;i<data.size();i++){
            flux << data[i].to_string(separateur) <<endl;
        }
        return true;
    }
    else {
        cout << "erreur d'ouverture du fichier \"" << nom_fichier << "\"" << endl;
        return false;
    }
}

bool Auteur::exportToFile(const string &nom_fichier,const string &separateur){
    vector<AuteurData> data;
    if(consulter(data)){
           return exportToFile(data,nom_fichier,separateur);
    }
    else return false;
}


unsigned int Auteur::importToVector(vector<AuteurData> &data,string nom_fichier,const string &separateur){
    ifstream flux (nom_fichier);
    string ligne;
    unsigned int i =0;

    if(flux){
        while(getline(flux,ligne)){
            vector<string> dataTemp;

            if(Util::isComment(ligne)){}
            else{
                dataTemp = Util::splitString(ligne,separateur);

                AuteurData ad(dataTemp[0],dataTemp[1]);
                data.push_back(ad);
                i++;
            }
        }
        return i;
    }
    else{
        cout << "erreur d'ouverture du fichier \"" << nom_fichier << "\"" << endl;
        return 0;
    }
}

unsigned int Auteur::importToDB(string nom_fichier,const string &separateur){
    vector<AuteurData> data;

    unsigned int nbrAjout = importToVector(data,nom_fichier,separateur);

    for(unsigned int i=0;i<data.size();i++){
        ajouter(data[i].nom,data[i].prenom);
    }
    return nbrAjout;
}

//-----------AuteurData----------------

AuteurData::AuteurData(string nom,string prenom){
    this->nom = nom;
    this->prenom = prenom;
}

AuteurData::AuteurData(unsigned int id,string nom,string prenom):
AuteurData(nom,prenom){
    this->id = id;
}

void AuteurData::affiche_auteurData(vector<AuteurData> &v){
    for(unsigned int i = 0;i<v.size();i++){
        cout << v[i].nom << " - " << v[i].prenom << endl;
    }
}

const string AuteurData::to_string(const string &separateur){
    string *res = new string();
    res->append(nom);
    res->append(separateur);
    res->append(prenom);
    return *res;
}
