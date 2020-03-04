#ifndef MSG_HPP
#define MSG_HPP

#include <boost/mpi.hpp>

#define TAG 0 // Tag commun à tous les messages.

/**
 * Type représentant un message.
 */
struct Msg {

  /** Le numéro du cpu émetteur. */
  int cpu_number;

  /** Le type de message (@c true si ELECTION, @c false si ELECTED). */
  bool is_election_kind;

};

// Fait du type Msg un type natif MPI donc serialisable.
namespace boost {

  namespace serialization {

    template< typename Archive >
    void serialize(Archive &ar, Msg &msg, unsigned int version) {
      ar & msg.cpu_number;
      ar & msg.is_election_kind;
    }

  }

}

BOOST_IS_MPI_DATATYPE(Msg);

#endif
