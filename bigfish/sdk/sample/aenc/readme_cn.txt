1��sample_aenc
��������: չʾaac���빦�ܣ��ϲ�Ӧ���ṩ��Ƶ�����룩
�����ʽ: ./sample_aenc infileName inChannel insamplerate outfileName aac outsamplerate
����˵����infileName    �������Դ�ļ����ƣ�pcm/wav��ʽ��
          inChannel     ����ͨ��������֧��1��2ͨ������ 
          insamplerate  ��������� ����������ʷ�Χ��8000-192000�� 
          outfileName   ��������ݱ�����ļ�����
          outsamplerate ��������ʣ���������ʷ�Χ��16000-48000��
��    ��: ./sample_aenc ./boys_48kHz_stereo_16.wav 2 48000 ./boys.aac aac 48000
ע�������Ҫָ���������Դͨ�����Ͳ����ʣ�����λ���֧��16bit

2��sample_aenc_track
��������: չʾaac���빦�ܣ�aenc��track�İ󶨣�
�����ʽ: ./sample_aenc_track infile intype outfile outtype
����˵����infile    �������Դ�ļ�����
          intype    �������Դ����
          outfile   ��������ݱ�����ļ�����
          outtype   ����󱣴���ļ�����      
��    ��: ./sample_aenc_track ./qgw.mp3 mp3 ./qgw.aac aac
ע�������֧���������Դ����aac/mp3/dts/dra/mlp/pcm/ddp(ac3/eac3)