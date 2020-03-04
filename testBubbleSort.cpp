#include "bubbleSort.hpp"
#include <array>
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
  typedef std::array< int, 1024 > Tableau;
  
  // Le tableau des éléments à trier que nous remplissons avec les entiers de
  // l'intervalle [0, 1024) via l'algorithme iosta de la bibliothèque standard.
  Tableau tableau;
  std::iota(tableau.begin(), tableau.end(), 0);

  // La relation d'ordre utilisée : "supérieur ou égal", ce qui correspond à
  // la complexité au pire pour le bubble sort puisque le tableau à trier est
  // déjà ordonné selon la relation d'ordre inverse.
  const std::greater_equal< Tableau::value_type > comp;

  // C'est parti.
  sorting::bubbleSort(tableau.begin(), tableau.end(), comp);

  // Nous vérifions que le tableau trié est correctement ordonné via
  // l'algorithme is_sorted de la bibliothèque standard.
  std::cout << "sorted ? "
            << std::boolalpha
            << std::is_sorted(tableau.begin(), tableau.end(), comp)
            << std::endl;
  
  // C'est terminé.
  return EXIT_SUCCESS;
  
}
