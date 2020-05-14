#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <atomic>
#include <mutex>
#include <deque>
#include <vector>
#include <condition_variable>

std::atomic<int> result;

std::atomic<bool>       end_of_read;

std::condition_variable cond;
std::deque<std::string> data;
std::mutex              mtx;

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
    end_of_read = false;

    std::string s;
    std::ifstream file;

    file.open(name);
    if ( !(file.is_open()) )
    {
        std::cout << name <<" not find\n";
        end_of_read = true;
        return;
    }

    while(getline(file, s))
    {
        std::unique_lock<std::mutex> lck(mtx);

        data.push_back(s);
    }

    file.close();

    end_of_read = true;
}

void count_sum()
{
    while(1)
    {
        if( end_of_read ) break;
        else
        {
            std::unique_lock<std::mutex> lck(mtx);
            if(data.empty() && end_of_read) break;
            if( data.empty() ) continue;

            result += sum_line( data.back() );
            data.pop_back();
        }
    }
}

int get_result()
{
    std::unique_lock<std::mutex> lck(mtx);
    cond.wait( lck, [](){ return end_of_read == true && data.empty(); } );
    return result.operator int();
}
int main()
{
    std::string fname = "1.txt";
    std::thread t1( read_file, fname );
    std::thread t2( count_sum );
    std::thread t3( count_sum );
    t1.join();
    t2.join();
    t3.join();

    std::cout << get_result();
    return 0;
}