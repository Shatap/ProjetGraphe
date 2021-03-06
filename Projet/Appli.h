#ifndef APPLI_H
#define APPLI_H
#include <SFML/Graphics.hpp>
#include "Graphe.h"
#include "Coord.h"

class Appli
{
public:
    Appli(unsigned int largeur, unsigned int hauteur);

    void setGraphe(Graphe &g);

    bool running() const;
    void exec();

private:
    sf::RenderWindow   m_fenetre;
    sf::Font           m_font;

    sf::CircleShape    m_sommet;
    sf::Text           m_etiquette;
    Graphe * m_g;

    bool m_montre_etiquette;

    static const float RAYON;
    static const std::string FICHIER_FONT;

    unsigned int m_largeur, m_hauteur;

    void traiter_evenements();
    void dessiner();

};

#endif // APPLI_H
