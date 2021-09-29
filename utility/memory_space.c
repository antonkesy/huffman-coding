#include "memory_space.h"

void add_bits(MemorySpace *ms, uint64_t bits)
{
    ms->bytes += bits / 8;
    uint8_t rest = (bits % 8) + ms->rest_bits;
    ms->bytes += rest / 8;
    ms->rest_bits = rest % 8;
}

void sub_bits(MemorySpace *ms, uint64_t bits)
{
    ms->bytes -= bits / 8;
    uint8_t rest = (bits % 8) + ms->rest_bits;
    ms->bytes -= rest / 8;
    ms->rest_bits = rest % 8;
}

bool is_empty_memory_space(MemorySpace *ms)
{
    return ms->bytes > 0 || ms->rest_bits > 0;
}
