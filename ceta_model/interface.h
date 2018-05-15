#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct libconf{
    char* model_dir;
    char* log_dir;
    int   feature_debug_rate;//e.g. 10 means 10%
    int   model_buffer;//seconds,should be 300s
};
    
struct gbdt_feature {
   unsigned int idx;
   double value;
};

int GbdtInit(struct libconf conf);
int GbdtScoring(struct gbdt_feature feas[] ,int feasize,const char *model_name, double *res);

#ifdef __cplusplus    
}
#endif
