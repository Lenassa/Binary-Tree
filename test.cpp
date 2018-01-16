/**
 * @file test.cpp
 * @date 21/03/2017 Création
 * @brief Programme de test de la classe Ancetres
**/

#include <iostream>
#include "individu.hpp"
#include "ancetres.hpp"
#include "descendants.hpp"
using namespace std;

/// Programme principal destiné à tester toutes les fonctionnalités des différentes classes implémentées
int main()
{
    // INDIVIDUS
    Individu    ind1={'m',"Camille","2007-01-15"}, 
                ind2={'m',"Jules","2007-01-15"}, 
                ind3={'f',"Camille","2007-01-15"}, 
                ind4={'m',"Camille","1977-01-15"}, 
                ind5={'m',"Camille","2007-11-15"}, 
                ind6={'m',"Camille","2007-01-25"},
                indTest={'f',"France","1951-03-03"},
                indTest1={'f',"Brigitte","1978-04-21"},
                indTest2={'m',"Jean","2004-02-29"},
                indTest3={'m',"Jacques","1980-06-06"};
                

    // Tests de la méthode Individu::enChaine et <<
    cout << "ind1 : " << ind1 << endl;
    cout << "ind2 : " << ind2 << endl;
    cout << "ind3 : " << ind3 << endl;
    cout << "ind4 : " << ind4 << endl;
    cout << "ind5 : " << ind5 << endl;
    cout << "ind6 : " << ind6 << endl;
    cout << endl;
    
    // Tests de la méthode Individu::operator==
    cout << boolalpha;
    cout << "ind1=ind1 ? " << (ind1==ind1) << endl;
    cout << "ind1=ind2 ? " << (ind1==ind2) << endl;
    cout << "ind1=ind3 ? " << (ind1==ind3) << endl;
    cout << "ind1=ind4 ? " << (ind1==ind4) << endl;
    cout << "ind1=ind5 ? " << (ind1==ind5) << endl;
    cout << "ind1=ind6 ? " << (ind1==ind6) << endl;
    cout << endl;
    
    // Tests de la méthode Individu::operator<
    cout << "ind1<ind1 ? " << (ind1<ind1) << endl;
    cout << "ind1<ind2 ? " << (ind1<ind2) << endl;
    cout << "ind1<ind3 ? " << (ind1<ind3) << endl;
    cout << "ind1<ind4 ? " << (ind1<ind4) << endl;
    cout << "ind1<ind5 ? " << (ind1<ind5) << endl;
    cout << "ind1<ind6 ? " << (ind1<ind6) << endl;
    cout << endl;

    // Tests de la fonction de hachage
    cout << "ind1 --> " << hash<Individu>{}(ind1) << endl;
    cout << "ind2 --> " << hash<Individu>{}(ind2) << endl;
    cout << "ind3 --> " << hash<Individu>{}(ind3) << endl;
    cout << "ind4 --> " << hash<Individu>{}(ind4) << endl;
    cout << "ind5 --> " << hash<Individu>{}(ind5) << endl;
    cout << "ind6 --> " << hash<Individu>{}(ind6) << endl;
    cout << endl;

		cout<<"________________________________________"<<endl<<"Méthodes de la classe Ancêtres : "<<endl;

    // ANCETRES
    Ancetres a, b("registre.txt");

    // Tests de l'affichage
    cout << "________________________________________"<<endl<<"Affichage a (vide) et b (rempli avec registre.txt)" << endl;
    cout << "a :" << endl << a << endl;
    cout << "b:" << endl << b << endl;
    cout << endl;
    
    cout <<endl<< "Press Enter to continue . . ."<<endl<<endl;
    cin.get();
    
    //Test de la fonction racines()
    cout <<"________________________________________"<<endl<< "Racines : " << endl;
    set<Individu> listeAnc = b.racines();
    for (Individu indRes:listeAnc)
    	cout << " | " << indRes << " | ";
    cout<<endl<<endl;
    
    cout <<endl<< "Press Enter to continue . . ."<<endl<<endl;
    cin.get();
    
    //Test de la fonction ancetresCommuns(Individu ind1, Individu ind2)
    cout<<"________________________________________"<<endl<<"Ancêtres communs entre Jean et Jacques : " << endl;
    Ancetres f = b.ancetresCommuns(indTest2,indTest3);
    cout<<f<<endl << endl;
    
    cout <<endl<< "Press Enter to continue . . ."<<endl<<endl;
    cin.get();
    
    //Test de la fusion entre b et g
    cout<<"________________________________________"<<endl<<"Fusion - utilise g (construit avec registrebis.txt) : "<<endl;
    Ancetres g("registrebis.txt");
    b.fusion(g);
    cout << b << endl << endl;
    
    cout <<endl<< "Press Enter to continue . . ."<<endl<<endl;
    cin.get();
    
    //Test séparé des fonctions hasPere(Individu ind), hasMere(Individu ind), getPere(Individu ind), getMere(Individu ind)
    cout<<"________________________________________"<<endl<<"Liste les liens de parenté de b - test de fonctionnement : "<<endl;
    listeAnc = b.individus();
    for (Individu ind:listeAnc) {
    	cout << ind << endl;
    	cout << "     hasMere = " << b.hasMere(ind) << endl;
    	if (b.hasMere(ind))
    		cout << "     getMere = " << b.getMere(ind) << endl;
    	cout << "     hasPere = " << b.hasPere(ind) << endl;
    	if (b.hasPere(ind))
    		cout << "     getPere = " << b.getPere(ind) << endl;
    		cout << endl;
    }
    cout << endl;
    
    cout <<endl<< "Press Enter to continue . . ."<<endl<<endl;
    cin.get();
    
    //DESCENDANTS
    cout<<"________________________________________"<<endl<<"Méthodes de la classe Descendants : "<<endl;
    Descendants c(indTest,b);
    
    Descendants d(indTest);
    d.ajouter(indTest,indTest1);
    d.ajouter(indTest1,indTest2);
    
    //Test d'affichage
    cout << "c :" << endl << c << endl << endl;
    
    cout <<endl<< "Press Enter to continue . . ."<<endl<<endl;
    cin.get();
    
    //Test de la fonction auDegre(int k)
    cout <<"________________________________________"<<endl<< "auDegre : " << endl;
    int k=1;
    set<Individu> res = c.auDegre(k);
    cout << "Il y a "<<res.size()<<" individus au degré "<<k<<endl;
    for (Individu indRes:res)
    	cout << " | " << indRes << " | ";
    cout<<endl<<endl;
    
    cout <<endl<< "Press Enter to continue . . ."<<endl<<endl;
    cin.get();
    
    //Test de la fonction descendantsCommuns(Ancetrezs anc)
    cout <<"________________________________________"<<endl<< "Descendants Communs : " << endl;
    res = c.descendantsCommuns(d);
    for (Individu indRes:res)
    	cout << " | " << indRes << " | ";
    cout<<endl<<endl;
    
    return 0;
}
