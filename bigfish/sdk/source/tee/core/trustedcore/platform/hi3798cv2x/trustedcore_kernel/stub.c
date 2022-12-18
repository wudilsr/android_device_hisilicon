int initCapture(int a)
{
	uart_printf_func("%s ERROR: We SHOULD NOT run this function!!!\n", __func__);
	while(1);
	return -1;
}

int readImage(int a)
{
	uart_printf_func("%s ERROR: We SHOULD NOT run this function!!!\n", __func__);
	while(1);
	return -1;
}

int bsp_efuse_write(const unsigned int* buf,
		  const unsigned int group,
		  const unsigned int size)
{
	return 0;
}

int bsp_efuse_read(unsigned int* buf,
		  const unsigned int group,
		  const unsigned int size)
{
	return 0;
}

int tee_hal_get_dieid(unsigned int * pBuffer, unsigned int u32Length)
{
    return 0;
}

int  hisi_secboot_copy_soc_data(void * dst_addr, const void * src_addr, unsigned int len)
{
    return 0;
}

int hisi_secboot_soc_reset(int soc_type)
{
    return 0;
}
int hisi_secboot_soc_set(int soc_type, int reset_type)
{
    return 0;
}

unsigned int hisi_secboot_soc_verification(int SoC_Type, unsigned int vrlAddress, unsigned int imageAddress, int lock_state)
{
	return 0;
}
void hisi_secboot_get_vrl_addr(unsigned int vrl_address)
{
    return;
}
#if 0
int driver_dep_test(void)
{
        return 0;
}
#endif
int get_vsim_sharemem(unsigned int *addr, unsigned int *size)
{
    uart_printf_func("ERROR!!![%s]:this platform does not support this func\n", __func__);
    return -1;

}
