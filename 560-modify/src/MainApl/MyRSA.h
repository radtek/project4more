#ifndef __MYRSA_H__
#define __MYRSA_H__

#include <string>

using std::string;

/*
#include "files.h"
#include "filters.h"
#include "hex.h"
#include "randpool.h"
#include "rsa.h"

using namespace std;
using namespace CryptoPP;

const string pubKey = "305A300D06092A864886F70D01010105000349003046024100AA90427A11AAB3714F8\
0046DDAE3E318547BD7D7495EE329A76460B2A47F860952FD150A9C081676BF446CB8711A4ABA967\
56AAA0DEFE787C01992A2B13CF24D020111";

const string privKey = "30820152020100300D06092A864886F70D01010105000482013C3082013802010002\
4100AA90427A11AAB3714F80046DDAE3E318547BD7D7495EE329A76460B2A47F860952FD150A9C08\
1676BF446CB8711A4ABA96756AAA0DEFE787C01992A2B13CF24D020111024003582975D83086073D\
CB4B6186CD40B029D03B72A715F06030756B4ECC02801E44B1AFDF2532275A61517A0759175F5336\
65E1068BC93F6BE4CDE9C252FA3A25022100BF185871BCDCAF3DE27F1376A883926C1BC4F056CB90\
0F7EF937C48D855EE1A3022100E47EB324762D9037798A09CB08EEBABAA464A6056948358A31DC3C\
5EA4047B4F022100A89D02BEB5B3A9AF1324D4F03A55F9AAAF172E6AB39D3AD9727C8040A2DB3F8F\
0220285298157E4446A060BE01BA6AFCF3C6957B2C5B4ED081EB35F9B04CEFC48E3B02201FE4BD24\
462D5815D519E4C51114D79C4302F6AD24D61893FBA5827531EEB55C";

class CMyRSA
{
public:
    CMyRSA(void);
    virtual ~CMyRSA(void);

    //You must set the KeyLength 512, 1024, 2048 ...
    void GenerateKey(const unsigned int KeyLength, const char *Seed, RSAES_OAEP_SHA_Decryptor &Priv, RSAES_OAEP_SHA_Encryptor &Pub);
    void GenerateKey(const unsigned int KeyLength, const char *Seed, string &strPriv, string &strPub);
    
    //use public key to encrypt
    void EncryptString(const RSAES_OAEP_SHA_Encryptor &Pub, const char *Seed, const string &Plaintext, string &Ciphertext);
    void EncryptString(const string &strPub, const char *Seed, const string &Plaintext, string &Ciphertext);
    string EncryptString(const char *Seed, const string &Plaintext);

    //use private key to decrypt
    void DecryptString(const RSAES_OAEP_SHA_Decryptor &Priv, const string &Ciphertext, string &Plaintext);
    void DecryptString(const string &strPriv, const string &Ciphertext, string &Plaintext);
    string DecryptString(const string &Ciphertext);

private:
    static RandomPool & RNG(void);

private:
    static RandomPool m_sRandPool;

};
*/

/***************************************
-----------------------------------------
****************************************/

class CMyRSA
{
public:
		string EncryptString(const char *Seed, const string &Plaintext)
		{
			return Plaintext;
		}

		string DecryptString(const string &Ciphertext)
		{
			return Ciphertext;
		}

};


#endif /* End of __MYRSA_H__ */