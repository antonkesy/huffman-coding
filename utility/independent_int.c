#include <stdlib.h>
#include <stddef.h>
#include "independent_int.h"

void *fill_iuint_x(const void *in, const size_t size_of_iuint)
{
    void *return_value = calloc(size_of_iuint, 1);
    if (return_value != NULL)
    {
        for (size_t i = 0U; i < size_of_iuint; ++i)
        {
            ((uint8_t *) return_value)[i] = ((uint8_t *) in)[
#ifdef BIG_ENDIAN_II_H
                    size_of_iuint - i - 1
#else
                    i
#endif
            ];
        }
    }
    return return_value;
}

void *get_iuint_x_value(const void *iuint_in, const size_t size_of_iuint)
{
    void *return_value = calloc(size_of_iuint, 1);
    if (return_value != NULL)
    {
        for (size_t i = 0U; i < size_of_iuint; ++i)
        {
            ((uint8_t *) return_value)[i] = ((uint8_t *) iuint_in)[
#ifdef BIG_ENDIAN_II_H
                    size_of_iuint - i - 1
#else
                    i
#endif
            ];
        }
    }
    return return_value;
}

iuint_16_t *fill_iuint_16(const uint16_t *in)
{
    return (iuint_16_t *) fill_iuint_x(in, sizeof(iuint_16_t));
}

uint16_t *get_iuint_16_value(const iuint_16_t *in)
{
    return (uint16_t *) get_iuint_x_value(in, sizeof(iuint_16_t));
}

iuint_32_t *fill_iuint_32(const uint32_t *in)
{
    return (iuint_32_t *) fill_iuint_x(in, sizeof(iuint_32_t));
}

uint32_t *get_iuint_32_value(const iuint_32_t *in)
{
    return (uint32_t *) get_iuint_x_value(in, sizeof(iuint_32_t));
}

iuint_64_t *fill_iuint_64(const uint64_t *in)
{
    return (iuint_64_t *) fill_iuint_x(in, sizeof(iuint_64_t));
}

uint64_t *get_iuint_64_value(const iuint_64_t *in)
{
    return (uint64_t *) get_iuint_x_value(in, sizeof(iuint_64_t));
}