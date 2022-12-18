����������
	sample_loader����ģ�ⴥ��loader������֧��OTA��USB��IP��������ʽ��
�����ʽ��
	usage: sample_loader [-t trigger] [-s set] [-g get] [[command] arg].
	command as follows:
 	sample_loader -t                  -- configure loader upgrade parameter and trigger it run.
 	sample_loader -s deviceinfo args  -- configure deviceinfo.
 	sample_loader -s sw               -- configure software.
 	sample_loader -g deviceinfo       -- get and display deviceinfo info.
 	sample_loader -g sw               -- get and display software version info.

ʹ��˵����
	deviceinfo�ľ��嶨��˵�����£�
	AAAAAAAA-BBBBBBBB-CCCCCCCC ....
	AAAAAAAA ���̱��
	BBBBBBBB Ӳ���汾��
	CCCCCCCC ������Ӳ��ϵ�к�
	.... ��չ����
	
	����deviceinfo��	
	#./sample_loader -s deviceinfo 00000003-00000001-1d000021  
	
	�õ�deviceinfo��
	#./sample_loader -g deviceinfo
	==================stb info================
	Factory ID              0x0000003
	HW version              0x00000001
	HW serial num           0x1d000021
	Cur software version    0x00000002
	==========================================

	���õ�ǰ����汾�ţ�
	#./sample_loader -s sw
	=============modify software ver==============
	cur software version    0x00000000 ? 2   
                   
	
	�õ���ǰ����汾�ţ�
	#./sample_loader -g sw
	cur software version    0x00000002
	
	����OTA Cable������
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
	
	����OTA����������
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
	
	����IP������
	# ./sample_loader -t
	> Select upgrade type(0-OTA, 1-IP, 2-USB) ? 1
	> Select protocol type(0-TFTP, 1-FTP, 2-HTTP) ? 0
	> Select IP type(0-static, 1-dynamic) ? 1
	> Input server IP address[0.0.0.0] ? 10.157.187.10
	> Input server port(default:69) ?
	> Input upgrade file name[] ? ip_update.bin
	
	=================================
	Upgrade Parameters
	Download Type           : IP
	Protocol Type           : TFTP
	IP Type                 : dynamic
	server ip               : 10.157.187.10
	server port             : 69
	Upgrade file name       : ip_update.bin
	=================================
	
	����USB������
	# ./sample_loader -t
	> Select upgrade type(0-OTA, 1-IP, 2-USB) ? 2
	> specify upgrade file name[] ? usb_update.bin
	
	=================================
	Upgrade Parameters
	Download Type           : USB
	Upgrade file name       : usb_update.bin
	=================================



	
	
	