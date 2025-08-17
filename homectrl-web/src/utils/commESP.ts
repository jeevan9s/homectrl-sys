/* mqtt data publishing, receiving script */
import { client } from "@/utils/mqtt";

type Callback<T> = (value: T) => void

// callback storage 
let moistureCallback: Callback<number> | null = null
let lastIrrigationCallback: Callback<Date> | null = null;
let shadesCallback: Callback<{open:boolean; percent:number;}> | null = null

export function subscribeESP() {
  if (!client) return

  client.on("message", (topic, message) => {
    const msg = message.toString()

    switch (topic) {
      case "home/soilMoisture":
        moistureCallback?.(parseFloat(msg))
        break
      case "home/shadesState":
        const [open, percent] = msg.split(",").map(Number)
        shadesCallback?.({ open: Boolean(open), percent })
        break
      case "home/lastIrrigation":
    lastIrrigationCallback?.(new Date(msg))
    break

    }
  });
  client.subscribe("home/soilMoisture")
  client.subscribe("home/shadesState")
  client.subscribe("home/lastIrrigation")
}

// ui updates
export function onMoistureUpdate(cb:Callback<number>) {
    moistureCallback= cb
} 

export function onIrrigationUpdate(cb: Callback<Date>) {
    lastIrrigationCallback = cb
}

export function onShadesUpdate(cb:Callback<{open:boolean; percent:number;}>) {
    shadesCallback = cb
} 

// publishing 
export function triggerPump() {
  if (!client) return
  client.publish("home/pump", "trigger")
}

export function setShades(open: boolean) {
  if (!client) return
  client.publish("home/shades/set", open ? "1" : "0")
}

export function setShadesPercent(percent: number) {
  if (!client) return
  client.publish("home/shades/percent", percent.toString())
}

// requesting
export function requestSoilMoisture() {
  if (!client) return
  client.publish("home/soilMoisture/get", "")
}

export function requestShadesState() {
  if (!client) return
  client.publish("home/shadesState/get", "")
}

export function requestLastIrrigation() {
  if (!client) return
  client.publish("home/lastIrrigation/get", "")
}



