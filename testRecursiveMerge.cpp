#include "recursiveMerge.hpp"
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <cstdlib>

/**
 * Programme principal.
 *
 * @return @c EXIT_FAILURE car exécution toujours réussie.
 */
int
main() {

  // Notre type tableau.
  typedef std::vector< int > Tableau;

  // Deux tableaux de taille différentes à fusionner. Les deux sont initialisés
  // via l'algorithme iota de la bibliothèque standard et pré-ordonnés selon
  // la relation d'ordre "strictement inférieur à".
  Tableau src1(128 * 1024), src2(src1.size() + 211);
  std::iota(src1.begin(), src1.end(), 19);
  std::iota(src2.begin(), src2.end(), 5);  

  // Le tableau cible de la fusion.
  Tableau dest(src1.size() + src2.size());

  // C'est parti avec la relation d'ordre "strictement inférieur à" par défaut.
  merging::recursiveMerge(src1.begin(), src1.end(),
                          src2.begin(), src2.end(),
                          dest.begin());
                          
  // Nous vérifions que le tableau cible est correctement ordonné via
  // l'algorithme is_sorted de la bibliothèque standard.
  std::cout << "sorted ? "
            << std::boolalpha
            << std::is_sorted(dest.begin(), dest.end())
            << std::endl;
  
  // C'est terminé.
  return EXIT_SUCCESS;
  
}
