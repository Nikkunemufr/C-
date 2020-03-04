#include "algos.hpp"

/******************
 * execute_algo_0 *
 ******************/

std::string
execute_algo_0(const boost::mpi::communicator& world) {

  // L'estampille (toutes les composantes sont initialisées à 0).
  timestamp_t timestamp(3, 0);

  // La trace d'exécution.
  std::string trace;

  // La composante de l'algo est reinitialisée à -1 car chaque exécution d'étape
  // provoque son incrémentation.
  timestamp[0] = -1;
  
  // ... à compléter ...
  
  // C'est terminé.
  return trace;
  
}

/******************
 * execute_algo_1 *
 ******************/

std::string
execute_algo_1(const boost::mpi::communicator& world) {

  // L'estampille (toutes les composantes sont initialisées à 0).
  timestamp_t timestamp(3, 0);

  // La trace d'exécution.
  std::string trace;

  // La composante de l'algo est reinitialisée à -1 car chaque exécution d'étape
  // provoque son incrémentation.
  timestamp[1] = -1;

  // ... à compléter ...
  
  // C'est terminé.
  return trace;
  
}

/******************
 * execute_algo_2 *
 ******************/

std::string
execute_algo_2(const boost::mpi::communicator& world) {

  // L'estampille (toutes les composantes sont initialisées à 0).
  timestamp_t timestamp(3, 0);

  // La trace d'exécution.
  std::string trace;

  // La composante de l'algo est reinitialisée à -1 car chaque exécution d'étape
  // provoque son incrémentation.
  timestamp[2] = -1;

  // ... à compléter ...
  
  // C'est terminé.
  return trace;
  
}
