#include "cmplx.hpp"
#include <iostream>
#include <sstream>
#include <functional>
#include <chrono>
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

  // Abolition du préfixage explicite pour notre librairie.
  using namespace cmplx;

  // Nos tableaux de nombres complexes alignés sur des blocs de 16 octets.
  const size_t n = 1024;
  alignas(16) Cmplx a[n], b[n], res[n];

  // Tous les éléments du tableau a sont initialisés à { 0 + i * 1.0 } tandis
  // que ceux de b le sont à { 1.0 + i * 0.0 }.
  for (size_t i = 0; i != n; i ++) {
    a[i][0] = b[i][1] = 1.0;
    a[i][1] = b[i][0] = 0.0;
  }  
  
  // Test de l'addition (les fonctions à appeler sont encaspulés dans des
  // lambdas sans arguments (les arguments nécessaires sont capturés par alias).
  {
    
    const auto f1 = [&]() -> void {
      for (size_t i = 0; i != n; i ++) {
        add(a[i], b[i], res[i]);
      }
    };

    const auto f2 = [&]() -> void {
      for (size_t i = 0; i != n; i ++) {
        addSSE2(a[i], b[i], res[i]);
      }      
    };
    
    const auto t1 = chronometrer(f1, iters);
    const auto t2 = chronometrer(f2, iters);
    std::cout << "add    :\t" << t1.count() << "\tms" << std::endl;
    std::cout << "addSSE2:\t" << t2.count() << "\tms" << std::endl;
    
  }
  
  // Test de la multiplication.
  {

    const auto f1 = [&]() -> void {
      for (size_t i = 0; i != n; i ++) {
        mul(a[i], b[i], res[i]);
      }
    };

    const auto f2 = [&]() -> void {
      for (size_t i = 0; i != n; i ++) {
        mulSSE2(a[i], b[i], res[i]);
      }      
    };
    
    const auto t1 = chronometrer(f1, iters);
    const auto t2 = chronometrer(f2, iters);
    std::cout << "mul    :\t" << t1.count() << "\tms" << std::endl;
    std::cout << "mulSSE2:\t" << t2.count() << "\tms" << std::endl;
    
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
