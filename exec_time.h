//Program: Library for calculation Execution Time
//Author: Sharath Chandra Nirmala
//USN: 4NI20CS093
using chrono::high_resolution_clock;
using chrono::duration;
using chrono::duration_cast;
using chrono::milliseconds;

class ExecTime
{
private:
    high_resolution_clock::time_point t1, t2;
public:
    void GetT1() { t1 = high_resolution_clock::now(); }
    void GetT2() { t2 = high_resolution_clock::now(); }
    void PrintExecTime()
    {
        duration<double, milli> timeTaken = t2 - t1;
        cout << "Execution Time: " << timeTaken.count() << "ms.\n";
    }
};