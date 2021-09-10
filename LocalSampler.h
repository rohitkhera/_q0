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
#include <string>


class LocalSampler
{

 public:
  LocalSampler() {};
  int sample(const unsigned long n, const unsigned long p, const std::vector<long> seed, const std::vector<std::string> files, unsigned char* buffer);

};

#endif /* HDR_BLAST_SAMPLER_H */
