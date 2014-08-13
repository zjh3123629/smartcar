#include "encoder.h"

// 使用脉冲累加器
// PTA19
static void init_left_encoder(void)
{
	LPTMR_InitTypeDef lptmr_init_struct;
	bzero(&lptmr_init_struct, sizeof(lptmr_init_struct));

	lptmr_init_struct.LPTMR_Mode = LPTMR_MODE_PLACC;
	lptmr_init_struct.LPTMR_PluseAccInput = LPTMR_ALT1;
	lptmr_init_struct.LPTMR_Isr = NULL;

	LPLD_LPTMR_Init(lptmr_init_struct); 
}

// 使用正交解码器
// PTB18, PTB19
static void init_right_encoder(void)
{
	// FTM2用于正交解码功能
	FTM_InitTypeDef ftm_init_struct;
	bzero(&ftm_init_struct, sizeof(ftm_init_struct));
	
	//配置正交解码功能参数
	ftm_init_struct.FTM_Ftmx = FTM2;
	ftm_init_struct.FTM_Mode = FTM_MODE_QD;
	ftm_init_struct.FTM_QdMode = QD_MODE_PHAB;
	//初始化FTM
	LPLD_FTM_Init(ftm_init_struct);

	LPLD_FTM_QD_Enable(FTM2, PTB18, PTB19);
}

void init_encoder(void)
{
	init_left_encoder();
	init_right_encoder();
}
