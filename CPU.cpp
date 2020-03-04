#include "CPU.hpp"

/**
 * Traite un message de type ELECTION.
 *
 * @param[in] world le communicateur du groupe.
 * @param[in] msg le message.
 * @param[in, out] cpu le cpu destinataire.
 */
static void process_election_msg(const boost::mpi::communicator& world,
                                 const Msg& msg,
                                 CPU& cpu);

/**
 * Traite un message de type ELECTED.
 *
 * @param[in] world le communicateur du groupe.
 * @param[in] msg le message.
 * @param[in, out] cpu le cpu destinataire.
 */
static void process_elected_msg(const boost::mpi::communicator& world,
                                const Msg& msg,
                                CPU& cpu);

/************
 * make_cpu *
 ************/

CPU
make_cpu(const boost::mpi::communicator& world) {
  const int size = world.size();
  CPU cpu;

  cpu.number               = world.rank();
  cpu.neighbor             = (cpu.number + 1) % size;
  cpu.is_candidate         = false;
  cpu.highest_known_number = size;
  cpu.winner_number        = size;

  return cpu;
}

/******************
 * start_election *
 ******************/

void
start_election(const boost::mpi::communicator& world, CPU& cpu) {
  cpu.is_candidate = true;
  cpu.highest_known_number = cpu.number;
  Msg msg = {cpu.highest_known_number, true};
  world.send(cpu.neighbor, TAG, msg);
}

/***************
 * process_msg *
 ***************/

bool
process_msg(const boost::mpi::communicator& world, CPU& cpu) {
  Msg msg;
  world.recv(boost::mpi::any_source, TAG, msg);//en provenance de n'importe qui
  if (msg.is_election_kind) {
    process_election_msg(world, msg, cpu);
    return true;
  } else {
    process_elected_msg(world, msg, cpu);
    return false;
  }

}

/************************
 * process_election_msg *
 ************************/

static void
process_election_msg(const boost::mpi::communicator& world,
                     const Msg& msg,
                     CPU& cpu) {
  const auto& num = msg.cpu_number;
  if(!cpu.is_candidate) {
    cpu.is_candidate = true;
    cpu.highest_known_number = std::max(cpu.number, num);
    Msg msg2 = {cpu.highest_known_number, true};
    world.send(cpu.neighbor, TAG, msg2);
  } else {
    if (num > cpu.highest_known_number) {
      cpu.highest_known_number = num;
      Msg msg3 = {cpu.highest_known_number, true};
      world.send(cpu.neighbor, TAG, msg3);
    } else if (cpu.number == num) {
      Msg msg4 = {cpu.number, false};
      world.send(cpu.neighbor, TAG, msg4);
    }
  }
}

/***********************
 * process_elected_msg *
 ***********************/

static void
process_elected_msg(const boost::mpi::communicator& world,
                    const Msg& msg,
                    CPU& cpu) {
  const auto& num = msg.cpu_number;
  cpu.winner_number = num;
  cpu.is_candidate = false;
  if (cpu.number != num) {
    Msg msg1 = {num, false};
    world.send(cpu.neighbor, TAG, msg1);
  }
}
