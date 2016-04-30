#include "problemes.h"
#include "arithmetiques.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <set>

#include <boost/algorithm/string.hpp>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(59, "XOR decryption")
{
    // Each character on a computer is assigned a unique code and the preferred standard is ASCII 
    // (American Standard Code for Information Interchange). For example, uppercase A = 65, asterisk (*) = 42, 
    // and lowercase k = 107.
    //
    // A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each byte 
    // with a given value, taken from a secret key. The advantage with the XOR function is that using 
    // the same encryption key on the cipher text, restores the plain text; for example, 65 XOR 42 = 107, 
    // then 107 XOR 42 = 65.
    //
    // For unbreakable encryption, the key is the same length as the plain text message, and the key is made 
    // up of random bytes. The user would keep the encrypted message and the encryption key in different 
    // locations, and without both "halves", it is impossible to decrypt the message.
    // 
    // Unfortunately, this method is impractical for most users, so the modified method is to use a password 
    // as a key. If the password is shorter than the message, which is likely, the key is repeated cyclically 
    // throughout the message. The balance for this method is using a sufficiently long password key for security, 
    // but short enough to be memorable.
    // 
    // Your task has been made easy, as the encryption key consists of three lower case characters. 
    // Using cipher.txt (right click and 'Save Link/Target As...'), a file containing the encrypted ASCII codes, 
    // and the knowledge that the plain text must contain common English words, decrypt the message and find 
    // the sum of the ASCII values in the original text.
    std::ifstream ifs("data/p059_cipher.txt");
    std::string entree;
    ifs >> entree;
    std::vector<std::string> names;
    boost::split(names, entree, boost::is_any_of(","));
    
    std::set<char> lettres = { ' ', ',', '(', ')', '.', '!', '\'', ';' };
    for (char c = 'a'; c < 'z' + 1; ++c) lettres.insert(c);
    for (char c = 'A'; c < 'Z' + 1; ++c) lettres.insert(c);
    for (char c = '0'; c < '9' + 1; ++c) lettres.insert(c);
    
    std::vector<char> data;
    std::transform(names.begin(), names.end(), std::back_inserter(data), 
        [](const std::string& str) { return std::stoi(str); });

    std::string message;
    for (char key1 = 'a'; key1 < 'z' + 1; ++key1)
    {
        if (lettres.find(data[0] ^ key1) == lettres.end())
            continue;
        for (char key2 = 'a'; key2 < 'z' + 1; ++key2)
        {
            if (lettres.find(data[1] ^ key2) == lettres.end())
                continue;
            for (char key3 = 'a'; key3 < 'z' + 1; ++key3)
            {
                if (lettres.find(data[2] ^ key3) == lettres.end())
                    continue;
                
                std::string key = { key1, key2, key3 }; 
                std::string decode;
                for (size_t n = 0; n < data.size(); ++n)
                {
                    const char c = data[n] ^ key[n%3];
                    if (lettres.find(c) == lettres.end())
                        break;
                    decode.push_back(data[n] ^ key[n%3]);
                }
                if (decode.size() == data.size())
                {
                    message = decode;
                    std::cout << key << ": " << decode << std::endl;
                }
            }
        }
    }
    
    nombre resultat = std::accumulate(message.begin(), message.end(), 0UL,
    		[](const nombre r, const char c)
			{
    			return r + static_cast<nombre>(c);
			}
    	);
    std::cout << "Solution: " << resultat << std::endl;
}
