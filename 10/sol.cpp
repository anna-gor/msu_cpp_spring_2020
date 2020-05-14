#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <atomic>
#include <mutex>
#include <deque>
#include <vector>
#include <condition_variable>

std::atomic<int> _result;

std::atomic<bool>       _end_of_read;

std::condition_variable _cond;
std::deque<std::string> _data;
std::mutex              _mtx;

int sum_line(const std::string& line)
{
    std::string word;
    std::istringstream iss(line, std::istringstream::in);
    std::vector<int> wordsVector;
    int sum = 0;
    while( iss >> word )
    {
        sum += std::stoi(word);
    }
    return sum;
}

void read_file(const std::string& name)
{
    _end_of_read = false;

    std::string s;
    std::ifstream file;

    file.open(name);
    if ( !(file.is_open()) )
    {
        std::cout << name <<" not find\n";
        _end_of_read = true;
        return;
    }

    while(getline(file, s))
    {
        std::unique_lock<std::mutex> lck(_mtx);

        _data.push_back(s);
        //        std::cout << s << std::endl;
        //_cond.notify_all();
    }

    file.close();

    _end_of_read = true;
}

void count_sum()
{
    while(1)
    {
        if( _end_of_read ) break;
        else
        {
            //std::cout << "here" << std::endl;
            std::unique_lock<std::mutex> lck(_mtx);
            if(_data.empty() && _end_of_read) break;

            //_cond.wait( lck, [](){ return _data.empty(); } );

            if( _data.empty() ) continue;

            _result += sum_line( _data.back() );
            _data.pop_back();
        }
    }
    //std::cout << "end1\n";
}

int get_result()
{
    //std::cout << "1\n";
    std::unique_lock<std::mutex> lck(_mtx);
    _cond.wait( lck, [](){ return _end_of_read == true && _data.empty(); } );
    return _result.operator int();
}
int main()
{
    std::string fname = "1.txt";
    std::thread t1( read_file, fname );
    std::thread t2( count_sum );
    std::thread t3( count_sum );
    t1.join();
    //std::cout << "111\n";
    t2.join();
    //std::cout << "122\n";
    t3.join();
    //std::cout << "133\n";

    std::cout << get_result();
    return 0;
}