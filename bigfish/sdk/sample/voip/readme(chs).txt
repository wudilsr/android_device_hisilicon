���ܣ�
     ��ʾvoip�������ܡ�
     
������
     ʹ��sampleǰ����Ҫȷ������voip���������
     Android�汾��
       1)��Ҫ�򿪶�ӦSDK�����ļ���CFG_HI_VOIP_SUPPORT��,�ر�������ϵͳ��
       2)��Ҫ��ϵͳ�����ű�������� insmod /system/lib/modules/voip_hme.ko
                                 insmod /system/lib/modules/hi_aud_adp.ko
�÷���

���ڴ�ALSA���ܣ�
     1)��LD_LIBRARY_PATH����������ALSA��������·��/usr/share/bluetooth/lib/
     	 export LD_LIBRARY_PATH="/usr/share/bluetooth/lib/:$LD_LIBRARY_PATH"

     2)ִ��./sample_voip para 
       	 para : ����ѡ��0--Normal,1--Play Announcement
            	 Normal : ����������Խӣ����Ի���ͨ�����ܡ�
            	 Play Announcement : �����ļ����˲��ţ��ʺ�ȷ����Ƶ�豸�Ƿ���������

       ʾ����./sample_voip 1, ���������ļ����˲��ŵ������Ĺ��ܡ�

     3) ������ʾ�������� Source IP(����), Dest IP(Զ��)����ʽ192.168.1.1��
     
     4) ������ʾ�������������豸������豸�ı�ţ��� 0 0��
        
     5) �����а�����ʾ������Ӧ�ַ���sample����ֱ�ִ�����¶�����
        'q' : �˳�voip sample����
        'r' : ������һ�� ����/���� VOIPͨ�� ѭ�����ԡ�
        's' : ѡ����Ƶ�豸��   
        
����û�д�ALSA���ܣ�

     1)ִ��./sample_voip para1 para2 
       	 para1 : ��Ƶ�豸ѡ��, 0--SIO(SLIC/ACI31),1--BLUETOOTH,2--USB MIC+HIAO 3--USB PHONE,4--SOUND CARD
       	 para2 : ����ѡ��0--Normal,1--Play Announcement
            	 Normal : ����������Խӣ����Ի���ͨ�����ܡ�
            	 Play Announcement : �����ļ����˲��ţ��ʺ�ȷ����Ƶ�豸�Ƿ���������

       ʾ����./sample_voip 1 1, ���������ļ����˲��ŵ����������Ĺ��ܡ�

     2) ������ʾ�������� Source IP(����), Dest IP(Զ��)����ʽ192.168.1.1��
        
     3) �����а�����ʾ������Ӧ�ַ���sample����ֱ�ִ�����¶�����
        'q' : �˳�voip sample����
        'r' : ������һ�� ����/���� VOIPͨ�� ѭ�����ԡ�
        's' : ѡ����Ƶ�豸��        

ע�⣺
    1�� ��sampleʹ��Ĭ�ϲ�����ʾvoip�Ļ������ܣ���Ҫ�޸�voip��Ĭ�ϲ�������������������á�

    2�� �ɸ����Լ�����Ҫ������������²�����Ĭ�����ã�

	static HI_U8   u8SrcIp[4] = {10,85,180,91};  // Source IP
	static HI_U8   u8DstIp[4] = {10,85,180,95};  // Dest IP
	static HI_U16  u16VoipSrcPort = 8100;        // Voip source port
	static HI_U16  u16VoipDstPort = 8100;        // Voip dest port
	static HI_CHAR cFileName[64]="/mnt/play/love1999.wav";  // The default audio file for play announcement .

    3�� �����˺�Զ�˵�IP��ַ�Ͷ˿ں�����Ϊ��ͬ����������㽫�Զ������������Ƶ���ݣ������ڲ��Գ������շ����VOIPģ�鼰��Ƶ�豸�����Ƿ�������

    4�� ��sampleĬ��ʹ�õ�SIO��Ƶ�豸Ϊ�绰��(SLIC), ��Ҫ����Ϊʹ�� ������MIC��ʽ(ACI31)���������Ӧ�۰塣
    
    	1) ������Ҫ֧��slicģʽ����sample\common\hi_adp_mpi.h�ļ������Ķ���
	   #define SLIC_AUDIO_DEVICE_ENABLE
	2) ������Ҫ֧��mic�Ͷ���ģʽ���򿪸�λ�õĶ���
	   #define TLV320_AUDIO_DEVICE_ENABLE
	
	ע�⣺
          1) Slicģʽ ��mic/����ģʽ ֻ�ܶ�ѡһ��������ͬʱ֧�֣����Ķ�������ɾ��sample\voipĿ¼�µ�ִ���ļ�sample_voip�ٱ��롣
          2) ��Ҫ��������SLIC�豸�Ƿ���������ִ��aiao sample������Ƶ���ع��ܣ����Ż���˵����������Ͳ�����Լ�˵����������
    
    