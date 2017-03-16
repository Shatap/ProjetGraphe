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


const int LARGEUR = 1200;
const int HAUTEUR = 800;


const float MAX_ATTRACTIVE = 100.*3;
const float MAX_REPULSIVE = 20.*3;
const float MAX_DEPLACEMENT = 20.;
const float EDGE_LENGTH = 10.*3;
const float GRAVITE = .01;


void initialiserDessin(Graphe & g, unsigned int largeur, unsigned int hauteur){

}

void initialiserIntelligementDessin(Graphe & g, unsigned int largeur, unsigned int hauteur){
    // TODO
}


Coord calculerAttractions(const Graphe &g, Sommet v){
    // TODO
    return Coord();
}

Coord calculerRepulsions(const Graphe & g, Sommet v){
    // TODO
    return Coord();
}

Coord calculerForces(const Graphe &g, Sommet v){
    // TODO
    return Coord();
}


Coord calculerBarycentre(const Graphe &g){
    // TODO
    return Coord();
}

Coord calculerForceGravite(const Graphe &g, Sommet v, const Coord &barycentre){
    // TODO
    return Coord();
}

void deplacer(Graphe &g, Sommet v, Coord deplacement){
    // TODO
}


void dessinerGraphe(Graphe & g, Appli &a){
    // initialisation aléatoire
    initialiserDessin(g, LARGEUR, HAUTEUR);

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

