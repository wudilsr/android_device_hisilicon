#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/version.h>
#include <sound/soc.h>
#include <sound/pcm_params.h>

#include "alsa_aiao_comm.h"


static int hisi_i2s_set_dai_fmt(struct snd_soc_dai *cpu_dai,
				   unsigned int fmt)
{
	return 0;
}
static int hisi_i2s_dai_set_clkdiv(struct snd_soc_dai *cpu_dai,
				int div_id, int div)
{
	return 0;
}

static const struct snd_soc_dai_ops hisi_i2s_dai_ops = {
	.startup	= NULL,
	.shutdown	= NULL,
	.prepare	= NULL,
	.trigger	= NULL,
	.hw_params	= NULL,
	.set_fmt	= hisi_i2s_set_dai_fmt,
	.set_clkdiv	= hisi_i2s_dai_set_clkdiv,
};

static struct snd_soc_dai_driver hisi_i2s_dai = {
	.playback = {
		.channels_min = 2,
		.channels_max = 2,
		.rates = AIAO_RATES,
		.formats = SNDRV_PCM_FMTBIT_S16_LE,},
	.capture = {
		.channels_min = 2,
		.channels_max = 2,
		.rates = AI_RATES,
		.formats = SNDRV_PCM_FMTBIT_S16_LE,},
	.ops = &hisi_i2s_dai_ops,

};
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
	//Nothing
#else
static const struct snd_soc_component_driver hisi_i2s_component = {
	.name		= "HISI-i2s",
};
#endif

static __init int hisi_i2s_dev_probe(struct platform_device *pdev)
{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
	return snd_soc_register_dai(&pdev->dev, &hisi_i2s_dai);
#else
	return snd_soc_register_component(&pdev->dev, &hisi_i2s_component,
					 &hisi_i2s_dai, 1);
#endif	
}

static __exit int hisi_i2s_dev_remove(struct platform_device *pdev)
{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
	snd_soc_unregister_dai(&pdev->dev);
#else	
	snd_soc_unregister_component(&pdev->dev);
#endif
	return 0;
}

static struct platform_driver hisi_i2s_driver = {
    	.driver = {
		.name = "hisi-i2s",
		.owner = THIS_MODULE,
	},
	.probe  = hisi_i2s_dev_probe,
	.remove = __exit_p(hisi_i2s_dev_remove),
};

static struct platform_device *hisi_i2s_device;

int hiaudio_i2s_init(void)
{
    int ret = 0;
    //register device
    hisi_i2s_device = platform_device_alloc("hisi-i2s", -1);
    if (!hisi_i2s_device) {
    	//printk(KERN_ERR "hisi-i2s SoC Cpu Dai  device: Unable to register\n");
    	return -ENOMEM;
    }
    
    ret = platform_device_add(hisi_i2s_device);
    if (ret) {
    	//printk(KERN_ERR "hisi-i2s SoC Cpu Dai  device: Unable to add\n");
    	platform_device_put(hisi_i2s_device);
       return ret;
    }

    //register drvier
    return platform_driver_register(&hisi_i2s_driver);
}

void hiaudio_i2s_deinit(void)
{
    platform_device_unregister(hisi_i2s_device);
    platform_driver_unregister(&hisi_i2s_driver);
}

