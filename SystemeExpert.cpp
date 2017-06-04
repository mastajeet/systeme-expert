/**
 * \file SystemeExpert.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe SystemeExpert
 * \author ?
 * \version 0.5
 * \date juin 2017
 *
 */

#include "SystemeExpert.h"

namespace tp1
{

	enum modeLecture{
		PremiseRegle, ConclusionRegle, Fait
	};

	SystemeExpert::SystemeExpert()
	:baseRegles(ListeCirculaire<Regle>()), baseFaits(std::list<TypeFait>())
	{


	}
	SystemeExpert::~SystemeExpert(){}

	void SystemeExpert::ajouterRegleSE(const Regle &tr){
			//baseRegles.ajouter(tr, baseRegles.taille());
	}

	void SystemeExpert::ajouterFaitSE(const TypeFait &tf){
			baseFaits.push_back(tf);
	}

	void SystemeExpert::chargerSE(std::ifstream & EntreeFichier){
		const std::string marqueurDebutPremisesRegle = "!>";
		const std::string marqueurDebutConclusionRegle = "!%";
		const std::string marqueurDebutFait = "!!";

		modeLecture modeLecture = PremiseRegle;

		//for(auto line : EntreeFichier){
		//	if(modeLecture)

		//}





	}

	void SystemeExpert::chainageAvant(ListeCirculaire<Regle> & er){

	}

	void SystemeExpert::sauvegarderSE(std::ofstream & SortieFichier) const {


	}

	SystemeExpert& SystemeExpert::operator = (const SystemeExpert & se){
		SystemeExpert retour = SystemeExpert();
		return retour;
	}
//Mettez l'implantation de vos méthodes ici.
}

