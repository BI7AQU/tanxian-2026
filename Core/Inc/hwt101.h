#ifndef __HWT101_H
#define __HWT101_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "wit_c_sdk.h"

    typedef struct
    {
        float pitch;
        float roll;
        float yaw;
        float angularx;
        float angulary;
        float angularz;
    } imu_TypeDef;

    void get_imu_data(void);

    extern imu_TypeDef imu;
    extern uint8_t ucRegIndex;

#ifdef __cplusplus
}
#endif

#endif /* __HWT101_H */

