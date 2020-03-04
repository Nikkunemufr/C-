/**
 * @mainpage 
 *
 * "Hello world" par implémentation du parallel design pattern Master/Slaves
 *  en Boost.MPI.
 *
 * @author Emmanuel CAGNIOT - Emmanuel.Cagniot@ensicaen.fr
 * @date 5.4.2018
 */

#include <boost/mpi.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>

#define MASTER_TO_SLAVES 0
#define SLAVES_TO_MASTER 1

/**
 * Code exécuté par le processus maître (pid = 0).
 * 
 * @param[in] world le communicateur du groupe.
 */
void master(const boost::mpi::communicator& world);

/**
 * Code exécuté par les processus esclaves (pid /= 0).
 *
 * @param[in] world le communicateur du groupe.
 */
void slave(const boost::mpi::communicator& world);

/**
 * Programme principal.
 *
 * @param[in] argc le nombre d'arguments de la ligne de commandes.
 * @param[in] argv les arguments de la ligne de commandes.
 */
int
main(int argc, char* argv[]) {

  // Initialisation de la bibliothèque MPI pour l'architecture sous-jacente.
  boost::mpi::environment env(argc, argv);

  // Communicateur commun à tous les processus lancés.
  const boost::mpi::communicator world;

  // Si un seul processus lancé alors rien à faire.
  if (world.size() == 1) {
    std::cout << "Only one process ..." << std::endl;
    return EXIT_SUCCESS;
  }

  // Choix du code à éxecuter.
  if (world.rank() == 0) {
    master(world);
  }
  else {
    slave(world);
  }

  // Tout s'est bien passé.
  return EXIT_SUCCESS;

}

/**********
 * master *
 **********/

void
master(const boost::mpi::communicator& world) {

  // Message générique à paufiner selon l'esclave.
  const std::string msg = "hello dear process";

  // Balayage des esclaves pour leur envoyer un message.
  for (int pid = 1; pid < world.size(); pid ++) {

    // Message personnalisé.
    std::ostringstream ostr;
    ostr << msg << "[" << pid << "]";

    // Envoyer le message.
    world.send(pid, MASTER_TO_SLAVES, ostr.str()); 

  }

  // Attente de la réponse des esclaves (ordre sans importance).
  for (int pid = 1; pid < world.size(); pid ++) {

    // Message à recevoir.
    std::string msg;

    // Récéption d'un message.
    world.recv(boost::mpi::any_source, SLAVES_TO_MASTER, msg);

    // Affichage sur la sortie standard du maître.
    std::cout << msg << std::endl;

  }
  
}

/*********
 * slave *
 *********/

void
slave(const boost::mpi::communicator& world) {

  // Message à recevoir.
  std::string msg;

  // Réception du message envoyé par le processus maître.
  world.recv(0, MASTER_TO_SLAVES, msg);
  
  // Préparation de la réponse.
  std::ostringstream ostr;
  ostr << "From process ["
       << world.rank()
       << "]: thank you for msg ("
       << msg
       << ")";

  // Envoie de la réponse au processus maître.
  world.send(0, SLAVES_TO_MASTER, ostr.str());

}


