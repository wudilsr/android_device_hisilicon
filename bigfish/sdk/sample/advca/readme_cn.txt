1.��ȡchipid
   ����������Ļ�ϴ�ӡChipid����"chip id:xxxxxxx"��
   Դ�ļ���sample_ca_getchipid.c
   �÷���./sample_ca_getchipid

2.����jtag����ģʽ
	����: ����jtag�Ĺ���ģʽ��
	Դ�ļ�: sample_ca_setjtag.c
	�÷�: ./sample_ca_setjtagmode mode[0|1|2]
          mode:0-Opened 1-Password Protected 2-Closed

3.�򿪰�ȫ����
   �������򿪰�ȫ������
   Դ�ļ���sample_ca_opensecboot.c
   �÷���./sample_ca_opensecboot
          
4.ts������
   ��demo�����¹��ܣ�
         1> ��������CW����ܵ�CWPK��оƬ�ڲ�
         2> ������ŵ�ts���������ʾ
         ��Ƶ���ݿ�ͨ��CVBS YPBPR��HDMI�ӿ������
         ������Ҫ����CW��CWPK�����޸Ĵ����ж�Ӧ�ĵ�CW��CWPK���ر��뼴�ɡ�
   Դ�ļ�:sample_ca_tsplay.c 
   �÷�: ./sample_ca_tsplay tsfile cwtype[0|1]
          cwtype: 0-ClearCw 1-EncrytedCw
          ����ж����Ŀ����ͨ����Ŀ��ָ��Ҫ���ŵĽ�Ŀ��

5.DVB����
   ����:��demo�ɰ������¹���
                1>��ȡchipid
                2>��Ƶ
                3>�������ĵ�CW����������CW������CWPK��оƬ
                4>ָ����ƵPID����ƵPID���Ž�Ŀ
                5>ָ����Ŀ�Ų��Ž�Ŀ
   Դ�ļ�:sample_ca_dvbplay.c
   �÷�: ./sample_ca_dvbplay freq
                    
6.���ݼ�/����
   ����:ʹ��keyladder�ӽ�������
   Դ�ļ�:sample_ca_crypto.c
   �÷�: ./sample_ca_crypto
   
7.PVR¼��
   ����:��ʾ�߰�PVR¼��
   Դ����:sample_ca_pvr_rec.c
   �÷�: ./sample_ca_pvrrec pvrrec file_path freq [SymbolRate] [qamtype] [vo_format]
      file_path: ��ָ����Ҫ¼�Ƶ��ļ����֣���ָ��·������demo���Զ�����¼���ļ���
      SymbolRate, qamtype, �� vo_format Ϊ��ѡ�Ĭ�ϵ�SymbolRate��6875��
      qamtype��ֵ��16, 32, 64, 128, 256, or 512��Ĭ��Ϊ 64QAM��
      vo_format��ֵ��1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��Ĭ����1080i_60��
      
      ��ʾ�� ���д�demoʱ��������
      1. 'r' ����ֹ��ǰ¼�ƣ���������¼�ơ�
      2. 'f' ������һ�����ڲ��Ե�fingerprint��
      2. 'm' ������һ�����Եĳ��ϼ���
      
8.PVR����
   ����:��demo��ʾ�߰�pvr���š�
   Դ����:sample_ca_pvr_play.c 
   �÷�: ./sample_ca_pvrplay file_name [vo_format]
      vo_formatֵΪ1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��Ĭ����1080i_60��

9.PVRʱ��
   ����:��demo��ʾ�߰�pvr���š�
   Դ����:sample_ca_pvr_timeshift.c��
   �÷�: ./sample_ca_pvrtimeshift file_path freq [SymbolRate] [qamtype] [vo_format]
       ��ϸ�÷���ο���ͨPVRʱ�ơ�

10.����STBSN
   ����: ����STBSN��
   Դ����:sample_ca_setSTBSN.c 
   �÷�: ./sample_ca_stbSTBSN

11.����MarketID
   ����: ����MarketID��
   Դ����:sample_ca_setMarketID.c 
   �÷�: ./sample_ca_MarketID

12.SWPK Keyladder��ʾ
   ����: ��ʾSWPK keyladder��ʹ�á�
   Դ����:sample_ca_swpk_keyladder.c��
   �÷�: ./sample_ca_swpk_keyladder

13.SWPK����
   ����: ��ʾ��������SWPK, ������MV200оƬ��
   Դ����:sample_ca_swpk.c��
   �÷�: ./sample_ca_swpk

14.CMAC����
   ����: ��ʾCMAC�����÷���
   Դ����:sample_ca_aes_cbc_mac.c
   �÷�: ./sample_ca_aes_cbc_mac