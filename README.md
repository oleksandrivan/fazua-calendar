# Fazua Calendar
Fazua's calendar exercise

##Compile instructions
By running the next command should be enough to compile 

```$ make```

##Execution
```$ ./calendar <SpeedFactor>```

Where SpeedFactor is the factor to increase program simulation time. '1' by Default if ommited

##Notes
- Make sure file schedule.txt is present where program is executed
- Make sure the activity format is correct: 
    
    - Start time , End time , Activity name
    - Eg: 21:00 , 23:59 , Dinner
##Additional
You can check memory leaks with Valgrind by running
```$ bash leakcheck.sh```