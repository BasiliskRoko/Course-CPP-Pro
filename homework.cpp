
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

#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>

// Program Options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "boost/filesystem.hpp" // includes all needed Boost.Filesystem declarations
#include "boost/filesystem/path.hpp"
namespace fs = boost::filesystem; // for ease of tutorial presentation;
                                  //  a namespace alias is preferred practice in real code

#include <boost/algorithm/string.hpp>
#include "boost/regex.hpp"

#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/crc.hpp>

class IHash
{
public:
    virtual void GetHash(const char *const buffer, size_t buffer_size) = 0;
    virtual bool operator>(const IHash *r) const = 0;
    virtual bool operator==(const IHash *right) const = 0;
};
class Md5Hash : public IHash
{
public:
    Md5Hash() = default;

    void GetHash(const char *const buffer, size_t buffer_size) override
    {
        GetMd5(buffer, buffer_size);
    }

    bool operator>(const IHash *r) const override
    {
        for (size_t i = 0; i < 4; ++i)
        {
            if (digest[i] > ((Md5Hash *)r)->digest[i])
                return true;
            else if (digest[i] < ((Md5Hash *)r)->digest[i])
                return false;
        }
        return false;
    }

    bool operator==(const IHash *r) const override
    {
        for (size_t i = 0; i < 4; ++i)
        {
            if (digest[i] != ((Md5Hash *)r)->digest[i])
                return false;
        }
        return true;
    };

private:
    void GetMd5(const char *const buffer, size_t buffer_size)
    {
        if (buffer == nullptr)
        {
            return;
        }

        boost::uuids::detail::md5 boost_md5;
        boost_md5.process_bytes(buffer, buffer_size);
        boost_md5.get_digest(digest);
    }
    boost::uuids::detail::md5::digest_type digest;
};

class Crc32Hash : public IHash
{
public:
    Crc32Hash() = default;

    void GetHash(const char *const buffer, size_t buffer_size) override
    {
        GetCrc32(buffer, buffer_size);
    }

    bool operator>(const IHash *r) const override
    {
        return (digest > ((Crc32Hash *)r)->digest);
    }

    bool operator==(const IHash *r) const override
    {
        return (digest == ((Crc32Hash *)r)->digest);
    };

private:
    void GetCrc32(const char *const buffer, size_t buffer_size)
    {
        boost::crc_32_type result;
        result.process_bytes(buffer, buffer_size);
        digest = result.checksum();
    }
    uint32_t digest;
};

struct ComparedFile
{
    ComparedFile(fs::path _path, std::shared_ptr<IHash> _hash) : strategy(std::move(_hash))
    {
        full_path = _path;
        id = -1;
        isEOF = false;
    }
    int id;
    fs::path full_path;
    std::ifstream file;
    bool isEOF;
    std::shared_ptr<IHash> strategy;
};

std::vector<ComparedFile> allFile;

/*!
Функция вывода целочисленного типа и, что можно к нему не явно преобразовать в побайтовом виде
\param[in] value значение
*/
bool skip_dir(const std::string dir, po::variables_map &vm)
{
    std::vector<std::string> ignores;
    boost::algorithm::split(ignores, vm["ignore"].as<std::string>(), boost::is_any_of(","));
    for (const auto &skip : ignores)
    {

        fs::path ignore_full_path(fs::initial_path<fs::path>());
        ignore_full_path = fs::system_complete(fs::path(skip));
        if (fs::exists(ignore_full_path))
        {
            if (std::string(dir).compare(ignore_full_path.string()) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

std::string str_toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](auto c)
                   { return std::toupper(c); });
    return s;
}

bool skip_mask(const std::string file, po::variables_map &vm)
{
    std::vector<std::string> masks;
    boost::algorithm::split(masks, vm["mask"].as<std::string>(), boost::is_any_of(";"));

    for (const auto &mask : masks)
    {
        boost::smatch what;

        std::string result = boost::regex_replace(mask, boost::regex("\\*"), ".*", boost::match_default | boost::format_all);
        result = boost::regex_replace(result, boost::regex("\\?"), ".", boost::match_default | boost::format_all);
        const boost::regex my_filter(str_toupper(result));
        if (!boost::regex_match(str_toupper(file), what, my_filter))
        {
            return true;
        }
    }
    return false;
}

void scan_dir(const std::string dir, po::variables_map &vm)
{

    fs::path full_path(fs::initial_path<fs::path>());
    full_path = fs::system_complete(fs::path(dir));
    if (!fs::exists(full_path))
    {
        std::cout << "\nNot found: " << full_path.string() << std::endl;
        return;
    }

    if (fs::is_directory(full_path))
    {

        if (skip_dir(full_path.string(), vm))
            return;

        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(full_path);
             dir_itr != end_iter;
             ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    if (vm["scan"].as<int>() == 0)
                        continue;
                    scan_dir(dir_itr->path().string(), vm);
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (fs::file_size(dir_itr->path()) < vm["min"].as<size_t>())
                        continue;

                    if (skip_mask(dir_itr->path().filename().string(), vm))
                        continue;
                    if (vm["hash"].as<std::string>().compare("crc32") == 0)
                    {
                        allFile.push_back(ComparedFile(dir_itr->path(), std::make_shared<Crc32Hash>()));
                    }
                    else
                    {
                        allFile.push_back(ComparedFile(dir_itr->path(), std::make_shared<Md5Hash>()));
                    }
                }
            }
            catch (const std::exception &ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
}

/*!
Функция main
последовательно выполняем требуемые кейсы
\return 0
*/
int main(int argc, const char *argv[])
{
    try
    {
        po::options_description desc{"Options"};
        desc.add_options()("help,h", "please read REDME.md")                                //
            ("input", po::value<std::string>()->default_value("./"), "input directory/ies") //
            ("ignore", po::value<std::string>()->default_value(""), "ignore directory/ies") //
            ("scan,s", po::value<int>()->default_value(0), "deep scan")                     //
            ("min", po::value<size_t>()->default_value(1), "minimum size file")             //
            ("mask", po::value<std::string>()->default_value("*"), "mask files")            //
            ("block,b", po::value<size_t>()->default_value(1), "block size")                //
            ("hash", po::value<std::string>()->default_value("md5"), "deep scan");          //

        po::variables_map vm;
        po::store(parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        std::vector<std::string> inputs;
        boost::algorithm::split(inputs, vm["input"].as<std::string>(), boost::is_any_of(","));

        for (const auto &in : inputs)
        {
            scan_dir(in, vm);
        }

        if (allFile.size() > 1)
        {
            size_t curMaxGroup = 1;
            std::streampos blockSize = vm["block"].as<size_t>();
            char *memblock = new char[blockSize];
            size_t countEOF = 0;
            while (countEOF < allFile.size() - 1)
            {
                for (auto &f : allFile)
                {
                    if (f.isEOF)
                    {
                        countEOF++;
                        continue;
                    }
                    if (!f.file.is_open())
                    {
                        f.file.open(f.full_path.string().c_str(), std::ios::binary);
                    }
                    if (f.file.is_open())
                    {
                        if (f.file.eof())
                        {
                            f.isEOF = true;
                            continue;
                        }

                        f.file.read(memblock, blockSize);
                        if (f.file.gcount() == 0)
                        {
                            f.isEOF = true;
                            continue;
                        }
                        if (f.file.gcount() != blockSize)
                            memset(memblock + f.file.gcount(), 0, blockSize - f.file.gcount());

                        f.strategy->GetHash(memblock, blockSize);
                    }
                }

                std::sort(allFile.begin(), allFile.end(), [](auto const &a, auto const &b)
                          { return *(a.strategy.get()) > (b.strategy.get()); });

                IHash *etalon;
                bool firstTime = true;
                for (auto &f : allFile)
                {
                    if (firstTime)
                    {
                        firstTime = false;
                        etalon = f.strategy.get();
                        if (f.isEOF)
                            continue;
                        f.id = ++curMaxGroup;
                    }
                    if (f.isEOF)
                        continue;
                    if (*(etalon) == f.strategy.get())
                    {
                        f.id = curMaxGroup;
                    }
                    else
                    {
                        etalon = f.strategy.get();
                        f.id = ++curMaxGroup;
                    }
                }
                std::sort(allFile.begin(), allFile.end(), [](auto const &a, auto const &b)
                          { return a.id > b.id; });

                auto itCurrent = allFile.begin();
                int countGroup = 1;
                for (auto it = itCurrent + 1; it != allFile.end(); ++it)
                {
                    if (it->id == itCurrent->id)
                        countGroup++;
                    else
                    {
                        if (!itCurrent->isEOF && countGroup == 1)
                        {
                            itCurrent->isEOF = true;
                        }
                        itCurrent = it;
                        countGroup = 1;
                    }
                }
            }

            for (auto &f : allFile)
            {
                if (f.file.is_open())
                {
                    f.file.close();
                }
            }
        }

        if (allFile.size() > 0)
        {
            int currrent_group = allFile.begin()->id;
            for (const auto &f : allFile)
            {
                if (currrent_group != f.id)
                {
                    std::cout << std::endl;
                    currrent_group = f.id;
                }
                std::cout << f.full_path.string() << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}