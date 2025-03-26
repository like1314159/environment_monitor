#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "jw01_co2.h"
#include "max4466_noise.h"
#include "mq4_gas.h"
#include "onenet_upload.h"

int main() {
    printf("环境监测系统启动...\n");
    
    // 初始化各模块
    if (mcp3008_init() < 0 || jw01_init() < 0) {
        fprintf(stderr, "硬件初始化失败\n");
        goto cleanup;
    }
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    // 主循环
    while (1) {
        int co2 = jw01_read_co2();
        float noise = max4466_read_noise();
        float gas = mq4_read_gas();
        
        printf("CO2: %dppm, 噪声: %.1fdB, 可燃气体: %.1fppm\n", co2, noise, gas);
        
        if (co2 > 0) {
            if (onenet_upload(co2, noise, gas) != 0) {
                fprintf(stderr, "数据上传失败\n");
            }
        }
        
        sleep(10); // 10秒采集周期
    }

cleanup:
    jw01_cleanup();
    onenet_global_cleanup();
    return 0;
}