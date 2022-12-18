Description£º
	sample_loader used to analog trigger upgrade, support OTA, USB, IP mode.
Command format£º
	usage: sample_loader [-t trigger] [-s set] [-g get] [[command] arg].
	command as follows:
 	sample_loader -t                  -- configure loader upgrade parameter and trigger it run.
 	sample_loader -s deviceinfo args  -- configure deviceinfo.
 	sample_loader -s sw               -- configure software.
 	sample_loader -g deviceinfo       -- get and display deviceinfo info.
 	sample_loader -g sw               -- get and display software version info.

Guide£º
	deviceinfo definition:
	AAAAAAAA-BBBBBBBB-CCCCCCCC ....
        AAAAAAAA 	Terminal product vendor authentication number
        BBBBBBBB 	Hardware version
        CCCCCCCC 	Hareware serial num within batch

	Set deviceinfo£º
	#./sample_loader -s deviceinfo 00000003-00000001-1d000021 
	
	Get deviceinfo£º
	#./sample_loader -g deviceinfo
	==================stb info================
	Factory ID              0x0000003
	HW version              0x00000001
	HW serial num           0x1d000021
	Cur software version    0x00000002
	==========================================

	Set current software version£º
	#./sample_loader -s sw
	=============modify software ver==============
	cur software version    0x00000000 ? 2   
	
	Get current software version£º
	#./sample_loader -g sw
	cur software version    0x00000002
	
	Trigger OTA Cable upgrade£º
	# ./sample_loader -t
	> Select upgrade type(0-OTA, 1-IP, 2-USB) ? 0
	> Select signal type(0-CAB, 1-SAT) ? 0
	> Input PID[0] ? 7000
	> Input Frequency(MHz)[0] ? 610
	> Input Symbol rate(KS/s)[0] ? 6875
	> Input Modulation(0-16,1-32,2-64,3-128,4-256Qam)[0] ? 2
	
	=================================
	Upgrade Parameters
	Download Type           : OTA
	Tuner Type              : Cable
	PID                     : 7000
	Frequency               : 610(MHZ)
	Symrate         	: 6875(Kbps)
	Modulation              : 64QAM
	=================================
	
	Trigger OTA DVB-T2 upgrade:
	# ./sample_loader -t
	> Select upgrade type(0-OTA, 1-IP, 2-USB) ? 0
	> Select signal type(0-CAB, 1-SAT, 2-DVB_T, 3-DVB_T2) ? 3
	> Input PID[7000] ? 7000
	> Input Frequency(KHz)[177500] ? 177500
	> Input BandWidth(MHz)[7] ? 7
	> Input Modulation(0-16,1-32,2-64,3-128,4-256Qam)[2] ? 2

	=================================
	Upgrade Parameters 
	Download Type    : OTA
	Tuner Type       : DVB_T2
	PID              : 7000
	Frequency        : 177.5(MHZ)
	BandWidth       : 7(MHZ)
	Modulation       : 64QAM
	=================================
	Trigger OTA Satellite upgrade:
	# sample_loader -t
	> Select upgrade type(0-OTA, 2-USB) ? 0
	> Select signal type(0-CAB, 1-SAT) ? 1
	> Input PID[7000] ?
	> Input Frequency(MHz)[4150] ?
	> Input Symbol rate(KS/s)[27500] ?
	> Input Polar(0-Horizontal,1-Vertical, 2-Left hand, 3-Right hand)[0] ?
	> Input LNB Low Frequency(MHZ)[5150] ?
	> Input LNB High Frequency(MHZ)[5750] ?
	> Input LNB Power Typte(0-LNB Power Off, 1-LNB Power On)[0] ?1
	> Input 22K Switch(0-Off, 1-On)[0] ?
	> Input DiSEqC1.1 Port(0-Disable, 1-port1, 2-port2,etc)[0] ?
	> Input DiSEqC1.0 Port(0-Disable, 1-port1, 2-port2,etc)[0] ?

	=================================
	Upgrade Parameters
	Download Type           : OTA
	Tuner Type              : Satellite
	PID                     : 7000
	Frequency               : 4150(MHZ)
	Symrate         : 27500(Kbps)
	Polar                   : Horizontal
	LNB Low Frequency       : 5150(MHZ)
	LNB High Frequency      : 5750(MHZ)
	LNB Power               : Power Off
	22K Switch              : Off
	DiSEqC1.1               : Disable
	DiSEqC1.0               : Disable
	=================================
	
	Trigger IP upgrade£º
	# ./sample_loader -t
	> Select upgrade type(0-OTA, 1-IP, 2-USB) ? 1
	> Select protocol type(0-TFTP, 1-FTP, 2-HTTP) ? 2
	> Select IP type(0-static, 1-dynamic) ? 1
	> Input server IP address[0.0.0.0] ? 10.157.187.10
	> Input server port(default:80) ?
	> Input upgrade file name[] ? ip_update.bin
	
	=================================
	Upgrade Parameters
	Download Type           : IP
	Protocol Type           : HTTP
	IP Type                 : dynamic
	server ip               : 10.157.187.10
	server port             : 80
	Upgrade file name       : ip_update.bin
	=================================
	
	Trigger USB upgrade£º
	# ./sample_loader -t
	> Select upgrade type(0-OTA, 1-IP, 2-USB) ? 2
	> specify upgrade file name[] ? usb_update.bin
	
	=================================
	Upgrade Parameters
	Download Type           : USB
	Upgrade file name       : usb_update.bin
	=================================



	
	
	
