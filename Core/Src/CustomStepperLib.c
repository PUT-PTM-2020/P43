#include "CustomStepperLib.h"

/* This fragment might need to be changed based on STM config */

uint16_t M_PIN1 = GPIO_PIN_1;
uint16_t M_PIN2 = GPIO_PIN_2;
uint16_t M_PIN3 = GPIO_PIN_3;
uint16_t M_PIN4 = GPIO_PIN_4;

void delay(uint16_t miliseconds)
{
	HAL_Delay(miliseconds);
}
/* End of this fragment */

void stepper_motor_set_rpm(uint8_t rpm)
{ 
	delay(60000 / rpm / spr); //60000000us = 1 min
}

void stepper_motor_full_drive(int step_id)
{
	switch (step_id) {
	case 0:
		HAL_GPIO_WritePin(GPIOA, M_PIN1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, M_PIN2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, M_PIN3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, M_PIN4, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, M_PIN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, M_PIN2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, M_PIN3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, M_PIN4, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, M_PIN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, M_PIN2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, M_PIN3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, M_PIN4, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA, M_PIN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, M_PIN2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, M_PIN3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, M_PIN4, GPIO_PIN_SET);
		break;
	}
}

void stepper_motor_rotate_by_angle(float rotation_angle, bool dir, uint8_t rpm)
{
	float angle_per_seq = (float)360 / 512; //Amount of degrees in a full rotation divided by the number of sequences
	int n_of_sequences = rotation_angle / angle_per_seq;

	for (int sq = 0; sq < n_of_sequences; sq++) {
		if (dir == 1) 					  //dir=1 for clockwise rotation
			for (int8_t st = 0; st <= 3; st++) {
				stepper_motor_full_drive(st);
				/*The set_rpm function is called after drive
				function because it achieves rpm control by
				adjusting delay*/
				stepper_motor_set_rpm(rpm);
			}
		else if (dir == 0) {				  //dir=0 for anti-clockwise rotation
			for (int8_t st = 3; st >= 0; st--) {
				stepper_motor_full_drive(st);
				stepper_motor_set_rpm(rpm);
			}
		}
	}

}
