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

        switch (line[0])
        {
            case 'R':
                for (int i = 0; i < jump; i++)
                {
                    dial++;
                    if (dial == 100)
                        dial = 0;
                    if (dial == 0)
                        count++;
                }
                break;
            case 'L':
                for (int i = 0; i < jump; i++)
                {
                    dial--;
                    if (dial < 0)
                        dial += 100;
                    if (dial == 0)
                        count++;
                }
                break;
        }
    }

    std::cout << "Count: " << count << '\n';
    return 0;
}