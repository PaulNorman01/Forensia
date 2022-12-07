

#include "common.h"


static uint8_t
CorruptStep(const char* filename, const off_t filesize, const char* pattern)
{
    uint8_t ret = 0;

    FILE* fp = fopen(filename, "w");
    if (fp != NULL)
    {
        off_t i;
        uint8_t length = (uint8_t)strlen(pattern);
        if (length > 0)
        {
            off_t times = (filesize / length) + (filesize % length);
            for (i = 0; i < times; i++)
            {
                fwrite(pattern, sizeof(char), length, fp);
            }
        }
        else
        {
            srand((unsigned int)time(NULL));
            for (i = 0; i < filesize; i++)
            {
                int n = rand();
                fwrite(&n, sizeof(char), 1, fp);
            }
        }
        fclose(fp);
    }
    else
    {
        ret = 1;
    }
    return ret;
}

static uint8_t
CorruptFile(const char* filename)
{
    uint8_t ret = 0;

    struct stat st;
    if (stat(filename, &st) == 0)
    {
        if (S_ISREG(st.st_mode) != 0)
        {
            off_t filesize = st.st_size;
            const char* steps[35] = { "", "", "", "", "\x55", "\xAA",
                                     "\x92\x49\x24", "\x49\x24\x92",
                                     "\x24\x92\x49", "\x00", "\x11",
                                     "\x22", "\x33", "\x44", "\x55",
                                     "\x66", "\x77", "\x88", "\x99",
                                     "\xAA", "\xBB", "\xCC", "\xDD",
                                     "\xEE", "\xFF", "\x92\x49\x24",
                                     "\x49\x24\x92", "\x24\x92\x49",
                                     "\x6D\xB6\xDB", "\xB6\xDB\x6D",
                                     "\xDB\x6D\xB6", "", "", "", "" };
            uint8_t i;
            for (i = 0; i < 35; i++)
            {
                if (CorruptStep(filename, filesize, steps[i]) != 0)
                {
                    fprintf(stderr, "corrupt: shredding of '%s' ", filename);
                    fprintf(stderr, "failed on step %d\n", i);
                    ret = 1;
                    break;
                }
            }
        }
        else
        {
            fprintf(stderr, "corrupt: '%s' is not a regular file\n", filename);
            ret = 1;
        }
    }
    else
    {
        fprintf(stderr, "corrupt: '%s' not found\n", filename);
        ret = 1;
    }
    return ret;
}

bool CorruptFunc (int argc, char* test)
{
    if (argc > 1)
    {
            std::cout << "received File: " << test << std::endl;
            CorruptFile(test);
        
    }
    else
    {
        fprintf(stderr, "Usage: corrupt FILES...\n");
        fprintf(stderr, "Shreds files using the Gutmann method\n");
    }
    return 0;
}