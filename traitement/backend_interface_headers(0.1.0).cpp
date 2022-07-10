#include <string>
#include <vector>

using namespace std;
//Uses 0.0.0 version of db
//Version 0.1.0 of header def


/*

0.1.0
Des definitions de fonctions on ete ajouter dans TableBDR
Les definitions qui prenez les (const ****Data&) en arguments prenne maintenant que les unsigned int id_******

0.0.0
initial

*/

namespace dut_puc2442_proj_backend{

	//La valeur de retour **bool** indique si tout s'est bien passée ou pas	 


	//Cette classe peut être utiliser pour gerer des tables SQL de facon generique	
	class TableBDR{
		public:
			static bool ajouter(const string nomTable,const vector<string> &nomChamps,const vector<string> &valeurs);	
			/* 
				A noter que  (valeurs.size() / nomChamps.size()) doit être le nombre de tuples a ajouter
			*/
			
			
			static bool modifier(const string nomTable,const vector<unsigned int> &ids,const vector<string> &nomChamps,const vector<string> &nouvelValeurs,const string nomChampID="id");	
			/*
				A noter que nouvelValeurs.size() == ids.size()*nomChamps.size()
			*/
			
			static bool modifier(const string nomTable,const vector<string> &nomChamps,const vector<string> &nouvelValeurs,const string cond="");
			/*
				A noter que nouvelValeurs.size() == nomChamps.size()
				
				"UPDATE nomTable SET .... WHERE " + cond  , si (cond != "")
				"UPDATE nomTable SET ...."  , si (cond == "")
			*/
			
			
			static bool supprimer(const string nomTable,const vector<unsigned int> &ids,const string nomChampID="id");		//Supprime les tuples avec les ids donner
			
			static bool supprimer(const string nomTable,const string cond="");		//Supprime les tuples en se basant sur des conditions
			/*
				"DELETE FROM nomTable WHERE " + cond , si (cond != "")
				"DELETE FROM nomTable" , si (cond == "")
			*/
			

			static bool consulter(const string nomTable,vector<string> &valeurs,const string concat="");		//Consulte tout les champs
			
			static bool consulter(const string nomTable,const vector<string> &nomChamps,vector<string> &valeurs,const string concat="");		//Consulte uniquement les champs specifier dans le vecteur nomChamps
			/* Le resultat sera charger dans le vecteur *valeurs* , concat est le code SQL a ajouter devant le "SELECT **** FROM nomTable " */
	};
	
	
	//AuteurData{nom,prenom}
	//LivreData{titre,dateDePub,AuteurData}
	//AdherentData{nom,addresse}
	//EmprunteData{LivreData,AdherentData,date}
	//RetourneData{LivreData,AdherentData,date}
	
	class Auteur{
		public:
			static bool ajouter(const string nom,const string prenom);
			static bool modifierNom(unsigned int id,const string nom);
			static bool modifierPrenom(unsigned int id,const string prenom);
			static bool supprimer(unsigned int id);
			static bool consulter(vector<AuteurData> &auteurs);
	};

	class Livre{
		public:
			static bool ajouter(const string titre,const string dateDePublication,unsigned int id_auteur);
			static bool modifierTitre(unsigned int id,const string titre);
			static bool modifierDateDePublication(unsigned int id,const string dateDePublication);
			static bool supprimer(unsigned int id);
			static bool consulter(vector<LivreData> &livres);
			
			static bool ajouterNbreDeCopies(unsigned int nbreAAjouter);
			static bool consulterLivresEmprunterTrieParNom(vector<LivreData> &livres);
			static bool consulterLivresEmprunterTrieParDate(vector<LivreData> &livres);
	};
	
	class Adherent{
		public:
			static bool ajouter(const string nom,const string addresse);
			static bool modifierNom(unsigned int id,const string nom);
			static bool modifierAddresse(unsigned int id,const string addresse);
			static bool supprimer(unsigned int id);
			static bool consulter(vector<AdherentData> &adherents);
			
			static bool emprunterLivre(unsigned int id_livre);
			static bool rendreLivre(unsigned int id_livre);
			
			static bool consulterEmprunteurTrieParNom(vector<LivreData> &livres);
			static bool consulterEmprunteurTrieParDate(vector<LivreData> &livres);
	};
	
	class Emprunte{
		public:
			static bool consulterEmprunts(vector<EmprunteData> &emprunts,const string dateG,const string dateD);	//Les emprunts entre la dateGauche et la dateDroite
	};
	
	class Retourne{
		public:
			static bool consulterRetours(vector<RetourneData> &retours,const string dateG,const string dateD);		//Les retours entre la dateGauche et la dateDroite
	};
	
	
};
