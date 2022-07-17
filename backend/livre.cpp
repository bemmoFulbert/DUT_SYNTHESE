#include "livre.h"

#include <cstring>
#include <string>
#include <vector>

#include "root.h"

vector<string> Livre::vChamps_full = {"id","titre","dateDePub","nbreExemplairesTotal","nbreExemplairesEmprunter","id_auteur","image"};
vector<string> Livre::vChamps = {"titre","dateDePub","nbreExemplairesTotal","nbreExemplairesEmprunter","id_auteur","image"};
//---------------------------------0-----------1--------------2----------------------3-----------------------4--------5-------------
string Livre::nomTable = "livre";

<<<<<<< HEAD
bool Livre::ajouter(const string titre,const string dateDePublication,unsigned int nbreExemplairesTotal,unsigned int id_auteur){
    vector<string> vValeurs = {"\""+titre+"\"","\""+dateDePublication+"\"","\""+to_string(nbreExemplairesTotal)+"\"","\""+to_string(0)+"\"","\""+to_string(id_auteur)+"\""};
=======
bool Livre::ajouter(const string titre,const string dateDePublication,unsigned int id_auteur){
    vector<string> vChamps = {"titre","dateDePub","nbreExemplairesTotal","nbreExemplairesEmprunter","id_auteur"};
    vector<string> vValeurs = {"\""+titre+"\"","\""+dateDePublication+"\"","\""+to_string(NBR_EXAMPLAIRE_DEPART)+"\"","\""+to_string(0)+"\"","\""+to_string(id_auteur)+"\""};

    return Root::recupererBD().ajouter(nomTable,vChamps,vValeurs);
}

bool Livre::ajouter(const string titre,const string dateDePublication,unsigned int id_auteur,string image){
    vector<string> vValeurs = {"\""+titre+"\"","\""+dateDePublication+"\"","\""+to_string(NBR_EXAMPLAIRE_DEPART)+"\"","\""+to_string(0)+"\"","\""+to_string(id_auteur)+"\"","\""+image+"\""};
>>>>>>> b0c3dba5479333b0f7023b47366a1c5670193393

    return Root::recupererBD().ajouter(nomTable,vChamps,vValeurs);
}

bool Livre::modifierTitre(unsigned int id,const string &titre){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[0]},{"\""+titre+"\""},"","id");
}

bool Livre::modifierTitres(const vector<unsigned int> &ids,const string &titre){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[0]},{"\""+titre+"\""},"","id");
}

bool Livre::modifierDateDePublication(unsigned int id,const string &dateDePublication){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[1]},{"\""+dateDePublication+"\""},"","id");
}

bool Livre::modifierDateDePublications(const vector<unsigned int> &ids,const string &dateDePublication){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[1]},{"\""+dateDePublication+"\""},"","id");
}

bool Livre::modifierTitres_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &titres){
    unsigned int idsLen = ids.size();
    unsigned int titresLen = titres.size();
    bool err = true;

    if(idsLen == titresLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(!modifierTitre(ids[i],titres[i])){
                err = false;
            }
        }
    }else err = false;
    return err;
}

bool Livre::modifierDateDePublications_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &dateDePublications){
    unsigned int idsLen = ids.size();
    unsigned int dateDePublicationsLen = dateDePublications.size();
    bool err = true;

    if(idsLen == dateDePublicationsLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(!modifierDateDePublication(ids[i],dateDePublications[i])){
                err = false;
            }
        }
    }else err = false;
    return err;
}

bool Livre::modifierImage(unsigned int id,const string &image){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[5]},{"\""+image+"\""},"","id");
}

bool Livre::modifierImage(const vector<unsigned int> &ids, const string &image){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[5]},{"\""+image+"\""},"","id");
}

bool Livre::modifierImages_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &images){
    unsigned int idsLen = ids.size();
    unsigned int imagesLen = images.size();
    bool err = true;

    if(idsLen == imagesLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(!modifierImage(ids[i],images[i])){
                err = false;
            }
        }
    }else err = false;
    return err;
}

bool Livre::supprimer(unsigned int id){
    return Root::recupererBD().supprimer(nomTable,{id},"id");
}

bool Livre::supprimer(const vector<unsigned int> &ids){
    return Root::recupererBD().supprimer(nomTable,ids);
}

bool Livre::consulter(vector<LivreData> &livres,const string &concat){
    vector<string> vValeurs;

    if(!Root::recupererBD().consulter(nomTable,vChamps_full,vValeurs,concat)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps_full.size()){
        LivreData data(strtoll(vValeurs[i].c_str(),NULL,10),vValeurs[i+1],vValeurs[i+2],strtoll(vValeurs[i+3].c_str(),NULL,10),strtoll(vValeurs[i+4].c_str(),NULL,10),strtoll(vValeurs[i+5].c_str(),NULL,10),vValeurs[i+6]);
        livres.push_back(data);
    }

    if (vValeurs.size())   dut_puc2442_proj_backend_fill_child_field(AuteurData,LivreData,id_auteur,auteur,livres,NULL,Livre::getAuteurDataPtrs,false);

    return true;
}

bool Livre::consulter(vector<LivreData> &livres,const vector<unsigned int> &ids,const string &condition,const string &concat){
    vector<string> vValeurs;

    if(!Root::recupererBD().consulter(nomTable,ids,vChamps_full,vValeurs,condition,concat)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps_full.size()){
        LivreData data(strtoll(vValeurs[i].c_str(),NULL,10),vValeurs[i+1],vValeurs[i+2],strtoll(vValeurs[i+3].c_str(),NULL,10),strtoll(vValeurs[i+4].c_str(),NULL,10),strtoll(vValeurs[i+5].c_str(),NULL,10),vValeurs[i+6]);
        livres.push_back(data);
    }

    if (vValeurs.size())    dut_puc2442_proj_backend_fill_child_field(AuteurData,LivreData,id_auteur,auteur,livres,&ids,Livre::getAuteurDataPtrs,false);

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
        flux << "// fichier d\"exportation de livres" <<endl;
        flux << "// "<< Util::vectorToString(vChamps,separateur) << endl <<endl;

        for(unsigned int i=0;i<data.size();i++){
            flux << data[i].to_string(separateur) <<endl;
        }
        return true;
    }
    else {
        cout << "erreur d\"ouverture du fichier \"" << nom_fichier << "\"" << endl;
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

                LivreData ad(strtoll(dataTemp[0].c_str(),NULL,10),dataTemp[1],dataTemp[2],strtoll(dataTemp[3].c_str(),NULL,10),strtoll(dataTemp[4].c_str(),NULL,10),strtoll(dataTemp[5].c_str(),NULL,10),dataTemp[6]);
                data.push_back(ad);
                i++;
            }
        }
        return i;
    }
    else{
        cout << "erreur d\"ouverture du fichier \"" << nom_fichier << "\"" << endl;
        return 0;
    }
}

unsigned int Livre::importToDB(string nom_fichier,const string &separateur){
    vector<LivreData> data;

    unsigned int nbrAjout = importToVector(data,nom_fichier,separateur);

    for(unsigned int i=0;i<data.size();i++){
        ajouter(data[i].titre,data[i].dateDePublication,data[i].nbreExemplairesTotal,data[i].id_auteur);
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

bool Livre::getAuteurDataPtrs(hash_map<unsigned int,AuteurData*> &vals,const vector<unsigned int> &ids,const string &concat){
    vector<AuteurData> auteurs;

    bool res = Auteur::consulter(auteurs,ids);

    if (!res)    return false;

    for (unsigned int i = 0 ; i < auteurs.size() ; i++){
        const unsigned int &id = ids[i];
        AuteurData *aut = new AuteurData(auteurs[i]);
        aut->unsafe_setRefCount(0);     //Inorder to not consider it's reference in the hashmap
        vals[id] = aut;
    }

    return true;
}

//----------LivreData-----------------

LivreData::LivreData(unsigned int id,
    string titre,
    string dateDePublication,
    unsigned int nbreExemplairesTotal,
    unsigned int nbreExemplairesEmprunter,
          unsigned int id_auteur,
          string image){

    this->id = id;
    this->titre = titre;
    this->dateDePublication = dateDePublication;
    this->nbreExemplairesTotal = nbreExemplairesTotal;
    this->nbreExemplairesEmprunter = nbreExemplairesEmprunter;
    this->id_auteur = id_auteur;
    this->image = image;
}

LivreData::LivreData(const LivreData &ld){
    *this = ld;
}


LivreData::~LivreData(){
    if (this->auteur)   auteur->unref();
}

void LivreData::operator=(const LivreData &ld){
    this->id = ld.id;
    this->titre = ld.titre;
    this->dateDePublication = ld.dateDePublication;
    this->nbreExemplairesEmprunter = ld.nbreExemplairesEmprunter;
    this->nbreExemplairesTotal = ld.nbreExemplairesTotal;
    this->id_auteur = ld.id_auteur;
    this->auteur = ld.auteur;

    if (this->auteur)   this->auteur->ref();
}

void LivreData::affiche_livreData(vector<LivreData> &v){
    for(unsigned int i = 0;i<v.size();i++){
        cout << v[i].titre << " - " << v[i].dateDePublication << " - " << v[i].nbreExemplairesTotal << " - "<< v[i].nbreExemplairesEmprunter << " - "<< v[i].id_auteur <<  endl;
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
