#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

LOG_FILE="$SCRIPT_DIR/ftp_usage.log"

echo "FTP Supervisor started. Logging to: $LOG_FILE"

while true; do
    TIMESTAMP=$(date '+%Y-%m-%d %H:%M:%S')

    echo "[$TIMESTAMP] Checking for ftp commands..."

    FTP_PROCESSES=$(ps aux | grep '[f]tp' | grep -v "$0")

    if [ ! -z "$FTP_PROCESSES" ]; then
        echo "$FTP_PROCESSES" | while read -r line; do
            USER=$(echo "$line" | awk '{print $1}')
            COMMAND=$(echo "$line" | awk '{$1=$2=$3=$4=$5=$6=$7=""; print $0}')
            SERVER=$(echo "$COMMAND" | grep -oP 'ftp\s+\K\S+' || echo "Unknown")

            echo "[$TIMESTAMP] User: $USER | Server: $SERVER" >> "$LOG_FILE"
        done
    fi

    sleep 5
done
