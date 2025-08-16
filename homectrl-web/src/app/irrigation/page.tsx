"use client";
import { Card, CardHeader, CardContent, CardTitle, CardDescription } from "@/components/ui/card";
import MoistureGraph from "@/components/chart";
import { Button } from "@/components/ui/button";

export default function Irrigation() {
  return (
    <div className="flex flex-col items-center gap-4 mt-4">

      <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6 w-full max-w-6xl">

        <Card className="w-full">
          <CardHeader>
            <CardTitle>last watering</CardTitle>
            <CardDescription>most recent irrigation time</CardDescription>
          </CardHeader>
          <CardContent className="text-2xl font-semibold text-center">
            2 hr ago
          </CardContent>
        </Card>

        <Card className="w-full">
          <CardHeader>
            <CardTitle>pump control</CardTitle>
            <CardDescription>manually water plant</CardDescription>
          </CardHeader>
          <CardContent className="flex justify-center items-center gap-4">
            <Button className="hover:bg-green-950 hover:font-bold">
              irrigate
            </Button>
          </CardContent>
        </Card>

        <Card className="w-full">
          <CardHeader>
            <CardTitle>soil moisture</CardTitle>
            <CardDescription>current soil moisture level</CardDescription>
          </CardHeader>
          <CardContent className="text-2xl font-semibold text-center">
            62%
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
            <MoistureGraph />
          </CardContent>
        </Card>
      </div>

    </div>
  );
}
