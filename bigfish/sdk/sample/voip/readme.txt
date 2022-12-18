Function:
     To demonstrate the basic functions of the Voice Over Internet Protocol (VoIP) module.

Depend:  
     Before run sample_voip, should insmod voip drivers.
     For Android:
        1)Enable CFG_HI_VOIP_SUPPORT of SDK config file,and recompile the whole system.
        2)add insmod /system/lib/modules/voip_hme.ko insmod /system/lib/modules/hi_aud_adp.ko to system init script.

Instruction:

for opening alsa function:

     1)Add alsa and bluetooth libraries path(/usr/share/bluetooth/lib/) into LD_LIBRARY_PATH
     	 export LD_LIBRARY_PATH="/usr/share/bluetooth/lib/:$LD_LIBRARY_PATH"

     2) Run ./sample_voip para. 
         para: function select. 0--normal; 1--play announcement
                 Normal: Tests basic voice function when two boards are connected.
                 Play announcement: Outputs audio to the local audio device to check whether the audio device works properly.

       Sample: ./sample_voip 1. This sample is used to test the function of listening to the audio played on the local audio device.

     3) Enter the source IP address (local end) and destination IP address (remote end) in sequence, for example, 192.168.1.1.
     
     4) Enter the input and output device number.
        
     5) Enter the following characters according to instructions:
        Enter q to end the VoIP sample.
        Enter r to conduct the next cyclic test of creating and destroying a VoIP channel.
        Enter s to select the audio device.

for doing not open alsa function:

     1) Run ./sample_voip para1 para2. 
       	 para1: audio device select. 0--sonic input output (SIO) (SLIC/ACI31); 1--Bluetooth; 2--USB MIC+HiAO 3--USB PHONE,4--SOUND CARD
       	 para2: function select. 0--normal; 1--play announcement
            	 Normal: Tests basic voice function when two boards are connected.
            	 Play announcement: Outputs audio to the local audio device to check whether the audio device works properly.

       Sample: ./sample_voip 1 1. This sample is used to test the function of listening to the audio played on the local audio device using the Bluetooth headset.

     2) Enter the source IP address (local end) and destination IP address (remote end) in sequence, for example, 192.168.1.1.
        
     3) Enter the following characters according to instructions:
        Enter q to end the VoIP sample.
        Enter r to conduct the next cyclic test of creating and destroying a VoIP channel.
	Enter s to select the audio device.
        

Note:
    1. This sample demonstrates the basic functions of VoIP using the default parameters. You can change the parameter values using related software.

    2. You can change default parameter values as required.

	static HI_U8   u8SrcIp[4] = {10,85,180,91};  // Source IP address
	static HI_U8   u8DstIp[4] = {10,85,180,95};  // Destination IP address
	static HI_U16  u16VoipSrcPort = 8100;        // VoIP source port
	static HI_U16  u16VoipDstPort = 8100;        // VoIP destination port
	static HI_CHAR cFileName[64]="/mnt/play/love1999.wav";  // The default audio file for playing announcement

    3. If the IP addresses and port IDs of the local end and remote end are the same, the network adaptation layer automatically loops the input audio data. This mode is used to test whether the VoIP module and audio device work properly. However, this mode cannot be used to test the function of receiving and transmitting data over Internet.

    4. In this sample, the SIO audio device serves as a telephone (SLIC) by default. To change the mode to headset+MIC (ACI31), change the corresponding daughter board.
    
    	1) To support the SLIC mode, enable the definition in the top of hi_adp_mpi.h in sample\common\:
	   #define SLIC_AUDIO_DEVICE_ENABLE
	2) To support the headset+MIC mode, enable the following definition:
	   #define TLV320_AUDIO_DEVICE_ENABLE
	
        3) The SLIC mode and headset+MIC mode cannot be supported at the same time. If the corresponding definition is changed, you must delete the sample_voip file in sample\voip, and compile the VoIP sample again.

        4) To test whether the SLIC device works properly, run the audio input/audio output (AIAO) sample in sample\aiao. This sample provides the audio loopback function. When you talk to the headset, you can hear your voice from the earphone.
    
    
