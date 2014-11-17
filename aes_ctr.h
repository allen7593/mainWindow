#include <crypto++/aes.h>
#include <crypto++/hex.h>
#include <crypto++/modes.h>
#include <sstream>
#include <string>

using namespace std;
using namespace CryptoPP;

string CTR_AESEncryptStr(string sKey, string sIV, const char *plainText);

string CTR_AESDecryptStr(string sKey, string sIV, const char *cipherText);


