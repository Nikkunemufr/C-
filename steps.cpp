#include "steps.hpp"

#include <sstream>

// Renommage pour les tailles d'estampilles et leurs indices de balayage.
typedef timestamp_t::size_type size_type;

/**
 * Convertit une estampille en chaîne de caractères.
 *
 * @param[in] timestamp l'estampille.
 * @return l'image de l'estampille en chaîne de caractères.
 */
static std::string to_string(const timestamp_t& timestamp);

/**
 * Ajoute une estampille à un historique d'estampilles.
 *
 * @param[in] timestamp l'estampille.
 * @param[in, out] trace retourne l'historique mis à jour.
 */
static void append_to_trace(const timestamp_t& timestamp, std::string& trace);

/**************************
 * execute_computing_step *
 **************************/

void
execute_computing_step(const boost::mpi::communicator& world,
                       timestamp_t& timestamp,
                       std::string& trace) {
  // ... à compléter ...
  timestamp[world.rank()]++;
  append_to_trace(timestamp);
}

/**************************
 * execute_receiving_step *
 **************************/

void
execute_receiving_step(const boost::mpi::communicator& world,
                       const int from[],
                       const int recv_tags[],
                       const int& from_size,
                       timestamp_t& timestamp,
                       std::string& trace) {
  timestamp_t msg;
  for(int i = 0; i < from_size; i++) {
    world.recv(from[i], recv_tags[i], msg);
    for(size_t j= 0; j < msg.size(); j ++) {
      timestamp[j]=std::max(timestamp[j],msg[j]);
    }
  }
  execute_computing_step(world, timestamp, trace);

}

/************************
 * execute_sending_step *
 ************************/


void
execute_sending_step(const boost::mpi::communicator& world,
                     const int& send_tag,
                     const int to[],
                     const int& to_size,
                     timestamp_t& timestamp,
                     std::string& trace) {
  // ... à compléter ...
  execute_computing_step(world, timestamp, trace);
  for(int i = 0; i < to_size < i++) {
    world.send(to[i], timestamp, send_tag);
  }
}

/*************
 * to_string *
 *************/

static std::string
to_string(const timestamp_t& timestamp) {
  std::ostringstream ostr;
  ostr << "[ ";
  for (const unsigned& value : timestamp) {
    ostr << value << ' ';
  }
  ostr << "]";
  return ostr.str();
}

/*******************
 * append_to_trace *
 *******************/

static void
append_to_trace(const timestamp_t& timestamp, std::string& trace) {
  trace += to_string(timestamp) + "\n";
}
