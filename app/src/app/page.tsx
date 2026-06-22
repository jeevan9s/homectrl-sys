"use client"
import { useEffect, useState } from "react"
import Home from "./home/page"
  const messages = [
    "initializing modules",
    "syncing devices",
    "almost set"
  ]

export default function Landing() {
  const [count, setCount] = useState(0)
  const [intervalTime, setIntervalTime] = useState(100)
  const [messageIndex, setMessageIndex] = useState(0)

  useEffect(()=> {
    

    const msgInterval = setInterval(() => {
      setMessageIndex((prev) => (prev + 1) % messages.length)
    }, 800)

    return () => clearInterval(msgInterval) 
  },[])

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
  if (count >= 100) return <Home />


return (
  <div className="font-sans flex flex-col items-center justify-center min-h-screen z-1 p-8 text-center lg:-translate-y-10">

    <h1 className="select-none text-white text-xl">welcome to homectrl.</h1>
    <h1 id="count" className="text-lg text-white/50 mt-10">
      {Math.round(count)}%
    </h1> 
    <p className="text-md text-white/30">{messages[messageIndex]}</p>
  </div>
)
}