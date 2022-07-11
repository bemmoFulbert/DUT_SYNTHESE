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
