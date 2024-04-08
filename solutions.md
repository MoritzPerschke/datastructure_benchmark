# Sheet 9

# A)

I have attached the full code, but the main parts of my benchmark look like this:
To space out the operations:

```C
void space_operations(int ratio_re_wr, int ratio_in_de){
    
    bool read   = true;
    bool insert = true;
    int n       = 0;
    int i       = 0;

    if (ratio_re_wr < ratio_in_de){ 

        ratio_re_wr != 0 ? n = (ratio_in_de / ratio_re_wr) + 1 : n = 100; // in case one of the values is 0
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
        // similar to case above
    }
    else{
        // similar to case above
    }
}
```

There is an enum with all the operations, and an array of size 100 to define which operations to be done.
The array is of a fixed size and iterated over using `%`.

I also defined the elements of different sizes as structs of `float[]`
There is a wrapper class for the array/list to create the array and fill the elements arrays with random values.

The code to run the actual benchmark on an array:

```C
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
                break;
            case WRITE:
                array[i] = store;
                opcount++;
                break;
            case INSERT:
                for (int j=i; j<ds_size; j++){
                    array[j+1] = array[j];
                }
                array[i] = store;
                opcount++;
                break;
            case DELETE:
                for (int j=i; j<ds_size; j++){
                    array[j] = array[j+1];
                }
                opcount++;
                break;
        }
        op++;
        i = (i + 1) % ds_size;
        elapsed = duration_cast<duration<double>>(Clock::now() - start);
        if(elapsed > duration<double>(time_goal)){
            running = false;
        }
    }
    float* data = array[rand() % ds_size].data;
    data[rand() % (sizeof(data)/sizeof(float))] += drand48();

    return elapsed.count();
};
```

Walk through the array of operations and perform the operation at index i for a fixed time.
Also do something with the array to not have the compiler throw away the values.
This function is ran a predefined number of times (3) and the values are averaged.
The time is returned because the loop rarely hits exatly the predefined time goal, so this value can be saved and be taken into consideration if neccessary

## B)

I did run the benchmark on the lcc2 but was unable to get a good amount of values, as my script crashed wednesday morning.
The values i did get are:

```Json
{
    "8": { //element size
        "10000000": { // size of the ds
            "(50, 50)": { // ratio of operations
                "operations": 7547,
                "time": 300.081
            }
        }
    },
    "512": { // element size
        "10000000": { // size of the ds
            "(50, 50)": { // ratio of operations
                "operations": 511,
                "time": 300.455
            }
        }
    }
}
```
After that my python script crashed without printing the rest of the values.
