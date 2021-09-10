/***************************************************************************
 *
 * Local sampler with probe compleity p. Samples p bytes 
 * from a key X of length n bytes where X is represented as a 
 * matrix with c rows and n/c columns sunject to the constraint 
 * that c divides p without remainder and that n, c and p and 
 * +ve integers
 * Assume that the input binary formatfiles containing the key X have 
 * variable length but that the total number of bytes in all the files is n. 
 * This recipe implements a random access facility for reading 
 * data from random ranges of bytes in the files. 
 *
 ***************************************************************************/

#ifndef HDR_BLAST_SAMPLER_H
#define HDR_BLAST_SAMPLER_H 

#include <vector>
#include <string>


class LocalSampler
{

 public:
  LocalSampler() {};
  unsigned long sample(const unsigned long n, const unsigned long p, const int *seed, const int seedLen, const std::vector<std::string> files, unsigned char* buffer);

};

#endif /* HDR_BLAST_SAMPLER_H */
