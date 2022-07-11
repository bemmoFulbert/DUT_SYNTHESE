#include "auteur.h"

BDR_SQLite3 Auteur::bd("dut_puc2442_proj.db");

bool Auteur::ajouter(const string &nom,const string &prenom){
    vector<string> vChamps = {"nom","prenom"};
    vector<string> vValeurs = {"'"+nom+"'","'"+prenom+"'"};

    return bd.ajouter("auteur",vChamps,vValeurs);
}

bool Auteur::modifierNom(unsigned int id,const string &nom){
    return bd.modifier("auteur",{id},{"nom"},{"'"+nom+"'"},"","id");
}

bool Auteur::modifierPrenom(unsigned int id,const string &prenom){
    return bd.modifier("auteur",{id},{"prenom"},{"'"+prenom+"'"},"","id");
}

bool Auteur::supprimer(unsigned int id){
    return bd.supprimer("auteur",{id},"id");
}

bool Auteur::consulter(vector<AuteurData> &auteurs){
    vector<string> vChamps = {"nom","prenom"};
    vector<string> vValeurs;

    if(!bd.consulter("auteur",vChamps,vValeurs)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=2){
        AuteurData data(vValeurs[i],vValeurs[i+1]);
        auteurs.push_back(data);
    }

    return true;
}

//-----------AuteurData----------------

AuteurData::AuteurData(string nom,string prenom){
    this->nom = nom;
    this->prenom = prenom;
}

void AuteurData::affiche_auteurData(vector<AuteurData> v){
    for(unsigned int i = 0;i<v.size();i++){
        cout << v[i].nom << " - " << v[i].prenom << endl;
    }
}
