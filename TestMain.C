/**************************************************************
 *
 * TestMain.C - test entry point
 *
 **************************************************************/
#include "FileOps.h"
#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "TestCommon.h"
#include "BLASTMatrix.h"
#include "LocalSampler.h"


/******************************************************* 

   Local sampler for n = 35, c = 5 and p = 15 
   from the following 5 by 7 matrix :

   
   a4 cf dd 84 f4 b8 48


   3b 1f 8a f6 c3 7c 79


   2c 7f fd ba 4f 20 3b 


   b8 08 65 2b 16 a6 5b  


   ee 5b 44 70 e6 ab 52   

   The sampler reads and concatenates bytes from each 
   row in the above matrix based on the seed vector
   { 5, 0, 2, 6, 4 }.

******************************************************/


int BLASTMatrixTest0()
{


  FileOps fops;
  unsigned char data[] = { 0xb8, 0x48, 0xa4, 0x3b, 0x1f, 0x8a, 0xfd, 0xba, 0x4f, 0x5b, 0xb8, 0x08, 0xe6, 0xab, 0x52 };
  unsigned char buffer[15] = { 0x00 };
  unsigned int seed[5] = { 5, 0, 2, 6, 4 };

  LocalSampler ls;
  unsigned long total = ls.sample(35, 15, seed, 5, fileset2, buffer);
  
  int n = mymemcmp (data, buffer, sizeof(buffer));
  if(n != 0)
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;

}



/* Get the 21st byte of the key by explicitly specifying and opening the file containtng this byte */

int BLASTMatrixTest1()
{
  
  FileToKeyByteMap map;
  unsigned char c = map.getNthByte("keydata/small/KeyData_5.dat", 0);

  if(c != 0xb8 )
    return EXIT_FAILURE;

  return EXIT_SUCCESS;

}



/* Get the 21st byte of the key without explicitly speficying the file */

int BLASTMatrixTest2()
{


  FileOps fops;

  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  unsigned char c = bm.readIthByte(21, keyMap);
  
  if(c != 0xb8 )
    return EXIT_FAILURE;

  return EXIT_SUCCESS;

}


/* Get the 15th byte of the key without explicitly speficying the file */

int BLASTMatrixTest3()
{


  FileOps fops;

  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  unsigned char c = bm.readIthByte(15, keyMap);
  
  if(c != 0x7f )
    return EXIT_FAILURE;

  return EXIT_SUCCESS;

}


/* Get the 3rd byte from the 1st  row */

int BLASTMatrixTest4()
{


  FileOps fops;

  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  unsigned char c = bm.IthByteInJthRow(3, 1, keyMap);
  
  if(c != 0xf6 )
    return EXIT_FAILURE;

  return EXIT_SUCCESS;

}


/* Get the 6th byte from the 3rd  row */

int BLASTMatrixTest5()
{


  FileOps fops;

  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  unsigned char c = bm.IthByteInJthRow(6, 3, keyMap);
  
  if(c != 0x5b )
    return EXIT_FAILURE;

  return EXIT_SUCCESS;

}

/* Verify file mapping for the following range - 3rd byte to the 6th byte of the second row */

int BLASTMatrixTest6()
{


  FileOps fops;

  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  unsigned long linearStartIndex = (2 * 7) + 3; // (row * col) + startIndex;
  unsigned long linearEndIndex = (2 * 7) + 6; // (row * col) + endIndex;
  
  std::vector<FileToKeyByteMap> outMap;
  bm.getFileMapsforByteRange(linearStartIndex, linearEndIndex, keyMap, outMap);
  
  if(outMap.size() != 2)
    return EXIT_FAILURE;

  if(outMap[0].filename != "keydata/small/KeyData_3.dat")
    return EXIT_FAILURE;

  if(outMap[1].filename != "keydata/small/KeyData_4.dat")
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;

}

/* Verify file mapping for the following range - 0th byte to the 0th byte of the third row */

int BLASTMatrixTest7()
{


  FileOps fops;

  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  unsigned long linearStartIndex = (3 * 7) + 0; // (row * col) + startIndex;
  unsigned long linearEndIndex = (3 * 7) + 0; // (row * col) + endIndex;
  
  std::vector<FileToKeyByteMap> outMap;
  bm.getFileMapsforByteRange(linearStartIndex, linearEndIndex, keyMap, outMap);
  
  if(outMap.size() != 1)
    return EXIT_FAILURE;

  if(outMap[0].filename != "keydata/small/KeyData_5.dat")
    return EXIT_FAILURE;

  
  return EXIT_SUCCESS;

}



/* Read information from the 3rd byte to the 6th byte of the second row */

int BLASTMatrixTest8()
{


  FileOps fops;
  unsigned char data[] = { 0xba, 0x4f, 0x20, 0x3b };
  unsigned char buffer[] = { 0x00, 0x00, 0x00, 0x00 };


  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  bm.readLinearRange(3, 6, 2, keyMap, buffer);

  int n = mymemcmp(data, buffer, sizeof(buffer));
  if(n != 0)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;

}


/* Read information from the 0th byte to the 1st byte of the 3rd row */

int BLASTMatrixTest9()
{


  FileOps fops;
  unsigned char data[] = { 0xb8, 0x08 };
  unsigned char buffer[] = { 0x00, 0x00 };

  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  bm.readLinearRange(0, 1, 3, keyMap, buffer);

  int n = mymemcmp (data, buffer, sizeof(buffer));
  if(n != 0)
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;

}


/* Read information from the 0th byte to the 6th byte of the 4th row */

int BLASTMatrixTest10()
{


  FileOps fops;
  unsigned char data[] = { 0xee, 0x5b, 0x44,0x70, 0xe6, 0xab, 0x52 };
  unsigned char buffer[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  bm.readLinearRange(0, 6, 4, keyMap, buffer);

  int n = mymemcmp (data, buffer, sizeof(buffer));
  if(n != 0)
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;

}

/* Read 6 bytes starting from the 4th position in the 4th row */

int BLASTMatrixTest11()
{


  FileOps fops;
  unsigned char data[] = { 0xe6, 0xab, 0x52, 0xee, 0x5b, 0x44 };
  unsigned char buffer[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  bm.readModularRange(4, 6, 4, keyMap, buffer);
  
  int n = mymemcmp (data, buffer, sizeof(buffer));
  if(n != 0)
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;

}

/* Read 6 non contigous bytes starting from the 6th position in the 4th row */

int BLASTMatrixTest12()
{


  FileOps fops;
  unsigned char data[] = { 0x52, 0xee, 0x5b, 0x44, 0x70, 0xe6 };
  unsigned char buffer[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  bm.readModularRange(6, 6, 4, keyMap, buffer);
  
  int n = mymemcmp (data, buffer, sizeof(buffer));
  if(n != 0)
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;

}


/* Read 3 non contigous bytes starting from the 5th position in the 1st row */

int BLASTMatrixTest13()
{


  FileOps fops;
  unsigned char data[] = { 0x7c, 0x79, 0x3b };
  unsigned char buffer[] = { 0x00, 0x00, 0x00 };


  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  bm.readModularRange(5, 3, 1, keyMap, buffer);
  
  int n = mymemcmp (data, buffer, sizeof(buffer));
  if(n != 0)
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;

}

/* Read 4 contigous bytes starting from the 1st  position in the 3rd  row */

int BLASTMatrixTest14()
{


  FileOps fops;
  unsigned char data[] = { 0x08, 0x65, 0x2b, 0x16 };
  unsigned char buffer[] = { 0x00, 0x00, 0x00, 0x00 };


  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  bm.readModularRange(1, 4, 3, keyMap, buffer);
  
  int n = mymemcmp (data, buffer, sizeof(buffer));
  if(n != 0)
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;

}

/* Read 2 contigous byte starting from the 5th  position in the zeroth  row */

int BLASTMatrixTest15()
{


  FileOps fops;
  unsigned char data[] = { 0xb8, 0x48 };
  unsigned char buffer[] = { 0x00, 0x00 };


  std::vector<FileToKeyByteMap> keyMap;
  fops.populateKeyMap(fileset2.size(), keyMap);
  fops.fileChecks(fileset2, keyMap);

  BLASTMatrix bm(35, 5);
  bm.readModularRange(5, 2, 0, keyMap, buffer);
  
  int n = mymemcmp (data, buffer, sizeof(buffer));
  if(n != 0)
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;

}




/* Ensure that the total size of the file is n bytes */

int fileOpsTest0(const unsigned long n)
{
  FileOps fops;

  std::vector<FileToKeyByteMap> keyMap;

  fops.populateKeyMap(fileset1.size(), keyMap);  

  if(fops.fileChecks(fileset1, keyMap) != n)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}


/* Verify Key Mapping to files */

int fileOpsTest1()
{
  FileOps fops;

  std::vector<FileToKeyByteMap> keyMap;

  fops.populateKeyMap(fileset1.size(), keyMap);  
  fops.fileChecks(fileset1, keyMap);
  
  if(keyMap[0].startByteIndex != 0)
    return EXIT_FAILURE;

  if(keyMap[0].endByteIndex != 99999)
    return EXIT_FAILURE;

  if(keyMap[1].startByteIndex != 100000)
    return EXIT_FAILURE;

  if(keyMap[1].endByteIndex != 145000)
    return EXIT_FAILURE;

  if(keyMap[2].startByteIndex != 145001)
    return EXIT_FAILURE;

  if(keyMap[2].endByteIndex != 199999)
    return EXIT_FAILURE;  


  return EXIT_SUCCESS;
}

/* Verify nth byte in a file */

int fileOpsTest2()
{

  FileToKeyByteMap map;
  unsigned char c = map.getNthByte("keydata/KeyData_0.dat", 199999);
  if(c != 'f')
    return EXIT_FAILURE;

  return EXIT_SUCCESS;

}

/* Verify Key Mapping to files */

int fileOpsTest3()
{

    FileOps fops;

  std::vector<FileToKeyByteMap> keyMap;

  fops.populateKeyMap(fileset2.size(), keyMap);  
  fops.fileChecks(fileset2, keyMap);
  
  if(keyMap[0].startByteIndex != 0)
    return EXIT_FAILURE;

  if(keyMap[0].endByteIndex != 3)
    return EXIT_FAILURE;

  if(keyMap[1].startByteIndex != 4)
    return EXIT_FAILURE;

  if(keyMap[1].endByteIndex != 10)
    return EXIT_FAILURE;

  if(keyMap[2].startByteIndex != 11)
    return EXIT_FAILURE;

  if(keyMap[2].endByteIndex != 13)
    return EXIT_FAILURE;
  
  if(keyMap[3].startByteIndex != 14)
    return EXIT_FAILURE;

  if(keyMap[3].endByteIndex != 18)
    return EXIT_FAILURE;

  if(keyMap[4].startByteIndex != 19)
    return EXIT_FAILURE;

  if(keyMap[4].endByteIndex != 20)
    return EXIT_FAILURE;

  if(keyMap[5].startByteIndex != 21)
    return EXIT_FAILURE;

  if(keyMap[5].endByteIndex != 21)
    return EXIT_FAILURE;  

  if(keyMap[6].startByteIndex != 22)
    return EXIT_FAILURE;

  if(keyMap[6].endByteIndex != 29)
    return EXIT_FAILURE;

  if(keyMap[7].startByteIndex != 30)
    return EXIT_FAILURE;

  if(keyMap[7].endByteIndex != 34)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;


}
  
int main(int argc, char **argv)
{

  fileset1.push_back("keydata/big/KeyData_0.dat");
  fileset1.push_back("keydata/big/KeyData_1.dat");
  fileset1.push_back("keydata/big/KeyData_2.dat");

  fileset2.push_back("keydata/small/KeyData_0.dat");
  fileset2.push_back("keydata/small/KeyData_1.dat");
  fileset2.push_back("keydata/small/KeyData_2.dat");
  fileset2.push_back("keydata/small/KeyData_3.dat");
  fileset2.push_back("keydata/small/KeyData_4.dat");
  fileset2.push_back("keydata/small/KeyData_5.dat");
  fileset2.push_back("keydata/small/KeyData_6.dat");
  fileset2.push_back("keydata/small/KeyData_7.dat");

  std::cout << "\n---------- START TESTS -----------" << std::endl;
  
  std::cout << "fileopsTest0" << std::endl;
  assert(fileOpsTest0(200000) == EXIT_SUCCESS);

  std::cout << "fileopsTest1" << std::endl;  
  assert(fileOpsTest1() == EXIT_SUCCESS);

  std::cout << "fileopsTest2" << std::endl;  
  assert(fileOpsTest2() == EXIT_SUCCESS);

  std::cout << "fileopsTest3" << std::endl;  
  assert(fileOpsTest3() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest0" << std::endl;  
  assert(BLASTMatrixTest0() == EXIT_SUCCESS);
  
  std::cout << "BLASTMatrixTest1" << std::endl;  
  assert(BLASTMatrixTest1() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest2" << std::endl;  
  assert(BLASTMatrixTest2() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest3" << std::endl;  
  assert(BLASTMatrixTest3() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest4" << std::endl;  
  assert(BLASTMatrixTest4() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest5" << std::endl;  
  assert(BLASTMatrixTest5() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest6" << std::endl;  
  assert(BLASTMatrixTest6() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest7" << std::endl;  
  assert(BLASTMatrixTest7() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest8" << std::endl;  
  assert(BLASTMatrixTest8() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest9" << std::endl;  
  assert(BLASTMatrixTest9() == EXIT_SUCCESS);

  /*
  std::cout << "BLASTMatrixTest10" << std::endl;  
  assert(BLASTMatrixTest10() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest11" << std::endl;  
  assert(BLASTMatrixTest11() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest12" << std::endl;  
  assert(BLASTMatrixTest12() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest13" << std::endl;  
  assert(BLASTMatrixTest13() == EXIT_SUCCESS);
  */
  
  std::cout << "BLASTMatrixTest14" << std::endl;  
  assert(BLASTMatrixTest14() == EXIT_SUCCESS);

  std::cout << "BLASTMatrixTest15" << std::endl;  
  assert(BLASTMatrixTest15() == EXIT_SUCCESS);

  std::cout << "----------- END TESTS ------------\n" << std::endl;
  return 0;

}
  

int mymemcmp(unsigned char *buf1, unsigned char *buf2, size_t len)
{

  for(int i = 0; i < len; i++)
    if(buf1[i] != buf2[i])
      return -1;

  return 0;

}




