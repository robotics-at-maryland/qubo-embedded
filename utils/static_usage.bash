#!/usr/bin/env bash

SRAM=32768
FLASH=262144

OUTPUT=$(arm-none-eabi-size $1)

TEXT_SIZE=$(echo "$OUTPUT" | sed -n '2 p' | awk '{print $1}')
DATA_SIZE=$(echo "$OUTPUT" | sed -n '2 p' | awk '{print $2}')
BSS_SIZE=$(echo "$OUTPUT" | sed -n '2 p' | awk '{print $3}')

FLASH_BYTES=$(echo $(($TEXT_SIZE + $DATA_SIZE)))
SRAM_BYTES=$(echo $(($DATA_SIZE + $BSS_SIZE)))

FLASH_USAGE_PCT=$(echo "(100 * ($FLASH_BYTES)) / $FLASH" | bc -l)
FLASH_AVAILABLE=$(echo "(100 - ($FLASH_USAGE_PCT))" | bc -l)
SRAM_USAGE_PCT=$(echo "(100 * ($SRAM_BYTES)) / $SRAM" | bc -l)
SRAM_AVAILABLE=$(echo "(100 - ($SRAM_USAGE_PCT))" | bc -l)

FLASH_PCT_STR=$(printf "%.2f %%" $FLASH_USAGE_PCT)
FLASH_AVAIL_STR=$(printf "%.2f %%" $FLASH_AVAILABLE)
SRAM_PCT_STR=$(printf "%.2f %%" $SRAM_USAGE_PCT)
SRAM_AVAIL_STR=$(printf "%.2f %%" $SRAM_AVAILABLE)

printf "\n================================================================="
printf "\n==================== STATIC USAGE STATISTICS ===================="
printf "\n=================================================================\n\n"


printf "         TYPE       %-15s%-15s%-10s\n" "BYTES" "USED" "FREE"
printf "         ------------------------------------------------\n"
printf "         FLASH      %-15d%-15s%-10s\n" $FLASH_BYTES "$FLASH_PCT_STR" "$FLASH_AVAIL_STR"
printf "         RAM        %-15d%-15s%-10s\n\n" $SRAM_BYTES "$SRAM_PCT_STR" "$SRAM_AVAIL_STR"
