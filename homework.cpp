
/*!
\file
\brief файл домашнего задания

    \author Aleksei
    \version 1.0
    \date Август 2023 года
    \warning Данный файл создан только в учебных целях

Данный файл содержит в себе функцию main и выполнение ДЗ
*/
#include "lib.h"
#include <iostream>
#include <fstream>

#include <algorithm>
#include <queue>
#include <any>
#include <chrono>
#include <string>
#include <thread>

/*!
    \brief Класс для пакетной обработки комманд

    Реализация пакетной обработки команд по блокам:
     - с заданным при создании размером блока команд
     - динамическим размером блока
*/
class Commander
{
    typedef std::vector<std::string> VECANY;

public:
    /*!
    Конструктор объекта
    \param[in] _size размер блока команд
    */
    Commander(size_t _size) : szSize(_size){

                              };

    /*!
    Деструктор.
    Если блок фиксированный, то блок завершается.
    Если динамический блок не закрыт, то введенные команды игнорируются.
    \param[in] _size размер блока команд
    */
    ~Commander()
    {
        if (isDynamic == 0)
            execSeq();
    };

    /*!
    Сохранение введенной команды в очередь.
    \param[in] _cmd команда
    */
    void push(std::string _cmd)
    {
        if (_cmd.compare("{") == 0)
        {
            if (0 == isDynamic++) //Игнорируем вложенные команды.
            {
                execSeq();  //Начало динамического блока – выводим предыдущий статический досрочно.
            }
            return;
        }
        else if (_cmd.compare("}") == 0)
        {
            if (isDynamic != 0 && 0 == --isDynamic) //Игнорируем вложенные команды.
            {
                execSeq(); ///Конец динамического блока – выводим.
            }
            return;
        }
        if (vCommands.empty()) //фиксируем время получения первой команды из блока
            open();
        vCommands.push(_cmd); //Помещаем команду в блок
        if (isDynamic == 0 && vCommands.size() == szSize) 
            execSeq();      //Выводим фиксированный блок
    }

private:
    /*!
    Вызов контруктора без парамтеров запрещен
    */
    Commander() = default;

    /*!
    Выполнение команд из очереди с логированием. После выполнения очередь очищается.
    \param[in] _sequence очередь команд
    */
    void execSeq()
    {
        if (vCommands.empty())
            return;
        log("bulk: ");
        while (vCommands.size() > 1)
        {
            
            std::string command = vCommands.back();
            exec(vCommands.front());
            log(vCommands.front());
            log(", ");
            vCommands.pop();
        }
        exec(vCommands.front());
        log(vCommands.front());
        log("\n");
        vCommands.pop();
    };

    /*!
    Выполнение команды
    \param[in] _cmd команда
    */
    void exec(std::string _cmd)
    {
        // чегото делаем
        UNUSED(_cmd);
    }

    /*!
    Функция логирования в консоль и в файл
    \param[in] message строка сообщения
    */
    void log(std::string message)
    {
        std::string fileName = std::string("bulk") + std::string(std::to_string(starttime)) + std::string(".log");
        std::ofstream ofs(fileName, std::ios::app);
        std::cout << std::any_cast<std::string>(message);
        ofs << message;
        ofs.close();
    }

    /*!
    Фиксация времени получения первой команды из блока
    */
    void open()
    {
        auto now = std::chrono::system_clock::now();
        starttime = std::chrono::system_clock::to_time_t(now);
    }

private:
    std::queue<std::string> vCommands; // очередь команд
    size_t isDynamic = 0;
    time_t starttime;
    size_t szSize;
};

/*!
Функция main
последовательно выполняем требуемые кейсы
\return 0
*/
int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cout << "no bulk size: example: ./bulk 3" << std::endl;
        return 1;
    }

    Commander commands(atoi(argv[1]));
    std::string value;
    while (!std::cin.fail() && std::cin >> value)
    {
        commands.push(value);
        
        //Данные подаются на стандартный вход построчно с паузой в 1 секунду для визуального контроля.
        std::this_thread::sleep_for(std::chrono::seconds(1)); // для отладки "args": ["3", "<", "input_file2.in"],
    };
    return 0;
}