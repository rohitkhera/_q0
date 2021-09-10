/*
 * Implement the BLAST Matrix through file operations
 */

#include "BLASTMatrix.h"
#include <iostream>
#include <cstdio>

/* read the ith byte in the key */

unsigned char BLASTMatrix::readIthByte(const long index, const std::vector<FileToKeyByteMap>& keyMap)
{

  const FileToKeyByteMap *map = NULL;
  FILE *fp = NULL;

  //for(int i = 0; i < keyMap.size(); i++)
  //keyMap[i].print();

  for(int i = 0; i < keyMap.size(); i++)
    {
      if(keyMap[i].endByteIndex >= index)
	{
	  map = &keyMap[i];
	  break;
	}

    }

  if(map == NULL)
    {
      std::cerr << "Could not find file containing the " << index << " 'th key byte" << std::endl;
      return 0x00;
    }

  fp = fopen(map->filename.c_str(), "r");

  if(fp == NULL)
    {
      std::cerr << map->filename << " : File not found" << std::endl;
      return 0;
    }


  fseek(fp, index - map->startByteIndex, SEEK_SET);

  return fgetc(fp);
  

}


unsigned char BLASTMatrix::IthByteInJthRow(const long index, const long row, const std::vector<FileToKeyByteMap>& keyMap)
{

  long linearIndex = (row * columns) + index;
  return readIthByte(linearIndex, keyMap);

}


void BLASTMatrix::getFileMapsforByteRange(const long linearStartIndex, const long linearEndIndex, const std::vector<FileToKeyByteMap>& inMap, std::vector<FileToKeyByteMap>& outMap)
{

  /* Find the start file for the linear range*/
  int i = 0;

  while(i < inMap.size())
    {
      if(inMap[i].endByteIndex >= linearStartIndex)
	{
	  outMap.push_back(inMap[i]);
	  i++;
	  break;
	}

      i++;
    }

  /* Now find the other files in the linear range */
  while(i < inMap.size())
    {
      if(inMap[i].startByteIndex <= linearEndIndex)
	{
	  outMap.push_back(inMap[i]);
	}

      i++;
    }
  return;
}


/* The semnatics of this function require that it not  receive an end index that overshoots the row */

int BLASTMatrix::readLinearRange(const long startIndex, const long endIndex, const long row, const std::vector<FileToKeyByteMap>& keyMap, unsigned char* buffer)
{

  long linearStartIndex = (row * columns) + startIndex;
  long linearEndIndex = (row * columns) + endIndex;
  long fileStartIndex = linearStartIndex;
  long curBufferIndex = 0;
  std::vector<FileToKeyByteMap> outMap;

  
  getFileMapsforByteRange(linearStartIndex, linearEndIndex, keyMap, outMap);
  FILE * fp = NULL;
  
  for(int i = 0; i < outMap.size(); i++)
    {
      
      fp = fopen(outMap[i].filename.c_str(), "r");
      if(fp == NULL)
	{
	  std::cerr << outMap[i].filename << " : File not found" << std::endl;
	  return 0;
	}


      long readStart = fileStartIndex - outMap[i].startByteIndex;
      size_t len = 0;
      fseek(fp, readStart, SEEK_SET); 
      if(outMap[i].endByteIndex <= linearEndIndex) //Entirely read the residual range in this file
	{
	  len = fread(buffer + curBufferIndex, 1, outMap[i].endByteIndex - fileStartIndex + 1, fp);
	  /*
	  std::cout << "---------------------------------------" << std::endl;
	  std::cout << "linearStartIndex : " << linearStartIndex << std::endl;	  
	  std::cout << "linearEndIndex : " << linearEndIndex << std::endl;
	  std::cout << "outMap[i].endByteIndex : " << outMap[i].endByteIndex << std::endl;	  	  
	  std::cout << "ReadStart = " << readStart << " : len " << len << " : curBufferIndex " << curBufferIndex << std::endl;
	  std::cout << "outMap[i].endByteIndex : " << outMap[i].endByteIndex << " : fileStartIndex : " << fileStartIndex << std::endl;
	  */

	  fileStartIndex += len;
	  curBufferIndex += len;
	  
	}
      else //This is the last partial read that is required for the specified range
	{
	  len = fread(buffer + curBufferIndex, 1, linearEndIndex - fileStartIndex + 1, fp);
	}
    }

  return EXIT_SUCCESS;

}

int BLASTMatrix::readModularRange(const long startIndex, const long numBytes, const long row, const std::vector<FileToKeyByteMap>& keyMap, unsigned char* buffer)
{

  size_t len = 0;
  if(startIndex + numBytes > columns)
    {

      long resLen = columns - startIndex;
      readLinearRange(startIndex, columns, row, keyMap, buffer);
      long wrappedLastIndex = numBytes - (columns - startIndex);

      readLinearRange(0, wrappedLastIndex, row, keyMap, buffer + resLen); 

    }
  else
    {
      readLinearRange(startIndex, startIndex + numBytes - 1, row, keyMap, buffer);
    }

  return EXIT_SUCCESS;

}

