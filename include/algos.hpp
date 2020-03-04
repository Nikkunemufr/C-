#ifndef ALGOS_HPP
#define ALGOS_HPP

#include "steps.hpp"

#define ALGO_0_STEP_0 0 
#define ALGO_0_STEP_1 1
#define ALGO_0_STEP_4 2
#define ALGO_2_STEP_1 3
#define ALGO_2_STEP_2 4

/**
 * Lance l'exécution du premier algorithme.
 *
 * @param[in] world le communicateur du groupe.
 * @return l'historique des estampilles.
 */
std::string execute_algo_0(const boost::mpi::communicator& world);

/**
 * Lance l'exécution du deuxième algorithme.
 *
 * @param[in] world le communicateur du groupe.
 * @return l'historique des estampilles.
 */
std::string execute_algo_1(const boost::mpi::communicator& world);

/**
 * Lance l'exécution du troisième algorithme.
 *
 * @param[in] world le communicateur du groupe.
 * @return l'historique des estampilles.
 */
std::string execute_algo_2(const boost::mpi::communicator& world);

#endif
