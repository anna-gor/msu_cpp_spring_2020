#include "sort.h"
#include "pool.h"
using namespace std;
const int batch_size = 1000;
ThreadPool pool(2);

void mymerge(vector<uint64_t>& vec, size_t start, size_t mid, size_t end)
{
	vector<uint64_t> one (vec.begin() + start, vec.begin() + mid + 1);
	vector<uint64_t> two (vec.begin() + mid + 1, vec.begin() + end + 1);

	size_t a = 0;
	size_t b = 0;
	size_t index = start;
	while (a < one.size() && b < two.size())
	{
		if (one[a] < two[b])
			vec[index ++] = one[a ++];
		else
			vec[index ++] = two[b ++];
	}
	while (a < one.size())
		vec[index ++] = one[a ++];
	while (b < two.size())
		vec[index ++] = two[b ++];
}

void usual_merge_sort(vector<uint64_t>& vec, size_t start, size_t end)
{
	if (start >= end)
		return;

	size_t mid = start + (end - start) / 2;

	usual_merge_sort(std::ref(vec), start, mid);
	usual_merge_sort(std::ref(vec), mid + 1, end);
	mymerge(vec, start, mid, end);
}



void merge_sort(vector<uint64_t>& vec, size_t start, size_t end)
{
	if (start >= end)
		return;

	size_t mid = start + (end - start) / 2;
    auto task1 = pool.exec(usual_merge_sort, std::ref(vec), start, mid);
    auto task2 = pool.exec(usual_merge_sort, std::ref(vec), mid + 1, end);
    task1.wait();
    task2.wait();
	mymerge(vec, start, mid, end);
}


void mergeF(const string& input1, const string& input2, const string& output)
{
	uint64_t x, y;
	ifstream f1(input1, ios::binary);
	ifstream f2(input2, ios::binary);
	ofstream f_res(output, ios::binary);
	if (!f1 || !f2 || !f_res)
	{
        throw std::runtime_error("Could not open file");
	}
	f1.read(reinterpret_cast<char*>(&x), sizeof(uint64_t));
	f2.read(reinterpret_cast<char*>(&y), sizeof(uint64_t));

	while(!f1.eof() && !f2.eof())
	{
		if(x > y)
		{
			f_res.write(reinterpret_cast<char*>(&y), sizeof(uint64_t));
			f2.read(reinterpret_cast<char*>(&y), sizeof(uint64_t));
		}
		else
		{
			f_res.write(reinterpret_cast<char*>(&x), sizeof(uint64_t));
			f1.read(reinterpret_cast<char*>(&x), sizeof(uint64_t));
		}
	}
	if(f1.eof())
	{
		while(!f2.eof())
		{
			f_res.write(reinterpret_cast<char*>(&y), sizeof(uint64_t));
			f2.read(reinterpret_cast<char*>(&y), sizeof(uint64_t));
		}
	}
	else
	{
		while(!f1.eof())
		{
			f_res.write(reinterpret_cast<char*>(&x), sizeof(uint64_t));
			f1.read(reinterpret_cast<char*>(&x), sizeof(uint64_t));
		}
	}
}

int batch(const string& strF)
{
    ifstream fin;
    fin.open(strF, ios::binary);
    vector<uint64_t> v;
    uint64_t a;
    int num_off = 0;
    if (!fin)
    {
        throw std::runtime_error("Could not open file");
    }
    while(fin.read(reinterpret_cast<char *>(&a), sizeof(uint64_t)))
    {
        if(v.size() < batch_size)
        {
            v.push_back(a);
        }
        else
        {
            ofstream fout;
            string str = "tmp_root/tmp" + to_string(num_off) + ".dat";
            fout.open(str, ios::binary);
            merge_sort(v, 0, v.size()-1);
            for(size_t i = 0; i < v.size(); i++)
            {
                fout.write(reinterpret_cast<char *>(&v[i]), sizeof(uint64_t));
            }
            v.clear();
            v.push_back(a);
            num_off++;
        }
    }
    if(v.size() != 0)
    {
        ofstream fout;
        string str = "tmp_root/tmp" + to_string(num_off) + ".dat";
        fout.open(str, ios::binary);
        merge_sort(v, 0, v.size()-1);
        for(size_t i = 0; i < v.size(); i++)
        {
            fout.write(reinterpret_cast<char *>(&v[i]), sizeof(uint64_t));
        }
        v.clear();
        num_off++;
    }
    return num_off;

}

int sort(const string& file_to_sort){
    mkdir("tmp_root", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
    int num_off = batch(file_to_sort);
    if(num_off == 0)
    {
        throw std::runtime_error("Wrong input file");
    }
    if(num_off > 2)
    {
        int i = 2;
        mergeF("tmp_root/tmp0.dat", "tmp_root/tmp1.dat", "tmp_root/tmp" + to_string(num_off) + ".dat");
        for(i; i < num_off-1; i++)
        {
            mergeF("tmp_root/tmp" + to_string(i) + ".dat",
                "tmp_root/tmp" + to_string(i + num_off - 2) + ".dat",
                "tmp_root/tmp"+ to_string(num_off - 1 + i) +".dat");

        }
        mergeF("tmp_root/tmp" + to_string(i) + ".dat",
            "tmp_root/tmp" + to_string(i + num_off - 2) + ".dat",
            "result.dat");

    }
    else
    {
        mergeF("tmp_root/tmp0.dat", "tmp_root/tmp1.dat", "result.dat");
    }
    return 0;
}