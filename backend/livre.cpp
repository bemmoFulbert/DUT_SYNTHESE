#include "livre.h"

#include <string>
#include <vector>

#include "BDR_SQLite3.h"

BDR_SQLite3 Livre::bd("dut_puc2442_proj.db");

bool Livre::ajouter(const string titre,const string dateDePublication,unsigned int id_auteur){
    vector<string> vChamps = {"titre","dateDePub","nbreExemplairesTotal","nbreExemplairesEmprunter","id_auteur"};
    vector<string> vValeurs = {"'"+titre+"'","'"+dateDePublication+"'","'"+to_string(100)+"'","'"+to_string(0)+"'","'"+to_string(id_auteur)+"'"};

    return bd.ajouter("livre",vChamps,vValeurs);
}

bool Livre::modifierTitre(unsigned int id,const string titre){
    return bd.modifier("livre",{id},{"titre"},{"'"+titre+"'"},"","id");
}

bool Livre::modifierDateDePublication(unsigned int id,const string dateDePublication){
    return bd.modifier("livre",{id},{"dateDePub"},{"'"+dateDePublication+"'"},"","id");
}

bool Livre::supprimer(unsigned int id){
    return bd.supprimer("livre",{id},"id");
}

bool Livre::consulter(vector<LivreData> &livres,const string &condition){
    vector<string> vChamps = {"titre","dateDePub","nbreExemplairesTotal","nbreExemplairesEmprunter","id_auteur"};
    vector<string> vValeurs;

    if(!bd.consulter("livre",vChamps,vValeurs,condition)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=5){
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
