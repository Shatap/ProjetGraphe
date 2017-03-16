#include "Sommet.h"
#include "iostream"

int Sommet::m_curId = 0;

Sommet::Sommet(bool valide) : m_id(valide ? m_curId++ : -1)
{
    std::cout << "n1 = " << m_id << " " << valide << std::endl;

}

int Sommet::id() const {
    return m_id;
}


bool Sommet::valide() const{
    return (m_id != -1);
}

bool Sommet::operator<(const Sommet &n) const{
    return m_id < n.m_id;
}

bool Sommet::operator==(const Sommet &n) const{
    return m_id == n.m_id;
}
