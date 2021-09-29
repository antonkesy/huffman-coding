#include "../../utility/memory_space.h"
//test == true == success

bool test_add_sub(void)
{
    MemorySpace ms = {0, 0};

    add_bits(&ms, 3);
    add_bits(&ms, 13);
    if (ms.bytes != 2)
    {
        return false;
    }

    sub_bits(&ms, 16);

    if (!is_empty_memory_space(&ms))
    {
        return false;
    }

    return true;
}

bool test_fill_bytes(void)
{
    MemorySpace ms = {0, 0};
    if (get_fill_bytes(&ms) != 0)
    {
        return false;
    }
    add_bits(&ms, 2);
    if (get_fill_bytes(&ms) != 1)
    {
        return false;
    }
    add_bits(&ms, 6);
    if (get_fill_bytes(&ms) != 1)
    {
        return false;
    }
    add_bits(&ms, 6);
    if (get_fill_bytes(&ms) != 2)
    {
        return false;
    }
    return true;
}

bool test_empty(void)
{
    MemorySpace ms = {0, 0};

    if (!is_empty_memory_space(&ms))
    {
        return false;
    }
    add_bits(&ms, 53);
    if (is_empty_memory_space(&ms))
    {
        return false;
    }
    sub_bits(&ms, 53);
    if (!is_empty_memory_space(&ms))
    {
        return false;
    }
    return true;
}

int main(void)
{
    return (test_add_sub() && test_fill_bytes() && test_empty()) ? 0 : 1;
}