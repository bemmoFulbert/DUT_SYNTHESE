#include "adherent.h"

BDR_SQLite3 Adherent::bd("dut_puc2442_proj.db");
vector<string> Adherent::vChamps = {"nom","addresse","nbreLivresEmprunter"};
string Adherent::nomTable = "adherent";


bool Adherent::ajouter(const string nom,const string addresse){
    vector<string> vValeurs = {"'"+nom+"'","'"+addresse+"'","'"+to_string(0)+"'"};

    return bd.ajouter(nomTable,vChamps,vValeurs);
}

bool Adherent::modifierNom(unsigned int id,const string &nom){
    return bd.modifier(nomTable,{id},{vChamps[0]},{"'"+nom+"'"},"","id");
}

bool Adherent::modifierNom(const vector<unsigned int> &ids, const string &nom){
    return bd.modifier(nomTable,ids,{vChamps[0]},{"'"+nom+"'"},"","id");
}

bool Adherent::modifierAddresse(unsigned int id,const string addresse){
    return bd.modifier(nomTable,{id},{vChamps[1]},{"'"+addresse+"'"},"","id");
}

bool Adherent::modifierAddresse(const vector<unsigned int> &ids,const string &addresse){
    return bd.modifier(nomTable,ids,{vChamps[1]},{"'"+addresse+"'"},"","id");
}

bool Adherent::supprimer(unsigned int id){
    return bd.supprimer(nomTable,{id},"id");
}

bool Adherent::supprimer(const vector<unsigned int> &ids){
    return bd.supprimer(nomTable,ids);
}

bool Adherent::consulter(vector<AdherentData> &adherents,const string &concat){
    vector<string> vValeurs;

    if(!bd.consulter(nomTable,vChamps,vValeurs,concat)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps.size()){
        AdherentData data(vValeurs[i],vValeurs[i+1],stoi(vValeurs[i+2]));
        adherents.push_back(data);
    }

    return true;
}

bool Adherent::consulter(vector<AdherentData> &adherents,const vector<unsigned int> &ids,const string &condition,const string &concat){
    vector<string> vValeurs;

    if(!bd.consulter(nomTable,ids,vChamps,vValeurs,condition,concat)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps.size()){
        AdherentData data(vValeurs[i],vValeurs[i+1],stoi(vValeurs[i+2]));
        adherents.push_back(data);
    }

    return true;
}

bool Adherent::consulterEmprunteurTrieParNom(vector<AdherentData> &adherents,bool isAsc){
    if(isAsc){
        return consulter(adherents,",Emprunte where Emprunte.id_adherent = Adherent.id order by Adherent.nom asc");
    }
    else{
        return consulter(adherents,",Emprunte where Emprunte.id_adherent = Adherent.id order by Adherent.nom desc");
    }
}

bool Adherent::consulterEmprunteurTrieParDate(vector<AdherentData> &adherents,bool isAsc){
    if(isAsc){
        return consulter(adherents,",Emprunte where Emprunte.id_adherent = Adherent.id order by Emprunte.date asc");
    }
    else{
        return consulter(adherents,",Emprunte where Emprunte.id_adherent = Adherent.id order by Emprunte.date desc");
    }
}

bool Adherent::exportToFile(vector<AdherentData> &data,const string &nom_fichier,const string &separateur){
    ofstream flux(nom_fichier.c_str());
    if(flux){
        flux << "// fichier d'exportation de adherents" <<endl;
        flux << "// "<< Util::vectorToString(vChamps,separateur) << endl <<endl;

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

bool Adherent::exportToFile(const string &nom_fichier,const string &separateur){
    vector<AdherentData> data;
    if(consulter(data)){
           return exportToFile(data,nom_fichier,separateur);
    }
    else return false;
}

unsigned int Adherent::importToVector(vector<AdherentData> &data,string nom_fichier,const string &separateur){
    ifstream flux (nom_fichier);
    string ligne;
    unsigned int i =0;

    if(flux){
        while(getline(flux,ligne)){
            vector<string> dataTemp;

            if(Util::isComment(ligne)){}
            else{
                dataTemp = Util::splitString(ligne,separateur);

                AdherentData ad(dataTemp[0],dataTemp[1],stoi(dataTemp[2]));
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

unsigned int Adherent::importToDB(string nom_fichier,const string &separateur){
    vector<AdherentData> data;

    unsigned int nbrAjout = importToVector(data,nom_fichier,separateur);

    for(unsigned int i=0;i<data.size();i++){
        ajouter(data[i].nom,data[i].addresse);
    }
    return nbrAjout;
}

//----------------AdherentData--------------

AdherentData::AdherentData(string nom,
                           string addresse,
                           unsigned int nbreLivresEmprunter){
    this->nom = nom;
    this->addresse = addresse;
    this->nbreLivresEmprunter = nbreLivresEmprunter;
}

AdherentData::AdherentData(unsigned int id,string nom,string addresse,unsigned int nbreLivresEmprunter):
AdherentData(nom,addresse,nbreLivresEmprunter){
    this->id = id;
}

const string AdherentData::to_string(const string &separateur){
    string *res = new string();
    res->append(nom); res->append(separateur);
    res->append(addresse); res->append(separateur);
    res->append(std::to_string(nbreLivresEmprunter));
    return *res;
}
