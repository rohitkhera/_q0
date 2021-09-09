/******************************************************
 * 
 * Take a vector of strings representing a list of files 
 *
 *****************************************************/
#ifndef HDR_BLAST_FILEOPS_H
#define HDR_BLAST_FILEOPS_H  

#include <vector>
#include <string>

/*
 * Mapping of bytes in a given file to byte ranges in the key
 */

typedef struct FileToKeyByteMap
{
  std::string filename;

  /* index in the key that corresponds to the first byte in this file */ 
  long startByteIndex;
  /* index in the key that corresponds to the last byte in this file */ 
  long endByteIndex;

  long file_sz;
  void print() const;
  unsigned char getNthByte(const std::string filename, const long n);

  FileToKeyByteMap(const FileToKeyByteMap &map) { filename = map.filename; startByteIndex = map.startByteIndex; endByteIndex = map.endByteIndex; }
  FileToKeyByteMap() { filename = ""; startByteIndex = 0; endByteIndex = 0; }
} FileToKeyByteMap;



class FileOps
{
public:
  FileOps() {};
  long fileChecks(const std::vector<std::string> fileNames, std::vector<FileToKeyByteMap>& keyMap);
  void populateKeyMap(const long n, std::vector<FileToKeyByteMap>& keyMap);  
  
};

#endif /* !HDR_BLAST_FILEOPS_H */
