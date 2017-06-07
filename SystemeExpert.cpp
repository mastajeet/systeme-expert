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

	/**
	 *  \brief Constructeur par défaut
	 *
	 *  \post Une instance de la classe SystemeExpert est initialisée
	 */
	SystemeExpert::SystemeExpert()
	:baseRegles(ListeCirculaire<Regle>()), baseFaits(std::list<TypeFait>())
	{
	}

	/**
	 *  \brief Destructeur
	 *  \post L'instance de SystemeExpoert est détruite.
	 */
	SystemeExpert::~SystemeExpert(){}

	/**
	 * \brief Surcharge de l'opérateur =
	 *
	 * \post Le systeme expert passé en paramètre est copiée
	 * \param[in] p_systeme le systeme expert a copier
	 */
	SystemeExpert& SystemeExpert::operator =(const SystemeExpert & p_systeme){

		this->baseFaits.clear();
		for(auto i=1; i<this->baseRegles.taille();i++){
			this->baseRegles.enleverPos(i);
		}

		this->baseFaits = std::list<TypeFait>(p_systeme.baseFaits);
		for(auto i=1; i<p_systeme.baseRegles.taille()+1;i++){
			Regle regle = p_systeme.baseRegles.element(i);
			this->baseRegles.ajouter(regle,i);
		}


		return *this;
	}

	/**
	 * \brief Constructeur copieur
	 *
	 * \post Le systeme expert passé en paramètre est copiée
	 * \param[in] p_systeme le systeme expert a copier
	 */
	SystemeExpert::SystemeExpert(const SystemeExpert & p_systeme)
	:baseRegles(ListeCirculaire<Regle>()), baseFaits(std::list<TypeFait>())
	{

		this->baseFaits = std::list<TypeFait>(p_systeme.baseFaits);
		for(auto i=1; i<p_systeme.baseRegles.taille()+1;i++){
			Regle regle = p_systeme.baseRegles.element(i);
			this->baseRegles.ajouter(regle,i);
		}

	}

	/**
	 * \brief Ajoute une regle a la base de regle du systeme expert
	 * \pre la regle doit avoir au moins une premisse et une conclusion
	 * \post Le systeme expert passé a une nouvelle regle
	 * \param[in] p_regle la regle a ajouter
	 */
	void SystemeExpert::ajouterRegleSE(const Regle &p_regle){
		size_t baseRegleTaille = baseRegles.taille();
		baseRegles.ajouter(p_regle, baseRegles.taille()+1);
		ASSERTION(++baseRegleTaille == baseRegles.taille());
	}

	/**
	 * \brief Ajoute un fait a la base de faits du systeme expert
	 * \post Le systeme expert a un nouveau fait s'il n'existe pas deja
	 * \param[in] p_fait la regle a ajouter
	 */
	void SystemeExpert::ajouterFaitSE(const TypeFait &p_fait){

		bool faitTrouve = false;
		for(auto fait : baseFaits){
			if(p_fait == fait){
				faitTrouve = true;
			}
		}
		if(!faitTrouve){
			size_t tailleBaseFait = baseFaits.size();
			baseFaits.push_back(p_fait);
			ASSERTION(++tailleBaseFait == baseFaits.size());
		}
	}

	/**
	 * \brief Ajoute le contenu d'un fichier texte au systeme expert
	 * \post Le systeme expert est charge avec le contenu d'un fichier texte
	 * \param[in] entreeFichier le fichier en stream a inserer dans le systeme expert
	 */
	void SystemeExpert::chargerSE(std::ifstream & entreeFichier){
		const std::string marqueurDebutPremisesRegle = "!%";
		const std::string marqueurDebutConclusionRegle = "!>";
		const std::string marqueurDebutFait = "!!";

		modeLecture modeLecture = PremiseRegle;
		bool regleACreer = false;
		Regle regle;
		std::string currentLine;
		while(std::getline(entreeFichier,currentLine)){

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

	/**
	 * \brief Sature la base de fait du systeme expert afin de tirer des conclusions
	 * \post Le systeme expert a tous les fait qu'il lui est possible de deduire dans sa base de faits
	 * \param[in] er La liste circulaire comprenant les regles utilisees pour la deduction
	 */
	void SystemeExpert::chainageAvant(ListeCirculaire<Regle> & er){
		unsigned int nombrePremissesTrouvees;
		int tailleInitiale = -1;
		int tailleFinale = 0;
		std::list<Regle*> reglesDejaAppliquees;
		while(tailleInitiale!=tailleFinale){
			tailleInitiale = reglesDejaAppliquees.size();
			for(int i =1 ; i<= baseRegles.taille(); i++){

				Regle re = baseRegles.element(i);
				Regle *rePointeur = &baseRegles.element(i);
				bool regleNonTrouvee = (std::find(reglesDejaAppliquees.begin(),reglesDejaAppliquees.end(),rePointeur)==reglesDejaAppliquees.end());

				if(regleNonTrouvee){
					nombrePremissesTrouvees = 0;
					for(auto fait : baseFaits){
						for(auto premise : re.GetPremisses()){
							if(fait==premise){
								 nombrePremissesTrouvees++;
							}
						}
					}
					if(nombrePremissesTrouvees == baseRegles.element(i).GetPremisses().size()){
						er.ajouter(re,er.taille()+1);
						reglesDejaAppliquees.push_back(rePointeur);
						for (auto conclusion : re.GetConclusions()){
							ajouterFaitSE(conclusion);
						}
					}
				}
			}
			tailleFinale = reglesDejaAppliquees.size();
		}
	}

	/**
	 * \brief Exporte le contenu du systeme expert vers un fichier texte
	 * \post Le systeme expert est exporte vers un fichier texte
	 * \param[in] sortieFichier le fichier en stream a inserer dans le systeme expert
	 */
	void SystemeExpert::sauvegarderSE(std::ofstream & sortieFichier) const {

			const std::string marqueurDebutPremisesRegle = "!%";
			const std::string marqueurDebutConclusionRegle = "!>";
			const std::string marqueurDebutFait = "!!";

			bool premiereRegle = true;
			for(auto i = 1; i<=baseRegles.taille(); i++){
				Regle re = baseRegles.element(i);

				if(premiereRegle){
					premiereRegle = false;
				}else{
					sortieFichier << marqueurDebutPremisesRegle << std::endl;
				}

				for(auto premisse : re.GetPremisses()){
					sortieFichier << premisse << std::endl;
				}

				sortieFichier << marqueurDebutConclusionRegle << std::endl;

				for(auto conclusion: re.GetConclusions()){
						sortieFichier << conclusion << std::endl;
				}


			}

			sortieFichier << marqueurDebutFait << std::endl;

			for(auto fait: baseFaits){
					sortieFichier << fait << std::endl;
			}


	}

}

