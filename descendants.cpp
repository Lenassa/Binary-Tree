/**
 * @file descendants.cpp
 * @date 21/03/2017 Création
 * @brief Définition des méthodes de la classe Descendants
**/

#include "descendants.hpp" // pour le type Descendants
#include <iostream>// EN AJOUTER SI BESOIN

//--------------------------------------------------------------------
Descendants::Noeud* Descendants::recuperer(Individu ind) {
		std::set<Noeud*> parcoursVec,parcoursVecCopie;
    Noeud* parcours = &racine;
    parcoursVec.emplace(parcours);
    while (parcoursVec.size() > 0) {
        parcoursVecCopie = parcoursVec;
        parcoursVec.clear();
        for (Noeud* nd:parcoursVecCopie) {
            if (nd->ind == ind) return nd;
            parcours = nd->fils;
            while (parcours != NULL) {
                if (parcoursVec.count(parcours) == 0)
                    parcoursVec.emplace(parcours);
                parcours = parcours->frere;
            }
        }
    }
    return nullptr;
}

//--------------------------------------------------------------------
void Descendants::detruire(Noeud* parcours) {
	if (parcours != NULL) {
		detruire(parcours->fils);
		detruire(parcours->frere);
		delete parcours->fils;
		delete parcours->frere;
	}
}


//--------------------------------------------------------------------
Descendants::Descendants(const Individu & ind)
{
    racine.ind = ind;
    racine.fils = NULL;
    racine.frere = NULL;
}

//--------------------------------------------------------------------
Descendants::Descendants(const Individu & ind, const Ancetres & anc):Descendants(ind)
{   
    std::set<Individu> liste = anc.individus();
    std::vector<Individu> degre, degreCopie;
    degre.push_back(ind);
    while (degre.size() > 0) {
        degreCopie = degre;
        degre.clear();
        for (Individu indTest:degreCopie) {
            for (Individu indEnf:liste) {
                if((anc.hasMere(indEnf) && anc.getMere(indEnf) == indTest) || (anc.hasPere(indEnf) && anc.getPere(indEnf) == indTest)) {
                	degre.push_back(indEnf);
                	if (estPresent(indTest) && !estPresent(indEnf))
                      ajouter(indTest,indEnf);
                }
        		}
    		}
    }
}

//--------------------------------------------------------------------
Descendants::~Descendants()
{
	if (racine.frere != NULL || racine.fils != NULL) {
		detruire(racine.frere);
		detruire(racine.fils);
		delete racine.fils;
		delete racine.frere;
	}
}

//--------------------------------------------------------------------
void Descendants::afficher(std::ostream & os) const
{
    std::set<const Noeud*> parcoursVec,parcoursVecCopie;
    const Noeud* parcours = &racine;
    parcoursVec.emplace(parcours);
    while (parcoursVec.size() > 0) {
        parcoursVecCopie = parcoursVec;
        parcoursVec.clear();
        for (const Noeud* nd:parcoursVecCopie) {
            os << nd->ind << std::endl;
            parcours = nd->fils;
            while (parcours != NULL) {
                if (parcoursVec.count(parcours) == 0)
                    parcoursVec.emplace(parcours);
                parcours = parcours->frere;
            }
        }
    }
    
    std::cout<<std::endl;

		parcours = &racine;
    parcoursVec.emplace(parcours);
    while (parcoursVec.size() > 0) {
        parcoursVecCopie = parcoursVec;
        parcoursVec.clear();
        for (const Noeud* nd:parcoursVecCopie) {
            os << nd->ind << std::endl;
            parcours = nd->fils;
            if (parcours != NULL)
                os << "-----> fils/filles :" << std::endl << "-----> ";
            else
                os << "      pas d'enfants" << std::endl;
            while (parcours != NULL) {
                os << parcours->ind << " | " << std::endl;
                if (parcoursVec.count(parcours) == 0)
                    parcoursVec.emplace(parcours);
                parcours = parcours->frere;
            }
        }
    }
}

//--------------------------------------------------------------------
bool Descendants::estPresent(const Individu & ind) const
{
    if (racine.ind == ind)
    	return true;
   	else
    	return estPresentBis(racine.fils,ind) || estPresentBis(racine.frere,ind);
}

bool Descendants::estPresentBis(const Noeud* indPtr, const Individu & ind ) const {
		if (indPtr != NULL)
			if (indPtr->ind == ind)
				return true;
			else
				return estPresentBis(indPtr->fils,ind) || estPresentBis(indPtr->frere,ind);
		else
			return false;
}

//--------------------------------------------------------------------
void Descendants::ajouter(const Individu & par, const Individu & enf)
{
    Noeud* enfPoint = new Noeud{enf,NULL,NULL};
    Noeud* ndPar, *parcours, *pred;
    ndPar = recuperer(par);
    if (ndPar->fils == nullptr) {
        ndPar->fils = enfPoint;
    } else {
    		parcours = ndPar->fils;
    		pred = parcours;
    		while (parcours != NULL && parcours->ind.date > enf.date)
    				pred = parcours;
    				parcours = parcours->frere;
    		if (pred == parcours) {
	  	    	enfPoint->frere = pred->frere;
  		    	pred->frere = enfPoint;
  		  } else {
  		  		ndPar->fils = enfPoint;
  		  		enfPoint->frere = pred;
  		  }
    }
    std::cout<<std::endl;
}

//--------------------------------------------------------------------
std::set<Individu> Descendants::auDegre(unsigned int k) const
{
    unsigned int compt = 0;
    std::set<Individu> res;
    std::set<const Noeud*> parcoursVec, parcoursVecCopie;
    const Noeud* parcours = &racine;
    parcoursVec.emplace(parcours);
    while (parcoursVec.size() > 0 && compt < k+1) {
        parcoursVecCopie = parcoursVec;
        parcoursVec.clear();
        for (const Noeud* nd:parcoursVecCopie) {
        		if (compt == k && res.count(nd->ind) == 0)
                    res.emplace(nd->ind);
            parcours = nd->fils;
            while (parcours != NULL) {
                if (parcoursVec.count(parcours) == 0)
                    parcoursVec.emplace(parcours);
                parcours = parcours->frere;
            }
        }
        compt++;
    }
    return res;
}

//--------------------------------------------------------------------
std::set<Individu> Descendants::descendantsCommuns(const Descendants & des) const
{
		std::set<Individu> res;
		std::set<const Noeud*> parcoursVec,parcoursVecCopie;
    const Noeud* parcours = &des.racine;
    parcoursVec.emplace(parcours);
    while (parcoursVec.size() > 0) {
        parcoursVecCopie = parcoursVec;
        parcoursVec.clear();
        for (const Noeud* nd:parcoursVecCopie) {
            if (estPresent(nd->ind) && res.count(nd->ind)==0) res.emplace(nd->ind);
            parcours = nd->fils;
            while (parcours != NULL) {
                if (parcoursVec.count(parcours) == 0)
                    parcoursVec.emplace(parcours);
                parcours = parcours->frere;
            }
        }
    }
    return res;
}

//--------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const Descendants & anc)
{
    anc.afficher(os);
    return os;
}
