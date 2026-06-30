"use client";
import { useState } from "react";
import {
  Card,
  CardHeader,
  CardContent,
  CardTitle,
  CardDescription,
} from "@/components/ui/card";
import { Switch } from "@/components/ui/switch";
import SliderWithLabelDemo from "@/components/slider-06";

export default function Shading() {
  const [shadesOpen, setShadesOpen] = useState(true);

  return (
    <div className="grid grid-cols-1 gap-4 mt-4">
      <Card>
        <CardHeader>
          <CardTitle>shades</CardTitle>
          <CardDescription>control blinds</CardDescription>
        </CardHeader>
        <CardContent className="flex justify-center items-center gap-4">
          <span>{shadesOpen ? "open" : "closed"}</span>
          <Switch checked={shadesOpen} onCheckedChange={setShadesOpen} />
        </CardContent>
      </Card>

      <Card>
        <CardHeader>
          <CardTitle>shading percent</CardTitle>
          <CardDescription>precise blind adjustment</CardDescription>
        </CardHeader>
        <CardContent className="text-2xl font-semibold text-center">
          <div className="flex justify-center">
            <SliderWithLabelDemo />
          </div>
        </CardContent>
      </Card>
    </div>
  );
}
