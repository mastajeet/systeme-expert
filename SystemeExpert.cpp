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
			baseRegles.ajouter(tr, baseRegles.taille()+1);
	}

	void SystemeExpert::ajouterFaitSE(const TypeFait &tf){
			baseFaits.push_back(tf);
	}

	void SystemeExpert::chargerSE(std::ifstream & EntreeFichier){
		const std::string marqueurDebutPremisesRegle = "!%";
		const std::string marqueurDebutConclusionRegle = "!>";
		const std::string marqueurDebutFait = "!!";

		modeLecture modeLecture = PremiseRegle;
		bool regleACreer = false;
		Regle regle;
		std::string currentLine;
		while(std::getline(EntreeFichier,currentLine)){

			if(currentLine==marqueurDebutPremisesRegle){
				if(regleACreer){
									ajouterRegleSE(regle);
								}
				modeLecture = PremiseRegle;

				regle = Regle();
			}else if(currentLine==marqueurDebutConclusionRegle){
				modeLecture = ConclusionRegle;
			}else if(currentLine==marqueurDebutFait){
				if(regleACreer){
					ajouterRegleSE(regle);
				}
				modeLecture = Fait;
			}else{
				regleACreer = true;
				switch (modeLecture) {

				case PremiseRegle:
						regle.GetPremisses().push_back(currentLine);
					break;

				case ConclusionRegle:
						regle.GetConclusions().push_back(currentLine);
					break;

				case Fait:
						ajouterFaitSE(currentLine);
					break;

				default:
					break;
				}
			}

		}






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

