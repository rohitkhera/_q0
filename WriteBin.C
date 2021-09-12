
/* arch specific program to wrtie binary test files */

#include <string>
#include <vector>
#include <iostream>

int main(int arcc, char **argv)
{
  
  std::vector<std::string> files;

  files.push_back("keydata/small/KeyData_0.dat");
  files.push_back("keydata/small/KeyData_1.dat");
  files.push_back("keydata/small/KeyData_2.dat");
  files.push_back("keydata/small/KeyData_3.dat");
  files.push_back("keydata/small/KeyData_4.dat");
  files.push_back("keydata/small/KeyData_5.dat");
  files.push_back("keydata/small/KeyData_6.dat");
  files.push_back("keydata/small/KeyData_7.dat");


  unsigned char f0[4] = { 0xa4, 0xcf, 0xdd, 0x84 };
  unsigned char f1[7] = { 0xf4, 0xb8, 0x48, 0x3b, 0x1f, 0x8a, 0xf6 };
  unsigned char f2[3] = { 0xc3, 0x7c, 0x79 };
  unsigned char f3[5] = { 0x2c, 0x7f, 0xfd, 0xba, 0x4f };
  unsigned char f4[2] = { 0x20, 0x3b };
  unsigned char f5[1] = { 0xb8 };
  unsigned char f6[8] = { 0x08, 0x65, 0x2b, 0x16, 0xa6, 0x5b, 0xee, 0x5b };
  unsigned char f7[5] = { 0x44, 0x70, 0xe6, 0xab, 0x52 };

  FILE *fptr = NULL;

  fptr = fopen(files[0].c_str(),"wb");
    if(fptr == NULL)
    {
      std::cerr <<  "Could not open file for write" << std::endl;
      return 0;
    }


  fwrite(f0, sizeof(f0),1,fptr);

  fclose(fptr);


  fptr = fopen(files[1].c_str(),"wb");  

    if(fptr == NULL)
    {
      std::cerr <<  "Could not open file for write" << std::endl;
      return 0;
    }

  fwrite(f1, sizeof(f1),1,fptr);

  fclose(fptr);


  fptr = fopen(files[2].c_str(),"wb");  

  if(fptr == NULL)
    {
      std::cerr <<  "Could not open file for write" << std::endl;
      return 0;
    }

  
  fwrite(f2, sizeof(f2),1,fptr);

  fclose(fptr);


  fptr = fopen(files[3].c_str(),"wb");  

  if(fptr == NULL)
    {
      std::cerr <<  "Could not open file for write" << std::endl;
      return 0;
    }

  
  fwrite(f3, sizeof(f3),1,fptr);

  fclose(fptr);


  fptr = fopen(files[4].c_str(),"wb");  

  if(fptr == NULL)
    {
      std::cerr <<  "Could not open file for write" << std::endl;
      return 0;
    }


  fwrite(f4, sizeof(f4),1,fptr);

  fclose(fptr);


  fptr = fopen(files[5].c_str(),"wb");  

  if(fptr == NULL)
    {
      std::cerr <<  "Could not open file for write" << std::endl;
      return 0;
    }

  
  fwrite(f5, sizeof(f5),1,fptr);

  fclose(fptr);


  fptr = fopen(files[6].c_str(),"wb");  

  if(fptr == NULL)
    {
      std::cerr <<  "Could not open file for write" << std::endl;
      return 0;
    }

  
  fwrite(f6, sizeof(f6),1,fptr);

  fclose(fptr);
  

  fptr = fopen(files[7].c_str(),"wb");  

  if(fptr == NULL)
    {
      std::cerr <<  "Could not open file for write" << std::endl;
      return 0;
    }

  
  fwrite(f7, sizeof(f7),1,fptr);

  fclose(fptr);


  return 0;
}


