export enum DashboardCommands {
    IRRIGATE_1 = 0,
    IRRIGATE_2 = 1,
    SHADE_DEFAULT = 2,
    SHADE_PCT = 3,
}

enum ActuatorState
{
    IDLE,
    ENERGIZING,
    RUNNING,
    FAULT
};

export interface PumpData {
    state: ActuatorState; 
    enable: number;
}

export interface StepMotorData {
    state: ActuatorState; 
    enable: number; 
    shadePct: number; 
}

export interface SMSData {
    raw: number;
    moisture: number; 
    hydrated: boolean; 
}

export interface FSWData {
    empty: boolean; 
}

export interface ControllerData {
    pump1: PumpData; 
    pump2: PumpData; 

    stepper: StepMotorData; 

    sms1: SMSData; 
    sms2: SMSData; 

    fsw: FSWData; 
}


export const DEFAULT_CONTROLLER_DATA: ControllerData = { 
  pump1: { state: ActuatorState.IDLE, enable: 0 },
  pump2: { state: ActuatorState.IDLE, enable: 0 },
  stepper: { state: ActuatorState.IDLE, enable: 0, shadePct: 0 },
  sms1: { raw: 0, moisture: 0, hydrated: false },
  sms2: { raw: 0, moisture: 0, hydrated: false },
  fsw: { empty: true }
};

export const DEFAULT_ESP_IP = "10.0.0.169";
