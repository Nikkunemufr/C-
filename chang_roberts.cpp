#include "CPU.hpp"

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

  // Instanciation du communicateur du groupe de tâches lancées.
  boost::mpi::communicator world;

  // Il faut au moins trois CPU sur l'anneau.
  if (world.size() < 3) {
    std::cerr << "Requires at least three CPUs ..." << std::endl;
    return EXIT_FAILURE;
  }

  // CPU dans son état initial.
  CPU cpu = make_cpu(world);

  if (cpu.number % 2 == 0) {
    start_election(world, cpu);
  }

  while(process_msg(world,cpu));

  if(world.rank() == 0) {
    std::cout << "CPU vainqeur : " << cpu.winner_number << "\n" <<
 R"(      ___________________________________________________________________________
     /   Brilliance220P LPY                                               LED    \
    |    ____________________________________________________________________     |
    |   | 21605783@C304L-406C06:~/0_MASTER_DOP/$                             |    |
    |   | $ mpirun -np 4 bin/Release/chang_roberts                           |    |
    |   | CPU vainqueur : )"<< cpu.winner_number << R"(                                                  |    |
    |   |                              ____                                  |    |
    |   |                            {} _  \                                 |    |
    |   |                                |__ \                               |    |
    |   |                               /_____\                              |    |
    |   |                               \o o)\)_______                       |    |
    |   |                               (<  ) /#######\                      |    |
    |   |                             __{'~` }#########|                     |    |
    |   |                            /  {   _}_/########|                    |    |
    |   |                           /   {  / _|#/ )####|                     |    |
    |   |                          /   \_~/ /_ \  |####|                     |    |
    |   |                          \______\/  \ | |####|                     |    |
    |   |                           \__________\|/#####|                     |    |
    |   |                            |__[X]_____/ \###/                      |    |
    |   |                            /___________\                           |    |
    |   |                             |    |/    |                           |    |
    |   |                             |___/ |___/                            |    |
    |   |                            _|   /_|   /                            |    |
    |   |                           (___,_(___,_)                            |    |
    |   |____________________________________________________________________|    |
    |                                  PHILIPS                                    |
     \___________________________________________________________________________/
                   \________________________________________________/
                    _______________________________________________
                 _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_
              _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_
           _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_
        _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_
     _-'.-.-.-.-.-. .---.-. .-----------------------------. .-.---. .---.-.-.-.`-_
    :-----------------------------------------------------------------------------:
    `---._.-----------------------------------------------------------------._.---'
)" <<

     std::endl;
  }

  // Tout s'est bien passé.
  return EXIT_SUCCESS;

}
