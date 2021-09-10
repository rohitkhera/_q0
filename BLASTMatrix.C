/*
 * Implement the BLAST Matrix through file operations
 */

#include "BLASTMatrix.h"
#include <iostream>


/* read the ith byte in the key */

unsigned char BLASTMatrix::readIthByte(const unsigned long index, const std::vector<FileToKeyByteMap>& keyMap)
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


unsigned char BLASTMatrix::IthByteInJthRow(const unsigned long index, const unsigned long row, const std::vector<FileToKeyByteMap>& keyMap)
{

  unsigned long linearIndex = (row * columns) + index;
  return readIthByte(linearIndex, keyMap);

}


void BLASTMatrix::getFileMapsforByteRange(const unsigned long linearStartIndex, const unsigned long linearEndIndex, const std::vector<FileToKeyByteMap>& inMap, std::vector<FileToKeyByteMap>& outMap)
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

int BLASTMatrix::readLinearRange(const unsigned long startIndex, const unsigned long endIndex, const unsigned long row, const std::vector<FileToKeyByteMap>& keyMap, unsigned char* buffer)
{

  unsigned long linearStartIndex = (row * columns) + startIndex;
  unsigned long linearEndIndex = (row * columns) + endIndex;
  unsigned long fileStartIndex = linearStartIndex;
  unsigned long curBufferIndex = 0;
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


      unsigned long readStart = fileStartIndex - outMap[i].startByteIndex;
      size_t len = 0;
      fseek(fp, readStart, SEEK_SET); 
      if(outMap[i].endByteIndex <= linearEndIndex) //Entirely read the residual range in this file
	{
	  len = fread(buffer + curBufferIndex, 1, outMap[i].endByteIndex - fileStartIndex + 1, fp);
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

int BLASTMatrix::readModularRange(const unsigned long startIndex, const unsigned long numBytes, const unsigned long row, const std::vector<FileToKeyByteMap>& keyMap, unsigned char* buffer)
{

  size_t len = 0;
  if(startIndex + numBytes > columns)
    {

      unsigned long resLen = columns - startIndex;
      readLinearRange(startIndex, columns, row, keyMap, buffer);
      unsigned long wrappedLastIndex = numBytes - (columns - startIndex);

      readLinearRange(0, wrappedLastIndex, row, keyMap, buffer + resLen); 

    }
  else
    {
      readLinearRange(startIndex, startIndex + numBytes - 1, row, keyMap, buffer);
    }

  return EXIT_SUCCESS;

}

