#include "livre.h"

#include <string>
#include <vector>

#include "root.h"

vector<string> Livre::vChamps = {"titre","dateDePub","nbreExemplairesTotal","nbreExemplairesEmprunter","id_auteur"};
string Livre::nomTable = "livre";

bool Livre::ajouter(const string titre,const string dateDePublication,unsigned int id_auteur){
    vector<string> vValeurs = {"'"+titre+"'","'"+dateDePublication+"'","'"+to_string(100)+"'","'"+to_string(0)+"'","'"+to_string(id_auteur)+"'"};

    return Root::recupererBD().ajouter(nomTable,vChamps,vValeurs);
}

bool Livre::modifierTitre(unsigned int id,const string &titre){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[0]},{"'"+titre+"'"},"","id");
}

bool Livre::modifierTitres(const vector<unsigned int> &ids,const string &titre){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[0]},{"'"+titre+"'"},"","id");
}

bool Livre::modifierDateDePublication(unsigned int id,const string &dateDePublication){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[1]},{"'"+dateDePublication+"'"},"","id");
}

bool Livre::modifierDateDePublications(const vector<unsigned int> &ids,const string &dateDePublication){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[1]},{"'"+dateDePublication+"'"},"","id");
}

unsigned int Livre::modifierTitres_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &titres){
    unsigned int idsLen = ids.size();
    unsigned int titresLen = titres.size();
    unsigned int nbrChampsModifie = 0;

    if(idsLen == titresLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(modifierTitre(ids[i],titres[i])){
                nbrChampsModifie++;
            }
        }
        return nbrChampsModifie;
    }else return -1;
}

unsigned int Livre::modifierDateDePublications_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &dateDePublications){
    unsigned int idsLen = ids.size();
    unsigned int dateDePublicationsLen = dateDePublications.size();
    unsigned int nbrChampsModifie = 0;

    if(idsLen == dateDePublicationsLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(modifierDateDePublication(ids[i],dateDePublications[i])){
                nbrChampsModifie++;
            }
        }
        return nbrChampsModifie;
    }else return -1;
}

bool Livre::supprimer(unsigned int id){
    return Root::recupererBD().supprimer(nomTable,{id},"id");
}

bool Livre::supprimer(const vector<unsigned int> &ids){
    return Root::recupererBD().supprimer(nomTable,ids);
}

bool Livre::consulter(vector<LivreData> &livres,const string &concat){
    vector<string> vValeurs;

    if(!Root::recupererBD().consulter(nomTable,vChamps,vValeurs,concat)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps.size()){
        LivreData data(vValeurs[i],vValeurs[i+1],strtoll(vValeurs[i+2].c_str(),NULL,10),strtoll(vValeurs[i+3].c_str(),NULL,10),strtoll(vValeurs[i+4].c_str(),NULL,10));
        livres.push_back(data);
    }

    dut_puc2442_proj_backend_fill_child_field(AuteurData,LivreData,id_auteur,auteur,livres,NULL,Livre::getAuteurDataPtrs,concat,false);

    return true;
}

bool Livre::consulter(vector<LivreData> &livres,const vector<unsigned int> &ids,const string &condition,const string &concat){
    vector<string> vValeurs;

    if(!Root::recupererBD().consulter(nomTable,ids,vChamps,vValeurs,condition,concat)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps.size()){
        LivreData data(vValeurs[i],vValeurs[i+1],strtoll(vValeurs[i+2].c_str(),NULL,10),strtoll(vValeurs[i+3].c_str(),NULL,10),strtoll(vValeurs[i+4].c_str(),NULL,10));
        livres.push_back(data);
    }

    dut_puc2442_proj_backend_fill_child_field(AuteurData,LivreData,id_auteur,auteur,livres,&ids,Livre::getAuteurDataPtrs,"",false);

    /*
    hash_map<unsigned int,AuteurData*> h1;
    if (Livre::getAuteurDataPtrs(h1,&ids))    return false;

    for (unsigned int i = 0 ; i < livres.size() ; i++){
        LivreData &livre = livres[i];
        livre.auteur = h1[livre.id_auteur];
    }*/

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

                LivreData ad(dataTemp[0],dataTemp[1],strtoll(dataTemp[2].c_str(),NULL,10),strtoll(dataTemp[3].c_str(),NULL,10),strtoll(dataTemp[4].c_str(),NULL,10));
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

bool Livre::ajouterNbreDeCopies(unsigned int id,unsigned int nbreAAjouter){
    string requete = "UPDATE Livre SET nbreExemplairesTotal = nbreExemplairesTotal+"+to_string(nbreAAjouter)+" WHERE id="+to_string(id)+";";
    return Root::recupererBD().executerCommandeSQL(requete);
}

bool Livre::enleverNbreDeCopies(unsigned int id,unsigned int nbreAEnlever){
    string requete = "UPDATE Livre SET nbreExemplairesTotal = nbreExemplairesTotal-"+to_string(nbreAEnlever)+" WHERE id="+to_string(id)+";";
    return Root::recupererBD().executerCommandeSQL(requete);
}

bool Livre::getAuteurDataPtrs(hash_map<unsigned int,AuteurData*> &vals,const vector<unsigned int> *ids,const string &concat){
    vector<AuteurData> auteurs;

    bool res;

    if (ids){
        res = Auteur::consulter(auteurs,*ids);
    }
    else{
        res = Auteur::consulter(auteurs,concat);
    }

    if (!res)    return res;

    for (unsigned int i = 0 ; i < auteurs.size() ; i++){
        const unsigned int &id = auteurs[i].id;
        AuteurData *aut = new AuteurData(auteurs[i]);
        vals[id] = aut;
    }
    return true;
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
LivreData::LivreData(unsigned int id,
    string titre,
    string dateDePublication,
    unsigned int nbreExemplairesTotal,
    unsigned int nbreExemplairesEmprunter,
          unsigned int id_auteur):
LivreData(titre,dateDePublication,nbreExemplairesTotal,nbreExemplairesEmprunter,id_auteur){
    this->id = id;
}

LivreData::LivreData(const LivreData &ld){
    *this = ld;
}


LivreData::~LivreData(){
    if (this->auteur)   auteur->unref();
}

void LivreData::operator=(const LivreData &ld){
    *this = ld;
    if (this->auteur)   this->auteur->ref();
}

void LivreData::affiche_livreData(vector<LivreData> &v){
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
