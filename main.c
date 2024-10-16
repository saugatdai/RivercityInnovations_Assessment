#include <stdio.h>


#include "sensor.h"

int main(){
    uint8_t status;
    SHTC3_DATA sensorData;

    printf("Checking Communication with SHTC3 Sensor\n");
    status = SHTC3_CheckCommunication();
    if(status==0){
        printf("\nCommunication with device SHTC3 successful!\n\n");
    }else{
        return 1;
    }
    
    while(1){
        status = SHTC3_Wakeup();
        if(status == 1){
            return 1;
        }
        printf("SHTC3 Wake Up Successful\n\n");
        
        status = SHTC3_ReadSensorData(&sensorData);
        if(status == 1){
            printf("\nError Reading Sensor Data SHTC3\n");
            return 1;
        }
        
        printf("\nTemperature: %.1f \u00B0C\n", sensorData.temp_C);
        printf("Humidity: %.1f %%\n\n", sensorData.hum_RH);
        
        status = SHTC3_Sleep();
        if(status == 1){
            return 1;
        }
        printf("SHTC3 in sleep mode\n\n");
        sleep(10);
    }
        
        
    return 0;
}