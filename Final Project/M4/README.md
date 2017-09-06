1. Split Task.cpp into t-test.cpp, t.h, t.cpp.  File t-test.cpp contains main and the t.h/t.cpp file pair contains class TaskManager and class Task. This is essentially the same process we used to split taskreader.cpp into taskdump.cpp, util.h and util.cpp.  Program t-test and task should do the same thing.  We didn’t write any new code or change any of the existing code.  All we did is move the code around between three files.
2. Similarily split item.cpp into i-test.cpp, i.h and i.cpp. 
3. Also split order.cpp into o-test.cpp o.h and o.cpp. 
4. Create a new program iot.cpp.  This program reads all three data files.  Essentially, t-test.cpp, i-test.cpp, nd o-test.cpp are merged into iot.cpp. 
5. Referential integrity (consistency) checking.
