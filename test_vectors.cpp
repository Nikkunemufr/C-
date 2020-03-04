#include "vectors.hpp"
#include <iostream>
#include <sstream>
#include <functional>
#include <chrono>
#include <algorithm>
#include <cstdlib>

// Type synonyme pour une routine de traitement de vecteurs (pattern Command
// réalisé via des lambdas).
typedef std::function< void () > Impl;

/**
 * Chronomètre l'implémentation d'une fonctionalité.
 * 
 * @param[in] impl l'implémentation à chronométrer.
 * @param[in] iters le nombre d'itérations à effectuer.
 * @return la durée d'exécution en millisecondes.
 */
std::chrono::milliseconds
chronometrer(const Impl& impl, const size_t& iters);

/**
 * Programme principal.
 *
 * @param[in] argc le nombre d'arguments de la ligne de commandes.
 * @param[in] argv les arguments de la ligne de commandes.
 * @return @c EXIT_SUCCESS en cas d'exécution réussie sinon @c EXIT_FAILURE.
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

  // Longueur paire des tableaux manipulés.
  const size_t n = 1024;

  // Deux tableaux x (initialisé à 1.0) et y et alignés sur des blocs de 16
  // octets.
  alignas(16) double x[n], y[n];
  std::fill(x, x + n, 1.0);

  // Abolition du préfixage explicite pour notre librairie.
  using namespace vectors;

  // Test de yaxb (les fonctions à appeler sont encaspulés dans des lambdas
  // sans arguments (les arguments nécessaires sont capturés par alias).
  {
    const double a = 0.5, b = 1.0;

    const auto t1 = chronometrer([&]{ yaxb    (a, x, n, b, y); }, iters);
    const auto t2 = chronometrer([&]{ yaxbSSE2(a, x, n, b, y); }, iters);
    std::cout << "yaxb    :\t" << t1.count() << "\tms" << std::endl;
    std::cout << "yaxbSSE2:\t" << t2.count() << "\tms" << std::endl;
    std::cout << std::endl;    
  }

  // Test de sum.
  {
    double acc;
    
    const auto t1 = chronometrer([&]{ acc = sum    (x, n); }, iters);
    const auto t2 = chronometrer([&]{ acc = sumSSE2(x, n); }, iters);
    std::cout << "sum    :\t" << t1.count() << "\tms" << std::endl;
    std::cout << "sumSSE2:\t" << t2.count() << "\tms" << std::endl;
    std::cout << std::endl;    
  }


  // Test de reverse.
  {    
    const auto t1 = chronometrer([&]{ reverse    (x, n, y); }, iters);
    const auto t2 = chronometrer([&]{ reverseSSE2(x, n, y); }, iters);
    std::cout << "reverse    :\t" << t1.count() << "\tms" << std::endl;
    std::cout << "reverseSSE2:\t" << t2.count() << "\tms" << std::endl;
    std::cout << std::endl;    
  }  

  // C'est terminé.
  return EXIT_SUCCESS;

}

/****************
 * chronometrer *
 ****************/

std::chrono::milliseconds
chronometrer(const Impl& impl, const size_t& iters) {

  // C'est parti.
  const auto start = std::chrono::steady_clock::now();
  for (size_t it = 0; it != iters; it ++) {
    impl();
  }
  const auto stop = std::chrono::steady_clock::now();

  // C'est terminé.
  return std::chrono::duration_cast< std::chrono::milliseconds >(stop - start);
  
}
