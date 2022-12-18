#ifndef __TEE_BITMAP_H
#define __TEE_BITMAP_H

static inline signed int get_valid_bit(unsigned char* bitmap, uint32_t bit_max)
{
    unsigned int index1, index2;
    signed int valid_bit = -1;

    for(index1 = 0; index1 < (bit_max>>3); index1 ++){
        if(bitmap[index1] != 0xff){
            for(index2 = 0; index2 < 8; index2 ++){
                if(!(bitmap[index1] & (0x1 << index2))){
                    valid_bit = index1*8 + index2;
                    break;
                }
            }
            if(valid_bit != -1)
                break;
        }
    }

    return valid_bit;
}

static inline unsigned char is_bit_seted(unsigned char* bitmap, uint32_t bit_max, unsigned int bit)
{
    unsigned char *set_map = &(bitmap[bit >> 3]);
    unsigned char set_bit = bit%8;

    if(bit >= bit_max)
        return 0;

    return ((*set_map) & (0x1<<set_bit)) ? 1 : 0;
}

static inline void set_bitmap(unsigned char* bitmap, uint32_t bit_max, unsigned int bit)
{
    unsigned char *set_map = &(bitmap[bit >> 3]);
    unsigned char set_bit = bit%8;

    if(bit < bit_max)
        *set_map = (*set_map) | (0x1<<set_bit);
}

static inline void clear_bitmap(unsigned char* bitmap, uint32_t bit_max, unsigned int bit)
{
    unsigned char *set_map = &(bitmap[bit >> 3]);
    unsigned char set_bit = bit%8;

    if(bit < bit_max)
        *set_map = (*set_map) & (~(uint8_t)(0x1<<set_bit));
}

#endif