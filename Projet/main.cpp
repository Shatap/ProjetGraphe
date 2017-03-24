    #include <iostream>
#include <deque>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include "Appli.h"
#include "time.h"
using namespace std;


const int LARGEUR = 1920;
const int HAUTEUR = 1080;


const float MAX_ATTRACTIVE = 100.*3;
const float MAX_REPULSIVE = 20.*3;
const float MAX_DEPLACEMENT = 20.;
const float EDGE_LENGTH = 10.*3;
const float GRAVITE = .01;


void initialiserDessin(Graphe & g, unsigned int largeur, unsigned int hauteur){
    std::cout<<"TAILLE DU SET"<<g.sommets().size()<<endl;

    srand(time(NULL));

    for(Sommet s : g.sommets())
    {
        float haut = rand()% HAUTEUR + 0;
        float larg= rand()% LARGEUR +0;
        Coord repos{larg,haut};
        g.positionSommet(s,repos);
    }
}

Coord calculerAttractions(const Graphe &g, Sommet v){

    Coord attra ;
    for(Sommet s : g.voisins(v)){
        attra = g.positionSommet(s)-g.positionSommet(v);
        attra= ((attra/attra.norm()*((attra.norm()*attra.norm())/EDGE_LENGTH*EDGE_LENGTH)));
    }
    if(attra.norm()>MAX_ATTRACTIVE)
        attra=(attra/attra.norm())*MAX_ATTRACTIVE;
    return attra;
}

Coord calculerRepulsions(const Graphe & g, Sommet v)
{

    Coord repulsion ;
    for (Sommet s : g.sommets())
    {
        repulsion=g.positionSommet(v)-g.positionSommet(s);
     if(!(s==v))
     {
         repulsion= (repulsion*EDGE_LENGTH)/(repulsion.norm()*repulsion.norm()*repulsion.norm());

     }
    }

    if(repulsion.norm()>MAX_REPULSIVE)
        repulsion=(repulsion/repulsion.norm())*MAX_REPULSIVE;
    return repulsion;
}

Coord calculerBarycentre(const Graphe &g){

    Coord coord ;

    for(auto  s:g.sommets())
    {
        coord+=g.positionSommet(s);

    }


    return coord/g.nbSommets();
}

Coord calculerForceGravite(const Graphe &g, Sommet v, const Coord &barycentre){

    float n=barycentre.norm();
    Coord f = g.positionSommet(v)-barycentre;
     Coord gravite = (f/n)*GRAVITE;


    return gravite;
}

Coord calculerForces(const Graphe &g, Sommet v){
    Coord coord;
   return  coord = calculerAttractions(g,v)+calculerRepulsions(g,v)+calculerForceGravite(g,v,calculerBarycentre(g));

}
void initialiserIntelligementDessin(Graphe & g, unsigned int largeur, unsigned int hauteur){

 initialiserDessin(g, largeur, hauteur);

 for(Sommet s:g.voisins(s))
     g.positionSommet(s,calculerForces(g,s));



}







void deplacer(Graphe &g, Sommet v, Coord deplacement){


    if(deplacement.norm()>MAX_DEPLACEMENT)
        deplacement = deplacement/deplacement.norm()*MAX_DEPLACEMENT;
    g.positionSommet(v,g.positionSommet(v)+deplacement);

}


void dessinerGraphe(Graphe & g, Appli &a){
    // initialisation aléatoire


    // répéter autant de fois qu'il y a de sommets
    unsigned int nb_iterations = g.nbSommets();
    for(unsigned int i = 0; i < nb_iterations; ++i){
        cout << i << " / " << nb_iterations << endl;
        Coord barycentre = calculerBarycentre(g);
        for(Sommet v: g.sommets()){
            Coord deplacement = calculerForces(g,v);
            deplacement = deplacement + calculerForceGravite(g, v, barycentre);
            deplacer(g,v, deplacement);
        }

        if(a.running())
            a.exec();
        else return;
    }
}

int main()
{
    srand(time(NULL));

    // chargement et création des graphe et fenetre d'affichage
    string fichier = "acteurs.txt";
    Graphe g;
    if(!g.charger(fichier)){
        cout << "Erreur de chargement de fichier" << endl;
        return 1;
    }

    Appli app {LARGEUR, HAUTEUR};
    app.setGraphe(g);

    cout << "Dessin du graphe..." << flush;
    dessinerGraphe(g, app);
    cout << "fini" << endl;

    // pour ne pas fermer la fenêtre après le dessin
    while(app.running())
        app.exec();

    return 0;
}

