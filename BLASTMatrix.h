/******************************************************
 * 
 * Implement the BLAST Matrix through file operations
 *
 *****************************************************/
#ifndef HDR_BLAST_MATRIX_H
#define HDR_BLAST_MATRIX_H  

#include "FileOps.h"

class BLASTMatrix 
{  
  
public:

  BLASTMatrix(const unsigned long n, const unsigned long c) : n(n), c(c), columns(n/c) {};

  unsigned char readIthByte(const unsigned long index, const std::vector<FileToKeyByteMap>& keyMap);

  unsigned char IthByteInJthRow(const unsigned long index, const unsigned long row, const std::vector<FileToKeyByteMap>& keyMap);

  int readLinearRange(const unsigned long startindex, const unsigned long endIndex, const unsigned long row, const std::vector<FileToKeyByteMap>& keyMap, unsigned char* buffer);

  int readModularRange(const unsigned long startIndex, const unsigned long len, const unsigned long row, const std::vector<FileToKeyByteMap>& keyMap, unsigned char* buffer);

  void getFileMapsforByteRange(const unsigned long linearStartIndex, const unsigned long linearEndIndex, const std::vector<FileToKeyByteMap>& inMap, std::vector<FileToKeyByteMap>& outMap);

private:

  BLASTMatrix() {};
  unsigned long n;
  unsigned long c;
  unsigned long columns;
  
};  


#endif /* !HDR_BLAST_MATRIX_H */
