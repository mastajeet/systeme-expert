/////////////////////////////////////////////////////////////////////////////
//Fichier Regle.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Regle.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Regle
 * \author ?
 * \version 0.5
 * \date mai 2017
 *
 */

#include "Regle.h"

namespace tp1
{
	/**
	 *  \brief Constructeur par défaut
	 *
	 *  \post Une instance de la classe Regle est initialisée
	 */
	Regle::Regle()
	:conclusions(), premisses()
	{}

	/**
	 *  \brief Destructeur
	 *  \post L'instance de ListeCirculaire est détruite.
	 */
	Regle::~Regle(){}

	/**
	 * \brief Compare deux regles ensemble
	 *
	 * \post les regles sont inchangees
	 * \return vrai si les deux regles sont egale, faux sinon
	 */
	bool Regle::operator == (const Regle & r) {

		bool premisesEgales = (r.premisses==premisses);
		bool conclusionsEgales = (r.conclusions==conclusions);

		return premisesEgales && conclusionsEgales;

	}

	/**
	 * \brief Surcharge de l'opérateur =
	 *
	 * \post La regle passée en paramètre est copiée
	 * \param[in] r La regle à copier
	 */
	Regle& Regle::operator = (const Regle & r) {
		Regle regle;


	    if (this != &r) { // self-assignment check expected
	    	this->premisses.clear();
	    	this->conclusions.clear();

			for(TypeFait premisse : r.premisses){
				this->premisses.push_back(premisse);
			}

			for(TypeFait conclusion: r.conclusions){
				this->conclusions.push_back(conclusion);
			}


	    }

	    return *this ;

	}

	/**
	 *  \brief Constructeur de copie.
	 *
	 * \post La Regle passée en paramètre est copiée
	 * \param[in] r La regle à copier
	 */
	Regle::Regle(const Regle& r)
	:conclusions(), premisses()
	{

		for(TypeFait premisse : r.premisses){
			premisses.push_back(premisse);
		}

		for(TypeFait conclusion: r.conclusions){
			conclusions.push_back(conclusion);
		}
	}



}

