"use client"
import { useEffect, useState } from "react"

export default function Lanading() {
  const [count, setCount] = useState(0)
  const [intervalTime, setIntervalTime] = useState(100)

  const incrementVal = (currCount: number): number => {
    if (currCount < 20) return 4.5
    if (currCount < 40) return 3
    if (currCount < 60) return 5
    if (currCount < 75) return 9
    if (currCount < 90) return 7
    return 3
  }

  useEffect(() => {
    const interval = setInterval(() => {
      setCount(prev => {
        if (prev >= 100) return 100

        const increment = incrementVal(prev)
        const newCount = Math.min(prev + increment, 100)

        
        if (newCount < 20) setIntervalTime(100)
        else if (newCount < 50) setIntervalTime(92)
        else if (newCount < 75) setIntervalTime(82)
        else setIntervalTime(75)

        return newCount
      })
    }, intervalTime)

    return () => clearInterval(interval)
  }, [intervalTime])

  return (
    <div className="font-sans items-center justify-items-center min-h-screen p-8 pb-1 gap-2 sm:p-20 bg-black">
      <h1 className="select-none mt-20 text-white text-xl">welcome to homectrl.</h1>
      <h1 id="count" className="text-lg text-white/50">
        {Math.round(count)}%
      </h1>
    </div>
  );
}