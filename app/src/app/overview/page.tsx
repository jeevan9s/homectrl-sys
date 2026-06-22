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

export default function Overview() {
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

      <div className="grid grid-cols-2 gap-4">
        <Card>
          <CardHeader>
            <CardTitle>soil moisture</CardTitle>
            <CardDescription>current soil moisture level</CardDescription>
          </CardHeader>
          <CardContent className="text-2xl font-semibold text-center">
            62%
          </CardContent>
        </Card>

        <Card>
          <CardHeader>
            <CardTitle>last watering</CardTitle>
            <CardDescription>most recent irrigation time</CardDescription>
          </CardHeader>
          <CardContent className="text-2xl font-semibold text-center">
            2 hr ago
          </CardContent>
        </Card>
      </div>
    </div>
  );
}
