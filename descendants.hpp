/**
 * @file descendants.hpp
 * @date 21/03/2017 Création
 * @brief Définition de la classe Descendants
**/

#ifndef _DESCENDANTS_HPP_
#define _DESCENDANTS_HPP_

#include <set> // pour le type std::set
#include <ostream> // pour le type std::ostream
#include "individu.hpp" // pour le type Individu
#include "ancetres.hpp" // pour le type Ancetres

/**
 * @brief La classe Descendants représente un arbre généalogique de descendants
**/
class Descendants
{
    public:
        /**
         * @brief Constructeur d'un arbre pour un individu
         * @param ind L'individu racine
         * @post L'arbre a ind pour racine et aucun autre nœud
         * 
         * @b Complexité -temporelle : O(1)
         *							 -spatiale : O(1)
         **/
        Descendants(const Individu & ind);

        /**
         * @brief Constructeur d'un arbre pour un individu à partir d'une forêt d'ancêtres
         * @param ind L'individu racine
         * @param anc La forêt d'ancêtres
         * @pre ind est présent dans anc
         * @post L'arbre a ind pour racine et contient tous les descendants de ind présents dans anc
         * 
         * @b Complexité -temporelle : O(nAnc*nbIndMaxDegre)
         * 														 avec nAnc le nombre d'individus dans anc
         *      											 nbIndMaxDegre le plus grand nombre d'ind par degré dans anc
         								 -spatiale : O(nAnc + 2*nbIndMaxDegre + O(ajouter))
         **/
        Descendants(const Individu & ind, const Ancetres & anc);
        
        /**
         * @brief Destructeur
         * 
         * @b Complexité -temporelle : O(detruire(Noeud*)) = O(1)
         *							 -spatiale : O(1)
         **/
        ~Descendants();
        
        /**
         * @brief Affiche dans un flux de sortie (fichier ou écran)
         * @param os Le flux de sortie
         * 
         * @b Complexité -temporelle : O(p*nMaxFrere*nIndMaxDegre)
         *														 avec p la profondeur de Decendant
         *      											 nMaxFrere le plus grand nombre d'enfants d'une fratrie
         *      											 nIndMaxDegre le plus grand nombre d'ind par degré de Descendants
         *							 -spatiale : O(2*nIndMaxDegre + 1)
         **/
        void afficher(std::ostream & os) const;

        /**
         * @brief Indique si un individu est présent dans l'arbre
         * @param ind L'individu à rechercher
         * @return Vrai ssi l'individu est dans l'arbre
         * 
         * @b Complexité -temporelle : O(1)
         *							 -spatiale : O(1)
         **/
        bool estPresent(const Individu & ind) const;

        /**
         * @brief Ajoute un nouvel enfant à un individu de l'arbre
         * @param par L'individu parent
         * @param enf Le nouvel individu enfant
         * @pre L'individu par est déjà dans l'arbre, pas l'individu enf
         * 
         * @b Complexité -temporelle : O(recuperer(Individu ind)) = O((p-pInd)*nMaxFrere*nIndMaxDegre)
         *														 avec p la profondeur de Decendant
         *														 pInd la profondeur de l'ind dans Descendants
         *      											 nMaxFrere le plus grand nombre d'enfants d'une fratrie
         *      											 nIndMaxDegre le plus grand nombre d'ind par degré de Descendants
         *							 -spatiale : O( O(recuperer) + 2 )
         **/
        void ajouter(const Individu & par, const Individu & enf);
        
        /**
         * @brief Calcule l'ensemble des individus descendants de l'individu racine au degré k (1 = les enfants, 2 = les petits enfants, ...)
         * @return Les descendants au k-ième degré
         * 
         * @b Complexité -temporelle : O((p-k)*nMaxFrere*nIndMaxDegre)
         *														 avec p la profondeur de Decendant
         *														 k le degré (donc la profondeur)
         *      											 nMaxFrere le plus grand nombre d'enfants d'une fratrie
         *      											 nIndMaxDegre le plus grand nombre d'ind par degré de Descendants
         *							 -spatiale : O(nRes + 2*nIndMaxDegre + 1)
         *													 avec nRes le nombre d'individus dans le set res
         **/
        std::set<Individu> auDegre(unsigned int k) const;
        
        /**
         * @brief Calcule l'ensemble des descendants communs à deux arbres
         * @return L'ensemble des descendants communs
         * 
         * @b Complexité -temporelle : O(p*nMaxFrere*nIndMaxDegre)
         * 														 avec p la profondeur de Decendant
         *  											     nMaxFrere le plus grand nombre d'enfants d'une fratrie
         *   												   nIndMaxDegre le plus grand nombre d'ind par degré de Descendants
         *							 -spatiale : O(nRes + 2*nIndMaxDegre + 1)
         *													 avec nRes le nombre d'individus dans le set res
         **/
        std::set<Individu> descendantsCommuns(const Descendants & des) const;

    private:
        // Type Nœud
        struct Noeud
        {
            Individu ind; // l'individu représenté
            Noeud *fils, *frere; // enfant aîné, prochain dans la fratrie
        };
        // Attributs
        Noeud racine; // le nœud de l'individu racine
        // Méthodes
        
        /**
         * @brief Récupère le Noeud contenant l'individu recherché
         * @param ind L'individu à récupérer
         * @return Le pointeur sur Noeud si existant, nullptr sinon
         * 
         * @b Complexité -temporelle : O((p-pInd*nMaxFrere*nIndMaxDegre)
         * 														 avec p la profondeur de Decendant
         *												 		 pInd la profondeur de l'ind dans Descendants
         *      											 nMaxFrere le plus grand nombre d'enfants d'une fratrie
         *      											 nIndMaxDegre le plus grand nombre d'ind par degré de Descendants
         *							 -spatiale : O(2*nIndMaxDegre)
         **/
        Noeud* recuperer(Individu ind);
        
        /**
         * @brief Fonction aidant le Destructeur
         * @param parcours le pointeur sur Noeud à supprimer
         * 
         * @b Complexité O(1)
         **/
        void detruire(Noeud* parcours);
        
        /**
         * @brief Fonction de recherche secondaire de estPresent
         * @param ind L'individu à rechercher, indPtr le pointeur sur le Noeud à étudier
         * @return Vrai ssi l'individu est dan le Noeud, sinon retourne (résultat du frère || résultat du fils), ou retourne faux si indPtr pointe sur NULL
         * 
         * @b Complexité -temporelle : O(1)
         *							 -spatiale : O(1)
         **/
        bool estPresentBis(const Noeud* indPtr, const Individu & ind ) const;
};

/// surcharge de l'opérateur d'affichage << pour les Descendants
std::ostream & operator<<(std::ostream & os, const Descendants & anc);

#endif // _DESCENDANTS_HPP_
