/***********************************************************************
 *
 * File Operations and Key to File Mappings
 *
 **********************************************************************/
#include "FileOps.h"
#include <iostream>

/*
 * Check basic properties of files containing the key data
 * Args: 
 * vector<string> filenames
 * vector<struct FileToKeyByteMap> - mapping of bytes in a file to 
 * byte ranges in the key populated by this function
 * returns the total numner of bytes in the file 
 */

long FileOps::fileChecks(const std::vector<std::string> filenames, std::vector<FileToKeyByteMap>& keyMap)
{

  long total_sz = 0;
  FILE *fp = NULL;
  int num = filenames.size();
  
  long lastIndex = 0;
    for(int i = 0; i < num; i++)
    {
      fp = fopen(filenames[i].c_str(), "r");
      if(fp == NULL)
	{
	  std::cerr << filenames[i] << " : File not found" << std::endl;
	  return -1;
	}
  
      // get the size of the file
      fseek(fp, 0L, SEEK_END);

      keyMap[i].file_sz = ftell(fp);
      
      keyMap[i].filename = filenames[i];
      
      keyMap[i].startByteIndex = lastIndex;
      keyMap[i].endByteIndex = lastIndex + keyMap[i].file_sz - 1;
      lastIndex += keyMap[i].file_sz;

      total_sz += keyMap[i].file_sz;
      fclose(fp);

    }

    return total_sz; 
  
}

void FileOps::populateKeyMap(const long n, std::vector<FileToKeyByteMap>& keyMap)
{

  FileToKeyByteMap maps[n];
  for(int i = 0; i < n; i++)
    {
      keyMap.push_back(maps[i]);
    }
}


void FileToKeyByteMap::print() const 
{

  std::cout << "Filename : " << filename << " : filesize : " << file_sz << " : startByteIndex: " << startByteIndex << " : endByteIndex : " << endByteIndex << std::endl;
  
}

unsigned char FileToKeyByteMap::getNthByte(const std::string filename, const long n)
{

  FILE*fp = NULL;
  fp = fopen(filename.c_str(), "r");

  if(fp == NULL)
    {
      std::cerr << filename << " : File not found" << std::endl;
      return 0;
    }

  fseek(fp, n, SEEK_SET);
  return fgetc(fp);

}
