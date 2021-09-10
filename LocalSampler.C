/**************************************************************
 *
 * For a local extractor with proble compleity p, sample p bytes 
 * from a key X of lenght n bytes where X is a represented as a 
 * matrix with c rows and n/c columns .
 * 
 **************************************************************/
#include "LocalSampler.h"
#include "FileOps.h"
#include "BLASTMatrix.h"

int LocalSampler::sample(const unsigned long n, const unsigned long p, const std::vector<long> seed, const std::vector<std::string> files, unsigned char* buffer)
{

  FileOps fops;

  if( p % seed.size()) // c should divide p without remainder
    return EXIT_FAILURE;

  if( n <=0 || p <=0 || seed.size() <= 0)
    return EXIT_FAILURE;
  
  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(files.size(), keyMap);
  fops.fileChecks(files, keyMap);

  BLASTMatrix bm(n, seed.size());
  bm.readModularRange(5, 2, 0, keyMap, buffer);


  return EXIT_SUCCESS;

}







