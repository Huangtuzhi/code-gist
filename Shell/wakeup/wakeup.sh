#!/bin/bash
#.wakeup

# Wait wifi connect
sleep 2s
query_wifi_name=`system_profiler SPAirPortDataType | awk -F':' '/Current Network Information:/{
 getline
 sub(/^ */,"")
 sub(/:$/,"")
 print
}'`

# If not located in Tecent Building Wifi
if [ "$query_wifi_name"x != "Tencent-WiFi"x ];then
    echo "`date` -- Not In Tencent Building" >> /tmp/wakeup.log
    exit 0
fi

# Open Sync Link
open /Users/titus/Library/PowerSyncKMLinkFull/PowerSyncKMLink.app
echo "`date` -- Open SyncKMLink | SamabaSvr" >> /tmp/wakeup.log

# Open Samba Server
exec osascript <<EOF
	tell application "Finder"
		open location "smb://10.123.*"
	end tell
EOF