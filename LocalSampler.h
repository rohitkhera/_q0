/**************************************************************
 *
 * For a local extractor with probe compleity p, sample p bytes 
 * from a key X of lenght n bytes where X is a represented as a 
 * matrix with c rows and n/c columns .
 * 
 **************************************************************/
#ifndef HDR_BLAST_SAMPLER_H
#define HDR_BLAST_SAMPLER_H 

#include <vector>

using namespace std;

class LocalSampler
{

 public:
  LocalSampler() {};
  unsigned char* sample(int p, vector<long> seed);

};

#endif /* HDR_BLAST_SAMPLER_H */
