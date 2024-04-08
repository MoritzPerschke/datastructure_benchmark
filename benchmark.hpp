#ifndef __BENCHMARK_HEADER
#define __BENCHMARK_HEADER
    #include <array>
    #include <list>
    #include <iostream>
    #include <iterator>
    #include <chrono>

    const char* k = "[+] ";
    const char* e = "[-] ";
    const char* i = "[*] ";

    // https://stackoverflow.com/questions/5521146/what-is-the-best-most-accurate-timer-in-c
    typedef std::chrono::high_resolution_clock Clock;
    using std::chrono::duration;
    using std::chrono::duration_cast;

    enum operation{
        READ,
        WRITE,
        INSERT,
        DELETE
    };

    std::array<operation, 100> operations;

    struct elem8{
        float data[1];
    };

    struct elem512{
        float data[64];
    };

    struct elem8M{
        float data[1000000];
    };

    template<typename element> element fill_element(){
        element el;
        for (int i = 0; i < sizeof(el.data)/sizeof(float); i++){
            el.data[i] = drand48();
        }
        return el;
    }

    void space_operations(int ratio_re_wr, int ratio_in_de);
#endif