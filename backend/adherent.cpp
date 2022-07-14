
#include "root.h"
#include "adherent.h"

vector<string> Adherent::vChamps = {"nom","addresse","nbreLivresEmprunter"};
string Adherent::nomTable = "adherent";


bool Adherent::ajouter(const string nom,const string addresse){
    vector<string> vValeurs = {"'"+nom+"'","'"+addresse+"'","'"+to_string(0)+"'"};

    return Root::recupererBD().ajouter(nomTable,vChamps,vValeurs);
}

bool Adherent::modifierNom(unsigned int id,const string &nom){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[0]},{"'"+nom+"'"},"","id");
}

bool Adherent::modifierNoms(const vector<unsigned int> &ids, const string &nom){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[0]},{"'"+nom+"'"},"","id");
}

bool Adherent::modifierAddresse(unsigned int id,const string addresse){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[1]},{"'"+addresse+"'"},"","id");
}

bool Adherent::modifierAddresses(const vector<unsigned int> &ids,const string &addresse){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[1]},{"'"+addresse+"'"},"","id");
}

unsigned int Adherent::modifierNoms_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &noms){
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

unsigned int Adherent::modifieraddresses_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &addresses){
    unsigned int idsLen = ids.size();
    unsigned int addressesLen = addresses.size();
    unsigned int nbrChampsModifie = 0;

    if(idsLen == addressesLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(modifierAddresse(ids[i],addresses[i])){
                nbrChampsModifie++;
            }
        }
        return nbrChampsModifie;
    }else return -1;
}

bool Adherent::supprimer(unsigned int id){
    return Root::recupererBD().supprimer(nomTable,{id},"id");
}

bool Adherent::supprimer(const vector<unsigned int> &ids){
    return Root::recupererBD().supprimer(nomTable,ids);
}

bool Adherent::consulter(vector<AdherentData> &adherents,const string &concat){
    vector<string> vValeurs;

    if(!Root::recupererBD().consulter(nomTable,vChamps,vValeurs,concat)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps.size()){
        AdherentData data(vValeurs[i],vValeurs[i+1],strtoll(vValeurs[i+2].c_str(),NULL,10));
        adherents.push_back(data);
    }

    return true;
}

#include <cstring>

bool Adherent::consulter(vector<AdherentData> &adherents,const vector<unsigned int> &ids,const string &condition,const string &concat){
    vector<string> vValeurs;

    if(!Root::recupererBD().consulter(nomTable,ids,vChamps,vValeurs,condition,concat)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps.size()){
        AdherentData data(vValeurs[i],vValeurs[i+1],strtoll(vValeurs[i+2].c_str(),NULL,10));
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

                AdherentData ad(dataTemp[0],dataTemp[1],strtoll(dataTemp[2].c_str(),NULL,10));
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

AdherentData::AdherentData(const AdherentData &ad){
    *this = ad;
}


const string AdherentData::to_string(const string &separateur){
    string *res = new string();
    res->append(nom); res->append(separateur);
    res->append(addresse); res->append(separateur);
    res->append(std::to_string(nbreLivresEmprunter));
    return *res;
}

void AdherentData::affiche_adherentData(vector<AdherentData> &v){
    for(unsigned int i = 0;i<v.size();i++){
        cout << v[i].to_string("-") << endl;
    }
}
