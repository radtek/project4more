#include "stdafx.h"
#include "MyRSA.h"

//#pragma comment(lib, "cryptlib.lib")
/*
CMyRSA::CMyRSA()
{

}

CMyRSA::~CMyRSA(void)
{

}

void CMyRSA::GenerateKey(const unsigned int KeyLength, const char *Seed, RSAES_OAEP_SHA_Decryptor &Priv, RSAES_OAEP_SHA_Encryptor &Pub)
{
    RandomPool RandPool;
    RandPool.IncorporateEntropy((byte *)Seed, strlen(Seed));
    
    //generate private key
    Priv = RSAES_OAEP_SHA_Decryptor(RandPool, KeyLength);

    //generate public key using private key
    Pub = RSAES_OAEP_SHA_Encryptor(Priv);
}

void CMyRSA::GenerateKey(const unsigned int KeyLength, const char *Seed, string &strPriv, string &strPub)
{
    RandomPool RandPool;
    RandPool.IncorporateEntropy((byte *)Seed, strlen(Seed));

    //generate private key
    RSAES_OAEP_SHA_Decryptor Priv(RandPool, KeyLength);
    HexEncoder PrivateEncoder(new StringSink(strPriv));
    Priv.DEREncode(PrivateEncoder);
    PrivateEncoder.MessageEnd();               

    //generate public key using private key
    RSAES_OAEP_SHA_Encryptor Pub(Priv);
    HexEncoder PublicEncoder(new StringSink(strPub));
    Pub.DEREncode(PublicEncoder);
    PublicEncoder.MessageEnd();
}

void CMyRSA::EncryptString(const RSAES_OAEP_SHA_Encryptor &Pub, const char *Seed, const string &Plaintext, string &Ciphertext)
{
    RandomPool RandPool;
    RandPool.IncorporateEntropy((byte *)Seed, strlen(Seed));

    int MaxMsgLength = Pub.FixedMaxPlaintextLength();
    for (int i = Plaintext.size(), j=0; i > 0; i -= MaxMsgLength, j += MaxMsgLength)
    {
        string PartPlaintext = Plaintext.substr(j, MaxMsgLength);
        string PartCiphertext;
        StringSource(PartPlaintext, true, new PK_EncryptorFilter(RandPool, Pub, new HexEncoder(new StringSink(PartCiphertext))));
        Ciphertext += PartCiphertext;                  
    }
}

void CMyRSA::EncryptString(const string &strPub, const char *Seed, const string &Plaintext, string &Ciphertext)
{
    StringSource PublicKey(strPub, true, new HexDecoder);
    RSAES_OAEP_SHA_Encryptor Pub(PublicKey);

    RandomPool RandPool;
    RandPool.IncorporateEntropy((byte *)Seed, strlen(Seed));

    int MaxMsgLength = Pub.FixedMaxPlaintextLength();
    for (int i = Plaintext.size(), j=0; i > 0; i -= MaxMsgLength, j += MaxMsgLength)
    {
        string PartPlaintext = Plaintext.substr(j, MaxMsgLength);
        string PartCiphertext;
        StringSource(PartPlaintext, true, new PK_EncryptorFilter(RandPool, Pub, new HexEncoder(new StringSink(PartCiphertext))));
        Ciphertext += PartCiphertext;                  
    }
}
    
string CMyRSA::EncryptString(const char *Seed, const string &Plaintext)
{
    string Ciphertext("");
    StringSource PublicKey(pubKey, true, new HexDecoder);
    RSAES_OAEP_SHA_Encryptor Pub(PublicKey);

    RandomPool RandPool;
    RandPool.IncorporateEntropy((byte *)Seed, strlen(Seed));

    int MaxMsgLength = Pub.FixedMaxPlaintextLength();
    for (int i = Plaintext.size(), j=0; i > 0; i -= MaxMsgLength, j += MaxMsgLength)
    {
        string PartPlaintext = Plaintext.substr(j, MaxMsgLength);
        string PartCiphertext;
        StringSource(PartPlaintext, true, new PK_EncryptorFilter(RandPool, Pub, new HexEncoder(new StringSink(PartCiphertext))));
        Ciphertext += PartCiphertext;                  
    }

    return Ciphertext;
}

void CMyRSA::DecryptString(const RSAES_OAEP_SHA_Decryptor &Priv, const string &Ciphertext, string &Plaintext)
{
    //indicate the ciphertext in hexcode
    int CiphertextLength = Priv.FixedCiphertextLength() * 2;
    for (int i = Ciphertext.size(), j=0; i > 0; i -= CiphertextLength, j += CiphertextLength)
    {
            string PartCiphertext = Ciphertext.substr(j, CiphertextLength);
            string PartPlaintext;
            StringSource(PartCiphertext, true, new HexDecoder(new PK_DecryptorFilter(RNG(), Priv, new StringSink(PartPlaintext))));
            Plaintext += PartPlaintext;
    }
}

void CMyRSA::DecryptString(const string &strPriv, const string &Ciphertext, string &Plaintext)
{
    StringSource PrivKey(strPriv, true, new HexDecoder);
    RSAES_OAEP_SHA_Decryptor Priv(PrivKey);
    
    //indicate the ciphertext in hexcode
    int CiphertextLength = Priv.FixedCiphertextLength() * 2;
    for (int i = Ciphertext.size(), j=0; i > 0; i -= CiphertextLength, j += CiphertextLength)
    {
            string PartCiphertext = Ciphertext.substr(j, CiphertextLength);
            string PartPlaintext;
            StringSource(PartCiphertext, true, new HexDecoder(new PK_DecryptorFilter(RNG(), Priv, new StringSink(PartPlaintext))));
            Plaintext += PartPlaintext;
    }
}
    
string CMyRSA::DecryptString(const string &Ciphertext)
{
    string Plaintext("");
    StringSource PrivKey(privKey, true, new HexDecoder);
    RSAES_OAEP_SHA_Decryptor Priv(PrivKey);
    
    //indicate the ciphertext in hexcode
    int CiphertextLength = Priv.FixedCiphertextLength() * 2;
    for (int i = Ciphertext.size(), j=0; i > 0; i -= CiphertextLength, j += CiphertextLength)
    {
            string PartCiphertext = Ciphertext.substr(j, CiphertextLength);
            string PartPlaintext;
            StringSource(PartCiphertext, true, new HexDecoder(new PK_DecryptorFilter(RNG(), Priv, new StringSink(PartPlaintext))));
            Plaintext += PartPlaintext;
    }

    return Plaintext;
}
    
RandomPool & CMyRSA::RNG(void)
{
    return m_sRandPool;
}

RandomPool CMyRSA::m_sRandPool;
*/

