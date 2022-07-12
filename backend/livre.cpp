#include "livre.h"

#include <string>
#include <vector>

#include "BDR_SQLite3.h"

BDR_SQLite3 Livre::bd("dut_puc2442_proj.db");
vector<string> Livre::vChamps = {"titre","dateDePub","nbreExemplairesTotal","nbreExemplairesEmprunter","id_auteur"};

bool Livre::ajouter(const string titre,const string dateDePublication,unsigned int id_auteur){
    vector<string> vValeurs = {"'"+titre+"'","'"+dateDePublication+"'","'"+to_string(100)+"'","'"+to_string(0)+"'","'"+to_string(id_auteur)+"'"};

    return bd.ajouter("livre",vChamps,vValeurs);
}

bool Livre::modifierTitre(unsigned int id,const string titre){
    return bd.modifier("livre",{id},{vChamps[0]},{"'"+titre+"'"},"","id");
}

bool Livre::modifierDateDePublication(unsigned int id,const string dateDePublication){
    return bd.modifier("livre",{id},{vChamps[1]},{"'"+dateDePublication+"'"},"","id");
}

bool Livre::supprimer(unsigned int id){
    return bd.supprimer("livre",{id},"id");
}

bool Livre::consulter(vector<LivreData> &livres,const string &condition){
    vector<string> vValeurs;

    if(!bd.consulter("livre",vChamps,vValeurs,condition)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps.size()){
        LivreData data(vValeurs[i],vValeurs[i+1],stoi(vValeurs[i+2]),stoi(vValeurs[i+3]),stoi(vValeurs[i+4]));
        livres.push_back(data);
    }

    return true;
}

bool Livre::consulterLivresEmprunterTrieParNom(vector<LivreData> &livres,bool isAsc){
    if(isAsc){
        return consulter(livres,",Emprunte where Emprunte.id_livre = Livre.id order by Livre.titre asc");
    }
    else{
        return consulter(livres,",Emprunte where Emprunte.id_livre = Livre.id order by Livre.titre desc");
    }
}

bool Livre::consulterLivresEmprunterTrieParDate(vector<LivreData> &livres,bool isAsc){
    if(isAsc){
        return consulter(livres,",Emprunte where Emprunte.id_livre = Livre.id order by Emprunte.date asc");
    }
    else{
        return consulter(livres,",Emprunte where Emprunte.id_livre = Livre.id order by Emprunte.date desc");
    }
}

bool Livre::exportToFile(vector<LivreData> &data, const string &nom_fichier, const string &separateur){
    ofstream flux(nom_fichier.c_str());
    if(flux){
        flux << "// fichier d'exportation de livres" <<endl;
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

bool Livre::exportToFile(const string &nom_fichier,const string &separateur){
    vector<LivreData> data;
    if(consulter(data)){
           return exportToFile(data,nom_fichier,separateur);
    }
    else return false;
}

unsigned int Livre::importToVector(vector<LivreData> &data,string nom_fichier,const string &separateur){
    ifstream flux (nom_fichier);
    string ligne;
    unsigned int i =0;

    if(flux){
        while(getline(flux,ligne)){
            vector<string> dataTemp;

            if(Util::isComment(ligne)){}
            else{
                dataTemp = Util::splitString(ligne,separateur);

                LivreData ad(dataTemp[0],dataTemp[1],stoi(dataTemp[2]),stoi(dataTemp[3]),stoi(dataTemp[4]));
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

unsigned int Livre::importToDB(string nom_fichier,const string &separateur){
    vector<LivreData> data;

    unsigned int nbrAjout = importToVector(data,nom_fichier,separateur);

    for(unsigned int i=0;i<data.size();i++){
        ajouter(data[i].titre,data[i].dateDePublication,data[i].id_auteur);
    }
    return nbrAjout;
}

//----------LivreData-----------------

LivreData::LivreData(string titre,
    string dateDePublication,
    unsigned int nbreExemplairesTotal,
    unsigned int nbreExemplairesEmprunter,
                     unsigned int id_auteur){

    this->titre = titre;
    this->dateDePublication = dateDePublication;
    this->nbreExemplairesTotal = nbreExemplairesTotal;
    this->nbreExemplairesEmprunter = nbreExemplairesEmprunter;
    this->id_auteur = id_auteur;
}

void LivreData::affiche_livreData(vector<LivreData> v){
    for(unsigned int i = 0;i<v.size();i++){
        cout << v[i].titre << " - " << v[i].dateDePublication << " - " << v[i].nbreExemplairesTotal << " - "<< v[i].nbreExemplairesEmprunter << " - "<< v[i].id_auteur << endl;
    }
}

const string LivreData::to_string(const string &separateur){
    string *res = new string();
    res->append(titre); res->append(separateur);
    res->append(dateDePublication); res->append(separateur);
    res->append(std::to_string(nbreExemplairesTotal)); res->append(separateur);
    res->append(std::to_string(nbreExemplairesEmprunter)); res->append(separateur);
    res->append(std::to_string(id_auteur));
    return *res;
}
