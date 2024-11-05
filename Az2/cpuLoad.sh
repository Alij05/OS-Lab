#!/bin/bash

while true
do
   
    echo "CPU Load: $(uptime | awk -F'load average:' '{ print $2 }')"
    
    sleep 5   

done

#برای پایش دائمی CPU Load در یک سیستم لینوکسی به کمک بش اسکریپت، می‌توان از دستور top یا uptime استفاده کرد.دستور uptime، زمان جاری و زمان کارکرد سیستم و میانگین لود را نمایش میدهد.دستور awk فقط قسمت میانگین لود را استخراج میکند.
