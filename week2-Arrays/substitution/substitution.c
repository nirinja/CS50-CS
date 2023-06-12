#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
//problem set 2-2

string ciphertext(string key, string text);
int keyArray[26];

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        int len = strlen(key);
        bool duplicates = false;
        bool isNotAZ = false;
        // key puts all in uppercase and then into array
        for (int i = 0; i < 26; i++)
        {
            keyArray[i] = key[i];
            for (int j = 0; j < i; j++)
            {
                if (key[i] == key[j])
                {
                    duplicates = true;
                }
            }
            if (isalpha(key[i]) == false)
            {
                isNotAZ = true;
            }
        }

        if (len == 26 && duplicates == false && isNotAZ == false)
        {
            string text = get_string("plaintext: ");
            printf("ciphertext: %s\n", ciphertext(key, text));
            return 0;
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

string ciphertext(string key, string text)
{
    string cipText = text;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (text[i] >= 65 && text[i] <= 90) // uppercase
        {
            int index = text[i] - 65;
            cipText[i] = keyArray[index];
            cipText[i] = toupper(cipText[i]);
        }
        if (text[i] >= 97 && text[i] <= 122) // lowercase
        {
            int index = text[i] - 97;
            cipText[i] = keyArray[index];
            cipText[i] = tolower(cipText[i]);
        }
    }
    return cipText;
}