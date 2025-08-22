/* mqtt data publishing, receiving script */
import { client } from "@/utils/mqtt";

type Callback<T> = (value: T) => void

let moistureCallback: Callback<number> | null = null
let lastIrrigationCallback: Callback<Date> | null = null;
let shadesCallback: Callback<{open:boolean; percent:number;}> | null = null

export function subscribeESP() {
  if (!client) return

  client.on("message", (topic, message) => {
    const msg = message.toString()

    switch (topic) {
      case "home/irrigation/moisture":
        moistureCallback?.(parseFloat(msg))
        break
      case "home/shade/state":
        const [open, percent] = msg.split(",").map(Number)
        shadesCallback?.({ open: Boolean(open), percent })
        break
      case "home/irrigation/last":
        lastIrrigationCallback?.(new Date(msg))
        break
    }
  });

  client.subscribe("home/irrigation/moisture")
  client.subscribe("home/shade/state")
  client.subscribe("home/irrigation/last")
}

export function onMoistureUpdate(cb:Callback<number>) {
  moistureCallback= cb
} 

export function onIrrigationUpdate(cb: Callback<Date>) {
  lastIrrigationCallback = cb
}

export function onShadesUpdate(cb:Callback<{open:boolean; percent:number;}>) {
  shadesCallback = cb
} 

export function triggerPump() {
  if (!client) return
  client.publish("home/irrigation/pump/cmd", "trigger")
}

export function setShades(open: boolean) {
  if (!client) return
  client.publish("home/shade/cmd", open ? "1" : "0")
}

export function setShadesPercent(percent: number) {
  if (!client) return
  client.publish("home/shade/position", percent.toString())
}

export function requestSoilMoisture() {
  if (!client) return
  client.publish("home/irrigation/telemetry/request", "moisture")
}

export function requestShadesState() {
  if (!client) return
  client.publish("home/shade/telemetry/request", "state")
}

export function requestLastIrrigation() {
  if (!client) return
  client.publish("home/irrigation/telemetry/request", "last")
}
