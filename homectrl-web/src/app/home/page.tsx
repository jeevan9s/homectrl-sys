"use client";
import { useState, useEffect } from "react";
import { motion, AnimatePresence } from "framer-motion";
import { Button } from "@/components/ui/button";
import {
  Card,
  CardHeader,
  CardContent,
  CardTitle,
  CardDescription,
} from "@/components/ui/card";

export default function Home() {
  return (
    <div
      id="page"
      className="font-sans select-none flex flex-col min-h-screen px-4 py-6 sm:px-6 md:px-10"
    >
      <div id="m-header-cntr" className="flex flex-col flex-1 gap-1">
        <h1 className="text-3xl sm:text-4xl font-semibold">homectrl</h1>
        <AnimatePresence>
          <motion.p
            className="text-sm text-white/70 flex items-center"
            initial={{ opacity: 0 }}
            animate={{ opacity: 1 }}
            exit={{ opacity: 0 }}
            transition={{ duration: 0.5 }}
            key="status"
          >
            <span className="text-xs">🟢</span> online
          </motion.p>
        </AnimatePresence>

      <Card className="mt-2">
  <CardHeader>
    <CardTitle>recent activity</CardTitle>
    <CardDescription>latest.</CardDescription>
  </CardHeader>
  <CardContent className="-mt-4">
    <ul className="space-y-2">
      <li className="flex justify-between text-sm">
        <span>activity 1</span>
        <time className="text-muted-foreground">2 hr ago</time>
      </li>
    </ul>
  </CardContent>
</Card>

        <div className="flex gap-4 justify-center items-center p-2 flex-wrap">
          {["overview", "irrigation", "shading"].map((section) => (
            <a  key={section} className="min-w-[80px]">
              {section}
            </a>
          ))}
        </div>
      </div>
    </div>
  );
}
