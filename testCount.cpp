#include "Count.hpp"
#include "Metrics.hpp"
#include <array>
#include <list>
#include <iostream>
#include <sstream>
#include <cstdlib>

/**
 * Routine d'évaluation des performances.
 *
 * @param[in] first le paramètre @c first de l'algorithme.
 * @param[in] last le paramètre @c last de l'algorithme.
 * @param[in] val  le paramètre @c val de l'algorithme.
 * @param[in] threads le nombre de threads utilisés.
 * @param[in] titre le titre du benckmark.
 * @param[in] iters le nombre d'itérations à effectuer sur le même algorithme 
 *   pour obtenir des mesures de temps conséquentes.
 */
template< typename InputIterator, typename T >
void
tester(const InputIterator& first, 
       const InputIterator& last, 
       const T& val,
       const int& threads,
       const std::string& titre,
       const size_t& iters) {

  using namespace paralgos;

  // Le résultat de l'algorithme (un par version).
  typename std::iterator_traits< InputIterator >::difference_type resSeq,
    resPar;

  // Durée d'exécution de la version séquentielle (bibliothèque standard).
  double seq;
  {
    const double start = omp_get_wtime( );
    for (size_t i = 0; i != iters; i ++) {
      resSeq = std::count(first, last, val); 
    }
    const double stop = omp_get_wtime( );
    seq = stop - start;
  }

  // Durée d'exécution de la version parallèle.
  double par;
  {
    const double start = omp_get_wtime( );
    for (size_t i = 0; i != iters; i ++) {
      resPar = Count::apply(first, last, val);
    }
    const double stop = omp_get_wtime( );
    par = stop - start;
  }

  // Affichage des résultats.
  std::cout << "--[ " << titre << ": begin ] --" << std::endl;
  std::cout << "\tDurée seq. :\t\t" << seq << " sec." << std::endl;
  std::cout << "\tres. seq.  :\t\t" << resSeq << std::endl;
  std::cout << "\tDurée par. :\t\t" << par << " sec." << std::endl;
  std::cout << "\tres. par.  :\t\t" << resPar << std::endl;  
  std::cout << "\tThread(s):\t\t" << threads << std::endl;
  std::cout << "\tSpeedup:\t\t" << Metrics::speedup(seq, par) << std::endl;
  std::cout << "\tEfficiency:\t\t"
	    << Metrics::efficiency(seq, par, threads)
	    << std::endl;
  std::cout << "--[ " << titre << ": end ] --" << std::endl;
  std::cout << std::endl;

}

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

  //  Nombre de threads utilisés.
  int threads;
#pragma omp parallel
#pragma omp single
    threads = omp_get_num_threads();

  // Nombres d'éléments à traiter.
  const size_t n = 1024 * 1021;

  // Conteneurs manipulés. Tous sont déclarés au même niveau afin que leurs
  // destructeurs éventuels ne viennent pas parasiter les mesures de durées
  // d'exécution.
  std::list< int > liste;
  std::array< int, n > tableau;
  for (int i = 0; i != n; i ++) {
      liste.push_back(i % 5);
      tableau[i] = i % 5;
  }

  // La valeur recherchée.
  const int val = 3;
  
  // Premier test : la liste d'entiers.  
  tester(liste.begin(), 
         liste.end(), 
         val,
         threads,
         "list",
         iters);

  // Second test : le tableau d'entiers.
  tester(tableau.begin(),
         tableau.end(), 
         val,
         threads,
         "array",
         iters);
 
  // Tout s'est bien passé.
  return EXIT_SUCCESS;

}

