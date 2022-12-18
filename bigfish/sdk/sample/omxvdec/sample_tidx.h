
#ifndef SAMPLE_TIDX_H
#define SAMPLE_TIDX_H

#define  PACK_OK            (0)
#define  PACK_ERR           (-1)

// ��.tidx�ļ��ж�ȡ��֡��Ϣ������
#define  MAX_LOAD_TIDX_NUM  (4*1024)    

/*ͼ��֡��Ϣ*/
typedef struct 
{
    int s32FrameNum;
	int s32Frameoffset;
	int s32FrameSize;
	int FrameType;              // frame coding type
	int TopFieldType;           // top field coding type
	int BtmFieldType;           // buttom field coding type
	long FramePts;
    int FrameStructure;         // 0-frame ; 1-fieldpair
    int TopFieldCrc;
    int BtmFieldCrc;
	int s32FrameCrc;
    int NVOPFlag;               // NVOP�䲻����ı�־
    int AlreadyOutPutFlag;      // ֡�Ѿ������־
	
}FRAME_INFO_S;

typedef struct
{
    FILE *fptidxFile;
	FRAME_INFO_S  stFrameInfotidx[MAX_LOAD_TIDX_NUM]; 
    
}STR_CONTEXT_S;

int ReadFrameInfoFromtidx(STR_CONTEXT_S *pstContext);

#endif

