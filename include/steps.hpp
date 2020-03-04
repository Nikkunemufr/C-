#ifndef STEPS_HPP
#define STEPS_HPP

#include <boost/mpi.hpp>
#include <vector>
#include <string>

/**
 * Type de nos estampilles.
 */
typedef std::vector< int > timestamp_t;

/**
 * Exécute une étape de calcul.
 *
 * @param[in] world le communicateur du groupe.
 * @param[in, out] timestamp l'estampille à mettre à jour.
 * @param[in, out] trace l'historique des estampilles à mettre à jour.
 */
void execute_computing_step(const boost::mpi::communicator& world,
                            timestamp_t& timestamp,
                            std::string& trace);

/**
 * Exécute une étape réception d'estampilles.
 *
 * @param[in] world le communicateur du groupe.
 * @param[in] from le tableau des identifiants des émetteurs.
 * @param[in] recv_tag le tableau des tags associés aux différentes réceptions.
 * @param[in] from_size la taille des tableaux from et recv_tags.
 * @param[in, out] timestamp l'estampille à mettre à jour.
 * @param[in, out] trace l'historique des estampilles à mettre à jour.
 */
void execute_receiving_step(const boost::mpi::communicator& world,
                            const int from[],
                            const int recv_tags[],
                            const int& from_size,
                            timestamp_t& timestamp,
                            std::string& trace);

/**
 * Exécute une étape de diffusion d'estampille.
 *
 * @param[in] world le communicateur du groupe.
 * @param[in] send_tag le tag associé à cette communication.
 * @param[in] to le tableau d'identifiants des destinataires.
 * @param[in] to_size le nombre de destinataires.
 * @param[in, out] timestamp l'estampille à mettre à jour.
 * @param[in, out] trace l'historique des estampilles à mettre à jour.
 */
void execute_sending_step(const boost::mpi::communicator& world,
                          const int& send_tag,
                          const int to[],
                          const int& to_size,
                          timestamp_t& timestamp,
                          std::string& trace);

#endif


