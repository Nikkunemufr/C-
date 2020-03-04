#include "bubbleSort.hpp"
#include "pipelinedBubbleSort.hpp"
#include "Metrics.hpp"
#include <tbb/task_scheduler_init.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <chrono>
#include <cstdlib>

/**
 * Programme principal.
 *
 * @param[in] argc le nombre d'arguments de la ligne de commandes.
 * @param[in] argv les arguments de la ligne de commandes.
 * @return @c EXIT_SUCCESS en cas d'exécution réussie ou @c EXIT_FAILURE en cas
 *   de problèmes.
 */
int
main(int argc, char* argv[]) {

  // La ligne de commandes est vide : l'utilisateur demande de l'aide.
  if (argc == 1) {
    std::cout << "Usage: " << argv[0] << " nb_iterations" << std::endl;
    return EXIT_SUCCESS;
  }

  // Le nombre d'arguments est différent de 1 : l'utilisateur fait n'importe
  // quoi.
  if (argc != 2) {
    std::cerr << "Nombre d'argument(s) incorrect." << std::endl;
    return EXIT_FAILURE;
  }

  // Tentative d'extraction du nombre d'itérations.
  size_t iters;
  {
    std::istringstream entree(argv[1]);
    entree >> iters;
    if (! entree || ! entree.eof()) {
      std::cerr << "Argument incorrect." << std::endl;
      return EXIT_FAILURE;
    }
  }    

  // Tableau des éléments à trier, ces derniers étant ici des nombres 
  // pseudo-réels double précision.
  std::vector< double > tableau(1021);

  // Relation d'ordre total pour le tri : "strictement inférieur à".
  const auto comp = std::less< const double& >();

  // Instants représentant respectivement le démarrage et l'arrêt du 
  // chronomètre.
  std::chrono::time_point< std::chrono::steady_clock > start, stop;

  // Chronométrage de la version séquentielle. A chaque itération de la boucle,
  // nous utilisons l'algorithme iota de la bibliothèque standard pour (re) 
  // placer le tableau à trier dans la pire des configurations pour le bubble 
  // sort.
  start = std::chrono::steady_clock::now();
  for (size_t i = 0; i < iters; i ++) {
    std::iota(tableau.rbegin(), tableau.rend(), 0);
    sorting::bubbleSort(tableau.begin(), tableau.end(), comp);
  }
  stop = std::chrono::steady_clock::now();
  const int seq = 
    std::chrono::duration_cast< std::chrono::milliseconds >(stop - start).count();

  // Affichage des résultats de la version séquentielle. Nous utilisons le
  // nouvel algorithme is_sorted, introduit par la norme C++ 2011, pour vérifier
  // que le tableau est trié selon la relation d'ordre total souhaité.
  std::cout << "--[ bubbleSort: begin ]--" << std::endl;
  std::cout << "\tDurée:\t\t" << seq << " msec." << std::endl;
  std::cout << "\tVerdict:\t\t"
	    << std::boolalpha 
	    << std::is_sorted(tableau.begin(), tableau.end(), comp)
	    << std::endl;
  std::cout << "--[ bubbleSort: end ]--" << std::endl;
  std::cout << std::endl;

  // Nombre de tronçons pouvant circuler à un instant donnée dans le pipeline.
  // En règle générale, la configuration optimale consiste à utiliser un thread
  // par coeur, ce nombre de threads représentant également le nombre de jeton
  // pouvant circuler dans le pipeline à un instant donné.
  const size_t chunks = tbb::task_scheduler_init::default_num_threads();
  tbb::task_scheduler_init init(chunks);

  // Chronométrage de la version parallèle dans les mêmes conditions que la
  // version séquentielle.
  start = std::chrono::steady_clock::now();
  for (size_t i = 0; i < iters; i ++) {
    std::iota(tableau.rbegin(), tableau.rend(), 0);
    sorting::pipelinedBubbleSort(tableau.begin(), 
    				 tableau.end(), 
    				 comp,
    				 chunks);
  }
  stop = std::chrono::steady_clock::now();
  const int par = 
    std::chrono::duration_cast< std::chrono::milliseconds >(stop - start).count();

  // Affichage des résultats de la version parallèle avec, en plus, le calcul
  // des facteurs d'accélération et d'efficacité. Une accélération sur-linéaire
  // indique une meilleure utilisation des caches L2 (partagé) et L1 (privé).
  std::cout << "--[ pipelinedBubbleSort: begin ]--" << std::endl;
  std::cout << "\tThread(s):\t" << chunks << std::endl;
  std::cout << "\tDurée:\t\t" << par << " msec." << std::endl;
  std::cout << "\tVerdict:\t\t"
	    << std::boolalpha 
	    << std::is_sorted(tableau.begin(), tableau.end(), comp)
	    << std::endl;
  std::cout << "\tSpeedup:\t" 
	    << Metrics::speedup(seq, par)
	    << std::endl;
  std::cout << "\tEfficiency:\t"
	    << Metrics::efficiency(seq, par, chunks)
	    << std::endl;
  std::cout << "--[ pipelinedBubbleSort: end ]--" << std::endl;
  std::cout << std::endl;

  // Tout s'est bien passé.
  return EXIT_SUCCESS;

}
