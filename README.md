Overview and Security Definitions

The code in this repo implements a local sampler in the the BLAST “sample and extract” paradigm where p where bits are sampled from a key X (based on a computationally secure seed of length c), and subsequently used by a non local extractor to compute one time encryption pads. 
The seeds are computationally secure in the sense that their security is based on the following computational assumptions (i) Decision Diffie Hellman (DDH) / Computational Diffie Hellman (CDH) (ii) the existence of pseudo random generators whose output is indistinguishable from random for PPT adversaries. 
The IND-CCA game used in the reductions is a hybrid consisting of (1) A computationally bounded adversary A_1 that capable of making adaptive oracle queries to learn linear functions of the key (recall that the encryption scheme implemented by the encryption oracle is an XOR of the message and extracted bits) (2) A computationally unbounded Information Theoretic adversary A_2 that is given the seed after access to the shared server T is removed. The security reduction utilizes linear algebra based arguments. 
During the extraction phase (not implemented here), the goal is to take non random (leaked) and random bits in the sample and mix them to produce a truly random string. The extraction method utilized is able to extract more entropy (more extracted random bits) from the sample than what is implied by the leftover hash lemma given some bounded amount of leakage of the sampled bits 

Implementation 

Local sampler - sample p bytes from a key X of length n bytes where X is represented as a matrix with c rows and n/c columns subject to the constraint that c divides p without remainder and that n, c and p and +ve integers. Assume that the input binary format files containing the key X have variable length but that the total number of bytes in all the files is n. This recipe implements a random access facility for reading data from random ranges of bytes in the files. 
An example test case is depicted below 



 Local sampler for n = 35, c = 5 and p = 15 
 from the following 5 by 7 matrix :

   
   a4 cf dd 84 f4 b8 48


   3b 1f 8a f6 c3 7c 79


   2c 7f fd ba 4f 20 3b 


   b8 08 65 2b 16 a6 5b  


   ee 5b 44 70 e6 ab 52   

The sampler reads and concatenates bytes from each row in the above matrix based on the following seed vector { 5, 0, 2, 6, 4 }. The memory complexity for the sampler is O(p) and the data is read of the following input files of unequal length:

KeyData_0.dat - containing 4 bytes
KeyData_1.dat - containing 7 bytes
KeyData_2.dat - containing 3 bytes
KeyData_3.dat - containing 5 bytes
KeyData_4.dat - containing 2 bytes
KeyData_5.dat - containing 1 byte
KeyData_6.dat - containing 8 bytes
KeyData_7.dat - containing 5 bytes


Side Channel Attacks

This implementation does not incorporate countermeasures against potential timing or cache attacks. 


Build 

Pre-requisites: g++ and make
Download this repo and cd in the directory _q0 and type make.
Then run the tests by entering the following on the command line 
./sampler_test

You may be required to add the current directory (_q0) to your LD_LIBRARY_PATH environment variable 

Testing

The test files were generated by the openssl rand command in binary format. Generating the files in ASCII hex format was considered for portability on different systems but the binary format was settled upon for performance. Since the binary files were generated on OSX, it is possible that format related issues could arise on other systems. 


