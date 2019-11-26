#include <FreeRTOS_ARM.h> 
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"
#include "Wire.h"


LSM303C board;
void setup() {

  Serial.begin(57600);
  Wire.begin();
  Wire.setClock(400000L);
  while (!SerialUSB);
  if (board.begin(
        MODE_I2C,
        MAG_DO_40_Hz,
        MAG_FS_16_Ga,
        MAG_BDU_ENABLE,
        MAG_OMXY_HIGH_PERFORMANCE,
        MAG_OMZ_HIGH_PERFORMANCE,
        MAG_MD_CONTINUOUS,
        ACC_FS_2g,
        ACC_BDU_ENABLE,
        ACC_X_ENABLE|ACC_Y_ENABLE|ACC_Z_ENABLE,
        ACC_ODR_100_Hz
      ) != IMU_SUCCESS)
  {
    Serial.println("Failed setup.");
    while (1);
  }

  if (board.checkWhoAmI() != IMU_SUCCESS){
        SerialUSB.println("Failed who am I");
  }
   
  
  xTaskCreate(readMag, "readMag", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  vTaskStartScheduler();
  while(1);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void readMag(void *arg){
  while(1){

    
    Serial.print("X = ");
    Serial.println(board.readMagX(), 4);
    Serial.print(" Y = ");
    Serial.println(board.readMagY(), 4);
    Serial.print(" Z = ");
    Serial.println(board.readMagZ(), 4);
    
  
  
    vTaskDelay(1000);
  }
}


