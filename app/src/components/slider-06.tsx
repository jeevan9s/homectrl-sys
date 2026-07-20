"use client";

import { Slider } from "@/components/ui/slider";

export default function SliderWithLabelDemo({
  value,
  onValueChange,
}: {
  value: number[];
  onValueChange: (value: number[]) => void;
}) {
  return (
    <div className="w-full max-w-sm flex items-center gap-2">
      <Slider value={value} onValueChange={onValueChange} max={100} step={1} />
      <span className="w-[5ch]">{value[0]}%</span>
    </div>
  );
}
