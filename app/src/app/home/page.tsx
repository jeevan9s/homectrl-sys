"use client";
import { useEffect, useRef, useState } from "react";
import { motion, AnimatePresence } from "framer-motion";
import {
  Card,
  CardHeader,
  CardContent,
  CardTitle,
  CardDescription,
} from "@/components/ui/card";
import { Switch } from "@/components/ui/switch";
import { Button } from "@/components/ui/button";
import SliderWithLabelDemo from "@/components/slider-06";
import MoistureGraph from "@/components/chart";
import { connectEsp, sendDashboardCommand } from "@/services/connect";
import parseControllerData from "@/services/fetchData";
import {
  DashboardCommands,
  DEFAULT_CONTROLLER_DATA,
  DEFAULT_ESP_IP,
  type ControllerData,
} from "@/types";

export default function Home() {
  const [activeSection, setActiveSection] = useState("overview");
  const [espIp] = useState(
    new URLSearchParams(window.location.search).get("esp") ?? DEFAULT_ESP_IP
  );
  const [connected, setConnected] = useState(false);
  const [controllerData, setControllerData] = useState<ControllerData>(
    DEFAULT_CONTROLLER_DATA
  );
  const wsRef = useRef<WebSocket | null>(null);
  const [shadePercent, setShadePercent] = useState([0]);

  useEffect(() => {
    const ws = connectEsp(
      espIp,
      (packet) => {
        const parsed = parseControllerData(packet);
        setControllerData(parsed);
        setShadePercent([parsed.stepper.shadePct]);
      },
      setConnected
    );

    wsRef.current = ws;

    return () => ws.close();
  }, [espIp]);

  return (
    <div
      id="page"
      className="font-sans select-none flex flex-col min-h-screen px-4 py-6 sm:px-6 md:px-10"
    >
      <div id="m-header-cntr" className="flex flex-col flex-1 gap-1">
        <h1 className="text-2xl sm:text-3xl md:text-4xl font-semibold">
          homectrl
        </h1>
        <AnimatePresence>
          <motion.p
            className="text-xs sm:text-sm text-white/70 flex items-center"
            initial={{ opacity: 0 }}
            animate={{ opacity: 1 }}
            exit={{ opacity: 0 }}
            transition={{ duration: 0.5 }}
            key="status"
          >
            <span className="text-[10px] sm:text-xs">
              {connected ? "🟢" : "🔴"}
            </span>{" "}
            {connected ? "online" : "offline"}
          </motion.p>
        </AnimatePresence>

        <Card className="mt-2">
          <CardHeader>
            <CardTitle className="text-base sm:text-lg">
              connection
            </CardTitle>
            <CardDescription className="text-sm sm:text-base">
              {connected ? "live telemetry" : "waiting for telemetry"}
            </CardDescription>
          </CardHeader>
          <CardContent className="-mt-4">
            <ul className="space-y-2">
              <li className="flex justify-between text-xs sm:text-sm">
                <span>esp endpoint</span>
                <time className="text-muted-foreground">{espIp}</time>
              </li>
            </ul>
          </CardContent>
        </Card>

        <h1 className="text-2xl sm:text-3xl md:text-4xl mt-10 font-semibold">
          dashboard
        </h1>

        <div className="flex justify-center gap-4 sm:gap-6 relative mt-2">
          {["overview", "irrigation", "shading"].map((section) => (
            <button
              key={section}
              onClick={() => setActiveSection(section)}
              className={`relative px-2 sm:px-4 py-2 text-sm cursor-pointer sm:text-base transition-colors ${
                activeSection === section ? "text-white" : "text-gray-500"
              }`}
            >
              {section}
              {activeSection === section && (
                <motion.div
                  layoutId="active-underline"
                  className="absolute left-0 right-0 bottom-0 h-[2px] bg-white"
                  transition={{ type: "spring", stiffness: 400, damping: 30 }}
                />
              )}
            </button>
          ))}
        </div>

        <div className="mt-6">
          <AnimatePresence mode="wait">
            {activeSection === "overview" && (
              <motion.div
                key="overview"
                initial={{ opacity: 0, y: 10 }}
                animate={{ opacity: 1, y: 0 }}
                exit={{ opacity: 0, y: -10 }}
                transition={{ duration: 0.3 }}
              >
                <div className="grid grid-cols-1 gap-4 mt-4">
                  <Card>
                    <CardHeader>
                      <CardTitle>shades</CardTitle>
                      <CardDescription>control blinds</CardDescription>
                    </CardHeader>
                    <CardContent className="flex justify-center items-center gap-4">
                      <span>{controllerData.stepper.enable ? "open" : "closed"}</span>
                      <Switch
                        checked={controllerData.stepper.enable > 0}
                        onCheckedChange={(checked) => {
                          sendDashboardCommand(
                            wsRef.current,
                            DashboardCommands.SHADE_PCT,
                            checked ? 100 : 0
                          );
                        }}
                      />
                    </CardContent>
                  </Card>

                  <div className="grid grid-cols-2 gap-4">
                    <Card>
                      <CardHeader>
                        <CardTitle>soil moisture</CardTitle>
                        <CardDescription>current soil moisture level</CardDescription>
                      </CardHeader>
                      <CardContent className="text-2xl font-semibold text-center">
                        {controllerData.sms1.moisture}%
                      </CardContent>
                    </Card>

                    <Card>
                      <CardHeader>
                        <CardTitle>last watering</CardTitle>
                        <CardDescription>most recent irrigation time</CardDescription>
                      </CardHeader>
                      <CardContent className="text-2xl font-semibold text-center">
                        {controllerData.pump1.enable ? "active" : "idle"}
                      </CardContent>
                    </Card>
                  </div>
                </div>
              </motion.div>
            )}
            {activeSection === "irrigation" && (
              <motion.div
                key="irrigation"
                initial={{ opacity: 0, y: 10 }}
                animate={{ opacity: 1, y: 0 }}
                exit={{ opacity: 0, y: -10 }}
                transition={{ duration: 0.3 }}
              >
                <div className="flex flex-col items-center gap-4 mt-4">
                  <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6 w-full max-w-6xl">
                    <Card className="w-full">
                      <CardHeader>
                        <CardTitle>last watering</CardTitle>
                        <CardDescription>most recent irrigation time</CardDescription>
                      </CardHeader>
                      <CardContent className="text-2xl font-semibold text-center">
                        {controllerData.pump1.enable ? "enabled" : "disabled"}
                      </CardContent>
                    </Card>

                    <Card className="w-full">
                      <CardHeader>
                        <CardTitle>pump control</CardTitle>
                        <CardDescription>manually water plant</CardDescription>
                      </CardHeader>
                      <CardContent className="flex justify-center items-center gap-4">
                        <Button
                          className="hover:bg-green-950 hover:font-bold"
                          onClick={() => {
                            sendDashboardCommand(
                              wsRef.current,
                              DashboardCommands.IRRIGATE_1,
                              controllerData.pump1.enable ? 0 : 1
                            );
                          }}
                        >
                          {controllerData.pump1.enable ? "stop" : "irrigate"}
                        </Button>
                      </CardContent>
                    </Card>

                    <Card className="w-full">
                      <CardHeader>
                        <CardTitle>soil moisture</CardTitle>
                        <CardDescription>current soil moisture level</CardDescription>
                      </CardHeader>
                      <CardContent className="text-2xl font-semibold text-center">
                        {controllerData.sms1.moisture}%
                      </CardContent>
                    </Card>
                  </div>

                  <div className="w-full max-w-6xl mt-6 flex justify-center">
                    <Card className="w-full lg:w-4/5">
                      <CardHeader>
                        <CardTitle>soil moisture graph</CardTitle>
                        <CardDescription>moisture vs time</CardDescription>
                      </CardHeader>
                      <CardContent className="h-64">
                        <MoistureGraph moisture={controllerData.sms1.moisture} />
                      </CardContent>
                    </Card>
                  </div>
                </div>
              </motion.div>
            )}
            {activeSection === "shading" && (
              <motion.div
                key="shading"
                initial={{ opacity: 0, y: 10 }}
                animate={{ opacity: 1, y: 0 }}
                exit={{ opacity: 0, y: -10 }}
                transition={{ duration: 0.3 }}
              >
                <div className="grid grid-cols-1 gap-4 mt-4">
                  <Card>
                    <CardHeader>
                      <CardTitle>shades</CardTitle>
                      <CardDescription>control blinds</CardDescription>
                    </CardHeader>
                    <CardContent className="flex justify-center items-center gap-4">
                      <span>{controllerData.stepper.enable ? "open" : "closed"}</span>
                      <Switch
                        checked={controllerData.stepper.enable > 0}
                        onCheckedChange={(checked) => {
                          sendDashboardCommand(
                            wsRef.current,
                            DashboardCommands.SHADE_PCT,
                            checked ? 100 : 0
                          );
                        }}
                      />
                    </CardContent>
                  </Card>

                  <Card>
                    <CardHeader>
                      <CardTitle>shading percent</CardTitle>
                      <CardDescription>precise blind adjustment</CardDescription>
                    </CardHeader>
                    <CardContent className="text-2xl font-semibold text-center">
                      <div className="flex justify-center">
                        <SliderWithLabelDemo
                          value={shadePercent}
                          onValueChange={(value) => {
                            setShadePercent(value);
                            setControllerData((prev) => ({
                              ...prev,
                              stepper: {
                                ...prev.stepper,
                                shadePct: value[0],
                              },
                            }));
                            sendDashboardCommand(
                              wsRef.current,
                              DashboardCommands.SHADE_PCT,
                              value[0]
                            );
                          }}
                        />
                      </div>
                    </CardContent>
                  </Card>
                </div>
              </motion.div>
            )}
          </AnimatePresence>
        </div>
      </div>
    </div>
  );
}
