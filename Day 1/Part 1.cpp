#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream file{"test.txt"};
    int count{0};
    int dial{50};

    std::string line{};
    while (!file.eof())
    {
        std::getline(file, line);

        int jump{std::stoi(line.substr(1, line.size() - 1))};
        jump = jump % 100;

        switch (line[0])
        {
            case 'R':
                dial = (dial + jump) % 100;
                break;
            case 'L':
                dial -= jump;
                if (dial < 0)
                    dial += 100;
                break;
        }

        if (dial == 0)
            count++;
    }

    std::cout << "Count: " << count << '\n';
    return 0;
}