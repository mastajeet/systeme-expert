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
	//Mettez l'implantation de vos méthodes ici.
	Regle::Regle()
	:conclusions(), premisses()
	{}

	Regle::~Regle(){}

	bool Regle::operator == (const Regle & r) {

		bool premisesEgales = (r.premisses==premisses);
		bool conclusionsEgales = (r.conclusions==conclusions);

		return premisesEgales && conclusionsEgales;

	}

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

