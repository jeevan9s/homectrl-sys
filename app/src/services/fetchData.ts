import {
  type ControllerData,
  type PumpData,
  DEFAULT_CONTROLLER_DATA,
  type FSWData,
  type StepMotorData,
  type SMSData,
} from "@/types";

function parsePumpData(pump: any): PumpData {
  return {
    state: pump?.state ?? 0,
    enable: pump?.enable ?? 0,
  };
}

function parseStepMotorData(stepper: any): StepMotorData {
  return {
    state: stepper?.state ?? 0,
    enable: stepper?.enable ?? 0,
    shadePct: stepper?.shadePct ?? 0,
  };
}

function parseSMSData(sens: any): SMSData {
  return {
    raw: sens?.raw ?? 0,
    moisture: sens?.moisture ?? 0,
    hydrated: sens?.hydrated ?? sens?.isHydrated ?? false,
  };
}

function parseFSWData(sw: any): FSWData {
  return {
    empty: sw?.empty ?? sw?.tankStatus ?? true,
  };
}

export default function parseControllerData(data: any): ControllerData {
  return {
    ...DEFAULT_CONTROLLER_DATA,
    pump1: parsePumpData(data?.PUMP1 ?? data?.pump1),
    pump2: parsePumpData(data?.PUMP2 ?? data?.pump2),
    stepper: parseStepMotorData(data?.STEP ?? data?.stepper),
    sms1: parseSMSData(data?.SMS1 ?? data?.sms1 ?? data?.sens1),
    sms2: parseSMSData(data?.SMS2 ?? data?.sms2 ?? data?.sens2),
    fsw: parseFSWData(data?.FSW ?? data?.fsw),
  };
}
