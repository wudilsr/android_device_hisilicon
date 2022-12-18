  
1.get chip info 
   executable program: getchipinfo
   source code: sample_ca_getchipinfo.c
   introduction: print chipset information on the debug screen.
   usage: sample_ca_getchipinfo

2.set chip info
   executable program: sample_ca_opensecboot sample_ca_setjtag sample_ca_setmsid sample_ca_setstbsn
   source code: sample_ca_opensecboot.c sample_ca_setjtag.c sample_ca_setmsid.c sample_ca_setstbsn.c
   introduction: Set the chipset information such as opening chipset secure boot, setting jtag protection mode, setting msid and setting stbsn.
   usage:   sample_ca_opensecboot 0
            sample_ca_setjtag 0
            sample_ca_setmsid
            sample_ca_setstbsn

3.encrypt and decrypt demo
   executable program: sample_ca_r2rcrypto
   source code:sample_ca_r2rcrypto.c 
   introduction:this demo show the following functions
                1> encrypting and decrypting data.
   usage: sample_ca_r2rcrypto

4.tsplay demo
   executable program: sample_ca_tsplay
   source code:sample_ca_tsplay.c 
   introduction: this demo show the following functions
                 1> testing the descrambling of the following payload streams:
                        EMI: 0x0020 -- AES CBC : ATIS IIF Default Scrambling Algorithm (IDSA)
                        EMI: 0x0021 -- AES ECB : AES-128 ECB mode. Termination in clear.
                        EMI: 0x0022 -- AES CBC : AES-128 CBC mode. IV modifiable. Termination in clear. (CI+)
                 2> The video data can be output through CVBS YPBPR or HDMI interface.
                 The source code should be changed and recompiled if the contentkey or protecting keys need to change.
   usage: sample_ca_tsplay
          Note that before using this demo, streams should be copied or mounted to the "SCR_STREAM_PATH" specified in "cfg_nagra.h".

5.dvbplay demo
   executable program: sample_ca_dvbplay
   source code:sample_ca_dvbplay.c 
   introduction:this demo show the following functions
                 1> testing the descrambling of the CSA2.0 stream (EMI 0x0000).
                 2> The video data can be output through CVBS YPBPR or HDMI interface.
                 The source code should be changed and recompiled if the contentkey or protecting keys need to change.
   usage: sample_ca_dvbplay
          Note that before using this demo, the parameters should be configured proporly as specified in "cfg_nagra.h".

6.scrplay demo
   executable program: sample_ca_scrplay
   source code:sample_ca_scrplay.c 
   introduction:this demo show the following functions
                 1> testing the decrypting of the following payload and raw streams:
                        EMI: 0x0020 -- AES CBC : ATIS IIF Default Scrambling Algorithm (IDSA)
                        EMI: 0x0021 -- AES ECB : AES-128 ECB mode. Termination in clear.
                        EMI: 0x0022 -- AES CBC : AES-128 CBC mode. IV modifiable. Termination in clear. (CI+)
                        EMI: 0x4022 -- AES CBC : AES-128 in CBC mode. MPEG/DASH standard
                        EMI: 0x4023 -- AES CBC : AES-128 in CBC mode. Apple Live Streaming
                        EMI: 0x4024 -- AES CTR : AES-128 in CTR mode. MPEG/DASH standard.
                 2> testing the encrypting and decrypting of the following raw streams:
                        EMI: 0x4020 -- AES CBC : AES-128 in CBC mode with all bits set to zero IV. Termination in clear.
                        EMI: 0x4021 -- AES ECB : AES-128 in ECB mode. Termination in clear.
                        EMI: 0x4040 -- TDES CBC : TDES keying option 2 in CBC mode with all bits set to zero IV. Termination in clear.
                        EMI: 0x4022 -- TDES ECB : TDES keying option 2 in ECB mode. Termination in clear.
                 3> The video data can be output through CVBS YPBPR or HDMI interface.
                 The source code should be changed if you want to test other streams.
   usage: sample_ca_scrplay
          Note that before using this demo, streams should be copied or mounted to the "SCR_STREAM_PATH" specified in "cfg_nagra.h".

7.pvprogram demo
    executable program: sample_ca_pvprogram_develop sample_ca_pvprogram_product
    source code: sample_ca_pvprogram_develop.c sample_ca_pvprogram_product.c
    introduction: pvprogram_develop demo shows how to program the pv value in develop phase. While pvprogram_product demo shows how to program the pv value in product phase.
                 1> You can set the following values seperately in pvprogram_develop:
                        [0] boot_mode_sel
                        [1] SCS_activation
                        [2] jtag_prt_mode
                        [3] self_boot_disable
                        [4] MSID
                        [5] STB_SN
                 2> You can set the following values in pvprogram_product:
                        [1] Set MSID and STBSN
                        [2] Set other PVs
                    In this demo, 1 is to set MSID and STBSN, while 2 is to set the boot_mode_sel, SCS_activation, jtag_prt_mode and self_boot_disable.
   usage: sample_ca_pvprogram_develop sample_ca_pvprogram_product
          Note that before using this demo, all the values should be set in pvprogram.cfg.
          Besides, all the addresses in pvprogram_develop.c must NOT be changed. Otherwise, the chipset will be damaged!

8.encrypt specific data demo
   executable program: sample_ca_r2rencrypt
   source code:sample_ca_r2rencrypt.c 
   introduction:this demo show the following functions:
                1> encrypting the specific data with TDES ECB.
   usage: sample_ca_r2rencrypt input.txt output.txt
          Note that the input and output files could be .txt or .bin.