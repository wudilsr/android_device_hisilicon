#ifndef SRE_PM_H
#define SRE_PM_H

/* 
 * TOdo
 * Now only support one level suspend/resume
 * Maybe we need add the level argument for 
 * suspend/resume callback to pass the level
 */
struct sre_pm_ops {
    char *dev_name;
/* Return 0 if suspend success, otherwise error number */
    int (*suspend)(void);
/* Return 0 if resume success, otherwise error number */
    int (*resume)(void);
};

/* Return 0 if Register success */
int SRE_PM_Register(struct sre_pm_ops *pm);
void SRE_PM_Suspend(void);
void SRE_PM_Resume(void);

#endif
