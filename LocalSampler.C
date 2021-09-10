/***************************************************************************
 *
 * Local sampler with probe compleity p. Samples p bytes 
 * from a key X of length n bytes where X is represented as a 
 * matrix with c rows and n/c columns subject to the constraint 
 * that c divides p without remainder and that n, c and p and 
 * +ve integers
 * Assume that the input binary format files containing the key X have 
 * variable length but that the total number of bytes in all the files is n. 
 * This recipe implements a random access facility for reading 
 * data from random ranges of bytes in the files. 
 *
 ***************************************************************************/

#include "LocalSampler.h"
#include "FileOps.h"
#include "BLASTMatrix.h"

unsigned long LocalSampler::sample(const unsigned long n, const unsigned long p, const int *seed, const int seedLen, const std::vector<std::string> files, unsigned char* buffer)
{

  FileOps fops;
  unsigned long totalSampledBytes = 0;

  if( p % seedLen) // c should divide p without remainder
    return EXIT_FAILURE;

  if( n <=0 || p <=0 || seedLen <= 0) // from the set of natural numbers excl. zero
    return EXIT_FAILURE;
  
  std::vector<FileToKeyByteMap> keyMap;
  for(int i = 0; i < seedLen; i++)
    {
      if(seed[i] >= n / seedLen)
	return EXIT_FAILURE;
    }

  fops.populateKeyMap(files.size(), keyMap);
  fops.fileChecks(files, keyMap);
  BLASTMatrix bm(n, seedLen);  

  for(int i = 0; i < seedLen; i++)
    {
      
      bm.readModularRange(seed[i], p/seedLen, i, keyMap, buffer + totalSampledBytes);
      totalSampledBytes += p/seedLen;
      
    }

  return totalSampledBytes;
  
}  







