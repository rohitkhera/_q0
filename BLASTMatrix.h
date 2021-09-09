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
  BLASTMatrix(const long n, const long c) : n(n), c(c), columns(n/c) {};
  unsigned char readIthByte(const long index, const std::vector<FileToKeyByteMap> keyMap);
  unsigned char IthByteInJthRow(const long index, const long row, const std::vector<FileToKeyByteMap> keyMap);
  int readRangePartial(const long startindex, const long endIndex, const long row, const std::vector<FileToKeyByteMap> keyMap, unsigned char* buffer, const long buflen);

private:
  BLASTMatrix() {};
  long n;
  long c;
  long columns;
  
};  


#endif /* !HDR_BLAST_MATRIX_H */
