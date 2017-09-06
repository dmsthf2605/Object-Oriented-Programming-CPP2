1. Verify each of the item, and order data files from the project website are read successfully by your CSV file reader..  
2. Copy Task.cpp to Item.cpp. 
3. Hack Item.cpp to process item data: read it, parse it, print it, graph it. 
4. Copy Item.cpp to Order.cpp 
5. Hack Order.cpp to process order data: read it, parse it, print it, graph it. 
6. Split Task.cpp into t-test.cpp, t.h, t.cpp.  File t-test.cpp contains main and the t.h/t.cpp comb contains class TaskManager and class Task. This is essentially the same process we used to split taskreader.cpp into taskdump.cpp, util.h and util.cpp.  Program t-test and task should doen the same thing.  All we did is move the code around into three files. 
7. Similarily split item.cpp into i-test.cpp, i.h and i.cpp. 
8. Also split oreder.cpp into o-test.cpp o.h and o.cpp. 
9. Consistency checking.
Task possibly references an accept and a reject task. Item references an installer and a remover task. Order data references items. We need to verify these references exist.
