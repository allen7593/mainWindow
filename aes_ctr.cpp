#include "aes_ctr.h"


std::string CTR_AESEncryptStr(string sKey, string sIV, const char *plainText)  
{  
    string outstr;  
        
    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);    
    memset(key,0x30,key.size() );    
    sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    
            
    //填iv    
    byte iv[AES::BLOCKSIZE];    
    memset(iv,0x30,AES::BLOCKSIZE);   
    sIV.size()<=AES::BLOCKSIZE?memcpy(iv,sIV.c_str(),sIV.size()):memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  
        
    AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);    
        
    CTR_Mode_ExternalCipher::Encryption ctrEncryption(aesEncryption, iv);    
        
    StreamTransformationFilter ctrEncryptor(ctrEncryption, new HexEncoder(new StringSink(outstr)));    
    ctrEncryptor.Put((byte *)plainText, strlen(plainText));    
    ctrEncryptor.MessageEnd();    
        
    return outstr;    
} 


std::string CTR_AESDecryptStr(string sKey, string sIV, const char *cipherText)    
{    
    string outstr;    
        
    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);    
    memset(key,0x30,key.size() );    
    sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    
            
    //填iv    
    byte iv[AES::BLOCKSIZE];    
    memset(iv,0x30,AES::BLOCKSIZE);    
    sIV.size()<=AES::BLOCKSIZE?memcpy(iv,sIV.c_str(),sIV.size()):memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  
  
    CTR_Mode<AES >::Decryption ctrDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);    
            
    HexDecoder decryptor(new StreamTransformationFilter(ctrDecryption, new StringSink(outstr)));    
    decryptor.Put((byte *)cipherText, strlen(cipherText));    
    decryptor.MessageEnd();    
        
    return outstr;    
} 
