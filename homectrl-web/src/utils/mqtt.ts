/* main MQTT script */
import mqtt, { MqttClient } from "mqtt";

export let client: MqttClient | null = null;
const topicCallbacks: Record<string, ((msg: string) => void)[]> = {};

export function connectMQTT(brokerURL: string, brokerOptions?: mqtt.IClientOptions) {
  if (!client) {
    client = mqtt.connect(brokerURL, brokerOptions);
    client.on("message", (topic, msg) => {
      const callbacks = topicCallbacks[topic];
      if (callbacks) callbacks.forEach(cb => cb(msg.toString()));
    });
  }
  return client;
}

export function subscribe(topic: string, callback: (message: string) => void) {
  if (!client) return;
  if (!topicCallbacks[topic]) topicCallbacks[topic] = [];
  topicCallbacks[topic].push(callback);
  client.subscribe(topic);
}

export function publish(topic: string, message: string, retain = false) {
  if (!client) return;
  client.publish(topic, message, { qos: 1, retain });
}

export function disconnect() {
  if (!client) return;
  client.end();
  client = null;
}

