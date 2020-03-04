#ifndef CPU_HPP
#define CPU_HPP

#include "Msg.hpp"

/**
 * Type représentant un CPU.
 */
struct CPU {

  /** Numéro du CPU (et aussi rang de la tâche associée). */
  int number;

  /** Numéro du CPU voisin. */
  int neighbor;

  /** Flag indiquant si le CPU est candidat à l'élection. */
  bool is_candidate;
  
  /** Plus haute priorité déjà rencontrée. */
  int highest_known_number;

  /** Le numéro du CPU vainqueur de l'élection. */
  int winner_number;

};

/**
 * Fabrique puis retourne un CPU dans son état initial (non candidat).
 *
 * @param[in] world le communicateur du groupe.
 * @return l'état initial du CPU.
 */
CPU make_cpu(const boost::mpi::communicator& world);

/**
 * Déclare un CPU comme candidat à l'élection.
 *
 * @param[in] world le communicateur du groupe.
 * @param[in, out] cpu le cpu après changement d'état.
 */
void start_election(const boost::mpi::communicator& world, CPU& cpu);

/**
 * Traite un message reçu et modifie l'état du CPU en conséquence.
 *
 * @param[in] world le communicateur du groupe.
 * @param[in, out] cpu le CPU.
 * @return @c true si d'autres messages doivent encore être traités.
 */
bool process_msg(const boost::mpi::communicator& world, CPU& cpu);

#endif

