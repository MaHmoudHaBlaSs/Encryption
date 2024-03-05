#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_MAXSIZE 10001
#define CIPHER_MAXSIZE 2002

//#define DEBUG_MODE 
//#define DEBUG_ADVANCED

void ReadFile(FILE *fptr, char Data[CIPHER_MAXSIZE]);
void Encrypt(FILE *fptr, char Plain_Text[TEXT_MAXSIZE], char Cipher_Text[CIPHER_MAXSIZE]);
void Decrypt(FILE *fptr, char Plain_Text[TEXT_MAXSIZE], char Cipher_Text[CIPHER_MAXSIZE]);

char PlainText[TEXT_MAXSIZE];
char Cipher[CIPHER_MAXSIZE];

int main()
{
    FILE *text_ptr = fopen("PlainText.txt", "r");
    ReadFile(text_ptr, PlainText);
    printf("Text : %s\n", PlainText);

    FILE *cipher_ptr = NULL;
    Encrypt(cipher_ptr, PlainText, Cipher);
    printf("Cipher = %s\n", Cipher);

    Decrypt(text_ptr, PlainText, Cipher);
    printf("Text : %s\n", PlainText);

    return 0;
}
/// @brief Read data from a file and put into local array(Data).
/// @param fptr Read File
/// @param Data Read Data
void ReadFile(FILE *fptr, char Data[TEXT_MAXSIZE])
{
    if (fptr)
    {
        int i = 0;
#ifdef DEBUG_MODE
printf("File Opened...\n");
#endif
        while ((Data[i++] = fgetc(fptr)) != EOF)
            ;
        Data[i - 1] = '\0'; // when Plaint_Text[i] = EOF
        fclose(fptr);
#ifdef DEBUG_MODE
printf("File Closed...\n");
#endif
    }
    else
    {
#ifdef DEBUG_MODE
printf("Invalid File Passed !!\n");
#endif
        fclose(fptr);
        exit(1);
    }
}
/// @brief Encrypting plain text to a cipher (Fixed Algorithm).
/// @param fptr        => Write the encrypted text(Cipher) into the cipher file.
/// @param Plain_Text  => Input txt (Copy of txt works at runtime)
/// @param Cipher_Text => Output Cipher (Copy of cipher works at runtime)
void Encrypt(FILE *fptr, char Plain_Text[TEXT_MAXSIZE], char Cipher_Text[CIPHER_MAXSIZE])
{
    fptr = fopen("CipherText.text", "w");
    if (fptr)
    {
#ifdef DEBUG_MODE
printf("Cipher File Opened...\nEncrypting...\n");
#endif
        int i = 0, j = 0, spaces = 0;
        while(Plain_Text[i] != '\0')
        {
            if(Plain_Text[i] != 32) // Character
            {
                Cipher_Text[j] = Plain_Text[i] + 3;
                Cipher_Text[j+1] = Plain_Text[i] - 3;
                fputc(Cipher_Text[j], fptr);
                fputc(Cipher_Text[j+1], fptr);
#ifdef DEBUG_ADVANCED
printf("i = %d, j = %d  --- [%d] => %c, [%d] => %c\n", i, j, j, Cipher_Text[j], j+1, Cipher_Text[j+1]);
#endif
                i++;
                j+=2;
            }
            else // Space
            {
                Cipher_Text[j] =97+ spaces*2;
                Cipher_Text[j+1] =98+ spaces*2;
                fputc(Cipher_Text[j], fptr);
                fputc(Cipher_Text[j+1], fptr);
#ifdef DEBUG_ADVANCED
printf("i = %d, j = %d  --- [%d] => %c, [%d] => %c\n", i, j, j, Cipher_Text[j], j+1, Cipher_Text[j+1]);
#endif
                i++;
                spaces++;
                j+=2;
            }
        }
        Cipher_Text[j] = '\0';
        fclose(fptr);
#ifdef DEBUG_MODE
printf("Cipher File Closed...\n");
#endif
    }
    else
    {
#ifdef DEBUG_MODE
printf("Invalid Cipher File Passed !!\n");
#endif
        fclose(fptr);
        exit(1);
    }
}
/// @brief Decrypting passed cipher to its origin text data (Fixed Algorithm).
/// @param fptr        => Write the decrypted Cipher(Text) into the text file.
/// @param Plain_Text  => Output Txt (Copy of txt works at runtime)
/// @param Cipher_Text => Input Cipher (Copy of cipher works at runtime)
void Decrypt(FILE *fptr, char Plain_Text[TEXT_MAXSIZE], char Cipher_Text[CIPHER_MAXSIZE])
{
    fptr = fopen("PlainText.txt", "w");
    if(fptr)
    {
        int i = 0, j = 0;
#ifdef DEBUG_MODE
printf("Text File Opened ...\nDecrypting...\n");
#endif
        while(Cipher_Text[i] != '\0')
        {
            if((Cipher_Text[i]-3) == (Cipher_Text[i+1] + 3)) // Character Condition
            {
                Plain_Text[j] = Cipher_Text[i]-3;
                fputc(Plain_Text[j], fptr);

                i+=2;
                j++;
            }
            else // Space Condition
            {
                Plain_Text[j] = ' ';
                fputc(Plain_Text[j], fptr);

                i+=2;
                j++;
            }
        }
        Plain_Text[j] = '\0';
        fclose(fptr);
#ifdef DEBUG_MODE
printf("Text File Closed...\n");
#endif
    }
    else
    {
#ifdef DEBUG_MODE
printf("Invalid File Text Passed \n");
#endif
        fclose(fptr);
        exit(1);
    }
}
