/**
 * @file individu.hpp
 * @date 21/03/2017 Création
 * @brief Définition de la classe Individu
**/

#ifndef _INDIVIDU_HPP_
#define _INDIVIDU_HPP_

#include <string> // pour le type std::string et ses opérations

/**
 * @brief La classe Individu représente les informations liées à un individu
 * 
 * les attributs sont directement accessibles (~enregistrement) par simplicité
**/ 
struct Individu
{
    // Attributs
    /// Le sexe de l'individu, 'f' ou 'm'
    char sexe;
    /// Le nom de l'individu, suite de lettres sans espace
    std::string nom;
    /// La date de naissance de l'individu au format AAAA-MM-JJ
    std::string date;

    /**
     * @brief Méthode pour affichage et hachage
     * @return Une chaîne décrivant l'individu au format "S   NOM   DATE"
     * 
     * @b Complexité Θ(1)
     **/
    std::string enChaine() const;

    /**
     * @brief Comparateur d'individus pour l'égalité
     * @param ind L'individu auquel se comparer
     * @return Vrai ssi l'instance et ind sont identiques (sexe, nom et date)
     * 
     * @b Complexité Θ(1)
     **/
    bool operator==(const Individu & ind) const;

		/**
     * @brief Assignation d'individu
     * @param ind L'individu à recopier
     * 
     * @b Complexité Θ(1)
     **/
    void operator=(const Individu & ind);


    /**
     * @brief Comparateur d'individus pour l'inégalité
     * @param ind L'individu auquel se comparer
     * @return Vrai ssi l'instance a une date de naissance antérieure à ind
     * 
     * @b Complexité Θ(1)
     **/
    bool operator<(const Individu & ind) const;
};

/// surcharge de l'opérateur d'affichage << pour les Individu
std::ostream & operator<<(std::ostream & os, const Individu & anc);

//--------------------------------------------------------------------
namespace std
{
    /**
     * Spécialisation de std::hash pour pouvoir utiliser des Individus dans les containers utilisant une fonction de hachage
    **/ 
    template<> struct hash<Individu>
    {
        /// Le type opérande
        typedef Individu argument_type;
        /// Le type résultat
        typedef std::size_t result_type;
        /// Le foncteur qui calcule le hachage
        result_type operator()(argument_type const & ind) const;
    };
}
#endif // _INDIVIDU_HPP_
