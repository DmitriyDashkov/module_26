
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

class Randoms
{
private:
    int m_N; //всего чисел
    int m_M; //количество векторов
    vector<int> m_intvector;
public:
    int N()                 { return m_N; }
    int M()                 { return m_M; }
    vector<int> intvector() { return m_intvector; }
    Randoms(int n, int m) : m_N(n), m_M(m)
    {};
    vector<vector<int>> vec;
    //проверка размеров векторов
    bool vector_size_check()
    {
        if (m_N % m_M != 0)
        {
            cout << "Data is not correct" << endl;
            return false;
        }
        else
        {
            //generate_vectors();
            return true;
        }
    };
    
    //генерация вектора
    void generate_randoms()
    {
        if(vector_size_check())
            for (int i = 0; i < m_N; i++)
            {
                int x = rand();
                m_intvector.push_back(x);
            }
    }
    
    //разбиение вектора на несколько векторов
    void generate_vectors()
    {
        for (int i = 0; i < m_M; i++)
        {
            vector<int> v;
            for (int j = 0; j < m_N / m_M; j++)
            {
                v.push_back(m_intvector.at(j * i + j));
            }
            vec.push_back(v);
        }
    };

    //печать векторов
    void write_vectors()
    {
        for (int i = 0; i < m_M; i++)
        {
            cout << "Vector " << i << "     ";
            for (int j = 0; j < m_N / m_M; j++)
            {
                cout << vec.at(i).at(j) << "  ";
            }
            cout << endl;
        }
    }

    //сумма чисел вектора
    int sum_vec(vector<int> vec)
    {
        int s = 0;
        for (int i = 0; i < vec.size(); i++)
        {
            s += vec.at(i);
        }
        return s;
    }
};

    int sum = 0;
    void sum_vec(vector<int> v)
    {
        for (int i = 0; i < v.size(); i++)
        {
            sum += v.at(i);
        }
    }

    int sum_vecLast(vector<int> v)
    {
        for (int i = 0; i < v.size(); i++)
        {
            sum += v.at(i);
        }
        return sum;
    }

int main()
{
    const int number_of_cores = 1;
    Randoms randoms(10000000, number_of_cores);
    randoms.generate_randoms();
    randoms.generate_vectors();
    auto t_start = std::chrono::system_clock::now();

    if (number_of_cores > 1) {
        thread tmpT(sum_vec, randoms.vec.at(0));
        sum += sum_vecLast(randoms.vec.at(1));
        tmpT.join();
    } else {
        sum += sum_vecLast(randoms.vec.at(0));
    }
    cout << "Sum =  " << sum << endl;

    auto t_end = std::chrono::system_clock::now();
    long diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
    cout << "Time (ms) is " << diff << endl;
   
    return 0;
}


