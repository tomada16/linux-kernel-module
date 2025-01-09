#!/bin/bash

SOURCE="$@"
BACKUP_DIR="/backup"
LOG_FILE="/backup/backup_log.txt"

DATE=$(date +"%Y-%m-%d")
BACKUP_NAME="backup_$DATE.tar.gz"
BACKUP_PATH="$BACKUP_DIR/$BACKUP_NAME"

echo "$(date +"%Y-%m-%d %H:%M:%S") - Tworzenie kopi zapasowej" >> "$LOG_FILE"

if tar -czf "$BACKUP_PATH" $SOURCE >> "$LOG_FILE" 2>&1; then
	echo "$(date +"%Y-%m-%d %H:%M:%S") - Kopia zapaswona utworzona" >> "$LOG_FILE"
else
	echo "$(date +"%Y-%m-%d %H:%M:%S") - Błąd podczas tworzenia kopii zapasowej" >> "$LOG_FILE"
fi