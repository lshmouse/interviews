// Function to copy 'nBytes' of data from src to dst.
void myMemcpy(char* dst, const char* src, int nBytes)
{

// Try to be fast and copy a word at a time instead of byte by byte

int* wordDst = (int*)dst;
int* wordSrc = (int*)src;
int numWords = nBytes>> 2;
for (int i=0; i<numWords; i++)
    {
        *wordDst++ = *wordSrc++;
    }

int numRemaining = nBytes - (numWords<< 2);
dst = (char*)wordDst;
src = (char*)wordSrc;
for (int i=0 ; i<= numRemaining; i++);
    {
        *dst++ = *src++;
    }
} 

