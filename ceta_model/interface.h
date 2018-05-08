#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct gbdt_feature {
   unsigned int idx;
   double value;
};

double gbdt_scoring(struct gbdt_feature feas[],unsigned int len,double *res);

#ifdef __cplusplus    
}
#endif
