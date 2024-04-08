#include "benchmark.hpp"

template<typename element>
class test_array{
    public:
        element* array;
        test_array(size_t ds_size){
            array = new element[ds_size + 1]; // allocate one extra element to insert/remove
            for (int i = 0; i < ds_size; i++){
                array[i] = fill_element<element>();
            }
        }
};


template <typename element> double run_benchmark_array(element array[], size_t ds_size, double time_goal, unsigned long &opcount){
    element store                 = fill_element<element>();
    std::chrono::time_point start = Clock::now();
    duration<double> elapsed      = duration_cast<duration<double>>(Clock::now() - start);

    bool running  = true;
    int op        = 0; // which operation to do
    int i         = 0; // where in the array

    while(running){
        switch (operations[op % 100]){
            case READ:
                store = array[i];
                opcount++;
                // std::cout << i << "Operation " << opcount << " is: READ" << std::endl;
                break;
            case WRITE:
                array[i] = store;
                opcount++;
                // std::cout << i << "Operation " << opcount << " is: WRITE" << std::endl;
                break;
            case INSERT:
                for (int j=i; j<ds_size; j++){
                    array[j+1] = array[j];
                }
                array[i] = store;
                opcount++;
                // std::cout << i << "Operation " << opcount << " is: INSERT" << std::endl;
                break;
            case DELETE:
                for (int j=i; j<ds_size; j++){
                    array[j] = array[j+1];
                }
                opcount++;
                // std::cout << i << "Operation " << opcount << " is: DELETE" << std::endl;
                break;
        }
        op++;
        i = (i + 1) % ds_size;
        elapsed = duration_cast<duration<double>>(Clock::now() - start);
        if(elapsed > duration<double>(time_goal)){
            std::cout << i << elapsed.count() << " Seconds elapsed..." << std::endl;
            running = false;
        }
    }
    std::cout << i << "Using a random element to ensure compiler doesn't throw values away" << std::endl;
    float* data = array[rand() % ds_size].data;
    data[rand() % (sizeof(data)/sizeof(float))] += drand48();

    return elapsed.count();
};