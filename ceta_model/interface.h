#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct gbdt_feature {
   unsigned int idx;
   double value;
};

int GbdtInit(char* model_dir,char * log_dir);
int GbdtScoring(struct gbdt_feature feas[] ,int feasize,const char *model_name, double *res);

#ifdef __cplusplus    
}
#endif
