#include <iostream>

void processResistors(void);
void processCapacitors(void);
int main() {
    std::cout << "请选择电容或者电阻，1为电容，2为电阻:";
    int flag;
    std::cin >> flag;
    if (flag == 1)
    {

    }
    else if (flag == 2)
    {
        processResistors();
    }
    else
    {
        std::cout << "输入错误！！" << std::endl;
    }
    return 0;
}

void processResistors(void)
{
    std::cout << "请输入您需要的阻值（如：0.02, 3.1m, 200, 2.2k, 2.4M）：" ;
    std::string str;
    std::cin >> str;
    float power = 1;
    if (str[str.length() - 1] == 'k' || str[str.length() -1] == 'K')
    {
        power = 1000;
    }
    else if (str[str.length() -1] == 'M')
    {
        power = 1000000;
    }
    else if( str[str.length() -1] == 'm')
    {
        power = 0.001;
    }
    float value;
    try
    {
        if (power == 1)
            value = std::stof(str);
        else
            value = std::stof(str.substr(0, str.length() - 1));
        std::cout << "value is " << value << std::endl;
    }catch (std::invalid_argument&)
    {
        std::cout << "输入错误！！" << std::endl;
        exit(-1);
    }
    value = value*power;
    std::cout << "请输入你需要的精度，1为5%，2为1%，3为0.1% ：";
    std::string precision;
    std::cin >> precision;
    if (precision == "1")
    {
        precision = "5%";
    } else if (precision == "2")
    {
        precision = "1%";
    }else if (precision == "3")
    {
        precision = "0.1%";
    }
    else
    {
        std::cout << "输入错误！！" << std::endl;
        exit(-1);
    }
    std::cout << "请输入你该贴片电阻的封装（如：0402，0603等）";
    std::string footprint;
    std::cin >> footprint;
    try
    {
        std::stoi(footprint);
    }catch (std::invalid_argument&)
    {
        std::cout << "输入错误！！" << std::endl;
        exit(-1);
    }
    std::string main;
    if (value >= 100 && value <=1000)
    {
        main = footprint + " ";
        main += std::to_string((int)value) + "Ω(" + std::to_string((int)value) + "0)±" + precision;
        std::cout << main << std::endl;
    }
}
void processCapacitors(void)
{

}
