/**
 * OBD_pids.h - OBD-II PID definitions for the OBD-Dos platform
 * Copyright (C) 2015 Josh Lubawy <jlubawy@gmail.com> <jlubawy@asu.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _OBD_PIDS_H_
#define _OBD_PIDS_H_

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
/* Source: https://en.wikipedia.org/wiki/OBD-II_PIDs#Mode_01 */
typedef enum {
    OBD_MODE_01_PID_SUPPORTED_01_20            = 0x00,  /* PIDs supported [01 - 20] */
    OBD_MODE_01_PID_MONITOR_STATUS             = 0x01,  /* Monitor status since DTCs cleared */
    OBD_MODE_01_PID_FREEZE_DTC                 = 0x02,  /* Freeze DTC */
    OBD_MODE_01_PID_FUEL_SYSTEM_STATUS         = 0x03,  /* Fuel system status */
    OBD_MODE_01_PID_CALC_ENGINE_LOAD           = 0x04,  /* Calculated engine load value */
    OBD_MODE_01_PID_ENGINE_COOLANT_TEMP        = 0x05,  /* Engine coolant temperature */
    OBD_MODE_01_PID_SHORT_TERM_FUEL_BANK_1     = 0x06,  /* Short term fuel % trim—Bank 1 */
    OBD_MODE_01_PID_LONG_TERM_FUEL_BANK_1      = 0x07,  /* Long term fuel % trim—Bank 1 */
    OBD_MODE_01_PID_SHORT_TERM_FUEL_BANK_2     = 0x08,  /* Short term fuel % trim—Bank 2 */
    OBD_MODE_01_PID_LONG_TERM_FUEL_BANK_2      = 0x09,  /* Long term fuel % trim—Bank 2 */
    OBD_MODE_01_PID_FUEL_PRESSURE              = 0x0A,  /* Fuel pressure */
    OBD_MODE_01_PID_INTAKE_MANIFOLD_PRESSURE   = 0x0B,  /* Intake manifold absolute pressure */
    OBD_MODE_01_PID_ENGINE_RPM                 = 0x0C,  /* Engine RPM */
    OBD_MODE_01_PID_VEHICLE_SPEED              = 0x0D,  /* Vehicle speed */
    OBD_MODE_01_PID_TIMING_ADVANCE             = 0x0E,  /* Timing advance */
    OBD_MODE_01_PID_INTAKE_AIR_TEMP            = 0x0F,  /* Intake air temperature */
    OBD_MODE_01_PID_MAF_AIR_FLOW_RATE          = 0x10,  /* MAF air flow rate */
    OBD_MODE_01_PID_THROTTLE_POSITION          = 0x11,  /* Throttle position */
    OBD_MODE_01_PID_SECONDARY_AIR_STATUS       = 0x12,  /* Commanded secondary air status */
    OBD_MODE_01_PID_O2_SENSORS_PRESENT_1       = 0x13,  /* Oxygen sensors present 1 */
    OBD_MODE_01_PID_O2_SENSOR_BANK_1_SENSOR_1  = 0x14,  /* Bank 1, Sensor 1 */
    OBD_MODE_01_PID_O2_SENSOR_BANK_1_SENSOR_2  = 0x15,  /* Bank 1, Sensor 2 */
    OBD_MODE_01_PID_O2_SENSOR_BANK_1_SENSOR_3  = 0x16,  /* Bank 1, Sensor 3 */
    OBD_MODE_01_PID_O2_SENSOR_BANK_1_SENSOR_4  = 0x17,  /* Bank 1, Sensor 4 */
    OBD_MODE_01_PID_O2_SENSOR_BANK_2_SENSOR_1  = 0x18,  /* Bank 2, Sensor 1 */
    OBD_MODE_01_PID_O2_SENSOR_BANK_2_SENSOR_2  = 0x19,  /* Bank 2, Sensor 2 */
    OBD_MODE_01_PID_O2_SENSOR_BANK_2_SENSOR_3  = 0x1A,  /* Bank 2, Sensor 3 */
    OBD_MODE_01_PID_O2_SENSOR_BANK_2_SENSOR_4  = 0x1B,  /* Bank 2, Sensor 4 */
    OBD_MODE_01_PID_STANDARDS                  = 0x1C,  /* OBD standards this vehicle conforms to */
    OBD_MODE_01_PID_O2_SENSORS_PRESENT_2       = 0x1D,  /* Oxygen sensors present 2 */
    OBD_MODE_01_PID_AUX_INPUT_STATUS           = 0x1E,  /* Auxiliary input status */
    OBD_MODE_01_PID_ENGINE_RUN_TIME            = 0x1F,  /* Run time since engine start */
    OBD_MODE_01_PID_SUPPORTED_21_40            = 0x20,  /* PIDs supported [21 - 40] */
    // OBD_MODE_01_PID_  = 0x21,  /* Distance traveled with malfunction indicator lamp (MIL) */
    // OBD_MODE_01_PID_  = 0x22,  /* Fuel Rail Pressure (relative to manifold vacuum) */
    // OBD_MODE_01_PID_  = 0x23,  /* Fuel Rail Pressure (diesel, or gasoline direct inject) */
    // OBD_MODE_01_PID_  = 0x24,  /* O2S1_WR_lambda(1) */
    // OBD_MODE_01_PID_  = 0x25,  /* O2S2_WR_lambda(1) */
    // OBD_MODE_01_PID_  = 0x26,  /* O2S3_WR_lambda(1) */
    // OBD_MODE_01_PID_  = 0x27,  /* O2S4_WR_lambda(1) */
    // OBD_MODE_01_PID_  = 0x28,  /* O2S5_WR_lambda(1) */
    // OBD_MODE_01_PID_  = 0x29,  /* O2S6_WR_lambda(1) */
    // OBD_MODE_01_PID_  = 0x2A,  /* O2S7_WR_lambda(1) */
    // OBD_MODE_01_PID_  = 0x2B,  /* O2S8_WR_lambda(1) */
    // OBD_MODE_01_PID_  = 0x2C,  /* Commanded EGR */
    // OBD_MODE_01_PID_  = 0x2D,  /* EGR Error */
    // OBD_MODE_01_PID_  = 0x2E,  /* Commanded evaporative purge */
    // OBD_MODE_01_PID_  = 0x2F,  /* Fuel Level Input */
    // OBD_MODE_01_PID_  = 0x30,  /* # of warm-ups since codes cleared */
    // OBD_MODE_01_PID_  = 0x31,  /* Distance traveled since codes cleared */
    // OBD_MODE_01_PID_  = 0x32,  /* Evap. System Vapor Pressure */
    // OBD_MODE_01_PID_  = 0x33,  /* Barometric pressure */
    // OBD_MODE_01_PID_  = 0x34,  /* O2S1_WR_lambda */
    // OBD_MODE_01_PID_  = 0x35,  /* O2S2_WR_lambda */
    // OBD_MODE_01_PID_  = 0x36,  /* O2S3_WR_lambda */
    // OBD_MODE_01_PID_  = 0x37,  /* O2S4_WR_lambda */
    // OBD_MODE_01_PID_  = 0x38,  /* O2S5_WR_lambda */
    // OBD_MODE_01_PID_  = 0x39,  /* O2S6_WR_lambda */
    // OBD_MODE_01_PID_  = 0x3A,  /* O2S7_WR_lambda */
    // OBD_MODE_01_PID_  = 0x3B,  /* O2S8_WR_lambda */
    // OBD_MODE_01_PID_  = 0x3C,  /* Catalyst Temperature */
    // OBD_MODE_01_PID_  = 0x3D,  /* Catalyst Temperature */
    // OBD_MODE_01_PID_  = 0x3E,  /* Catalyst Temperature */
    // OBD_MODE_01_PID_  = 0x3F,  /* Catalyst Temperature */
    OBD_MODE_01_PID_SUPPORTED_41_60  = 0x40,  /* PIDs supported [41 - 60] */
    // OBD_MODE_01_PID_  = 0x41,  /* Monitor status this drive cycle */
    // OBD_MODE_01_PID_  = 0x42,  /* Control module voltage */
    // OBD_MODE_01_PID_  = 0x43,  /* Absolute load value */
    // OBD_MODE_01_PID_  = 0x44,  /* Fuel/Air commanded equivalence ratio */
    // OBD_MODE_01_PID_  = 0x45,  /* Relative throttle position */
    // OBD_MODE_01_PID_  = 0x46,  /* Ambient air temperature */
    // OBD_MODE_01_PID_  = 0x47,  /* Absolute throttle position B */
    // OBD_MODE_01_PID_  = 0x48,  /* Absolute throttle position C */
    // OBD_MODE_01_PID_  = 0x49,  /* Accelerator pedal position D */
    // OBD_MODE_01_PID_  = 0x4A,  /* Accelerator pedal position E */
    // OBD_MODE_01_PID_  = 0x4B,  /* Accelerator pedal position F */
    // OBD_MODE_01_PID_  = 0x4C,  /* Commanded throttle actuator */
    // OBD_MODE_01_PID_  = 0x4D,  /* Time run with MIL */
    // OBD_MODE_01_PID_  = 0x4E,  /* Time since trouble codes cleared */
    // OBD_MODE_01_PID_  = 0x4F,  /* Maximum value for equivalence ratio, oxygen sensor voltage, oxygen sensor current, and intake manifold absolute pressure */
    // OBD_MODE_01_PID_  = 0x50,  /* Maximum value for air flow rate from mass air flow sensor */
    // OBD_MODE_01_PID_  = 0x51,  /* Fuel Type */
    // OBD_MODE_01_PID_  = 0x52,  /* Ethanol fuel % */
    // OBD_MODE_01_PID_  = 0x53,  /* Absolute Evap system Vapor Pressure */
    // OBD_MODE_01_PID_  = 0x54,  /* Evap system vapor pressure */
    // OBD_MODE_01_PID_  = 0x55,  /* Short term secondary oxygen sensor trim bank 1 and bank 3 */
    // OBD_MODE_01_PID_  = 0x56,  /* Long term secondary oxygen sensor trim bank 1 and bank 3 */
    // OBD_MODE_01_PID_  = 0x57,  /* Short term secondary oxygen sensor trim bank 2 and bank 4 */
    // OBD_MODE_01_PID_  = 0x58,  /* Long term secondary oxygen sensor trim bank 2 and bank 4 */
    // OBD_MODE_01_PID_  = 0x59,  /* Fuel rail pressure (absolute) */
    // OBD_MODE_01_PID_  = 0x5A,  /* Relative accelerator pedal position */
    // OBD_MODE_01_PID_  = 0x5B,  /* Hybrid battery pack remaining life */
    // OBD_MODE_01_PID_  = 0x5C,  /* Engine oil temperature */
    // OBD_MODE_01_PID_  = 0x5D,  /* Fuel injection timing */
    // OBD_MODE_01_PID_  = 0x5E,  /* Engine fuel rate */
    // OBD_MODE_01_PID_  = 0x5F,  /* Emission requirements to which vehicle is designed */
    OBD_MODE_01_PID_SUPPORTED_61_80  = 0x60,  /* PIDs supported [61 - 80] */
    // OBD_MODE_01_PID_  = 0x61,  /* Driver's demand engine - percent torque */
    // OBD_MODE_01_PID_  = 0x62,  /* Actual engine - percent torque */
    // OBD_MODE_01_PID_  = 0x63,  /* Engine reference torque */
    // OBD_MODE_01_PID_  = 0x64,  /* Engine percent torque data */
    // OBD_MODE_01_PID_  = 0x65,  /* Auxiliary input / output supported */
    // OBD_MODE_01_PID_  = 0x66,  /* Mass air flow sensor */
    // OBD_MODE_01_PID_  = 0x67,  /* Engine coolant temperature */
    // OBD_MODE_01_PID_  = 0x68,  /* Intake air temperature sensor */
    // OBD_MODE_01_PID_  = 0x69,  /* Commanded EGR and EGR Error */
    // OBD_MODE_01_PID_  = 0x6A,  /* Commanded Diesel intake air flow control and relative intake air flow position */
    // OBD_MODE_01_PID_  = 0x6B,  /* Exhaust gas recirculation temperature */
    // OBD_MODE_01_PID_  = 0x6C,  /* Commanded throttle actuator control and relative throttle position */
    // OBD_MODE_01_PID_  = 0x6D,  /* Fuel pressure control system */
    // OBD_MODE_01_PID_  = 0x6E,  /* Injection pressure control system */
    // OBD_MODE_01_PID_  = 0x6F,  /* Turbocharger compressor inlet pressure */
    // OBD_MODE_01_PID_  = 0x70,  /* Boost pressure control */
    // OBD_MODE_01_PID_  = 0x71,  /* Variable Geometry turbo (VGT) control */
    // OBD_MODE_01_PID_  = 0x72,  /* Wastegate control */
    // OBD_MODE_01_PID_  = 0x73,  /* Exhaust pressure */
    // OBD_MODE_01_PID_  = 0x74,  /* Turbocharger RPM */
    // OBD_MODE_01_PID_  = 0x75,  /* Turbocharger temperature */
    // OBD_MODE_01_PID_  = 0x76,  /* Turbocharger temperature */
    // OBD_MODE_01_PID_  = 0x77,  /* Charge air cooler temperature (CACT) */
    // OBD_MODE_01_PID_  = 0x78,  /* Exhaust Gas temperature (EGT) Bank 1 */
    // OBD_MODE_01_PID_  = 0x79,  /* Exhaust Gas temperature (EGT) Bank 2 */
    // OBD_MODE_01_PID_  = 0x7A,  /* Diesel particulate filter (DPF) */
    // OBD_MODE_01_PID_  = 0x7B,  /* Diesel particulate filter (DPF) */
    // OBD_MODE_01_PID_  = 0x7C,  /* Diesel Particulate filter (DPF) temperature */
    // OBD_MODE_01_PID_  = 0x7D,  /* NOx NTE control area status */
    // OBD_MODE_01_PID_  = 0x7E,  /* PM NTE control area status */
    // OBD_MODE_01_PID_  = 0x7F,  /* Engine run time */
    OBD_MODE_01_PID_SUPPORTED_81_A0  = 0x80,  /* PIDs supported [81 - A0] */
    // OBD_MODE_01_PID_  = 0x81,  /* Engine run time for Auxiliary Emissions Control Device (AECD) */
    // OBD_MODE_01_PID_  = 0x82,  /* Engine run time for Auxiliary Emissions Control Device (AECD) */
    // OBD_MODE_01_PID_  = 0x83,  /* NOx sensor */
    // OBD_MODE_01_PID_  = 0x84,  /* Manifold surface temperature */
    // OBD_MODE_01_PID_  = 0x85,  /* NOx reagent system */
    // OBD_MODE_01_PID_  = 0x86,  /* Particulate matter (PM) sensor */
    // OBD_MODE_01_PID_  = 0x87,  /* Intake manifold absolute pressure */
    OBD_MODE_01_PID_SUPPORTED_A1_C0  = 0xA0,  /* PIDs supported [A1 - C0] */
    OBD_MODE_01_PID_SUPPORTED_C1_E0  = 0xC0,  /* PIDs supported [C1 - E0] */
    // OBD_MODE_01_PID_  = 0xC3,  /* Returns numerous data, including Drive Condition ID and Engine Speed */
    // OBD_MODE_01_PID_  = 0xC4,  /* B5 is Engine Idle Request */
    // OBD_MODE_01_PID_  = 0xB6,  /* is Engine Stop Request */
} ODB_Mode_01_Pid_t;


/*****************************************************************************/
/* Source: https://en.wikipedia.org/wiki/OBD-II_PIDs#Mode_02 */
typedef enum {
    OBD_MODE_02_UNDEFINED
} ODB_Mode_02_Pid_t;


/*****************************************************************************/
/* Source: https://en.wikipedia.org/wiki/OBD-II_PIDs#Mode_03 */
typedef enum {
    OBD_MODE_03_UNDEFINED
} ODB_Mode_03_Pid_t;


/*****************************************************************************/
/* Source: https://en.wikipedia.org/wiki/OBD-II_PIDs#Mode_04 */
typedef enum {
    OBD_MODE_04_UNDEFINED
} ODB_Mode_04_Pid_t;


/*****************************************************************************/
/* Source: https://en.wikipedia.org/wiki/OBD-II_PIDs#Mode_05 */
typedef enum {
    OBD_MODE_05_UNDEFINED
} ODB_Mode_05_Pid_t;


/*****************************************************************************/
/* Source: https://en.wikipedia.org/wiki/OBD-II_PIDs#Mode_09 */
typedef enum {
    OBD_MODE_09_UNDEFINED
} ODB_Mode_09_Pid_t;


#endif /* _OBD_PIDS_H_ */
