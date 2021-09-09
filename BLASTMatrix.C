/*
 * Implement the BLAST Matrix through file operations
 */

#include "BLASTMatrix.h"
#include <iostream>


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


/* This function is guranteed not to receive an end index that overshoots the row */

int BLASTMatrix::readRangePartial(const long startIndex, const long endIndex, const long row, const std::vector<FileToKeyByteMap>& keyMap, unsigned char* buffer, const long buflen)
{

  long linearStartIndex = (row * columns) + startIndex;
  long linearEndIndex = (row * columns) + endIndex;

  std::vector<FileToKeyByteMap> outMap;
  
  getFileMapsforByteRange(linearStartIndex, linearEndIndex, keyMap, outMap);
  return EXIT_SUCCESS;

}
