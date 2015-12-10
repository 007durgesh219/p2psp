
#include "trusted_peer.h"

namespace p2psp {

void TrustedPeer::Init() {
  next_sampled_index_ = 0;
  counter_ = 1;
  LOG("Initialized");
}
void TrustedPeer::SetCheckAll(bool value) { check_all_ = value; };

int TrustedPeer::CalculateNextSampled() {
  if (check_all_) {
    return 0;
  }
  int max_random = (int)(peer_list_.size() / kSamplingEffort);
  return (int)((std::rand() % std::max(1, max_random)) + kPassNumber);
};

void TrustedPeer::SendChunkHash(int chunk_number) {
  Chunk chunk = chunks_[chunk_number % buffer_size_];
  // chunk_hash = hashlib.sha256(chunk).digest()

  std::vector<char> msg(34);

  *((short*)msg.data()) = htons((short)chunk_number);
  // TODO: SHA256 library
  // msg = struct.pack('H32s', chunk_number, chunk_hash)
  team_socket_.send_to(buffer(msg), splitter_);
};
}