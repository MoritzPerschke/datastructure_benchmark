#include "benchmark_array.hpp"
#include "benchmark_list.hpp"

void space_operations(int ratio_re_wr, int ratio_in_de){
    
    bool read   = true;
    bool insert = true;
    int n       = 0;
    int i       = 0;

    if (ratio_re_wr < ratio_in_de){ 

        ratio_re_wr != 0 ? n = (ratio_in_de / ratio_re_wr) + 1 : n = 100;
        for (int i = 0; i < 100; i++){
            if (i % n == 0){
                operations[i] = read ? READ : WRITE;
                read = !read;
            }
            else{
                operations[i] = insert ? INSERT : DELETE;
                insert = !insert;
            }
        }
    }
    else if(ratio_in_de < ratio_re_wr){

        ratio_in_de != 0 ? n = (ratio_re_wr / ratio_in_de) + 1 : n = 100;
        for (int i = 0; i < 100; i++){
            if (i % n == 0){
                operations[i] = insert ? INSERT : DELETE;
                insert = !insert;
            }
            else{
                operations[i] = read ? READ : WRITE;
                read = !read;
            }
        }
    }
    else{
        for (int i = 0; i < 100; i++){
            n = 2;
            if (i % n == 0){
                operations[i] = insert ? INSERT : DELETE;
                insert = !insert;
            }
            else{
                operations[i] = read ? READ : WRITE;
                read = !read;
            }
        }
    }
}

int main(int argc, char* argv[]){

    int ratio_re_wr = atoi(argv[1]);
    int ratio_in_de = atoi(argv[2]);
    size_t elem_size;
    size_t ds_size;
    std::string ds_type;

    if(argc == 6){
        if(ratio_in_de + ratio_re_wr != 100){
            std::cout << e << "ratios have to add up to 100..." << std::endl <<
            " Read/Write: " << ratio_re_wr << " Insert/Delete: " << ratio_in_de <<
            std::endl << ratio_re_wr + ratio_in_de << std::endl;
            return 1;  
        } 

        elem_size = atoi(argv[3]);
        ds_size   = atoi(argv[4]);
        ds_type   = argv[5];
        
    }
    else{
        std::cout << e << "Usage: ./Benchmark [ratio Read/Write] [ratio Insert/Delete] [size of elements(bytes)] [size of DS] [array/list], exiting..." << std::endl;
        std::cout << ratio_re_wr << " " << ratio_in_de << " " << elem_size << " " << ds_size << " " << ds_type << " " << "total: " << argc << std::endl;
        return 1;
    }

    // create order of operations
    space_operations(ratio_re_wr, ratio_in_de);

    int n                 = 5;
    unsigned long opcount = 0;
    double time_goal      = 300;
    double time           = 0.;

    if (ds_type == "array"){
        std::cout << i << "Data structure is array" << std::endl;
        if (elem_size == 8){
            test_array<elem8> test = test_array<elem8>(ds_size);
            std::cout << i << "DS init done, running benchmark..." << std::endl;
            for(int i = 0; i<n; i++){
                time += run_benchmark_array(test.array, ds_size, time_goal, opcount);
            }
            opcount /= n;
            time /= n;
        }
        else if (elem_size == 512){
            test_array<elem512> test = test_array<elem512>(ds_size);
            std::cout << i << "DS init done, running benchmark..." << std::endl;
            for(int i = 0; i<n; i++){
                time += run_benchmark_array(test.array, ds_size, time_goal, opcount);
            }
            opcount /= n;
            time /= n;
        }
        else if (elem_size == 8000000){
            test_array<elem8M> test = test_array<elem8M>(ds_size);
            std::cout << i << "DS init done, running benchmark..." << std::endl;
            for(int i = 0; i<n; i++){
                time += run_benchmark_array(test.array, ds_size, time_goal, opcount);
            }
            opcount /= n;
            time /= n;
        }
        else{
            std::cout << e << "Element size not supported" << std::endl;
            return 1;
        }
    }
    else if (ds_type == "list"){
        std::cout << i << "Data structure is list" << std::endl;
        if (elem_size == 8){
            test_list<elem8> test = test_list<elem8>(ds_size);
            std::cout << i << "DS init done, running benchmark..." << std::endl;
            for(int i = 0; i < n; i++){
                time += run_benchmark_list(test.list, ds_size, time_goal, opcount);
            }
            opcount /= n;
            time /= n;
        }
        else if (elem_size == 512){
            test_list<elem512> test = test_list<elem512>(ds_size);
            std::cout << i << "DS init done, running benchmark..." << std::endl;
            for(int i = 0; i < n; i++){
                time += run_benchmark_list(test.list, ds_size, time_goal, opcount);
            }
            opcount /= n;
            time /= n;
        }
        else if (elem_size == 8000000){
            test_list<elem512> test = test_list<elem512>(ds_size);
            std::cout << i << "DS init done, running benchmark..." << std::endl;
            for(int i = 0; i < n; i++){
                time += run_benchmark_list(test.list, ds_size, time_goal, opcount);
            }
            opcount /= n;
            time /= n;
        }
        else{
            std::cout << e << "Element size not supported" << std::endl;
            return 1;
        }
    }


    std::cout << k << opcount << " operations completed in " << time << " seconds" << std::endl;
    std::cerr << "{\n    \"operations\":" << opcount << ",\n    \"time\":" << time << "\n}";
    return 0;
}
