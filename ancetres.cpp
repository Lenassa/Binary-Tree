/**
 * @file ancetres.cpp
 * @date 21/03/2017 Création
 * @brief Définition des méthodes de la classe Ancetre
**/
#include "ancetres.hpp" // pour le type Ancetres
#include <fstream> // pour le type std::ifstream
#include <sstream> // pour le type std::stringstream
#include <cassert> // pour les assertions

//--------------------------------------------------------------------
Ancetres::Ancetres()
: noeuds(0) // vecteur vide
{}

//--------------------------------------------------------------------
Ancetres::Ancetres(std::string fic)
: noeuds(0) // vecteur vide
{
    // ouverture du fichier ...
    std::ifstream f(fic);
    // ... supposé fonctionner
    assert(f.is_open());

    // tampon de lecture
    std::string ligne;

    // première partie du fichier : créer les individus
    std::getline(f,ligne);
    while ( f.good()  and  ( ligne.at(0) == 'f'  or  ligne.at(0) == 'm' ) )
    {
        std::stringstream ss(ligne);
        Individu ind;
        ss >> ind.sexe >> ind.nom >> ind.date; // déchiffrage des données
        this->ajouter(ind); // ajout au moyen de la méthode éponyme
        std::getline(f,ligne); // prochaine ligne
    }

    // deuxième partie : lier les individus
    while ( f.good() )
    {
        std::stringstream ss(ligne);
        int i, p, m; // numéros de l'individu, son père, sa mère
        ss >> i >> p >> m; // déchiffrage des liens
        Individu ind, per, mer; // individus correspondants
        ind = noeuds.at(i-1).ind;
        // enregistrement du père si connu
        if ( p != 0 )
        {
            per = noeuds.at(p-1).ind;
            this->setPere(ind,per);
        }
        // enregistrement de la mère si connue
        if ( m != 0 )
        {
            mer = noeuds.at(m-1).ind;
            this->setMere(ind,mer);
        }
        std::getline(f,ligne); // prochaine ligne
    }
    f.close();
}

//--------------------------------------------------------------------
void Ancetres::afficher(std::ostream & os) const
{ // affichage formaté des individus, puis de leurs liens de filiation

    // affichage des individus
    for ( auto & nd : noeuds )
    {
        os << nd.ind << std::endl;
    }

    // affichage des liens de filiation
    for ( size_t i = 0 ; i < noeuds.size() ; ++ i )
    {
        os << i+1 << '\t' << noeuds.at(i).pere+1 << '\t' << noeuds.at(i).mere+1 << std::endl;
    }
}

//--------------------------------------------------------------------
bool Ancetres::estPresent(const Individu & ind) const
{
    return indTOnd.count(ind)>0;
}

//--------------------------------------------------------------------
void Ancetres::ajouter(const Individu & ind)
{
    noeuds.push_back(Noeud{ind, -1, -1});
    indTOnd.emplace(ind,(unsigned int)noeuds.size()-1);
}

//--------------------------------------------------------------------
bool Ancetres::hasPere(Individu ind) const
{
    bool hp = false;
    if (noeuds.at(indTOnd.at(ind)).pere != -1)
      hp = true;
    return hp;
}
        
//--------------------------------------------------------------------
Individu Ancetres::getPere(Individu ind) const
{
    Individu p;
    p = noeuds.at(noeuds.at(indTOnd.at(ind)).pere).ind;
    return p;
}
        
//--------------------------------------------------------------------
void Ancetres::setPere(Individu ind, Individu pere)
{
    noeuds.at(indTOnd.at(ind)).pere = indTOnd.at(pere);
}

//--------------------------------------------------------------------
bool Ancetres::hasMere(Individu ind) const
{
    bool hm = false;
    if (noeuds.at(indTOnd.at(ind)).mere != -1)
      hm = true;
    return hm;
}
        
//--------------------------------------------------------------------
Individu Ancetres::getMere(Individu ind) const
{
    Individu m;
    m = noeuds.at(noeuds.at(indTOnd.at(ind)).mere).ind;
    return m;
}
        
//--------------------------------------------------------------------
void Ancetres::setMere(Individu ind, Individu mere)
{
    noeuds.at(indTOnd.at(ind)).mere = indTOnd.at(mere);
}

//--------------------------------------------------------------------
std::set<Individu> Ancetres::racines() const
{
    std::set<Individu> rac;
    std::vector<bool> enfant;
    for (size_t i=0;i<noeuds.size();++i) enfant.push_back(true);
    for (Noeud Nds:noeuds) {
    	if (Nds.pere != -1 && enfant.at(Nds.pere))
    		enfant.at(Nds.pere) = false;
    	if (Nds.mere != -1 && enfant.at(Nds.mere))
    		enfant.at(Nds.mere) = false;
    }
    for (size_t i=0;i<enfant.size();++i)
    	if (enfant.at(i))
    		rac.emplace(noeuds.at(i).ind);
    return rac;
}

//--------------------------------------------------------------------
std::set<Individu> Ancetres::individus() const
{
    std::set<Individu> inds;
    for (Noeud Nds:noeuds)
    	if (inds.count(Nds.ind) == 0)
    		inds.emplace(Nds.ind);
    return inds;
}

//--------------------------------------------------------------------
Ancetres Ancetres::ancetresCommuns(Individu ind1, Individu ind2) const
{
    Ancetres com;
    size_t indice = 0;
    //création d'un tableau contenant les indices des ancètres
    std::vector<int> Anc1;
    //Ajout de l'individu pour lancer la boucle
    Anc1.push_back(indTOnd.at(ind1));
    //Tant que tous les ancètres n'ont pas été parcouru
    while (indice <= Anc1.size()-1) {
    	//Ajout du père si existant
    	if (noeuds.at(Anc1.at(indice)).pere != -1)
    		Anc1.push_back(noeuds.at(Anc1.at(indice)).pere);
    	//Ajout de la mère si existante
    	if (noeuds.at(Anc1.at(indice)).mere != -1)
    		Anc1.push_back(noeuds.at(Anc1.at(indice)).mere);
    	indice++;
    }
    //Réinitialisation de l'indice pour la seconde boucle
    indice = 0;
    std::vector<int> Anc2;
    //Ajout de l'individu pour lancer la boucle
    Anc2.push_back(indTOnd.at(ind2));
    while (indice <= Anc2.size()-1) {
    	if (noeuds.at(Anc2.at(indice)).pere != -1)
    		Anc2.push_back(noeuds.at(Anc2.at(indice)).pere);
    	if (noeuds.at(Anc2.at(indice)).mere != -1)
    		Anc2.push_back(noeuds.at(Anc2.at(indice)).mere);
    	indice++;
    }
    /*Parcours des vecteurs, ajouts de tous les ancètres communs aux deux sans doublons*/
    for (int i = (int)Anc1.size()-1; i >= 0; --i) {
    	for (int j = (int)Anc2.size()-1; j >= 0; --j) {
    		if (Anc2.at(j)==Anc1.at(i)) {
    			if (!com.estPresent(noeuds.at(Anc1.at(i)).ind)) {
    				com.ajouter(noeuds.at(Anc1.at(i)).ind);
    			}
    		}
    	}
    }
    /*Parcours du vecteur noeuds du nouvel arbre d'ancètres
	    com.noeuds.at(i).ind est l'individu du nouvel arbre à la position i
  	  noeuds.at(indTOnd.at(ind)).pere récupère l'indice du père dans l'ancien arbre
  	  noeuds.at(pere).ind) récupère l'individu père dans l'ancien arbre
  	MEME PRINCIPE POUR LA MERE*/
    for (size_t i = 0; i < com.noeuds.size();++i) {
    	if (noeuds.at(indTOnd.at(com.noeuds.at(i).ind)).pere != -1)
    		com.setPere(com.noeuds.at(i).ind, noeuds.at(noeuds.at(indTOnd.at(com.noeuds.at(i).ind)).pere).ind);
    	if (noeuds.at(indTOnd.at(com.noeuds.at(i).ind)).mere != -1)
    		com.setMere(com.noeuds.at(i).ind, noeuds.at(noeuds.at(indTOnd.at(com.noeuds.at(i).ind)).mere).ind);
    }
    return com;
}

//--------------------------------------------------------------------
void Ancetres::fusion(Ancetres anc)
{
    for (Noeud Nds:anc.noeuds)
    	if (!estPresent(Nds.ind))
    		ajouter(Nds.ind);
    for (int i = (int)noeuds.size()-1;i>=0;--i) {
    	if (!hasMere(noeuds.at(i).ind))
    		if (anc.estPresent(noeuds.at(i).ind) && anc.hasMere(noeuds.at(i).ind))
    			setMere(noeuds.at(i).ind, anc.getMere(noeuds.at(i).ind));
    	if (!hasPere(noeuds.at(i).ind))
    		if (anc.estPresent(noeuds.at(i).ind) && anc.hasPere(noeuds.at(i).ind))
    			setPere(noeuds.at(i).ind, anc.getPere(noeuds.at(i).ind));
    }
}

//--------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const Ancetres & anc)
{
    anc.afficher(os);
    return os;
}
