#include "alsa_aiao_proc_func.h"

#ifdef CONFIG_AIAO_ALSA_PROC_SUPPORT
static void hiaudio_ao_proc_read(struct snd_info_entry *entry,
                                    struct snd_info_buffer *buffer)
{

    struct hiaudio_data *had = entry->private_data;

     snd_iprintf(buffer,
                        " dma_index=0x%x, irq_num= %d, int_cnt(discard/total)=0x%x/0x%x\n",
                         had->dma_index, had->irq_num, had->isr_discard_cnt, had->isr_total_cnt
                         );
      snd_iprintf(buffer,
                        " aiao_isr_num=0x%x, local_isr_num=0x%x\n",
                         had->aiao_isr_num, had->local_isr_num
                         );    
     snd_iprintf(buffer,
                        " runtime_appl_ptr=0x%x, runtime_appl_offset=0x%x\n",
                         had->runtime_appl_ptr , had->runtime_appl_offset
                         );
      snd_iprintf(buffer,
                        " aoe_appl_ptr=0x%x, aoe_updatewptr_offset=0x%x\n",
                         had->aoe_write_ptr, had->aoe_updatewptr_offset
                         );

     snd_iprintf(buffer,
                        " aoe_write_offset=0x%x, hw_readpos=0x%x, aoe_readpos=0x%x,\n",
                         had->aoe_write_offset, had->hw_readpos, had->aoe_readpos
                         );
      snd_iprintf(buffer,
                        " ack_cnt=0x%x, last_pos=0x%x, pointer_frame_offset=0x%x\n",
                         had->ack_cnt, had->last_pos, had->pointer_frame_offset
                         );
#ifdef CONFIG_PM
 	 snd_iprintf(buffer, " -----pm-----\n");						   
     snd_iprintf(buffer,
                        " pm_aoe_readpos=0x%x,pm_aoe_writepos=0x%x\n",
                         had->pm_aoe_readpos, had->pm_aoe_writepos
                         );    
	snd_iprintf(buffer,
					   " suspend_state=0x%x,suspend_isradjust=0x%x\n",
						had->suspend_state, had->suspend_isradjust
                         );                         
#endif
}

int hiaudio_ao_proc_init(void * card, const char * name, struct hiaudio_data *had)
{
    int ret;
    if((NULL == card) || (NULL == name) || (NULL == had))
    {
        return -EINVAL;
    }
    ret = snd_card_proc_new((struct snd_card *)card, name, &had->entry);
    if(ret)
    {
        //TO DO    
    }
    snd_info_set_text_ops(had->entry, had, hiaudio_ao_proc_read);    
    
    return 0;
}

#ifdef HI_ALSA_AI_SUPPORT
static void hiaudio_ai_proc_read(struct snd_info_entry *entry,
                                    struct snd_info_buffer *buffer)
{
    struct hiaudio_data *had = entry->private_data;
     snd_iprintf(buffer,
                        "ai_handle=%d,dma isr cnt =%d\n",
                         had->ai_handle, had->isr_total_cnt_c
                         );
    snd_iprintf(buffer,
                       "  dma writepos=%d,dma read pos=%d\n",
                          had->ai_writepos,had->ai_readpos
                        );

}
int hiaudio_ai_proc_init(void * card, const char * name, struct hiaudio_data *had)
{
    int ret;
    if((NULL == card) || (NULL == name) || (NULL == had))
    {
        return -EINVAL;
    }
    ret = snd_card_proc_new((struct snd_card *)card, name, &had->entry);
    if(ret)
    {
    }
    snd_info_set_text_ops(had->entry, had, hiaudio_ai_proc_read);    
    return 0;
}
#endif
void hiaudio_proc_cleanup(void)
{
    //TODO
}
#endif




