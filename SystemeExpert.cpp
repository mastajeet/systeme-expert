/**
 * \file SystemeExpert.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe SystemeExpert
 * \author ?
 * \version 0.5
 * \date juin 2017
 *
 */


#include <algorithm>
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


	SystemeExpert& SystemeExpert::operator =(const SystemeExpert & systeme){

		this->baseFaits.clear();
		for(auto i=1; i<this->baseRegles.taille();i++){
			this->baseRegles.enleverPos(i);
		}

		this->baseFaits = std::list<TypeFait>(systeme.baseFaits);
		for(auto i=1; i<systeme.baseRegles.taille();i++){
			Regle regle = systeme.baseRegles.element(i);
			this->baseRegles.ajouter(regle,i);
		}


		return *this;
	}


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
		unsigned int nombrePremissesTrouvees;
		for(int i =1 ; i<= baseRegles.taille(); i++){

			Regle re = baseRegles.element(i);
			nombrePremissesTrouvees = 0;
			for(auto premise : re.GetPremisses()){
				for(auto fait : baseFaits){
					if(fait==premise){
						 nombrePremissesTrouvees++;
					}
				}
			}
			if(nombrePremissesTrouvees == baseRegles.element(i).GetPremisses().size()){
				er.ajouter(re,er.taille()+1);
				for (auto conclusion : re.GetConclusions()){
					ajouterFaitSE(conclusion);
				}
			}


		}
	}

	void SystemeExpert::sauvegarderSE(std::ofstream & SortieFichier) const {

			const std::string marqueurDebutPremisesRegle = "!%";
			const std::string marqueurDebutConclusionRegle = "!>";
			const std::string marqueurDebutFait = "!!";

			bool premiereRegle = true;
			for(auto i = 1; i<=baseRegles.taille(); i++){
				Regle re = baseRegles.element(i);

				if(premiereRegle){
					premiereRegle = false;
				}else{
					SortieFichier << marqueurDebutPremisesRegle << std::endl;
				}

				for(auto premisse : re.GetPremisses()){
					SortieFichier << premisse << std::endl;
				}

				SortieFichier << marqueurDebutConclusionRegle << std::endl;

				for(auto conclusion: re.GetConclusions()){
						SortieFichier << conclusion << std::endl;
				}


			}

			SortieFichier << marqueurDebutFait << std::endl;

			for(auto fait: baseFaits){
					SortieFichier << fait << std::endl;
			}


	}

}

