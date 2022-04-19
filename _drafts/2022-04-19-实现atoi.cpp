#include <string>
#include <math.h>

int my_atoi(std::string str)
{
    if (str.empty() || (str.size() == 1 && str[0] == '-'))
    {
        return 0;
    }
    int res = 0;
    int endIndex = 0;
    if (str[0] == '-')
    {
        endIndex++;
    }

    int p = 1;
    for (int i = str.size() - 1; i >= endIndex; i--)
    {

        char c = str[i];

        if (c < '0' || c > '9')
        {
            printf("error: not a integer.\n");
            exit(0);
        }
        int cur = (int)(c - '0');
        res += cur * p;
        p *= 10;
    }

    if (str[0] == '-')
    {
        res = -res;
    }
    return res;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s [int string]", argv[0]);
        return 0;
    }
    printf("string [%s] => int [%d]", argv[1], my_atoi(argv[1]));
}