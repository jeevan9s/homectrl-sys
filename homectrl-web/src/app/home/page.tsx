"use client";
import { useState } from "react";
import { motion, AnimatePresence } from "framer-motion";
import {
  Card,
  CardHeader,
  CardContent,
  CardTitle,
  CardDescription,
} from "@/components/ui/card";

import Overview from "../overview/page";
import Irrigation from "../irrigation/page";
import Shading from "../shading/page";

export default function Home() {
  const [activeSection, setActiveSection] = useState("overview");

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
            <span className="text-[10px] sm:text-xs">🟢</span> online
          </motion.p>
        </AnimatePresence>

        <Card className="mt-2">
          <CardHeader>
            <CardTitle className="text-base sm:text-lg">
              recent activity
            </CardTitle>
            <CardDescription className="text-sm sm:text-base">
              latest.
            </CardDescription>
          </CardHeader>
          <CardContent className="-mt-4">
            <ul className="space-y-2">
              <li className="flex justify-between text-xs sm:text-sm">
                <span>activity 1</span>
                <time className="text-muted-foreground">2 hr ago</time>
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
                <Overview />
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
                <Irrigation />
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
                <Shading />
              </motion.div>
            )}
          </AnimatePresence>
        </div>
      </div>
    </div>
  );
}
