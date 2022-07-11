#include "adherent.h"

BDR_SQLite3 Adherent::bd("dut_puc2442_proj.db");

bool Adherent::ajouter(const string nom,const string addresse){
    vector<string> vChamps = {"nom","addresse"};
    vector<string> vValeurs = {"'"+nom+"'","'"+addresse+"'"};

    return bd.ajouter("adherent",vChamps,vValeurs);
}

bool Adherent::modifierNom(unsigned int id,const string nom){
    return bd.modifier("adherent",{id},{"nom"},{"'"+nom+"'"},"","id");
}

bool Adherent::modifierAddresse(unsigned int id,const string addresse){
    return bd.modifier("adherent",{id},{"addresse"},{"'"+addresse+"'"},"","id");
}

bool Adherent::supprimer(unsigned int id){
    return bd.supprimer("adherent",{id},"id");
}

bool Adherent::consulter(vector<AdherentData> &adherents,const string &condition){
    vector<string> vChamps = {"nom","addresse","nbreLivresEmprunter"};
    vector<string> vValeurs;

    if(!bd.consulter("livre",vChamps,vValeurs,condition)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=3){
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

//----------------AdherentData--------------

AdherentData::AdherentData(string nom,
                           string addresse,
                           unsigned int nbreLivresEmprunter){
    this->nom = nom;
    this->addresse = addresse;
    this->nbreLivresEmprunter = nbreLivresEmprunter;
}
