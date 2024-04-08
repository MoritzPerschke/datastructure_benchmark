#include "benchmark.hpp"

template <typename element>
class test_list{
    public:
        std::list<element> list;
        test_list(size_t ds_size){
            for (int i = 0; i < ds_size; i++){
                list.emplace_back(fill_element<element>());
            }

        }
};

template<typename element> double run_benchmark_list(std::list<element> list, size_t ds_size, double time_goal, unsigned long &opcount){
    element store                 = fill_element<element>();
    std::chrono::time_point start = Clock::now();
    duration<double> elapsed      = duration_cast<duration<double>>(Clock::now() - start);

    bool running  = true;
    int op        = 0; // which operation to do

    typename std::list<element>::iterator iter = list.begin(); // iterator through the list

    while(running){
        switch (operations[op % 100]){
            case READ:
                store = *iter;
                opcount++;
                // std::cout << i << "Operation " << opcount << " is: READ" << std::endl;
                break;
            case WRITE:
                *iter = store;
                opcount++;
                // std::cout << i << "Operation " << opcount << " is: WRITE" << std::endl;
                break;
            case INSERT:
                list.insert(iter, store);
                opcount++;
                // std::cout << i << "Operation " << opcount << " is: INSERT" << std::endl;
                break;
            case DELETE:
                iter = list.erase(iter);
                opcount++;
                // std::cout << i << "Operation " << opcount << " is: DELETE" << std::endl;
                break;
        }
        op++;
        iter == list.end() ? iter = list.begin() : iter++;

        elapsed = duration_cast<duration<double>>(Clock::now() - start);
        if(elapsed > duration<double>(time_goal)){
            std::cout << elapsed.count() << i << " Seconds elapsed..." << std::endl;
            running = false;
        }
    }

    std::cout << i << "Using a random element to ensure compiler doesn't throw values away" << std::endl;
    float* data = store.data;
    data[rand() % (sizeof(data)/sizeof(float))] += drand48();
    store = *iter;
    data[rand() % (sizeof(data)/sizeof(float))] += drand48();

    return elapsed.count();
}