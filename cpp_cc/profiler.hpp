#pragma once

#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using i8 = int8_t;
using i16 = short;
using i32 = int32_t;
using cstr = const char*;
using b32 = u32;


namespace perf
{
    void profile_init();

    void profile_clear();

    void profile_report(cstr report_label = 0);
}


namespace perf
{
    class Profile
    {
    public:
        
        Profile(cstr label);

        ~Profile();

        int profile_id = 0;

    
    private:

        u64 cpu_start = 0;
        u64 cpu_end = 0;
    };

}


//#define PROFILE_BLOCK(label) perf::Profile profile_block(label);

//#define PROFILE(func_call, label) [&](){ perf::Profile p(label); return func_call; }();

#define PROFILE(func_call) [&](){ perf::Profile p( #func_call ); return func_call; }();

//#define PROFILE(func, ...) [&](){ perf::Profile p("\""#func"\""); return func(...); }();

#define PROFILE_X(func_call) [&](){ perf::Profile p( "*" #func_call ); return func_call; }();
