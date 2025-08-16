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

export default function Irrigation() {
    const [shadesOpen, setShadesOpen] = useState(true);

    return (
        <div>
                <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-4 mt-4">

      <Card className="sm:col-span-1">
        <CardHeader>
          <CardTitle>shades</CardTitle>
          <CardDescription>control blinds</CardDescription>
        </CardHeader>
        <CardContent className="flex justify-center items-center gap-4">
          <span>{shadesOpen ? "open" : "closed"}</span>
          <Switch checked={shadesOpen} onCheckedChange={setShadesOpen} />
        </CardContent>
      </Card>

      <Card className="sm:col-span-2 lg:col-span-1">
        <CardHeader>
          <CardTitle>soil moisture</CardTitle>
          <CardDescription>current soil moisture level</CardDescription>
        </CardHeader>
        <CardContent className="text-2xl font-semibold text-center">
          62%
        </CardContent>
      </Card>

      <Card className="sm:col-span-1">
        <CardHeader>
          <CardTitle>last watering</CardTitle>
          <CardDescription>ost recent irrigation time</CardDescription>
        </CardHeader>
        <CardContent className="text-2xl font-semibold text-center">
          2 hr ago
        </CardContent>
      </Card>
    </div>
        </div>
    )
}