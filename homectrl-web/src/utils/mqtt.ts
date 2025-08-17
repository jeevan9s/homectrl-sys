import mqtt, { MqttClient} from "mqtt";

/* main MQTT script */
export let client: MqttClient | null = null

export function connectMQTT(brokerURL:string, brokerOptions?: mqtt.IClientOptions) {
    if (!client){
     client = mqtt.connect(brokerURL, brokerOptions)
    }
    return client 
}

export function subscribe(topic: string, callback: (message: string) => void) {
  if (!client) return
  client.subscribe(topic)
  client.on("message", (t, msg) => {
    if (t === topic) callback(msg.toString());
  })
}

export function publish(topic: string, message: string) {
  if (!client) return
  client.publish(topic, message)
}

export function disconnect() {
  if (!client) return
  client.end()
  client = null
}
