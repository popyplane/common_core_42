
#include <iostream>
#include <cstring>

static void megaphone(char *str);

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            megaphone(argv[i]);
            if (i + 1 < argc)
                std::cout << " ";
        }
    }
    else
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    std::cout << std::endl;
    return (0);
}

static void megaphone(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (islower(str[i]))
            str[i] -= 32;
    }
    std::cout << str;
}