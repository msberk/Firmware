/****************************************************************************
 *
 *   Copyright (c) 2013, 2014 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/*
 * @file aa241x_high_data_struct.h
 *
 * Structure for the data to be sent from this module
 * (the high priority module) to the low priority module.
 *
 *  @author Adrien Perkins		<adrienp@stanford.edu>
 *  @author YOUR NAME			<YOU@EMAIL.COM>
 */
#ifndef AA241X_HIGH_DATA_STRUCT_H_
#define AA241X_HIGH_DATA_STRUCT_H_

/**
 * This is the structure that will contain the data to be sent
 * from the high priority thread to the low priority thread.
 *
 * NOTE: do not edit the define name (HIGH_FIELD#), but please
 * do change variable_name# to be your desired variable names.
 *
 * NOTE: any fields you add to this structure will NOT be logged
 * or sent to the ground station, therefore it is recommended
 * you DO NOT ADD FIELDS TO THIS STRUCT.
 *
 * You may also change the data type of fields to one of the following:
 * boolean, int (of any size and type)
 * Though note that all the data will be logged as a float.
 *
 */

// list of variable names
#define HIGH_FIELD1 xOrigin;		/**< change variable_name1 to the desired variable name */
#define HIGH_FIELD2 yOrigin;
#define HIGH_FIELD3 inRedzone;
#define HIGH_FIELD4 wpreached_high;
#define HIGH_FIELD5 wet;
#define HIGH_FIELD6 pic_flag;
#define HIGH_FIELD7 run_flag;
#define HIGH_FIELD8 douse_flag;
#define HIGH_FIELD9 dist2dest;
#define HIGH_FIELD10 y;
#define HIGH_FIELD11 ydot;
#define HIGH_FIELD12 turn_degrees;
#define HIGH_FIELD13 turn_num;
#define HIGH_FIELD14 variable_name14;
#define HIGH_FIELD15 variable_name15;
#define HIGH_FIELD16 variable_name16;



/**
 * This string is a list of labels for each field in the log file.
 *
 * Feel free to edit f## to the desired name, but please note length of each
 * label must be less than 3 char per label!!!!
 *
 * THIS STRING MUST BE < 64 CHARS LONG AND CONTAIN 16 LABELS, IF IT DOES NOT
 * MEET THESE REQUIREMENTS, LOGGING WILL FAIL!!!!!!
 *
 */
#define HIGH_DATA_LABELS "xO,yO,f03,f04,f05,f06,f07,f08,d2d,y,yd,td,tn,f14,f15,f16"

struct aa241x_high_data_s {
	float HIGH_FIELD1;
	float HIGH_FIELD2;
	float HIGH_FIELD3;
	float HIGH_FIELD4;
	float HIGH_FIELD5;
	float HIGH_FIELD6;
	float HIGH_FIELD7;
	float HIGH_FIELD8;
	float HIGH_FIELD9;
	float HIGH_FIELD10;
	float HIGH_FIELD11;
	float HIGH_FIELD12;
	float HIGH_FIELD13;
	float HIGH_FIELD14;
	float HIGH_FIELD15;
	float HIGH_FIELD16;
};


#endif /* AA241X_HIGH_DATA_STRUCT_H_ */
