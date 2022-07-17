
#include "root.h"
#include "adherent.h"

vector<string> Adherent::vChamps = {"nom","addresse","nbreLivresEmprunter","prenom","email","dateDeNaissance","sexe"};
////////////-------------------------0-------1--------------2-----------------3--------4--------------5==========6==============
vector<string> Adherent::vChamps_full = {"id","nom","addresse","nbreLivresEmprunter","prenom","email","dateDeNaissance","sexe"};
string Adherent::nomTable = "adherent";


bool Adherent::ajouter(const string &nom,const string &addresse,const string &prenom,const string &email,const string &dateDeNaissance,const string &sexe){
    vector<string> vValeurs = {"\""+nom+"\"","\""+addresse+"\"","\""+to_string(0)+"\"","\""+prenom+"\"","\""+email+"\"","\""+dateDeNaissance+"\"","\""+sexe+"\""};

    return Root::recupererBD().ajouter(nomTable,vChamps,vValeurs);
}

bool Adherent::modifierNom(unsigned int id,const string &nom){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[0]},{"\""+nom+"\""},"","id");
}

bool Adherent::modifierNoms(const vector<unsigned int> &ids, const string &nom){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[0]},{"\""+nom+"\""},"","id");
}

bool Adherent::modifierPrenom(unsigned int id,const string prenom){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[3]},{"\""+prenom+"\""},"","id");
}

bool Adherent::modifierPrenoms(const vector<unsigned int> &ids,const string &prenom){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[3]},{"\""+prenom+"\""},"","id");
}

bool Adherent::modifierAddresse(unsigned int id,const string addresse){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[1]},{"\""+addresse+"\""},"","id");
}

bool Adherent::modifierAddresses(const vector<unsigned int> &ids,const string &addresse){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[1]},{"\""+addresse+"\""},"","id");
}

bool Adherent::modifierEmail(unsigned int id,const string email){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[4]},{"\""+email+"\""},"","id");
}

bool Adherent::modifieEmails(const vector<unsigned int> &ids,const string &email){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[4]},{"\""+email+"\""},"","id");
}

bool Adherent::modifierDateDeNaissance(unsigned int id,const string dateDeNaissance){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[5]},{"\""+dateDeNaissance+"\""},"","id");
}

bool Adherent::modifierDateDeNaissances(const vector<unsigned int> &ids,const string &dateDeNaissance){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[5]},{"\""+dateDeNaissance+"\""},"","id");
}

bool Adherent::modifierSexe(unsigned int id,const string sexe){
    return Root::recupererBD().modifier(nomTable,{id},{vChamps[6]},{"\""+sexe+"\""},"","id");
}

bool Adherent::modifierSexes(const vector<unsigned int> &ids,const string &sexe){
    return Root::recupererBD().modifier(nomTable,ids,{vChamps[6]},{"\""+sexe+"\""},"","id");
}

bool Adherent::modifierNoms_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &noms){
    unsigned int idsLen = ids.size();
    unsigned int nomsLen = noms.size();
    bool err = true;

    if(idsLen == nomsLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(!modifierNom(ids[i],noms[i])){
                err = false;
            }
        }
    }else err = false;
    return err;
}

bool Adherent::modifierPrenoms_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &prenoms){
    unsigned int idsLen = ids.size();
    unsigned int prenomsLen = prenoms.size();
    bool err = true;

    if(idsLen == prenomsLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(!modifierPrenom(ids[i],prenoms[i])){
                err = false;
            }
        }
    }else err = false;
    return err;
}

bool Adherent::modifierAddresses_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &addresses){
    unsigned int idsLen = ids.size();
    unsigned int addressesLen = addresses.size();
    bool err = true;

    if(idsLen == addressesLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(!modifierAddresse(ids[i],addresses[i])){
                err=false;
            }
        }
    }else err = false;
    return err;
}

bool Adherent::modifierEmails_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &emails){
    unsigned int idsLen = ids.size();
    unsigned int emailsLen = emails.size();
    bool err = true;

    if(idsLen == emailsLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(!modifierEmail(ids[i],emails[i])){
                err=false;
            }
        }
    }else err = false;
    return err;
}

bool Adherent::modifierDateDeNaissances_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &dateDeNaissances){
    unsigned int idsLen = ids.size();
    unsigned int dateDeNaissancesLen = dateDeNaissances.size();
    bool err = true;

    if(idsLen == dateDeNaissancesLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(!modifierDateDeNaissance(ids[i],dateDeNaissances[i])){
                err=false;
            }
        }
    }else err = false;
    return err;
}

bool Adherent::modifierSexes_WithDiffValues(const vector<unsigned int> &ids,const vector<string> &sexes){
    unsigned int idsLen = ids.size();
    unsigned int sexesLen = sexes.size();
    bool err = true;

    if(idsLen == sexesLen){
        for(unsigned int i=0; i<idsLen ; i++){
            if(!modifierSexe(ids[i],sexes[i])){
                err=false;
            }
        }
    }else err = false;
    return err;
}

bool Adherent::supprimer(unsigned int id){
    return Root::recupererBD().supprimer(nomTable,{id},"id");
}

bool Adherent::supprimer(const vector<unsigned int> &ids){
    return Root::recupererBD().supprimer(nomTable,ids);
}

bool Adherent::consulter(vector<AdherentData> &adherents,const string &concat){
    vector<string> vValeurs;

    if(!Root::recupererBD().consulter(nomTable,vChamps_full,vValeurs,concat)) return false;

    cerr << vValeurs.size() <<endl;
    for(unsigned int i=0;i<vValeurs.size();i+=vChamps_full.size()){
        cerr << i <<endl;
        AdherentData data(Util::str_to_integer(vValeurs[i]),vValeurs[i+1],
                vValeurs[i+2],strtoll(vValeurs[i+3].c_str(),NULL,10),
                vValeurs[i+4],vValeurs[i+5],vValeurs[i+6],vValeurs[i+7]);
        adherents.push_back(data);
        cerr << data.to_string(" , ") << endl;
    }

    return true;
}

bool Adherent::consulter(vector<AdherentData> &adherents,const vector<unsigned int> &ids,const string &condition,const string &concat){
    vector<string> vValeurs;

    if(!Root::recupererBD().consulter(nomTable,ids,vChamps_full,vValeurs,condition,concat)) return false;

    for(unsigned int i=0;i<vValeurs.size();i+=vChamps_full.size()){
        AdherentData data(Util::str_to_integer(vValeurs[i]),vValeurs[i+1],
                vValeurs[i+2],strtoll(vValeurs[i+3].c_str(),NULL,10),
                vValeurs[i+4],vValeurs[i+5],vValeurs[i+6],vValeurs[i+7]);
        adherents.push_back(data);
        cout << data.to_string("--");
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
        flux << "// fichier d\"exportation de adherents" <<endl;
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

                AdherentData ad(Util::str_to_integer(dataTemp[0]),dataTemp[1],dataTemp[2],strtoll(dataTemp[3].c_str(),NULL,10),dataTemp[4],dataTemp[5],dataTemp[6],dataTemp[7]);
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

unsigned int Adherent::importToDB(string nom_fichier,const string &separateur){
    vector<AdherentData> data;

    unsigned int nbrAjout = importToVector(data,nom_fichier,separateur);

    for(unsigned int i=0;i<data.size();i++){
        ajouter(data[i].nom,data[i].addresse,data[i].prenom,data[i].email,data[i].dateDeNaissance,data[i].sexe);
    }
    return nbrAjout;
}

bool Adherent::emprunterLivre(unsigned int id_livre,unsigned int id_adherent){
    vector<string> vChampsEmprunte = {"id_livre","id_adherent","date"};
    vector<string> vValeurs = {to_string(id_livre),to_string(id_adherent),"CURRENT_TIMESTAMP"};

    if(Root::recupererBD().ajouter("Emprunte",vChampsEmprunte,vValeurs)){
        Root::recupererBD().executerCommandeSQL("UPDATE Adherent SET nbreLivresEmprunter = nbreLivresEmprunter+1 WHERE id="+to_string(id_adherent)+";");
        Root::recupererBD().executerCommandeSQL("UPDATE Livre SET nbreExemplairesEmprunter = nbreExemplairesEmprunter-1 WHERE id="+to_string(id_livre)+";");
        return true;
    }
    return false;
}

bool Adherent::rendreLivre(unsigned int id_livre,unsigned int id_adherent){
    vector<string> vValeursVerif;
    Root::recupererBD().consulter("Emprunte",{"date"},vValeursVerif,"WHERE id_livre="+to_string(id_livre)+" AND id_adherent="+to_string(id_adherent)+" AND date NOT IN (SELECT date_Emprunte FROM Retourne)");
    if(vValeursVerif[0].empty() || vValeursVerif[0] == "0") return false;

    string dateEmprunt = vValeursVerif[0];
    vector<string> vChampsRetourne = {"date_Emprunte","date"};
    vector<string> vValeurs = {dateEmprunt,"CURRENT_TIMESTAMP"};

    if(Root::recupererBD().ajouter("Retourne",vChampsRetourne,vValeurs)){
        Root::recupererBD().executerCommandeSQL("UPDATE Adherent SET nbreLivresEmprunter = nbreLivresEmprunter-1 WHERE id="+to_string(id_adherent)+";");
        Root::recupererBD().executerCommandeSQL("UPDATE Livre SET nbreExemplairesEmprunter = nbreExemplairesEmprunter+1 WHERE id="+to_string(id_livre)+";");
        return true;
    }
    return false;
}

//----------------AdherentData--------------

AdherentData::AdherentData(unsigned int id,string nom,
    string addresse,
    unsigned int nbreLivresEmprunter,
    string prenom,string email, string dateDeNaissance, string sexe){

    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->addresse = addresse;
    this->nbreLivresEmprunter = nbreLivresEmprunter;
    this->email = email;
    this->dateDeNaissance = dateDeNaissance;
    this->sexe = sexe;
}

AdherentData::AdherentData(const AdherentData &ad){
    *this = ad;
}


const string AdherentData::to_string(const string &separateur){
    string *res = new string();
    res->append(nom); res->append(separateur);
    res->append(addresse);res->append(separateur);
    res->append(std::to_string(nbreLivresEmprunter));res->append(separateur);
    res->append(prenom); res->append(separateur);
    res->append(email); res->append(separateur);
    res->append(dateDeNaissance); res->append(separateur);
    res->append(sexe); res->append(separateur);
    return *res;
}

void AdherentData::affiche_adherentData(vector<AdherentData> &v){
    for(unsigned int i = 0;i<v.size();i++){
        cout << v[i].to_string("-") << endl;
    }
}

void AdherentData::toQStringLists(const vector<AdherentData> &vAdhData, QStringList &ids, QStringList &addresses, QStringList &nbreLivresEmprunters, QStringList &prenoms, QStringList &emails, QStringList &dateDeNaissances, QStringList &sexes){
    for (unsigned int i=0;i<vAdhData.size();i++){
        ids << QString::number(vAdhData[i].id);
        addresses << QString::fromStdString(vAdhData[i].addresse);
        nbreLivresEmprunters << QString::number(vAdhData[i].nbreLivresEmprunter);
        prenoms << QString::fromStdString(vAdhData[i].prenom);
        emails << QString::fromStdString(vAdhData[i].email);
        dateDeNaissances << QString::fromStdString(vAdhData[i].dateDeNaissance);
        sexes << QString::fromStdString(vAdhData[i].sexe);
    }
}




