/**
 * @file individu.cpp
 * @date 21/03/2017 Création
 * @brief Définition des méthodes de la classe Individu
**/

#include "individu.hpp" // pour le type Individu

//--------------------------------------------------------------------
std::string Individu::enChaine() const 
{ 
    return std::string() + sexe + "\t" + nom + "\t" + date; 
}

//--------------------------------------------------------------------
bool Individu::operator==(const Individu & ind) const
{
    return (sexe==ind.sexe and nom==ind.nom and date==ind.date); 
}

//--------------------------------------------------------------------
void Individu::operator=(const Individu & ind)
{
    sexe=ind.sexe;
    nom=ind.nom;
    date=ind.date; 
}

//--------------------------------------------------------------------
bool Individu::operator<(const Individu & ind) const
{
    // comparaison lexicographique, par année, puis mois, puis jour, puis sexe, puis nom
    return ( date < ind.date ) 
        or ( date == ind.date and ( sexe < ind.sexe 
                               or ( sexe == ind.sexe and nom < nom ) ) ) ; 
}

//--------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const Individu & anc)
{
    os << anc.enChaine();
    return os;
}

//--------------------------------------------------------------------
namespace std
{
    hash<Individu>::result_type hash<Individu>::operator()(argument_type const& ind) const
    {
        hash<Individu>::result_type const s ( std::hash<char>{}(ind.sexe) );
        hash<Individu>::result_type const n ( std::hash<std::string>{}(ind.nom) );
        hash<Individu>::result_type const d ( std::hash<std::string>{}(ind.date) );
        return s ^ (n ^ (d << 1) << 1);
    }
}
