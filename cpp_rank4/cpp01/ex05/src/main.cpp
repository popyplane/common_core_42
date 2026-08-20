#include "../inc/Harl.hpp"

int main(int argc, char **argv)
{
    Harl    robot;

    if (argc != 2)
    {
        cout << "Usage: ./harl [DEBUG|INFO|WARNING|ERROR]" << endl;
        return (1);
    }
    robot.complain(argv[1]);

    return (0);
}