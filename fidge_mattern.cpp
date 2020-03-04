#include "algos.hpp"

#include <cstdlib>

/**
 * Programme principal.
 *
 * @param[in] argc le nombre d'arguments de la ligne de commandes.
 * @param[in] argv les arguments de la ligne de commandes.
 * @return @c EXIT_SUCCESS en cas d'exécution réussie sinon @c EXIT_FAILURE.
 */
int
main(int argc, char* argv[]) {

  // Initialisation de l'implémentation MPI sous-jacente.
  boost::mpi::environment env(argc, argv);

  // Communicateur permettant de dialoguer avec les autres processus lancés.
  boost::mpi::communicator world;

  // Il faut au moins trois processus lancés. Si tel n'est pas le cas le
  // processus maître affiche un message sur sa sortie erreur. Tous terminent
  // en retournant le code 
  if (world.size() < 3) {
    if (world.rank() == 0) {
      std::cerr << "Il faut au moins trois processus" << std::endl;
    }
    return EXIT_FAILURE;
  }

  // C'est parti. Si plus de trois processus ont été lancés alors le surplus
  // termine immédiatement.
  std::string trace;
  switch (world.rank()) {
  case 0:
    trace = execute_algo_0(world);
    break;
  case 1:
    trace = execute_algo_1(world);
    break;
  case 2:
    trace = execute_algo_2(world);
    break;
  default:
    break;
  }

  // Le processus maître rassemble les traces d'exécution avant de les
  // afficher tandis que les autres terminent après avoir envoyer leur trace.
  // Nous pourrions utiliser une fonctionnalité
  std::vector< std::string > traces(3);
  boost::mpi::gather(world, trace, traces, 0);
  if (world.rank() == 0) {
    for (int i = 0; i < 3; i ++) {
      std::cout << "-- [ algo " << i << " ] --" << std::endl;
      std::cout << traces[i] << std::endl;
    }
  }
  
  // Tout s'est bien passé.
  return EXIT_SUCCESS;
  
}
